#include "GMD.hpp"
#include "util/IO.hpp"
#include "util/MIDFile.hpp"
#include "types/Midi.hpp"

GMD::GMD(Midi *midi)
{
	MIDFile midFile;
	midFile.open(midi->getMidiPath());
	for (int i = 0; i < midFile.getNumberOfDataBytes(); i++)
		_dataBytes.push_back(midFile.getDataByte(i));
}

uint32_t GMD::getSize()
{
	uint32_t size = 0;
	size += 4 * sizeof(uint8_t); // identifier
	size += sizeof(uint32_t); // size
	size += _dataBytes.size(); // data
	return size;
}

void GMD::write(fstream &f)
{
	IO::writeString(f, "GMD ");
	IO::writeU32BE(f, getSize());
	for (int i = 0; i < _dataBytes.size(); i++)
		IO::writeU8(f, _dataBytes[i]);
}

GMD::~GMD()
{
}
