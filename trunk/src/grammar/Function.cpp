#include "Function.hpp"
#include <sstream>
#include "util/Log.hpp"
#include "Context.hpp"
#include "Declaration.hpp"
#include "Instruction.hpp"
#include "Statement.hpp"

Function::Function(string name, bool thread, BlockStatement *blockS)
{
	_name = name;
	_thread = thread;
	_blockStatement = blockS;
	_id = 0; // This member is filled later
}

void Function::removeLabels()
{
	// First, we get the label instruction addresses and remove the corresponding instructions
	map<uint32_t, uint32_t> labelAddresses;
	vector<Instruction *>::iterator iterator = _instructions.begin();
	while (iterator != _instructions.end())
		if ((*iterator)->getType() == INSTRUCTION_LABEL)
		{
			labelAddresses[(*iterator)->getLabel()] = (*iterator)->getAddress();
			delete (*iterator);
			iterator = _instructions.erase(iterator);
		}
		else
			iterator++;

	// Then, we replace labels by relative offsets
	for (int i = 0; i < _instructions.size(); i++)
		if (_instructions[i]->getType() == INSTRUCTION_VALUE && _instructions[i]->getValue().substr(0, 6) == "LABEL_")
		{
			uint32_t label;
			istringstream iss(_instructions[i]->getValue().substr(6, 1));
			iss >> label;
			// The magic 2 in this statement is because SCUMM jump/if/ifNot instructions
			// don't take the offset following them into account
			int32_t offset = (int32_t)labelAddresses[label] - (int32_t)_instructions[i]->getAddress() - 2;
			ostringstream oss;
			oss << offset;
			_instructions[i]->setValue(oss.str());
		}
}

void Function::displayAssembly()
{
	Log::getInstance().write(LOG_INFO, "Function \"%s\" (id n°%u) assembly:\n", _name.c_str(), _id);
	Log::getInstance().indent();
	for (int i = 0; i < _instructions.size(); i++)
		Log::getInstance().write(LOG_INFO, "%s\n", _instructions[i]->toString().c_str());
	Log::getInstance().unIndent();
}

void Function::compile()
{
	Log::getInstance().write(LOG_INFO, "Compiling function \"%s\"...\n", _name.c_str());
	Log::getInstance().indent();

	// We add an invisible argument which eventually tells if the 
	// function has been called directly by ScummVM or via the code
	vector<Declaration *> arguments;
	Declaration invisibleArgument(DECLARATION_VAR, "__caller");
	for (int i = 0; i < _arguments.size(); i++)
		arguments.push_back(_arguments[i]);
	arguments.push_back(&invisibleArgument);

	// Push the function context specifying LABEL_0 as the return label
	Context context(_thread ? CONTEXT_THREAD : CONTEXT_FUNCTION, &arguments, NULL, -1, -1, 0);
	Context::pushContext(&context);

	// Prepare labels first
	Context::labelCounter += _thread ? 1 : 2;

	// Compile block statement
	_blockStatement->compile(_instructions);

	// label 0
	_instructions.push_back(new Instruction(0));

	if (!_thread)
	{
		// Push 0 as a return value in case the current function has been called from within the code
		// and not by ScummVM directly
		uint16_t value;
		SymbolType symbolType;
		ostringstream oss;
		Context::resolveSymbol("__caller", value, symbolType);
		oss << value;
		_instructions.push_back(new Instruction("pushWordVar"));
		_instructions.push_back(new Instruction(VALUE_WORD, oss.str()));
		_instructions.push_back(new Instruction("ifNot"));
		_instructions.push_back(new Instruction(VALUE_WORD, "LABEL_1"));
		_instructions.push_back(new Instruction("pushByte"));
		_instructions.push_back(new Instruction(VALUE_BYTE, "0"));

		// label 1
		_instructions.push_back(new Instruction(1));
	}

	// stopObjectCode instruction
	if (!_instructions.empty() && _instructions.back()->getOpcodeName() != "stopObjectCode")
		_instructions.push_back(new Instruction("stopObjectCode"));

	Context::popContext();

	displayAssembly();

	// Replace labels by relative offsets
	removeLabels();

	// Assemble instructions
	for (int i = 0; i < _instructions.size(); i++)
		_instructions[i]->assemble(_byteCode);

	Log::getInstance().unIndent();
}

Function::~Function()
{
	for (int i = 0; i < _arguments.size(); i++)
		delete _arguments[i];
	delete _blockStatement;
	for (int i = 0; i < _instructions.size(); i++)
		delete _instructions[i];
}

