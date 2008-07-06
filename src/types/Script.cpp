#include "Script.hpp"
#include <fstream>
#include "util/Log.hpp"

const uint8_t Script::MIN_LOCAL_INDEX = 200;

// opcodes
const uint8_t Script::OC_PUSH_BYTE = 0x00;
const uint8_t Script::OC_PUSH_WORD = 0x01;
const uint8_t Script::OC_PUSH_BYTE_VAR = 0x02;
const uint8_t Script::OC_PUSH_WORD_VAR = 0x03;
const uint8_t Script::OC_BYTE_ARRAY_READ = 0x06;
const uint8_t Script::OC_WORD_ARRAY_READ = 0x07;
const uint8_t Script::OC_BYTE_ARRAY_INDEXED_READ = 0x0A;
const uint8_t Script::OC_WORD_ARRAY_INDEXED_READ = 0x0B;
const uint8_t Script::OC_DUP = 0x0C;
const uint8_t Script::OC_NOT = 0x0D;
const uint8_t Script::OC_EQ = 0x0E;
const uint8_t Script::OC_NEQ = 0x0F;
const uint8_t Script::OC_GT = 0x10;
const uint8_t Script::OC_LT = 0x11;
const uint8_t Script::OC_LE = 0x12;
const uint8_t Script::OC_GE = 0x13;
const uint8_t Script::OC_ADD = 0x14;
const uint8_t Script::OC_SUB = 0x15;
const uint8_t Script::OC_MUL = 0x16;
const uint8_t Script::OC_DIV = 0x17;
const uint8_t Script::OC_LAND = 0x18;
const uint8_t Script::OC_LOR = 0x19;
const uint8_t Script::OC_POP = 0x1A;
const uint8_t Script::OC_WRITE_BYTE_VAR = 0x42;
const uint8_t Script::OC_WRITE_WORD_VAR = 0x43;
const uint8_t Script::OC_BYTE_ARRAY_WRITE = 0x46;
const uint8_t Script::OC_WORD_ARRAY_WRITE = 0x47;
const uint8_t Script::OC_BYTE_ARRAY_INDEXED_WRITE = 0x4A;
const uint8_t Script::OC_WORD_ARRAY_INDEXED_WRITE = 0x4B;
const uint8_t Script::OC_BYTE_VAR_INC = 0x4E;
const uint8_t Script::OC_WORD_VAR_INC = 0x4F;
const uint8_t Script::OC_BYTE_ARRAY_INC = 0x52;
const uint8_t Script::OC_WORD_ARRAY_INC = 0x53;
const uint8_t Script::OC_BYTE_VAR_DEC = 0x56;
const uint8_t Script::OC_WORD_VAR_DEC = 0x57;
const uint8_t Script::OC_BYTE_ARRAY_DEC = 0x5A;
const uint8_t Script::OC_WORD_ARRAY_DEC = 0x5B;
const uint8_t Script::OC_IF = 0x5C;
const uint8_t Script::OC_IF_NOT = 0x5D;
const uint8_t Script::OC_START_SCRIPT = 0x5E;
const uint8_t Script::OC_START_SCRIPT_QUICK = 0x5F;
const uint8_t Script::OC_START_OBJECT = 0x60;
const uint8_t Script::OC_DRAW_OBJECT = 0x61;
const uint8_t Script::OC_DRAW_OBJECT_AT = 0x62;
const uint8_t Script::OC_DRAW_BLAST_OBJECT = 0x63;
const uint8_t Script::OC_SET_BLAST_OBJECT_WINDOW = 0x54;
const uint8_t Script::OC_STOP_OBJECT_CODE = 0x65;
const uint8_t Script::OC_END_CUTSCENE = 0x67;
const uint8_t Script::OC_CUTSCENE = 0x68;
const uint8_t Script::OC_STOP_MUSIC = 0x69;
const uint8_t Script::OC_FREEZE_UNFREEZE = 0x6A;
const uint8_t Script::OC_CURSOR_COMMAND = 0x6B;
	const uint8_t Script::SO_CURSOR_ON = 0x90;
	const uint8_t Script::SO_CURSOR_OFF = 0x91;
	const uint8_t Script::SO_USERPUT_ON = 0x92;
	const uint8_t Script::SO_USERPUT_OFF = 0x93;
	const uint8_t Script::SO_CURSOR_SOFT_ON = 0x94;
	const uint8_t Script::SO_CURSOR_SOFT_OFF = 0x95;
	const uint8_t Script::SO_USERPUT_SOFT_ON = 0x96;
	const uint8_t Script::SO_USERPUT_SOFT_OFF = 0x97;
	const uint8_t Script::SO_CURSOR_IMAGE = 0x99;
	const uint8_t Script::SO_CURSOR_HOTSPOT = 0x9A;
	const uint8_t Script::SO_CHARSET_SET = 0x9C;
	const uint8_t Script::SO_CHARSET_COLOR = 0x9D;
	const uint8_t Script::SO_CURSOR_TRANSPARENT = 0xD6;
const uint8_t Script::OC_BREAK_HERE = 0x6C;
const uint8_t Script::OC_IF_CLASS_OF_IS = 0x6D;
const uint8_t Script::OC_SET_CLASS = 0x6E;
const uint8_t Script::OC_GET_STATE = 0x6F;
const uint8_t Script::OC_SET_STATE = 0x70;
const uint8_t Script::OC_SET_OWNER = 0x71;
const uint8_t Script::OC_GET_OWNER = 0x72;
const uint8_t Script::OC_JUMP = 0x73;
const uint8_t Script::OC_START_SOUND = 0x74;
const uint8_t Script::OC_STOP_SOUND = 0x75;
const uint8_t Script::OC_STAR_MUSIC = 0x76;
const uint8_t Script::OC_STOP_OBJECT_SCRIPT = 0x77;
const uint8_t Script::OC_PAN_CAMERA_TO = 0x78;
const uint8_t Script::OC_ACTOR_FOLLOW_CAMERA = 0x79;
const uint8_t Script::OC_SET_CAMERA_AT = 0x7A;
const uint8_t Script::OC_LOAD_ROOM = 0x7B;
const uint8_t Script::OC_STOP_SCRIPT = 0x7C;
const uint8_t Script::OC_WALK_ACTOR_TO_OBJ = 0x7D;
const uint8_t Script::OC_WALK_ACTOR_TO = 0x7E;
const uint8_t Script::OC_PUT_ACTOR_AT_XY = 0x7F;
const uint8_t Script::OC_PUT_ACTOR_AT_OBJECT = 0x80;
const uint8_t Script::OC_FACE_ACTOR = 0x81;
const uint8_t Script::OC_ANIMATE_ACTOR = 0x82;
const uint8_t Script::OC_DO_SENTENCE = 0x83;
const uint8_t Script::OC_PICKUP_OBJECT = 0x84;
const uint8_t Script::OC_LOAD_ROOM_WITH_EGO = 0x85;
const uint8_t Script::OC_GET_RANDOM_NUMBER = 0x87;
const uint8_t Script::OC_GET_RANDOM_NUMBER_RANGE = 0x88;
const uint8_t Script::OC_GET_ACTOR_MOVING = 0x8A;
const uint8_t Script::OC_IS_SCRIPT_RUNNING = 0x8B;
const uint8_t Script::OC_GET_ACTOR_ROOM = 0x8C;
const uint8_t Script::OC_GET_OBJECT_X = 0x8D;
const uint8_t Script::OC_GET_OBJECT_Y = 0x8E;
const uint8_t Script::OC_GET_OBJECT_OLD_DIR = 0x8F;
const uint8_t Script::OC_GET_ACTOR_WALK_BOX = 0x90;
const uint8_t Script::OC_GET_ACTOR_COSTUME = 0x91;
const uint8_t Script::OC_FIND_INVENTORY = 0x92;
const uint8_t Script::OC_GET_INVENTORY_COUNT = 0x93;
const uint8_t Script::OC_GET_VERB_FROM_XY = 0x94;
const uint8_t Script::OC_BEGIN_OVERRIDE = 0x95;
const uint8_t Script::OC_END_OVERRIDE = 0x96;
const uint8_t Script::OC_SET_OBJECT_NAME = 0x97;
const uint8_t Script::OC_IS_SOUND_RUNNING = 0x98;
const uint8_t Script::OC_SET_BOX_FLAGS = 0x99;
const uint8_t Script::OC_CREATE_BOX_MATRIX = 0x9A;
const uint8_t Script::OC_RESOURCE_ROUTINES = 0x9B;
	const uint8_t Script::SO_LOAD_SCRIPT = 0x64;
	const uint8_t Script::SO_LOAD_SOUND = 0x65;
	const uint8_t Script::SO_LOAD_COSTUME = 0x66;
	const uint8_t Script::SO_LOAD_ROOM = 0x67;
	const uint8_t Script::SO_NUKE_SCRIPT = 0x68;
	const uint8_t Script::SO_NUKE_SOUND = 0x69;
	const uint8_t Script::SO_NUKE_COSTUME = 0x6A;
	const uint8_t Script::SO_NUKE_ROOM = 0x6B;
	const uint8_t Script::SO_LOCK_SCRIPT = 0x6C;
	const uint8_t Script::SO_LOCK_SOUND = 0x6D;
	const uint8_t Script::SO_LOCK_COSTUME = 0x6E;
	const uint8_t Script::SO_LOCK_ROOM = 0x6F;
	const uint8_t Script::SO_UNLOCK_SCRIPT = 0x70;
	const uint8_t Script::SO_UNLOCK_SOUND = 0x71;
	const uint8_t Script::SO_UNLOCK_COSTUME = 0x72;
	const uint8_t Script::SO_UNLOCK_ROOM = 0x73;
	const uint8_t Script::SO_CLEAR_HEAP = 0x74;
	const uint8_t Script::SO_LOAD_CHARSET = 0x75;
	const uint8_t Script::SO_NUKE_CHARSET = 0x76;
	const uint8_t Script::SO_LOAD_OBJECT = 0x77;
const uint8_t Script::OC_ROOM_OPS = 0x9C;
	const uint8_t Script::SO_ROOM_SCROLL = 0xAC;
	const uint8_t Script::SO_ROOM_SCREEN = 0xAE;
	const uint8_t Script::SO_ROOM_PALETTE = 0xAF;
	const uint8_t Script::SO_ROOM_SHAKE_ON = 0xB0;
	const uint8_t Script::SO_ROOM_SHAKE_OFF = 0xB1;
	const uint8_t Script::SO_ROOM_INTENSITY = 0xB3;
	const uint8_t Script::SO_ROOM_SAVE_GAME = 0xB4;
	const uint8_t Script::SO_ROOM_FADE = 0xB5;
	const uint8_t Script::SO_RGB_ROOM_INTENSITY = 0xB6;
	const uint8_t Script::SO_ROOM_SHADOW = 0xB7;
	const uint8_t Script::SO_ROOM_TRANSFORM = 0xBA;
	const uint8_t Script::SO_CYCLE_SPEED = 0xBB;
	const uint8_t Script::SO_ROOM_NEW_PALETTE = 0xD5;
const uint8_t Script::OC_ACTOR_OPS = 0x9D;
	const uint8_t Script::SO_ACTOR_SET_CURRENT = 0xC5;
	const uint8_t Script::SO_COSTUME = 0x4C;
	const uint8_t Script::SO_STEP_DIST = 0x4D;
	const uint8_t Script::SO_SOUND = 0x4E;
	const uint8_t Script::SO_WALK_ANIMATION = 0x4F;
	const uint8_t Script::SO_TALK_ANIMATION = 0x50;
	const uint8_t Script::SO_STAND_ANIMATION = 0x51;
	const uint8_t Script::SO_DEFAULT = 0x53;
	const uint8_t Script::SO_ELEVATION = 0x54;
	const uint8_t Script::SO_ANIMATION_DEFAULT = 0x55;
	const uint8_t Script::SO_PALETTE = 0x56;
	const uint8_t Script::SO_TALK_COLOR = 0x57;
	const uint8_t Script::SO_ACTOR_NAME = 0x58;
	const uint8_t Script::SO_INIT_ANIMATION = 0x59;
	const uint8_t Script::SO_ACTOR_WIDTH = 0x5B;
	const uint8_t Script::SO_SCALE = 0x5C;
	const uint8_t Script::SO_NEVER_ZCLIP = 0x5D;
	const uint8_t Script::SO_ALWAYS_ZCLIP = 0x5E;
	const uint8_t Script::SO_IGNORE_BOXES = 0x5F;
	const uint8_t Script::SO_FOLLOW_BOXES = 0x60;
	const uint8_t Script::SO_ANIMATION_SPEED = 0x61;
	const uint8_t Script::SO_SHADOW = 0x62;
	const uint8_t Script::SO_TEXT_OFFSET = 0x63;
	const uint8_t Script::SO_ACTOR_VARIABLE = 0xC6;
	const uint8_t Script::SO_ACTOR_IGNORE_TURNS_ON = 0xD7;
	const uint8_t Script::SO_ACTOR_IGNORE_TURNS_OFF = 0xD8;
	const uint8_t Script::SO_ACTOR_NEW = 0xD9;
	const uint8_t Script::SO_ACTOR_DEPTH = 0xE3;
	const uint8_t Script::SO_ACTOR_WALK_SCRIPT = 0xE4;
	const uint8_t Script::SO_ACTOR_STOP = 0xE5;
	const uint8_t Script::SO_ACTOR_SET_DIRECTION = 0xE6;
	const uint8_t Script::SO_ACTOR_TURN_TO_DIRECTION = 0xE7;
	const uint8_t Script::SO_ACTOR_WALK_PAUSE = 0xE9;
	const uint8_t Script::SO_ACTOR_WALK_RESUME = 0xEA;
	const uint8_t Script::SO_ACTOR_TALK_SCRIPT = 0xEB;
const uint8_t Script::OC_VERB_OPS = 0x9E;
	const uint8_t Script::SO_VERB_SET_CURRENT = 0xC4;
	const uint8_t Script::SO_VERB_IMAGE = 0x7C;
	const uint8_t Script::SO_VERB_NAME = 0x7D;
	const uint8_t Script::SO_VERB_COLOR = 0x7E;
	const uint8_t Script::SO_VERB_HICOLOR = 0x7F;
	const uint8_t Script::SO_VERB_AT = 0x80;
	const uint8_t Script::SO_VERB_ON = 0x81;
	const uint8_t Script::SO_VERB_OFF = 0x82;
	const uint8_t Script::SO_VERB_DELETE = 0x83;
	const uint8_t Script::SO_VERB_NEW = 0x84;
	const uint8_t Script::SO_VERB_DIMCOLOR = 0x85;
	const uint8_t Script::SO_VERB_DIM = 0x86;
	const uint8_t Script::SO_VERB_KEY = 0x87;
	const uint8_t Script::SO_VERB_CENTER = 0x88;
	const uint8_t Script::SO_VERB_NAME_STR = 0x89;
	const uint8_t Script::SO_VERB_IMAGE_IN_ROOM = 0x8B;
	const uint8_t Script::SO_VERB_BACKCOLOR = 0x8C;
	const uint8_t Script::SO_VERB_DRAW = 0xFF;
const uint8_t Script::OC_GET_ACTOR_FROM_XY = 0x9F;
const uint8_t Script::OC_FIND_OBJECT = 0xA0;
const uint8_t Script::OC_PSEUDO_ROOM = 0xA1;
const uint8_t Script::OC_GET_ACTOR_ELEVATION = 0xA2;
const uint8_t Script::OC_GET_VERB_ENTRY_POINT = 0xA3;
const uint8_t Script::OC_ARRAY_OPS = 0xA4;
	const uint8_t Script::SO_ASSIGN_STRING = 0xCD;
	const uint8_t Script::SO_ASSIGN_INT_LIST = 0xD0;
	const uint8_t Script::SO_ASSIGN_2DIM_LIST = 0xD4;
const uint8_t Script::OC_SAVE_RESTORE_VERBS = 0xA5;
	const uint8_t Script::SO_SAVE_VERBS = 0x8D;
	const uint8_t Script::SO_RESTORE_VERBS = 0x8E;
	const uint8_t Script::SO_DELETE_VERBS = 0x8F;
const uint8_t Script::OC_DRAW_BOX = 0xA6;
const uint8_t Script::OC_GET_ACTOR_WIDTH = 0xA8;
const uint8_t Script::OC_WAIT = 0xA9;
	const uint8_t Script::SO_WAIT_FOR_ACTOR = 0xA8;
	const uint8_t Script::SO_WAIT_FOR_MESSAGE = 0xA9;
	const uint8_t Script::SO_WAIT_FOR_CAMERA = 0xAA;
	const uint8_t Script::SO_WAIT_FOR_SENTENCE = 0xAB;
	const uint8_t Script::SO_WAIT_FOR_ANIMATION = 0xE2;
	const uint8_t Script::SO_WAIT_FOR_TURN = 0xE8;
const uint8_t Script::OC_GET_ACTOR_SCALE_X = 0xAA;
const uint8_t Script::OC_GET_ACTOR_ANIM_COUNTER = 0xAB;
const uint8_t Script::OC_SOUND_KLUDGE = 0xAC;
const uint8_t Script::OC_IS_ANY_OF = 0xAD;
const uint8_t Script::OC_SYSTEM_OPS = 0xAE;
	const uint8_t Script::SO_RESTART = 0x9E;
	const uint8_t Script::SO_PAUSE = 0x9F;
	const uint8_t Script::SO_QUIT = 0xA0;
const uint8_t Script::OC_IS_ACTOR_IN_BOX = 0xAF;
const uint8_t Script::OC_DELAY = 0xB0;
const uint8_t Script::OC_DELAY_SECONDS = 0xB1;
const uint8_t Script::OC_DELAY_MINUTES = 0xB2;
const uint8_t Script::OC_STOP_SENTENCE = 0xB3;
const uint8_t Script::OC_PRINT_LINE = 0xB4;
const uint8_t Script::OC_PRINT_TEXT = 0xB5;
const uint8_t Script::OC_PRINT_DEBUG = 0xB6;
const uint8_t Script::OC_PRINT_SYSTEM = 0xB7;
const uint8_t Script::OC_PRINT_ACTOR = 0xB8;
const uint8_t Script::OC_PRINT_EGO = 0xB9;
	const uint8_t Script::SO_AT = 0x41;
	const uint8_t Script::SO_COLOR = 0x42;
	const uint8_t Script::SO_CLIPPED = 0x43;
	const uint8_t Script::SO_CENTER = 0x45;
	const uint8_t Script::SO_LEFT = 0x47;
	const uint8_t Script::SO_OVERHEAD = 0x48;
	const uint8_t Script::SO_MUMBLE = 0x4A;
	const uint8_t Script::SO_TEXTSTRING = 0x4B;
	const uint8_t Script::SO_LOAD_DEFAULT = 0xFE;
	const uint8_t Script::SO_SAVE_DEFAULT = 0xFF;
const uint8_t Script::OC_TALK_ACTOR = 0xBA;
const uint8_t Script::OC_TALK_EGO = 0xBB;
const uint8_t Script::OC_DIM_ARRAY = 0xBC;
const uint8_t Script::OC_DUMMY = 0xBD;
const uint8_t Script::OC_START_OBJECT_QUICK = 0xBE;
const uint8_t Script::OC_START_SCRIPT_QUICK_2 = 0xBF;
const uint8_t Script::OC_DIM_2_DIM_ARRAY = 0xC0;
		const uint8_t Script::SO_INT_ARRAY = 0xC7;
		const uint8_t Script::SO_BIT_ARRAY = 0xC8;
		const uint8_t Script::SO_NIBBLE_ARRAY = 0xC9;
		const uint8_t Script::SO_BYTE_ARRAY = 0xCA;
		const uint8_t Script::SO_STRING_ARRAY = 0xCB;
		const uint8_t Script::SO_UNDIM_ARRAY = 0xCC;
const uint8_t Script::OC_ABS = 0xC4;
const uint8_t Script::OC_DIST_OBJECT_OBJECT = 0xC5;
const uint8_t Script::OC_DIST_OBJECT_PT = 0xC6;
const uint8_t Script::OC_DIST_PT_PT = 0xC7;
const uint8_t Script::OC_KERNEL_GET_FUNCTIONS = 0xC8;
const uint8_t Script::OC_KERNEL_SET_FUNCTIONS = 0xC9;
const uint8_t Script::OC_DELAY_FRAMES = 0xCA;
const uint8_t Script::OC_PICK_ONE_OF = 0xCB;
const uint8_t Script::OC_PICK_ONE_OF_DEFAULT = 0xCC;
const uint8_t Script::OC_STAMP_OBJECT = 0xCD;
const uint8_t Script::OC_GET_DATE_TIME = 0xD0;
const uint8_t Script::OC_STOP_TALKING = 0xD1;
const uint8_t Script::OC_GET_ANIMATE_VARIABLE = 0xD2;
const uint8_t Script::OC_SHUFFLE = 0xD4;
const uint8_t Script::OC_JUMP_TO_SCRIPT = 0xD5;
const uint8_t Script::OC_BAND = 0xD6;
const uint8_t Script::OC_BOR = 0xD7;
const uint8_t Script::OC_IS_ROOM_SCRIPT_RUNNING = 0xD8;
const uint8_t Script::OC_FIND_ALL_OBJECTS = 0xDD;
const uint8_t Script::OC_GET_PIXEL = 0xE1;
const uint8_t Script::OC_PICK_VAR_RANDOM = 0xE3;
const uint8_t Script::OC_SET_BOX_SET = 0xE4;
const uint8_t Script::OC_GET_ACTOR_LAYER = 0xEC;
const uint8_t Script::OC_GET_OBJECT_NEW_DIR = 0xED;

vector<Script *> Script::_globalScriptsInstances;
vector<Script *> Script::_localScriptsInstances;

const string Script::EXTENSION = ".sgc";

Script *Script::getInstanceFromName(string scriptName)
{
	for (int i = 0; i < _globalScriptsInstances.size(); i++)
		if (_globalScriptsInstances[i]->getName() == scriptName)
			return _globalScriptsInstances[i];
	for (int i = 0; i < _localScriptsInstances.size(); i++)
		if (_localScriptsInstances[i]->getName() == scriptName)
			return _localScriptsInstances[i];
	return NULL;
}

Script::Script(string fileName, ScriptType type)
{
	Log::getInstance().write("Script\n");
	Log::getInstance().indent();

	int posB = fileName.find_last_of('.') - 1;
	int posA = fileName.find_last_of('/') + 1;
	_name = fileName.substr(posA, posB + 1 - posA);
	Log::getInstance().write("name: %s\n", _name.c_str());

	switch (type)
	{
		case TYPE_GLOBAL:
			Log::getInstance().write("type: global\n");
			_globalScriptsInstances.push_back(this);
			_id = _globalScriptsInstances.size();
			Log::getInstance().write("id: %u\n", _id);
			break;
		case TYPE_LOCAL:
			Log::getInstance().write("type: local\n");
			_localScriptsInstances.push_back(this);
			_id = _localScriptsInstances.size() - 1 + MIN_LOCAL_INDEX;
			Log::getInstance().write("id: %u\n", _id);
			if (_id == 200)
			{
				asm_printDebug();
				asm_print_textstring("This is a message hard-coded into the resource file created by ScummGEN");

				asm_pushByte(1);
				asm_delaySeconds();

				asm_printSystem();
				asm_print_textstring("Cool effect isn't it ? Now, shake it baby ! ;)");
				
				asm_roomOps();
				asm_roomOps_roomShakeOn();

				asm_pushByte(2);
				asm_delaySeconds();

				asm_roomOps();
				asm_roomOps_roomShakeOff();

				asm_pushByte(1);
				asm_resourceRoutines();
				asm_resourceRoutines_loadCostume();

				asm_pushByte(1);
				asm_actorOps();
				asm_actorOps_actorSetCurrent();

				asm_pushByte(1);
				asm_actorOps();
				asm_actorOps_default();

				asm_pushByte(1);
				asm_actorOps();
				asm_actorOps_costume();

				asm_actorOps();
				asm_actorOps_ignoreBoxes();

				asm_pushByte(60);
				asm_actorOps();
				asm_actorOps_animationSpeed();

				asm_pushByte(1);
				asm_pushByte(50);
				asm_pushByte(75);
				asm_pushByte(1);
				asm_putActorAtXY();

				asm_pushByte(10);
				asm_delaySeconds();

				asm_systemOps();
				asm_systemOps_pause();

				asm_systemOps();
				asm_systemOps_restart();
			}
			break;
		case TYPE_OTHER:
		default:
			_id = 0; // unused
			Log::getInstance().write("type: other\n");
	}

	Log::getInstance().unIndent();
}

void Script::writeByte(uint8_t byte)
{
	_bytes.push_back(byte);
}

void Script::writeWord(uint16_t word)
{
	_bytes.push_back(word);
	_bytes.push_back(word >> 8);
}

void Script::writeString(string s)
{
	for (int i = 0; i < s.length(); i++)
		writeByte(s[i]);
	writeByte(0);
}

Script::~Script()
{
}

