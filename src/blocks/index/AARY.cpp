#include "AARY.hpp"
#include "util/IO.hpp"
#include "util/Log.hpp"

AARY::AARY(ifstream &f)
{
	_size = IO::readU32BE(f);
	Log::getInstance().write("size: %d\n", _size);

	Log::getInstance().indent();

	while (true)
	{
		uint32_t arrayID = IO::readU32LE(f);
		if (arrayID == 0)
			break;
		_arrayIDs.push_back(arrayID);
		Log::getInstance().write("arrayID: %d\n", arrayID);

		uint32_t arrayDimA = IO::readU32LE(f);
		_arrayDimAs.push_back(arrayDimA);
		Log::getInstance().write("arrayDimA: %d\n", arrayDimA);

		uint32_t arrayDimB = IO::readU32LE(f);
		_arrayDimBs.push_back(arrayDimB);
		Log::getInstance().write("arrayDimB: %d\n", arrayDimB);
	}

	Log::getInstance().unIndent();
}

uint32_t AARY::getSize()
{
	uint32_t size = 0;
	size += 4 * sizeof(uint8_t); // identifier
	size += sizeof(uint32_t); // size
	size += _arrayIDs.size() * sizeof(uint32_t); // arrayIDs
	size += _arrayDimAs.size() * sizeof(uint32_t); // arrayDimAs
	size += _arrayDimBs.size() * sizeof(uint32_t); // arrayDimBs
	size += sizeof(uint32_t); // 0
	return size;
}

void AARY::write(ofstream &f)
{
	IO::writeString(f, "AARY");
	IO::writeU32BE(f, getSize());
	for (int i = 0; i < _arrayIDs.size(); i++)
	{
		IO::writeU32LE(f, _arrayIDs[i]);
		IO::writeU32LE(f, _arrayDimAs[i]);
		IO::writeU32LE(f, _arrayDimBs[i]);
	}
	IO::writeU32LE(f, 0);
}

AARY::~AARY()
{
}

