SUBDIRS = blocks \
          grammar \
          types \
          util

bin_PROGRAMS = scummgen
scummgen_SOURCES = main.cpp \
                   ScummGEN.cpp ScummGEN.hpp
scummgen_LDADD = blocks/libblocks.la types/libtypes.la util/libutil.la grammar/libgrammar.la @XML_LIBS@
