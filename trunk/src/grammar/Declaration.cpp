#include "Declaration.hpp"

Declaration::Declaration(DeclarationType type, string name)
{
	_type = type;
	_name = name;
	_fixedAddress = false;
}

Declaration::Declaration(DeclarationType type, string name, uint16_t value)
{
	_type = type;
	_name = name;
	_value = value;
	_fixedAddress = (type == DECLARATION_VAR);
}

Declaration::~Declaration()
{
}

