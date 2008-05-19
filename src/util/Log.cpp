#include "Log.hpp"
#include <stdarg.h>

const uint8_t Log::INDENT_WIDTH = 4;

Log::Log():
_active(false),
_indent(0)
{
}

Log &Log::getInstance()
{
	static Log instance;
	return instance;
}

void Log::setActive(bool active)
{
	_active = active;
	if (active && !_output.is_open())
		_output.open("log.txt", ios::out);
}

void Log::write(const char *s, ...)
{
	if (!_active)
		return;

	char buf[1024];
	va_list va;

	va_start(va, s);
	vsnprintf(buf, 1024, s, va);
	va_end(va);

	for (int i = 0; i < _indent * INDENT_WIDTH; i++)
		_output << ' ';
	_output << buf << flush;
}

Log::~Log()
{
	if (_output.is_open())
		_output.close();
}

