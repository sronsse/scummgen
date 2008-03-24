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
	static const uint8_t MODE_SINGLE_FRAME;
	static const uint8_t MODE_STOP_LIMB;
	static const uint8_t MODE_START_LIMB;

	uint8_t _mode;
	uint16_t _start;
	uint16_t _length;
public:
	Limb(XMLNode *node);
	uint8_t getMode() { return _mode; }
	uint16_t getStart() { return _start; }
	uint16_t getLength() { return _length; }
	~Limb();
};

class Anim
{
private:
	uint16_t _mask;
	vector<Limb *> _limbs;
public:
	Anim(XMLNode *node);
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
	uint8_t **_pixels;
public:
	Frame(string fileName);
	uint16_t getWidth() { return _width; }
	uint16_t getHeight() { return _height; }
	uint8_t getPixel(uint16_t x, uint16_t y) { return _pixels[x][y]; }
	~Frame();
};

class Costume
{
private:
	static const uint8_t N_DIRECTIONS;
	static const uint8_t N_CHANNELS;
	static const uint8_t BOMP_CODEC;

	uint16_t _id;
	vector<Anim *> _anims;
	vector<Frame *> _frames;
	vector<uint8_t> _palette;
	vector<uint8_t> _commands;	
	bool _mirror;
public:
	Costume(string dirName);
	uint16_t getID() { return _id; }
	uint8_t isMirror() { return _mirror; }
	uint8_t getNumberOfDirections() { return N_DIRECTIONS; }
	uint8_t getNumberOfAnims() { return _anims.size(); }
	Anim *getAnim(uint32_t index) { return _anims.at(index); }
	uint32_t getNumberOfFrames() { return _frames.size(); }
	Frame *getFrame(uint32_t index) { return _frames[index]; }
	uint8_t getCodec() { return BOMP_CODEC; }
	uint32_t getNumberOfColors() { return _palette.size() / N_CHANNELS; }
	uint8_t getColor(uint32_t index, uint8_t channel) { return _palette[index * N_CHANNELS + channel]; }
	uint32_t getNumberOfCommands() { return _commands.size(); }
	uint8_t getCommand(uint32_t index) { return _commands[index]; }
	~Costume();
};

#endif

