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
	string _name;
	uint8_t _id;
	int16_t _ulx,  _uly;
	int16_t _urx, _ury;
	int16_t _lrx, _lry;
	int16_t _llx, _lly;
	uint8_t _mask;
	uint8_t _flags;
	uint16_t _scale;
	float _centerX;
	float _centerY;
	vector<string> _neighbors;
public:
	Box();
	void load(XMLNode *node);
	void save(XMLNode *node);
	void prepare();
	string getName() { return _name; }
	uint8_t getID() { return _id; }
	uint8_t setID(uint8_t id) { _id = id; }
	int16_t getULX() { return _ulx; }
	int16_t getULY() { return _uly; }
	int16_t getURX() { return _urx; }
	int16_t getURY() { return _ury; }
	int16_t getLRX() { return _lrx; }
	int16_t getLRY() { return _lry; }
	int16_t getLLX() { return _llx; }
	int16_t getLLY() { return _lly; }
	uint8_t getMask() { return _mask; }
	uint8_t getFlags() { return _flags; }
	uint16_t getScale() { return _scale; }
	uint8_t getNumberOfNeighbors() { return _neighbors.size(); }
	string getNeighbor(uint8_t index) { return _neighbors[index]; }
	float getCenterX() { return _centerX; }
	float getCenterY() { return _centerY; }
	~Box();
};

class Scale
{
private:
	uint16_t _s1;
	uint16_t _y1;
	uint16_t _s2;
	uint16_t _y2;
public:
	Scale();
	void load(XMLNode *node);
	void save(XMLNode *node);
	uint16_t getS1() { return _s1; }
	uint16_t getY1() { return _y1; }
	uint16_t getS2() { return _s2; }
	uint16_t getY2() { return _y2; }
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
	vector<Node *> _neighbors;
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
	uint8_t getNumberOfNeighbors() { return _neighbors.size(); }
	Node *getNeighbor(uint8_t index) { return _neighbors[index]; }
	void addNeighbor(Node *neighbor) { _neighbors.push_back(neighbor); }
	float distanceSquared(Node *node);
	~Node();
};

class Matrix
{
private:
	vector<vector<uint8_t> > _from;
	vector<vector<uint8_t> > _to;
	vector<vector<uint8_t> > _dests;

	Node *AStar(vector<Node *> *open, vector<Node *> *closed, Node *goal);
public:
	Matrix(vector<Box *> *boxes);
	uint8_t getNumberOfEntries(uint8_t boxIndex) { return _from[boxIndex].size(); }
	uint8_t getFrom(uint8_t boxIndex, uint8_t index) { return _from[boxIndex][index]; }
	uint8_t getTo(uint8_t boxIndex, uint8_t index) { return _to[boxIndex][index]; }
	uint8_t getDest(uint8_t boxIndex, uint8_t index) { return _dests[boxIndex][index]; }
	~Matrix();
};

class Map
{
private:
	static const string XML_FILE_NAME;

	vector<Box *> _boxes;
	vector<Scale *> _scales;
	Matrix *_matrix;
public:
	static const uint8_t N_SLOTS;

	Map();
	void load(string dirName);
	void save(string dirName);
	void prepare();
	uint8_t getNumberOfBoxes() { return _boxes.size(); }
	Box *getBox(uint8_t index) { return _boxes[index]; }
	uint8_t getNumberOfScales() { return _scales.size(); }
	Scale *getScale(uint8_t index) { return _scales[index]; }
	Matrix *getMatrix() { return _matrix; }
	~Map();
};

#endif
