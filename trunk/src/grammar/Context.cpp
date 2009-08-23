#include "Context.hpp"
#include "util/Log.hpp"
#include "types/Game.hpp"
#include "Declaration.hpp"

vector<Context *> Context::_instances;

const uint16_t Context::LOCAL_VARIABLE_MASK = 0x4000;

uint32_t Context::labelCounter;
uint32_t Context::currentAddress;

void Context::pushContext(Context *context)
{
	_instances.push_back(context);

	string contextType;
	switch (context->_type)
	{
		case CONTEXT_GAME:
			contextType = "game";
			break;
		case CONTEXT_ROOM:
			contextType = "room";
			break;
		case CONTEXT_FUNCTION:
			contextType = "function";
			break;
		case CONTEXT_THREAD:
			contextType = "thread";
			break;
		case CONTEXT_INLINED:
			contextType = "inlined";
			break;
		case CONTEXT_BLOCK:
			contextType = "block";
			break;
		case CONTEXT_SWITCH:
			contextType = "switch";
			break;
		case CONTEXT_VERB:
			contextType = "switch";
			break;
		case CONTEXT_FOR:
			contextType = "for";
			break;
		case CONTEXT_WHILE:
			contextType = "while";
	}
	Log::write(LOG_INFO, "Pushing context (%s)...\n", contextType.c_str());
	Log::indent();

	// Compute the different kinds of symbols
	Log::write(LOG_INFO, "Computing symbols...\n");
	Log::indent();
	context->setConstantSymbols();
	context->setVariableSymbols(true);
	context->setVariableSymbols(false);
	context->setFunctionSymbols();
	context->displaySymbols();
	Log::unIndent();

	// When we enter functions, we have to reset the label counter and the current instruction address
	if (context->_type == CONTEXT_FUNCTION)
	{
		labelCounter = 0;
		currentAddress = 0;
	}
}

void Context::popContext()
{
	_instances.pop_back();
	Log::unIndent();
}

bool Context::resolveSymbol(string symbol, uint32_t &value, SymbolType &type)
{
	bool reachedInlinedContext = false;

	for (int i = _instances.size() - 1; i >= 0; i--)
		if (!reachedInlinedContext || _instances[i]->_type == CONTEXT_GAME || _instances[i]->_type == CONTEXT_ROOM)
		{
			// Check all the different symbol types
			if (_instances[i]->_constantSymbols.find(symbol) != _instances[i]->_constantSymbols.end())
			{
				value = _instances[i]->_constantSymbols[symbol];
				type = SYMBOL_CONSTANT;
				return true;
			}
			if (_instances[i]->_variableSymbols.find(symbol) != _instances[i]->_variableSymbols.end())
			{
				value = _instances[i]->_variableSymbols[symbol];
				type = SYMBOL_VARIABLE;
				return true;
			}
			if (_instances[i]->_functionSymbols.find(symbol) != _instances[i]->_functionSymbols.end())
			{
				value = _instances[i]->_functionSymbols[symbol];
				type = SYMBOL_FUNCTION;
				return true;
			}

			// When reaching an inlined function context here,
			// it means that if the symbol can be resolved, it
			// has to be global (room or game context).
			if (_instances[i]->_type == CONTEXT_INLINED)
				reachedInlinedContext = true;
		}
	return false;
}

Function* Context::getFunction(string functionName)
{
	for (int i = _instances.size() - 1; i >= 0; i--)
	{
		if (_instances[i]->_functions == NULL)
			continue;

		for (int j = 0; j < _instances[i]->_functions->size(); j++)
			if ((*_instances[i]->_functions)[j]->getName() == functionName)
				return (*_instances[i]->_functions)[j];
	}
	return NULL;
}

int32_t Context::getContinueLabel()
{
	for (int i = _instances.size() - 1; i >= 0; i--)
		if (_instances[i]->_continueLabel != -1)
			return _instances[i]->_continueLabel;
	return -1;
}

int32_t Context::getBreakLabel()
{
	for (int i = _instances.size() - 1; i >= 0; i--)
		if (_instances[i]->_breakLabel != -1)
			return _instances[i]->_breakLabel;
	return -1;
}

int32_t Context::getReturnLabel()
{
	for (int i = _instances.size() - 1; i >= 0; i--)
		if (_instances[i]->_returnLabel != -1)
			return _instances[i]->_returnLabel;
	return -1;
}

FunctionType Context::getFunctionType()
{
	for (int i = _instances.size() - 1; i >= 0; i--)
		switch (_instances[i]->_type)
		{
			case CONTEXT_FUNCTION:
				return FUNCTION_NORMAL;
			case CONTEXT_THREAD:
				return FUNCTION_THREAD;
			case CONTEXT_INLINED:
				return FUNCTION_INLINED;
			default:
				break;
		}
	return FUNCTION_NORMAL;
}

bool Context::symbolExists(string name)
{
	bool reachedInlinedContext = false;

	for (int i = _instances.size() - 1; i >= 0; i--)
	if (!reachedInlinedContext || _instances[i]->_type == CONTEXT_GAME || _instances[i]->_type == CONTEXT_ROOM)
		{
			if (_instances[i]->_constantSymbols.find(name) != _instances[i]->_constantSymbols.end())
				return true;
			if (_instances[i]->_variableSymbols.find(name) != _instances[i]->_variableSymbols.end())
				return true;
			if (_instances[i]->_functionSymbols.find(name) != _instances[i]->_functionSymbols.end())
				return true;

			// When reaching an inlined function context here,
			// it means that if the symbol exists, it has to
			// be global (room or game context).
			if (_instances[i]->_type == CONTEXT_INLINED)
				reachedInlinedContext = true;
		}
	return false;
}

bool Context::isAddressUsed(uint32_t address)
{
	map<string, uint32_t>::const_iterator iterator;
	for (int i = _instances.size() - 1; i >= 0; i--)
		for (iterator = _instances[i]->_variableSymbols.begin(); iterator != _instances[i]->_variableSymbols.end(); iterator++)
			if (iterator->second == address)
				return true;
	return false;
}

Context::Context(ContextType type, vector<Declaration *> *declarations, vector<Function *> *functions, int32_t continueLabel, int32_t breakLabel, int32_t returnLabel)
{
	_type = type;
	_declarations = declarations;
	_functions = functions;
	_continueLabel = continueLabel;
	_breakLabel = breakLabel;
	_returnLabel = returnLabel;
}

void Context::setConstantSymbols()
{
	if (_declarations == NULL)
		return;

	for (int i = 0; i < _declarations->size(); i++)
		if ((*_declarations)[i]->getType() == DECLARATION_CONST)
		{
			string name = (*_declarations)[i]->getName();
			if (symbolExists(name))
				Log::write(LOG_ERROR, "Symbol \"%s\" already declared !\n", name.c_str());
			_constantSymbols[name] = (*_declarations)[i]->getValue();
		}
}

void Context::setVariableSymbols(bool fixedAddresses)
{
	// No need to look for variables with fixed addresses when the context type is not global
	if (_declarations == NULL || ((_type != CONTEXT_GAME) && fixedAddresses))
		return;

	for (int i = 0; i < _declarations->size(); i++)
		if ((*_declarations)[i]->getType() == DECLARATION_VAR)
		{
			if ((*_declarations)[i]->hasFixedAddress() != fixedAddresses)
			{
				if (_type != CONTEXT_GAME)
					Log::write(LOG_ERROR, "Cannot specify the address of local variable !\n");
				continue;
			}

			string name = (*_declarations)[i]->getName();
			uint32_t address;

			// Check if symbol doesn't exist already
			if (symbolExists(name))
				Log::write(LOG_ERROR, "Symbol \"%s\" already declared !\n", name.c_str());

			// Check if address is not already taken in case it's a fixed address
			map<string, uint32_t>::const_iterator iterator = _variableSymbols.begin();
			if (fixedAddresses)
			{
				address = (*_declarations)[i]->getValue();
				if (isAddressUsed(address))
					Log::write(LOG_ERROR, "Symbol \"%s\" can't be mapped as this address is already used !\n", name.c_str());
			}
			// Search through the map to get the smallest available address
			else
			{
				address = (_type == CONTEXT_GAME) ? 0 : LOCAL_VARIABLE_MASK;
				while (isAddressUsed(address))
					address++;
			}

			// Check wether the address fits in the autorized range
			// (and make sure we reserve the last local variable for temporary arrays)
			if ((_type == CONTEXT_GAME && address >= Game::MAX_WORD_VARIABLES)
			|| (_type != CONTEXT_GAME && (address < LOCAL_VARIABLE_MASK || address >= ((Game::MAX_LOCAL_VARIABLES - 1) | LOCAL_VARIABLE_MASK))))
				Log::write(LOG_ERROR, "Symbol \"%s\" can't be mapped as this address is invalid !\n", name.c_str());
			_variableSymbols[name] = address;
		}
}

void Context::setFunctionSymbols()
{
	if (_functions == NULL)
		return;

	for (int i = 0; i < _functions->size(); i++)
	{
		string name = (*_functions)[i]->getName();
		if (symbolExists(name))
			Log::write(LOG_ERROR, "Function \"%s\" already declared !\n", name.c_str());
		_functionSymbols[name] = (*_functions)[i]->getID();
	}
}

void Context::displaySymbols()
{
	map<string, uint32_t>::const_iterator iterator;
	for (iterator = _constantSymbols.begin(); iterator != _constantSymbols.end(); iterator++)
		Log::write(LOG_INFO, "%s - 0x%08x\n", iterator->first.c_str(), iterator->second);

	for (iterator = _variableSymbols.begin(); iterator != _variableSymbols.end(); iterator++)
		Log::write(LOG_INFO, "%s - 0x%08x\n", iterator->first.c_str(), iterator->second);

	for (iterator = _functionSymbols.begin(); iterator != _functionSymbols.end(); iterator++)
		Log::write(LOG_INFO, "%s - 0x%08x\n", iterator->first.c_str(), iterator->second);
}

Context::~Context()
{
}
