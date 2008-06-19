#include "OBIM.hpp"
#include "util/IO.hpp"
#include "types/Object.hpp"
#include "IMHD.hpp"
#include "IMxx.hpp"

OBIM::OBIM(Object *object)
{
	_imhd = new IMHD(object);
	for (int i = 0; i < object->getNumberOfImages(); i++)
		_imxxs.push_back(new IMxx(object->getImage(i), i + 1));
}

uint32_t OBIM::getSize()
{
	uint32_t size = 0;
	size += 4 * sizeof(uint8_t); // identifier
	size += sizeof(uint32_t); // size
	size += _imhd->getSize(); // imhd
	for (int i = 0; i < _imxxs.size(); i++) // imxxs
		size += _imxxs[i]->getSize();
	return size;
}

void OBIM::write(fstream &f)
{
	IO::writeString(f, "OBIM");
	IO::writeU32BE(f, getSize());
	_imhd->write(f);
	for (int i = 0; i < _imxxs.size(); i++)
		_imxxs[i]->write(f);
}

OBIM::~OBIM()
{
	delete _imhd;
	for (int i = 0; i < _imxxs.size(); i++)
		delete _imxxs[i];
}

