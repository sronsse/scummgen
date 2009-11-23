#include "Palette.hpp"
#include "Image.hpp"
#include "util/IO.hpp"
#include "util/Log.hpp"
#include "util/XMLFile.hpp"

const uint8_t Palette::MAX_CYCLES = 4;
const uint8_t Palette::N_COMMON_COLORS = 16;

// Common palette colors (names obtained from http://chir.ag/projects/name-that-color/)
const Color Palette::COLOR_BLACK = { 0, 0, 0 };
const Color Palette::COLOR_DARK_BLUE = { 0, 0, 171 };
const Color Palette::COLOR_JAPANESE_LAUREL = { 0, 171, 0 };
const Color Palette::COLOR_PERSIAN_GREEN = { 0, 171, 171 };
const Color Palette::COLOR_BRIGHT_RED = { 171, 0, 0 };
const Color Palette::COLOR_FLIRT = { 171, 0, 171 };
const Color Palette::COLOR_CHELSEA_GEM = { 171, 87, 0 };
const Color Palette::COLOR_SILVER_CHALICE = { 171, 171, 171 };
const Color Palette::COLOR_SCORPION = { 87, 87, 87 };
const Color Palette::COLOR_DODGER_BLUE = { 87, 87, 255 };
const Color Palette::COLOR_SCREAMIN_GREEN = { 87, 255, 87 };
const Color Palette::COLOR_AQUAMARINE = { 87, 255, 255 };
const Color Palette::COLOR_PERSIMMON = { 255, 87, 87 };
const Color Palette::COLOR_PINK_FLAMINGO = { 255, 87, 255 };
const Color Palette::COLOR_GORSE = { 255, 255, 87 };
const Color Palette::COLOR_WHITE = { 255, 255, 255 };

const uint16_t Palette::MAX_COLORS = 256;

Palette::Palette():
_startCursor(0),
_endCursor(0)
{
}

uint8_t Palette::addColor(Color *c, bool reserved, bool fromStart)
{
	uint8_t index;

	// Check if palette is fully filled already
	if (_startCursor == _endCursor)
		Log::write(LOG_ERROR, "Palette contains too many colors !\n");

	// Compute right index
	if (fromStart)
	{
		index = _startCursor;
		_startCursor++;
	}
	else
	{
		_endCursor--;
		index = _endCursor;
	}

	// Add color at the right position and fill the correponding reserved entry
	_colors[index] = *c;
	_reserved[index] = reserved;

	// Return index
	return index;
}

int16_t Palette::addCycle(vector<Color> *colors, Cycle *cycle, bool fromStart)
{
	// Check if the maximum number of cycles has been reached
	if (_cycles.size() == MAX_CYCLES)
		Log::write(LOG_ERROR, "Rooms can't have more than %u palette cycles !\n", MAX_CYCLES);

	// Compute cycle offset
	int16_t offset;
	if (fromStart)
		offset = _startCursor - cycle->getStart();
	else
		offset = _endCursor - cycle->getEnd() - cycle->getStart() - 1;

	// Add cycle colors to the palette
	for (int i = cycle->getStart(); i <= cycle->getEnd(); i++)
		addColor(&(*colors)[i], true, fromStart);

	// Add cycle to the palette cycles list
	_cycles.push_back(new Cycle());
	_cycles.back()->setName(cycle->getName());
	_cycles.back()->setStart(cycle->getStart() + offset);
	_cycles.back()->setEnd(cycle->getEnd() + offset);
	_cycles.back()->setDelay(cycle->getDelay());
	_cycles.back()->setForward(fromStart ? cycle->isForward() : !cycle->isForward());
	_cycles.back()->setID(_cycles.size());

	// Return offset
	return offset;
}

int16_t Palette::findColor(Color *c, bool fromStart)
{
	// Check if color is already present in the palette
	if (fromStart)
	{
		for (int i = 0; i < _startCursor; i++)
			if (!_reserved[i] && c->r == _colors[i].r && c->g == _colors[i].g && c->b == _colors[i].b)
				return i;
	}
	else
	{
		for (int i = MAX_COLORS - 1; i >= _endCursor; i--)
			if (c->r == _colors[i].r && c->g == _colors[i].g && c->b == _colors[i].b)
				return i;
	}

	// Color was not found
	return -1;
}

int8_t Palette::getPixelCycle(uint8_t pixel, vector<Cycle *> *cycles)
{
	// Check if pixel is present in cycles
	for (int i = 0; i < cycles->size(); i++)
		if (pixel >= (*cycles)[i]->getStart() && pixel <= (*cycles)[i]->getEnd())
			return i;

	// Pixel is not included in any cycle
	return -1;
}

void Palette::prepare()
{
	// Set cursors
	_startCursor = N_COMMON_COLORS;
	_endCursor = MAX_COLORS;

	// Set palette size and default colors
	_colors.clear();
	_colors.push_back(COLOR_BLACK);
	_colors.push_back(COLOR_DARK_BLUE);
	_colors.push_back(COLOR_JAPANESE_LAUREL);
	_colors.push_back(COLOR_PERSIAN_GREEN);
	_colors.push_back(COLOR_BRIGHT_RED);
	_colors.push_back(COLOR_FLIRT);
	_colors.push_back(COLOR_CHELSEA_GEM);
	_colors.push_back(COLOR_SILVER_CHALICE);
	_colors.push_back(COLOR_SCORPION);
	_colors.push_back(COLOR_DODGER_BLUE);
	_colors.push_back(COLOR_SCREAMIN_GREEN);
	_colors.push_back(COLOR_AQUAMARINE);
	_colors.push_back(COLOR_PERSIMMON);
	_colors.push_back(COLOR_PINK_FLAMINGO);
	_colors.push_back(COLOR_GORSE);
	_colors.push_back(COLOR_WHITE);
	_colors.resize(MAX_COLORS);

	// Clear our reserved array
	_reserved.clear();
	_reserved.resize(MAX_COLORS);
}

void Palette::add(vector<Color> *colors, vector<vector<uint8_t> > &pixels, vector<Cycle *> *cycles, bool transparent, bool fromStart)
{
	vector<int16_t> cycleOffsets;

	// Add cycle colors to the palette first
	if (cycles != NULL)
		for (int i = 0; i < cycles->size(); i++)
			cycleOffsets.push_back(addCycle(colors, (*cycles)[i], fromStart));

	// Cycle through all pixels
	for (int x = 0; x < pixels.size(); x++)
		for (int y = 0; y < pixels[x].size(); y++)
		{
			// No operation needed if the pixel is transparent
			if (pixels[x][y] == 0 && transparent)
				continue;

			// Check if pixel is included in a cycle
			if (cycles != NULL)
			{
				int8_t cycle = getPixelCycle(pixels[x][y], cycles);
				if (cycle != -1)
				{
					pixels[x][y] += cycleOffsets[cycle];
					continue;
				}
			}

			// Check if color already exists in palette
			Color *c = &((*colors)[pixels[x][y]]);
			int16_t found = findColor(c, fromStart);
			if (found != -1)
			{
				pixels[x][y] = found;
				continue;
			}

			// Add color to the palette
			pixels[x][y] = addColor(c, false, fromStart);
		}
}

Palette::~Palette()
{
	for (int i = 0; i < _cycles.size(); i++)
		delete _cycles[i];
}
