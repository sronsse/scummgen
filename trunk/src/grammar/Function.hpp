#ifndef _FUNCTION_HPP_
#define _FUNCTION_HPP_

#include <map>
#include <stdint.h>
#include <string>
#include <vector>
using namespace std;

class BlockStatement;
class Declaration;
class Instruction;

typedef enum
{
	FUNCTION_NORMAL,
	FUNCTION_THREAD,
	FUNCTION_INLINED
} FunctionType;

class Function
{
private:
	FunctionType _type;
	string _name;
	uint16_t _id;
	vector<Declaration *> _arguments;
	BlockStatement *_blockStatement;
	vector<Instruction *> _instructions;
	map<string, uint16_t> _localSymbols;
	vector<uint8_t> _byteCode;

	void removeLabels();
	void displayAssembly();
public:
	Function(FunctionType type, string name, BlockStatement *blockS);
	void compile();
	FunctionType getType() { return _type; }
	string getName() { return _name; }
	uint16_t getID() { return _id; }
	void setID(uint16_t id) { _id = id; }
	void addArgument(Declaration *d) { _arguments.push_back(d); }
	uint8_t getNumberOfArguments() { return _arguments.size(); }
	Declaration *getArgument(uint8_t index) { return _arguments[index]; }
	BlockStatement *getBlockStatement() { return _blockStatement; }
	uint32_t getNumberOfInstructions() { return _instructions.size(); }
	Instruction *getInstruction(uint32_t index) { return _instructions[index]; }
	uint32_t getNumberOfBytes() { return _byteCode.size(); }
	uint8_t getByte(uint32_t index) { return _byteCode[index]; }
	~Function();
};

#endif
