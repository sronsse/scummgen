#ifndef _OBJECT_HPP_
#define _OBJECT_HPP_

#include <stdint.h>
#include <string>
#include <vector>
using namespace std;

class Image;
class Script;

class Object
{
private:
	string _name;
	uint32_t _nImages;
	vector<Image *> _images;
	uint32_t _x;
	uint32_t _y;
	uint32_t _width;
	uint32_t _height;
	uint32_t _hotSpotX;
	uint32_t _hotSpotY;
	uint16_t _id;
	uint8_t _parent;
	uint8_t _parentState;
	string _displayName;
	Script *_script;
	uint32_t _classData;
public:
	Object(string dirName, uint32_t nZPlanes);
	string getName() { return _name; }
	uint32_t getNumberOfImages() { return _nImages; }
	Image *getImage(uint8_t index) { return _images[index]; }
	uint32_t getX() { return _x; }
	uint32_t getY() { return _y; }
	uint32_t getWidth() { return _width; }
	uint32_t getHeight() { return _height; }
	uint32_t getHotSpotX() { return _hotSpotX; }
	uint32_t getHotSpotY() { return _hotSpotY; }
	uint16_t getID() { return _id; }
	uint8_t getParent() { return _parent; }
	uint8_t getParentState() { return _parentState; }
	string getDisplayName() { return _displayName; }
	Script *getScript() { return _script; }
	uint32_t getClassData() { return _classData; }

	//tmp
	int getFlags() { return 0; }
	int getWalkX() { return 0; }
	int getWalkY() { return 0; }
	int getActorDir() { return 0; }
	int getNumberOfZPlanesPerImage() { return 0; }
	int getImageX() { return 0; }
	int getImageY() { return 0; }
	~Object();
};

#endif

