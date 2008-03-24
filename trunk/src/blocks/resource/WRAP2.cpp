#include "WRAP2.hpp"
#include "util/IO.hpp"
#include "types/Image.hpp"
#include "types/Object.hpp"
#include "OFFS.hpp"
#include "SMAP.hpp"
#include "BOMP.hpp"

WRAP2::WRAP2(Image *image)
{
	if (!image->isBomp())
		_smaps.push_back(new SMAP(image));
	else
		_bomps.push_back(new BOMP(image));
	_offs = new OFFS(_smaps, _bomps);
}

WRAP2::WRAP2(Object *object)
{
	for (int i = 0; i < object->getNumberOfImages(); i++)
	{
		if (!object->getImage(i)->isBomp())
			_smaps.push_back(new SMAP(object->getImage(i)));
		else
			_bomps.push_back(new BOMP(object->getImage(i)));
	}
	_offs = new OFFS(_smaps, _bomps);
}

uint32_t WRAP2::getSize()
{
	uint32_t size = 0;
	size += 4 * sizeof(uint8_t); // identifier
	size += sizeof(uint32_t); // size
	size += _offs->getSize(); // offs
	for (int i = 0; i < _smaps.size(); i++) // smaps
		size += _smaps[i]->getSize();
	for (int i = 0; i < _bomps.size(); i++) // bomps
		size += _bomps[i]->getSize();
	return size;
}

void WRAP2::write(ofstream &f)
{
	IO::writeString(f, "WRAP");
	IO::writeU32BE(f, getSize());
	_offs->write(f);
	for (int i = 0; i < _smaps.size(); i++)
		_smaps[i]->write(f);
	for (int i = 0; i < _bomps.size(); i++)
		_bomps[i]->write(f);
}

WRAP2::~WRAP2()
{
	delete _offs;
	for (int i = 0; i < _smaps.size(); i++)
		delete _smaps[i];
	for (int i = 0; i < _bomps.size(); i++)
		delete _bomps[i];
}

