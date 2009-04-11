#ifndef _VOICE_HPP_
#define _VOICE_HPP_

#include <stdint.h>
#include <string>
#include <vector>
using namespace std;

class Voice
{
private:
	static const string XML_FILE_NAME;

	uint32_t _id;
	string _name;
	string _description;
	string _wavePath;
	vector<uint16_t> _syncTimes;
public:
	Voice();
	void load(string dirPath);
	void save(string dirPath);
	uint32_t getID() { return _id; }
	void setID(uint32_t id) { _id = id; }
	string getName() { return _name; }
	string getDescription() { return _description; }
	string getWavePath() { return _wavePath; }	
	uint8_t getNumberOfSyncTimes() { return _syncTimes.size(); }
	uint16_t getSyncTime(uint8_t index) { return _syncTimes[index]; }
	~Voice();
};

#endif
