#ifndef _WAVFILE_HPP_
#define _WAVFILE_HPP_

#include <string>
#include <vector>
using namespace std;

class WAVFile
{
private:
	uint32_t _sampleRate;
	vector<uint8_t> _dataBytes;
public:
	WAVFile();
	bool open(string fileName);
	uint32_t getSampleRate() { return _sampleRate; }
	uint32_t getNumberOfDataBytes() { return _dataBytes.size(); }
	uint8_t getDataByte(uint32_t index) { return _dataBytes[index]; }
	~WAVFile();
};

#endif
