#include "Script.hpp"
#include "util/Log.hpp"
#include "util/XMLFile.hpp"
#include "grammar/Declaration.hpp"
#include "grammar/Function.hpp"

// External flex/bison declarations
extern FILE *yyin;
extern int yyparse(vector<Declaration *> &declarations, vector<Function *> &functions);
extern int yylineno;

Script::Script():
_description(""),
_scriptPath("")
{
}

void Script::load(string dirPath)
{
	Log::getInstance().write(LOG_INFO, "Script\n");
	Log::getInstance().indent();

	XMLFile xmlFile;
	xmlFile.open(dirPath + "script.xml");
	XMLNode *rootNode = xmlFile.getRootNode();

	_name = rootNode->getChild("name")->getStringContent();
	Log::getInstance().write(LOG_INFO, "name: %s\n", _name.c_str());

	_description = rootNode->getChild("description")->getStringContent();
	Log::getInstance().write(LOG_INFO, "description: %s\n", _description.c_str());

	_scriptPath = dirPath + rootNode->getChild("scriptName")->getStringContent();
	Log::getInstance().write(LOG_INFO, "scriptPath: %s\n", _scriptPath.c_str());

	Log::getInstance().unIndent();
}

void Script::parse(vector<Declaration *> &declarations, vector<Function *> &functions)
{
	Log::getInstance().write(LOG_INFO, "Parsing \"%s\"...\n", _scriptPath.c_str());

	yyin = fopen(_scriptPath.c_str(), "r");

	yylineno = 1;
	if (yyparse(declarations, functions))
	{
		fclose(yyin);
		for (int j = 0; j < functions.size(); j++)
			delete functions[j];
		Log::getInstance().write(LOG_ERROR, "Parsing error !\n");
	}
	
	fclose(yyin);
}

Script::~Script()
{
}
