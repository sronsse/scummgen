#include "Palette.hpp"
#include "util/IO.hpp"
#include "util/Log.hpp"
#include "util/XMLFile.hpp"

const string PaletteData::XML_FILE_NAME = "palette.xml";

const uint8_t Palette::MAX_CYCLES = 4;
const uint8_t Palette::N_EGA_COLORS = 16;

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

Area::Area():
_name(),
_start(0),
_end(0)
{
}

void Area::load(XMLNode *node)
{
	Log::write(LOG_INFO, "Area\n");
	Log::indent();

	_name = node->getChild("name")->getStringContent();
	Log::write(LOG_INFO, "name: %s\n", _name.c_str());

	_start = node->getChild("start")->getIntegerContent();
	Log::write(LOG_INFO, "start: %u\n", _start);

	_end = node->getChild("end")->getIntegerContent();
	Log::write(LOG_INFO, "end: %u\n", _end);

	Log::unIndent();
}

void Area::save(XMLNode *node)
{
	Log::write(LOG_INFO, "Area\n");
	Log::indent();

	node->addChild(new XMLNode("name", _name));
	Log::write(LOG_INFO, "name: %s\n", _name.c_str());

	node->addChild(new XMLNode("start", _start));
	Log::write(LOG_INFO, "start: %u\n", _start);

	node->addChild(new XMLNode("end", _end));
	Log::write(LOG_INFO, "end: %u\n", _end);

	Log::unIndent();
}

Area::~Area()
{
}

Cycle::Cycle():
_id(0),
_name(),
_start(0),
_end(0),
_delay(0),
_forward(true)
{
}

void Cycle::load(XMLNode *node)
{
	Log::write(LOG_INFO, "Cycle\n");
	Log::indent();

	_name = node->getChild("name")->getStringContent();
	Log::write(LOG_INFO, "name: %s\n", _name.c_str());

	_start = node->getChild("start")->getIntegerContent();
	Log::write(LOG_INFO, "start: %u\n", _start);

	_end = node->getChild("end")->getIntegerContent();
	Log::write(LOG_INFO, "end: %u\n", _end);

	_delay = node->getChild("delay")->getIntegerContent();
	Log::write(LOG_INFO, "delay: %u\n", _delay);

	_forward = node->getChild("forward")->getBooleanContent();
	Log::write(LOG_INFO, "forward: %s\n", _forward ? "true" : "false");

	Log::unIndent();
}

void Cycle::save(XMLNode *node)
{
	Log::write(LOG_INFO, "Cycle\n");
	Log::indent();

	node->addChild(new XMLNode("name", _name));
	Log::write(LOG_INFO, "name: %s\n", _name.c_str());

	node->addChild(new XMLNode("start", _start));
	Log::write(LOG_INFO, "start: %u\n", _start);

	node->addChild(new XMLNode("end", _end));
	Log::write(LOG_INFO, "end: %u\n", _end);

	node->addChild(new XMLNode("delay", _delay));
	Log::write(LOG_INFO, "delay: %u\n", _delay);

	node->addChild(new XMLNode("forward", _forward));
	Log::write(LOG_INFO, "forward: %s\n", _forward ? "true" : "false");

	Log::unIndent();
}

Cycle::~Cycle()
{
}

PaletteData::PaletteData():
_transparent(false)
{
}

void PaletteData::load(string dirPath)
{
	Log::write(LOG_INFO, "PaletteData\n");
	Log::indent();

	XMLFile xmlFile;
	xmlFile.open(dirPath + XML_FILE_NAME);
	XMLNode *rootNode = xmlFile.getRootNode();

	_transparent = rootNode->getChild("transparent")->getBooleanContent();
	Log::write(LOG_INFO, "transparent: %s\n", _transparent ? "true" : "false");

	int i = 0;
	XMLNode *child;
	while ((child = rootNode->getChild("area", i++)) != NULL)
	{
		Area *area = new Area();
		area->load(child);
		_areas.push_back(area);
	}

	i = 0;
	while ((child = rootNode->getChild("cycle", i++)) != NULL)
	{
		Cycle *cycle = new Cycle();
		cycle->load(child);
		_cycles.push_back(cycle);
	}

	Log::unIndent();
}

void PaletteData::save(string dirPath)
{
	Log::write(LOG_INFO, "PaletteData\n");
	Log::indent();

	if (!IO::createDirectory(dirPath))
		Log::write(LOG_ERROR, "Could not create directory \"%s\" !\n", dirPath.c_str());

	XMLFile xmlFile;
	XMLNode *rootNode = new XMLNode("palette");
	xmlFile.setRootNode(rootNode);

	rootNode->addChild(new XMLNode("transparent", _transparent));
	Log::write(LOG_INFO, "transparent: %s\n", _transparent ? "true" : "false");

	for (int i = 0; i < _areas.size(); i++)
	{
		XMLNode *child = new XMLNode("area");
		rootNode->addChild(child);
		_areas[i]->save(child);
	}

	for (int i = 0; i < _cycles.size(); i++)
	{
		XMLNode *child = new XMLNode("cycle");
		rootNode->addChild(child);
		_cycles[i]->save(child);
	}

	if (!xmlFile.save(dirPath + XML_FILE_NAME))
		Log::write(LOG_ERROR, "Couldn't save object to the specified directory !\n");

	Log::unIndent();
}

PaletteData::~PaletteData()
{
	for (int i = 0; i < _areas.size(); i++)
		delete _areas[i];
	for (int i = 0; i < _cycles.size(); i++)
		delete _cycles[i];
}

Palette::Palette(bool local):
_local(local),
_cursor(0)
{
}

uint8_t Palette::addColor(Color *c, bool reserved)
{
	uint8_t index;

	// Check if palette is fully filled already
	if ((_local && _cursor == MAX_COLORS - 1) || (!_local && _cursor == N_EGA_COLORS))
		Log::write(LOG_ERROR, "Palette contains too many colors !\n");

	// Compute right index
	if (_local)
	{
		index = _cursor;
		_cursor++;
	}
	else
	{
		_cursor--;
		index = _cursor;
	}

	// Add color at the right position and fill the correponding reserved entry
	_colors[index] = *c;
	_reserved[index] = reserved;

	// Return index
	return index;
}

int16_t Palette::findColor(Color *c)
{
	// Check if color is already present in the palette
	if (_local)
	{
		for (int i = _cursor - 1; i >= 0 ; i--)
			if (!_reserved[i] && c->r == _colors[i].r && c->g == _colors[i].g && c->b == _colors[i].b)
		return i;
	}
	else
	{
		for (int i = MAX_COLORS - 1; i >= _cursor; i--)
			if (!_reserved[i] && c->r == _colors[i].r && c->g == _colors[i].g && c->b == _colors[i].b)
		return i;
	}

	// Color was not found
	return -1;
}

void Palette::prepare()
{
	Log::write(LOG_INFO, "Preparing palette...\n");
	Log::indent();

	// Set cursor
	_cursor = _local ? N_EGA_COLORS : MAX_COLORS;

	// Clear palette
	_colors.clear();

	// If the palette is local, then we fill the EGA colors first
	if (_local)
	{
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
	}

	// Resize palette
	_colors.resize(MAX_COLORS);

	// Clear our reserved array
	_reserved.clear();
	_reserved.resize(MAX_COLORS);

	Log::write(LOG_INFO, "Palette cursor: %u...\n", _cursor);
	Log::unIndent();
}

void Palette::add(vector<Color> *colors, vector<vector<uint8_t> > &pixels, PaletteData *paletteData)
{
	vector<int16_t> areaOffsets;
	vector<int16_t> cycleOffsets;

	// Add area colors to the palette first
	for (int i = 0; i < paletteData->getNumberOfAreas(); i++)
	{
		Area *area = paletteData->getArea(i);
		uint8_t start;

		// Check if area is already present
		bool found = false;
		for (int j = 0; j < _areas.size(); j++)
			if (area->getName() == _areas[j]->getName())
			{
				found = true;
				start = _areas[j]->getStart();
				break;
			}

		// Only add the area if it's not existing already
		if (!found)
		{
			// Compute area start
			start = _local ? _cursor : _cursor - (area->getEnd() - area->getStart()) - 1;

			// Add area colors to the palette
			for (int j = area->getStart(); j <= area->getEnd(); j++)
				addColor(&(*colors)[_local ? j : area->getStart() + area->getEnd() - j], true);

			// Add area to the palette area list
			_areas.push_back(new Area());
			_areas.back()->setName(area->getName());
			_areas.back()->setStart(start);
			_areas.back()->setEnd(area->getEnd() - area->getStart() + start);
		}

		// Add offset
		areaOffsets.push_back((int16_t)start - (int16_t)area->getStart());
	}

	// Add cycle colors to the palette
	for (int i = 0; i < paletteData->getNumberOfCycles(); i++)
	{
		Cycle *cycle = paletteData->getCycle(i);

		int16_t start = -1;

		// Check if cycle is included in an area
		for (int j = 0; j < paletteData->getNumberOfAreas(); j++)
			if (paletteData->getCycle(i)->getStart() >= paletteData->getArea(j)->getStart() && paletteData->getCycle(i)->getStart() <= paletteData->getArea(j)->getEnd())
			{
				if (paletteData->getCycle(i)->getEnd() > paletteData->getArea(j)->getEnd())
					Log::write(LOG_ERROR, "Palette areas and cycles overlap !\n");
				start = areaOffsets[j] + paletteData->getCycle(i)->getStart() - paletteData->getArea(j)->getStart();
			}

		// Add cycle colors if cycle is not included in an area
		bool found = false;
		if (start == -1)
		{
			// Check if cycle is already present
			for (int j = 0; j < _cycles.size(); j++)
				if (cycle->getName() == _cycles[j]->getName())
				{
					found = true;
					start = _cycles[j]->getStart();
					break;
				}

			// Check if cycle is not existing already and add its colors
			if (!found)
			{
				// Compute cycle start
				start = _local ? _cursor : _cursor - (cycle->getEnd() - cycle->getStart()) - 1;

				// Add colors
				for (int j = cycle->getStart(); j <= cycle->getEnd(); j++)
					addColor(&(*colors)[_local ? j : cycle->getStart() + cycle->getEnd() - j], true);
			}
		}

		// Add cycle to the palette cycles list if it is not existing already
		if (!found)
		{
			_cycles.push_back(new Cycle());
			_cycles.back()->setName(cycle->getName());
			_cycles.back()->setStart(start);
			_cycles.back()->setEnd(cycle->getEnd() - cycle->getStart() + start);
			_cycles.back()->setDelay(cycle->getDelay());
			_cycles.back()->setForward(cycle->isForward());
		}

		// Add offset
		cycleOffsets.push_back((int16_t)start - (int16_t)cycle->getStart());
	}

	// Go through all pixels
	for (int x = 0; x < pixels.size(); x++)
		for (int y = 0; y < pixels[x].size(); y++)
		{
			// No operation needed if the pixel is transparent
			if (pixels[x][y] == 0 && paletteData->isTransparent())
				continue;

			// Check if pixel is present in areas
			bool foundArea = false;
			for (int i = 0; i < paletteData->getNumberOfAreas(); i++)
				if (pixels[x][y] >= paletteData->getArea(i)->getStart() && pixels[x][y] <= paletteData->getArea(i)->getEnd())
				{
					pixels[x][y] += areaOffsets[i];
					foundArea = true;
					break;
				}
			if (foundArea)
				continue;

			// Check if pixel is present in cycles
			bool foundCycle = false;
			for (int i = 0; i < paletteData->getNumberOfCycles(); i++)
				if (pixels[x][y] >= paletteData->getCycle(i)->getStart() && pixels[x][y] <= paletteData->getCycle(i)->getEnd())
				{
					pixels[x][y] += cycleOffsets[i];
					foundCycle = true;
					break;
				}
			if (foundCycle)
				continue;

			// Check if color already exists in palette
			Color *c = &((*colors)[pixels[x][y]]);
			int16_t found = findColor(c);
			if (found != -1)
			{
				pixels[x][y] = found;
				continue;
			}

			// Add color to the palette
			pixels[x][y] = addColor(c, false);
		}
}

Palette::~Palette()
{
	for (int i = 0; i < _areas.size(); i++)
		delete _areas[i];
	for (int i = 0; i < _cycles.size(); i++)
		delete _cycles[i];
}
