#include "COST.hpp"
#include "util/BMPFile.hpp"
#include "util/IO.hpp"
#include "types/Costume.hpp"
#include "types/Palette.hpp"

const uint8_t COST::DEFAULT_FORMAT = 0x60;
const uint32_t COST::UNKNOWN = 0;
const uint8_t COST::N_LIMBS = 16;
const uint16_t COST::LIMB_MASK = 0x0001;
const uint8_t COST::REDIR_LIMB = 0xFF;
const uint8_t COST::REDIR_PICT = 0xFF;
const int16_t COST::X_INC = 0;
const int16_t COST::Y_INC = 0;
const uint8_t COST::SHIFT_16 = 4;
const uint8_t COST::SHIFT_32 = 3;

COST::COST(Costume *costume)
{
	_format = DEFAULT_FORMAT;
	_format |= !costume->isMirror() << 7; // If the animations are not mirrored, format's bit 7 should be set

	uint8_t nColors = costume->getNumberOfColors() <= 16 ? 16 : 32;
	if (nColors == 32) // If the number of colors is 32, format's bit 0 should be set
		_format |= 0x01;

	// Costume redirection palette
	for (int i = 0; i < costume->getNumberOfColors(); i++)
		_palette.push_back(costume->getColor(i));
	for (int i = costume->getNumberOfColors(); i < nColors; i++)
		_palette.push_back(0);

	calculateAnimCmdsOffset(costume);
	calculateLimbOffsets(costume);
	calculateAnimOffsets(costume);
	calculateAnimStarts(costume);
	calculateAnimNoLoopAndEndOffsets(costume);
	getAnimCmds(costume);
	getFrames(costume);
	calculatePictOffsets(costume);	
}

void COST::calculateAnimCmdsOffset(Costume *costume)
{
	_animCmdsOffset = 0;
	_animCmdsOffset += sizeof(uint32_t); // unknown
	_animCmdsOffset += 2 * sizeof(uint8_t); // "CO"
	_animCmdsOffset += sizeof(uint8_t); // anims.size()
	_animCmdsOffset += sizeof(uint8_t); // format
	_animCmdsOffset += _palette.size() * sizeof(uint8_t); // palette
	_animCmdsOffset += sizeof(uint16_t); // animCmdsOffset
	_animCmdsOffset += N_LIMBS * sizeof(uint16_t); // limbsOffsets
	_animCmdsOffset += costume->getNumberOfAnims() * Anim::N_DIRECTIONS * sizeof(uint16_t); // animsOffsets
	_animCmdsOffset += costume->getNumberOfAnims() * Anim::N_DIRECTIONS * sizeof(uint16_t); // limbMasks
	_animCmdsOffset += costume->getNumberOfAnims() * Anim::N_DIRECTIONS * sizeof(uint16_t); // animStarts
	_animCmdsOffset += costume->getNumberOfAnims() * Anim::N_DIRECTIONS * sizeof(uint8_t); // animNoLoopAndEndOffset
}

void COST::calculateLimbOffsets(Costume *costume)
{
	for (int i = 0; i  < N_LIMBS - 1; i++) // We only support one limb for now
		_limbsOffsets.push_back(0);

	uint16_t lastLimbOffset = 0;
	lastLimbOffset += _animCmdsOffset; // From "CO" to the start of the anim commands
	for (int i = 0; i < costume->getNumberOfAnims(); i++) // animCmds
	{
		lastLimbOffset += costume->getAnim(i)->getNumberOfCommands(ANIM_WEST) * sizeof(uint8_t);
		lastLimbOffset += costume->getAnim(i)->getNumberOfCommands(ANIM_EAST) * sizeof(uint8_t);
		lastLimbOffset += costume->getAnim(i)->getNumberOfCommands(ANIM_SOUTH) * sizeof(uint8_t);
		lastLimbOffset += costume->getAnim(i)->getNumberOfCommands(ANIM_NORTH) * sizeof(uint8_t);
	}
	_limbsOffsets.push_back(lastLimbOffset);
}

void COST::calculateAnimOffsets(Costume *costume)
{
	uint16_t firstAnimOffset = 0;
	firstAnimOffset += sizeof(uint32_t); // unknown
	firstAnimOffset += 2 * sizeof(uint8_t); // "CO"
	firstAnimOffset += sizeof(uint8_t); // anims.size()
	firstAnimOffset += sizeof(uint8_t); // format
	firstAnimOffset += _palette.size() * sizeof(uint8_t); // palette
	firstAnimOffset += sizeof(uint16_t); // animCmdsOffset
	firstAnimOffset += N_LIMBS * sizeof(uint16_t); // limbsOffsets
	firstAnimOffset += costume->getNumberOfAnims() * Anim::N_DIRECTIONS * sizeof(uint16_t); // animsOffsets
	_animsOffsets.push_back(firstAnimOffset);

	for (int i = 1; i < costume->getNumberOfAnims() * Anim::N_DIRECTIONS; i++)
	{
		uint8_t animOffset = 0;
		animOffset += _animsOffsets[i - 1];
		animOffset += sizeof(uint16_t); // limbMask
		animOffset += sizeof(uint16_t); // animStart
		animOffset += sizeof(uint8_t); // animNoLoopAndEndOffset
		_animsOffsets.push_back(animOffset);
	}
}

void COST::calculateAnimStarts(Costume *costume)
{
	_animStarts.push_back(0);
	_animStarts.push_back(_animStarts.back() + costume->getAnim(0)->getNumberOfCommands(ANIM_WEST));
	_animStarts.push_back(_animStarts.back() + costume->getAnim(0)->getNumberOfCommands(ANIM_EAST));
	_animStarts.push_back(_animStarts.back() + costume->getAnim(0)->getNumberOfCommands(ANIM_SOUTH));

	for (int i = 1; i < costume->getNumberOfAnims(); i++)
	{
		_animStarts.push_back(_animStarts.back() + costume->getAnim(i - 1)->getNumberOfCommands(ANIM_NORTH));
		_animStarts.push_back(_animStarts.back() + costume->getAnim(i)->getNumberOfCommands(ANIM_WEST));
		_animStarts.push_back(_animStarts.back() + costume->getAnim(i)->getNumberOfCommands(ANIM_EAST));
		_animStarts.push_back(_animStarts.back() + costume->getAnim(i)->getNumberOfCommands(ANIM_SOUTH));
	}
}

void COST::calculateAnimNoLoopAndEndOffsets(Costume *costume)
{
	bool animLooped;
	for (int i = 0; i < costume->getNumberOfAnims(); i++)
	{
		animLooped = costume->getAnim(i)->isLoop();
		_animNoLoopAndEndOffsets.push_back((!animLooped << 7) | (costume->getAnim(i)->getNumberOfCommands(ANIM_WEST) - 1));
		_animNoLoopAndEndOffsets.push_back((!animLooped << 7) | (costume->getAnim(i)->getNumberOfCommands(ANIM_EAST) - 1));
		_animNoLoopAndEndOffsets.push_back((!animLooped << 7) | (costume->getAnim(i)->getNumberOfCommands(ANIM_SOUTH) - 1));
		_animNoLoopAndEndOffsets.push_back((!animLooped << 7) | (costume->getAnim(i)->getNumberOfCommands(ANIM_NORTH) - 1));
	}
}

void COST::getAnimCmds(Costume *costume)
{
	for (int i = 0; i < costume->getNumberOfAnims(); i++)
	{
		for (int j = 0; j < costume->getAnim(i)->getNumberOfCommands(ANIM_WEST); j++)
			_animCmds.push_back(costume->getAnim(i)->getCommand(ANIM_WEST, j));
		for (int j = 0; j < costume->getAnim(i)->getNumberOfCommands(ANIM_EAST); j++)
			_animCmds.push_back(costume->getAnim(i)->getCommand(ANIM_EAST, j));
		for (int j = 0; j < costume->getAnim(i)->getNumberOfCommands(ANIM_SOUTH); j++)
			_animCmds.push_back(costume->getAnim(i)->getCommand(ANIM_SOUTH, j));
		for (int j = 0; j < costume->getAnim(i)->getNumberOfCommands(ANIM_NORTH); j++)
			_animCmds.push_back(costume->getAnim(i)->getCommand(ANIM_NORTH, j));
	}
}

void COST::getFrames(Costume *costume)
{
	for (int i = 0; i < costume->getNumberOfFrames(); i++)
	{
		_pictWidths.push_back(costume->getWidth());
		_pictHeights.push_back(costume->getHeight());
		_pictXs.push_back(costume->getFrame(i)->getXOffset());
		_pictYs.push_back(costume->getFrame(i)->getYOffset());
		vector<uint8_t> dataBytes;
		getDataBytes(costume, costume->getFrame(i), dataBytes);
		_dataBytes.push_back(dataBytes);
	}
}

void COST::calculatePictOffsets(Costume *costume)
{
	uint16_t firstPictOffset = 0;
	firstPictOffset += _animCmdsOffset; // from "CO" to the start of the anim commands
	firstPictOffset += _animCmds.size() * sizeof(uint8_t); // animCmds
	firstPictOffset += costume->getNumberOfFrames() * sizeof(uint16_t); // pictOffsets
	_pictOffsets.push_back(firstPictOffset);
	for (int i = 1; i < _dataBytes.size(); i++)
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
		pictOffset += _dataBytes[i - 1].size() * sizeof(uint8_t); // dataBytes
		_pictOffsets.push_back(pictOffset);
	}
}

void COST::getDataBytes(Costume *costume, Frame *frame, vector<uint8_t> &dataBytes)
{
	// Prepare data for RLE
	vector<uint8_t> pixels;
	vector<uint32_t> repCounts;
	uint8_t lastPixel = frame->getPixel(0, 0);
	uint32_t repCount = 0;
	for (int i = 0; i < frame->getWidth(); i++)
	{
		for (int j = 0; j < frame->getHeight(); j++)
			addPixel(frame->getPixel(i, j), lastPixel, repCount, pixels, repCounts);
		for (int j = 0; j < costume->getHeight() - frame->getHeight(); j++)
			addPixel(0, lastPixel, repCount, pixels, repCounts);
	}
	for (int i = 0; i < costume->getWidth() - frame->getWidth(); i++)
		for (int j = 0; j < costume->getHeight(); j++)
			addPixel(0, lastPixel, repCount, pixels, repCounts);
	pixels.push_back(lastPixel);
	repCounts.push_back(repCount);

	// Write data bytes using the RLE algorithm
	writeRLEData(dataBytes, costume->getNumberOfColors() <= 16 ? SHIFT_16 : SHIFT_32, &pixels, &repCounts);
}

void COST::addPixel(uint8_t pixel, uint8_t &lastPixel, uint32_t &repCount, vector<uint8_t> &pixels, vector<uint32_t> &repCounts)
{
	if (pixel == lastPixel)
		repCount++;
	else
	{
		pixels.push_back(lastPixel);
		repCounts.push_back(repCount);
		lastPixel = pixel;
		repCount = 1;
	}
}

void COST::writeRLEData(vector<uint8_t> &dataBytes, uint8_t shift, vector<uint8_t> *pixels, vector<uint32_t> *repCounts)
{
	// Get the max repetition count if using one byte for description
	uint8_t maxRepCount = (1 << shift) - 1;

	// Write data bytes
	for (int i = 0; i < repCounts->size(); i++)
	{
		uint8_t pixel = (*pixels)[i];
		uint32_t repCount = (*repCounts)[i];

		if (repCount <= maxRepCount)
			dataBytes.push_back(pixel << shift | repCount);
		else
		{
			while (repCount > 255)
			{
				dataBytes.push_back(pixel << shift);
				dataBytes.push_back(255);
				repCount -= 255;
			}
			if (repCount <= maxRepCount)
				dataBytes.push_back(pixel << shift | repCount);
			else
			{
				dataBytes.push_back(pixel << shift);
				dataBytes.push_back(repCount);
			}
		}
	}
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
	size += _dataBytes.size() * sizeof(int16_t); // pictXIncs
	size += _dataBytes.size() * sizeof(int16_t); // pictYIncs
	size += _dataBytes.size() * sizeof(uint8_t); // redirLimbs
	size += _dataBytes.size() * sizeof(uint8_t); // redirPicts
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
	for (int i = 0; i < _dataBytes.size(); i++)
	{
		IO::writeU16LE(f, _pictWidths[i]);
		IO::writeU16LE(f, _pictHeights[i]);
		IO::writeU16LE(f, _pictXs[i]);
		IO::writeU16LE(f, _pictYs[i]);
		IO::writeU16LE(f, X_INC);
		IO::writeU16LE(f, Y_INC);
		IO::writeU8(f, REDIR_LIMB);
		IO::writeU8(f, REDIR_PICT);
		for (int j = 0; j < _dataBytes[i].size(); j++)
			IO::writeU8(f, _dataBytes[i][j]);
	}
}

COST::~COST()
{
}
