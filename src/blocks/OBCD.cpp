#include "OBCD.hpp"
#include "util/IO.hpp"
#include "types/Object.hpp"
#include "CDHD.hpp"
#include "OBNA.hpp"
#include "VERB.hpp"

OBCD::OBCD(Object *object)
{
	_cdhd = new CDHD(object);
	if (object->getFunction() != NULL)
		_verb = new VERB(object->getFunction());
	else
		_verb = NULL;
	_obna = new OBNA(object);
}

uint32_t OBCD::getSize()
{
	uint32_t size = 0;
	size += sizeof(uint32_t); // identifier
	size += sizeof(uint32_t); // size
	size += _cdhd->getSize(); // cdhd
	if (_verb != NULL)
		size += _verb->getSize(); // verb
	size += _obna->getSize(); // obna
	return size;
}

void OBCD::write(fstream &f)
{
	IO::writeString(f, "OBCD");
	IO::writeU32BE(f, getSize());
	_cdhd->write(f);
	if (_verb != NULL)
		_verb->write(f);
	_obna->write(f);
}

OBCD::~OBCD()
{
	delete _cdhd;
	if (_verb != NULL)
		delete _verb;
	delete _obna;
}

