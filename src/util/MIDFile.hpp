#ifndef _MIDFILE_HPP_
#define _MIDFILE_HPP_

#include <string>
#include <vector>
using namespace std;

class MIDFile
{
private:
	vector<uint8_t> _dataBytes;
public:
	MIDFile();
	bool open(string fileName);
	uint32_t getNumberOfDataBytes() { return _dataBytes.size(); }
	uint8_t getDataByte(uint32_t index) { return _dataBytes[index]; }
	~MIDFile();
};

#endif
