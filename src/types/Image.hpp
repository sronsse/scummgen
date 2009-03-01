#ifndef _IMAGE_HPP_
#define _IMAGE_HPP_

#include <string>
#include <vector>
using namespace std;

class Image
{
private:
	string _bitmapPath;
	vector<string> _zPlanePaths;
public:
	Image();
	void load(string dirPath);
	string getBitmapPath() { return _bitmapPath; }
	uint16_t getNumberOfZPlanePaths() { return _zPlanePaths.size(); }
	string getZPlanePath(uint16_t index) { return _zPlanePaths[index]; }
	~Image();
};

#endif
