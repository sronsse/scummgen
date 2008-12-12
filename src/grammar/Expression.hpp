#ifndef _EXPRESSION_HPP_
#define _EXPRESSION_HPP_

#include <map>
#include <stdint.h>
#include <string>
#include <vector>
using namespace std;

class Instruction;

typedef enum
{
	EXPRESSION_VARIABLE,
	EXPRESSION_CONSTANT,
	EXPRESSION_STRING,
	EXPRESSION_UMINUS,
	EXPRESSION_NOT,
	EXPRESSION_ADD,
	EXPRESSION_SUB,
	EXPRESSION_DIV,
	EXPRESSION_MUL,
	EXPRESSION_LT,
	EXPRESSION_GT,
	EXPRESSION_BAND,
	EXPRESSION_BOR,
	EXPRESSION_LE,
	EXPRESSION_GE,
	EXPRESSION_NE,
	EXPRESSION_EQ,
	EXPRESSION_LAND,
	EXPRESSION_LOR,
	EXPRESSION_ASSIGNMENT,
	EXPRESSION_CALL,
	EXPRESSION_PREINC,
	EXPRESSION_POSTINC,
	EXPRESSION_PREDEC,
	EXPRESSION_POSTDEC
} ExpressionType;

class Expression
{
protected:
	ExpressionType _type;
public:
	static Expression *simplifyUnaryExpression(ExpressionType type, Expression *e);
	static Expression *simplifyBinaryExpression(ExpressionType type, Expression *e1, Expression *e2);

	Expression(ExpressionType type) { _type = type; }
	ExpressionType getType() { return _type; }
	virtual void compile(vector<Instruction *> &instructions) = 0;
	virtual ~Expression() {}
};

class VariableExpression: public Expression
{
private:
	string _identifier;
public:
	VariableExpression(string identifier);
	string getIdentifier() { return _identifier; }
	void compile(vector<Instruction *> &instructions);
	~VariableExpression();
};

class ConstantExpression: public Expression
{
private:
	int32_t _number;
public:
	ConstantExpression(int32_t number);
	int32_t getNumber() { return _number; }
	void compile(vector<Instruction *> &instructions);
	~ConstantExpression();
};

class StringExpression: public Expression
{
private:
	string _string;

	static char parseEscapeCharacter(string s, int &pos);
	static string parseSpecialCode(string s, int &pos);
	static string parseSymbol(string s, int &pos);
public:
	static string convertString(string s);

	StringExpression(string s);
	string getString() { return _string; }
	void compile(vector<Instruction *> &instructions);
	~StringExpression();
};

class UnaryExpression: public Expression
{
private:
	Expression *_e;
public:
	UnaryExpression(ExpressionType type, Expression *e);
	void compile(vector<Instruction *> &instructions);
	~UnaryExpression();
};

class BinaryExpression: public Expression
{
private:
	Expression *_e1;
	Expression *_e2;
public:
	BinaryExpression(ExpressionType type, Expression *e1, Expression *e2);
	void compile(vector<Instruction *> &instructions);
	~BinaryExpression();
};

class AssignmentExpression: public Expression
{
private:
	Expression *_expression;
	VariableExpression *_variable;
public:
	AssignmentExpression(VariableExpression *v, Expression *e);
	void compile(vector<Instruction *> &instructions);
	~AssignmentExpression();
};

class CallExpression: public Expression
{
private:
	string _functionName;
	vector<Expression *>_parameters;
public:
	CallExpression(string functionName);
	void addParameter(Expression *parameter) { _parameters.push_back(parameter); }
	void compile(vector<Instruction *> &instructions);
	~CallExpression();
};

#endif

