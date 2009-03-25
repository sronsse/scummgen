SUBDIRS = blocks \
          grammar \
          types \
          util

bin_PROGRAMS = scummgen
scummgen_SOURCES = main.cpp
scummgen_LDADD = types/libtypes.la blocks/libblocks.la grammar/libgrammar.la util/libutil.la @XML_LIBS@
