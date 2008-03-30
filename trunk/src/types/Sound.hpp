#ifndef _SOUND_HPP_
#define _SOUND_HPP_

#include <stdint.h>
#include <string>
#include <vector>
using namespace std;

class Sound
{
private:
	uint32_t _id;
	vector<uint16_t> _syncTimes;
	uint32_t _sampleRate;
	vector<uint8_t> _dataBytes;

	void loadWAV(string fileName);
public:
	Sound(string dirName);
	uint32_t getID() { return _id; }
	uint8_t getNumberOfSyncTimes() { return _syncTimes.size(); }
	uint16_t getSyncTime(uint32_t index) { return _syncTimes[index]; }
	uint32_t getSampleRate() { return _sampleRate; }
	uint32_t getNumberOfDataBytes() { return _dataBytes.size(); }
	uint8_t getDataByte(uint32_t index) { return _dataBytes[index]; }
	~Sound();
};

#endif

