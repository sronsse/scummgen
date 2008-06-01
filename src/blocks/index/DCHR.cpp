#include "DCHR.hpp"
#include "util/IO.hpp"
#include "types/Game.hpp"
#include "types/Charset.hpp"
#include "blocks/resource/LFLF.hpp"

DCHR::DCHR(Game *game, LFLF *lflf)
{
	_ids.push_back(0);
	_offsets.push_back(0);

	for (int i = 0; i < game->getNumberOfCharsets(); i++)
	{
		_ids.push_back(game->getCharset(i)->getID());
		_offsets.push_back(lflf->getCHAROffset(i));
	}

	_nItems = _ids.size();
}

uint32_t DCHR::getSize()
{
	uint32_t size = 0;
	size += 4 * sizeof(uint8_t); // identifier
	size += sizeof(uint32_t); // size
	size += sizeof(uint16_t); // nItems
	size += _ids.size() * sizeof(uint8_t); // ids
	size += _offsets.size() * sizeof(uint32_t); // offsets
	return size;
}

void DCHR::write(ofstream &f)
{
	IO::writeString(f, "DCHR");
	IO::writeU32BE(f, getSize());
	IO::writeU16LE(f, _nItems);
	for (int i = 0; i < _nItems; i++)
		IO::writeU8(f, _ids[i]);
	for (int i = 0; i < _nItems; i++)
		IO::writeU32LE(f, _offsets[i]);
}

DCHR::~DCHR()
{
}

