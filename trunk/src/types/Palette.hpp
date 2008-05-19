#ifndef _PALETTE_HPP_
#define _PALETTE_HPP_

#include <stdint.h>
#include <vector>
#include <string>
using namespace std;

class XMLNode;

class Cycle
{
private:
	uint8_t _id;
	uint8_t _start;
	uint8_t _end;
	uint8_t _delay;
	bool _forward;
public:
	Cycle(XMLNode *node);
	uint8_t getID()  { return _id; }
	uint8_t getStart()  { return _start; }
	uint8_t getEnd() { return _end; }
	uint8_t getDelay()  { return _delay; }
	bool isForward() { return _forward; }
	~Cycle();
};

class Palette
{
private:
	static const uint8_t N_CHANNELS;

	vector<uint8_t> _colors;
	vector<Cycle *> _cycles;
	uint8_t _transparentIndex;
public:
	Palette(string dirName);
	uint32_t getNumberOfColors() { return _colors.size() / N_CHANNELS; }
	uint8_t getColor(uint32_t index, uint8_t channel) { return _colors[index * N_CHANNELS + channel]; }
	uint8_t getNumberOfCycles() { return _cycles.size(); }
	Cycle *getCycle(uint32_t index) { return _cycles.at(index); }
	uint8_t getTransparentIndex() { return _transparentIndex; }
	~Palette();
};

#endif

