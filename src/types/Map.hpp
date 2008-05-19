#ifndef _MAP_HPP_
#define _MAP_HPP_

#include <stdint.h>
#include <string>
#include <vector>
using namespace std;

class XMLNode;

class Matrix
{
private:
	vector<uint8_t> _boxAs;
	vector<uint8_t> _boxBs;
	vector<uint8_t> _dests;
public:
	Matrix(XMLNode *node);
	uint8_t getNumberOfEntries() { return _boxAs.size(); }
	uint8_t getBoxA(uint8_t index) { return _boxAs[index]; }
	uint8_t getBoxB(uint8_t index) { return _boxBs[index]; }
	uint8_t getDest(uint8_t index) { return _dests[index]; }
	~Matrix();
};

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
	Matrix *_matrix;
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
	Matrix *getMatrix() { return _matrix; }
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

class Map
{
private:
	vector<Box *> _boxes;
	vector<Scale *> _scales;
public:
	Map(string dirName);
	uint32_t getNumberOfBoxes() { return _boxes.size(); }
	Box *getBox(uint32_t index) { return _boxes[index]; }
	uint8_t getNumberOfScales() { return _scales.size(); }
	Scale *getScale(uint8_t index) { return _scales[index]; }
	~Map();
};

#endif

