#include "AKSQ.hpp"
#include "util/IO.hpp"
#include "types/Costume.hpp"

AKSQ::AKSQ(Costume *costume)
{
	for (int i = 0; i < costume->getNumberOfCommands(); i++)
		_commands.push_back(costume->getCommand(i));
}

uint32_t AKSQ::getSize()
{
	uint32_t size = 0;
	size += 4 * sizeof(uint8_t); // identifier
	size += sizeof(uint32_t); // size
	size += _commands.size() * sizeof(uint8_t); // commands
	return size;
}

void AKSQ::write(ofstream &f)
{
	IO::writeString(f, "AKSQ");
	IO::writeU32BE(f, getSize());
	for (int i = 0; i < _commands.size(); i++)
		IO::writeU8(f, _commands[i]);
}

AKSQ::~AKSQ()
{
}

