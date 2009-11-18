#ifndef _STATEMENT_HPP_
#define _STATEMENT_HPP_

#include <stdint.h>
#include <string>
#include <vector>
using namespace std;

class Declaration;
class Expression;
class VariableExpression;
class Instruction;

class Statement
{
public:
	Statement() {};
	virtual void compile(vector<Instruction *> &instructions) = 0;
	virtual ~Statement() {};
};

class ExpressionStatement: public Statement
{
private:
	Expression *_expression;
public:
	ExpressionStatement(Expression *e);
	void compile(vector<Instruction *> &instructions);
	~ExpressionStatement();
};

class BlockStatement: public Statement
{
private:
	vector<Declaration *> _declarations;
	vector<Statement *> _statements;
public:
	BlockStatement();
	void addDeclaration(Declaration *d) { _declarations.push_back(d); }
	uint32_t getNumberOfDeclarations() { return _declarations.size(); }
	Declaration *getDeclaration(uint32_t index) { return _declarations[index]; }
	void addStatement(Statement *s) { _statements.push_back(s); }
	uint32_t getNumberOfStatements() { return _statements.size(); }
	Statement *getStatement(uint32_t index) { return _statements[index]; }
	void compile(vector<Instruction *> &instructions);
	~BlockStatement();
};

class IfStatement: public Statement
{
private:
	Expression *_expression;
	Statement *_statement;
public:
	IfStatement(Expression *e, Statement *s);
	void compile(vector<Instruction *> &instructions);
	~IfStatement();
};

class IfElseStatement: public Statement
{
private:
	Expression *_expression;
	Statement *_ifStatement;
	Statement *_elseStatement;
public:
	IfElseStatement(Expression *e, Statement *ifS, Statement *elseS);
	void compile(vector<Instruction *> &instructions);
	~IfElseStatement();
};

class CaseStatement: public Statement
{
private:
	Expression *_expression;
	vector<Statement *> _statements;
public:
	CaseStatement(Expression *e);
	CaseStatement();
	Expression *getExpression() { return _expression; }
	void addStatement(Statement *s) { _statements.push_back(s); }
	void compile(vector<Instruction *> &instructions);
	~CaseStatement();
};

class SwitchStatement: public Statement
{
private:
	Expression *_expression;
	vector<CaseStatement *> _caseStatements;
public:
	SwitchStatement(Expression *e);
	void addCaseStatement(CaseStatement *caseS) { _caseStatements.push_back(caseS); }
	void compile(vector<Instruction *> &instructions);
	~SwitchStatement();
};

class VerbStatement: public Statement
{
private:
	static const uint8_t HEADER_SIZE;
	vector<CaseStatement *> _caseStatements;
public:
	VerbStatement();
	void addCaseStatement(CaseStatement *caseS) { _caseStatements.push_back(caseS); }
	void compile(vector<Instruction *> &instructions);
	~VerbStatement();
};

class ForStatement: public Statement
{
private:
	ExpressionStatement *_initExpressionStatement;
	Expression *_conditionExpression;
	ExpressionStatement *_increaseExpressionStatement;
	Statement *_statement;
public:
	ForStatement(ExpressionStatement *initES, Expression *conditionE, ExpressionStatement *increaseES, Statement *s);
	void compile(vector<Instruction *> &instructions);
	~ForStatement();
};

class WhileStatement: public Statement
{
private:
	Expression *_expression;
	Statement *_statement;
public:
	WhileStatement(Expression *e, Statement *s);
	void compile(vector<Instruction *> &instructions);
	~WhileStatement();
};

class DoWhileStatement: public Statement
{
private:
	Statement *_statement;
	Expression *_expression;
public:
	DoWhileStatement(Statement *s, Expression *e);
	void compile(vector<Instruction *> &instructions);
	~DoWhileStatement();
};

class ContinueStatement: public Statement
{
public:
	ContinueStatement();
	void compile(vector<Instruction *> &instructions);
	~ContinueStatement();
};

class BreakStatement: public Statement
{
public:
	BreakStatement();
	void compile(vector<Instruction *> &instructions);
	~BreakStatement();
};

class ReturnStatement: public Statement
{
	Expression *_expression;
public:
	ReturnStatement(Expression *e = NULL);
	void compile(vector<Instruction *> &instructions);
	~ReturnStatement();
};

class CutsceneStatement: public Statement
{
private:
	Statement *_statement;
	vector<Expression *> _parameters;
public:
	CutsceneStatement(Statement *s);
	void addParameter(Expression *parameter) { _parameters.push_back(parameter); }
	void compile(vector<Instruction *> &instructions);
	~CutsceneStatement();
};

class TryCatchFinallyStatement: public Statement
{
private:
	Statement *_tryStatement;
	Statement *_catchStatement;
	Statement *_finallyStatement;
public:
	TryCatchFinallyStatement(Statement *tryS, Statement *catchS, Statement *finallyS);
	void compile(vector<Instruction *> &instructions);
	~TryCatchFinallyStatement();
};

class AssemblyStatement: public Statement
{
private:
	vector<string> _tokens;
public:
	AssemblyStatement();
	void addToken(string token) { _tokens.push_back(token); }
	void compile(vector<Instruction *> &instructions);
	~AssemblyStatement();
};

#endif

