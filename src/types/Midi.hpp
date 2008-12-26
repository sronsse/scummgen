#ifndef _MIDI_HPP_
#define _MIDI_HPP_

#include <stdint.h>
#include <string>
#include <vector>
using namespace std;

class Midi
{
private:
	string _name;
	uint16_t _id;
	vector<uint8_t> _dataBytes;
public:
	Midi(string fileName);
	string getName() { return _name; }
	uint16_t getID() { return _id; }
	uint32_t getNumberOfDataBytes() { return _dataBytes.size(); }
	uint8_t getDataByte(uint32_t index) { return _dataBytes[index]; }
	~Midi();
};

#endif
