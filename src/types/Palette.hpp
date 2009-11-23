#ifndef _PALETTE_HPP_
#define _PALETTE_HPP_

#include <stdint.h>
#include <vector>
#include <string>
#include "util/BMPFile.hpp"
using namespace std;

class Cycle;

class Palette
{
private:
	static const string XML_FILE_NAME;
	static const uint8_t MAX_CYCLES;
	static const uint8_t N_COMMON_COLORS;
	static const Color COLOR_BLACK;
	static const Color COLOR_DARK_BLUE;
	static const Color COLOR_JAPANESE_LAUREL;
	static const Color COLOR_PERSIAN_GREEN;
	static const Color COLOR_BRIGHT_RED;
	static const Color COLOR_FLIRT;
	static const Color COLOR_CHELSEA_GEM;
	static const Color COLOR_SILVER_CHALICE;
	static const Color COLOR_SCORPION;
	static const Color COLOR_DODGER_BLUE;
	static const Color COLOR_SCREAMIN_GREEN;
	static const Color COLOR_AQUAMARINE;
	static const Color COLOR_PERSIMMON;
	static const Color COLOR_PINK_FLAMINGO;
	static const Color COLOR_GORSE;
	static const Color COLOR_WHITE;

	vector<Color> _colors;
	vector<Cycle *> _cycles;
	uint16_t _startCursor;
	uint16_t _endCursor;
	vector<bool> _reserved;

	uint8_t addColor(Color *c, bool fromStart, bool reserved);
	int16_t addCycle(vector<Color> *colors, Cycle *cycle, bool fromStart);
	int16_t findColor(Color *c, bool fromStart);
	int8_t getPixelCycle(uint8_t pixel, vector<Cycle *> *cycles);
public:
	static const uint16_t MAX_COLORS;

	Palette();
	void prepare();
	Color getColor(uint8_t index) { return _colors[index]; }
	uint8_t getNumberOfCycles() { return _cycles.size(); }
	Cycle *getCycle(uint8_t index) { return _cycles[index]; }
	void add(vector<Color> *colors, vector<vector<uint8_t> > &pixels, vector<Cycle *> *cycles, bool transparent, bool fromStart);
	~Palette();
};

#endif
