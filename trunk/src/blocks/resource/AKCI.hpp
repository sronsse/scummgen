#ifndef _AKCI_BLOCK_HPP_
#define _AKCI_BLOCK_HPP_

#include <fstream>
#include <stdint.h>
#include <vector>
using namespace std;

class Costume;

class AKCI
{
private:
	uint32_t _size;
	vector<uint16_t> _widths;
	vector<uint16_t> _heights;
public:
	AKCI(Costume *costume);
	uint32_t getSize();
	void write(ofstream &f);
	~AKCI();
};

#endif

