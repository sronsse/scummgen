#ifndef _VOICE_HPP_
#define _VOICE_HPP_

#include <stdint.h>
#include <string>
#include <vector>
using namespace std;

class Voice
{
private:
	string _name;
	string _wavePath;
	vector<uint16_t> _syncTimes;
public:
	Voice();
	void load(string dirPath);
	string getName() { return _name; }
	string getWavePath() { return _wavePath; }	
	uint8_t getNumberOfSyncTimes() { return _syncTimes.size(); }
	uint16_t getSyncTime(uint8_t index) { return _syncTimes[index]; }
	~Voice();
};

#endif
