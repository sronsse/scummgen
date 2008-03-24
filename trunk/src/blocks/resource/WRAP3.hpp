#ifndef _WRAP3_BLOCK_HPP_
#define _WRAP3_BLOCK_HPP_

#include <fstream>
#include <stdint.h>
#include <vector>
using namespace std;

class Image;
class OFFS;
class WRAP;

class WRAP3
{
private:
	static const uint8_t STRIP_WIDTH;
	static const uint8_t CID_UNCOMPRESSED;
	static const uint8_t CID_FIRST_V_NO;
	static const uint8_t CID_FIRST_H_NO;
	static const uint8_t CID_FIRST_V_YES;
	static const uint8_t CID_FIRST_H_YES;
	static const uint8_t CID_SECOND_NO;
	static const uint8_t CID_SECOND_YES;
	static const uint8_t CID_SECOND_YES2;
	static const uint8_t CID_SECOND_NO2;

	OFFS *_offs;
	vector<vector<uint8_t> > _strips;
public:
	WRAP3(Image *image);
	uint32_t getSize();
	void write(ofstream &f);
	~WRAP3();
};

#endif

