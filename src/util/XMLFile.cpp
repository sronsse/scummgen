#include "XMLFile.hpp"
#include <libxml/parser.h>

XMLNode::XMLNode(string name, string content):
_name(name),
_content(content)
{
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
		delete _children.at(i);
}

XMLFile::XMLFile(string fileName):
_rootNode(NULL)
{
	LIBXML_TEST_VERSION

	xmlDocPtr doc = xmlParseFile(fileName.c_str());
	if (doc == NULL)
		return;

	xmlNode *rootNode = xmlDocGetRootElement(doc);
	if (!rootNode || !rootNode->name) 
	{
     	xmlFreeDoc(doc);
		return;
	}

	// Parsing the root node and filling our own data types
	parse(_rootNode, rootNode);

	xmlFreeDoc(doc);

	xmlCleanupParser();
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

