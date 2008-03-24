#include "DSOU.hpp"
#include "util/IO.hpp"
#include "util/Log.hpp"

DSOU::DSOU(ifstream &f)
{
	_size = IO::readU32BE(f);
	Log::getInstance().write("size: %d\n", _size);

	Log::getInstance().indent();

	_nItems = IO::readU32LE(f);
	Log::getInstance().write("nItems: %d\n", _nItems);

	for (int i = 0; i < _nItems; i++)
	{
		uint8_t id = IO::readU8(f);
		_ids.push_back(id);
		Log::getInstance().write("id: %d\n", id);
	}

	for (int i = 0; i < _nItems; i++)
	{
		uint32_t offset = IO::readU32LE(f);
		_offsets.push_back(offset);
		Log::getInstance().write("offset: %x\n", offset);
	}

	Log::getInstance().unIndent();
}

uint32_t DSOU::getSize()
{
	uint32_t size = 0;
	size += 4 * sizeof(uint8_t); // identifier
	size += sizeof(uint32_t); // size
	size += sizeof(uint32_t); // nItems
	size += _nItems * sizeof(uint8_t); // ids
	size += _nItems * sizeof(uint32_t); // offsets
	return size;
}

void DSOU::write(ofstream &f)
{
	IO::writeString(f, "DSOU");
	IO::writeU32BE(f, getSize());
	IO::writeU32LE(f, _nItems);
	for (int i = 0; i < _nItems; i++)
		IO::writeU8(f, _ids[i]);
	for (int i = 0; i < _nItems; i++)
		IO::writeU32LE(f, _offsets[i]);
}

DSOU::~DSOU()
{
}

