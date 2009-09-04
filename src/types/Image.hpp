#ifndef _IMAGE_HPP_
#define _IMAGE_HPP_

#include <string>
#include <vector>
using namespace std;

class Palette;

class Image
{
private:
	static const string XML_FILE_NAME;

	string _name;
	bool _transparent;
	string _bitmapPath;
	vector<string> _zPlanePaths;
	uint8_t _paletteBaseIndex;
public:
	Image();
	void load(string dirPath);
	void save(string dirPath);
	void setPalette(Palette *palette, bool global);
	string getName() { return _name; }
	bool isTransparent() { return _transparent; }
	string getBitmapPath() { return _bitmapPath; }
	uint16_t getNumberOfZPlanePaths() { return _zPlanePaths.size(); }
	string getZPlanePath(uint16_t index) { return _zPlanePaths[index]; }
	uint8_t getPaletteBaseIndex() { return _paletteBaseIndex; }
	~Image();
};

#endif
