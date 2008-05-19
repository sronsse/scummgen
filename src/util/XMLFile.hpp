#ifndef _XMLFILE_HPP_
#define _XMLFILE_HPP_

#include <libxml/tree.h>
#include <string>
#include <vector>
using namespace std;

class XMLNode
{
private:
	string _name;
	string _content;
	vector<XMLNode *> _children;
public:
	XMLNode(string name, string content);
	void addChild(XMLNode *child) { _children.push_back(child); }
	XMLNode *getChild(string name);
	XMLNode *getChild(string name, uint32_t index);
	string getName() { return _name; }
	string getStringContent() { return _content; }
	int getIntegerContent() { return atoi(_content.c_str()); }
	bool getBooleanContent() { return (_content == "true"); }
	~XMLNode();
};

class XMLFile
{
private:
	XMLNode *_rootNode;

	void parse(XMLNode *&destNode, xmlNode *srcNode);
public:
	XMLFile(string fileName);
	XMLNode *getRootNode() { return _rootNode; }
	~XMLFile();
};

#endif

