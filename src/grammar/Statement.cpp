#include "Statement.hpp"
#include <set>
#include <sstream>
#include "util/Log.hpp"
#include "Context.hpp"
#include "Declaration.hpp"
#include "Expression.hpp"
#include "Instruction.hpp"

const uint8_t VerbStatement::HEADER_SIZE = 8;

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
	Context::labelCounter += _elseStatement != NULL ? 2 : 1;

	// if condition
	_expression->compile(instructions);

	// ifNot instruction
	oss << "LABEL_" << labelCounter;
	instructions.push_back(new Instruction("ifNot"));
	instructions.push_back(new Instruction(VALUE_WORD, oss.str()));

	// if statement
	_ifStatement->compile(instructions);

	// The following code is generated only if an else statement is present
	if (_elseStatement != NULL)
	{
		// jump instruction
		oss.str("");
		oss << "LABEL_" << labelCounter + 1;
		instructions.push_back(new Instruction("jump"));
		instructions.push_back(new Instruction(VALUE_WORD, oss.str()));
	}

	// label
	instructions.push_back(new Instruction(labelCounter));

	// The following code is generated only if an else statement is present
	if (_elseStatement != NULL)
	{
		// else statement
		_elseStatement->compile(instructions);

		// label
		instructions.push_back(new Instruction(labelCounter + 1));
	}
}

IfElseStatement::~IfElseStatement()
{
	delete _expression;
	delete _ifStatement;
	if (_elseStatement != NULL)
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
	int defaultLabel = -1;
	set<int16_t> caseValues;
	for (int i = 0; i < _caseStatements.size(); i++)
	{
		caseExpression = _caseStatements[i]->getExpression();

		// Check if it's not the default statement
		if (caseExpression == NULL)
		{
			if (defaultStatement != NULL)
				Log::write(LOG_ERROR, "Only one default statement is allowed in switch statements !\n");
			defaultStatement = _caseStatements[i];
			defaultLabel = labelCounter + i;
			continue;
		}

		// switch expression
		_expression->compile(instructions);

		// case expression
		caseExpression->compile(instructions);

		// We check that the case expression is constant
		uint32_t value;
		if (caseExpression->getType() == EXPRESSION_VARIABLE)
		{
			string identifier = ((VariableExpression *)caseExpression)->getIdentifier();
			SymbolType symbolType;
			if (!Context::resolveSymbol(identifier, value, symbolType))
				Log::write(LOG_ERROR, "Could not resolve symbol \"%s\" !\n", identifier.c_str());
			if (symbolType != SYMBOL_CONSTANT)
				Log::write(LOG_ERROR, "Case expression \"%s\" is not constant !\n", identifier.c_str());
		}
		else
		{
			if (caseExpression->getType() != EXPRESSION_CONSTANT)
				Log::write(LOG_ERROR, "Case expressions should always be constant !\n");
			value = ((ConstantExpression *)caseExpression)->getNumber();
		}

		// We check that the case expression has not already been used
		if (!caseValues.insert(value).second)
			Log::write(LOG_ERROR, "Case value \"%d\" already used !\n", value);

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
		Log::write(LOG_WARNING, "Switch statement has no default case !\n");

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

VerbStatement::VerbStatement()
{
}

void VerbStatement::compile(vector<Instruction *> &instructions)
{
	ostringstream oss;

	// Prepare labels first
	uint32_t labelCounter = Context::labelCounter;
	Context::labelCounter++;

	// Set the verb table index
	uint16_t verbTableIndex = instructions.size();

	Context context(CONTEXT_VERB, NULL, NULL, -1, labelCounter, -1);
	Context::pushContext(&context);

	// We first consider all the case conditions
	CaseStatement *defaultStatement = NULL;
	Expression *caseExpression;
	set<int16_t> caseValues;
	for (int i = 0; i < _caseStatements.size(); i++)
	{
		caseExpression = _caseStatements[i]->getExpression();

		// Check if it's not the default statement
		if (caseExpression == NULL)
		{
			if (defaultStatement != NULL)
				Log::write(LOG_ERROR, "Only one default statement is allowed in switch statements !\n");
			defaultStatement = _caseStatements[i];
			// Default statements are equivalent to a verb of value 0xFF
			instructions.push_back(new Instruction(VALUE_BYTE, "255"));
			instructions.push_back(new Instruction(VALUE_WORD, "0"));
			continue;
		}

		// We check that the case expression is constant
		uint32_t value;
		if (caseExpression->getType() == EXPRESSION_VARIABLE)
		{
			string identifier = ((VariableExpression *)caseExpression)->getIdentifier();
			SymbolType symbolType;
			if (!Context::resolveSymbol(identifier, value, symbolType))
				Log::write(LOG_ERROR, "Could not resolve symbol \"%s\" !\n", identifier.c_str());
			if (symbolType != SYMBOL_CONSTANT)
				Log::write(LOG_ERROR, "Case expression \"%s\" is not constant !\n", identifier.c_str());
		}
		else
		{
			if (caseExpression->getType() != EXPRESSION_CONSTANT)
				Log::write(LOG_ERROR, "Case expressions should always be constant !\n");
			value = ((ConstantExpression *)caseExpression)->getNumber();
		}

		// We check that the case expression has not already been used
		if (!caseValues.insert(value).second)
			Log::write(LOG_ERROR, "Case value \"%d\" already used !\n", value);

		// Add verb table entry (the address is filled later)
		oss << value;
		instructions.push_back(new Instruction(VALUE_BYTE, oss.str()));
		instructions.push_back(new Instruction(VALUE_WORD, "0"));
		oss.str("");
	}

	if (defaultStatement == NULL)
		Log::write(LOG_WARNING, "Verb statement has no default case !\n");

	// End of table index
	instructions.push_back(new Instruction(VALUE_BYTE, "0"));

	// Then we compile the case statements
	for (int i = 0; i < _caseStatements.size(); i++)
	{
		// Replace the verb address with a correct value
		oss << Context::currentAddress + HEADER_SIZE;
		instructions[verbTableIndex + i * 2 + 1]->setValue(oss.str());
		_caseStatements[i]->compile(instructions);
		oss.str("");
	}

	Context::popContext();

	// label
	instructions.push_back(new Instruction(labelCounter));
}

VerbStatement::~VerbStatement()
{
	for (int i = 0; i < _caseStatements.size(); i++)
		delete _caseStatements[i];
}

ForStatement::ForStatement(ExpressionStatement *initES, Expression *conditionE, ExpressionStatement *increaseES, Statement *s)
{
	_initExpressionStatement = initES;
	_conditionExpression = conditionE;
	_increaseExpressionStatement = increaseES;
	_statement = s;
}

void ForStatement::compile(vector<Instruction *> &instructions)
{
	ostringstream oss;

	// Prepare labels first
	uint32_t labelCounter = Context::labelCounter;
	Context::labelCounter += 2;

	// for initialization
	_initExpressionStatement->compile(instructions);

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
	_increaseExpressionStatement->compile(instructions);

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
	delete _initExpressionStatement;
	delete _conditionExpression;
	delete _increaseExpressionStatement;
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

DoWhileStatement::DoWhileStatement(Statement *s, Expression *e)
{
	_statement = s;
	_expression = e;
}

void DoWhileStatement::compile(vector<Instruction *> &instructions)
{
	ostringstream oss;

	// Prepare labels first
	uint32_t labelCounter = Context::labelCounter;
	Context::labelCounter += 3;

	// label
	instructions.push_back(new Instruction(labelCounter));

	Context context(CONTEXT_DO_WHILE, NULL, NULL, labelCounter + 1, labelCounter + 2, -1);
	Context::pushContext(&context);

	// do statement
	_statement->compile(instructions);

	Context::popContext();

	// label
	instructions.push_back(new Instruction(labelCounter + 1));

	// while condition
	_expression->compile(instructions);

	// if instruction
	oss << "LABEL_" << labelCounter;
	instructions.push_back(new Instruction("if"));
	instructions.push_back(new Instruction(VALUE_WORD, oss.str()));

	// label
	instructions.push_back(new Instruction(labelCounter + 2));
}

DoWhileStatement::~DoWhileStatement()
{
	delete _statement;
	delete _expression;
}

ContinueStatement::ContinueStatement()
{
}

void ContinueStatement::compile(vector<Instruction *> &instructions)
{
	ostringstream oss;

	int32_t label = Context::getContinueLabel();
	if (label == -1)
		Log::write(LOG_ERROR, "Keyword \"continue\" can only be used within loops !\n");

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
		Log::write(LOG_ERROR, "Keyword \"break\" can only be used within loops or switches !\n");

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

	// If an expression has been specified, we return it (only if we're in an inlined function)
	if (_expression != NULL && Context::getFunctionType() != FUNCTION_INLINED)
		Log::write(LOG_ERROR, "Return values are only accepted in inlined functions !\n");

	if (Context::getFunctionType() == FUNCTION_INLINED && _expression != NULL)
	{
		// Compile expression
		_expression->compile(instructions);

		// Write result
		uint32_t value;
		SymbolType symbolType;
		Context::resolveSymbol("returnValue", value, symbolType);
		oss << value;
		instructions.push_back(new Instruction("writeWordVar"));
		instructions.push_back(new Instruction(VALUE_WORD, oss.str()));
	}

	// jump instruction
	oss.str("");
	oss << "LABEL_" << Context::getReturnLabel();
	instructions.push_back(new Instruction("jump"));
	instructions.push_back(new Instruction(VALUE_WORD, oss.str()));
}

ReturnStatement::~ReturnStatement()
{
	if (_expression != NULL)
		delete _expression;
}

CutsceneStatement::CutsceneStatement(Statement *s)
{
	_statement = s;
}

void CutsceneStatement::compile(vector<Instruction *> &instructions)
{
	ostringstream oss;

	// cutscene parameters
	for (int i = 0; i < _parameters.size(); i++)
		_parameters[i]->compile(instructions);

	// pushWord parameters size
	oss << _parameters.size();
	instructions.push_back(new Instruction("pushByte"));
	instructions.push_back(new Instruction(VALUE_BYTE, oss.str()));

	// cutscene instruction
	instructions.push_back(new Instruction("cutscene"));

	// cutscene statement
	_statement->compile(instructions);

	// endCutscene instruction
	instructions.push_back(new Instruction("endCutscene"));
}

CutsceneStatement::~CutsceneStatement()
{
	delete _statement;
}

TryCatchFinallyStatement::TryCatchFinallyStatement(Statement *tryS, Statement *catchS, Statement *finallyS)
{
	_tryStatement = tryS;
	_catchStatement = catchS;
	_finallyStatement = finallyS;
}

void TryCatchFinallyStatement::compile(vector<Instruction *> &instructions)
{
	ostringstream oss;

	// Prepare labels first
	uint32_t labelCounter = Context::labelCounter;
	Context::labelCounter += _catchStatement != NULL ? 2 : 1;

	// beginOverride instruction
	instructions.push_back(new Instruction("beginOverride"));

	// jump instruction
	oss << "LABEL_" << labelCounter;
	instructions.push_back(new Instruction("jump"));
	instructions.push_back(new Instruction(VALUE_WORD, oss.str()));
	
	// try statement
	_tryStatement->compile(instructions);

	// label
	instructions.push_back(new Instruction(labelCounter));

	// The following code is generated only if a catch statement is present
	if (_catchStatement != NULL)
	{
		// Push VAR_OVERRIDE value
		uint32_t value;
		SymbolType symbolType;
		Context::resolveSymbol("VAR_OVERRIDE", value, symbolType);
		oss.str("");
		oss << value;
		instructions.push_back(new Instruction("pushWordVar"));
		instructions.push_back(new Instruction(VALUE_WORD, oss.str()));

		// ifNot instruction
		oss.str("");
		oss << "LABEL_" << labelCounter + 1;
		instructions.push_back(new Instruction("ifNot"));
		instructions.push_back(new Instruction(VALUE_WORD, oss.str()));

		// catch statement
		_catchStatement->compile(instructions);

		// label
		instructions.push_back(new Instruction(labelCounter + 1));
	}

	// finally statement (if present)
	if (_finallyStatement != NULL)
		_finallyStatement->compile(instructions);

	// endOverride instruction
	instructions.push_back(new Instruction("endOverride"));
}

TryCatchFinallyStatement::~TryCatchFinallyStatement()
{
	delete _tryStatement;
	if (_catchStatement != NULL)
		delete _catchStatement;
	if (_finallyStatement != NULL)
		delete _finallyStatement;
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
		string originalValue;
		if (valueType != VALUE_NULL)
		{
			if (i == _tokens.size())
				Log::write(LOG_ERROR, "A value is expected !\n");
			originalValue = _tokens[i++];
		}

		// Resolve symbols if necessary
		string convertedValue;
		if (valueType == VALUE_BYTE || valueType == VALUE_WORD)
		{
			istringstream iss(originalValue);
			uint32_t v;
			if (iss >> v)
				convertedValue = originalValue;
			else
			{
				SymbolType symbolType;
				if (!Context::resolveSymbol(originalValue, v, symbolType))
					Log::write(LOG_ERROR, "Could not resolve symbol \"%s\" !\n", originalValue.c_str());
				ostringstream oss;
				oss << v;
				convertedValue = oss.str();
			}
		}
		else if (valueType == VALUE_STRING)
			convertedValue = StringExpression::convertString(originalValue);

		// Add instruction (which can be an opcode or a direct value)
		Instruction *instruction;
		if (valueType == VALUE_NULL)
			instruction = new Instruction(token);
		else
			instruction = new Instruction(valueType, convertedValue, valueType == VALUE_STRING ? originalValue : "");

		instructions.push_back(instruction);
	}
}

AssemblyStatement::~AssemblyStatement()
{
}
