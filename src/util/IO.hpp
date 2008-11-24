#ifndef _IO_HPP_
#define _IO_HPP_

#include <stdint.h>
#include <fstream>
#include <string>
using namespace std;

class IO
{
private:
	static uint8_t _key;
public:
	static void setKey(uint8_t key) { _key = key; }
	static string readString(fstream &f, uint8_t length);
	static uint8_t readU8(fstream &f);
	static uint16_t readU16LE(fstream &f);
	static uint16_t readU16BE(fstream &f);
	static uint32_t readU32LE(fstream &f);
	static uint32_t readU32BE(fstream &f);
	static uint8_t readBits(fstream &f, uint8_t &byte, uint8_t &bitPos, uint8_t nBits);
	static void writeString(fstream &f, string s);
	static void writeU8(fstream &f, uint8_t data);
	static void writeU16LE(fstream &f, uint16_t data);
	static void writeU16BE(fstream &f, uint16_t data);
	static void writeU24LE(fstream &f, uint32_t data);
	static void writeU24BE(fstream &f, uint32_t data);
	static void writeU32LE(fstream &f, uint32_t data);
	static void writeU32BE(fstream &f, uint32_t data);
	static string getStringFromIndex(uint32_t index, uint8_t nDigits);
};

#endif

