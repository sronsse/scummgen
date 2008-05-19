#include "COST.hpp"
#include "util/IO.hpp"
#include "types/Costume.hpp"

COST::COST(Costume *costume)
{
}

uint32_t COST::getSize()
{

}

void COST::write(ofstream &f)
{
	IO::writeString(f, "COST");
	IO::writeU32BE(f, 0);
}

COST::~COST()
{
}

