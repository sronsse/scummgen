#include "DSCR.hpp"
#include "util/IO.hpp"
#include "LFLF.hpp"

DSCR::DSCR(Game *game, LFLF *lflf)
{
	_ids.push_back(0);
	_offsets.push_back(0);

	for (int i = 0; i < lflf->getNumberOfSCRPOffsets(); i++)
	{
		_ids.push_back(1); // Global scripts are all in room n°1
		_offsets.push_back(lflf->getSCRPOffset(i));
	}

	_nItems = _ids.size();
}

uint32_t DSCR::getSize()
{
	uint32_t size = 0;
	size += 4 * sizeof(uint8_t); // identifier
	size += sizeof(uint32_t); // size
	size += sizeof(uint16_t); // nItems
	size += _ids.size() * sizeof(uint8_t); // ids
	size += _offsets.size() * sizeof(uint32_t); // offsets
	return size;
}

void DSCR::write(fstream &f)
{
	IO::writeString(f, "DSCR");
	IO::writeU32BE(f, getSize());
	IO::writeU16LE(f, _nItems);
	for (int i = 0; i < _nItems; i++)
		IO::writeU8(f, _ids[i]);
	for (int i = 0; i < _nItems; i++)
		IO::writeU32LE(f, _offsets[i]);
}

DSCR::~DSCR()
{
}

