#ifndef _CYCLE_HPP_
#define _CYCLE_HPP_

#include <string>
using namespace std;

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

#endif
