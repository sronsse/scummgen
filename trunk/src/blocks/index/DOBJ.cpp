#include "DOBJ.hpp"
#include "util/IO.hpp"
#include "types/Game.hpp"
#include "types/Room.hpp"
#include "types/Object.hpp"

const uint8_t DOBJ::N_CHARS = 40;

DOBJ::DOBJ(Game *game)
{
	/*_nObjects = 1;
	for (int i = 0; i < game->getNumberOfRooms(); i++)
		for (int j = 0; j < game->getRoom(i)->getNumberOfObjects(); j++)
			if (game->getRoom(i)->getObject(j)->getID() + 1 > _nObjects)
				_nObjects = game->getRoom(i)->getObject(j)->getID() + 1;
	for (int i = 0; i < _nObjects; i++)
	{
		string objectName = "";
		objectName.resize(N_CHARS, '\0');
		_objectNames.push_back(objectName);
		_objectStates.push_back(0);
		_objectRooms.push_back(0);
		_classData.push_back(0);
	}
	for (int i = 0; i < game->getNumberOfRooms(); i++)
		for (int j = 0; j < game->getRoom(i)->getNumberOfObjects(); j++)
		{
			_objectNames[game->getRoom(i)->getObject(j)->getID()] = game->getRoom(i)->getObject(j)->getName();
			_objectNames[game->getRoom(i)->getObject(j)->getID()].resize(N_CHARS, '\0');
			_objectStates[game->getRoom(i)->getObject(j)->getID()] = game->getRoom(i)->getObject(j)->getParentState();
			_objectRooms[game->getRoom(i)->getObject(j)->getID()] = game->getRoom(i)->getID();
			_classData[game->getRoom(i)->getObject(j)->getID()] = game->getRoom(i)->getObject(j)->getClassData();
		}*/
}

uint32_t DOBJ::getSize()
{
	/*uint32_t size = 0;
	size += 4 * sizeof(uint8_t); // identifier
	size += sizeof(uint32_t); // size
	size += sizeof(uint32_t); // nObjects
	size += _nObjects * N_CHARS * sizeof(uint8_t); // objectNames
	size += _nObjects * sizeof(uint8_t); // objectStates
	size += _nObjects * sizeof(uint8_t); // objectRooms
	size += _nObjects * sizeof(uint32_t); // classData
	return size;*/
	return 0;
}

void DOBJ::write(ofstream &f)
{
	/*IO::writeString(f, "DOBJ");
	IO::writeU32BE(f, getSize());
	IO::writeU32LE(f, _nObjects);
	for (int i = 0; i < _nObjects; i++)
	{
		IO::writeString(f, _objectNames[i]);
		IO::writeU8(f, _objectStates[i]);
		IO::writeU8(f, _objectRooms[i]);
		IO::writeU32LE(f, _classData[i]);
	}*/
}

DOBJ::~DOBJ()
{
}

