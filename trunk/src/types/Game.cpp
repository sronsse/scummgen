#include "Game.hpp"
#include "util/IO.hpp"
#include "util/Log.hpp"
#include "util/XMLFile.hpp"
#include "Room.hpp"
#include "Script.hpp"
#include "Charset.hpp"
#include "Voice.hpp"

Game::Game(string dirName)
{
	Log::getInstance().write("Game\n");
	Log::getInstance().indent();

	XMLFile xmlFile(dirName + "game.xml");
	XMLNode *node = xmlFile.getRootNode();

	_longName = node->getChild("longName")->getStringContent();
	Log::getInstance().write("longName: %s\n", _longName.c_str());

	_shortName = node->getChild("shortName")->getStringContent();
	Log::getInstance().write("shortName: %s\n", _shortName.c_str());

	loadRooms(dirName + "rooms/");
	loadScripts(dirName + "scripts/");
	loadCharsets(dirName + "charsets/");
	loadVoices(dirName + "voices/");

	Log::getInstance().unIndent();
}

void Game::loadRooms(string dirName)
{
	XMLFile xmlFile(dirName + "rooms.xml");
	XMLNode *node = xmlFile.getRootNode();

	if (node == NULL)
		return;

	int i = 0;
	XMLNode *child;
	while ((child = node->getChild("room", i++)) != NULL)
		_rooms.push_back(new Room(dirName + child->getStringContent() + "/"));
}

void Game::loadScripts(string dirName)
{
	XMLFile xmlFile(dirName + "scripts.xml");
	XMLNode *node = xmlFile.getRootNode();

	if (node == NULL)
		return;

	int i = 0;
	XMLNode *child;
	while ((child = node->getChild("script", i++)) != NULL)
		_scripts.push_back(new Script(dirName + child->getStringContent() + Script::EXTENSION));
}

void Game::loadCharsets(string dirName)
{
	XMLFile xmlFile(dirName + "charsets.xml");
	XMLNode *node = xmlFile.getRootNode();

	if (node == NULL)
		return;

	int i = 0;
	XMLNode *child;
	while ((child = node->getChild("charset", i++)) != NULL)
		_charsets.push_back(new Charset(dirName + child->getStringContent() + "/"));
}

void Game::loadVoices(string dirName)
{
	XMLFile xmlFile(dirName + "voices.xml");
	XMLNode *node = xmlFile.getRootNode();

	if (node == NULL)
		return;

	int i = 0;
	XMLNode *child;
	while ((child = node->getChild("voice", i++)) != NULL)
		_voices.push_back(new Voice(dirName + child->getStringContent() + "/"));
}

Game::~Game()
{
	for (int i = 0; i < _rooms.size(); i++)
		delete _rooms[i];
	for (int i = 0; i < _scripts.size(); i++)
		delete _scripts[i];
	for (int i = 0; i < _charsets.size(); i++)
		delete _charsets[i];
	for (int i = 0; i < _voices.size(); i++)
		delete _voices[i];
}

