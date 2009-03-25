#ifndef _SCRIPT_HPP_
#define _SCRIPT_HPP_

#include <stdint.h>
#include <string>
#include <vector>
using namespace std;

class Declaration;
class Function;

class Script
{
private:
	string _name;
	string _description;
	string _scriptPath;
public:
	Script();
	void load(string dirPath);
	void parse(vector<Declaration *> &declarations, vector<Function *> &functions);
	string getName() { return _name; }
	string getDescription() { return _description; }
	string getScriptPath() { return _scriptPath; }
	~Script();
};

#endif
