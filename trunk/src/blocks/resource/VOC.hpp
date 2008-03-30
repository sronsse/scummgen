#ifndef _VOC_BLOCK_HPP_
#define _VOC_BLOCK_HPP_

#include <fstream>
#include <stdint.h>
#include <vector>
using namespace std;

class Sound;

class VOC
{
private:
	static const uint8_t EOF_CHAR;
	static const uint16_t HEADER_SIZE;
	static const uint16_t VERSION;
	static const uint16_t MAGIC_NUMBER;
	static const uint8_t TERMINATOR_BLOCK_ID;
	static const uint8_t SOUND_DATA_BLOCK_ID;
	static const uint8_t PCM_CODEC_ID;

	uint8_t _freqDivisor;
	vector<uint8_t> _dataBytes;
public:
	VOC(Sound *sound);
	uint32_t getSize();
	void write(ofstream &f);
	~VOC();
};

#endif

