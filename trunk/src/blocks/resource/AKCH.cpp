#include "AKCH.hpp"
#include "util/IO.hpp"
#include "types/Costume.hpp"

const uint8_t AKCH::MODE_SINGLE_FRAME = 1;
const uint8_t AKCH::MODE_STOP_LIMB = 4;
const uint8_t AKCH::MODE_START_LIMB = 5;

AKCH::AKCH(Costume *costume)
{
	_offsets.push_back(costume->getNumberOfAnims() * sizeof(uint16_t));
	for (int i = 0; i < costume->getNumberOfAnims(); i++)
	{
		uint16_t offset = sizeof(uint16_t); // limbMask
		_limbMasks.push_back(costume->getAnim(i)->getMask());
		vector<uint8_t> modes;
		vector<uint16_t> starts;
		vector<uint16_t> lengths;
		for (int j = 0; j < costume->getAnim(i)->getNumberOfLimbs(); j++)
		{
			offset += sizeof(uint8_t); // mode
			modes.push_back(costume->getAnim(i)->getLimb(j)->getMode());
			if (modes[j] != MODE_SINGLE_FRAME && modes[j] != MODE_STOP_LIMB && modes[j] != MODE_START_LIMB)
			{
				offset += 2 * sizeof(uint16_t); // start and length
				starts.push_back(costume->getAnim(i)->getLimb(j)->getStart());
				lengths.push_back(costume->getAnim(i)->getLimb(j)->getLength());
			}
		}
		if (i != costume->getNumberOfAnims() - 1)
			_offsets.push_back(_offsets[_offsets.size() - 1] + offset);
		_modes.push_back(modes);
		_starts.push_back(starts);
		_lengths.push_back(lengths);
	}
}

uint32_t AKCH::getSize()
{
	uint32_t size = 0;
	size += 4 * sizeof(uint8_t); // identifier
	size += sizeof(uint32_t); // size
	size += _offsets.size() * sizeof(uint16_t); // offsets
	size += _limbMasks.size() * sizeof(uint16_t); // limbMasks
	for (int i = 0; i < _modes.size(); i++) // modes
		size += _modes[i].size() * sizeof(uint8_t);
	for (int i = 0; i < _starts.size(); i++) // starts
		size += _starts[i].size() * sizeof(uint16_t);
	for (int i = 0; i < _lengths.size(); i++) // lengths
		size += _lengths[i].size() * sizeof(uint16_t);
	return size;
}

void AKCH::write(ofstream &f)
{
	IO::writeString(f, "AKCH");
	IO::writeU32BE(f, getSize());
	for (int i = 0; i < _offsets.size(); i++)
		IO::writeU16LE(f, _offsets[i]);
	for (int i = 0; i < _limbMasks.size(); i++)
	{
		IO::writeU16LE(f, _limbMasks[i]);
		for (int j = 0; j < _modes[i].size(); j++)
		{
			IO::writeU8(f, _modes[i][j]);
			if (_modes[i][j] != MODE_SINGLE_FRAME && _modes[i][j] != MODE_STOP_LIMB && _modes[i][j] != MODE_START_LIMB)
			{
				IO::writeU16LE(f, _starts[i][j]);
				IO::writeU16LE(f, _lengths[i][j]);
			}
		}
	}
}

AKCH::~AKCH()
{
}

