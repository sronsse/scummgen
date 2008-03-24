#include "IO.hpp"

string IO::readString(ifstream &f, uint8_t length)
{
	string s(length, 0); 
	for (int i = 0; i < length; i++)
		f.read(&s[i], 1);
	return s;
}

uint8_t IO::readU8(ifstream &f)
{
	uint8_t u8;
	f.read((char *)&u8, 1);
	return u8;
}

uint16_t IO::readU16LE(ifstream &f)
{
	uint16_t u16;
	f.read((char *)&u16, 2);
	return u16;
}

uint16_t IO::readU16BE(ifstream &f)
{
	uint16_t u16;
	uint8_t u8;
	f.read((char *)&u8, 1);
	u16 = u8 << 8;
	f.read((char *)&u8, 1);
	u16 |= u8;
	return u16;
}

uint32_t IO::readU32LE(ifstream &f)
{
	uint32_t u32;
	f.read((char *)&u32, 4);
	return u32;
}

uint32_t IO::readU32BE(ifstream &f)
{
	uint32_t u32;
	uint8_t u8;
	f.read((char *)&u8, 1);
	u32 = u8 << 24;
	f.read((char *)&u8, 1);
	u32 |= u8 << 16;
	f.read((char *)&u8, 1);
	u32 |= u8 << 8;
	f.read((char *)&u8, 1);
	u32 |= u8;
	return u32;
}

uint8_t IO::readBits(ifstream &f, uint8_t &byte, uint8_t &bitPos, uint8_t nBits)
{
	uint8_t result = 0;
	for (int i = 0; i < nBits; i++)
	{
		if (bitPos == 0)
			f.read((char *)&byte, 1);
		result |= ((byte >> bitPos++) & 0x01) << i;
		if (bitPos == 8)
			bitPos = 0;
	}
	return result;
}

void IO::writeString(ofstream &f, string s)
{
	for (int i = 0; i < s.length(); i++)
		f.write(&s[i], 1);
}

void IO::writeU8(ofstream &f, uint8_t data)
{
	f.write((char *)&data, 1);
}

void IO::writeU16LE(ofstream &f, uint16_t data)
{
	f.write((char *)&data, 2);
}

void IO::writeU16BE(ofstream &f, uint16_t data)
{
	uint8_t u8;
	u8 = data >> 8;
	f.write((char *)&u8, 1);
	u8 = data;
	f.write((char *)&u8, 1);
}

void IO::writeU32LE(ofstream &f, uint32_t data)
{
	f.write((char *)&data, 4);
}

void IO::writeU32BE(ofstream &f, uint32_t data)
{
	uint8_t u8;
	u8 = data >> 24;
	f.write((char *)&u8, 1);
	u8 = data >> 16;
	f.write((char *)&u8, 1);
	u8 = data >> 8;
	f.write((char *)&u8, 1);
	u8 = data;
	f.write((char *)&u8, 1);
}

string IO::getStringFromIndex(uint32_t index, uint8_t nDigits)
{
	char s[nDigits + 1];
	uint32_t v = 1;
	for (int i = nDigits - 1; i >= 0; i--)
	{
		s[i] = (char)((index % (v * 10)) / v + (int)'0');
		v *= 10;
	}
	s[nDigits] = 0;
	return s;
}

