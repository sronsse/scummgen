#include "Game.hpp"
#include "util/IO.hpp"
#include "util/Log.hpp"
#include "util/XMLFile.hpp"
#include "Room.hpp"

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

	uint8_t nRooms = node->getChild("nRooms")->getIntegerContent();
	Log::getInstance().write("nRooms: %u\n", nRooms);

	for (int i = 0; i < nRooms; i++)
		_rooms.push_back(new Room(dirName + "rooms/room_" + IO::getStringFromIndex(i, 3) + "/"));

	Log::getInstance().unIndent();
}

Game::~Game()
{
	for (int i = 0; i < _rooms.size(); i++)
		delete _rooms[i];
}

