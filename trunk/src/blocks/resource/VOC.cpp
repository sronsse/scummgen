#include "VOC.hpp"
#include <util/IO.hpp>
#include <types/Sound.hpp>

const uint8_t VOC::EOF_CHAR = 0x1A;
const uint16_t VOC::HEADER_SIZE = 26;
const uint16_t VOC::VERSION = 0x10A;
const uint16_t VOC::MAGIC_NUMBER = 0x1234;
const uint8_t VOC::TERMINATOR_BLOCK_ID = 0;
const uint8_t VOC::SOUND_DATA_BLOCK_ID = 1;
const uint8_t VOC::PCM_CODEC_ID = 0;

VOC::VOC(Sound *sound)
{
	_freqDivisor = 256 - 1000000 / sound->getSampleRate();
	for (int i = 0; i < sound->getNumberOfDataBytes(); i++)
		_dataBytes.push_back(sound->getDataByte(i));
}

uint32_t VOC::getSize()
{
	uint32_t size = 0;
	size += 19 * sizeof(uint8_t); // identifier
	size += sizeof(uint8_t); // EOF_CHAR
	size += sizeof(uint16_t); // HEADER_SIZE
	size += sizeof(uint16_t); // VERSION
	size += sizeof(uint16_t); // ~VERSION + MAGIC_NUMBER
	size += sizeof(uint8_t); // SOUND_DATA_BLOCK_ID
	size += 3 * sizeof(uint8_t); // 2 + nDataBytes
	size += sizeof(uint8_t); // freqDivisor
	size += sizeof(uint8_t); // PCM_CODEC_ID
	size += _dataBytes.size() * sizeof(uint8_t); // dataBytes
	size += sizeof(uint8_t); // TERMINATOR_BLOCK_ID
	return size;
}

void VOC::write(ofstream &f)
{
	IO::writeString(f, "Creative Voice File");
	IO::writeU8(f, EOF_CHAR);
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

