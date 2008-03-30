INDEX_OBJ_FILES = blocks/index/AARY.o blocks/index/DCHR.o blocks/index/DCOS.o blocks/index/DOBJ.o blocks/index/DROO.o blocks/index/DRSC.o blocks/index/DSCR.o blocks/index/DSOU.o blocks/index/MAXS.o blocks/index/RNAM.o
RESOURCE_OBJ_FILES = blocks/resource/AKCD.o blocks/resource/AKCH.o blocks/resource/AKCI.o blocks/resource/AKHD.o blocks/resource/AKOF.o blocks/resource/AKOS.o blocks/resource/AKPL.o blocks/resource/AKSQ.o blocks/resource/APAL.o blocks/resource/BOMP.o blocks/resource/BOXD.o blocks/resource/BOXM.o blocks/resource/BSTR.o blocks/resource/CDHD.o blocks/resource/CYCL.o blocks/resource/ENCD.o blocks/resource/EXCD.o blocks/resource/FRMT.o blocks/resource/IMAG.o blocks/resource/IMHD.o blocks/resource/iMUS.o blocks/resource/LECF.o blocks/resource/LFLF.o blocks/resource/LOFF.o blocks/resource/LSCR.o blocks/resource/MAP.o blocks/resource/OBCD.o blocks/resource/OBIM.o blocks/resource/OBNA.o blocks/resource/OFFS.o blocks/resource/PALS.o blocks/resource/RGBS.o blocks/resource/RMHD.o blocks/resource/RMSC.o blocks/resource/ROOM.o blocks/resource/SCAL.o blocks/resource/SCRP.o blocks/resource/SMAP.o blocks/resource/SOUN.o blocks/resource/VERB.o blocks/resource/VOC.o blocks/resource/WRAP.o blocks/resource/WRAP2.o blocks/resource/WRAP3.o blocks/resource/WRAP4.o blocks/resource/WRAP5.o blocks/resource/ZPLN.o blocks/resource/ZSTR.o
BLOCKS_OBJ_FILES = $(INDEX_OBJ_FILES) $(RESOURCE_OBJ_FILES)
TYPES_OBJ_FILES = types/Costume.o types/Game.o types/Image.o types/Map.o types/Object.o types/Palette.o types/Room.o types/Script.o types/Sound.o
UTIL_OBJ_FILES = util/BMPFile.o util/IO.o util/Log.o util/XMLFile.o
OBJ_FILES = main.o Assembler.o $(BLOCKS_OBJ_FILES) $(UTIL_OBJ_FILES) $(TYPES_OBJ_FILES)

CPP_FLAGS = -g -I. `xml2-config --cflags`
LD_FLAGS = `xml2-config --libs`

all: assembler

assembler : $(OBJ_FILES)
	g++ -o assembler $(LD_FLAGS) $(OBJ_FILES)

main.o : main.cpp
	g++ -o main.o $(CPP_FLAGS) -c main.cpp

Assembler.o : Assembler.cpp
	g++ -o Assembler.o $(CPP_FLAGS) -c Assembler.cpp

blocks/index/AARY.o : blocks/index/AARY.cpp
	g++ -o blocks/index/AARY.o $(CPP_FLAGS) -c blocks/index/AARY.cpp

blocks/index/DCHR.o : blocks/index/DCHR.cpp
	g++ -o blocks/index/DCHR.o $(CPP_FLAGS) -c blocks/index/DCHR.cpp

blocks/index/DCOS.o : blocks/index/DCOS.cpp
	g++ -o blocks/index/DCOS.o $(CPP_FLAGS) -c blocks/index/DCOS.cpp

blocks/index/DOBJ.o : blocks/index/DOBJ.cpp
	g++ -o blocks/index/DOBJ.o $(CPP_FLAGS) -c blocks/index/DOBJ.cpp

blocks/index/DROO.o : blocks/index/DROO.cpp
	g++ -o blocks/index/DROO.o $(CPP_FLAGS) -c blocks/index/DROO.cpp

blocks/index/DRSC.o : blocks/index/DRSC.cpp
	g++ -o blocks/index/DRSC.o $(CPP_FLAGS) -c blocks/index/DRSC.cpp

blocks/index/DSCR.o : blocks/index/DSCR.cpp
	g++ -o blocks/index/DSCR.o $(CPP_FLAGS) -c blocks/index/DSCR.cpp

blocks/index/DSOU.o : blocks/index/DSOU.cpp
	g++ -o blocks/index/DSOU.o $(CPP_FLAGS) -c blocks/index/DSOU.cpp

blocks/index/MAXS.o : blocks/index/MAXS.cpp
	g++ -o blocks/index/MAXS.o $(CPP_FLAGS) -c blocks/index/MAXS.cpp

blocks/index/RNAM.o : blocks/index/RNAM.cpp
	g++ -o blocks/index/RNAM.o $(CPP_FLAGS) -c blocks/index/RNAM.cpp

blocks/resource/AKCD.o : blocks/resource/AKCD.cpp
	g++ -o blocks/resource/AKCD.o $(CPP_FLAGS) -c blocks/resource/AKCD.cpp

blocks/resource/AKCH.o : blocks/resource/AKCH.cpp
	g++ -o blocks/resource/AKCH.o $(CPP_FLAGS) -c blocks/resource/AKCH.cpp

blocks/resource/AKCI.o : blocks/resource/AKCI.cpp
	g++ -o blocks/resource/AKCI.o $(CPP_FLAGS) -c blocks/resource/AKCI.cpp

blocks/resource/AKHD.o : blocks/resource/AKHD.cpp
	g++ -o blocks/resource/AKHD.o $(CPP_FLAGS) -c blocks/resource/AKHD.cpp

blocks/resource/AKOF.o : blocks/resource/AKOF.cpp
	g++ -o blocks/resource/AKOF.o $(CPP_FLAGS) -c blocks/resource/AKOF.cpp

blocks/resource/AKOS.o : blocks/resource/AKOS.cpp
	g++ -o blocks/resource/AKOS.o $(CPP_FLAGS) -c blocks/resource/AKOS.cpp

blocks/resource/AKPL.o : blocks/resource/AKPL.cpp
	g++ -o blocks/resource/AKPL.o $(CPP_FLAGS) -c blocks/resource/AKPL.cpp

blocks/resource/AKSQ.o : blocks/resource/AKSQ.cpp
	g++ -o blocks/resource/AKSQ.o $(CPP_FLAGS) -c blocks/resource/AKSQ.cpp

blocks/resource/APAL.o : blocks/resource/APAL.cpp
	g++ -o blocks/resource/APAL.o $(CPP_FLAGS) -c blocks/resource/APAL.cpp

blocks/resource/BOMP.o : blocks/resource/BOMP.cpp
	g++ -o blocks/resource/BOMP.o $(CPP_FLAGS) -c blocks/resource/BOMP.cpp

blocks/resource/BOXD.o : blocks/resource/BOXD.cpp
	g++ -o blocks/resource/BOXD.o $(CPP_FLAGS) -c blocks/resource/BOXD.cpp

blocks/resource/BOXM.o : blocks/resource/BOXM.cpp
	g++ -o blocks/resource/BOXM.o $(CPP_FLAGS) -c blocks/resource/BOXM.cpp

blocks/resource/BSTR.o : blocks/resource/BSTR.cpp
	g++ -o blocks/resource/BSTR.o $(CPP_FLAGS) -c blocks/resource/BSTR.cpp

blocks/resource/CDHD.o : blocks/resource/CDHD.cpp
	g++ -o blocks/resource/CDHD.o $(CPP_FLAGS) -c blocks/resource/CDHD.cpp

blocks/resource/CYCL.o : blocks/resource/CYCL.cpp
	g++ -o blocks/resource/CYCL.o $(CPP_FLAGS) -c blocks/resource/CYCL.cpp

blocks/resource/ENCD.o : blocks/resource/ENCD.cpp
	g++ -o blocks/resource/ENCD.o $(CPP_FLAGS) -c blocks/resource/ENCD.cpp

blocks/resource/EXCD.o : blocks/resource/EXCD.cpp
	g++ -o blocks/resource/EXCD.o $(CPP_FLAGS) -c blocks/resource/EXCD.cpp

blocks/resource/FRMT.o : blocks/resource/FRMT.cpp
	g++ -o blocks/resource/FRMT.o $(CPP_FLAGS) -c blocks/resource/FRMT.cpp

blocks/resource/IMAG.o : blocks/resource/IMAG.cpp
	g++ -o blocks/resource/IMAG.o $(CPP_FLAGS) -c blocks/resource/IMAG.cpp

blocks/resource/IMHD.o : blocks/resource/IMHD.cpp
	g++ -o blocks/resource/IMHD.o $(CPP_FLAGS) -c blocks/resource/IMHD.cpp

blocks/resource/iMUS.o : blocks/resource/iMUS.cpp
	g++ -o blocks/resource/iMUS.o $(CPP_FLAGS) -c blocks/resource/iMUS.cpp

blocks/resource/LECF.o : blocks/resource/LECF.cpp
	g++ -o blocks/resource/LECF.o $(CPP_FLAGS) -c blocks/resource/LECF.cpp

blocks/resource/LFLF.o : blocks/resource/LFLF.cpp
	g++ -o blocks/resource/LFLF.o $(CPP_FLAGS) -c blocks/resource/LFLF.cpp

blocks/resource/LOFF.o : blocks/resource/LOFF.cpp
	g++ -o blocks/resource/LOFF.o $(CPP_FLAGS) -c blocks/resource/LOFF.cpp

blocks/resource/LSCR.o : blocks/resource/LSCR.cpp
	g++ -o blocks/resource/LSCR.o $(CPP_FLAGS) -c blocks/resource/LSCR.cpp

blocks/resource/MAP.o : blocks/resource/MAP.cpp
	g++ -o blocks/resource/MAP.o $(CPP_FLAGS) -c blocks/resource/MAP.cpp

blocks/resource/OBCD.o : blocks/resource/OBCD.cpp
	g++ -o blocks/resource/OBCD.o $(CPP_FLAGS) -c blocks/resource/OBCD.cpp

blocks/resource/OBIM.o : blocks/resource/OBIM.cpp
	g++ -o blocks/resource/OBIM.o $(CPP_FLAGS) -c blocks/resource/OBIM.cpp

blocks/resource/OBNA.o : blocks/resource/OBNA.cpp
	g++ -o blocks/resource/OBNA.o $(CPP_FLAGS) -c blocks/resource/OBNA.cpp

blocks/resource/OFFS.o : blocks/resource/OFFS.cpp
	g++ -o blocks/resource/OFFS.o $(CPP_FLAGS) -c blocks/resource/OFFS.cpp

blocks/resource/PALS.o : blocks/resource/PALS.cpp
	g++ -o blocks/resource/PALS.o $(CPP_FLAGS) -c blocks/resource/PALS.cpp

blocks/resource/RGBS.o : blocks/resource/RGBS.cpp
	g++ -o blocks/resource/RGBS.o $(CPP_FLAGS) -c blocks/resource/RGBS.cpp

blocks/resource/RMHD.o : blocks/resource/RMHD.cpp
	g++ -o blocks/resource/RMHD.o $(CPP_FLAGS) -c blocks/resource/RMHD.cpp

blocks/resource/RMSC.o : blocks/resource/RMSC.cpp
	g++ -o blocks/resource/RMSC.o $(CPP_FLAGS) -c blocks/resource/RMSC.cpp

blocks/resource/ROOM.o : blocks/resource/ROOM.cpp
	g++ -o blocks/resource/ROOM.o $(CPP_FLAGS) -c blocks/resource/ROOM.cpp

blocks/resource/SCAL.o : blocks/resource/SCAL.cpp
	g++ -o blocks/resource/SCAL.o $(CPP_FLAGS) -c blocks/resource/SCAL.cpp

blocks/resource/SCRP.o : blocks/resource/SCRP.cpp
	g++ -o blocks/resource/SCRP.o $(CPP_FLAGS) -c blocks/resource/SCRP.cpp

blocks/resource/SMAP.o : blocks/resource/SMAP.cpp
	g++ -o blocks/resource/SMAP.o $(CPP_FLAGS) -c blocks/resource/SMAP.cpp

blocks/resource/SOUN.o : blocks/resource/SOUN.cpp
	g++ -o blocks/resource/SOUN.o $(CPP_FLAGS) -c blocks/resource/SOUN.cpp

blocks/resource/VERB.o : blocks/resource/VERB.cpp
	g++ -o blocks/resource/VERB.o $(CPP_FLAGS) -c blocks/resource/VERB.cpp

blocks/resource/VOC.o : blocks/resource/VOC.cpp
	g++ -o blocks/resource/VOC.o $(CPP_FLAGS) -c blocks/resource/VOC.cpp

blocks/resource/WRAP.o : blocks/resource/WRAP.cpp
	g++ -o blocks/resource/WRAP.o $(CPP_FLAGS) -c blocks/resource/WRAP.cpp

blocks/resource/WRAP2.o : blocks/resource/WRAP2.cpp
	g++ -o blocks/resource/WRAP2.o $(CPP_FLAGS) -c blocks/resource/WRAP2.cpp

blocks/resource/WRAP3.o : blocks/resource/WRAP3.cpp
	g++ -o blocks/resource/WRAP3.o $(CPP_FLAGS) -c blocks/resource/WRAP3.cpp

blocks/resource/WRAP4.o : blocks/resource/WRAP4.cpp
	g++ -o blocks/resource/WRAP4.o $(CPP_FLAGS) -c blocks/resource/WRAP4.cpp

blocks/resource/WRAP5.o : blocks/resource/WRAP5.cpp
	g++ -o blocks/resource/WRAP5.o $(CPP_FLAGS) -c blocks/resource/WRAP5.cpp

blocks/resource/ZPLN.o : blocks/resource/ZPLN.cpp
	g++ -o blocks/resource/ZPLN.o $(CPP_FLAGS) -c blocks/resource/ZPLN.cpp

blocks/resource/ZSTR.o : blocks/resource/ZSTR.cpp
	g++ -o blocks/resource/ZSTR.o $(CPP_FLAGS) -c blocks/resource/ZSTR.cpp

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

types/Script.o : types/Script.cpp
	g++ -o types/Script.o $(CPP_FLAGS) -c types/Script.cpp

types/Sound.o : types/Sound.cpp
	g++ -o types/Sound.o $(CPP_FLAGS) -c types/Sound.cpp

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

