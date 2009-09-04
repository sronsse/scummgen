#ifndef _SCRIPT_HPP_
#define _SCRIPT_HPP_

#include <sstream>
#include <stdint.h>
#include <string>
#include <vector>
using namespace std;

class Declaration;
class Function;

class Script
{
private:
	static const string XML_FILE_NAME;

	string _name;
	string _scriptPath;
public:
	Script();
	void load(string dirPath);
	void save(string dirPath);
	void parse(vector<Declaration *> &declarations, vector<Function *> &functions);
	string getName() { return _name; }
	string getScriptPath() { return _scriptPath; }
	~Script();
};

#endif
