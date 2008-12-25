#include "IO.hpp"

uint8_t IO::_key;

string IO::readString(fstream &f, uint8_t length)
{
	string s(length, 0); 
	for (int i = 0; i < length; i++)
		f.read(&s[i], 1);
	return s;
}

uint8_t IO::readU8(fstream &f)
{
	uint8_t u8;
	f.read((char *)&u8, 1);
	return u8;
}

uint16_t IO::readU16LE(fstream &f)
{
	uint16_t u16;
	f.read((char *)&u16, 2);
	return u16;
}

uint16_t IO::readU16BE(fstream &f)
{
	uint16_t u16;
	uint8_t u8;
	f.read((char *)&u8, 1);
	u16 = u8 << 8;
	f.read((char *)&u8, 1);
	u16 |= u8;
	return u16;
}

uint32_t IO::readU32LE(fstream &f)
{
	uint32_t u32;
	f.read((char *)&u32, 4);
	return u32;
}

uint32_t IO::readU32BE(fstream &f)
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

uint32_t IO::readBits(fstream &f, uint8_t &byte, uint8_t &bitPos, uint8_t nBits)
{
	uint32_t result = 0;
	for (int i = nBits - 1; i >= 0; i--)
	{
		if (bitPos == 0)
			f.read((char *)&byte, 1);
		result |= ((byte >> (7 - bitPos)) & 0x01) << i;
		if (++bitPos == 8)
			bitPos = 0;
	}
	return result;
}

void IO::writeString(fstream &f, string s)
{
	uint8_t data;
	for (int i = 0; i < s.length(); i++)
	{
		data = s[i] ^ _key;
		f.write((char *)&data, 1);
	}
}

void IO::writeU8(fstream &f, uint8_t data)
{
	data ^= _key;
	f.write((char *)&data, 1);
}

void IO::writeU16LE(fstream &f, uint16_t data)
{
	data ^= (_key << 8) | _key;
	f.write((char *)&data, 2);
}

void IO::writeU16BE(fstream &f, uint16_t data)
{
	uint8_t u8;
	u8 = (data >> 8) ^ _key;
	f.write((char *)&u8, 1);
	u8 = data ^ _key;
	f.write((char *)&u8, 1);
}

void IO::writeU24LE(fstream &f, uint32_t data)
{
	uint8_t u8;
	u8 = data ^ _key;
	f.write((char *)&u8, 1);
	u8 = (data >> 8) ^ _key;
	f.write((char *)&u8, 1);
	u8 = (data >> 16) ^ _key;
	f.write((char *)&u8, 1);
}

void IO::writeU24BE(fstream &f, uint32_t data)
{
	uint8_t u8;
	u8 = (data >> 16) ^ _key;
	f.write((char *)&u8, 1);
	u8 = (data >> 8) ^ _key;
	f.write((char *)&u8, 1);
	u8 = data ^ _key;
	f.write((char *)&u8, 1);
}

void IO::writeU32LE(fstream &f, uint32_t data)
{
	data ^= (_key << 24) | (_key << 16) | (_key << 8) | _key;
	f.write((char *)&data, 4);
}

void IO::writeU32BE(fstream &f, uint32_t data)
{
	uint8_t u8;
	u8 = (data >> 24) ^ _key;
	f.write((char *)&u8, 1);
	u8 = (data >> 16) ^ _key;
	f.write((char *)&u8, 1);
	u8 = (data >> 8) ^ _key;
	f.write((char *)&u8, 1);
	u8 = data ^ _key;
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

