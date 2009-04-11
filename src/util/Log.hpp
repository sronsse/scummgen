#ifndef _LOG_HPP_
#define _LOG_HPP_

#include <fstream>
#include <stdint.h>
#include <string>
using namespace std;

typedef enum
{
	LOG_INFO,
	LOG_WARNING,
	LOG_ERROR
} LogType;

class Log
{
private:
	static const uint8_t INDENT_WIDTH;

	static uint8_t _indent;
	static ofstream _output;
public:
	static void reset();
	static void indent() { _indent++; }
	static void unIndent() { _indent--; }
	static void write(LogType type, const char *s, ...);
	static void close();
};

#endif
