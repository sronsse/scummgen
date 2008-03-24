#ifndef _AKOS_BLOCK_HPP_
#define _AKOS_BLOCK_HPP_

#include <fstream>
#include <stdint.h>
using namespace std;

class Costume;
class AKHD;
class AKPL;
class RGBS;
class AKSQ;
class AKCH;
class AKOF;
class AKCI;
class AKCD;

class AKOS
{
private:
	AKHD *_akhd;
	AKPL *_akpl;
	RGBS *_rgbs;
	AKSQ *_aksq;
	AKCH *_akch;
	AKOF *_akof;
	AKCI *_akci;
	AKCD *_akcd;
public:
	AKOS(Costume *costume);
	uint32_t getSize();
	void write(ofstream &f);
	~AKOS();
};

#endif

