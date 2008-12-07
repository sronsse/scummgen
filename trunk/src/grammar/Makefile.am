BUILT_SOURCES = parser.h
AM_YFLAGS = -d
AM_LFLAGS = -o$(LEX_OUTPUT_ROOT).c

noinst_LTLIBRARIES = libgrammar.la
libgrammar_la_SOURCES = Context.cpp Context.hpp \
                        Declaration.cpp Declaration.hpp \
                        Expression.cpp Expression.hpp \
                        Function.cpp Function.hpp \
                        Instruction.cpp Instruction.hpp \
                        lexer.ll \
                        parser.yy \
                        Statement.cpp Statement.hpp
libgrammar_la_CPPFLAGS = -I$(top_srcdir)/src @XML_CFLAGS@
