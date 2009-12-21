%{
#include "types/Script.hpp"
#include "util/Log.hpp"
#include "Declaration.hpp"
#include "Expression.hpp"
#include "Function.hpp"
#include "Statement.hpp"
#include "parser.h"

// Local declarations
int commentCaller;
int parseString();
%}

%option yylineno
%option nounput
%option noyywrap

%x SINGLE_LINE_COMMENT
%x MULTIPLE_LINES_COMMENT
%x ASSEMBLY

%%

 /* Common expressions */
"//"							{ commentCaller = INITIAL; BEGIN SINGLE_LINE_COMMENT; }
"/*"							{ commentCaller = INITIAL; BEGIN MULTIPLE_LINES_COMMENT; }
\"								return parseString();
"const"							return T_CONST;
"var"							return T_VAR;
"enum"							return T_ENUM;
"actor"							return T_ACTOR;
"verb"							return T_VERB;
"class"							return T_CLASS;
"function"         				return T_FUNCTION;
"inline"						return T_INLINE;
"thread"         				return T_THREAD;
"if"            				return T_IF;
"else"          				return T_ELSE;
"switch"						return T_SWITCH;
"action"						return T_ACTION;
"case"							return T_CASE;
"default"						return T_DEFAULT;
"for"	         				return T_FOR;
"while"         				return T_WHILE;
"do"         					return T_DO;
"continue"						return T_CONTINUE;
"break"							return T_BREAK;
"return"          				return T_RETURN;
"cutscene"						return T_CUTSCENE;
"try"							return T_TRY;
"catch"							return T_CATCH;
"finally"						return T_FINALLY;
"asm"							{ BEGIN ASSEMBLY; return T_ASSEMBLY; }
">="            				return T_GE;
"<="            				return T_LE;
"=="            				return T_EQ;
"!="            				return T_NE;
"&&"							return T_LAND;
"||"							return T_LOR;
"+="							return T_INC;
"-="							return T_DEC;
"++"							return T_UNI_INC;
"--"							return T_UNI_DEC;
[-+()<>=*/;{},!&|@:\[\]]		return *yytext;
[0-9]+							{ yylval.number = atoi(yytext); return T_NUMBER; }
"0x"[a-fA-F0-9]+				{ yylval.number = strtol(yytext, NULL, 16); return T_NUMBER; }
[a-zA-Z_]+[a-zA-Z0-9_]*			{ strncpy(yylval.string, yytext, STRING_LENGTH); yylval.string[STRING_LENGTH - 1] = 0; return T_IDENTIFIER; }
[ \n\t]|.						;

 /* Assembly expressions */
<ASSEMBLY>"//"				{ commentCaller = ASSEMBLY; BEGIN SINGLE_LINE_COMMENT; }
<ASSEMBLY>"/*"				{ commentCaller = ASSEMBLY; BEGIN MULTIPLE_LINES_COMMENT; }
<ASSEMBLY>"{"				return *yytext;
<ASSEMBLY>"}"				{ BEGIN INITIAL; return *yytext; }
<ASSEMBLY>\"				return parseString();
<ASSEMBLY>[-+]*[0-9]+		{ sprintf(yylval.string, "%d", atoi(yytext)); return T_STRING; }
<ASSEMBLY>"0x"[a-fA-F0-9]+	{ sprintf(yylval.string, "%u", strtol(yytext, NULL, 16)); return T_STRING; }
<ASSEMBLY>\'.\'				{ sprintf(yylval.string, "%u", (int)yytext[1]); return T_STRING; }
<ASSEMBLY>\.*[a-zA-Z0-9_]+	{ strncpy(yylval.string, yytext, STRING_LENGTH); yylval.string[STRING_LENGTH - 1] = 0; return T_STRING; }
<ASSEMBLY>[ \n\t]|.			;

 /* Single line comments */
<SINGLE_LINE_COMMENT>\n			BEGIN commentCaller;
<SINGLE_LINE_COMMENT>.			;

 /* Multiple line comments */
<MULTIPLE_LINES_COMMENT>"*/"	BEGIN commentCaller;
<MULTIPLE_LINES_COMMENT>.|\n	;

%%

int parseString()
{
	int lineNumber = yylineno;
	uint16_t i = 0;
	char c;
	char previous = 0;

	while ((i < STRING_LENGTH - 1) && (c = yyinput()))
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
		Log::write(LOG_INFO, "Line %u: string length too long !\n", lineNumber);

	yylval.string[STRING_LENGTH - 1] = 0;
	return T_STRING;
}
