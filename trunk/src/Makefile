BLOCKS_OBJ_FILES = blocks/AARY.o blocks/APAL.o blocks/BOXD.o blocks/BOXM.o blocks/CDHD.o blocks/DCHR.o blocks/DCOS.o blocks/DOBJ.o blocks/DROO.o blocks/DSCR.o blocks/DSOU.o blocks/CHAR.o blocks/COST.o blocks/CYCL.o blocks/ENCD.o blocks/EXCD.o blocks/IMHD.o blocks/IMxx.o blocks/LECF.o blocks/LFLF.o blocks/LOFF.o blocks/LSCR.o blocks/MAXS.o blocks/NLSC.o blocks/OBCD.o blocks/OBIM.o blocks/OBNA.o blocks/OFFS.o blocks/PALS.o blocks/RMHD.o blocks/RMIH.o blocks/RMIM.o blocks/RNAM.o blocks/ROOM.o blocks/SCAL.o blocks/SCRP.o blocks/SMAP.o blocks/SOU.o blocks/TRNS.o blocks/VCTL.o blocks/VERB.o blocks/VOC.o blocks/WRAP.o blocks/ZPxx.o
GRAMMAR_OBJ_FILES = grammar/Context.o grammar/Declaration.o grammar/Expression.o grammar/Function.o grammar/Instruction.o grammar/lex.yy.o grammar/Statement.o grammar/y.tab.o
TYPES_OBJ_FILES = types/Costume.o types/Charset.o types/Game.o types/Image.o types/Map.o types/Object.o types/Palette.o types/Room.o types/Voice.o
UTIL_OBJ_FILES = util/BMPFile.o util/IO.o util/Log.o util/XMLFile.o
OBJ_FILES = main.o ScummGEN.o $(BLOCKS_OBJ_FILES) $(GRAMMAR_OBJ_FILES) $(TYPES_OBJ_FILES) $(UTIL_OBJ_FILES)

CPP_FLAGS = -O2 -Wall -Wno-sign-compare -I. `xml2-config --cflags`
LD_FLAGS = `xml2-config --libs`

all: scummgen

scummgen : $(OBJ_FILES)
	g++ -o scummgen $(LD_FLAGS) $(OBJ_FILES)

main.o : main.cpp
	g++ -o main.o $(CPP_FLAGS) -c main.cpp

ScummGEN.o : ScummGEN.cpp
	g++ -o ScummGEN.o $(CPP_FLAGS) -c ScummGEN.cpp

blocks/AARY.o : blocks/AARY.cpp
	g++ -o blocks/AARY.o $(CPP_FLAGS) -c blocks/AARY.cpp

blocks/APAL.o : blocks/APAL.cpp
	g++ -o blocks/APAL.o $(CPP_FLAGS) -c blocks/APAL.cpp

blocks/BOXD.o : blocks/BOXD.cpp
	g++ -o blocks/BOXD.o $(CPP_FLAGS) -c blocks/BOXD.cpp

blocks/BOXM.o : blocks/BOXM.cpp
	g++ -o blocks/BOXM.o $(CPP_FLAGS) -c blocks/BOXM.cpp

blocks/CDHD.o : blocks/CDHD.cpp
	g++ -o blocks/CDHD.o $(CPP_FLAGS) -c blocks/CDHD.cpp

blocks/CHAR.o : blocks/CHAR.cpp
	g++ -o blocks/CHAR.o $(CPP_FLAGS) -c blocks/CHAR.cpp

blocks/COST.o : blocks/COST.cpp
	g++ -o blocks/COST.o $(CPP_FLAGS) -c blocks/COST.cpp

blocks/CYCL.o : blocks/CYCL.cpp
	g++ -o blocks/CYCL.o $(CPP_FLAGS) -c blocks/CYCL.cpp

blocks/DCHR.o : blocks/DCHR.cpp
	g++ -o blocks/DCHR.o $(CPP_FLAGS) -c blocks/DCHR.cpp

blocks/DCOS.o : blocks/DCOS.cpp
	g++ -o blocks/DCOS.o $(CPP_FLAGS) -c blocks/DCOS.cpp

blocks/DOBJ.o : blocks/DOBJ.cpp
	g++ -o blocks/DOBJ.o $(CPP_FLAGS) -c blocks/DOBJ.cpp

blocks/DROO.o : blocks/DROO.cpp
	g++ -o blocks/DROO.o $(CPP_FLAGS) -c blocks/DROO.cpp

blocks/DRSC.o : blocks/DRSC.cpp
	g++ -o blocks/DRSC.o $(CPP_FLAGS) -c blocks/DRSC.cpp

blocks/DSCR.o : blocks/DSCR.cpp
	g++ -o blocks/DSCR.o $(CPP_FLAGS) -c blocks/DSCR.cpp

blocks/DSOU.o : blocks/DSOU.cpp
	g++ -o blocks/DSOU.o $(CPP_FLAGS) -c blocks/DSOU.cpp

blocks/ENCD.o : blocks/ENCD.cpp
	g++ -o blocks/ENCD.o $(CPP_FLAGS) -c blocks/ENCD.cpp

blocks/EXCD.o : blocks/EXCD.cpp
	g++ -o blocks/EXCD.o $(CPP_FLAGS) -c blocks/EXCD.cpp

blocks/IMHD.o : blocks/IMHD.cpp
	g++ -o blocks/IMHD.o $(CPP_FLAGS) -c blocks/IMHD.cpp

blocks/IMxx.o : blocks/IMxx.cpp
	g++ -o blocks/IMxx.o $(CPP_FLAGS) -c blocks/IMxx.cpp

blocks/LECF.o : blocks/LECF.cpp
	g++ -o blocks/LECF.o $(CPP_FLAGS) -c blocks/LECF.cpp

blocks/LFLF.o : blocks/LFLF.cpp
	g++ -o blocks/LFLF.o $(CPP_FLAGS) -c blocks/LFLF.cpp

blocks/LOFF.o : blocks/LOFF.cpp
	g++ -o blocks/LOFF.o $(CPP_FLAGS) -c blocks/LOFF.cpp

blocks/LSCR.o : blocks/LSCR.cpp
	g++ -o blocks/LSCR.o $(CPP_FLAGS) -c blocks/LSCR.cpp

blocks/MAXS.o : blocks/MAXS.cpp
	g++ -o blocks/MAXS.o $(CPP_FLAGS) -c blocks/MAXS.cpp

blocks/NLSC.o : blocks/NLSC.cpp
	g++ -o blocks/NLSC.o $(CPP_FLAGS) -c blocks/NLSC.cpp

blocks/OBCD.o : blocks/OBCD.cpp
	g++ -o blocks/OBCD.o $(CPP_FLAGS) -c blocks/OBCD.cpp

blocks/OBIM.o : blocks/OBIM.cpp
	g++ -o blocks/OBIM.o $(CPP_FLAGS) -c blocks/OBIM.cpp

blocks/OBNA.o : blocks/OBNA.cpp
	g++ -o blocks/OBNA.o $(CPP_FLAGS) -c blocks/OBNA.cpp

blocks/OFFS.o : blocks/OFFS.cpp
	g++ -o blocks/OFFS.o $(CPP_FLAGS) -c blocks/OFFS.cpp

blocks/PALS.o : blocks/PALS.cpp
	g++ -o blocks/PALS.o $(CPP_FLAGS) -c blocks/PALS.cpp

blocks/RMHD.o : blocks/RMHD.cpp
	g++ -o blocks/RMHD.o $(CPP_FLAGS) -c blocks/RMHD.cpp

blocks/RMIH.o : blocks/RMIH.cpp
	g++ -o blocks/RMIH.o $(CPP_FLAGS) -c blocks/RMIH.cpp

blocks/RMIM.o : blocks/RMIM.cpp
	g++ -o blocks/RMIM.o $(CPP_FLAGS) -c blocks/RMIM.cpp

blocks/RNAM.o : blocks/RNAM.cpp
	g++ -o blocks/RNAM.o $(CPP_FLAGS) -c blocks/RNAM.cpp

blocks/ROOM.o : blocks/ROOM.cpp
	g++ -o blocks/ROOM.o $(CPP_FLAGS) -c blocks/ROOM.cpp

blocks/SCAL.o : blocks/SCAL.cpp
	g++ -o blocks/SCAL.o $(CPP_FLAGS) -c blocks/SCAL.cpp

blocks/SCRP.o : blocks/SCRP.cpp
	g++ -o blocks/SCRP.o $(CPP_FLAGS) -c blocks/SCRP.cpp

blocks/SMAP.o : blocks/SMAP.cpp
	g++ -o blocks/SMAP.o $(CPP_FLAGS) -c blocks/SMAP.cpp

blocks/SOU.o : blocks/SOU.cpp
	g++ -o blocks/SOU.o $(CPP_FLAGS) -c blocks/SOU.cpp

blocks/SOUN.o : blocks/SOUN.cpp
	g++ -o blocks/SOUN.o $(CPP_FLAGS) -c blocks/SOUN.cpp

blocks/VERB.o : blocks/VERB.cpp
	g++ -o blocks/VERB.o $(CPP_FLAGS) -c blocks/VERB.cpp

blocks/TRNS.o : blocks/TRNS.cpp
	g++ -o blocks/TRNS.o $(CPP_FLAGS) -c blocks/TRNS.cpp

blocks/VCTL.o : blocks/VCTL.cpp
	g++ -o blocks/VCTL.o $(CPP_FLAGS) -c blocks/VCTL.cpp

blocks/VOC.o : blocks/VOC.cpp
	g++ -o blocks/VOC.o $(CPP_FLAGS) -c blocks/VOC.cpp

blocks/WRAP.o : blocks/WRAP.cpp
	g++ -o blocks/WRAP.o $(CPP_FLAGS) -c blocks/WRAP.cpp

blocks/ZPxx.o : blocks/ZPxx.cpp
	g++ -o blocks/ZPxx.o $(CPP_FLAGS) -c blocks/ZPxx.cpp

grammar/Context.o : grammar/Context.cpp
	g++ -o grammar/Context.o $(CPP_FLAGS) -c grammar/Context.cpp

grammar/Declaration.o : grammar/Declaration.cpp
	g++ -o grammar/Declaration.o $(CPP_FLAGS) -c grammar/Declaration.cpp

grammar/Expression.o : grammar/Expression.cpp
	g++ -o grammar/Expression.o $(CPP_FLAGS) -c grammar/Expression.cpp

grammar/Function.o : grammar/Function.cpp
	g++ -o grammar/Function.o $(CPP_FLAGS) -c grammar/Function.cpp

grammar/Instruction.o : grammar/Instruction.cpp
	g++ -o grammar/Instruction.o $(CPP_FLAGS) -c grammar/Instruction.cpp

grammar/lex.yy.o : grammar/scummgen.l grammar/y.tab.o
	lex -o grammar/lex.yy.c grammar/scummgen.l
	g++ -o grammar/lex.yy.o $(CPP_FLAGS) -c grammar/lex.yy.c

grammar/Statement.o : grammar/Statement.cpp
	g++ -o grammar/Statement.o $(CPP_FLAGS) -c grammar/Statement.cpp

grammar/y.tab.o : grammar/scummgen.y
	yacc -d grammar/scummgen.y -o grammar/y.tab.c
	g++ -o grammar/y.tab.o $(CPP_FLAGS) -c grammar/y.tab.c

types/Charset.o : types/Charset.cpp
	g++ -o types/Charset.o $(CPP_FLAGS) -c types/Charset.cpp

types/Costume.o : types/Costume.cpp
	g++ -o types/Costume.o $(CPP_FLAGS) -c types/Costume.cpp

types/Game.o : types/Game.cpp
	g++ -o types/Game.o $(CPP_FLAGS) -c types/Game.cpp

types/Image.o : types/Image.cpp
	g++ -o types/Image.o $(CPP_FLAGS) -c types/Image.cpp

types/Map.o : types/Map.cpp
	g++ -o types/Map.o $(CPP_FLAGS) -c types/Map.cpp

types/Object.o : types/Object.cpp
	g++ -o types/Object.o $(CPP_FLAGS) -c types/Object.cpp

types/Palette.o : types/Palette.cpp
	g++ -o types/Palette.o $(CPP_FLAGS) -c types/Palette.cpp

types/Room.o : types/Room.cpp
	g++ -o types/Room.o $(CPP_FLAGS) -c types/Room.cpp

types/Voice.o : types/Voice.cpp
	g++ -o types/Voice.o $(CPP_FLAGS) -c types/Voice.cpp

util/BMPFile.o : util/BMPFile.cpp
	g++ -o util/BMPFile.o $(CPP_FLAGS) -c util/BMPFile.cpp

util/IO.o : util/IO.cpp
	g++ -o util/IO.o $(CPP_FLAGS) -c util/IO.cpp

util/Log.o : util/Log.cpp
	g++ -o util/Log.o $(CPP_FLAGS) -c util/Log.cpp

util/XMLFile.o : util/XMLFile.cpp
	g++ -o util/XMLFile.o $(CPP_FLAGS) -c util/XMLFile.cpp

.PHONY : clean

clean :
	find . -name "*.o" -delete
	find . -name "*~" -delete
	rm -rf grammar/lex.yy.c grammar/y.tab.c grammar/y.tab.h
