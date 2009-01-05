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
const uint8_t Instruction::OC_START_MUSIC = 0x76;
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
	_opcodes["abs"] = OC_ABS;
	_opcodes["actorDepth"] = SO_ACTOR_DEPTH;
	_opcodes["actorFollowCamera"] = OC_ACTOR_FOLLOW_CAMERA;
	_opcodes["actorIgnoreTurnsOff"] = SO_ACTOR_IGNORE_TURNS_OFF;
	_opcodes["actorIgnoreTurnsOn"] = SO_ACTOR_IGNORE_TURNS_ON;
	_opcodes["actorName"] = SO_ACTOR_NAME;
	_opcodes["actorNew"] = SO_ACTOR_NEW;
	_opcodes["actorOps"] = OC_ACTOR_OPS;
	_opcodes["actorSetCurrent"] = SO_ACTOR_SET_CURRENT;
	_opcodes["actorSetDirection"] = SO_ACTOR_SET_DIRECTION;
	_opcodes["actorStop"] = SO_ACTOR_STOP;
	_opcodes["actorTalkScript"] = SO_ACTOR_TALK_SCRIPT;
	_opcodes["actorTurnToDirection"] = SO_ACTOR_TURN_TO_DIRECTION;
	_opcodes["actorVariable"] = SO_ACTOR_VARIABLE;
	_opcodes["actorWalkPause"] = SO_ACTOR_WALK_PAUSE;
	_opcodes["actorWalkResume"] = SO_ACTOR_WALK_RESUME;
	_opcodes["actorWalkScript"] = SO_ACTOR_WALK_SCRIPT;
	_opcodes["actorWidth"] = SO_ACTOR_WIDTH;
	_opcodes["add"] = OC_ADD;
	_opcodes["alwaysZClip"] = SO_ALWAYS_ZCLIP;
	_opcodes["animateActor"] = OC_ANIMATE_ACTOR;
	_opcodes["animationDefault"] = SO_ANIMATION_DEFAULT;
	_opcodes["animationSpeed"] = SO_ANIMATION_SPEED;
	_opcodes["arrayOps"] = OC_ARRAY_OPS;
	_opcodes["assign2DimList"] = SO_ASSIGN_2DIM_LIST;
	_opcodes["assignIntList"] = SO_ASSIGN_INT_LIST;
	_opcodes["assignString"] = SO_ASSIGN_STRING;
	_opcodes["at"] = SO_AT;
	_opcodes["band"] = OC_BAND;
	_opcodes["beginOverride"] = OC_BEGIN_OVERRIDE;
	_opcodes["bitArray"] = SO_BIT_ARRAY;
	_opcodes["bor"] = OC_BOR;
	_opcodes["breakHere"] = OC_BREAK_HERE;
	_opcodes["byteArray"] = SO_BYTE_ARRAY;
	_opcodes["byteArrayDec"] = OC_BYTE_ARRAY_DEC;
	_opcodes["byteArrayInc"] = OC_BYTE_ARRAY_INC;
	_opcodes["byteArrayIndexedRead"] = OC_BYTE_ARRAY_INDEXED_READ;
	_opcodes["byteArrayIndexedWrite"] = OC_BYTE_ARRAY_INDEXED_WRITE;
	_opcodes["byteArrayRead"] = OC_BYTE_ARRAY_READ;
	_opcodes["byteArrayWrite"] = OC_BYTE_ARRAY_WRITE;
	_opcodes["byteVarDec"] = OC_BYTE_VAR_DEC;
	_opcodes["byteVarInc"] = OC_BYTE_VAR_INC;
	_opcodes["center"] = SO_CENTER;
	_opcodes["charsetColor"] = SO_CHARSET_COLOR;
	_opcodes["charsetSet"] = SO_CHARSET_SET;
	_opcodes["clearHeap"] = SO_CLEAR_HEAP;
	_opcodes["clipped"] = SO_CLIPPED;
	_opcodes["color"] = SO_COLOR;
	_opcodes["costume"] = SO_COSTUME;
	_opcodes["createBoxMatrix"] = OC_CREATE_BOX_MATRIX;
	_opcodes["cursorCommand"] = OC_CURSOR_COMMAND;
	_opcodes["cursorHotspot"] = SO_CURSOR_HOTSPOT;
	_opcodes["cursorImage"] = SO_CURSOR_IMAGE;
	_opcodes["cursorOff"] = SO_CURSOR_OFF;
	_opcodes["cursorOn"] = SO_CURSOR_ON;
	_opcodes["cursorSoftOff"] = SO_CURSOR_SOFT_OFF;
	_opcodes["cursorSoftOn"] = SO_CURSOR_SOFT_ON;
	_opcodes["cursorTransparent"] = SO_CURSOR_TRANSPARENT;
	_opcodes["cutscene"] = OC_CUTSCENE;
	_opcodes["cycleSpeed"] = SO_CYCLE_SPEED;
	_opcodes["default"] = SO_DEFAULT;
	_opcodes["delay"] = OC_DELAY;
	_opcodes["delayFrames"] = OC_DELAY_FRAMES;
	_opcodes["delayMinutes"] = OC_DELAY_MINUTES;
	_opcodes["delaySeconds"] = OC_DELAY_SECONDS;
	_opcodes["deleteVerbs"] = SO_DELETE_VERBS;
	_opcodes["dim2DimArray"] = OC_DIM_2_DIM_ARRAY;
	_opcodes["dimArray"] = OC_DIM_ARRAY;
	_opcodes["distObjectObject"] = OC_DIST_OBJECT_OBJECT;
	_opcodes["distObjectPt"] = OC_DIST_OBJECT_PT;
	_opcodes["distPtPt"] = OC_DIST_PT_PT;
	_opcodes["div"] = OC_DIV;
	_opcodes["doSentence"] = OC_DO_SENTENCE;
	_opcodes["drawBlastObject"] = OC_DRAW_BLAST_OBJECT;
	_opcodes["drawBox"] = OC_DRAW_BOX;
	_opcodes["drawObject"] = OC_DRAW_OBJECT;
	_opcodes["drawObjectAt"] = OC_DRAW_OBJECT_AT;
	_opcodes["dummy"] = OC_DUMMY;
	_opcodes["dup"] = OC_DUP;
	_opcodes["elevation"] = SO_ELEVATION;
	_opcodes["endCutscene"] = OC_END_CUTSCENE;
	_opcodes["endOverride"] = OC_END_OVERRIDE;
	_opcodes["eq"] = OC_EQ;
	_opcodes["faceActor"] = OC_FACE_ACTOR;
	_opcodes["findAllObjects"] = OC_FIND_ALL_OBJECTS;
	_opcodes["findInventory"] = OC_FIND_INVENTORY;
	_opcodes["findObject"] = OC_FIND_OBJECT;
	_opcodes["followBoxes"] = SO_FOLLOW_BOXES;
	_opcodes["freezeUnfreeze"] = OC_FREEZE_UNFREEZE;
	_opcodes["ge"] = OC_GE;
	_opcodes["getActorAnimCounter"] = OC_GET_ACTOR_ANIM_COUNTER;
	_opcodes["getActorCostume"] = OC_GET_ACTOR_COSTUME;
	_opcodes["getActorElevation"] = OC_GET_ACTOR_ELEVATION;
	_opcodes["getActorFromXy"] = OC_GET_ACTOR_FROM_XY;
	_opcodes["getActorLayer"] = OC_GET_ACTOR_LAYER;
	_opcodes["getActorMoving"] = OC_GET_ACTOR_MOVING;
	_opcodes["getActorRoom"] = OC_GET_ACTOR_ROOM;
	_opcodes["getActorScaleX"] = OC_GET_ACTOR_SCALE_X;
	_opcodes["getActorWalkBox"] = OC_GET_ACTOR_WALK_BOX;
	_opcodes["getActorWidth"] = OC_GET_ACTOR_WIDTH;
	_opcodes["getAnimateVariable"] = OC_GET_ANIMATE_VARIABLE;
	_opcodes["getDateTime"] = OC_GET_DATE_TIME;
	_opcodes["getInventoryCount"] = OC_GET_INVENTORY_COUNT;
	_opcodes["getObjectNewDir"] = OC_GET_OBJECT_NEW_DIR;
	_opcodes["getObjectOldDir"] = OC_GET_OBJECT_OLD_DIR;
	_opcodes["getObjectX"] = OC_GET_OBJECT_X;
	_opcodes["getObjectY"] = OC_GET_OBJECT_Y;
	_opcodes["getOwner"] = OC_GET_OWNER;
	_opcodes["getPixel"] = OC_GET_PIXEL;
	_opcodes["getRandomNumber"] = OC_GET_RANDOM_NUMBER;
	_opcodes["getRandomNumberRange"] = OC_GET_RANDOM_NUMBER_RANGE;
	_opcodes["getState"] = OC_GET_STATE;
	_opcodes["getVerbEntryPoint"] = OC_GET_VERB_ENTRY_POINT;
	_opcodes["getVerbFromXy"] = OC_GET_VERB_FROM_XY;
	_opcodes["gt"] = OC_GT;
	_opcodes["if"] = OC_IF;
	_opcodes["ifClassOfIs"] = OC_IF_CLASS_OF_IS;
	_opcodes["ifNot"] = OC_IF_NOT;
	_opcodes["ignoreBoxes"] = SO_IGNORE_BOXES;
	_opcodes["initAnimation"] = SO_INIT_ANIMATION;
	_opcodes["intArray"] = SO_INT_ARRAY;
	_opcodes["isActorInBox"] = OC_IS_ACTOR_IN_BOX;
	_opcodes["isAnyOf"] = OC_IS_ANY_OF;
	_opcodes["isRoomScriptRunning"] = OC_IS_ROOM_SCRIPT_RUNNING;
	_opcodes["isScriptRunning"] = OC_IS_SCRIPT_RUNNING;
	_opcodes["isSoundRunning"] = OC_IS_SOUND_RUNNING;
	_opcodes["jump"] = OC_JUMP;
	_opcodes["jumpToScript"] = OC_JUMP_TO_SCRIPT;
	_opcodes["kernelGetFunctions"] = OC_KERNEL_GET_FUNCTIONS;
	_opcodes["kernelSetFunctions"] = OC_KERNEL_SET_FUNCTIONS;
	_opcodes["land"] = OC_LAND;
	_opcodes["le"] = OC_LE;
	_opcodes["left"] = SO_LEFT;
	_opcodes["loadCharset"] = SO_LOAD_CHARSET;
	_opcodes["loadCostume"] = SO_LOAD_COSTUME;
	_opcodes["loadDefault"] = SO_LOAD_DEFAULT;
	_opcodes["loadObject"] = SO_LOAD_OBJECT;
	_opcodes["loadRoom"] = OC_LOAD_ROOM;
	_opcodes["loadRoom2"] = SO_LOAD_ROOM;
	_opcodes["loadRoomWithEgo"] = OC_LOAD_ROOM_WITH_EGO;
	_opcodes["loadScript"] = SO_LOAD_SCRIPT;
	_opcodes["loadSound"] = SO_LOAD_SOUND;
	_opcodes["lockCostume"] = SO_LOCK_COSTUME;
	_opcodes["lockRoom"] = SO_LOCK_ROOM;
	_opcodes["lockScript"] = SO_LOCK_SCRIPT;
	_opcodes["lockSound"] = SO_LOCK_SOUND;
	_opcodes["lor"] = OC_LOR;
	_opcodes["lt"] = OC_LT;
	_opcodes["mul"] = OC_MUL;
	_opcodes["mumble"] = SO_MUMBLE;
	_opcodes["neq"] = OC_NEQ;
	_opcodes["neverZClip"] = SO_NEVER_ZCLIP;
	_opcodes["nibbleArray"] = SO_NIBBLE_ARRAY;
	_opcodes["not"] = OC_NOT;
	_opcodes["nukeCharset"] = SO_NUKE_CHARSET;
	_opcodes["nukeCostume"] = SO_NUKE_COSTUME;
	_opcodes["nukeRoom"] = SO_NUKE_ROOM;
	_opcodes["nukeScript"] = SO_NUKE_SCRIPT;
	_opcodes["nukeSound"] = SO_NUKE_SOUND;
	_opcodes["overhead"] = SO_OVERHEAD;
	_opcodes["palette"] = SO_PALETTE;
	_opcodes["panCameraTo"] = OC_PAN_CAMERA_TO;
	_opcodes["pause"] = SO_PAUSE;
	_opcodes["pickOneOf"] = OC_PICK_ONE_OF;
	_opcodes["pickOneOfDefault"] = OC_PICK_ONE_OF_DEFAULT;
	_opcodes["pickVarRandom"] = OC_PICK_VAR_RANDOM;
	_opcodes["pickupObject"] = OC_PICKUP_OBJECT;
	_opcodes["pop"] = OC_POP;
	_opcodes["printActor"] = OC_PRINT_ACTOR;
	_opcodes["printDebug"] = OC_PRINT_DEBUG;
	_opcodes["printEgo"] = OC_PRINT_EGO;
	_opcodes["printLine"] = OC_PRINT_LINE;
	_opcodes["printSystem"] = OC_PRINT_SYSTEM;
	_opcodes["printText"] = OC_PRINT_TEXT;
	_opcodes["pseudoRoom"] = OC_PSEUDO_ROOM;
	_opcodes["pushByte"] = OC_PUSH_BYTE;
	_opcodes["pushByteVar"] = OC_PUSH_BYTE_VAR;
	_opcodes["pushWord"] = OC_PUSH_WORD;
	_opcodes["pushWordVar"] = OC_PUSH_WORD_VAR;
	_opcodes["putActorAtObject"] = OC_PUT_ACTOR_AT_OBJECT;
	_opcodes["putActorAtXY"] = OC_PUT_ACTOR_AT_XY;
	_opcodes["quit"] = SO_QUIT;
	_opcodes["resourceRoutines"] = OC_RESOURCE_ROUTINES;
	_opcodes["restart"] = SO_RESTART;
	_opcodes["restoreVerbs"] = SO_RESTORE_VERBS;
	_opcodes["rgbRoomIntensity"] = SO_RGB_ROOM_INTENSITY;
	_opcodes["roomFade"] = SO_ROOM_FADE;
	_opcodes["roomIntensity"] = SO_ROOM_INTENSITY;
	_opcodes["roomNewPalette"] = SO_ROOM_NEW_PALETTE;
	_opcodes["roomOps"] = OC_ROOM_OPS;
	_opcodes["roomPalette"] = SO_ROOM_PALETTE;
	_opcodes["roomSaveGame"] = SO_ROOM_SAVE_GAME;
	_opcodes["roomScreen"] = SO_ROOM_SCREEN;
	_opcodes["roomScroll"] = SO_ROOM_SCROLL;
	_opcodes["roomShadow"] = SO_ROOM_SHADOW;
	_opcodes["roomShakeOff"] = SO_ROOM_SHAKE_OFF;
	_opcodes["roomShakeOn"] = SO_ROOM_SHAKE_ON;
	_opcodes["roomTransform"] = SO_ROOM_TRANSFORM;
	_opcodes["saveDefault"] = SO_SAVE_DEFAULT;
	_opcodes["saveRestoreVerbs"] = OC_SAVE_RESTORE_VERBS;
	_opcodes["saveVerbs"] = SO_SAVE_VERBS;
	_opcodes["scale"] = SO_SCALE;
	_opcodes["setBlastObjectWindow"] = OC_SET_BLAST_OBJECT_WINDOW;
	_opcodes["setBoxFlags"] = OC_SET_BOX_FLAGS;
	_opcodes["setBoxSet"] = OC_SET_BOX_SET;
	_opcodes["setCameraAt"] = OC_SET_CAMERA_AT;
	_opcodes["setClass"] = OC_SET_CLASS;
	_opcodes["setObjectName"] = OC_SET_OBJECT_NAME;
	_opcodes["setOwner"] = OC_SET_OWNER;
	_opcodes["setState"] = OC_SET_STATE;
	_opcodes["shadow"] = SO_SHADOW;
	_opcodes["shuffle"] = OC_SHUFFLE;
	_opcodes["sound"] = SO_SOUND;
	_opcodes["soundKludge"] = OC_SOUND_KLUDGE;
	_opcodes["stampObject"] = OC_STAMP_OBJECT;
	_opcodes["standAnimation"] = SO_STAND_ANIMATION;
	_opcodes["startMusic"] = OC_START_MUSIC;
	_opcodes["startObject"] = OC_START_OBJECT;
	_opcodes["startObjectQuick"] = OC_START_OBJECT_QUICK;
	_opcodes["startScript"] = OC_START_SCRIPT;
	_opcodes["startScriptQuick"] = OC_START_SCRIPT_QUICK;
	_opcodes["startScriptQuick2"] = OC_START_SCRIPT_QUICK_2;
	_opcodes["startSound"] = OC_START_SOUND;
	_opcodes["stepDist"] = SO_STEP_DIST;
	_opcodes["stopMusic"] = OC_STOP_MUSIC;
	_opcodes["stopObjectCode"] = OC_STOP_OBJECT_CODE;
	_opcodes["stopObjectScript"] = OC_STOP_OBJECT_SCRIPT;
	_opcodes["stopScript"] = OC_STOP_SCRIPT;
	_opcodes["stopSentence"] = OC_STOP_SENTENCE;
	_opcodes["stopSound"] = OC_STOP_SOUND;
	_opcodes["stopTalking"] = OC_STOP_TALKING;
	_opcodes["stringArray"] = SO_STRING_ARRAY;
	_opcodes["sub"] = OC_SUB;
	_opcodes["systemOps"] = OC_SYSTEM_OPS;
	_opcodes["talkActor"] = OC_TALK_ACTOR;
	_opcodes["talkAnimation"] = SO_TALK_ANIMATION;
	_opcodes["talkColor"] = SO_TALK_COLOR;
	_opcodes["talkEgo"] = OC_TALK_EGO;
	_opcodes["textOffset"] = SO_TEXT_OFFSET;
	_opcodes["textString"] = SO_TEXTSTRING;
	_opcodes["undimArray"] = SO_UNDIM_ARRAY;
	_opcodes["unlockCostume"] = SO_UNLOCK_COSTUME;
	_opcodes["unlockRoom"] = SO_UNLOCK_ROOM;
	_opcodes["unlockScript"] = SO_UNLOCK_SCRIPT;
	_opcodes["unlockSound"] = SO_UNLOCK_SOUND;
	_opcodes["userputOff"] = SO_USERPUT_OFF;
	_opcodes["userputOn"] = SO_USERPUT_ON;
	_opcodes["userputSoftOff"] = SO_USERPUT_SOFT_OFF;
	_opcodes["userputSoftOn"] = SO_USERPUT_SOFT_ON;
	_opcodes["verbAt"] = SO_VERB_AT;
	_opcodes["verbBackcolor"] = SO_VERB_BACKCOLOR;
	_opcodes["verbCenter"] = SO_VERB_CENTER;
	_opcodes["verbColor"] = SO_VERB_COLOR;
	_opcodes["verbDelete"] = SO_VERB_DELETE;
	_opcodes["verbDim"] = SO_VERB_DIM;
	_opcodes["verbDimcolor"] = SO_VERB_DIMCOLOR;
	_opcodes["verbDraw"] = SO_VERB_DRAW;
	_opcodes["verbHicolor"] = SO_VERB_HICOLOR;
	_opcodes["verbImage"] = SO_VERB_IMAGE;
	_opcodes["verbImageInRoom"] = SO_VERB_IMAGE_IN_ROOM;
	_opcodes["verbKey"] = SO_VERB_KEY;
	_opcodes["verbName"] = SO_VERB_NAME;
	_opcodes["verbNameStr"] = SO_VERB_NAME_STR;
	_opcodes["verbNew"] = SO_VERB_NEW;
	_opcodes["verbOff"] = SO_VERB_OFF;
	_opcodes["verbOn"] = SO_VERB_ON;
	_opcodes["verbOps"] = OC_VERB_OPS;
	_opcodes["verbSetCurrent"] = SO_VERB_SET_CURRENT;
	_opcodes["wait"] = OC_WAIT;
	_opcodes["waitForActor"] = SO_WAIT_FOR_ACTOR;
	_opcodes["waitForAnimation"] = SO_WAIT_FOR_ANIMATION;
	_opcodes["waitForCamera"] = SO_WAIT_FOR_CAMERA;
	_opcodes["waitForMessage"] = SO_WAIT_FOR_MESSAGE;
	_opcodes["waitForSentence"] = SO_WAIT_FOR_SENTENCE;
	_opcodes["waitForTurn"] = SO_WAIT_FOR_TURN;
	_opcodes["walkActorTo"] = OC_WALK_ACTOR_TO;
	_opcodes["walkActorToObj"] = OC_WALK_ACTOR_TO_OBJ;
	_opcodes["walkAnimation"] = SO_WALK_ANIMATION;
	_opcodes["wordArrayDec"] = OC_WORD_ARRAY_DEC;
	_opcodes["wordArrayInc"] = OC_WORD_ARRAY_INC;
	_opcodes["wordArrayIndexedRead"] = OC_WORD_ARRAY_INDEXED_READ;
	_opcodes["wordArrayIndexedWrite"] = OC_WORD_ARRAY_INDEXED_WRITE;
	_opcodes["wordArrayRead"] = OC_WORD_ARRAY_READ;
	_opcodes["wordArrayWrite"] = OC_WORD_ARRAY_WRITE;
	_opcodes["wordVarDec"] = OC_WORD_VAR_DEC;
	_opcodes["wordVarInc"] = OC_WORD_VAR_INC;
	_opcodes["writeByteVar"] = OC_WRITE_BYTE_VAR;
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
					oss << _address << ": .byte ";
					break;
				case VALUE_WORD:
					oss << _address << ": .word ";
					break;
				case VALUE_STRING:
					oss << _address << ": .string ";
			}
			oss << (_pretty.empty() ? _value : '\"' + _pretty + '\"');
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
