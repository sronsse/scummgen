#ifndef _ZPxx_BLOCK_HPP_
#define _ZPxx_BLOCK_HPP_

#include <fstream>
#include <stdint.h>
#include <vector>
using namespace std;

class ZPxx
{
private:
	static const uint8_t STRIP_WIDTH;
	static const uint8_t MAX_BYTES;

	uint8_t _index;
	vector<vector<uint8_t> > _strips;
	vector<uint16_t> _offsets;
public:
	ZPxx(string filePath, uint8_t index);
	uint32_t getSize();
	void write(fstream &f);
	~ZPxx();
};

#endif

