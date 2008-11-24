#include "AARY.hpp"
#include "util/IO.hpp"
#include "types/Game.hpp"

AARY::AARY(Game *game)
{
	for (int i = 0; i < game->getNumberOfArrays(); i++)
	{
		_varNumbers.push_back(game->getArray(i)->getVarNumber());
		_dimAs.push_back(game->getArray(i)->getDimA());
		_dimBs.push_back(game->getArray(i)->getDimB());
		_types.push_back(game->getArray(i)->getType());
	}
}

uint32_t AARY::getSize()
{
	uint32_t size = 0;
	size += 4 * sizeof(uint8_t); // identifier
	size += sizeof(uint32_t); // size
	size += _varNumbers.size() * sizeof(uint16_t); // varNumbers
	size += _dimAs.size() * sizeof(uint16_t); // dimAs
	size += _dimBs.size() * sizeof(uint16_t); // dimBs
	size += _types.size() * sizeof(uint16_t); // types
	size += sizeof(uint16_t); // 0
	return size;
}

void AARY::write(fstream &f)
{
	IO::writeString(f, "AARY");
	IO::writeU32BE(f, getSize());
	for (int i = 0; i < _varNumbers.size(); i++)
	{
		IO::writeU16LE(f, _varNumbers[i]);
		IO::writeU16LE(f, _dimAs[i]);
		IO::writeU16LE(f, _dimBs[i]);
		IO::writeU16LE(f, _types[i]);
	}
	IO::writeU16LE(f, 0);
}

AARY::~AARY()
{
}
