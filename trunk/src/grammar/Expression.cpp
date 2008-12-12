#include "Expression.hpp"
#include <sstream>
#include "util/Log.hpp"
#include "types/Game.hpp"
#include "Context.hpp"
#include "Function.hpp"
#include "Instruction.hpp"

Expression *Expression::simplifyUnaryExpression(ExpressionType type, Expression *e)
{
	if (e->getType() != EXPRESSION_CONSTANT)
		return new UnaryExpression(type, e);

	ConstantExpression *result;
	switch (type)
	{
		case EXPRESSION_UMINUS:
			result = new ConstantExpression(-((ConstantExpression *)e)->getNumber());
			break;
		case EXPRESSION_NOT:
			result = new ConstantExpression(!((ConstantExpression *)e)->getNumber());
			break;
		default:
			result = NULL;
	}

	delete e;
	return result;
}

Expression *Expression::simplifyBinaryExpression(ExpressionType type, Expression *e1, Expression *e2)
{
	if (e1->getType() != EXPRESSION_CONSTANT || e2->getType() != EXPRESSION_CONSTANT)
		return new BinaryExpression(type, e1, e2);

	ConstantExpression *result;
	switch (type)
	{
		case EXPRESSION_ADD:
			result = new ConstantExpression(((ConstantExpression *)e1)->getNumber() + ((ConstantExpression *)e2)->getNumber());
			break;
		case EXPRESSION_SUB:
			result = new ConstantExpression(((ConstantExpression *)e1)->getNumber() - ((ConstantExpression *)e2)->getNumber());
			break;
		case EXPRESSION_DIV:
			if (((ConstantExpression *)e2)->getNumber() == 0)
				Log::getInstance().write(LOG_ERROR, "Found a division by zero !\n");
			result = new ConstantExpression(((ConstantExpression *)e1)->getNumber() / ((ConstantExpression *)e2)->getNumber());
			break;
		case EXPRESSION_MUL:
			result = new ConstantExpression(((ConstantExpression *)e1)->getNumber() * ((ConstantExpression *)e2)->getNumber());
			break;
		case EXPRESSION_LT:
			result = new ConstantExpression(((ConstantExpression *)e1)->getNumber() < ((ConstantExpression *)e2)->getNumber());
			break;
		case EXPRESSION_GT:
			result = new ConstantExpression(((ConstantExpression *)e1)->getNumber() > ((ConstantExpression *)e2)->getNumber());
			break;
		case EXPRESSION_BAND:
			result = new ConstantExpression(((ConstantExpression *)e1)->getNumber() & ((ConstantExpression *)e2)->getNumber());
			break;
		case EXPRESSION_BOR:
			result = new ConstantExpression(((ConstantExpression *)e1)->getNumber() | ((ConstantExpression *)e2)->getNumber());
			break;
		case EXPRESSION_LE:
			result = new ConstantExpression(((ConstantExpression *)e1)->getNumber() <= ((ConstantExpression *)e2)->getNumber());
			break;
		case EXPRESSION_GE:
			result = new ConstantExpression(((ConstantExpression *)e1)->getNumber() >= ((ConstantExpression *)e2)->getNumber());
			break;
		case EXPRESSION_NE:
			result = new ConstantExpression(((ConstantExpression *)e1)->getNumber() != ((ConstantExpression *)e2)->getNumber());
			break;
		case EXPRESSION_EQ:
			result = new ConstantExpression(((ConstantExpression *)e1)->getNumber() == ((ConstantExpression *)e2)->getNumber());
			break;
		case EXPRESSION_LAND:
			result = new ConstantExpression(((ConstantExpression *)e1)->getNumber() && ((ConstantExpression *)e2)->getNumber());
			break;
		case EXPRESSION_LOR:
			result = new ConstantExpression(((ConstantExpression *)e1)->getNumber() || ((ConstantExpression *)e2)->getNumber());
			break;
		default:
			result = NULL;
	}

	delete e1;
	delete e2;
	return result;
}

VariableExpression::VariableExpression(string identifier):
Expression(EXPRESSION_VARIABLE)
{
	_identifier = identifier;
}

void VariableExpression::compile(vector<Instruction *> &instructions)
{
	uint16_t value;
	SymbolType symbolType;
	if (!Context::resolveSymbol(_identifier, value, symbolType))
		Log::getInstance().write(LOG_ERROR, "Could not resolve symbol \"%s\" !\n", _identifier.c_str());
	ostringstream oss;
	oss << value;
	if (symbolType == SYMBOL_VARIABLE)
		instructions.push_back(new Instruction("pushWordVar"));
	else
		instructions.push_back(new Instruction("pushWord"));
	instructions.push_back(new Instruction(VALUE_WORD, oss.str()));
}

VariableExpression::~VariableExpression()
{
}

ConstantExpression::ConstantExpression(int32_t number):
Expression(EXPRESSION_CONSTANT)
{
	_number = number;
}

void ConstantExpression::compile(vector<Instruction *> &instructions)
{
	ostringstream oss;
	oss << _number;
	instructions.push_back(new Instruction("pushWord"));
	instructions.push_back(new Instruction(VALUE_WORD, oss.str()));
}

ConstantExpression::~ConstantExpression()
{
}

StringExpression::StringExpression(string s):
Expression(EXPRESSION_STRING)
{
	_string = s;
}

string StringExpression::convertString(string s)
{
	string convertedString;
	int pos = 0;

	while (pos < s.length())
	{
		switch (s[pos])
		{
			case '\\':
				convertedString += parseEscapeCharacter(s, ++pos);
				break;
			case '%':
				convertedString += parseSpecialCode(s, ++pos);
				break;
			default:
				convertedString += s[pos++];
		}
	}

	return convertedString;
}

char StringExpression::parseEscapeCharacter(string s, int &pos)
{
	char c;

	// Get escape character
	switch (s[pos++])
	{
		case '\\':
			c = '\\';
			break;
		case 'n':
			c = '\n';
			break;
		case 't':
			c = '\t';
			break;
		case '%':
			c = '%';
			break;
		default:
			Log::getInstance().write(LOG_ERROR, "Unknown escape character in string \"%s\" !\n", s.c_str());
	}

	return c;
}

string StringExpression::parseSpecialCode(string s, int &pos)
{
	string convertedString;

	// Special SCUMM string opcode
	convertedString += 0xFF;

	// Get special code
	switch (s[pos++])
	{
		case 'i':
			convertedString += 4;
			convertedString += parseSymbol(s, pos);
			break;
		case 'v':
			convertedString += 5;
			convertedString += parseSymbol(s, pos);
			break;
		/*case 'V':
			convertedString += parseSymbol(s, pos);*/
			break;
		default:
			Log::getInstance().write(LOG_ERROR, "Unknown special code in string \"%s\" !\n", s.c_str());
	}

	return convertedString;
}

string StringExpression::parseSymbol(string s, int &pos)
{
	string convertedString;

	if (s[pos++] != '{')
		Log::getInstance().write(LOG_ERROR, "Expected '{' while parsing special code in string \"%s\" !\n", s.c_str());

	// Get symbol
	string symbol;
	for (;;)
	{
		if (s[pos] == string::npos)
			Log::getInstance().write(LOG_ERROR, "Expected '}' while parsing special code in string \"%s\" !\n", s.c_str());

		if (s[pos] == '}')
		{
			pos++;
			break;
		}

		symbol += s[pos++];
	}

	// Resolve symbol
	istringstream iss(symbol);
	uint16_t value;
	if (!(iss >> value))
	{
		SymbolType symbolType;
		if (!Context::resolveSymbol(symbol, value, symbolType))
			Log::getInstance().write(LOG_ERROR, "Could not resolve symbol \"%s\" in string \"%s\" !\n", symbol.c_str(), s.c_str());
	}

	// Add the symbol to the string
	convertedString += (uint8_t)value;
	convertedString += (uint8_t)(value >> 8);

	return convertedString;
}

void StringExpression::compile(vector<Instruction *> &instructions)
{
	// We use the last local variable slot for a temporary array
	ostringstream oss;
	oss << ((Game::MAX_LOCAL_VARIABLES - 1) | Context::LOCAL_VARIABLE_MASK);

	// Push index
	instructions.push_back(new Instruction("pushWord"));
	instructions.push_back(new Instruction(VALUE_WORD, "0"));

	// Add arrayOps assignString instruction
	instructions.push_back(new Instruction("arrayOps"));
	instructions.push_back(new Instruction("assignString"));
	instructions.push_back(new Instruction(VALUE_WORD, oss.str()));

	// Convert string and add the corresponding instruction
	instructions.push_back(new Instruction(VALUE_STRING, convertString(_string), _string));

	// Push array
	instructions.push_back(new Instruction("pushWordVar"));
	instructions.push_back(new Instruction(VALUE_WORD, oss.str()));
}

StringExpression::~StringExpression()
{
}

UnaryExpression::UnaryExpression(ExpressionType type, Expression *e):
Expression(type)
{
	_e = e;
}

void UnaryExpression::compile(vector<Instruction *> &instructions)
{
	switch (_type)
	{
		case EXPRESSION_UMINUS:
			_e->compile(instructions);
			instructions.push_back(new Instruction("uminus"));
			return;
		case EXPRESSION_NOT:
			_e->compile(instructions);
			instructions.push_back(new Instruction("not"));
			return;
		default:
			break;
	}

	// If we're here, it means the expression has to be a variable
	string identifier = ((VariableExpression *)_e)->getIdentifier();
	uint16_t value;
	SymbolType symbolType;
	if (!Context::resolveSymbol(identifier, value, symbolType))
		Log::getInstance().write(LOG_ERROR, "Could not resolve symbol \"%s\" !\n", identifier.c_str());
	if (symbolType != SYMBOL_VARIABLE)
		Log::getInstance().write(LOG_ERROR, "Only variables can be incremented or decremented !\n");
	ostringstream oss;
	oss << value;

	switch (_type)
	{
		case EXPRESSION_UMINUS:
			_e->compile(instructions);
			instructions.push_back(new Instruction("uminus"));
			break;
		case EXPRESSION_NOT:
			_e->compile(instructions);
			instructions.push_back(new Instruction("not"));
			break;
		case EXPRESSION_PREINC:
			instructions.push_back(new Instruction("wordVarInc"));
			instructions.push_back(new Instruction(VALUE_WORD, oss.str()));
			_e->compile(instructions);
			break;
		case EXPRESSION_POSTINC:
			_e->compile(instructions);
			instructions.push_back(new Instruction("wordVarInc"));
			instructions.push_back(new Instruction(VALUE_WORD, oss.str()));
			break;
		case EXPRESSION_PREDEC:
			instructions.push_back(new Instruction("wordVarDec"));
			instructions.push_back(new Instruction(VALUE_WORD, oss.str()));
			_e->compile(instructions);
			break;
		case EXPRESSION_POSTDEC:
			_e->compile(instructions);
			instructions.push_back(new Instruction("wordVarDec"));
			instructions.push_back(new Instruction(VALUE_WORD, oss.str()));
			break;
		default:
			break;
	}
}

UnaryExpression::~UnaryExpression()
{
	delete _e;
}

BinaryExpression::BinaryExpression(ExpressionType type, Expression *e1, Expression *e2):
Expression(type)
{
	_e1 = e1;
	_e2 = e2;
}

void BinaryExpression::compile(vector<Instruction *> &instructions)
{
	_e1->compile(instructions);
	_e2->compile(instructions);

	switch (_type)
	{
		case EXPRESSION_ADD:
			instructions.push_back(new Instruction("add"));
			break;
		case EXPRESSION_SUB:
			instructions.push_back(new Instruction("sub"));
			break;
		case EXPRESSION_DIV:
			instructions.push_back(new Instruction("div"));
			break;
		case EXPRESSION_MUL:
			instructions.push_back(new Instruction("mul"));
			break;
		case EXPRESSION_LT:
			instructions.push_back(new Instruction("lt"));
			break;
		case EXPRESSION_GT:
			instructions.push_back(new Instruction("gt"));
			break;
		case EXPRESSION_BAND:
			instructions.push_back(new Instruction("band"));
			break;
		case EXPRESSION_BOR:
			instructions.push_back(new Instruction("bor"));
			break;
		case EXPRESSION_LE:
			instructions.push_back(new Instruction("le"));
			break;
		case EXPRESSION_GE:
			instructions.push_back(new Instruction("ge"));
			break;
		case EXPRESSION_NE:
			instructions.push_back(new Instruction("neq"));
			break;
		case EXPRESSION_EQ:
			instructions.push_back(new Instruction("eq"));
			break;
		case EXPRESSION_LAND:
			instructions.push_back(new Instruction("land"));
			break;
		case EXPRESSION_LOR:
			instructions.push_back(new Instruction("lor"));
			break;
		default:
			break;
	}
}

BinaryExpression::~BinaryExpression()
{
	delete _e1;
	delete _e2;
}

AssignmentExpression::AssignmentExpression(VariableExpression *v, Expression *e):
Expression(EXPRESSION_ASSIGNMENT)
{
	_variable = v;
	_expression = e;
}

void AssignmentExpression::compile(vector<Instruction *> &instructions)
{
	string identifier = _variable->getIdentifier();

	uint16_t address;
	SymbolType symbolType;
	if (!Context::resolveSymbol(identifier, address, symbolType))
		Log::getInstance().write(LOG_ERROR, "Could not resolve symbol \"%s\" !\n", identifier.c_str());

	if (symbolType != SYMBOL_VARIABLE)
		Log::getInstance().write(LOG_ERROR, "Assignements only apply to variables !\n");

	_expression->compile(instructions);

	// Write variable
	ostringstream oss;
	oss << address;
	instructions.push_back(new Instruction("writeWordVar"));
	instructions.push_back(new Instruction(VALUE_WORD, oss.str()));

	// Push the variable we just wrote on the stack
	instructions.push_back(new Instruction("pushWordVar"));
	instructions.push_back(new Instruction(VALUE_WORD, oss.str()));
}

AssignmentExpression::~AssignmentExpression()
{
	delete _variable;
	delete _expression;
}

CallExpression::CallExpression(string functionName):
Expression(EXPRESSION_CALL)
{
	_functionName = functionName;
}

void CallExpression::compile(vector<Instruction *> &instructions)
{
	ostringstream oss;

	// pushWord function
	Function *function = Context::getFunction(_functionName);
	if (function == NULL)
		Log::getInstance().write(LOG_ERROR, "Function \"%s\" has not been declared !\n", _functionName.c_str());

	if (function->getNumberOfArguments() != _parameters.size())
		Log::getInstance().write(LOG_ERROR, "Function \"%s\" should have %u argument(s) !\n", _functionName.c_str(), function->getNumberOfArguments());

	// push function ID
	oss << function->getID();
	string functionID = oss.str();
	instructions.push_back(new Instruction("pushWord"));
	instructions.push_back(new Instruction(VALUE_WORD, functionID));

	// function parameters
	for (int i = 0; i < _parameters.size(); i++)
		_parameters[i]->compile(instructions);

	// invisible parameter __caller to prove this function is called from the code
	instructions.push_back(new Instruction("pushByte"));
	instructions.push_back(new Instruction(VALUE_BYTE, "1"));

	// pushWord parameters size
	oss.str("");
	oss << _parameters.size() + 1;
	instructions.push_back(new Instruction("pushByte"));
	instructions.push_back(new Instruction(VALUE_BYTE, oss.str()));

	// startScriptQuick instruction
	instructions.push_back(new Instruction("startScriptQuick2"));

	// If the function is not treated as a thread, we just wait until its execution is over
	if (!function->isThread())
	{
		// Prepare labels first
		uint32_t labelCounter = Context::labelCounter;
		Context::labelCounter++;

		instructions.push_back(new Instruction(labelCounter));

		// We let the scheduler take care of other threads
		instructions.push_back(new Instruction("pushByte"));
		instructions.push_back(new Instruction(VALUE_BYTE, "0"));
		instructions.push_back(new Instruction("delaySeconds"));

		// push function ID
		instructions.push_back(new Instruction("pushWord"));
		instructions.push_back(new Instruction(VALUE_WORD, functionID));

		// isScriptRunning instruction
		instructions.push_back(new Instruction("isScriptRunning"));

		// if instruction
		oss.str("");
		oss << "LABEL_" << labelCounter;
		instructions.push_back(new Instruction("if"));
		instructions.push_back(new Instruction(VALUE_WORD, oss.str()));
	}
	else
	{
		// If the function is a thread, we push 0 onto the stack
		instructions.push_back(new Instruction("pushByte"));
		instructions.push_back(new Instruction(VALUE_BYTE, "0"));
	}
}

CallExpression::~CallExpression()
{
	for (int i = 0; i < _parameters.size(); i++)
		delete _parameters[i];
}

