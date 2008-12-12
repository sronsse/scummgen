%{
#include "util/Log.hpp"
#include "Declaration.hpp"
#include "Expression.hpp"
#include "Function.hpp"
#include "Statement.hpp"
#include "parser.h"
%}

%option yylineno
%option nounput
%option noyywrap

%x SINGLE_LINE_COMMENT
%x MULTIPLE_LINES_COMMENT

%%

 /* Comments */
"//"							BEGIN SINGLE_LINE_COMMENT;
<SINGLE_LINE_COMMENT>\n			BEGIN INITIAL;
<SINGLE_LINE_COMMENT>.			;

"/*"							BEGIN MULTIPLE_LINES_COMMENT;
<MULTIPLE_LINES_COMMENT>"*/"	BEGIN INITIAL;
<MULTIPLE_LINES_COMMENT>.|\n	;

 /* Strings */
\"	{
		int lineNumber = yylineno;
		uint16_t i = 0;
		char c;
		char previous = 0;
		while ((i < STRING_LENGTH) && (c = yyinput()))
		{
			if (c == '"' && previous != '\\')
			{
				yylval.string[i] = 0;
				return T_STRING;
			}

			// Add character to the resulting string
			yylval.string[i++] = c;
			previous = c;
		}
		if (c != '\"')
			Log::getInstance().write(LOG_INFO, "Line %u: string length too long !\n", lineNumber);

		yylval.string[STRING_LENGTH - 1] = 0;
		return T_STRING;
	}

 /* Other tokens */
"const"							return T_CONST;
"var"							return T_VAR;
"function"         				return T_FUNCTION;
"thread"         				return T_THREAD;
"if"            				return T_IF;
"else"          				return T_ELSE;
"switch"						return T_SWITCH;
"case"							return T_CASE;
"default"						return T_DEFAULT;
"for"	         				return T_FOR;
"while"         				return T_WHILE;
"continue"						return T_CONTINUE;
"break"							return T_BREAK;
"return"          				return T_RETURN;
"asm"							return T_ASSEMBLY;
">="            				return T_GE;
"<="            				return T_LE;
"=="            				return T_EQ;
"!="            				return T_NE;
"&&"							return T_LAND;
"||"							return T_LOR;
"++"							return T_INC;
"--"							return T_DEC;
[-()<>=+*/;{},!&|@:]			return *yytext;
[0-9]+							{ yylval.number = atoi(yytext); return T_NUMBER; }
"0x"[a-fA-F0-9]+				{ yylval.number = strtol(yytext, NULL, 16); return T_NUMBER; }
\'.\'							{ yylval.number = (int)yytext[1]; return T_NUMBER; }
\.*[a-zA-Z_]+[a-zA-Z0-9_]*		{ strncpy(yylval.string, yytext, STRING_LENGTH); yylval.string[STRING_LENGTH - 1] = 0; return T_IDENTIFIER; }
[ \n\t]+						;
.								;

