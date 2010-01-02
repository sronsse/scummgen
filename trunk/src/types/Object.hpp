#ifndef _OBJECT_HPP_
#define _OBJECT_HPP_

#include <stdint.h>
#include <string>
#include <vector>
using namespace std;

class Image;
class Palette;
class PaletteData;
class Function;

class Object
{
private:
	static const string XML_FILE_NAME;
	static const uint8_t ACTOR_DIR_WEST;
	static const uint8_t ACTOR_DIR_EAST;
	static const uint8_t ACTOR_DIR_SOUTH;
	static const uint8_t ACTOR_DIR_NORTH;

	uint16_t _id;
	string _name;
	string _displayName;	
	vector<Image *> _images;
	int16_t _hotspotX;
	int16_t _hotspotY;
	uint16_t _x;
	uint16_t _y;
	uint16_t _width;
	uint16_t _height;
	uint8_t _actorDir;
	PaletteData *_paletteData;
	Function *_function;
public:
	Object();
	void load(string dirName);
	void save(string dirName);
	void prepare(Palette *palette);
	void compile();
	uint16_t getID() { return _id; }
	void setID(uint16_t id) { _id = id; }
	string getName() { return _name; }
	string getDisplayName() { return _displayName; }
	uint16_t getNumberOfImages() { return _images.size(); }
	Image *getImage(uint16_t index) { return _images[index]; }
	int16_t getHotspotX() { return _hotspotX; }
	int16_t getHotspotY() { return _hotspotY; }
	uint16_t getX() { return _x; }
	uint16_t getY() { return _y; }
	uint16_t getWidth() { return _width; }
	uint16_t getHeight() { return _height; }
	uint8_t getActorDir() { return _actorDir; }
	Function *getFunction() { return _function; }
	void setFunction(Function *function) { _function = function; }
	~Object();
};

#endif
