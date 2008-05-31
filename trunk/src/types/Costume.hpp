#ifndef _COSTUME_HPP_
#define _COSTUME_HPP_

#include <stdint.h>
#include <string>
#include <vector>
using namespace std;

class XMLNode;

class Limb
{
private:
	uint8_t _id;
	uint16_t _start;
	uint8_t _length;
	bool _loop;
public:
	Limb(XMLNode *node);
	uint8_t getID() { return _id; }
	uint16_t getStart() { return _start; }
	uint8_t getLength() { return _length; }
	bool isLoop() { return _loop; }
	~Limb();
};

class Anim
{
private:
	uint8_t _id;
	uint16_t _mask;
	vector<Limb *> _limbs;
public:
	Anim(XMLNode *node);
	uint8_t getID() { return _id; }
	uint16_t getMask() { return _mask; }
	uint8_t getNumberOfLimbs() { return _limbs.size(); }
	Limb *getLimb(uint8_t index) { return _limbs.at(index); }
	~Anim();
};

class Frame
{
private:
	uint32_t _id;
	uint16_t _width;
	uint16_t _height;
	int16_t _x;
	int16_t _y;
	int16_t _xInc;
	int16_t _yInc;
	vector<vector<uint8_t> > _pixels;
public:
	Frame(XMLNode *node, string fileName);
	uint32_t getID() { return _id; }
	uint16_t getWidth() { return _width; }
	uint16_t getHeight() { return _height; }
	int16_t getX() { return _x; }
	int16_t getY() { return _y; }
	int16_t getXInc() { return _xInc; }
	int16_t getYInc() { return _yInc; }
	uint8_t getPixel(uint16_t x, uint16_t y) { return _pixels[x][y]; }
	~Frame();
};

class Costume
{
private:
	static const int N_LIMBS;
	static vector<Costume *> _instances;

	string _name;
	uint16_t _id;
	uint8_t _nAnims;
	bool _mirror;
	uint8_t _nColors;
	vector<uint8_t> _palette;
	vector<uint8_t> _table;
	vector<Anim *> _anims;
	vector<uint8_t> _commands;
	vector<Frame *> _frames;
public:
	static Costume *getInstanceFromName(string costumeName);

	Costume(string dirName);
	string getName() { return _name; }
	uint16_t getID() { return _id; }
	uint8_t getNumberOfAnims() { return _nAnims; }
	bool isMirror() { return _mirror; }
	uint8_t getNumberOfColors() { return _nColors; }
	uint8_t getColor(uint8_t index) { return _palette[index]; }
	uint8_t getTableIndex(uint8_t index) { return _table[index]; }
	uint32_t getNumberOfAnimEntries() { return _anims.size(); }
	Anim *getAnim(uint32_t index) { return _anims.at(index); }
	uint32_t getNumberOfCommands() { return _commands.size(); }
	uint8_t getCommand(uint32_t index) { return _commands.at(index); }
	uint32_t getNumberOfFrames() { return _frames.size(); }
	Frame *getFrame(uint32_t index) { return _frames.at(index); }
	~Costume();
};

#endif

