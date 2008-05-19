#ifndef _CHAR_BLOCK_HPP_
#define _CHAR_BLOCK_HPP_

#include <fstream>
#include <stdint.h>
#include <vector>
using namespace std;

class Char;
class Charset;

class CHAR
{
private:
	static const int N_COLORS;
	static const int MAGIC_NUMBER_SIZE;
	static const int MAGIC_NUMBER_UNKNOWN;

	vector<uint8_t> _palette;
	uint8_t _bpp;
	uint8_t _fontHeight;
	uint16_t _nChars;
	vector<uint32_t> _offsets;
	vector<uint8_t> _widths;
	vector<uint8_t> _heights;
	vector<int8_t> _xOffsets;
	vector<int8_t> _yOffsets;
	vector<vector<uint8_t> > _dataBytes;

	void getDataBytes(Charset *charset, Char *chr, vector<uint8_t> &dataBytes);
public:
	CHAR(Charset *charset);
	uint32_t getSize();
	void write(ofstream &f);
	~CHAR();
};

#endif

