#ifndef _VCTL_BLOCK_HPP_
#define _VCTL_BLOCK_HPP_

#include <fstream>
#include <stdint.h>
#include <vector>
using namespace std;

class Voice;

class VCTL
{
private:
	vector<uint16_t> _syncTimes;
public:
	VCTL(Voice *voice);
	uint32_t getSize();
	void write(fstream &f);
	~VCTL();
};

#endif

