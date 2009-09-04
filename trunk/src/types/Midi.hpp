#ifndef _MIDI_HPP_
#define _MIDI_HPP_

#include <stdint.h>
#include <string>
using namespace std;

class Midi
{
private:
	static const string XML_FILE_NAME;

	uint16_t _id;
	string _name;
	string _midiPath;
public:
	Midi();
	void load(string dirPath);
	void save(string dirPath);
	uint16_t getID() { return _id; }
	void setID(uint16_t id) { _id = id; }
	string getName() { return _name; }
	string getMidiPath() { return _midiPath; }
	~Midi();
};

#endif
