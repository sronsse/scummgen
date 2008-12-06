#include "Map.hpp"
#include <algorithm>
#include "util/Log.hpp"
#include "util/XMLFile.hpp"

Box::Box(XMLNode *node)
{
	_ulx = node->getChild("ulx")->getIntegerContent();
	_uly = node->getChild("uly")->getIntegerContent();
	_urx = node->getChild("urx")->getIntegerContent();
	_ury = node->getChild("ury")->getIntegerContent();
	_lrx = node->getChild("lrx")->getIntegerContent();
	_lry = node->getChild("lry")->getIntegerContent();
	_llx = node->getChild("llx")->getIntegerContent();
	_lly = node->getChild("lly")->getIntegerContent();
	_mask = node->getChild("mask")->getIntegerContent();
	_flags = node->getChild("flags")->getIntegerContent();
	_scaleSlot = node->getChild("scaleSlot")->getIntegerContent();
	_scale = node->getChild("scale")->getIntegerContent();

	int i = 0;
	XMLNode *child;
	while ((child = node->getChild("neighbour", i++)) != NULL)
		_neighbours.push_back(child->getIntegerContent());

	// We calculate here the barycenter of the box
	_centerX = (_ulx + _urx + _lrx + _llx) / 4.0f;
	_centerY = (_uly + _ury + _lry + _lly) / 4.0f;
}

Box::~Box()
{
}

Scale::Scale(XMLNode *node)
{
	Log::getInstance().write(LOG_INFO, "Scale\n");
	Log::getInstance().indent();

	_s1 = node->getChild("s1")->getIntegerContent();
	_y1 = node->getChild("y1")->getIntegerContent();
	_s2 = node->getChild("s2")->getIntegerContent();
	_y2 = node->getChild("y2")->getIntegerContent();

	Log::getInstance().unIndent();
}

Scale::~Scale()
{
}

bool Node::compare(Node *node1, Node *node2)
{
	return node1->_fCost > node2->_fCost;
}

Node::Node(uint8_t id, float posX, float posY)
{
	_id = id;
	_posX = posX;
	_posY = posY;
}

void Node::init()
{
	_parent = NULL;
	_fCost = 0;
	_gCost = 0;
}

float Node::distanceSquared(Node *node)
{
	float a = node->getPosX() - _posX;
	float b = node->getPosY() - _posY;
	return a * a + b * b;
}

Node::~Node()
{
}

Matrix::Matrix(vector<Box *> *boxes)
{
	Log::getInstance().write(LOG_INFO, "Building matrix...\n");
	Log::getInstance().indent();
	
	// Create nodes from boxes
	vector<Node *> nodes;
	for (int i = 0; i < boxes->size(); i++)
		nodes.push_back(new Node(i, (*boxes)[i]->getCenterX(), (*boxes)[i]->getCenterY()));

	// Add neighbours
	for (int i = 0; i < boxes->size(); i++)
		for (int j = 0; j < (*boxes)[i]->getNumberOfNeighbours(); j++)
			nodes[i]->addNeighbour(nodes[(*boxes)[i]->getNeighbour(j)]);

	// Calculate destinations using the A* algorithm between each box
	for (int i = 0; i < nodes.size(); i++)
	{
		vector<uint8_t> dests;
		for (int j = 0; j < nodes.size(); j++)
		{
			// Launch the A* algorithm
			vector<Node *> open;
			vector<Node *> closed;
			nodes[i]->init();
			open.push_back(nodes[i]);
			Node *dest = AStar(&open, &closed, nodes[j]);

			// Add the destination to our list (if no path is found, we push the start node)
			dests.push_back(dest != NULL ? dest->getID() : i);
			Log::getInstance().write(LOG_INFO, "A = %u, B = %u -> dest = %u\n", i, j, dests.back());
		}
		_dests.push_back(dests);
	}

	// Delete nodes
	for (int i = 0; i < nodes.size(); i++)
		delete nodes[i];

	Log::getInstance().unIndent();
}

Node *Matrix::AStar(vector<Node *> *open, vector<Node *> *closed, Node *goal)
{
	// If the open list is empty, it means no path exists
	if (open->empty())
		return NULL;
		
	// Get the open node with the best cost, i.e. the top open node
	Node *best = open->back();
	open->pop_back();

	// Check if the best node is our goal and in that case return the destination
	if (best == goal)
	{
		vector<Node *> path;
		Node *node = best;
		do
		{
			path.push_back(node);
			node = node->getParent();
		}
		while (node != NULL);

		// If the starting node is the ending node, we return the goal directly
		if (path.size() == 1)
			return goal;

		// We return the second box in the path
		return path[path.size() - 2];
	}
	
	// Add the best node to the closed list as we're treating it now
	closed->push_back(best);

	// Add neighbours to the open list if needed
	for (int i = 0; i < best->getNumberOfNeighbours(); i++)
	{
		// Get neighbour node
		Node *neighbour = best->getNeighbour(i);

		// Check if neighbour is in the closed list already
		bool found = false;
		for (int j = 0; j < closed->size(); j++)
			if ((*closed)[j] == neighbour)
			{
				found = true;
				break;
			}

		// If the neighbour is not in the closed list, we add it to the open list
		if (!found)
		{
			// Calculate A* costs
			float g = best->getGCost() + best->distanceSquared(neighbour);
			float h = neighbour->distanceSquared(goal);
			neighbour->setParent(best);
			neighbour->setGCost(g);
			neighbour->setFCost(g + h);
			open->push_back(neighbour);
			sort(open->begin(), open->end(), Node::compare);
		}
	}

	return AStar(open, closed, goal);
}

Matrix::~Matrix()
{
}

Map::Map(string dirName)
{
	Log::getInstance().write(LOG_INFO, "Map\n");
	Log::getInstance().indent();

	_matrix = NULL;

	XMLFile xmlFile;
	xmlFile.open(dirName + "map.xml");
	XMLNode *rootNode = xmlFile.getRootNode();

	if (rootNode == NULL)
	{
		Log::getInstance().write(LOG_WARNING, "Room doesn't contain any map !\n");
		return;
	}

	int i = 0;
	XMLNode *child;
	while ((child = rootNode->getChild("box", i++)) != NULL)
		_boxes.push_back(new Box(child));

	i = 0;
	while ((child = rootNode->getChild("scale", i++)) != NULL)
		_scales.push_back(new Scale(child));

	_matrix = new Matrix(&_boxes);

	Log::getInstance().unIndent();
}

Map::~Map()
{
	for (int i = 0; i < _boxes.size(); i++)
		delete _boxes[i];

	for (int i = 0; i < _scales.size(); i++)
		delete _scales[i];

	if (_matrix != NULL)
		delete _matrix;
}
