#ifndef _MAP_HPP_
#define _MAP_HPP_

#include <stdint.h>
#include <string>
#include <vector>
using namespace std;

class XMLNode;

class Box
{
private:
	int32_t _ulx,  _uly;
	int32_t _urx, _ury;
	int32_t _lrx, _lry;
	int32_t _llx, _lly;
	uint32_t _mask;
	uint32_t _flags;
	uint32_t _scaleSlot;
	uint32_t _scale;
	float _centerX;
	float _centerY;
	vector<uint8_t> _neighbours;
public:
	Box(XMLNode *node);
	int32_t getULX() { return _ulx; }
	int32_t getULY() { return _uly; }
	int32_t getURX() { return _urx; }
	int32_t getURY() { return _ury; }
	int32_t getLRX() { return _lrx; }
	int32_t getLRY() { return _lry; }
	int32_t getLLX() { return _llx; }
	int32_t getLLY() { return _lly; }
	uint32_t getMask() { return _mask; }
	uint32_t getFlags() { return _flags; }
	uint32_t getScaleSlot() { return _scaleSlot; }
	uint32_t getScale() { return _scale; }
	uint8_t getNumberOfNeighbours() { return _neighbours.size(); }
	uint8_t getNeighbour(uint8_t index) { return _neighbours[index]; }
	float getCenterX() { return _centerX; }
	float getCenterY() { return _centerY; }
	~Box();
};

class Scale
{
private:
	uint32_t _s1;
	uint32_t _y1;
	uint32_t _s2;
	uint32_t _y2;
public:
	Scale(XMLNode *node);
	uint32_t getS1() { return _s1; }
	uint32_t getY1() { return _y1; }
	uint32_t getS2() { return _s2; }
	uint32_t getY2() { return _y2; }
	~Scale();
};

class Node
{
private:
	uint8_t _id;
	Node *_parent;
	float _fCost;
	float _gCost;
	float _posX;
	float _posY;
	vector<Node *> _neighbours;
public:
	static bool compare(Node *node1, Node *node2);

	Node(uint8_t id, float posX, float posY);
	void init();
	uint8_t getID() { return _id; }
	Node *getParent() { return _parent; }
	void setParent(Node *parent) { _parent = parent; }
	float getFCost() { return _fCost; }
	void setFCost(float fCost) { _fCost = fCost; }
	float getGCost() { return _gCost; }
	void setGCost(float gCost) { _gCost = gCost; }
	float getPosX() { return _posX; }
	float getPosY() { return _posY; }
	uint8_t getNumberOfNeighbours() { return _neighbours.size(); }
	Node *getNeighbour(uint8_t index) { return _neighbours[index]; }
	void addNeighbour(Node *neighbour) { _neighbours.push_back(neighbour); }
	float distanceSquared(Node *node);
	~Node();
};

class Matrix
{
private:
	vector<vector<uint8_t> > _dests;

	Node *AStar(vector<Node *> *open, vector<Node *> *closed, Node *goal);
public:
	Matrix(vector<Box *> *boxes);
	uint8_t getDest(uint8_t indexA, uint8_t indexB) { return _dests[indexA][indexB]; }
	~Matrix();
};

class Map
{
private:
	vector<Box *> _boxes;
	vector<Scale *> _scales;
	Matrix *_matrix;
public:
	Map(string dirName);
	uint32_t getNumberOfBoxes() { return _boxes.size(); }
	Box *getBox(uint32_t index) { return _boxes[index]; }
	uint8_t getNumberOfScales() { return _scales.size(); }
	Scale *getScale(uint8_t index) { return _scales[index]; }
	Matrix *getMatrix() { return _matrix; }
	~Map();
};

#endif
