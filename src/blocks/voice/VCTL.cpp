#include "VCTL.hpp"
#include <util/IO.hpp>
#include <types/Voice.hpp>

VCTL::VCTL(Voice *voice)
{
	for (int i = 0; i < voice->getNumberOfSyncTimes(); i++)
		_syncTimes.push_back(voice->getSyncTime(i));
}

uint32_t VCTL::getSize()
{
	uint32_t size = 0;
	size += 4 * sizeof(uint8_t); // identifier
	size += sizeof(uint32_t); // size
	size += _syncTimes.size() * sizeof(uint16_t); // syncTimes
	return size;
}

void VCTL::write(ofstream &f)
{
	IO::writeString(f, "VCTL");
	IO::writeU32BE(f, getSize());
	for (int i = 0; i < _syncTimes.size(); i++)
		IO::writeU16BE(f, _syncTimes[i]);
}

VCTL::~VCTL()
{
}

