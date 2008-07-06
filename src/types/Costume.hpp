#ifndef _COSTUME_HPP_
#define _COSTUME_HPP_

#include <stdint.h>
#include <string>
#include <vector>
using namespace std;

class XMLNode;

class Anim
{
private:
	static vector<Anim *> _instances;

	string _name;
	uint8_t _id;
	bool _loop;
	vector<uint8_t> _commands;
public:
	static Anim *getInstanceFromName(string animName);

	Anim(string fileName, uint8_t id);
	string getName() { return _name; }
	uint8_t getID() { return _id; }
	bool isLoop() { return _loop; }
	uint16_t getNumberOfCommands() { return _commands.size(); }
	uint8_t getCommand(uint16_t index) { return _commands[index]; }
	~Anim();
};

class Frame
{
private:
	uint16_t _width;
	uint16_t _height;
	int16_t _x;
	int16_t _y;
	int16_t _xInc;
	int16_t _yInc;
	vector<vector<uint8_t> > _pixels;
public:
	Frame(XMLNode *node, string fileName);
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
	bool _mirror;
	uint8_t _nColors;
	vector<uint8_t> _palette;
	vector<Anim *> _anims;
	vector<Frame *> _frames;
public:
	static Costume *getInstanceFromName(string costumeName);

	Costume(string dirName);
	string getName() { return _name; }
	uint16_t getID() { return _id; }
	bool isMirror() { return _mirror; }
	uint8_t getNumberOfColors() { return _nColors; }
	uint8_t getColor(uint8_t index) { return _palette[index]; }
	uint32_t getNumberOfAnims() { return _anims.size(); }
	Anim *getAnim(uint32_t index) { return _anims[index]; }
	uint8_t getNumberOfFrames() { return _frames.size(); }
	Frame *getFrame(uint8_t index) { return _frames[index]; }
	~Costume();
};

#endif

