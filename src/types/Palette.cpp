#include "Palette.hpp"
#include "util/IO.hpp"
#include "util/Log.hpp"
#include "util/XMLFile.hpp"

const string Palette::XML_FILE_NAME = "palette.xml";
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

Cycle::Cycle():
_id(0),
_name(),
_start(0),
_end(0),
_delay(0),
_forward(true)
{}

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

Palette::Palette():
_transparentIndex(0),
_startCursor(0),
_endCursor(0)
{
}

void Palette::load(string dirPath)
{
	Log::write(LOG_INFO, "Palette\n");
	Log::indent();

	XMLFile xmlFile;
	xmlFile.open(dirPath + XML_FILE_NAME);
	XMLNode *rootNode = xmlFile.getRootNode();

	_transparentIndex = rootNode->getChild("transparentIndex")->getIntegerContent();
	Log::write(LOG_INFO, "transparentIndex: %u\n", _transparentIndex);

	int i = 0;
	XMLNode *child;
	while ((child = rootNode->getChild("cycle", i++)) != NULL)
	{
		Cycle *cycle = new Cycle();
		cycle->load(child);
		_cycles.push_back(cycle);
	}

	Log::unIndent();
}

void Palette::save(string dirPath)
{
	Log::write(LOG_INFO, "Palette\n");
	Log::indent();

	if (!IO::createDirectory(dirPath))
		Log::write(LOG_ERROR, "Could not create directory \"%s\" !\n", dirPath.c_str());

	XMLFile xmlFile;
	XMLNode *rootNode = new XMLNode("palette");
	xmlFile.setRootNode(rootNode);

	rootNode->addChild(new XMLNode("transparentIndex", _transparentIndex));
	Log::write(LOG_INFO, "transparentIndex: %u\n", _transparentIndex);

	for (int i = 0; i < _cycles.size(); i++)
	{
		XMLNode *child = new XMLNode("cycle");
		rootNode->addChild(child);
		_cycles[i]->save(child);
	}

	if (!xmlFile.save(dirPath + XML_FILE_NAME))
		Log::write(LOG_ERROR, "Couldn't save palette to the specified directory !\n");

	Log::unIndent();
}

void Palette::prepare()
{
	// Set cycles IDs
	for (int i = 0; i < _cycles.size(); i++)
		_cycles[i]->setID(i + 1);

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

	// Clear our optimization array
	_optimizable.clear();
	_optimizable.resize(MAX_COLORS);
}

void Palette::add(vector<Color> *colors, vector<vector<uint8_t> > &pixels, bool transparent, bool optimizable, bool fromStart)
{
	// If we don't need optimization, we just append colors to the palette
	if (!optimizable)
	{
		for (int i = transparent ? 1 : 0; i < colors->size(); i++)
		{
			if (_startCursor == _endCursor)
					Log::write(LOG_ERROR, "Palette contains too many colors !\n");

			if (fromStart)
			{
				_colors[_startCursor] = (*colors)[i];
				_optimizable[_startCursor] = false;
				_startCursor++;
			}
			else
			{
				_endCursor--;
				_colors[_endCursor] = (*colors)[colors->size() - 1 - i + (transparent ? 1 : 0)];
				_optimizable[_endCursor] = false;
				
			}
		}

		// Update pixels
		uint8_t paletteIndex = fromStart ? _startCursor - colors->size() + (transparent ? 1 : 0) : _endCursor;
		for (int x = 0; x < pixels.size(); x++)
			for (int y = 0; y < pixels[x].size(); y++)
				if (!transparent || pixels[x][y] != 0)
					pixels[x][y] += paletteIndex - (transparent ? 1 : 0);
	}
	else
	{
		Color c;
		bool found;
		for (int x = 0; x < pixels.size(); x++)
			for (int y = 0; y < pixels[x].size(); y++)
			{
				// If pixel is equal to 0 and the image is transparent, the pixel
				// should be kept as is and the palette should not be updated
				if (transparent && pixels[x][y] == 0)
					continue;

				// See if the color already exists and update pixel if needed,
				// otherwise append the color to the palette
				c = (*colors)[pixels[x][y]];
				found = false;
				if (fromStart)
				{
					for (int i = N_COMMON_COLORS; i < _startCursor; i++)
						if (_optimizable[i] && c.r == _colors[i].r && c.g == _colors[i].g && c.b == _colors[i].b)
						{
							pixels[x][y] = i;
							found = true;
							break;
						}
					if (!found)
					{
						if (_startCursor == _endCursor)
							Log::write(LOG_ERROR, "Palette contains too many colors !\n");

						_colors[_startCursor] = c;
						pixels[x][y] = _startCursor;
						_optimizable[_startCursor] = true;
						_startCursor++;
					}
				}
				else
				{
					for (int i = MAX_COLORS; i > _endCursor; i--)
						if (c.r == _colors[i - 1].r && c.g == _colors[i - 1].g && c.b == _colors[i - 1].b)
						{
							pixels[x][y] = i - 1;
							found = true;
							break;
						}
					if (!found)
					{
						if (_endCursor == _startCursor)
							Log::write(LOG_ERROR, "Palette contains too many colors !\n");

						_endCursor--;
						_colors[_endCursor] = c;
						pixels[x][y] = _endCursor;
						_optimizable[_endCursor] = true;
					}
				}
			}
	}
}

Palette::~Palette()
{
	for (int i = 0; i < _cycles.size(); i++)
		delete _cycles[i];
}
