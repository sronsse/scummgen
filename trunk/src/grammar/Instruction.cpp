#include "Instruction.hpp"
#include <sstream>
#include "util/Log.hpp"
#include "Context.hpp"

// Opcodes list
const uint8_t Instruction::OC_PUSH_BYTE = 0x00;
const uint8_t Instruction::OC_PUSH_WORD = 0x01;
const uint8_t Instruction::OC_PUSH_BYTE_VAR = 0x02;
const uint8_t Instruction::OC_PUSH_WORD_VAR = 0x03;
const uint8_t Instruction::OC_BYTE_ARRAY_READ = 0x06;
const uint8_t Instruction::OC_WORD_ARRAY_READ = 0x07;
const uint8_t Instruction::OC_BYTE_ARRAY_INDEXED_READ = 0x0A;
const uint8_t Instruction::OC_WORD_ARRAY_INDEXED_READ = 0x0B;
const uint8_t Instruction::OC_DUP = 0x0C;
const uint8_t Instruction::OC_NOT = 0x0D;
const uint8_t Instruction::OC_EQ = 0x0E;
const uint8_t Instruction::OC_NEQ = 0x0F;
const uint8_t Instruction::OC_GT = 0x10;
const uint8_t Instruction::OC_LT = 0x11;
const uint8_t Instruction::OC_LE = 0x12;
const uint8_t Instruction::OC_GE = 0x13;
const uint8_t Instruction::OC_ADD = 0x14;
const uint8_t Instruction::OC_SUB = 0x15;
const uint8_t Instruction::OC_MUL = 0x16;
const uint8_t Instruction::OC_DIV = 0x17;
const uint8_t Instruction::OC_LAND = 0x18;
const uint8_t Instruction::OC_LOR = 0x19;
const uint8_t Instruction::OC_POP = 0x1A;
const uint8_t Instruction::OC_WRITE_BYTE_VAR = 0x42;
const uint8_t Instruction::OC_WRITE_WORD_VAR = 0x43;
const uint8_t Instruction::OC_BYTE_ARRAY_WRITE = 0x46;
const uint8_t Instruction::OC_WORD_ARRAY_WRITE = 0x47;
const uint8_t Instruction::OC_BYTE_ARRAY_INDEXED_WRITE = 0x4A;
const uint8_t Instruction::OC_WORD_ARRAY_INDEXED_WRITE = 0x4B;
const uint8_t Instruction::OC_BYTE_VAR_INC = 0x4E;
const uint8_t Instruction::OC_WORD_VAR_INC = 0x4F;
const uint8_t Instruction::OC_BYTE_ARRAY_INC = 0x52;
const uint8_t Instruction::OC_WORD_ARRAY_INC = 0x53;
const uint8_t Instruction::OC_BYTE_VAR_DEC = 0x56;
const uint8_t Instruction::OC_WORD_VAR_DEC = 0x57;
const uint8_t Instruction::OC_BYTE_ARRAY_DEC = 0x5A;
const uint8_t Instruction::OC_WORD_ARRAY_DEC = 0x5B;
const uint8_t Instruction::OC_IF = 0x5C;
const uint8_t Instruction::OC_IF_NOT = 0x5D;
const uint8_t Instruction::OC_START_SCRIPT = 0x5E;
const uint8_t Instruction::OC_START_SCRIPT_QUICK = 0x5F;
const uint8_t Instruction::OC_START_OBJECT = 0x60;
const uint8_t Instruction::OC_DRAW_OBJECT = 0x61;
const uint8_t Instruction::OC_DRAW_OBJECT_AT = 0x62;
const uint8_t Instruction::OC_DRAW_BLAST_OBJECT = 0x63;
const uint8_t Instruction::OC_SET_BLAST_OBJECT_WINDOW = 0x54;
const uint8_t Instruction::OC_STOP_OBJECT_CODE = 0x65;
const uint8_t Instruction::OC_END_CUTSCENE = 0x67;
const uint8_t Instruction::OC_CUTSCENE = 0x68;
const uint8_t Instruction::OC_STOP_MUSIC = 0x69;
const uint8_t Instruction::OC_FREEZE_UNFREEZE = 0x6A;
const uint8_t Instruction::OC_CURSOR_COMMAND = 0x6B;
	const uint8_t Instruction::SO_CURSOR_ON = 0x90;
	const uint8_t Instruction::SO_CURSOR_OFF = 0x91;
	const uint8_t Instruction::SO_USERPUT_ON = 0x92;
	const uint8_t Instruction::SO_USERPUT_OFF = 0x93;
	const uint8_t Instruction::SO_CURSOR_SOFT_ON = 0x94;
	const uint8_t Instruction::SO_CURSOR_SOFT_OFF = 0x95;
	const uint8_t Instruction::SO_USERPUT_SOFT_ON = 0x96;
	const uint8_t Instruction::SO_USERPUT_SOFT_OFF = 0x97;
	const uint8_t Instruction::SO_CURSOR_IMAGE = 0x99;
	const uint8_t Instruction::SO_CURSOR_HOTSPOT = 0x9A;
	const uint8_t Instruction::SO_CHARSET_SET = 0x9C;
	const uint8_t Instruction::SO_CHARSET_COLOR = 0x9D;
	const uint8_t Instruction::SO_CURSOR_TRANSPARENT = 0xD6;
const uint8_t Instruction::OC_BREAK_HERE = 0x6C;
const uint8_t Instruction::OC_IF_CLASS_OF_IS = 0x6D;
const uint8_t Instruction::OC_SET_CLASS = 0x6E;
const uint8_t Instruction::OC_GET_STATE = 0x6F;
const uint8_t Instruction::OC_SET_STATE = 0x70;
const uint8_t Instruction::OC_SET_OWNER = 0x71;
const uint8_t Instruction::OC_GET_OWNER = 0x72;
const uint8_t Instruction::OC_JUMP = 0x73;
const uint8_t Instruction::OC_START_SOUND = 0x74;
const uint8_t Instruction::OC_STOP_SOUND = 0x75;
const uint8_t Instruction::OC_STAR_MUSIC = 0x76;
const uint8_t Instruction::OC_STOP_OBJECT_SCRIPT = 0x77;
const uint8_t Instruction::OC_PAN_CAMERA_TO = 0x78;
const uint8_t Instruction::OC_ACTOR_FOLLOW_CAMERA = 0x79;
const uint8_t Instruction::OC_SET_CAMERA_AT = 0x7A;
const uint8_t Instruction::OC_LOAD_ROOM = 0x7B;
const uint8_t Instruction::OC_STOP_SCRIPT = 0x7C;
const uint8_t Instruction::OC_WALK_ACTOR_TO_OBJ = 0x7D;
const uint8_t Instruction::OC_WALK_ACTOR_TO = 0x7E;
const uint8_t Instruction::OC_PUT_ACTOR_AT_XY = 0x7F;
const uint8_t Instruction::OC_PUT_ACTOR_AT_OBJECT = 0x80;
const uint8_t Instruction::OC_FACE_ACTOR = 0x81;
const uint8_t Instruction::OC_ANIMATE_ACTOR = 0x82;
const uint8_t Instruction::OC_DO_SENTENCE = 0x83;
const uint8_t Instruction::OC_PICKUP_OBJECT = 0x84;
const uint8_t Instruction::OC_LOAD_ROOM_WITH_EGO = 0x85;
const uint8_t Instruction::OC_GET_RANDOM_NUMBER = 0x87;
const uint8_t Instruction::OC_GET_RANDOM_NUMBER_RANGE = 0x88;
const uint8_t Instruction::OC_GET_ACTOR_MOVING = 0x8A;
const uint8_t Instruction::OC_IS_SCRIPT_RUNNING = 0x8B;
const uint8_t Instruction::OC_GET_ACTOR_ROOM = 0x8C;
const uint8_t Instruction::OC_GET_OBJECT_X = 0x8D;
const uint8_t Instruction::OC_GET_OBJECT_Y = 0x8E;
const uint8_t Instruction::OC_GET_OBJECT_OLD_DIR = 0x8F;
const uint8_t Instruction::OC_GET_ACTOR_WALK_BOX = 0x90;
const uint8_t Instruction::OC_GET_ACTOR_COSTUME = 0x91;
const uint8_t Instruction::OC_FIND_INVENTORY = 0x92;
const uint8_t Instruction::OC_GET_INVENTORY_COUNT = 0x93;
const uint8_t Instruction::OC_GET_VERB_FROM_XY = 0x94;
const uint8_t Instruction::OC_BEGIN_OVERRIDE = 0x95;
const uint8_t Instruction::OC_END_OVERRIDE = 0x96;
const uint8_t Instruction::OC_SET_OBJECT_NAME = 0x97;
const uint8_t Instruction::OC_IS_SOUND_RUNNING = 0x98;
const uint8_t Instruction::OC_SET_BOX_FLAGS = 0x99;
const uint8_t Instruction::OC_CREATE_BOX_MATRIX = 0x9A;
const uint8_t Instruction::OC_RESOURCE_ROUTINES = 0x9B;
	const uint8_t Instruction::SO_LOAD_SCRIPT = 0x64;
	const uint8_t Instruction::SO_LOAD_SOUND = 0x65;
	const uint8_t Instruction::SO_LOAD_COSTUME = 0x66;
	const uint8_t Instruction::SO_LOAD_ROOM = 0x67;
	const uint8_t Instruction::SO_NUKE_SCRIPT = 0x68;
	const uint8_t Instruction::SO_NUKE_SOUND = 0x69;
	const uint8_t Instruction::SO_NUKE_COSTUME = 0x6A;
	const uint8_t Instruction::SO_NUKE_ROOM = 0x6B;
	const uint8_t Instruction::SO_LOCK_SCRIPT = 0x6C;
	const uint8_t Instruction::SO_LOCK_SOUND = 0x6D;
	const uint8_t Instruction::SO_LOCK_COSTUME = 0x6E;
	const uint8_t Instruction::SO_LOCK_ROOM = 0x6F;
	const uint8_t Instruction::SO_UNLOCK_SCRIPT = 0x70;
	const uint8_t Instruction::SO_UNLOCK_SOUND = 0x71;
	const uint8_t Instruction::SO_UNLOCK_COSTUME = 0x72;
	const uint8_t Instruction::SO_UNLOCK_ROOM = 0x73;
	const uint8_t Instruction::SO_CLEAR_HEAP = 0x74;
	const uint8_t Instruction::SO_LOAD_CHARSET = 0x75;
	const uint8_t Instruction::SO_NUKE_CHARSET = 0x76;
	const uint8_t Instruction::SO_LOAD_OBJECT = 0x77;
const uint8_t Instruction::OC_ROOM_OPS = 0x9C;
	const uint8_t Instruction::SO_ROOM_SCROLL = 0xAC;
	const uint8_t Instruction::SO_ROOM_SCREEN = 0xAE;
	const uint8_t Instruction::SO_ROOM_PALETTE = 0xAF;
	const uint8_t Instruction::SO_ROOM_SHAKE_ON = 0xB0;
	const uint8_t Instruction::SO_ROOM_SHAKE_OFF = 0xB1;
	const uint8_t Instruction::SO_ROOM_INTENSITY = 0xB3;
	const uint8_t Instruction::SO_ROOM_SAVE_GAME = 0xB4;
	const uint8_t Instruction::SO_ROOM_FADE = 0xB5;
	const uint8_t Instruction::SO_RGB_ROOM_INTENSITY = 0xB6;
	const uint8_t Instruction::SO_ROOM_SHADOW = 0xB7;
	const uint8_t Instruction::SO_ROOM_TRANSFORM = 0xBA;
	const uint8_t Instruction::SO_CYCLE_SPEED = 0xBB;
	const uint8_t Instruction::SO_ROOM_NEW_PALETTE = 0xD5;
const uint8_t Instruction::OC_ACTOR_OPS = 0x9D;
	const uint8_t Instruction::SO_ACTOR_SET_CURRENT = 0xC5;
	const uint8_t Instruction::SO_COSTUME = 0x4C;
	const uint8_t Instruction::SO_STEP_DIST = 0x4D;
	const uint8_t Instruction::SO_SOUND = 0x4E;
	const uint8_t Instruction::SO_WALK_ANIMATION = 0x4F;
	const uint8_t Instruction::SO_TALK_ANIMATION = 0x50;
	const uint8_t Instruction::SO_STAND_ANIMATION = 0x51;
	const uint8_t Instruction::SO_DEFAULT = 0x53;
	const uint8_t Instruction::SO_ELEVATION = 0x54;
	const uint8_t Instruction::SO_ANIMATION_DEFAULT = 0x55;
	const uint8_t Instruction::SO_PALETTE = 0x56;
	const uint8_t Instruction::SO_TALK_COLOR = 0x57;
	const uint8_t Instruction::SO_ACTOR_NAME = 0x58;
	const uint8_t Instruction::SO_INIT_ANIMATION = 0x59;
	const uint8_t Instruction::SO_ACTOR_WIDTH = 0x5B;
	const uint8_t Instruction::SO_SCALE = 0x5C;
	const uint8_t Instruction::SO_NEVER_ZCLIP = 0x5D;
	const uint8_t Instruction::SO_ALWAYS_ZCLIP = 0x5E;
	const uint8_t Instruction::SO_IGNORE_BOXES = 0x5F;
	const uint8_t Instruction::SO_FOLLOW_BOXES = 0x60;
	const uint8_t Instruction::SO_ANIMATION_SPEED = 0x61;
	const uint8_t Instruction::SO_SHADOW = 0x62;
	const uint8_t Instruction::SO_TEXT_OFFSET = 0x63;
	const uint8_t Instruction::SO_ACTOR_VARIABLE = 0xC6;
	const uint8_t Instruction::SO_ACTOR_IGNORE_TURNS_ON = 0xD7;
	const uint8_t Instruction::SO_ACTOR_IGNORE_TURNS_OFF = 0xD8;
	const uint8_t Instruction::SO_ACTOR_NEW = 0xD9;
	const uint8_t Instruction::SO_ACTOR_DEPTH = 0xE3;
	const uint8_t Instruction::SO_ACTOR_WALK_SCRIPT = 0xE4;
	const uint8_t Instruction::SO_ACTOR_STOP = 0xE5;
	const uint8_t Instruction::SO_ACTOR_SET_DIRECTION = 0xE6;
	const uint8_t Instruction::SO_ACTOR_TURN_TO_DIRECTION = 0xE7;
	const uint8_t Instruction::SO_ACTOR_WALK_PAUSE = 0xE9;
	const uint8_t Instruction::SO_ACTOR_WALK_RESUME = 0xEA;
	const uint8_t Instruction::SO_ACTOR_TALK_SCRIPT = 0xEB;
const uint8_t Instruction::OC_VERB_OPS = 0x9E;
	const uint8_t Instruction::SO_VERB_SET_CURRENT = 0xC4;
	const uint8_t Instruction::SO_VERB_IMAGE = 0x7C;
	const uint8_t Instruction::SO_VERB_NAME = 0x7D;
	const uint8_t Instruction::SO_VERB_COLOR = 0x7E;
	const uint8_t Instruction::SO_VERB_HICOLOR = 0x7F;
	const uint8_t Instruction::SO_VERB_AT = 0x80;
	const uint8_t Instruction::SO_VERB_ON = 0x81;
	const uint8_t Instruction::SO_VERB_OFF = 0x82;
	const uint8_t Instruction::SO_VERB_DELETE = 0x83;
	const uint8_t Instruction::SO_VERB_NEW = 0x84;
	const uint8_t Instruction::SO_VERB_DIMCOLOR = 0x85;
	const uint8_t Instruction::SO_VERB_DIM = 0x86;
	const uint8_t Instruction::SO_VERB_KEY = 0x87;
	const uint8_t Instruction::SO_VERB_CENTER = 0x88;
	const uint8_t Instruction::SO_VERB_NAME_STR = 0x89;
	const uint8_t Instruction::SO_VERB_IMAGE_IN_ROOM = 0x8B;
	const uint8_t Instruction::SO_VERB_BACKCOLOR = 0x8C;
	const uint8_t Instruction::SO_VERB_DRAW = 0xFF;
const uint8_t Instruction::OC_GET_ACTOR_FROM_XY = 0x9F;
const uint8_t Instruction::OC_FIND_OBJECT = 0xA0;
const uint8_t Instruction::OC_PSEUDO_ROOM = 0xA1;
const uint8_t Instruction::OC_GET_ACTOR_ELEVATION = 0xA2;
const uint8_t Instruction::OC_GET_VERB_ENTRY_POINT = 0xA3;
const uint8_t Instruction::OC_ARRAY_OPS = 0xA4;
	const uint8_t Instruction::SO_ASSIGN_STRING = 0xCD;
	const uint8_t Instruction::SO_ASSIGN_INT_LIST = 0xD0;
	const uint8_t Instruction::SO_ASSIGN_2DIM_LIST = 0xD4;
const uint8_t Instruction::OC_SAVE_RESTORE_VERBS = 0xA5;
	const uint8_t Instruction::SO_SAVE_VERBS = 0x8D;
	const uint8_t Instruction::SO_RESTORE_VERBS = 0x8E;
	const uint8_t Instruction::SO_DELETE_VERBS = 0x8F;
const uint8_t Instruction::OC_DRAW_BOX = 0xA6;
const uint8_t Instruction::OC_GET_ACTOR_WIDTH = 0xA8;
const uint8_t Instruction::OC_WAIT = 0xA9;
	const uint8_t Instruction::SO_WAIT_FOR_ACTOR = 0xA8;
	const uint8_t Instruction::SO_WAIT_FOR_MESSAGE = 0xA9;
	const uint8_t Instruction::SO_WAIT_FOR_CAMERA = 0xAA;
	const uint8_t Instruction::SO_WAIT_FOR_SENTENCE = 0xAB;
	const uint8_t Instruction::SO_WAIT_FOR_ANIMATION = 0xE2;
	const uint8_t Instruction::SO_WAIT_FOR_TURN = 0xE8;
const uint8_t Instruction::OC_GET_ACTOR_SCALE_X = 0xAA;
const uint8_t Instruction::OC_GET_ACTOR_ANIM_COUNTER = 0xAB;
const uint8_t Instruction::OC_SOUND_KLUDGE = 0xAC;
const uint8_t Instruction::OC_IS_ANY_OF = 0xAD;
const uint8_t Instruction::OC_SYSTEM_OPS = 0xAE;
	const uint8_t Instruction::SO_RESTART = 0x9E;
	const uint8_t Instruction::SO_PAUSE = 0x9F;
	const uint8_t Instruction::SO_QUIT = 0xA0;
const uint8_t Instruction::OC_IS_ACTOR_IN_BOX = 0xAF;
const uint8_t Instruction::OC_DELAY = 0xB0;
const uint8_t Instruction::OC_DELAY_SECONDS = 0xB1;
const uint8_t Instruction::OC_DELAY_MINUTES = 0xB2;
const uint8_t Instruction::OC_STOP_SENTENCE = 0xB3;
const uint8_t Instruction::OC_PRINT_LINE = 0xB4;
const uint8_t Instruction::OC_PRINT_TEXT = 0xB5;
const uint8_t Instruction::OC_PRINT_DEBUG = 0xB6;
const uint8_t Instruction::OC_PRINT_SYSTEM = 0xB7;
const uint8_t Instruction::OC_PRINT_ACTOR = 0xB8;
const uint8_t Instruction::OC_PRINT_EGO = 0xB9;
	const uint8_t Instruction::SO_AT = 0x41;
	const uint8_t Instruction::SO_COLOR = 0x42;
	const uint8_t Instruction::SO_CLIPPED = 0x43;
	const uint8_t Instruction::SO_CENTER = 0x45;
	const uint8_t Instruction::SO_LEFT = 0x47;
	const uint8_t Instruction::SO_OVERHEAD = 0x48;
	const uint8_t Instruction::SO_MUMBLE = 0x4A;
	const uint8_t Instruction::SO_TEXTSTRING = 0x4B;
	const uint8_t Instruction::SO_LOAD_DEFAULT = 0xFE;
	const uint8_t Instruction::SO_SAVE_DEFAULT = 0xFF;
const uint8_t Instruction::OC_TALK_ACTOR = 0xBA;
const uint8_t Instruction::OC_TALK_EGO = 0xBB;
const uint8_t Instruction::OC_DIM_ARRAY = 0xBC;
const uint8_t Instruction::OC_DUMMY = 0xBD;
const uint8_t Instruction::OC_START_OBJECT_QUICK = 0xBE;
const uint8_t Instruction::OC_START_SCRIPT_QUICK_2 = 0xBF;
const uint8_t Instruction::OC_DIM_2_DIM_ARRAY = 0xC0;
		const uint8_t Instruction::SO_INT_ARRAY = 0xC7;
		const uint8_t Instruction::SO_BIT_ARRAY = 0xC8;
		const uint8_t Instruction::SO_NIBBLE_ARRAY = 0xC9;
		const uint8_t Instruction::SO_BYTE_ARRAY = 0xCA;
		const uint8_t Instruction::SO_STRING_ARRAY = 0xCB;
		const uint8_t Instruction::SO_UNDIM_ARRAY = 0xCC;
const uint8_t Instruction::OC_ABS = 0xC4;
const uint8_t Instruction::OC_DIST_OBJECT_OBJECT = 0xC5;
const uint8_t Instruction::OC_DIST_OBJECT_PT = 0xC6;
const uint8_t Instruction::OC_DIST_PT_PT = 0xC7;
const uint8_t Instruction::OC_KERNEL_GET_FUNCTIONS = 0xC8;
const uint8_t Instruction::OC_KERNEL_SET_FUNCTIONS = 0xC9;
const uint8_t Instruction::OC_DELAY_FRAMES = 0xCA;
const uint8_t Instruction::OC_PICK_ONE_OF = 0xCB;
const uint8_t Instruction::OC_PICK_ONE_OF_DEFAULT = 0xCC;
const uint8_t Instruction::OC_STAMP_OBJECT = 0xCD;
const uint8_t Instruction::OC_GET_DATE_TIME = 0xD0;
const uint8_t Instruction::OC_STOP_TALKING = 0xD1;
const uint8_t Instruction::OC_GET_ANIMATE_VARIABLE = 0xD2;
const uint8_t Instruction::OC_SHUFFLE = 0xD4;
const uint8_t Instruction::OC_JUMP_TO_SCRIPT = 0xD5;
const uint8_t Instruction::OC_BAND = 0xD6;
const uint8_t Instruction::OC_BOR = 0xD7;
const uint8_t Instruction::OC_IS_ROOM_SCRIPT_RUNNING = 0xD8;
const uint8_t Instruction::OC_FIND_ALL_OBJECTS = 0xDD;
const uint8_t Instruction::OC_GET_PIXEL = 0xE1;
const uint8_t Instruction::OC_PICK_VAR_RANDOM = 0xE3;
const uint8_t Instruction::OC_SET_BOX_SET = 0xE4;
const uint8_t Instruction::OC_GET_ACTOR_LAYER = 0xEC;
const uint8_t Instruction::OC_GET_OBJECT_NEW_DIR = 0xED;

map<string, uint8_t> Instruction::_opcodes;

void Instruction::setOpcodes()
{
	_opcodes["add"] = OC_ADD;
	_opcodes["actorSetCurrent"] = SO_ACTOR_SET_CURRENT;
	_opcodes["actorDefault"] = SO_DEFAULT;
	_opcodes["actorOps"] = OC_ACTOR_OPS;
	_opcodes["animationSpeed"] = SO_ANIMATION_SPEED;
	_opcodes["arrayOps"] = OC_ARRAY_OPS;
	_opcodes["assignString"] = SO_ASSIGN_STRING;
	_opcodes["costume"] = SO_COSTUME;
	_opcodes["cursorCommand"] = OC_CURSOR_COMMAND;
	_opcodes["cursorImage"] = SO_CURSOR_IMAGE;
	_opcodes["cursorOff"] = SO_CURSOR_OFF;
	_opcodes["cursorOn"] = SO_CURSOR_ON;
	_opcodes["cursorTransparent"] = SO_CURSOR_TRANSPARENT;
	_opcodes["cycleSpeed"] = SO_CYCLE_SPEED;
	_opcodes["delay"] = OC_DELAY;
	_opcodes["delaySeconds"] = OC_DELAY_SECONDS;
	_opcodes["dimArray"] = OC_DIM_ARRAY;
	_opcodes["eq"] = OC_EQ;
	_opcodes["if"] = OC_IF;
	_opcodes["ifNot"] = OC_IF_NOT;
	_opcodes["ignoreBoxes"] = SO_IGNORE_BOXES;
	_opcodes["isScriptRunning"] = OC_IS_SCRIPT_RUNNING;
	_opcodes["jump"] = OC_JUMP;
	_opcodes["land"] = OC_LAND;
	_opcodes["le"] = OC_LE;
	_opcodes["lt"] = OC_LT;
	_opcodes["loadCostume"] = SO_LOAD_COSTUME;
	_opcodes["loadRoom"] = OC_LOAD_ROOM;
	_opcodes["lockRoom"] = SO_LOCK_ROOM;
	_opcodes["mul"] = OC_MUL;
	_opcodes["not"] = OC_NOT;
	_opcodes["pop"] = OC_POP;
	_opcodes["printDebug"] = OC_PRINT_DEBUG;
	_opcodes["printSystem"] = OC_PRINT_SYSTEM;
	_opcodes["pushByte"] = OC_PUSH_BYTE;
	_opcodes["pushWord"] = OC_PUSH_WORD;
	_opcodes["pushWordVar"] = OC_PUSH_WORD_VAR;
	_opcodes["putActorAtXY"] = OC_PUT_ACTOR_AT_XY;
	_opcodes["quit"] = SO_QUIT;
	_opcodes["resourceRoutines"] = OC_RESOURCE_ROUTINES;
	_opcodes["roomOps"] = OC_ROOM_OPS;
	_opcodes["roomScreen"] = SO_ROOM_SCREEN;
	_opcodes["roomShakeOff"] = SO_ROOM_SHAKE_OFF;
	_opcodes["roomShakeOn"] = SO_ROOM_SHAKE_ON;
	_opcodes["soundKludge"] = OC_SOUND_KLUDGE;
	_opcodes["startScript"] = OC_START_SCRIPT;
	_opcodes["startScriptQuick"] = OC_START_SCRIPT_QUICK;
	_opcodes["startScriptQuick2"] = OC_START_SCRIPT_QUICK_2;
	_opcodes["startSound"] = OC_START_SOUND;
	_opcodes["stepDist"] = SO_STEP_DIST;
	_opcodes["stopObjectCode"] = OC_STOP_OBJECT_CODE;
	_opcodes["stringArray"] = SO_STRING_ARRAY;
	_opcodes["sub"] = OC_SUB;
	_opcodes["systemOps"] = OC_SYSTEM_OPS;
	_opcodes["textString"] = SO_TEXTSTRING;
	_opcodes["undimArray"] = SO_UNDIM_ARRAY;
	_opcodes["userPutOff"] = SO_USERPUT_OFF;
	_opcodes["userPutOn"] = SO_USERPUT_ON;
	_opcodes["walkActorTo"] = OC_WALK_ACTOR_TO;
	_opcodes["wordArrayIndexedRead"] = OC_WORD_ARRAY_INDEXED_READ;
	_opcodes["wordArrayIndexedWrite"] = OC_WORD_ARRAY_INDEXED_WRITE;
	_opcodes["wordVarInc"] = OC_WORD_VAR_INC;
	_opcodes["wordVarDec"] = OC_WORD_VAR_DEC;
	_opcodes["writeWordVar"] = OC_WRITE_WORD_VAR;
}

int16_t Instruction::toInteger(string s)
{
	istringstream iss(s);
	int16_t result;
	if (!(iss >> result))
		Log::getInstance().write(LOG_ERROR, "\"%s\" is not an integer !\n", s.c_str());
	return result;
}

Instruction::Instruction(string opcodeName)
{
	_type = INSTRUCTION_OPCODE;
	_address = Context::currentAddress;
	_opcodeName = opcodeName;

	// Check if opcode exists
	if (_opcodes.find(_opcodeName) == _opcodes.end())
		Log::getInstance().write(LOG_ERROR, "Unknown opcode \"%s\" !\n", _opcodeName.c_str());

	// Update current address
	Context::currentAddress++;
}

Instruction::Instruction(ValueType valueType, string value, string pretty)
{
	_type = INSTRUCTION_VALUE;
	_address = Context::currentAddress;
	_valueType = valueType;
	_value = value;
	_pretty = pretty;

	// Update current address
	switch (_valueType)
	{
		case VALUE_NULL:
			break;
		case VALUE_BYTE:
			Context::currentAddress++;
			break;
		case VALUE_WORD:
			Context::currentAddress += 2;
			break;
		case VALUE_STRING:
			Context::currentAddress += value.length() + 1;
	}
}

Instruction::Instruction(uint32_t label)
{
	_type = INSTRUCTION_LABEL;
	_address = Context::currentAddress;
	_label = label;
}

string Instruction::toString()
{
	ostringstream oss;
	switch (_type)
	{
		case INSTRUCTION_OPCODE:
			oss << dec << _address << dec << ": " << _opcodeName;
			break;
		case INSTRUCTION_VALUE:
			switch (_valueType)
			{
				case VALUE_NULL:
					break;
				case VALUE_BYTE:
					oss << dec <<_address << dec << ": .byte ";
					break;
				case VALUE_WORD:
					oss << dec <<_address << dec << ": .word ";
					break;
				case VALUE_STRING:
					oss << dec <<_address << dec << ": .string ";
			}
			oss << (_pretty.empty() ? _value : _pretty);
			break;
		case INSTRUCTION_LABEL:
			oss << "LABEL_" << _label << ":";
	}
	return oss.str();
}

void Instruction::assemble(vector<uint8_t> &byteCode)
{
	uint16_t word;
	switch (_type)
	{
		case INSTRUCTION_OPCODE:
			byteCode.push_back(_opcodes[_opcodeName]);
			break;
		case INSTRUCTION_VALUE:
			switch (_valueType)
			{
				case VALUE_NULL:
					break;
				case VALUE_BYTE:
					byteCode.push_back(toInteger(_value));
					break;
				case VALUE_WORD:
					word = toInteger(_value);
					byteCode.push_back(word);
					byteCode.push_back(word >> 8);
					break;
				case VALUE_STRING:
					for (int i = 0; i < _value.length(); i++)
						byteCode.push_back(_value[i]);
					byteCode.push_back(0);
			}
			break;
		case INSTRUCTION_LABEL:
			Log::getInstance().write(LOG_ERROR, "Labels can't be assembled !\n");
	}
}

Instruction::~Instruction()
{
}
