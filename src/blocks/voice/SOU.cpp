#include "SOU.hpp"
#include "util/IO.hpp"
#include "types/Game.hpp"
#include "VCTL.hpp"
#include "VOC.hpp"

SOU::SOU(Game *game)
{
	for (int i = 0; i < game->getNumberOfVoices(); i++)
	{
		_vctls.push_back(new VCTL(game->getVoice(i)));
		_vocs.push_back(new VOC(game->getVoice(i)));
	}
}

uint32_t SOU::getSize()
{
	uint32_t size = 0;
	size += 4 * sizeof(uint8_t); // identifier
	size += sizeof(uint32_t); // 0
	for (int i = 0; i < _vctls.size(); i++) // vctls
		size += _vctls[i]->getSize();
	for (int i = 0; i < _vocs.size(); i++) // vocs
		size += _vocs[i]->getSize();
	return size;
}

void SOU::write(ofstream &f)
{
	IO::writeString(f, "SOU ");
	IO::writeU32BE(f, 0);
	for (int i = 0; i < _vctls.size(); i++)
	{
		_vctls[i]->write(f);
		_vocs[i]->write(f);
	}
}

SOU::~SOU()
{
	for (int i = 0; i < _vctls.size(); i++)
		delete _vctls[i];
	for (int i = 0; i < _vocs.size(); i++)
		delete _vocs[i];
}

