#ifndef _IMAGE_HPP_
#define _IMAGE_HPP_

#include <string>
#include <vector>
using namespace std;

class Palette;

class Image
{
private:
	string _bitmapPath;
	vector<string> _zPlanePaths;
	uint8_t _paletteBaseIndex;
public:
	Image();
	void load(string dirPath, Palette *palette, bool global);
	string getBitmapPath() { return _bitmapPath; }
	uint16_t getNumberOfZPlanePaths() { return _zPlanePaths.size(); }
	string getZPlanePath(uint16_t index) { return _zPlanePaths[index]; }
	uint8_t getPaletteBaseIndex() { return _paletteBaseIndex; }
	~Image();
};

#endif
