#ifndef _CONTEXT_HPP_
#define _CONTEXT_HPP_

#include <map>
#include <stdint.h>
#include <string>
#include <vector>
#include "Function.hpp"
using namespace std;

class Declaration;
class Function;

typedef enum
{
	CONTEXT_GAME,
	CONTEXT_ROOM,
	CONTEXT_FUNCTION,
	CONTEXT_THREAD,
	CONTEXT_INLINED,
	CONTEXT_BLOCK,
	CONTEXT_SWITCH,
	CONTEXT_VERB,
	CONTEXT_FOR,
	CONTEXT_WHILE
} ContextType;

typedef enum
{
	SYMBOL_CONSTANT,
	SYMBOL_VARIABLE,
	SYMBOL_FUNCTION
} SymbolType;

class Context
{
private:
	static vector<Context *> _instances;
	static uint32_t _currentActor;
	static uint32_t _currentVerb;

	ContextType _type;
	vector<Declaration *> *_declarations;
	vector<Function *> *_functions;
	int32_t _continueLabel;
	int32_t _breakLabel;
	int32_t _returnLabel;
	map<string, uint32_t> _constantSymbols;
	map<string, uint32_t> _variableSymbols;
	map<string, uint32_t> _functionSymbols;

	static bool symbolExists(string name);
	static bool isAddressUsed(uint32_t address);

	void setConstantSymbols();
	void setVariableSymbols(bool fixedAddresses);
	void setFunctionSymbols();
	void displaySymbols();
public:
	static const uint16_t LOCAL_VARIABLE_MASK;

	static uint32_t labelCounter;
	static uint32_t currentAddress;

	static void pushContext(Context *context);
	static void popContext();
	static bool resolveSymbol(string symbol, uint32_t &value, SymbolType &type);
	static Function* getFunction(string functionName);
	static int32_t getContinueLabel();
	static int32_t getBreakLabel();
	static int32_t getReturnLabel();
	static FunctionType getFunctionType();

	Context(ContextType type, vector<Declaration *> *declarations, vector<Function *> *functions, int32_t continueLabel, int32_t breakLabel, int32_t returnLabel);
	~Context();
};

#endif

