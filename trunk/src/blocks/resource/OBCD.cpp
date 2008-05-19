#include "OBCD.hpp"
#include "util/IO.hpp"
#include "types/Object.hpp"
#include "CDHD.hpp"
#include "OBNA.hpp"
#include "VERB.hpp"

OBCD::OBCD(Object *object)
{
	_cdhd = new CDHD(object);
	_obna = new OBNA(object);
	_verb = new VERB(object->getScript());
}

uint32_t OBCD::getSize()
{
	uint32_t size = 0;
	size += sizeof(uint32_t); // identifier
	size += sizeof(uint32_t); // size
	size += _cdhd->getSize(); // cdhd
	size += _obna->getSize(); // obna
	size += _verb->getSize(); // verb
	return size;
}

void OBCD::write(ofstream &f)
{
	IO::writeString(f, "OBCD");
	IO::writeU32BE(f, getSize());
	_cdhd->write(f);
	_obna->write(f);
	_verb->write(f);
}

OBCD::~OBCD()
{
	delete _cdhd;
	delete _obna;
	delete _verb;
}

