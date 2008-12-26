#ifndef _VOICE_HPP_
#define _VOICE_HPP_

#include <map>
#include <stdint.h>
#include <string>
#include <vector>
using namespace std;

class Voice
{
private:
	string _name;
	vector<uint16_t> _syncTimes;
	uint32_t _sampleRate;
	vector<uint8_t> _dataBytes;

	void loadWAV(string fileName);
public:
	Voice(string dirName);
	string getName() { return _name; }
	uint8_t getNumberOfSyncTimes() { return _syncTimes.size(); }
	uint16_t getSyncTime(uint8_t index) { return _syncTimes[index]; }
	uint32_t getSampleRate() { return _sampleRate; }
	uint32_t getNumberOfDataBytes() { return _dataBytes.size(); }
	uint8_t getDataByte(uint32_t index) { return _dataBytes[index]; }
	~Voice();
};

#endif
