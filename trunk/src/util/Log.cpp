#include "Log.hpp"
#include <iostream>
#include <stdarg.h>
#include <stdlib.h>
using namespace std;

const uint8_t Log::INDENT_WIDTH = 4;

Log &Log::getInstance()
{
	static Log instance;
	return instance;
}

Log::Log()
{
	_active = false;
	_indent = 0;
}

void Log::setActive(bool active)
{
	_active = active;
	if (active && !_output.is_open())
		_output.open("log.txt", ios::out);
}

void Log::write(LogType type, const char *s, ...)
{
	if (!_active)
		return;

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

Log::~Log()
{
	if (_output.is_open())
		_output.close();
}

