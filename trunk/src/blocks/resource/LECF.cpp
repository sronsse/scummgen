#include "LECF.hpp"
#include "types/Game.hpp"
#include "util/IO.hpp"
#include "LOFF.hpp"
#include "LFLF.hpp"

LECF::LECF(Game *game)
{
	for (int i = 0; i < game->getNumberOfRooms(); i++)
		_lflfs.push_back(new LFLF(game, i));
	_loff = new LOFF(game, _lflfs);
}

uint32_t LECF::getSize()
{
	uint32_t size = 0;
	size += 4 * sizeof(uint8_t); // identifier
	size += sizeof(uint32_t); // size
	size += _loff->getSize(); // loff
	for (int i = 0; i < _lflfs.size(); i++) // lflfs
		size += _lflfs[i]->getSize();
	return size;
}

void LECF::write(ofstream &f)
{
	IO::writeString(f, "LECF");
	IO::writeU32BE(f, getSize());
	_loff->write(f);
	for (int i = 0; i < _lflfs.size(); i++) // lflfs
		_lflfs[i]->write(f);
}

LECF::~LECF()
{
	delete _loff;
	for (int i = 0; i < _lflfs.size(); i++)
		delete _lflfs[i];
}

