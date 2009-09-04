#include "Script.hpp"
#include "util/IO.hpp"
#include "util/Log.hpp"
#include "util/XMLFile.hpp"
#include "grammar/Declaration.hpp"
#include "grammar/Function.hpp"

const string Script::XML_FILE_NAME = "script.xml";

// External flex/bison declarations
extern FILE *yyin;
extern int yyparse(vector<Declaration *> &declarations, vector<Function *> &functions);
extern int yylex();
extern int yylineno;

Script::Script():
_scriptPath("")
{
}

void Script::load(string dirPath)
{
	Log::write(LOG_INFO, "Script\n");
	Log::indent();

	XMLFile xmlFile;
	xmlFile.open(dirPath + XML_FILE_NAME);
	XMLNode *rootNode = xmlFile.getRootNode();

	_name = rootNode->getChild("name")->getStringContent();
	Log::write(LOG_INFO, "name: %s\n", _name.c_str());

	_scriptPath = dirPath + rootNode->getChild("scriptName")->getStringContent();
	Log::write(LOG_INFO, "scriptPath: %s\n", _scriptPath.c_str());

	Log::unIndent();
}

void Script::save(string dirPath)
{
	Log::write(LOG_INFO, "Script\n");
	Log::indent();

	if (!IO::createDirectory(dirPath))
		Log::write(LOG_ERROR, "Could not create directory \"%s\" !\n", dirPath.c_str());

	XMLFile xmlFile;
	XMLNode *rootNode = new XMLNode("script");
	xmlFile.setRootNode(rootNode);

	rootNode->addChild(new XMLNode("name", _name));
	Log::write(LOG_INFO, "name: %s\n", _name.c_str());

	string scriptName = _scriptPath.substr(_scriptPath.find_last_of('/') + 1);
	rootNode->addChild(new XMLNode("scriptName", scriptName));
	string newScriptPath = dirPath + scriptName;
	if (_scriptPath != newScriptPath)
	{
		if (!IO::copyFile(_scriptPath, newScriptPath))
			Log::write(LOG_ERROR, "Could not copy file \"%s\" to \"%s\" !\n", _scriptPath.c_str(), newScriptPath.c_str());
		_scriptPath = newScriptPath;
	}
	Log::write(LOG_INFO, "scriptPath: %s\n", _scriptPath.c_str());

	if (!xmlFile.save(dirPath + XML_FILE_NAME))
		Log::write(LOG_ERROR, "Couldn't save script to the specified directory !\n");

	Log::unIndent();
}

void Script::parse(vector<Declaration *> &declarations, vector<Function *> &functions)
{
	Log::write(LOG_INFO, "Parsing \"%s\"...\n", _scriptPath.c_str());

	yyin = fopen(_scriptPath.c_str(), "r");

	yylineno = 1;
	if (yyparse(declarations, functions))
	{
		fclose(yyin);
		for (int j = 0; j < functions.size(); j++)
			delete functions[j];
		Log::write(LOG_ERROR, "Parsing error !\n");
	}
	else
		fclose(yyin);
}

Script::~Script()
{
}
