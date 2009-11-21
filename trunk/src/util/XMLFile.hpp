#ifndef _XMLFILE_HPP_
#define _XMLFILE_HPP_

#include <libxml/tree.h>
#include <stdint.h>
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
	XMLNode(string name, string content = "");
	XMLNode(string name, int content);
	XMLNode(string name, bool content);
	uint32_t getNumberOfChildren() { return _children.size(); }
	XMLNode *getChild(uint32_t index) { return _children[index]; }
	XMLNode *getChild(string name, uint32_t index = 0);
	void addChild(XMLNode *child) { _children.push_back(child); }
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

	void read(xmlNode *srcNode, XMLNode *&destNode);
	void write(XMLNode *srcNode, xmlNode *&destNode, uint8_t indent);
public:
	XMLFile();
	bool open(string fileName);
	bool save(string fileName);
	XMLNode *getRootNode() { return _rootNode; }
	void setRootNode(XMLNode *rootNode) { _rootNode = rootNode; }
	~XMLFile();
};

#endif

