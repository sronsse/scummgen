#include "AKOS.hpp"
#include "util/IO.hpp"
#include "types/Costume.hpp"
#include "AKHD.hpp"
#include "AKPL.hpp"
#include "RGBS.hpp"
#include "AKSQ.hpp"
#include "AKCH.hpp"
#include "AKOF.hpp"
#include "AKCI.hpp"
#include "AKCD.hpp"

AKOS::AKOS(Costume *costume)
{
	_akhd = new AKHD(costume);
	_akpl = new AKPL(costume);
	_rgbs = new RGBS(costume);
	_aksq = new AKSQ(costume);
	_akch = new AKCH(costume);
	_akci = new AKCI(costume);
	_akcd = new AKCD(costume);
	_akof = new AKOF(costume, _akcd);
}

uint32_t AKOS::getSize()
{
	uint32_t size = 0;
	size += 4 * sizeof(uint8_t); // identifier
	size += sizeof(uint32_t); // size
	size += _akhd->getSize(); // akhd
	size += _akpl->getSize(); // akpl
	size += _rgbs->getSize(); // rgbs
	size += _aksq->getSize(); // aksq
	size += _akch->getSize(); // akch
	size += _akof->getSize(); // akof
	size += _akci->getSize(); // akci
	size += _akcd->getSize(); // akcd
	return size;
}

void AKOS::write(ofstream &f)
{
	IO::writeString(f, "AKOS");
	IO::writeU32BE(f, getSize());
	_akhd->write(f);
	_akpl->write(f);
	_rgbs->write(f);
	_aksq->write(f);
	_akch->write(f);
	_akof->write(f);
	_akci->write(f);
	_akcd->write(f);
}

AKOS::~AKOS()
{
	delete _akhd;
	delete _akpl;
	delete _rgbs;
	delete _aksq;
	delete _akch;
	delete _akof;
	delete _akci;
	delete _akcd;
}

