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
	EXPRESSION_LIST,
	EXPRESSION_LIST_ENTRY,
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

class AssignableExpression: public Expression
{
protected:
	string _identifier;
public:
	AssignableExpression(ExpressionType type, string identifier): Expression(type) {_identifier = identifier; }
	string getIdentifier() { return _identifier; }
	virtual void compile(vector<Instruction *> &instructions) = 0;
	virtual ~AssignableExpression() {}
};

class VariableExpression: public AssignableExpression
{
public:
	VariableExpression(string identifier);
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
	static const uint8_t STRING_OPCODE;
	static const uint8_t INT_MESSAGE;
	static const uint8_t VERB_MESSAGE;
	static const uint8_t NAME_MESSAGE;
	static const uint8_t STRING_MESSAGE;

	string _string;

	static char parseEscapeCharacter(string s, int &pos);
	static string parseSpecialCode(string s, int &pos);
	static string parseSymbol(string s, int &pos);
public:
	static string convertString(string s);

	StringExpression(string s);
	string getString() { return _string; }
	void compile(vector<Instruction *> &instructions);
	void assign(vector<Instruction *> &instructions, uint32_t address);
	~StringExpression();
};

class ListExpression: public Expression
{
private:
	vector<Expression *> _entries;
public:
	ListExpression();
	void addEntry(Expression *entry) { _entries.push_back(entry); }
	void compile(vector<Instruction *> &instructions);
	void assign(vector<Instruction *> &instructions, uint32_t address);
	~ListExpression();
};

class ListEntryExpression: public AssignableExpression
{
private:
	Expression *_e;
public:
	ListEntryExpression(string identifier, Expression *e);
	Expression *getExpression() { return _e; }
	void compile(vector<Instruction *> &instructions);
	~ListEntryExpression();
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
	AssignableExpression *_assignableExpression;
	Expression *_expression;
public:
	AssignmentExpression(AssignableExpression *a, Expression *e);
	void compile(vector<Instruction *> &instructions);
	~AssignmentExpression();
};

class CallExpression: public Expression
{
private:
	string _functionName;
	vector<Expression *> _parameters;
public:
	CallExpression(string functionName);
	void addParameter(Expression *parameter) { _parameters.push_back(parameter); }
	void compile(vector<Instruction *> &instructions);
	~CallExpression();
};

#endif

