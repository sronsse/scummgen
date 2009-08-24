#include "Expression.hpp"
#include <sstream>
#include "util/Log.hpp"
#include "types/Game.hpp"
#include "Context.hpp"
#include "Declaration.hpp"
#include "Function.hpp"
#include "Instruction.hpp"
#include "Statement.hpp"

const uint8_t StringExpression::STRING_OPCODE = 0xFF;
const uint8_t StringExpression::INT_MESSAGE = 4;
const uint8_t StringExpression::VERB_MESSAGE = 5;
const uint8_t StringExpression::NAME_MESSAGE = 6;
const uint8_t StringExpression::STRING_MESSAGE = 7;
const uint8_t StringExpression::VOICE_MESSAGE = 10;

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
				Log::write(LOG_ERROR, "Found a division by zero !\n");
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
AssignableExpression(EXPRESSION_VARIABLE, identifier)
{
}

void VariableExpression::compile(vector<Instruction *> &instructions)
{
	uint32_t value;
	SymbolType symbolType;
	if (!Context::resolveSymbol(_identifier, value, symbolType))
		Log::write(LOG_ERROR, "Could not resolve symbol \"%s\" !\n", _identifier.c_str());
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
		case '%':
			c = '%';
			break;
		default:
			Log::write(LOG_ERROR, "Unknown escape character in string \"%s\" !\n", s.c_str());
	}

	return c;
}

string StringExpression::parseSpecialCode(string s, int &pos)
{
	string convertedString;

	// Special SCUMM string opcode
	convertedString += STRING_OPCODE;

	// Get special code
	uint8_t specialCode;
	switch (s[pos++])
	{
		case 'i':
			specialCode = INT_MESSAGE;
			break;
		case 'v':
			specialCode = VERB_MESSAGE;
			break;
		case 'n':
			specialCode = NAME_MESSAGE;
			break;
		case 's':
			specialCode = STRING_MESSAGE;
			break;
		case 'V':
			specialCode = VOICE_MESSAGE;
			break;
		default:
			Log::write(LOG_ERROR, "Unknown special code in string \"%s\" !\n", s.c_str());
	}
	convertedString += specialCode;

	// Parse, resolve and add symbol to the string
	string symbol = parseSymbol(s, pos);
	istringstream iss(symbol);
	uint32_t value;
	if (!(iss >> value))
	{
		SymbolType symbolType;
		if (!Context::resolveSymbol(symbol, value, symbolType))
			Log::write(LOG_ERROR, "Could not resolve symbol \"%s\" in string \"%s\" !\n", symbol.c_str(), s.c_str());
	}
	convertedString += (uint8_t)value;
	convertedString += (uint8_t)(value >> 8);

	// Specific case for voices
	if (specialCode == VOICE_MESSAGE)
	{
		uint8_t zero = 0;
		convertedString += STRING_OPCODE;
		convertedString += VOICE_MESSAGE;
		convertedString += (uint8_t)(value >> 16);
		convertedString += (uint8_t)(value >> 24);
		convertedString += STRING_OPCODE;
		convertedString += VOICE_MESSAGE;
		convertedString += zero;
		convertedString += zero;
		convertedString += STRING_OPCODE;
		convertedString += VOICE_MESSAGE;
		convertedString += zero;
		convertedString += zero;
	}

	return convertedString;
}

string StringExpression::parseSymbol(string s, int &pos)
{
	if (s[pos++] != '{')
		Log::write(LOG_ERROR, "Expected '{' while parsing special code in string \"%s\" !\n", s.c_str());

	// Get symbol
	string symbol;
	for (;;)
	{
		if (s[pos] == string::npos)
			Log::write(LOG_ERROR, "Expected '}' while parsing special code in string \"%s\" !\n", s.c_str());

		if (s[pos] == '}')
		{
			pos++;
			break;
		}

		symbol += s[pos++];
	}

	return symbol;
}

void StringExpression::compile(vector<Instruction *> &instructions)
{
	Log::write(LOG_ERROR, "String expressions can't be evaluated as is !\n");
}

void StringExpression::assign(vector<Instruction *> &instructions, uint32_t address)
{
	ostringstream oss;

	// Push index
	instructions.push_back(new Instruction("pushByte"));
	instructions.push_back(new Instruction(VALUE_BYTE, "0"));

	// Set the address contents to 0 to avoid the arrayOps assignString
	// from nuking or writing to a non-existing array
	oss << address;
	instructions.push_back(new Instruction("pushByte"));
	instructions.push_back(new Instruction(VALUE_BYTE, "0"));
	instructions.push_back(new Instruction("writeWordVar"));
	instructions.push_back(new Instruction(VALUE_WORD, oss.str()));

	// Add arrayOps assignString instruction
	instructions.push_back(new Instruction("arrayOps"));
	instructions.push_back(new Instruction("assignString"));
	instructions.push_back(new Instruction(VALUE_WORD, oss.str()));

	// Convert string and add the corresponding instruction
	instructions.push_back(new Instruction(VALUE_STRING, convertString(_string), _string));
}

StringExpression::~StringExpression()
{
}

ListExpression::ListExpression():
Expression(EXPRESSION_LIST)
{
}

void ListExpression::compile(vector<Instruction *> &instructions)
{
	Log::write(LOG_ERROR, "List expressions can't be evaluated as is !\n");
}

void ListExpression::assign(vector<Instruction *> &instructions, uint32_t address)
{
	ostringstream oss;

	// Push entries
	for (int i = 0; i < _entries.size(); i++)
		_entries[i]->compile(instructions);

	// Push dimensions
	oss << _entries.size();
	instructions.push_back(new Instruction("pushWord"));
	instructions.push_back(new Instruction(VALUE_WORD, oss.str()));
	instructions.push_back(new Instruction("pushByte"));
	instructions.push_back(new Instruction(VALUE_BYTE, "0"));

	oss.str("");
	oss << address;

	// Set the address contents to 0 to avoid the arrayOps assignIntList
	// from nuking and writing to a non-existing array
	instructions.push_back(new Instruction("pushByte"));
	instructions.push_back(new Instruction(VALUE_BYTE, "0"));
	instructions.push_back(new Instruction("writeWordVar"));
	instructions.push_back(new Instruction(VALUE_WORD, oss.str()));

	// Add arrayOps assignIntList instruction
	instructions.push_back(new Instruction("arrayOps"));
	instructions.push_back(new Instruction("assignIntList"));
	instructions.push_back(new Instruction(VALUE_WORD, oss.str()));
}

ListExpression::~ListExpression()
{
	for (int i = 0; i < _entries.size(); i++)
		delete _entries[i];
}

ListEntryExpression::ListEntryExpression(string identifier, Expression *e):
AssignableExpression(EXPRESSION_LIST_ENTRY, identifier)
{
	_e = e;
}

void ListEntryExpression::compile(vector<Instruction *> &instructions)
{
	uint32_t value;
	SymbolType symbolType;
	if (!Context::resolveSymbol(_identifier, value, symbolType))
		Log::write(LOG_ERROR, "Could not resolve symbol \"%s\" !\n", _identifier.c_str());
	ostringstream oss;
	oss << value;

	// push base
	_e->compile(instructions);

	// wordArrayRead instruction
	instructions.push_back(new Instruction("wordArrayRead"));
	instructions.push_back(new Instruction(VALUE_WORD, oss.str()));
}

ListEntryExpression::~ListEntryExpression()
{
	delete _e;
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
			instructions.push_back(new Instruction("pushByte"));
			instructions.push_back(new Instruction(VALUE_BYTE, "0"));
			_e->compile(instructions);
			instructions.push_back(new Instruction("sub"));
			break;
		case EXPRESSION_NOT:
			_e->compile(instructions);
			instructions.push_back(new Instruction("not"));
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

AssignmentExpression::AssignmentExpression(AssignmentType assignmentType, bool preOperation, AssignableExpression *a, Expression *e):
Expression(EXPRESSION_ASSIGNMENT)
{
	_assignmentType = assignmentType;
	_preOperation = preOperation;
	_assignableExpression = a;
	_expression = e;
}

void AssignmentExpression::compile(vector<Instruction *> &instructions)
{
	// Check the assignable expression type as it should be a variable or a list entry
	string identifier = _assignableExpression->getIdentifier();
	uint32_t address;
	SymbolType symbolType;
	if (!Context::resolveSymbol(identifier, address, symbolType))
		Log::write(LOG_ERROR, "Could not resolve symbol \"%s\" !\n", identifier.c_str());
	if (symbolType != SYMBOL_VARIABLE)
		Log::write(LOG_ERROR, "Assignements only apply to variables and list entry expressions !\n");
	ostringstream oss;
	oss << address;

	// Push the assignable expression on the stack in case of a "post-operation"
	if (!_preOperation)
		_assignableExpression->compile(instructions);

	if (_assignableExpression->getType() == EXPRESSION_VARIABLE)
	{
		// We have to consider strings and arrays differently
		if (_expression->getType() == EXPRESSION_STRING)
		{
			if (_assignmentType != ASSIGNMENT_EQUAL)
				Log::write(LOG_ERROR, "Incrementations and decrementations don't apply to strings !\n");
			((StringExpression *)_expression)->assign(instructions, address);
		}
		else if (_expression->getType() == EXPRESSION_LIST)
		{
			if (_assignmentType != ASSIGNMENT_EQUAL)
				Log::write(LOG_ERROR, "Incrementations and decrementations don't apply to lists !\n");
			((ListExpression *)_expression)->assign(instructions, address);
		}
		else
		{
			switch (_assignmentType)
			{
				case ASSIGNMENT_EQUAL:
					_expression->compile(instructions);
					break;
				case ASSIGNMENT_INC:
					_assignableExpression->compile(instructions);
					_expression->compile(instructions);
					instructions.push_back(new Instruction("add"));
					break;
				case ASSIGNMENT_DEC:
					_assignableExpression->compile(instructions);
					_expression->compile(instructions);
					instructions.push_back(new Instruction("sub"));
					break;
			}

			// Write variable
			instructions.push_back(new Instruction("writeWordVar"));
			instructions.push_back(new Instruction(VALUE_WORD, oss.str()));
		}
	}
	// It's a list entry expression
	else 
	{
		if ((_expression->getType() == EXPRESSION_STRING) || (_expression->getType() == EXPRESSION_LIST))
			Log::write(LOG_ERROR, "Cannot assign strings or lists to list entry expressions !\n");

		// Push base
		((ListEntryExpression *)_assignableExpression)->getExpression()->compile(instructions);

		switch (_assignmentType)
		{
			case ASSIGNMENT_EQUAL:
				_expression->compile(instructions);
				break;
			case ASSIGNMENT_INC:
				_assignableExpression->compile(instructions);
				_expression->compile(instructions);
				instructions.push_back(new Instruction("add"));
				break;
			case ASSIGNMENT_DEC:
				_assignableExpression->compile(instructions);
				_expression->compile(instructions);
				instructions.push_back(new Instruction("sub"));
				break;
		}

		// wordArrayWrite instruction
		instructions.push_back(new Instruction("wordArrayWrite"));
		instructions.push_back(new Instruction(VALUE_WORD, oss.str()));
	}

	// Push what we just wrote on the stack in case of a "pre-operation"
	if (_preOperation)
		_assignableExpression->compile(instructions);
}

AssignmentExpression::~AssignmentExpression()
{
	delete _assignableExpression;
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

	// Get function
	Function *function = Context::getFunction(_functionName);
	if (function == NULL)
		Log::write(LOG_ERROR, "Function \"%s\" has not been declared !\n", _functionName.c_str());

	if (_parameters.size() != function->getNumberOfArguments())
		Log::write(LOG_ERROR, "Function \"%s\" should have %u argument(s) !\n", _functionName.c_str(), function->getNumberOfArguments());

	// If the function is inlined, we compile it and add the instructions to the current function
	if (function->getType() == FUNCTION_INLINED)
	{
		// We first build a declarations list
		vector<Declaration *> declarations;
		for (int i = 0; i < function->getNumberOfArguments(); i++)
			declarations.push_back(new Declaration(DECLARATION_VAR, function->getArgument(i)->getName()));
		for (int i = 0; i < function->getBlockStatement()->getNumberOfDeclarations(); i++)
		{
			Declaration *declaration = function->getBlockStatement()->getDeclaration(i);
			// Variable and constant declaration have to be treated separately
			if (declaration->getType() == DECLARATION_VAR)
				declarations.push_back(new Declaration(declaration->getType(), declaration->getName()));
			else
				declarations.push_back(new Declaration(declaration->getType(), declaration->getName(), declaration->getValue()));
		}
		declarations.push_back(new Declaration(DECLARATION_VAR, "returnValue"));

		// Prepare labels first
		uint32_t labelCounter = Context::labelCounter;
		Context::labelCounter++;

		// Create the inlined context and push it a first time to get the argument addresses
		Context *context = new Context(CONTEXT_INLINED, &declarations, NULL, -1, -1, labelCounter);
		Context::pushContext(context);

		// Store the addresses of the function arguments
		vector<uint16_t> argumentAddresses;
		for (int i = 0; i < _parameters.size(); i++)
		{
			uint32_t value;
			SymbolType symbolType;
			Context::resolveSymbol(function->getArgument(i)->getName(), value, symbolType);
			argumentAddresses.push_back(value);
		}

		// Pop the inlined context as the parameters shouldn't be aware of it
		Context::popContext();
		delete context;

		// Push parameters
		for (int i = 0; i < _parameters.size(); i++)
		{
			oss.str("");
			oss << argumentAddresses[i];

			// Special case for strings
			if (_parameters[i]->getType() == EXPRESSION_STRING)
				((StringExpression *)_parameters[i])->assign(instructions, argumentAddresses[i]);
			else if (_parameters[i]->getType() == EXPRESSION_LIST)
				((ListExpression *)_parameters[i])->assign(instructions, argumentAddresses[i]);
			else
			{
				_parameters[i]->compile(instructions);

				// writeWordVar instruction
				instructions.push_back(new Instruction("writeWordVar"));
				instructions.push_back(new Instruction(VALUE_WORD, oss.str()));
			}
		}

		// Recreate the context and push it again for the block statement
		context = new Context(CONTEXT_INLINED, &declarations, NULL, -1, -1, labelCounter);
		Context::pushContext(context);

		// Compile the function block statements
		for (int i = 0; i < function->getBlockStatement()->getNumberOfStatements(); i++)
			function->getBlockStatement()->getStatement(i)->compile(instructions);

		// We have to nuke the previous allocated arrays
		for (int i = 0; i < _parameters.size(); i++)
			if (_parameters[i]->getType() == EXPRESSION_STRING || _parameters[i]->getType() == EXPRESSION_LIST)
			{
				oss.str("");
				oss << argumentAddresses[i];

				// undim array
				instructions.push_back(new Instruction("dimArray"));
				instructions.push_back(new Instruction("undimArray"));
				instructions.push_back(new Instruction(VALUE_WORD, oss.str()));
			}
			
		// Return label
		instructions.push_back(new Instruction(labelCounter));
		
		// Push return value
		uint32_t value;
		SymbolType symbolType;
		Context::resolveSymbol("returnValue", value, symbolType);
		oss.str("");
		oss << value;
		instructions.push_back(new Instruction("pushWordVar"));
		instructions.push_back(new Instruction(VALUE_WORD, oss.str()));

		// No need to use the inlined context anymore
		Context::popContext();
		delete context;

		// Delete the previous created declarations
		for (int i = 0; i < declarations.size(); i++)
			delete declarations[i];
	}
	else
	{
		// push function ID
		oss.str("");
		oss << function->getID();
		string functionID = oss.str();
		instructions.push_back(new Instruction("pushWord"));
		instructions.push_back(new Instruction(VALUE_WORD, functionID));

		// function parameters
		for (int i = 0; i < _parameters.size(); i++)
			_parameters[i]->compile(instructions);

		// pushWord parameters size
		oss.str("");
		oss << _parameters.size();
		instructions.push_back(new Instruction("pushByte"));
		instructions.push_back(new Instruction(VALUE_BYTE, oss.str()));

		// startScriptQuick instruction
		instructions.push_back(new Instruction("startScriptQuick"));

		// If the function is not treated as a thread, we just wait until its execution is over
		if (function->getType() == FUNCTION_NORMAL)
		{
			// Prepare labels first
			uint32_t labelCounter = Context::labelCounter;
			Context::labelCounter++;

			instructions.push_back(new Instruction(labelCounter));

			// We let the scheduler take care of other threads
			instructions.push_back(new Instruction("breakHere"));

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

		// For now, we just push 0 as a return value for normal functions and threads
		instructions.push_back(new Instruction("pushByte"));
		instructions.push_back(new Instruction(VALUE_BYTE, "0"));
	}
}

CallExpression::~CallExpression()
{
	for (int i = 0; i < _parameters.size(); i++)
		delete _parameters[i];
}
