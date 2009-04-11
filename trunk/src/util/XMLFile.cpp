#include "XMLFile.hpp"
#include <fstream>
#include <sstream>
#include <libxml/parser.h>
#include "Log.hpp"
using namespace std;

const uint8_t XMLFile::INDENT_WIDTH = 4;

XMLNode::XMLNode(string name, string content)
{
	_name = name;
	_content = content;
}

XMLNode::XMLNode(string name, int content)
{
	_name = name;
	ostringstream oss;
	oss << content;
	_content = oss.str();
}

XMLNode::XMLNode(string name, bool content)
{
	_name = name;
	_content = content ? "true" : "false";
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

XMLFile::XMLFile():
_rootNode(NULL)
{
	LIBXML_TEST_VERSION
}

void XMLFile::read(xmlNode *srcNode, XMLNode *&destNode)
{
	string content = "";
	if (srcNode->children != NULL && srcNode->children->content != NULL)
		content = (char *)srcNode->children->content;
	destNode = new XMLNode((char *)srcNode->name, content);

	for (xmlNode *childNode = srcNode->children; childNode != NULL; childNode = childNode->next)
		if (childNode->type == XML_ELEMENT_NODE)
		{
			XMLNode *node;
			read(childNode, node);
			destNode->addChild(node);
		}
}

void XMLFile::write(XMLNode *srcNode, xmlNode *&destNode, uint8_t indent)
{
	string space;

	// Create new node
	destNode = xmlNewNode(NULL, (const xmlChar *)srcNode->getName().c_str());
	xmlNode *childTextNode = xmlNewText((const xmlChar *)srcNode->getStringContent().c_str());
	xmlAddChild(destNode, childTextNode);

	for (int i = 0; i < srcNode->getNumberOfChildren(); i++)
	{
		// Add new line if the current child is not the last one
		space = "\n";
		for (int j = 0; j < (indent + 1) * INDENT_WIDTH; j++)
			space += ' ';
		childTextNode = xmlNewText((const xmlChar *)space.c_str());
		xmlAddChild(destNode, childTextNode);

		// Add child
		xmlNode *node;
		write(srcNode->getChild(i), node, indent + 1);
		node->type = XML_ELEMENT_NODE;
		xmlAddChild(destNode, node);
	}

	// Add new line if the node has children
	if (srcNode->getNumberOfChildren() > 0)
	{
		space = '\n';
		for (int i = 0; i < indent * INDENT_WIDTH; i++)
			space += ' ';
		childTextNode = xmlNewText((const xmlChar *)space.c_str());
		xmlAddChild(destNode, childTextNode);
	}
}

bool XMLFile::open(string fileName)
{
	// Check if file exists
	ifstream f(fileName.c_str(), ios::in);
	if (!f.is_open())
	{
		Log::write(LOG_WARNING, "Could not open file \"%s\" !\n", fileName.c_str());
		f.close();
		return false;
	}
	f.close();

	// Read XML file
	xmlDocPtr doc = xmlParseFile(fileName.c_str());

	// Read the root node and fill our own data types
	read(xmlDocGetRootElement(doc), _rootNode);

	xmlFreeDoc(doc);

	return true;
}

bool XMLFile::save(string fileName)
{
	// Check the root node is valid
	if (_rootNode == NULL)
	{
		Log::write(LOG_WARNING, "Root node has not been created !\n");
		return false;
	}

	// Create document and root node
	xmlDocPtr doc = xmlNewDoc((const xmlChar *)"1.0");
	xmlNode *rootNode;

	// Read our own data types and fill the root node
	write(_rootNode, rootNode, 0);
	xmlDocSetRootElement(doc, rootNode);

	// Write XML File
	if (xmlSaveFile(fileName.c_str(), doc) == -1)
	{
		Log::write(LOG_WARNING, "Could not open file \"%s\" for writing !\n", fileName.c_str());
		return false;
	}

	xmlFreeDoc(doc);

	return true;
}

XMLFile::~XMLFile()
{
	if (_rootNode != NULL)
		delete _rootNode;

	xmlCleanupParser();
}
