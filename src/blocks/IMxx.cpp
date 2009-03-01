#include "IMxx.hpp"
#include "util/IO.hpp"
#include "types/Image.hpp"
#include "SMAP.hpp"
#include "ZPxx.hpp"

IMxx::IMxx(Image *image, uint8_t index)
{
	_index = index;
	_smap = new SMAP(image);
	for (int i = 0; i < image->getNumberOfZPlanePaths(); i++)
		_zpxxs.push_back(new ZPxx(image->getZPlanePath(i), i + 1));
}

uint32_t IMxx::getSize()
{
	uint32_t size = 0;
	size += 4 * sizeof(uint8_t); // identifier
	size += sizeof(uint32_t); // size
	size += _smap->getSize(); // smap
	for (int i = 0; i < _zpxxs.size(); i++) // zpxxs
		size += _zpxxs[i]->getSize();
	return size;
}

void IMxx::write(fstream &f)
{
	IO::writeString(f, "IM" + IO::getStringFromIndex(_index, 2));
	IO::writeU32BE(f, getSize());
	_smap->write(f);
	for (int i = 0; i < _zpxxs.size(); i++)
		_zpxxs[i]->write(f);
}

IMxx::~IMxx()
{
	delete _smap;
	for (int i = 0; i < _zpxxs.size(); i++)
		delete _zpxxs[i];
}
