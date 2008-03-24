#include "WRAP3.hpp"
#include "util/IO.hpp"
#include "types/Image.hpp"
#include "OFFS.hpp"
#include "WRAP.hpp"
#include "APAL.hpp"

const uint8_t WRAP3::STRIP_WIDTH = 8;
const uint8_t WRAP3::CID_UNCOMPRESSED = 0x01;
const uint8_t WRAP3::CID_FIRST_V_NO = 0x0E;
const uint8_t WRAP3::CID_FIRST_H_NO = 0x18;
const uint8_t WRAP3::CID_FIRST_V_YES = 0x22;
const uint8_t WRAP3::CID_FIRST_H_YES = 0x2C;
const uint8_t WRAP3::CID_SECOND_NO = 0x40;
const uint8_t WRAP3::CID_SECOND_YES = 0x54;
const uint8_t WRAP3::CID_SECOND_YES2 = 0x68;
const uint8_t WRAP3::CID_SECOND_NO2 = 0x7C;

WRAP3::WRAP3(Image *image)
{
	for (int i = 0; i < image->getWidth() / STRIP_WIDTH; i++)
	{
		vector<uint8_t> strip;
		strip.push_back(CID_UNCOMPRESSED);
		for (int j = 0; j < image->getHeight(); j++)
			for (int k = 0; k < STRIP_WIDTH; k++)
				strip.push_back(image->getPixel(i * STRIP_WIDTH + k, j));
		_strips.push_back(strip);
	}
	_offs = new OFFS(_strips);
}

uint32_t WRAP3::getSize()
{
	uint32_t size = 0;
	size += 4 * sizeof(uint8_t); // identifier
	size += sizeof(uint32_t); // size
	size += _offs->getSize(); // offs
	for (int i = 0; i < _strips.size(); i++) // strips
		size += _strips[i].size() * sizeof(uint8_t);
	return size;
}

void WRAP3::write(ofstream &f)
{
	IO::writeString(f, "WRAP");
	IO::writeU32BE(f, getSize());
	_offs->write(f);
	for (int i = 0; i < _strips.size(); i++)
		for (int j = 0; j < _strips[i].size(); j++)
			IO::writeU8(f, _strips[i][j]);
}

WRAP3::~WRAP3()
{
	delete _offs;
}

