#include "Statement.hpp"
#include <set>
#include <sstream>
#include "util/Log.hpp"
#include "Context.hpp"
#include "Declaration.hpp"
#include "Expression.hpp"
#include "Instruction.hpp"

ExpressionStatement::ExpressionStatement(Expression *e)
{
	_expression = e;
}

void ExpressionStatement::compile(vector<Instruction *> &instructions)
{
	// expression
	_expression->compile(instructions);

	// pop instruction
	instructions.push_back(new Instruction("pop"));
}

ExpressionStatement::~ExpressionStatement()
{
	delete _expression;
}

BlockStatement::BlockStatement()
{
}

void BlockStatement::compile(vector<Instruction *> &instructions)
{
	Context context(CONTEXT_BLOCK, &_declarations, NULL, -1, -1, -1);
	Context::pushContext(&context);

	// block instructions
	for (int i = 0; i < _statements.size(); i++)
		_statements[i]->compile(instructions);

	Context::popContext();
}

BlockStatement::~BlockStatement()
{
	for (int i = 0; i < _declarations.size(); i++)
		delete _declarations[i];
	for (int i = 0; i < _statements.size(); i++)
		delete _statements[i];
}

IfStatement::IfStatement(Expression *e, Statement *s)
{
	_expression = e;
	_statement = s;
}

void IfStatement::compile(vector<Instruction *> &instructions)
{
	ostringstream oss;

	// Prepare label first
	uint32_t labelCounter = Context::labelCounter;
	Context::labelCounter++;

	// if condition
	_expression->compile(instructions);

	// ifNot instruction
	oss << "LABEL_" << labelCounter;
	instructions.push_back(new Instruction("ifNot"));
	instructions.push_back(new Instruction(VALUE_WORD, oss.str()));

	// if statement
	_statement->compile(instructions);

	// label
	instructions.push_back(new Instruction(labelCounter));
}

IfStatement::~IfStatement()
{
	delete _expression;
	delete _statement;
}

IfElseStatement::IfElseStatement(Expression *e, Statement *ifS, Statement *elseS)
{
	_expression = e;
	_ifStatement = ifS;
	_elseStatement = elseS;
}

void IfElseStatement::compile(vector<Instruction *> &instructions)
{
	ostringstream oss;

	// Prepare labels first
	uint32_t labelCounter = Context::labelCounter;
	Context::labelCounter += 2;

	// if condition
	_expression->compile(instructions);

	// ifNot instruction
	oss << "LABEL_" << labelCounter;
	instructions.push_back(new Instruction("ifNot"));
	instructions.push_back(new Instruction(VALUE_WORD, oss.str()));

	// if statement
	_ifStatement->compile(instructions);

	// jump instruction
	oss.str("");
	oss << "LABEL_" << labelCounter + 1;
	instructions.push_back(new Instruction("jump"));
	instructions.push_back(new Instruction(VALUE_WORD, oss.str()));

	// label
	instructions.push_back(new Instruction(labelCounter));

	// else statement
	_elseStatement->compile(instructions);

	// label
	instructions.push_back(new Instruction(labelCounter + 1));
}

IfElseStatement::~IfElseStatement()
{
	delete _expression;
	delete _ifStatement;
	delete _elseStatement;
}

CaseStatement::CaseStatement(Expression *e)
{
	_expression = e;
}

CaseStatement::CaseStatement()
{
	_expression = NULL;
}

// This function is called for switch "case" statements translation
void CaseStatement::compile(vector<Instruction *> &instructions)
{
	// case instructions
	for (int i = 0; i < _statements.size(); i++)
		_statements[i]->compile(instructions);
}

CaseStatement::~CaseStatement()
{
	if (_expression != NULL)
		delete _expression;
	for (int i = 0; i < _statements.size(); i++)
		delete _statements[i];
}

SwitchStatement::SwitchStatement(Expression *e)
{
	_expression = e;
}

void SwitchStatement::compile(vector<Instruction *> &instructions)
{
	ostringstream oss;

	// Prepare labels first
	uint32_t labelCounter = Context::labelCounter;
	Context::labelCounter += _caseStatements.size() + 1;

	Context context(CONTEXT_SWITCH, NULL, NULL, -1, labelCounter + _caseStatements.size(), -1);
	Context::pushContext(&context);

	// We first consider all the case conditions
	CaseStatement *defaultStatement = NULL;
	Expression *caseExpression;
	int defaultLabel;
	set<int16_t> caseValues;
	for (int i = 0; i < _caseStatements.size(); i++)
	{
		caseExpression = _caseStatements[i]->getExpression();

		// Check if it's not the default statement
		if (caseExpression == NULL)
		{
			if (defaultStatement != NULL)
				Log::getInstance().write(LOG_ERROR, "Only one default statement is allowed in switch statements !\n");
			defaultStatement = _caseStatements[i];
			defaultLabel = labelCounter + i;
			continue;
		}

		// switch expression
		_expression->compile(instructions);

		// case expression
		caseExpression->compile(instructions);

		// We check that the case expression is constant
		uint16_t value;
		if (caseExpression->getType() == EXPRESSION_VARIABLE)
		{
			string identifier = ((VariableExpression *)caseExpression)->getIdentifier();
			SymbolType symbolType;
			Context::resolveSymbol(identifier, value, symbolType);
			if (symbolType != SYMBOL_CONSTANT)
				Log::getInstance().write(LOG_ERROR, "Case expression \"%s\" is not constant !\n", identifier.c_str());
		}
		else
		{
			if (caseExpression->getType() != EXPRESSION_CONSTANT)
				Log::getInstance().write(LOG_ERROR, "Case expressions should always be constant !\n");
			value = ((ConstantExpression *)caseExpression)->getNumber();
		}

		// We check that the case expression has not already been used
		if (!caseValues.insert(value).second)
			Log::getInstance().write(LOG_ERROR, "Case value \"%d\" already used !\n", value);

		// if instruction
		instructions.push_back(new Instruction("eq"));

		// if instruction
		oss << "LABEL_" << labelCounter + i;
		instructions.push_back(new Instruction("if"));
		instructions.push_back(new Instruction(VALUE_WORD, oss.str()));
		oss.str("");
	}

	// default case
	if (defaultStatement != NULL)
	{
		// jump instruction
		oss << "LABEL_" << defaultLabel;
		instructions.push_back(new Instruction("jump"));
		instructions.push_back(new Instruction(VALUE_WORD, oss.str()));
		oss.str("");
	}
	else
	{
		Log::getInstance().write(LOG_WARNING, "Switch statement has no default case !\n");

		// jump instruction
		oss << "LABEL_" << labelCounter + _caseStatements.size();
		instructions.push_back(new Instruction("jump"));
		instructions.push_back(new Instruction(VALUE_WORD, oss.str()));
		oss.str("");
	}

	// Then we compile the case statements
	for (int i = 0; i < _caseStatements.size(); i++)
	{
		instructions.push_back(new Instruction(labelCounter + i));
		_caseStatements[i]->compile(instructions);
	}

	Context::popContext();

	// label
	instructions.push_back(new Instruction(labelCounter + _caseStatements.size()));
}

SwitchStatement::~SwitchStatement()
{
	delete _expression;
	for (int i = 0; i < _caseStatements.size(); i++)
		delete _caseStatements[i];
}

ForStatement::ForStatement(Expression *initE, Expression *conditionE, Expression *increaseE, Statement *s)
{
	_initExpression = initE;
	_conditionExpression = conditionE;
	_increaseExpression = increaseE;
	_statement = s;
}

void ForStatement::compile(vector<Instruction *> &instructions)
{
	ostringstream oss;

	// Prepare labels first
	uint32_t labelCounter = Context::labelCounter;
	Context::labelCounter += 2;

	// for initialization
	_initExpression->compile(instructions);

	// label
	instructions.push_back(new Instruction(labelCounter));

	// for condition
	_conditionExpression->compile(instructions);

	// ifNot instruction
	oss << "LABEL_" << labelCounter + 1;
	instructions.push_back(new Instruction("ifNot"));
	instructions.push_back(new Instruction(VALUE_WORD, oss.str()));

	Context context(CONTEXT_FOR, NULL, NULL, labelCounter, labelCounter + 1, -1);
	Context::pushContext(&context);

	// for statement
	_statement->compile(instructions);

	Context::popContext();

	// for increase
	_increaseExpression->compile(instructions);

	// jump instruction
	oss.str("");
	oss << "LABEL_" << labelCounter;
	instructions.push_back(new Instruction("jump"));
	instructions.push_back(new Instruction(VALUE_WORD, oss.str()));

	// label
	instructions.push_back(new Instruction(labelCounter + 1));
}

ForStatement::~ForStatement()
{
	delete _initExpression;
	delete _conditionExpression;
	delete _increaseExpression;
	delete _statement;
}

WhileStatement::WhileStatement(Expression *e, Statement *s)
{
	_expression = e;
	_statement = s;
}

void WhileStatement::compile(vector<Instruction *> &instructions)
{
	ostringstream oss;

	// Prepare labels first
	uint32_t labelCounter = Context::labelCounter;
	Context::labelCounter += 2;

	// label
	instructions.push_back(new Instruction(labelCounter));

	// while condition
	_expression->compile(instructions);

	// ifNot instruction
	oss << "LABEL_" << labelCounter + 1;
	instructions.push_back(new Instruction("ifNot"));
	instructions.push_back(new Instruction(VALUE_WORD, oss.str()));

	Context context(CONTEXT_WHILE, NULL, NULL, labelCounter, labelCounter + 1, -1);
	Context::pushContext(&context);

	// while statement
	_statement->compile(instructions);

	Context::popContext();

	// jump instruction
	oss.str("");
	oss << "LABEL_" << labelCounter;
	instructions.push_back(new Instruction("jump"));
	instructions.push_back(new Instruction(VALUE_WORD, oss.str()));

	// label
	instructions.push_back(new Instruction(labelCounter + 1));
}

WhileStatement::~WhileStatement()
{
	delete _expression;
	delete _statement;
}

ContinueStatement::ContinueStatement()
{
}

void ContinueStatement::compile(vector<Instruction *> &instructions)
{
	ostringstream oss;

	int32_t label = Context::getContinueLabel();
	if (label == -1)
		Log::getInstance().write(LOG_ERROR, "Keyword \"continue\" can only be used within loops !\n");

	// jump instruction
	oss << "LABEL_" << label;
	instructions.push_back(new Instruction("jump"));
	instructions.push_back(new Instruction(VALUE_WORD, oss.str()));
}

ContinueStatement::~ContinueStatement()
{
}

BreakStatement::BreakStatement()
{
}

void BreakStatement::compile(vector<Instruction *> &instructions)
{
	ostringstream oss;

	int32_t label = Context::getBreakLabel();
	if (label == -1)
		Log::getInstance().write(LOG_ERROR, "Keyword \"break\" can only be used within loops or switches !\n");

	// jump instruction
	oss << "LABEL_" << label;
	instructions.push_back(new Instruction("jump"));
	instructions.push_back(new Instruction(VALUE_WORD, oss.str()));
}

BreakStatement::~BreakStatement()
{
}

ReturnStatement::ReturnStatement(Expression *e)
{
	_expression = e;
}

void ReturnStatement::compile(vector<Instruction *> &instructions)
{
	ostringstream oss;

	if (_expression != NULL)
	{
		if (Context::insideThread())
			Log::getInstance().write(LOG_ERROR, "Threads can't return values !\n");

		// expression
		_expression->compile(instructions);

		// stopObjectCode
		instructions.push_back(new Instruction("stopObjectCode"));
	}
	else
	{
		// jump instruction
		oss << "LABEL_" << Context::getReturnLabel();
		instructions.push_back(new Instruction("jump"));
		instructions.push_back(new Instruction(VALUE_WORD, oss.str()));
	}
}

ReturnStatement::~ReturnStatement()
{
	if (_expression != NULL)
		delete _expression;
}

AssemblyStatement::AssemblyStatement()
{
}

void AssemblyStatement::compile(vector<Instruction *> &instructions)
{
	// Parse the block tokens
	uint32_t i = 0;
	while (i < _tokens.size())
	{
		string token = _tokens[i++];

		// First, check for "value" instructions
		ValueType valueType = VALUE_NULL;
		if (token == ".byte")
			valueType = VALUE_BYTE;
		else if (token == ".word")
			valueType = VALUE_WORD;
		else if (token == ".string")
			valueType = VALUE_STRING;

		// Get next token if the instruction is in fact a value
		string value;
		if (valueType != VALUE_NULL)
		{
			if (i == _tokens.size())
				Log::getInstance().write(LOG_ERROR, "A value is expected !\n");
			value = _tokens[i++];
		}

		// Resolve symbols if necessary
		if (valueType == VALUE_BYTE || valueType == VALUE_WORD)
		{
			istringstream iss(value);
			uint16_t v;
			if (!(iss >> v))
			{
				SymbolType symbolType;
				if (!Context::resolveSymbol(value, v, symbolType))
					Log::getInstance().write(LOG_ERROR, "Could not resolve symbol \"%s\" !\n", value.c_str());
				ostringstream oss;
				oss << v;
				value = oss.str();
			}
		}
		else if (valueType == VALUE_STRING)
			value = StringExpression::convertString(value);

		// Add instruction (which can be an opcode or a direct value)
		Instruction *instruction;
		if (valueType == VALUE_NULL)
			instruction = new Instruction(token);
		else
			instruction = new Instruction(valueType, value, value);
		instructions.push_back(instruction);
	}
}

AssemblyStatement::~AssemblyStatement()
{
}

