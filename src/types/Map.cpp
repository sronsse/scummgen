#include "Map.hpp"
#include <algorithm>
#include <map>
#include "util/IO.hpp"
#include "util/Log.hpp"
#include "util/XMLFile.hpp"

const string Map::XML_FILE_NAME = "map.xml";
const uint8_t Map::N_SLOTS = 4;

Box::Box():
_id(0),
_name(""),
_ulx(0),
_uly(0),
_urx(0),
_ury(0),
_lrx(0),
_lry(0),
_llx(0),
_lly(0),
_mask(0),
_flags(0),
_scale(0),
_centerX(0.0f),
_centerY(0.0f)
{
}

void Box::load(XMLNode *node)
{
	Log::write(LOG_INFO, "Box\n");
	Log::indent();

	_name = node->getChild("name")->getStringContent();
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
	_scale = node->getChild("scale")->getIntegerContent();

	int i = 0;
	XMLNode *child;
	while ((child = node->getChild("neighbor", i++)) != NULL)
		_neighbors.push_back(child->getStringContent());

	Log::unIndent();
}

void Box::save(XMLNode *node)
{
	Log::write(LOG_INFO, "Box\n");
	Log::indent();

	node->addChild(new XMLNode("name", _name));
	node->addChild(new XMLNode("ulx", _ulx));
	node->addChild(new XMLNode("uly", _uly));
	node->addChild(new XMLNode("urx", _urx));
	node->addChild(new XMLNode("ury", _ury));
	node->addChild(new XMLNode("lrx", _lrx));
	node->addChild(new XMLNode("lry", _lry));
	node->addChild(new XMLNode("llx", _llx));
	node->addChild(new XMLNode("lly", _lly));
	node->addChild(new XMLNode("mask", _mask));
	node->addChild(new XMLNode("flags", _flags));
	node->addChild(new XMLNode("scale", _scale));

	for (int i = 0; i < _neighbors.size(); i++)
		node->addChild(new XMLNode("neighbor", _neighbors[i]));

	Log::unIndent();
}

void Box::prepare()
{
	// We calculate here the barycenter of the box
	_centerX = (_ulx + _urx + _lrx + _llx) / 4.0f;
	_centerY = (_uly + _ury + _lry + _lly) / 4.0f;
}

Box::~Box()
{
}

Scale::Scale():
_s1(0),
_y1(0),
_s2(0),
_y2(0)
{
}

void Scale::load(XMLNode *node)
{
	Log::write(LOG_INFO, "Scale\n");
	Log::indent();

	_s1 = node->getChild("s1")->getIntegerContent();
	_y1 = node->getChild("y1")->getIntegerContent();
	_s2 = node->getChild("s2")->getIntegerContent();
	_y2 = node->getChild("y2")->getIntegerContent();

	Log::unIndent();
}

void Scale::save(XMLNode *node)
{
	Log::write(LOG_INFO, "Scale\n");
	Log::indent();

	node->addChild(new XMLNode("s1", _s1));
	node->addChild(new XMLNode("y1", _y1));
	node->addChild(new XMLNode("s2", _s2));
	node->addChild(new XMLNode("y2", _y2));

	Log::unIndent();
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
	Log::write(LOG_INFO, "Building matrix...\n");
	Log::indent();
	
	// Create nodes from boxes
	vector<Node *> nodes;
	map<string, uint8_t> indices;
	for (int i = 0; i < boxes->size(); i++)
	{
		Box *box = (*boxes)[i];
		indices[box->getName()] = i;
		Node *node = new Node(box->getID(), box->getCenterX(), box->getCenterY());
		nodes.push_back(node);
	}

	// Add neighbors
	for (int i = 0; i < boxes->size(); i++)
	{
		Box *box = (*boxes)[i];
		for (int j = 0; j < box->getNumberOfNeighbors(); j++)
			nodes[i]->addNeighbor(nodes[indices[box->getNeighbor(j)]]);
	}

	// Calculate destinations using the A* algorithm between each box
	for (int i = 0; i < nodes.size(); i++)
	{
		vector<uint8_t> from;
		vector<uint8_t> to;
		vector<uint8_t> dests;
		uint8_t lastDest = 0;
		for (int j = 0; j < nodes.size(); j++)
		{
			// Launch the A* algorithm
			vector<Node *> open;
			vector<Node *> closed;
			nodes[i]->init();
			open.push_back(nodes[i]);
			Node *dest = AStar(&open, &closed, nodes[j]);

			// If no path has been found, we reset lastDest to create a new entry next time
			if (dest == NULL)
				lastDest = 0;
			else
			{
				// If the current destination found is equal to the last one, we just increment the "to" field,
				// otherwise we create new entries
				if (dest->getID() == lastDest)
					to.back()++;
				else
				{
					from.push_back(nodes[j]->getID());
					to.push_back(nodes[j]->getID());
					dests.push_back(dest->getID());
					lastDest = dest->getID();
				}
			}
		}

		// Add entries 
		Log::write(LOG_INFO, "Box %u:\n", nodes[i]->getID());
		Log::indent();
		for (int j = 0; j < from.size(); j++)
			Log::write(LOG_INFO, "From %u to %u -> dest = %u\n", from[j], to[j], dests[j]);
		Log::unIndent();
		_from.push_back(from);
		_to.push_back(to);
		_dests.push_back(dests);
	}

	// Delete nodes
	for (int i = 0; i < nodes.size(); i++)
		delete nodes[i];

	Log::unIndent();
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

	// Add neighbors to the open list if needed
	for (int i = 0; i < best->getNumberOfNeighbors(); i++)
	{
		// Get neighbor node
		Node *neighbor = best->getNeighbor(i);

		// Check if neighbor is in the closed list already
		bool found = false;
		for (int j = 0; j < closed->size(); j++)
			if ((*closed)[j] == neighbor)
			{
				found = true;
				break;
			}

		// If the neighbor is not in the closed list, we add it to the open list
		if (!found)
		{
			// Calculate A* costs
			float g = best->getGCost() + best->distanceSquared(neighbor);
			float h = neighbor->distanceSquared(goal);
			neighbor->setParent(best);
			neighbor->setGCost(g);
			neighbor->setFCost(g + h);
			open->push_back(neighbor);
			sort(open->begin(), open->end(), Node::compare);
		}
	}

	return AStar(open, closed, goal);
}

Matrix::~Matrix()
{
}

Map::Map():
_matrix(NULL)
{
}

void Map::load(string dirPath)
{
	Log::write(LOG_INFO, "Map\n");
	Log::indent();

	XMLFile xmlFile;
	xmlFile.open(dirPath + XML_FILE_NAME);
	XMLNode *rootNode = xmlFile.getRootNode();

	_description = rootNode->getChild("description")->getStringContent();
	Log::write(LOG_INFO, "description: %s\n", _description.c_str());

	int i = 0;
	XMLNode *child;
	while ((child = rootNode->getChild("box", i++)) != NULL)
	{
		Box *box = new Box();
		box->load(child);
		_boxes.push_back(box);
	}

	i = 0;
	while ((child = rootNode->getChild("scale", i++)) != NULL)
	{
		Scale *scale = new Scale();
		scale->load(child);
		_scales.push_back(scale);
	}
	for (i = _scales.size(); i < N_SLOTS; i++)
		_scales.push_back(new Scale());

	Log::unIndent();
}

void Map::save(string dirPath)
{
	Log::write(LOG_INFO, "Map\n");
	Log::indent();

	if (!IO::createDirectory(dirPath))
		Log::write(LOG_ERROR, "Could not create directory \"%s\" !\n", dirPath.c_str());

	XMLFile xmlFile;
	XMLNode *rootNode = new XMLNode("map");
	xmlFile.setRootNode(rootNode);

	rootNode->addChild(new XMLNode("description", _description));
	Log::write(LOG_INFO, "description: %s\n", _description.c_str());

	for (int i = 0; i < _boxes.size(); i++)
	{
		XMLNode *child = new XMLNode("box");
		rootNode->addChild(child);
		_boxes[i]->save(child);
	}

	for (int i = 0; i < _scales.size(); i++)
	{
		XMLNode *child = new XMLNode("scale");
		rootNode->addChild(child);
		_scales[i]->save(child);
	}

	if (!xmlFile.save(dirPath + XML_FILE_NAME))
		Log::write(LOG_ERROR, "Couldn't save costume to the specified directory !\n");

	Log::unIndent();
}

void Map::prepare()
{
	// Prepapre and set boxes IDs
	for (int i = 0; i < _boxes.size(); i++)
	{
		_boxes[i]->prepare();
		_boxes[i]->setID(i + 1);
	}

	// Construct matrix
	if (_matrix != NULL)
		delete _matrix;
	_matrix = new Matrix(&_boxes);
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
