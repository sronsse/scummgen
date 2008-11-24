#ifndef _VOC_BLOCK_HPP_
#define _VOC_BLOCK_HPP_

#include <fstream>
#include <stdint.h>
#include <vector>
using namespace std;

class Voice;

class VOC
{
private:
	static const int HEADER_SIZE;
	static const int VERSION;
	static const int MAGIC_NUMBER;
	static const int TERMINATOR_BLOCK_ID;
	static const int SOUND_DATA_BLOCK_ID;
	static const int PCM_CODEC_ID;

	uint8_t _freqDivisor;
	vector<uint8_t> _dataBytes;
public:
	VOC(Voice *voice);
	uint32_t getSize();
	void write(fstream &f);
	~VOC();
};

#endif

