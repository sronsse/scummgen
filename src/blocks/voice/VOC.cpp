#include "VOC.hpp"
#include <util/IO.hpp>
#include <types/Voice.hpp>

const int VOC::HEADER_SIZE = 26;
const int VOC::VERSION = 0x10A;
const int VOC::MAGIC_NUMBER = 0x1234;
const int VOC::TERMINATOR_BLOCK_ID = 0;
const int VOC::SOUND_DATA_BLOCK_ID = 1;
const int VOC::PCM_CODEC_ID = 0;

VOC::VOC(Voice *voice)
{
	_freqDivisor = 256 - 1000000 / voice->getSampleRate();
	for (int i = 0; i < voice->getNumberOfDataBytes(); i++)
		_dataBytes.push_back(voice->getDataByte(i));
}

uint32_t VOC::getSize()
{
	uint32_t size = 0;
	size += 19 * sizeof(uint8_t); // identifier
	size += sizeof(uint8_t); // EOF
	size += sizeof(uint16_t); // HEADER_SIZE
	size += sizeof(uint16_t); // VERSION
	size += sizeof(uint16_t); // ~VERSION + MAGIC_NUMBER
	size += sizeof(uint8_t); // SOUND_DATA_BLOCK_ID
	size += 3 * sizeof(uint8_t); // 2 + _nDataBytes
	size += sizeof(uint8_t); // freqDivisor
	size += sizeof(uint8_t); // PCM_CODEC_ID
	size += _dataBytes.size() * sizeof(uint8_t); // dataBytes
	size += sizeof(uint8_t); // TERMINATOR_BLOCK_ID
	return size;
}

void VOC::write(ofstream &f)
{
	// First, we write the header, beginning with the identifier
	IO::writeString(f, "Creative Voice File");
	IO::writeU8(f, 0x1A);
	IO::writeU16LE(f, HEADER_SIZE);
	IO::writeU16LE(f, VERSION);
	IO::writeU16LE(f, ~VERSION + MAGIC_NUMBER);
	IO::writeU8(f, SOUND_DATA_BLOCK_ID);
	IO::writeU24LE(f, 2 + _dataBytes.size());
	IO::writeU8(f, _freqDivisor);
	IO::writeU8(f, PCM_CODEC_ID);
	for (int i = 0; i < _dataBytes.size(); i++)
		IO::writeU8(f, _dataBytes[i]);
	IO::writeU8(f, TERMINATOR_BLOCK_ID);
}

VOC::~VOC()
{
}

