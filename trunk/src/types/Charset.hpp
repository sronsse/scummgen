#ifndef _CHARSET_HPP_
#define _CHARSET_HPP_

#include <map>
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
	Char(XMLNode *node);
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
	static const uint8_t N_COLORS;
	static map<string, Charset *> _instances;

	string _name;
	uint32_t _width;
	uint32_t _height;
	vector<vector<uint8_t> > _pixels;
	uint16_t _id;
	vector<uint8_t> _palette;
	uint8_t _bpp;
	uint8_t _fontHeight;
	vector<Char *>_chars;
public:
	static Charset *getInstanceFromName(string charsetName);

	Charset(string dirName);
	string getName() { return _name; }
	uint32_t getWidth() { return _width; }
	uint32_t getHeight() { return _height; }
	uint8_t getPixel(uint32_t i, uint32_t j) { return _pixels[i][j]; }
	uint16_t getID() { return _id; }
	uint8_t getNumberOfPaletteIndices() { return _palette.size(); }
	uint8_t getPaletteIndex(uint8_t index) { return _palette[index]; }
	uint8_t getBPP() { return _bpp; }
	uint8_t getFontHeight() { return _fontHeight; }
	uint16_t getNumberOfChars() { return _chars.size(); }
	Char *getChar(uint16_t index) { return _chars[index]; }
	~Charset();
};

#endif

