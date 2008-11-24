#include "XMLFile.hpp"
#include <fstream>
#include <libxml/parser.h>
#include "Log.hpp"
using namespace std;

XMLNode::XMLNode(string name, string content)
{
	_name = name;
	_content = content;
}

XMLNode *XMLNode::getChild(string name)
{
	for (int i = 0; i < _children.size(); i++)
		if (name == _children[i]->getName())
			return _children[i];

	return NULL;
}

XMLNode *XMLNode::getChild(string name, uint32_t index)
{
	uint32_t childIndex = 0;
	for (int i = 0; i < _children.size(); i++)
		if (name == _children[i]->getName() && childIndex++ == index)
			return _children[i];

	return NULL;
}

XMLNode::~XMLNode()
{
	for (int i = 0; i < _children.size(); i++)
		delete _children[i];
}

XMLFile::XMLFile()
{
	_rootNode = NULL;
}

bool XMLFile::open(string fileName)
{
	LIBXML_TEST_VERSION

	// Check if file exists
	ifstream f(fileName.c_str(), ios::in);
	if (!f.is_open())
	{
		Log::getInstance().write(LOG_WARNING, "Cannot open file \"%s\" !\n", fileName.c_str());
		return false;
	}
	f.close();

	xmlDocPtr doc = xmlParseFile(fileName.c_str());
	if (doc == NULL)
	{
		xmlCleanupParser();
		return false;
	}

	xmlNode *rootNode = xmlDocGetRootElement(doc);

	// Parsing the root node and filling our own data types
	parse(_rootNode, rootNode);

	xmlFreeDoc(doc);

	xmlCleanupParser();
	return true;
}

void XMLFile::parse(XMLNode *&destNode, xmlNode *srcNode)
{
	xmlChar *content = xmlNodeGetContent(srcNode);
	destNode = new XMLNode((char *)srcNode->name, (char *)content);
	xmlFree(content);

	xmlNode *childNode;
	for (childNode = srcNode->children; childNode != NULL; childNode = childNode->next)
		if (childNode->type == XML_ELEMENT_NODE)
		{
			XMLNode *node;
			parse(node, childNode);
			destNode->addChild(node);	
		}
}

XMLFile::~XMLFile()
{
	delete _rootNode;
}

