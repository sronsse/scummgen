#ifndef _SCRIPT_HPP_
#define _SCRIPT_HPP_

#include <stdint.h>
#include <string>
#include <vector>
using namespace std;

class Script
{
	static const uint8_t MIN_LOCAL_INDEX;
	static const uint8_t OC_PUSH_BYTE;
	static const uint8_t OC_PUSH_WORD;
	static vector<Script *> _globalScriptsInstances;
	static vector<Script *> _localScriptsInstances;

	string _name;
	uint32_t _id;
	vector<uint8_t> _bytes;

	void asm_pushByte(uint8_t byte);
	void asm_pushWord(int16_t word);
public:
	enum ScriptType {TYPE_GLOBAL, TYPE_LOCAL, TYPE_OTHER};

	static const string EXTENSION;

	static Script *getInstanceFromName(string scriptName);

	Script(string fileName, ScriptType type);
	string getName() { return _name; }
	uint32_t getID() { return _id; }
	uint32_t getNumberOfBytes() { return _bytes.size(); }
	uint32_t getByte(uint32_t index) { return _bytes[index]; }
	~Script();
};

#endif

