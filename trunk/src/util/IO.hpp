#ifndef _IO_HPP_
#define _IO_HPP_

#include <stdint.h>
#include <fstream>
#include <string>
using namespace std;

class IO
{
public:
	static string readString(ifstream &f, uint8_t length);
	static uint8_t readU8(ifstream &f);
	static uint16_t readU16LE(ifstream &f);
	static uint16_t readU16BE(ifstream &f);
	static uint32_t readU32LE(ifstream &f);
	static uint32_t readU32BE(ifstream &f);
	static uint8_t readBits(ifstream &f, uint8_t &byte, uint8_t &bitPos, uint8_t nBits);

	static void writeString(ofstream &f, string s);
	static void writeU8(ofstream &f, uint8_t data);
	static void writeU16LE(ofstream &f, uint16_t data);
	static void writeU16BE(ofstream &f, uint16_t data);
	static void writeU24LE(ofstream &f, uint32_t data);
	static void writeU24BE(ofstream &f, uint32_t data);
	static void writeU32LE(ofstream &f, uint32_t data);
	static void writeU32BE(ofstream &f, uint32_t data);
	static string getStringFromIndex(uint32_t index, uint8_t nDigits);
};

#endif

