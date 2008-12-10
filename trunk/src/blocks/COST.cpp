#include "COST.hpp"
#include "util/IO.hpp"
#include "types/Costume.hpp"

const uint32_t COST::UNKNOWN = 0;
const uint8_t COST::N_LIMBS = 16;
const uint16_t COST::LIMB_MASK = 0x0001;
const uint8_t COST::REDIR_LIMB = 0xFF;
const uint8_t COST::REDIR_PICT = 0xFF;

COST::COST(Costume *costume)
{
	_format = !costume->isMirror() << 7; // If format's bit 7 is set, the animations are not mirrored

	uint8_t nColors = costume->getNumberOfColors() <= 16 ? 16 : 32;
	if (nColors == 32) // If the number of colors is 32, the first bit of format should be set
		_format |= 0x61;

	for (int i = 0; i < nColors; i++)
		_palette.push_back(costume->getPaletteBaseIndex() + i);

	_animCmdsOffset = 0;
	_animCmdsOffset += sizeof(uint32_t); // unknown
	_animCmdsOffset += 2 * sizeof(uint8_t); // "CO"
	_animCmdsOffset += sizeof(uint8_t); // anims.size()
	_animCmdsOffset += sizeof(uint8_t); // format
	_animCmdsOffset += _palette.size() * sizeof(uint8_t); // palette
	_animCmdsOffset += sizeof(uint16_t); // animCmdsOffset
	_animCmdsOffset += N_LIMBS * sizeof(uint16_t); // limbsOffsets
	_animCmdsOffset += costume->getNumberOfAnims() * sizeof(uint16_t); // animsOffsets
	_animCmdsOffset += costume->getNumberOfAnims() * sizeof(uint16_t); // limbMasks
	_animCmdsOffset += costume->getNumberOfAnims() * sizeof(uint16_t); // animStarts
	_animCmdsOffset += costume->getNumberOfAnims() * sizeof(uint8_t); // animNoLoopAndEndOffset

	for (int i = 0; i  < N_LIMBS - 1; i++) // We only support one limb for now
		_limbsOffsets.push_back(0);
	uint16_t lastLimbOffset = 0;
	lastLimbOffset += _animCmdsOffset; // From "CO" to the start of the anim commands
	for (int i = 0; i < costume->getNumberOfAnims(); i++) // animCmds
		lastLimbOffset += costume->getAnim(i)->getNumberOfCommands() * sizeof(uint8_t);
	_limbsOffsets.push_back(lastLimbOffset);

	uint16_t firstAnimOffset = 0;
	firstAnimOffset += sizeof(uint32_t); // unknown
	firstAnimOffset += 2 * sizeof(uint8_t); // "CO"
	firstAnimOffset += sizeof(uint8_t); // anims.size()
	firstAnimOffset += sizeof(uint8_t); // format
	firstAnimOffset += _palette.size() * sizeof(uint8_t); // palette
	firstAnimOffset += sizeof(uint16_t); // animCmdsOffset
	firstAnimOffset += N_LIMBS * sizeof(uint16_t); // limbsOffsets
	firstAnimOffset += costume->getNumberOfAnims() * sizeof(uint16_t); // animsOffsets
	_animsOffsets.push_back(firstAnimOffset);
	for (int i = 1; i < costume->getNumberOfAnims(); i++)
	{
		uint8_t animOffset = 0;
		animOffset += _animsOffsets[i - 1];
		animOffset += sizeof(uint16_t); // limbMask
		animOffset += sizeof(uint16_t); // animStart
		animOffset += sizeof(uint8_t); // animNoLoopAndEndOffset
		_animsOffsets.push_back(animOffset);
	}

	uint16_t firstAnimStart = 0;
	_animStarts.push_back(firstAnimStart);
	uint16_t firstAnimNoLoopAndEndOffset = (!costume->getAnim(0)->isLoop() << 7) | (costume->getAnim(0)->getNumberOfCommands() - 1);
	_animNoLoopAndEndOffsets.push_back(firstAnimNoLoopAndEndOffset);
	for (int i = 1; i < costume->getNumberOfAnims(); i++)
	{
		_animStarts.push_back(_animStarts[i - 1] + costume->getAnim(i - 1)->getNumberOfCommands());
		_animNoLoopAndEndOffsets.push_back((!costume->getAnim(i)->isLoop() << 7) | (costume->getAnim(i)->getNumberOfCommands() - 1));
	}

	for (int i = 0; i < costume->getNumberOfAnims(); i++)
		for (int j = 0; j < costume->getAnim(i)->getNumberOfCommands(); j++)
			_animCmds.push_back(costume->getAnim(i)->getCommand(j));

	for (int i = 0; i < costume->getNumberOfFrames(); i++)
	{
		_pictWidths.push_back(costume->getFrame(i)->getWidth());
		_pictHeights.push_back(costume->getFrame(i)->getHeight());
		_pictXs.push_back(costume->getFrame(i)->getX());
		_pictYs.push_back(costume->getFrame(i)->getY());
		_pictXIncs.push_back(costume->getFrame(i)->getXInc());
		_pictYIncs.push_back(costume->getFrame(i)->getYInc());
		vector<uint8_t> dataBytes;
		getDataBytes(costume, costume->getFrame(i), dataBytes);
		_dataBytes.push_back(dataBytes);
	}

	uint16_t firstPictOffset = 0;
	firstPictOffset += _animCmdsOffset; // from "CO" to the start of the anim commands
	for (int i = 0; i < costume->getNumberOfAnims(); i++) // animCmds
		firstPictOffset += costume->getAnim(i)->getNumberOfCommands() * sizeof(uint8_t);
	firstPictOffset += costume->getNumberOfFrames() * sizeof(uint16_t); // pictOffsets
	_pictOffsets.push_back(firstPictOffset);
	for (int i = 1; i < _pictWidths.size(); i++)
	{
		uint16_t pictOffset = _pictOffsets[i - 1];
		pictOffset += sizeof(uint16_t); // pictWidth
		pictOffset += sizeof(uint16_t); // pictHeight
		pictOffset += sizeof(int16_t); // pictX
		pictOffset += sizeof(int16_t); // pictY
		pictOffset += sizeof(int16_t); // pictXInc
		pictOffset += sizeof(int16_t); // pictYInc
		pictOffset += sizeof(uint8_t); // redirLimb
		pictOffset += sizeof(uint8_t); // redirPict
		pictOffset += _dataBytes[i].size() * sizeof(uint8_t); // dataBytes
		_pictOffsets.push_back(pictOffset);
	}	
}

void COST::getDataBytes(Costume *costume, Frame *frame, vector<uint8_t> &dataBytes)
{
	uint8_t shift = 4;
	if (costume->getNumberOfColors() > 16)
		shift = 3;

	for (int i = 0; i < frame->getWidth(); i++)
		for (int j = 0; j < frame->getHeight(); j++)
			dataBytes.push_back(frame->getPixel(i, j) << shift | 0x01);
}

uint32_t COST::getSize()
{
	uint32_t size = 0;
	size += 4 * sizeof(uint8_t); // identifier
	size += sizeof(uint32_t); // size
	size += sizeof(uint32_t); // unknown
	size += 2 * sizeof(uint8_t); // small identifier
	size += sizeof(uint8_t); // animOffsets size
	size += sizeof(uint8_t); // format
	size += _palette.size() * sizeof(uint8_t); // palette
	size += sizeof(uint16_t); // animCmdsOffset
	size += _limbsOffsets.size() * sizeof(uint16_t); // limbsOffsets
	size += _animsOffsets.size() * sizeof(uint16_t); // animsOffsets
	size += _animStarts.size() * sizeof(uint16_t); // limbMasks
	size += _animStarts.size() * sizeof(uint16_t); // animStarts
	size += _animNoLoopAndEndOffsets.size() * sizeof(uint8_t); // animNoLoopAndEndOffsets
	size += _animCmds.size() * sizeof(uint8_t); // animCmds
	size += _pictOffsets.size() * sizeof(uint16_t); // pictOffsets
	size += _pictWidths.size() * sizeof(uint16_t); // pictWidths
	size += _pictHeights.size() * sizeof(uint16_t); // pictHeights
	size += _pictXs.size() * sizeof(int16_t); // pictXs
	size += _pictYs.size() * sizeof(int16_t); // pictYs
	size += _pictXIncs.size() * sizeof(int16_t); // pictXIncs
	size += _pictYIncs.size() * sizeof(int16_t); // pictYIncs
	size += _pictWidths.size() * sizeof(uint8_t); // redirLimbs
	size += _pictWidths.size() * sizeof(uint8_t); // redirPicts
	for (int i = 0; i < _dataBytes.size(); i++) // dataBytes
		size += _dataBytes[i].size() * sizeof(uint8_t);
	return size;
}

void COST::write(fstream &f)
{
	IO::writeString(f, "COST");
	IO::writeU32BE(f, getSize());
	IO::writeU32LE(f, UNKNOWN);
	IO::writeString(f, "CO");
	IO::writeU8(f, _animsOffsets.size());
	IO::writeU8(f, _format);
	for (int i = 0; i < _palette.size(); i++)
		IO::writeU8(f, _palette[i]);
	IO::writeU16LE(f, _animCmdsOffset);
	for (int i = 0; i < _limbsOffsets.size(); i++)
		IO::writeU16LE(f, _limbsOffsets[i]);
	for (int i = 0; i < _animsOffsets.size(); i++)
		IO::writeU16LE(f, _animsOffsets[i]);
	for (int i = 0; i < _animStarts.size(); i++)
	{
		IO::writeU16LE(f, LIMB_MASK);
		IO::writeU16LE(f, _animStarts[i]);
		IO::writeU8(f, _animNoLoopAndEndOffsets[i]);
	}
	for (int i = 0; i < _animCmds.size(); i++)
		IO::writeU8(f, _animCmds[i]);
	for (int i = 0; i < _pictOffsets.size(); i++)
		IO::writeU16LE(f, _pictOffsets[i]);
	for (int i = 0; i < _pictWidths.size(); i++)
	{
		IO::writeU16LE(f, _pictWidths[i]);
		IO::writeU16LE(f, _pictHeights[i]);
		IO::writeU16LE(f, _pictXs[i]);
		IO::writeU16LE(f, _pictYs[i]);
		IO::writeU16LE(f, _pictXIncs[i]);
		IO::writeU16LE(f, _pictYIncs[i]);
		IO::writeU8(f, REDIR_LIMB);
		IO::writeU8(f, REDIR_PICT);
		for (int j = 0; j < _dataBytes[i].size(); j++)
			IO::writeU8(f, _dataBytes[i][j]);
	}
}

COST::~COST()
{
}
