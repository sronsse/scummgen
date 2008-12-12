#ifndef _INSTRUCTION_HPP_
#define _INSTRUCTION_HPP_

#include <map>
#include <string>
#include <stdint.h>
#include <vector>
using namespace std;

typedef enum
{
	VALUE_NULL,
	VALUE_BYTE,
	VALUE_WORD,
	VALUE_STRING
} ValueType;

typedef enum
{
	INSTRUCTION_OPCODE,
	INSTRUCTION_VALUE,
	INSTRUCTION_LABEL
} InstructionType;

class Instruction
{
private:
	static const uint8_t OC_PUSH_BYTE;
	static const uint8_t OC_PUSH_WORD;
	static const uint8_t OC_PUSH_BYTE_VAR;
	static const uint8_t OC_PUSH_WORD_VAR;
	static const uint8_t OC_BYTE_ARRAY_READ;
	static const uint8_t OC_WORD_ARRAY_READ;
	static const uint8_t OC_BYTE_ARRAY_INDEXED_READ;
	static const uint8_t OC_WORD_ARRAY_INDEXED_READ;
	static const uint8_t OC_DUP;
	static const uint8_t OC_NOT;
	static const uint8_t OC_EQ;
	static const uint8_t OC_NEQ;
	static const uint8_t OC_GT;
	static const uint8_t OC_LT;
	static const uint8_t OC_LE;
	static const uint8_t OC_GE;
	static const uint8_t OC_ADD;
	static const uint8_t OC_SUB;
	static const uint8_t OC_MUL;
	static const uint8_t OC_DIV;
	static const uint8_t OC_LAND;
	static const uint8_t OC_LOR;
	static const uint8_t OC_POP;
	static const uint8_t OC_WRITE_BYTE_VAR;
	static const uint8_t OC_WRITE_WORD_VAR;
	static const uint8_t OC_BYTE_ARRAY_WRITE;
	static const uint8_t OC_WORD_ARRAY_WRITE;
	static const uint8_t OC_BYTE_ARRAY_INDEXED_WRITE;
	static const uint8_t OC_WORD_ARRAY_INDEXED_WRITE;
	static const uint8_t OC_BYTE_VAR_INC;
	static const uint8_t OC_WORD_VAR_INC;
	static const uint8_t OC_BYTE_ARRAY_INC;
	static const uint8_t OC_WORD_ARRAY_INC;
	static const uint8_t OC_BYTE_VAR_DEC;
	static const uint8_t OC_WORD_VAR_DEC;
	static const uint8_t OC_BYTE_ARRAY_DEC;
	static const uint8_t OC_WORD_ARRAY_DEC;
	static const uint8_t OC_IF;
	static const uint8_t OC_IF_NOT;
	static const uint8_t OC_START_SCRIPT;
	static const uint8_t OC_START_SCRIPT_QUICK;
	static const uint8_t OC_START_OBJECT;
	static const uint8_t OC_DRAW_OBJECT;
	static const uint8_t OC_DRAW_OBJECT_AT;
	static const uint8_t OC_DRAW_BLAST_OBJECT;
	static const uint8_t OC_SET_BLAST_OBJECT_WINDOW;
	static const uint8_t OC_STOP_OBJECT_CODE;
	static const uint8_t OC_END_CUTSCENE;
	static const uint8_t OC_CUTSCENE;
	static const uint8_t OC_STOP_MUSIC;
	static const uint8_t OC_FREEZE_UNFREEZE;
	static const uint8_t OC_CURSOR_COMMAND;
		static const uint8_t SO_CURSOR_ON;
		static const uint8_t SO_CURSOR_OFF;
		static const uint8_t SO_USERPUT_ON;
		static const uint8_t SO_USERPUT_OFF;
		static const uint8_t SO_CURSOR_SOFT_ON;
		static const uint8_t SO_CURSOR_SOFT_OFF;
		static const uint8_t SO_USERPUT_SOFT_ON;
		static const uint8_t SO_USERPUT_SOFT_OFF;
		static const uint8_t SO_CURSOR_IMAGE;
		static const uint8_t SO_CURSOR_HOTSPOT;
		static const uint8_t SO_CHARSET_SET;
		static const uint8_t SO_CHARSET_COLOR;
		static const uint8_t SO_CURSOR_TRANSPARENT;
	static const uint8_t OC_BREAK_HERE;
	static const uint8_t OC_IF_CLASS_OF_IS;
	static const uint8_t OC_SET_CLASS;
	static const uint8_t OC_GET_STATE;
	static const uint8_t OC_SET_STATE;
	static const uint8_t OC_SET_OWNER;
	static const uint8_t OC_GET_OWNER;
	static const uint8_t OC_JUMP;
	static const uint8_t OC_START_SOUND;
	static const uint8_t OC_STOP_SOUND;
	static const uint8_t OC_STAR_MUSIC;
	static const uint8_t OC_STOP_OBJECT_SCRIPT;
	static const uint8_t OC_PAN_CAMERA_TO;
	static const uint8_t OC_ACTOR_FOLLOW_CAMERA;
	static const uint8_t OC_SET_CAMERA_AT;
	static const uint8_t OC_LOAD_ROOM;
	static const uint8_t OC_STOP_SCRIPT;
	static const uint8_t OC_WALK_ACTOR_TO_OBJ;
	static const uint8_t OC_WALK_ACTOR_TO;
	static const uint8_t OC_PUT_ACTOR_AT_XY;
	static const uint8_t OC_PUT_ACTOR_AT_OBJECT;
	static const uint8_t OC_FACE_ACTOR;
	static const uint8_t OC_ANIMATE_ACTOR;
	static const uint8_t OC_DO_SENTENCE;
	static const uint8_t OC_PICKUP_OBJECT;
	static const uint8_t OC_LOAD_ROOM_WITH_EGO;
	static const uint8_t OC_GET_RANDOM_NUMBER;
	static const uint8_t OC_GET_RANDOM_NUMBER_RANGE;
	static const uint8_t OC_GET_ACTOR_MOVING;
	static const uint8_t OC_IS_SCRIPT_RUNNING;
	static const uint8_t OC_GET_ACTOR_ROOM;
	static const uint8_t OC_GET_OBJECT_X;
	static const uint8_t OC_GET_OBJECT_Y;
	static const uint8_t OC_GET_OBJECT_OLD_DIR;
	static const uint8_t OC_GET_ACTOR_WALK_BOX;
	static const uint8_t OC_GET_ACTOR_COSTUME;
	static const uint8_t OC_FIND_INVENTORY;
	static const uint8_t OC_GET_INVENTORY_COUNT;
	static const uint8_t OC_GET_VERB_FROM_XY;
	static const uint8_t OC_BEGIN_OVERRIDE;
	static const uint8_t OC_END_OVERRIDE;
	static const uint8_t OC_SET_OBJECT_NAME;
	static const uint8_t OC_IS_SOUND_RUNNING;
	static const uint8_t OC_SET_BOX_FLAGS;
	static const uint8_t OC_CREATE_BOX_MATRIX;
	static const uint8_t OC_RESOURCE_ROUTINES;
		static const uint8_t SO_LOAD_SCRIPT;
		static const uint8_t SO_LOAD_SOUND;
		static const uint8_t SO_LOAD_COSTUME;
		static const uint8_t SO_LOAD_ROOM;
		static const uint8_t SO_NUKE_SCRIPT;
		static const uint8_t SO_NUKE_SOUND;
		static const uint8_t SO_NUKE_COSTUME;
		static const uint8_t SO_NUKE_ROOM;
		static const uint8_t SO_LOCK_SCRIPT;
		static const uint8_t SO_LOCK_SOUND;
		static const uint8_t SO_LOCK_COSTUME;
		static const uint8_t SO_LOCK_ROOM;
		static const uint8_t SO_UNLOCK_SCRIPT;
		static const uint8_t SO_UNLOCK_SOUND;
		static const uint8_t SO_UNLOCK_COSTUME;
		static const uint8_t SO_UNLOCK_ROOM;
		static const uint8_t SO_CLEAR_HEAP;
		static const uint8_t SO_LOAD_CHARSET;
		static const uint8_t SO_NUKE_CHARSET;
		static const uint8_t SO_LOAD_OBJECT;
	static const uint8_t OC_ROOM_OPS;
		static const uint8_t SO_ROOM_SCROLL;
		static const uint8_t SO_ROOM_SCREEN;
		static const uint8_t SO_ROOM_PALETTE;
		static const uint8_t SO_ROOM_SHAKE_ON;
		static const uint8_t SO_ROOM_SHAKE_OFF;
		static const uint8_t SO_ROOM_INTENSITY;
		static const uint8_t SO_ROOM_SAVE_GAME;
		static const uint8_t SO_ROOM_FADE;
		static const uint8_t SO_RGB_ROOM_INTENSITY;
		static const uint8_t SO_ROOM_SHADOW;
		static const uint8_t SO_ROOM_TRANSFORM;
		static const uint8_t SO_CYCLE_SPEED;
		static const uint8_t SO_ROOM_NEW_PALETTE;
	static const uint8_t OC_ACTOR_OPS;
		static const uint8_t SO_ACTOR_SET_CURRENT;
		static const uint8_t SO_COSTUME;
		static const uint8_t SO_STEP_DIST;
		static const uint8_t SO_SOUND;
		static const uint8_t SO_WALK_ANIMATION;
		static const uint8_t SO_TALK_ANIMATION;
		static const uint8_t SO_STAND_ANIMATION;
		static const uint8_t SO_DEFAULT;
		static const uint8_t SO_ELEVATION;
		static const uint8_t SO_ANIMATION_DEFAULT;
		static const uint8_t SO_PALETTE;
		static const uint8_t SO_TALK_COLOR;
		static const uint8_t SO_ACTOR_NAME;
		static const uint8_t SO_INIT_ANIMATION;
		static const uint8_t SO_ACTOR_WIDTH;
		static const uint8_t SO_SCALE;
		static const uint8_t SO_NEVER_ZCLIP;
		static const uint8_t SO_ALWAYS_ZCLIP;
		static const uint8_t SO_IGNORE_BOXES;
		static const uint8_t SO_FOLLOW_BOXES;
		static const uint8_t SO_ANIMATION_SPEED;
		static const uint8_t SO_SHADOW;
		static const uint8_t SO_TEXT_OFFSET;
		static const uint8_t SO_ACTOR_VARIABLE;
		static const uint8_t SO_ACTOR_IGNORE_TURNS_ON;
		static const uint8_t SO_ACTOR_IGNORE_TURNS_OFF;
		static const uint8_t SO_ACTOR_NEW;
		static const uint8_t SO_ACTOR_DEPTH;
		static const uint8_t SO_ACTOR_WALK_SCRIPT;
		static const uint8_t SO_ACTOR_STOP;
		static const uint8_t SO_ACTOR_SET_DIRECTION;
		static const uint8_t SO_ACTOR_TURN_TO_DIRECTION;
		static const uint8_t SO_ACTOR_WALK_PAUSE;
		static const uint8_t SO_ACTOR_WALK_RESUME;
		static const uint8_t SO_ACTOR_TALK_SCRIPT;
	static const uint8_t OC_VERB_OPS;
		static const uint8_t SO_VERB_SET_CURRENT;
		static const uint8_t SO_VERB_IMAGE;
		static const uint8_t SO_VERB_NAME;
		static const uint8_t SO_VERB_COLOR;
		static const uint8_t SO_VERB_HICOLOR;
		static const uint8_t SO_VERB_AT;
		static const uint8_t SO_VERB_ON;
		static const uint8_t SO_VERB_OFF;
		static const uint8_t SO_VERB_DELETE;
		static const uint8_t SO_VERB_NEW;
		static const uint8_t SO_VERB_DIMCOLOR;
		static const uint8_t SO_VERB_DIM;
		static const uint8_t SO_VERB_KEY;
		static const uint8_t SO_VERB_CENTER;
		static const uint8_t SO_VERB_NAME_STR;
		static const uint8_t SO_VERB_IMAGE_IN_ROOM;
		static const uint8_t SO_VERB_BACKCOLOR;
		static const uint8_t SO_VERB_DRAW;
	static const uint8_t OC_GET_ACTOR_FROM_XY;
	static const uint8_t OC_FIND_OBJECT;
	static const uint8_t OC_PSEUDO_ROOM;
	static const uint8_t OC_GET_ACTOR_ELEVATION;
	static const uint8_t OC_GET_VERB_ENTRY_POINT;
	static const uint8_t OC_ARRAY_OPS;
		static const uint8_t SO_ASSIGN_STRING;
		static const uint8_t SO_ASSIGN_INT_LIST;
		static const uint8_t SO_ASSIGN_2DIM_LIST;
	static const uint8_t OC_SAVE_RESTORE_VERBS;
		static const uint8_t SO_SAVE_VERBS;
		static const uint8_t SO_RESTORE_VERBS;
		static const uint8_t SO_DELETE_VERBS;
	static const uint8_t OC_DRAW_BOX;
	static const uint8_t OC_GET_ACTOR_WIDTH;
	static const uint8_t OC_WAIT;
		static const uint8_t SO_WAIT_FOR_ACTOR;
		static const uint8_t SO_WAIT_FOR_MESSAGE;
		static const uint8_t SO_WAIT_FOR_CAMERA;
		static const uint8_t SO_WAIT_FOR_SENTENCE;
		static const uint8_t SO_WAIT_FOR_ANIMATION;
		static const uint8_t SO_WAIT_FOR_TURN;
	static const uint8_t OC_GET_ACTOR_SCALE_X;
	static const uint8_t OC_GET_ACTOR_ANIM_COUNTER;
	static const uint8_t OC_SOUND_KLUDGE;
	static const uint8_t OC_IS_ANY_OF;
	static const uint8_t OC_SYSTEM_OPS;
		static const uint8_t SO_RESTART;
		static const uint8_t SO_PAUSE;
		static const uint8_t SO_QUIT;
	static const uint8_t OC_IS_ACTOR_IN_BOX;
	static const uint8_t OC_DELAY;
	static const uint8_t OC_DELAY_SECONDS;
	static const uint8_t OC_DELAY_MINUTES;
	static const uint8_t OC_STOP_SENTENCE;
	static const uint8_t OC_PRINT_LINE;
	static const uint8_t OC_PRINT_TEXT;
	static const uint8_t OC_PRINT_DEBUG;
	static const uint8_t OC_PRINT_SYSTEM;
	static const uint8_t OC_PRINT_ACTOR;
	static const uint8_t OC_PRINT_EGO;
		static const uint8_t SO_AT;
		static const uint8_t SO_COLOR;
		static const uint8_t SO_CLIPPED;
		static const uint8_t SO_CENTER;
		static const uint8_t SO_LEFT;
		static const uint8_t SO_OVERHEAD;
		static const uint8_t SO_MUMBLE;
		static const uint8_t SO_TEXTSTRING;
		static const uint8_t SO_LOAD_DEFAULT;
		static const uint8_t SO_SAVE_DEFAULT;
	static const uint8_t OC_TALK_ACTOR;
	static const uint8_t OC_TALK_EGO;
	static const uint8_t OC_DIM_ARRAY;
		static const uint8_t SO_INT_ARRAY;
		static const uint8_t SO_BIT_ARRAY;
		static const uint8_t SO_NIBBLE_ARRAY;
		static const uint8_t SO_BYTE_ARRAY;
		static const uint8_t SO_STRING_ARRAY;
		static const uint8_t SO_UNDIM_ARRAY;
	static const uint8_t OC_DUMMY;
	static const uint8_t OC_START_OBJECT_QUICK;
	static const uint8_t OC_START_SCRIPT_QUICK_2;
	static const uint8_t OC_DIM_2_DIM_ARRAY;
	static const uint8_t OC_ABS;
	static const uint8_t OC_DIST_OBJECT_OBJECT;
	static const uint8_t OC_DIST_OBJECT_PT;
	static const uint8_t OC_DIST_PT_PT;
	static const uint8_t OC_KERNEL_GET_FUNCTIONS;
	static const uint8_t OC_KERNEL_SET_FUNCTIONS;
	static const uint8_t OC_DELAY_FRAMES;
	static const uint8_t OC_PICK_ONE_OF;
	static const uint8_t OC_PICK_ONE_OF_DEFAULT;
	static const uint8_t OC_STAMP_OBJECT;
	static const uint8_t OC_GET_DATE_TIME;
	static const uint8_t OC_STOP_TALKING;
	static const uint8_t OC_GET_ANIMATE_VARIABLE;
	static const uint8_t OC_SHUFFLE;
	static const uint8_t OC_JUMP_TO_SCRIPT;
	static const uint8_t OC_BAND;
	static const uint8_t OC_BOR;
	static const uint8_t OC_IS_ROOM_SCRIPT_RUNNING;
	static const uint8_t OC_FIND_ALL_OBJECTS;
	static const uint8_t OC_GET_PIXEL;
	static const uint8_t OC_PICK_VAR_RANDOM;
	static const uint8_t OC_SET_BOX_SET;
	static const uint8_t OC_GET_ACTOR_LAYER;
	static const uint8_t OC_GET_OBJECT_NEW_DIR;

	static map<string, uint8_t> _opcodes;

	InstructionType _type;
	uint32_t _address;
	string _opcodeName;
	ValueType _valueType;
	string _value;
	string _pretty;
	uint32_t _label;

	static int16_t toInteger(string s);
public:
	static void setOpcodes();

	Instruction(string opcodeName);
	Instruction(ValueType valueType, string value, string pretty = "");
	Instruction(uint32_t label);
	InstructionType getType() { return _type; }
	uint32_t getAddress() { return _address; }
	string getOpcodeName() { return _opcodeName; }
	string getValue() { return _value; }
	void setValue(string value) { _value = value; }
	uint32_t getLabel() { return _label; }
	string toString();
	void assemble(vector<uint8_t> &byteCode);
	~Instruction();
};

#endif
