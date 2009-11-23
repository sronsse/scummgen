#ifndef _IMAGE_HPP_
#define _IMAGE_HPP_

#include <string>
#include <vector>
using namespace std;

class Palette;
class XMLNode;

class Cycle
{
private:
	uint8_t _id;
	string _name;
	uint8_t _start;
	uint8_t _end;
	uint8_t _delay;
	bool _forward;
public:
	Cycle();
	void load(XMLNode *node);
	void save(XMLNode *node);
	uint8_t getID() { return _id; }
	void setID(uint8_t id) { _id = id; }
	string getName() { return _name; }
	void setName(string name) { _name = name; }
	uint8_t getStart()  { return _start; }
	void setStart(uint8_t start) { _start = start; }
	uint8_t getEnd() { return _end; }
	void setEnd(uint8_t end) { _end = end; }
	uint8_t getDelay()  { return _delay; }
	void setDelay(uint8_t delay) { _delay = delay; }
	bool isForward() { return _forward; }
	void setForward(bool forward)  { _forward = forward; }
	~Cycle();
};

class Image
{
private:
	static const string XML_FILE_NAME;

	string _name;
	bool _transparent;
	string _bitmapPath;
	vector<string> _zPlanePaths;
	uint32_t _width;
	uint32_t _height;
	vector<vector<uint8_t> > _pixels;
	vector<Cycle *> _cycles;
public:
	Image();
	void load(string dirPath);
	void save(string dirPath);
	void fillPalette(Palette *palette, bool global);
	string getName() { return _name; }
	bool isTransparent() { return _transparent; }
	uint16_t getNumberOfZPlanePaths() { return _zPlanePaths.size(); }
	string getZPlanePath(uint16_t index) { return _zPlanePaths[index]; }
	uint32_t getWidth() { return _width; }
	uint32_t getHeight() { return _height; }
	uint32_t getPixel(uint32_t x, uint32_t y) { return _pixels[x][y]; }
	~Image();
};

#endif
