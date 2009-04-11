#include "Log.hpp"
#include <iostream>
#include <stdarg.h>
#include <stdlib.h>
using namespace std;

const uint8_t Log::INDENT_WIDTH = 4;

uint8_t Log::_indent = 0;
ofstream Log::_output;

void Log::reset()
{
	if (_output.is_open())
		_output.close();
	_output.open("log.txt", ios::out);
}

void Log::write(LogType type, const char *s, ...)
{
	char buf[1024];
	va_list va;

	va_start(va, s);
	vsnprintf(buf, 1024, s, va);
	va_end(va);

	// Spaces for indentation
	for (int i = 0; i < _indent * INDENT_WIDTH; i++)
		_output << ' ';

	switch (type)
	{
		case LOG_INFO:
			_output << buf << flush;
			break;
		case LOG_WARNING:
			_output << "WARNING : " << buf << flush;
			break;
		case LOG_ERROR:
			_output << "ERROR : " << buf << flush;
			cout << "ScummGEN encountered an error - see log for more details.\n";
			throw 1;
	}
}

void Log::close()
{
	if (_output.is_open())
		_output.close();
}
