#ifndef _SCRIPT_HPP_
#define _SCRIPT_HPP_

#include <stdint.h>
#include <string>
#include <vector>
using namespace std;

class Script
{
private:
	static const uint8_t MIN_LOCAL_INDEX;
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

	static vector<Script *> _globalScriptsInstances;
	static vector<Script *> _localScriptsInstances;

	string _name;
	uint32_t _id;
	vector<uint8_t> _bytes;

	void writeByte(uint8_t byte);
	void writeWord(uint16_t word);
	void writeString(string s);
public:
	enum ScriptType {TYPE_GLOBAL, TYPE_LOCAL, TYPE_OTHER};

	static const string EXTENSION;

	static Script *getInstanceFromName(string scriptName);

	Script(string fileName, ScriptType type);
	string getName() { return _name; }
	uint32_t getID() { return _id; }
	uint32_t getNumberOfBytes() { return _bytes.size(); }
	uint32_t getByte(uint32_t index) { return _bytes[index]; }

	void asm_pushByte(uint8_t byte) { writeByte(OC_PUSH_BYTE); writeByte(byte); }
	void asm_pushWord(int16_t word) { writeByte(OC_PUSH_WORD); writeWord(word); }
	void asm_pushByteVar(uint8_t byteVar) { writeByte(OC_PUSH_BYTE_VAR); writeByte(byteVar); }
	void asm_pushWordVar(uint16_t wordVar) { writeByte(OC_PUSH_WORD_VAR); writeWord(wordVar); }
	void asm_byteArrayRead(uint8_t array) { writeByte(OC_BYTE_ARRAY_READ); writeByte(array); }
	void asm_wordArrayRead(uint16_t array) { writeByte(OC_WORD_ARRAY_READ); writeWord(array); }
	void asm_byteArrayIndexedRead(uint8_t array) { writeByte(OC_BYTE_ARRAY_INDEXED_READ); writeByte(array);  }
	void asm_wordArrayIndexedRead(uint16_t array) { writeByte(OC_WORD_ARRAY_INDEXED_READ); writeWord(array); }
	void asm_dup() { writeByte(OC_DUP); }
	void asm_not() { writeByte(OC_NOT); }
	void asm_eq() { writeByte(OC_EQ); }
	void asm_neq() { writeByte(OC_NEQ); }
	void asm_gt() { writeByte(OC_GT); }
	void asm_lt() { writeByte(OC_LT); }
	void asm_le() { writeByte(OC_LE); }
	void asm_ge() { writeByte(OC_GE); }
	void asm_add() { writeByte(OC_ADD); }
	void asm_sub() { writeByte(OC_SUB); }
	void asm_mul() { writeByte(OC_MUL); }
	void asm_div() { writeByte(OC_DIV); }
	void asm_land() { writeByte(OC_LAND); }
	void asm_lor() { writeByte(OC_LOR); }
	void asm_pop() { writeByte(OC_POP); }
	void asm_writeByteVar(uint8_t byteVar) { writeByte(OC_WRITE_BYTE_VAR); writeByte(byteVar); }
	void asm_writeWordVar(uint16_t wordVar) { writeByte(OC_WRITE_WORD_VAR); writeWord(wordVar); }
	void asm_byteArrayWrite(uint8_t array) { writeByte(OC_BYTE_ARRAY_WRITE); writeByte(array); }
	void asm_wordArrayWrite(uint16_t array) { writeByte(OC_WORD_ARRAY_WRITE); writeWord(array); }
	void asm_byteArrayIndexedWrite(uint8_t array) { writeByte(OC_BYTE_ARRAY_INDEXED_WRITE); writeByte(array); }
	void asm_wordArrayIndexedWrite(uint16_t array) { writeByte(OC_WORD_ARRAY_INDEXED_WRITE); writeWord(array); }
	void asm_byteVarInc(uint8_t byteVar) { writeByte(OC_BYTE_VAR_INC); writeByte(byteVar); }
	void asm_wordVarInc(uint16_t wordVar) { writeByte(OC_WORD_VAR_INC); writeWord(wordVar); }
	void asm_byteArrayInc(uint8_t array) { writeByte(OC_BYTE_ARRAY_INC); writeByte(array); }
	void asm_wordArrayInc(uint16_t array) { writeByte(OC_WORD_ARRAY_INC); writeWord(array); }
	void asm_byteVarDec(uint8_t byteVar) { writeByte(OC_BYTE_VAR_DEC); writeByte(byteVar); }
	void asm_wordVarDec(uint16_t wordVar) { writeByte(OC_WORD_VAR_DEC); writeWord(wordVar); }
	void asm_byteArrayDec(uint8_t array) { writeByte(OC_BYTE_ARRAY_DEC); writeByte(array); }
	void asm_wordArrayDec(uint16_t array) { writeByte(OC_WORD_ARRAY_DEC); writeWord(array); }
	void asm_if(int16_t offset) { writeByte(OC_IF); writeWord(offset); }
	void asm_ifNot(int16_t offset) { writeByte(OC_IF_NOT); writeWord(offset); }
	void asm_startScript() { writeByte(OC_START_SCRIPT); }
	void asm_startScriptQuick() { writeByte(OC_START_SCRIPT_QUICK); }
	void asm_startObject() { writeByte(OC_START_OBJECT); }
	void asm_drawObject() { writeByte(OC_DRAW_OBJECT); }
	void asm_drawObjectAt() { writeByte(OC_DRAW_OBJECT_AT); }
	void asm_drawBlastObject() { writeByte(OC_DRAW_BLAST_OBJECT); }
	void asm_setBlastObjectWindow() { writeByte(OC_SET_BLAST_OBJECT_WINDOW); }
	void asm_stopObjectCode() { writeByte(OC_STOP_OBJECT_CODE); }
	void asm_endCutscene() { writeByte(OC_END_CUTSCENE); }
	void asm_cutscene() { writeByte(OC_CUTSCENE); }
	void asm_stopMusic() { writeByte(OC_STOP_MUSIC); }
	void asm_freezeUnfreeze() { writeByte(OC_FREEZE_UNFREEZE); }
	void asm_cursorCommand() { writeByte(OC_CURSOR_COMMAND); }
	void asm_cursorCommand_cursorOn() { writeByte(SO_CURSOR_ON); }
	void asm_cursorCommand_cursorOff() { writeByte(SO_CURSOR_OFF); }
	void asm_cursorCommand_userputOn() { writeByte(SO_USERPUT_ON); }
	void asm_cursorCommand_userputOff() { writeByte(SO_USERPUT_OFF); }
	void asm_cursorCommand_cursorSoftOn() { writeByte(SO_CURSOR_SOFT_ON); }
	void asm_cursorCommand_cursorSoftOff() { writeByte(SO_CURSOR_SOFT_OFF); }
	void asm_cursorCommand_userputSoftOn() { writeByte(SO_USERPUT_SOFT_ON); }
	void asm_cursorCommand_userputSoftOff() { writeByte(SO_USERPUT_SOFT_OFF); }
	void asm_cursorCommand_cursorImage() { writeByte(SO_CURSOR_IMAGE); }
	void asm_cursorCommand_cursorHotspot() { writeByte(SO_CURSOR_HOTSPOT); }
	void asm_cursorCommand_charsetSet() { writeByte(SO_CHARSET_SET); }
	void asm_cursorCommand_charsetColor() { writeByte(SO_CHARSET_COLOR); }
	void asm_cursorCommand_cursorTransparent() { writeByte(SO_CURSOR_TRANSPARENT); }
	void asm_breakHere() { writeByte(OC_BREAK_HERE); }
	void asm_ifClassOfIs() { writeByte(OC_IF_CLASS_OF_IS); }
	void asm_setClass() { writeByte(OC_SET_CLASS); }
	void asm_getState() { writeByte(OC_GET_STATE); }
	void asm_setState() { writeByte(OC_SET_STATE); }
	void asm_setOwner() { writeByte(OC_SET_OWNER); }
	void asm_getOwner() { writeByte(OC_GET_OWNER); }
	void asm_jump(int16_t offset) { writeByte(OC_JUMP); writeWord(offset); }
	void asm_startSound() { writeByte(OC_START_SOUND); }
	void asm_stopSound() { writeByte(OC_STOP_SOUND); }
	void asm_startMusic() { writeByte(OC_STAR_MUSIC); }
	void asm_stopObjectScript() { writeByte(OC_STOP_OBJECT_SCRIPT); }
	void asm_panCameraTo() { writeByte(OC_PAN_CAMERA_TO); }
	void asm_actorFollowCamera() { writeByte(OC_ACTOR_FOLLOW_CAMERA); }
	void asm_setCameraAt() { writeByte(OC_SET_CAMERA_AT); }
	void asm_loadRoom() { writeByte(OC_LOAD_ROOM); }
	void asm_stopScript() { writeByte(OC_STOP_SCRIPT); }
	void asm_walkActorToObj() { writeByte(OC_WALK_ACTOR_TO_OBJ); }
	void asm_walkActorTo() { writeByte(OC_WALK_ACTOR_TO); }
	void asm_putActorAtXY() { writeByte(OC_PUT_ACTOR_AT_XY); }
	void asm_putActorAtObject() { writeByte(OC_PUT_ACTOR_AT_OBJECT); }
	void asm_faceActor() { writeByte(OC_FACE_ACTOR); }
	void asm_animateActor() { writeByte(OC_ANIMATE_ACTOR); }
	void asm_doSentence() { writeByte(OC_DO_SENTENCE); }
	void asm_pickupObject() { writeByte(OC_PICKUP_OBJECT); }
	void asm_loadRoomWithEgo() { writeByte(OC_LOAD_ROOM_WITH_EGO); }
	void asm_getRandomNumber() { writeByte(OC_GET_RANDOM_NUMBER); }
	void asm_getRandomNumberRange() { writeByte(OC_GET_RANDOM_NUMBER_RANGE); }
	void asm_getActorMoving() { writeByte(OC_GET_ACTOR_MOVING); }
	void asm_isScriptRunning() { writeByte(OC_IS_SCRIPT_RUNNING); }
	void asm_getActorRoom() { writeByte(OC_GET_ACTOR_ROOM); }
	void asm_getObjectX() { writeByte(OC_GET_OBJECT_X); }
	void asm_getObjectY() { writeByte(OC_GET_OBJECT_Y); }
	void asm_getObjectOldDir() { writeByte(OC_GET_OBJECT_OLD_DIR); }
	void asm_getActorWalkBox() { writeByte(OC_GET_ACTOR_WALK_BOX); }
	void asm_getActorCostume() { writeByte(OC_GET_ACTOR_COSTUME); }
	void asm_findInventory() { writeByte(OC_FIND_INVENTORY); }
	void asm_getInventoryCount() { writeByte(OC_GET_INVENTORY_COUNT); }
	void asm_getVerbFromXY() { writeByte(OC_GET_VERB_FROM_XY); }
	void asm_beginOverride() { writeByte(OC_BEGIN_OVERRIDE); }
	void asm_endOverride() { writeByte(OC_END_OVERRIDE); }
	void asm_setObjectName() { writeByte(OC_SET_OBJECT_NAME); }
	void asm_isSoundRunning() { writeByte(OC_IS_SOUND_RUNNING); }
	void asm_setBoxFlags() { writeByte(OC_SET_BOX_FLAGS); }
	void asm_createBoxMatrix() { writeByte(OC_CREATE_BOX_MATRIX); }
	void asm_resourceRoutines() { writeByte(OC_RESOURCE_ROUTINES); }
	void asm_resourceRoutines_loadScript() { writeByte(SO_LOAD_SCRIPT); }
	void asm_resourceRoutines_loadSound() { writeByte(SO_LOAD_SOUND); }
	void asm_resourceRoutines_loadCostume() { writeByte(SO_LOAD_COSTUME); }
	void asm_resourceRoutines_loadRoom() { writeByte(SO_LOAD_ROOM); }
	void asm_resourceRoutines_nukeScript() { writeByte(SO_NUKE_SCRIPT); }
	void asm_resourceRoutines_nukeSound() { writeByte(SO_NUKE_SOUND); }
	void asm_resourceRoutines_nukeCostume() { writeByte(SO_NUKE_COSTUME); }
	void asm_resourceRoutines_nukeRoom() { writeByte(SO_NUKE_ROOM); }
	void asm_resourceRoutines_lockScript() { writeByte(SO_LOCK_SCRIPT); }
	void asm_resourceRoutines_lockSound() { writeByte(SO_LOCK_SOUND); }
	void asm_resourceRoutines_lockCostume() { writeByte(SO_LOCK_COSTUME); }
	void asm_resourceRoutines_lockRoom() { writeByte(SO_LOCK_ROOM); }
	void asm_resourceRoutines_unlockScript() { writeByte(SO_UNLOCK_SCRIPT); }
	void asm_resourceRoutines_unlockSound() { writeByte(SO_UNLOCK_SOUND); }
	void asm_resourceRoutines_unlockCostume() { writeByte(SO_UNLOCK_COSTUME); }
	void asm_resourceRoutines_unlockRoom() { writeByte(SO_UNLOCK_ROOM); }
	void asm_resourceRoutines_clearHeap() { writeByte(SO_CLEAR_HEAP); }
	void asm_resourceRoutines_loadCharset() { writeByte(SO_LOAD_CHARSET); }
	void asm_resourceRoutines_nukeCharset() { writeByte(SO_NUKE_CHARSET); }
	void asm_resourceRoutines_loadObject() { writeByte(SO_LOAD_OBJECT); }
	void asm_roomOps() { writeByte(OC_ROOM_OPS); }
	void asm_roomOps_roomScroll() { writeByte(SO_ROOM_SCROLL); }
	void asm_roomOps_roomScreen() { writeByte(SO_ROOM_SCREEN); }
	void asm_roomOps_roomPalette() { writeByte(SO_ROOM_PALETTE); }
	void asm_roomOps_roomShakeOn() { writeByte(SO_ROOM_SHAKE_ON); }
	void asm_roomOps_roomShakeOff() { writeByte(SO_ROOM_SHAKE_OFF); }
	void asm_roomOps_roomIntensity() { writeByte(SO_ROOM_INTENSITY); }
	void asm_roomOps_roomSaveGame() { writeByte(SO_ROOM_SAVE_GAME); }
	void asm_roomOps_roomFade() { writeByte(SO_ROOM_FADE); }
	void asm_roomOps_roomRGBRoomIntensity() { writeByte(SO_RGB_ROOM_INTENSITY); }
	void asm_roomOps_roomShadow() { writeByte(SO_ROOM_SHADOW); }
	void asm_roomOps_roomTransform() { writeByte(SO_ROOM_TRANSFORM); }
	void asm_roomOps_cycleSpeed() { writeByte(SO_CYCLE_SPEED); }
	void asm_roomOps_roomNewPalette() { writeByte(SO_ROOM_NEW_PALETTE); }
	void asm_actorOps() { writeByte(OC_ACTOR_OPS); }
	void asm_actorOps_actorSetCurrent() { writeByte(SO_ACTOR_SET_CURRENT); }
	void asm_actorOps_costume() { writeByte(SO_COSTUME); }
	void asm_actorOps_stepDist() { writeByte(SO_STEP_DIST); }
	void asm_actorOps_sound() { writeByte(SO_SOUND); }
	void asm_actorOps_walkAnimation() { writeByte(SO_WALK_ANIMATION); }
	void asm_actorOps_talkAnimation() { writeByte(SO_TALK_ANIMATION); }
	void asm_actorOps_standAnimation() { writeByte(SO_STAND_ANIMATION); }
	void asm_actorOps_default() { writeByte(SO_DEFAULT); }
	void asm_actorOps_elevation() { writeByte(SO_ELEVATION); }
	void asm_actorOps_animationDefault() { writeByte(SO_ANIMATION_DEFAULT); }
	void asm_actorOps_palette() { writeByte(SO_PALETTE); }
	void asm_actorOps_talkColor() { writeByte(SO_TALK_COLOR); }
	void asm_actorOps_actorName() { writeByte(SO_ACTOR_NAME); }
	void asm_actorOps_initAnimation() { writeByte(SO_INIT_ANIMATION); }
	void asm_actorOps_actorWidth() { writeByte(SO_ACTOR_WIDTH); }
	void asm_actorOps_scale() { writeByte(SO_SCALE); }
	void asm_actorOps_neverZClip() { writeByte(SO_NEVER_ZCLIP); }
	void asm_actorOps_alwaysZClip() { writeByte(SO_ALWAYS_ZCLIP); }
	void asm_actorOps_ignoreBoxes() { writeByte(SO_IGNORE_BOXES); }
	void asm_actorOps_followBoxes() { writeByte(SO_FOLLOW_BOXES); }
	void asm_actorOps_animationSpeed() { writeByte(SO_ANIMATION_SPEED); }
	void asm_actorOps_shadow() { writeByte(SO_SHADOW); }
	void asm_actorOps_textOffset() { writeByte(SO_TEXT_OFFSET); }
	void asm_actorOps_actorVariable() { writeByte(SO_ACTOR_VARIABLE); }
	void asm_actorOps_actorIgnoreTurnsOn() { writeByte(SO_ACTOR_IGNORE_TURNS_ON); }
	void asm_actorOps_actorIgnoreTurnsOff() { writeByte(SO_ACTOR_IGNORE_TURNS_OFF); }
	void asm_actorOps_actorNew() { writeByte(SO_ACTOR_NEW); }
	void asm_actorOps_actorDepth() { writeByte(SO_ACTOR_DEPTH); }
	void asm_actorOps_actorWalkScript() { writeByte(SO_ACTOR_WALK_SCRIPT); }
	void asm_actorOps_actorStop() { writeByte(SO_ACTOR_STOP); }
	void asm_actorOps_actorSetDirection() { writeByte(SO_ACTOR_SET_DIRECTION); }
	void asm_actorOps_actorTurnToDirection() { writeByte(SO_ACTOR_TURN_TO_DIRECTION); }
	void asm_actorOps_actorWalkPause() { writeByte(SO_ACTOR_WALK_PAUSE); }
	void asm_actorOps_actorWalkResume() { writeByte(SO_ACTOR_WALK_RESUME); }
	void asm_actorOps_actorTalkScript() { writeByte(SO_ACTOR_TALK_SCRIPT); }
	void asm_verbOps() { writeByte(OC_VERB_OPS); }
	void asm_verbOps_verbSetCurrent() { writeByte(SO_VERB_SET_CURRENT); }
	void asm_verbOps_verbImage() { writeByte(SO_VERB_IMAGE); }
	void asm_verbOps_verbName() { writeByte(SO_VERB_NAME); }
	void asm_verbOps_verbColor() { writeByte(SO_VERB_COLOR); }
	void asm_verbOps_verbHicolor() { writeByte(SO_VERB_HICOLOR); }
	void asm_verbOps_verbAt() { writeByte(SO_VERB_AT); }
	void asm_verbOps_verbOn() { writeByte(SO_VERB_ON); }
	void asm_verbOps_verbOff() { writeByte(SO_VERB_OFF); }
	void asm_verbOps_verbDelete() { writeByte(SO_VERB_DELETE); }
	void asm_verbOps_verbNew() { writeByte(SO_VERB_NEW); }
	void asm_verbOps_verbDimcolor() { writeByte(SO_VERB_DIMCOLOR); }
	void asm_verbOps_verbDim() { writeByte(SO_VERB_DIM); }
	void asm_verbOps_verbKey() { writeByte(SO_VERB_KEY); }
	void asm_verbOps_verbCenter() { writeByte(SO_VERB_CENTER); }
	void asm_verbOps_verbNameStr() { writeByte(SO_VERB_NAME_STR); }
	void asm_verbOps_verbImageInRoom() { writeByte(SO_VERB_IMAGE_IN_ROOM); }
	void asm_verbOps_verbBackcolor() { writeByte(SO_VERB_BACKCOLOR); }
	void asm_verbOps_verbDraw() { writeByte(SO_VERB_DRAW); }
	void asm_getActorFromXY() { writeByte(OC_GET_ACTOR_FROM_XY); }
	void asm_findObject() { writeByte(OC_FIND_OBJECT); }
	void asm_pseudoRoom() { writeByte(OC_PSEUDO_ROOM); }
	void asm_getActorElevation() { writeByte(OC_GET_ACTOR_ELEVATION); }
	void asm_getVerbEntrypoint() { writeByte(OC_GET_VERB_ENTRY_POINT); }
	void asm_arrayOps() { writeByte(OC_ARRAY_OPS); }
	void asm_arrayOps_assignString() { writeByte(SO_ASSIGN_STRING); }
	void asm_arrayOps_assignIntList() { writeByte(SO_ASSIGN_INT_LIST); }
	void asm_arrayOps_assign2DimList() { writeByte(SO_ASSIGN_2DIM_LIST); }
	void asm_saveRestoreVerbs() { writeByte(OC_SAVE_RESTORE_VERBS); }
	void asm_saveRestoreVerbs_saveVerbs() { writeByte(SO_SAVE_VERBS); }
	void asm_saveRestoreVerbs_restoreVerbs() { writeByte(SO_RESTORE_VERBS); }
	void asm_saveRestoreVerbs_deleteVerbs() { writeByte(SO_DELETE_VERBS); }
	void asm_drawBox() { writeByte(OC_DRAW_BOX); }
	void asm_getActorWidth() { writeByte(OC_GET_ACTOR_WIDTH); }
	void asm_wait() { writeByte(OC_WAIT); }
	void asm_wait_waitForActor(int16_t offset) { writeByte(SO_WAIT_FOR_ACTOR); writeWord(offset); }
	void asm_wait_waitForMessage() { writeByte(SO_WAIT_FOR_MESSAGE); }
	void asm_wait_waitForCamera() { writeByte(SO_WAIT_FOR_CAMERA); }
	void asm_wait_waitForSentence() { writeByte(SO_WAIT_FOR_SENTENCE); }
	void asm_wait_waitForAnimation(int16_t offset) { writeByte(SO_WAIT_FOR_ANIMATION); writeWord(offset); }
	void asm_wait_waitForTurn(int16_t offset) { writeByte(SO_WAIT_FOR_TURN); writeWord(offset); }
	void asm_getActorScaleX() { writeByte(OC_GET_ACTOR_SCALE_X); }
	void asm_getActorAnimCounter() { writeByte(OC_GET_ACTOR_ANIM_COUNTER); }
	void asm_soundKludge() { writeByte(OC_SOUND_KLUDGE); }
	void asm_isAnyOf() { writeByte(OC_IS_ANY_OF); }
	void asm_systemOps() { writeByte(OC_SYSTEM_OPS); }
	void asm_systemOps_restart() { writeByte(SO_RESTART); }
	void asm_systemOps_pause() { writeByte(SO_PAUSE); }
	void asm_systemOps_quit() { writeByte(SO_QUIT); }
	void asm_isActorInBox() { writeByte(OC_IS_ACTOR_IN_BOX); }
	void asm_delay() { writeByte(OC_DELAY); }
	void asm_delaySeconds() { writeByte(OC_DELAY_SECONDS); }
	void asm_delayMinutes() { writeByte(OC_DELAY_MINUTES); }
	void asm_stopSentence() { writeByte(OC_STOP_SENTENCE); }
	void asm_printLine() { writeByte(OC_PRINT_LINE); }
	void asm_printText() { writeByte(OC_PRINT_TEXT); }
	void asm_printDebug() { writeByte(OC_PRINT_DEBUG); }
	void asm_printSystem() { writeByte(OC_PRINT_SYSTEM); }
	void asm_printActor() { writeByte(OC_PRINT_ACTOR); }
	void asm_printEgo() { writeByte(OC_PRINT_EGO); }
	void asm_print_at() { writeByte(SO_AT); }
	void asm_print_color() { writeByte(SO_COLOR); }
	void asm_print_clipped() { writeByte(SO_CLIPPED); }
	void asm_print_center() { writeByte(SO_CENTER); }
	void asm_print_left() { writeByte(SO_LEFT); }
	void asm_print_overhead() { writeByte(SO_OVERHEAD); }
	void asm_print_mumble() { writeByte(SO_MUMBLE); }
	void asm_print_textstring(string s) { writeByte(SO_TEXTSTRING); writeString(s); }
	void asm_print_loadDefault() { writeByte(SO_LOAD_DEFAULT); }
	void asm_print_saveDefault() { writeByte(SO_SAVE_DEFAULT); }
	void asm_talkActor() { writeByte(OC_TALK_ACTOR); }
	void asm_talkEgo() { writeByte(OC_TALK_EGO); }
	void asm_dimArray() { writeByte(OC_DIM_ARRAY); }
	void asm_dimArray_intArray(uint16_t array) { writeByte(SO_INT_ARRAY); writeWord(array); }
	void asm_dimArray_bitArray(uint16_t array) { writeByte(SO_BIT_ARRAY); writeWord(array); }
	void asm_dimArray_nibbleArray(uint16_t array) { writeByte(SO_NIBBLE_ARRAY); writeWord(array); }
	void asm_dimArray_byteArray(uint16_t array) { writeByte(SO_BYTE_ARRAY); writeWord(array); }
	void asm_dimArray_stringArray(uint16_t array) { writeByte(SO_STRING_ARRAY); writeWord(array); }
	void asm_dimArray_undimArray(uint16_t array) { writeByte(SO_UNDIM_ARRAY); writeWord(array); }
	void asm_dummy() { writeByte(OC_DUMMY); }
	void asm_startObjectQuick() { writeByte(OC_START_OBJECT_QUICK); }
	void asm_startScriptQuick2() { writeByte(OC_START_SCRIPT_QUICK_2); }
	void asm_dim2dimArray() { writeByte(OC_DIM_2_DIM_ARRAY); }
	void asm_abs() { writeByte(OC_ABS); }
	void asm_distObjectObject() { writeByte(OC_DIST_OBJECT_OBJECT); }
	void asm_distObjectPt() { writeByte(OC_DIST_OBJECT_PT); }
	void asm_distPtPt() { writeByte(OC_DIST_PT_PT); }
	void asm_kernelGetFunctions() { writeByte(OC_KERNEL_GET_FUNCTIONS); }
	void asm_kernelSetFunctions() { writeByte(OC_KERNEL_SET_FUNCTIONS); }
	void asm_delayFrames() { writeByte(OC_DELAY_FRAMES); }
	void asm_pickOneOf() { writeByte(OC_PICK_ONE_OF); }
	void asm_pickOneOfDefault() { writeByte(OC_PICK_ONE_OF_DEFAULT); }
	void asm_stampObject() { writeByte(OC_STAMP_OBJECT); }
	void asm_getDateTime() { writeByte(OC_GET_DATE_TIME); }
	void asm_stopTalking() { writeByte(OC_STOP_TALKING); }
	void asm_getAnimateVariable() { writeByte(OC_GET_ANIMATE_VARIABLE); }
	void asm_shuffle(uint16_t array) { writeByte(OC_SHUFFLE); writeWord(array); }
	void asm_jumpToScript() { writeByte(OC_JUMP_TO_SCRIPT); }
	void asm_band() { writeByte(OC_BAND); }
	void asm_bor() { writeByte(OC_BOR); }
	void asm_isRoomScriptRunning() { writeByte(OC_IS_ROOM_SCRIPT_RUNNING); }
	void asm_findAllObjects() { writeByte(OC_FIND_ALL_OBJECTS); }
	void asm_getPixel() { writeByte(OC_GET_PIXEL); }
	void asm_pickVarRandom(uint16_t array) { writeByte(OC_PICK_VAR_RANDOM); writeWord(array); }
	void asm_setBoxSet() { writeByte(OC_SET_BOX_SET); }
	void asm_getActorLayer() { writeByte(OC_GET_ACTOR_LAYER); }
	void asm_getObjectNewDir() { writeByte(OC_GET_OBJECT_NEW_DIR); }

	~Script();
};

#endif

