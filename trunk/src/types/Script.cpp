#include "Script.hpp"
#include <fstream>
#include "util/Log.hpp"

const uint8_t Script::MIN_LOCAL_INDEX = 200;

// opcodes
const uint8_t Script::OC_PUSH_BYTE = 0x00;
const uint8_t Script::OC_PUSH_WORD = 0x01;

vector<Script *> Script::_globalScriptsInstances;
vector<Script *> Script::_localScriptsInstances;

const string Script::EXTENSION = ".sgc";

Script *Script::getInstanceFromName(string scriptName)
{
	for (int i = 0; i < _globalScriptsInstances.size(); i++)
		if (_globalScriptsInstances[i]->getName() == scriptName)
			return _globalScriptsInstances[i];
	for (int i = 0; i < _localScriptsInstances.size(); i++)
		if (_localScriptsInstances[i]->getName() == scriptName)
			return _localScriptsInstances[i];
	return NULL;
}

Script::Script(string fileName, ScriptType type)
{
	Log::getInstance().write("Script\n");
	Log::getInstance().indent();

	int posB = fileName.find_last_of('.') - 1;
	int posA = fileName.find_last_of('/') + 1;
	_name = fileName.substr(posA, posB + 1 - posA);
	Log::getInstance().write("name: %s\n", _name.c_str());

	switch (type)
	{
		case TYPE_GLOBAL:
			Log::getInstance().write("type: global\n");
			_globalScriptsInstances.push_back(this);
			_id = _globalScriptsInstances.size();
			Log::getInstance().write("id: %u\n", _id);
			break;
		case TYPE_LOCAL:
			Log::getInstance().write("type: local\n");
			_localScriptsInstances.push_back(this);
			_id = _localScriptsInstances.size() - 1 + MIN_LOCAL_INDEX;
			Log::getInstance().write("id: %u\n", _id);
			if (_id == 200)
			{
				asm_pushByte(50);
				asm_pushWord(1500);
			}
			break;
		case TYPE_OTHER:
		default:
			_id = 0; // unused
			Log::getInstance().write("type: other\n");
	}

	Log::getInstance().unIndent();
}

void Script::asm_pushByte(uint8_t byte)
{
	_bytes.push_back(OC_PUSH_BYTE);
	_bytes.push_back(byte);
}

void Script::asm_pushWord(int16_t word)
{
	_bytes.push_back(OC_PUSH_WORD);
	_bytes.push_back(word);
	_bytes.push_back(word >> 8);
}

Script::~Script()
{
}

