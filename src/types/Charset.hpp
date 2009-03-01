#ifndef _CHARSET_HPP_
#define _CHARSET_HPP_

#include <stdint.h>
#include <string>
#include <vector>
using namespace std;

class XMLNode;

class Char
{
private:
	uint16_t _id;
	uint16_t _x;
	uint16_t _y;
	uint8_t _width;
	uint8_t _height;
	int8_t _xOffset;
	int8_t _yOffset;
public:
	Char();
	void load(XMLNode *node);
	uint16_t getID() { return _id; }
	uint16_t getX() { return _x; }
	uint16_t getY() { return _y; }
	uint8_t getWidth() { return _width; }
	uint8_t getHeight() { return _height; }
	int8_t getXOffset() { return _xOffset; }
	int8_t getYOffset() { return _yOffset; }
};

class Charset
{
private:
	uint16_t _id;
	string _name;
	string _bitmapPath;
	uint8_t _fontHeight;
	vector<Char *>_chars;
public:
	Charset();
	void load(string dirPath);
	uint16_t getID() { return _id; }
	string getName() { return _name; }
	string getBitmapPath() { return _bitmapPath; }
	uint8_t getFontHeight() { return _fontHeight; }
	uint16_t getNumberOfChars() { return _chars.size(); }
	Char *getChar(uint16_t index) { return _chars[index]; }
	~Charset();
};

#endif
