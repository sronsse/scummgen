#ifndef _DECLARATION_HPP_
#define _DECLARATION_HPP_

#include <stdint.h>
#include <string>
using namespace std;

typedef enum
{
	DECLARATION_CONST,
	DECLARATION_VAR
} DeclarationType;

class Declaration
{
private:
	DeclarationType _type;
	string _name;
	uint16_t _value;
	bool _fixedAddress;
public:
	Declaration(DeclarationType type, string name);
	Declaration(DeclarationType type, string name, uint16_t value);
	DeclarationType getType() { return _type; }
	string getName() { return _name; }
	uint16_t getValue() { return _value; }
	bool hasFixedAddress() { return _fixedAddress; }
	~Declaration();
};

#endif

