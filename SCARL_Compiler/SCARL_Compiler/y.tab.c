#ifndef lint
static char yysccsid[] = "@(#)yaccpar	1.9 (Berkeley) 02/21/93";
#endif
#define YYBYACC 1
#define YYMAJOR 1
#define YYMINOR 9
#define yyclearin (yychar=(-1))
#define yyerrok (yyerrflag=0)
#define YYRECOVERING (yyerrflag!=0)
#define YYPREFIX "yy"
#line 3 "scarl_tokens.y"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "scarlast.h"
#include "visitors.h"

int yylex(void);
void yyerror(char *);

int yydebug = 1;

/*for counting line numbers. Lines are incremented in scarl.l*/
extern unsigned lineNumber;
/*handled in scarl.l. for hinting at where error occured*/
extern char *lastTokenText;

/*for performing actions on the code file*/
/*for the compiling unit, this is intermediatary code*/
extern FILE *codeFile;

/*for building the tree that will be used for generating the code later on*/
extern struct ast_node *syntax_tree;

/*the stack to be used when creating nonterminal sub-ASTs*/
extern struct ast_node_stack *node_stack;
extern struct ast_node_stack *ident_stack;

/*the symbol table for tracking program constructs. type checking. This is the parent*/
/*symbol table - the global symbol table*/
extern struct scarl_symbol_table *symbol_table;

extern struct scarl_symbol_table *current_symbol_table;

#line 48 "y.tab.c"
#define IDENTIFIER 257
#define PLUS 258
#define MINUS 259
#define STAR 260
#define SLASH 261
#define BANG 262
#define BOOL 263
#define INT 264
#define CHAR 265
#define POINTER 266
#define VOID 267
#define LPAREN 268
#define RPAREN 269
#define GTR 270
#define LESS 271
#define GTR_EQ 272
#define LESS_EQ 273
#define DBL_EQ 274
#define EQ 275
#define NOT_EQ 276
#define OR 277
#define AND 278
#define COMMA 279
#define SEMICOLON 280
#define IF 281
#define ELSE 282
#define WHILE 283
#define LBRACE 284
#define RBRACE 285
#define DECIMAL 286
#define OCTAL 287
#define HEX 288
#define BINARY 289
#define LIGHT_ACTUATOR 290
#define SERVO_ACTUATOR 291
#define SOUND_SENSOR 292
#define LIGHT_SENSOR 293
#define DISTANCE_SENSOR 294
#define TEMPERATURE_SENSOR 295
#define TRUE 296
#define FALSE 297
#define YYERRCODE 256
short yylhs[] = {                                        -1,
    0,    1,    1,    2,    2,    2,    6,    7,    7,    8,
    8,    8,    8,    8,    8,    3,   14,    4,    5,    9,
   18,   10,   11,   11,   12,   17,   17,   17,   19,   19,
   19,   16,   20,   20,   21,   21,   22,   22,   22,   23,
   23,   23,   23,   23,   24,   24,   25,   25,   25,   26,
   26,   26,   27,   27,   27,   28,   28,   28,   28,   29,
   29,   29,   29,   30,   30,   15,   15,   15,   15,   15,
   13,   13,   13,   13,   13,   13,
};
short yylen[] = {                                         2,
    1,    1,    2,    1,    1,    1,    3,    1,    2,    1,
    1,    1,    1,    1,    1,    3,    2,    4,    5,    4,
    4,    2,    5,    7,    5,    0,    1,    3,    0,    1,
    3,    1,    1,    3,    1,    3,    1,    3,    3,    1,
    3,    3,    3,    3,    1,    2,    1,    3,    3,    1,
    3,    3,    1,    2,    3,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,
};
short yydefred[] = {                                      0,
   66,   67,   68,   69,   70,   71,   72,   73,   74,   75,
   76,    0,    1,    0,    4,    5,    6,    0,    0,    0,
    3,    0,    0,    0,   17,   16,    0,    0,    0,    0,
    0,    0,   60,   61,   62,   63,   64,   65,    0,   59,
    0,    0,    0,    0,   40,    0,    0,   50,   53,   57,
   58,    0,    0,    0,   54,    0,    0,   18,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
   28,    0,   19,    0,    0,   55,    0,    0,    0,    0,
   41,   42,   43,   44,    0,    0,   51,   52,    0,    0,
    0,   10,   11,    0,    0,   12,   13,   14,   15,    0,
    0,    0,   21,    0,    0,    0,    7,    9,   22,   31,
    0,    0,    0,   20,    0,    0,    0,   25,    0,   24,
};
short yydgoto[] = {                                      12,
   13,   14,   15,   16,   17,   93,   94,   95,   96,   97,
   98,   99,   18,   19,   20,   74,   28,   40,   75,   41,
   42,   43,   44,   45,   46,   47,   48,   49,   50,   51,
};
short yysindex[] = {                                   -207,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0, -207,    0,    0,    0, -247, -227, -240,
    0, -255, -160, -254,    0,    0, -251, -238, -228, -250,
 -250, -250,    0,    0,    0,    0,    0,    0, -231,    0,
 -205, -204, -221, -132,    0, -196, -216,    0,    0,    0,
    0, -160, -193, -254,    0, -196, -243,    0, -254, -254,
 -254, -254, -254, -254, -254, -254, -250, -250, -250, -250,
    0, -165,    0, -185, -161,    0, -204, -221, -132, -132,
    0,    0,    0,    0, -216, -216,    0,    0, -214, -155,
 -154,    0,    0, -170, -165,    0,    0,    0,    0, -158,
 -138, -254,    0, -254, -254, -254,    0,    0,    0,    0,
 -122, -104,  -88,    0, -193, -193,  -98,    0, -193,    0,
};
short yyrindex[] = {                                      0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,  185,    0,    0,    0,    0,    0,    0,
    0,    0,  -83,    0,    0,    0,  -82,    0, -149,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
 -256, -120, -258,  -43,    0,  -67, -126,    0,    0,    0,
    0,  -83,    0,  -81,    0,  -55,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,  -74,    0,    0,  -97, -143,  -31,  -19,
    0,    0,    0,    0, -103,  -80,    0,    0,    0,    0,
    0,    0,    0,    0,  -84,    0,    0,    0,    0,    0,
    0,  -81,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0, -188,    0,    0,    0,
};
short yygindex[] = {                                      0,
  194,    0,    0,  -68,    0,  -51,  125,    0,    0,    0,
    0,    0,    0,  -22,    0,  -24,  175,  -66,  126,    0,
  170,  172,    5,   98,   39,   22,  -18,    0,    0,    0,
};
#define YYTABLESIZE 261
short yytable[] = {                                      39,
   27,   73,   29,   92,   30,  101,   29,   31,   30,   22,
   35,   55,   32,   32,   67,   68,   25,   32,   35,   35,
   35,   35,   32,   32,   26,   76,   92,   52,  101,   27,
   53,   33,   34,   35,   36,   33,   34,   35,   36,   54,
   23,   37,   38,   69,   70,   37,   38,   24,   58,  100,
   87,   88,   61,   54,   62,    1,    2,    3,    4,    5,
  104,   67,   68,  117,  118,   79,   80,  120,   23,   56,
   57,   59,  100,   60,   23,   23,   23,   23,   23,  111,
  112,  113,    6,    7,    8,    9,   10,   11,   85,   86,
   72,   89,   23,  102,   23,   23,   23,    1,    2,    3,
    4,    5,    1,    2,    3,    4,    5,  103,   56,   56,
   56,   56,  105,  106,  107,   90,   24,   91,   72,   56,
   56,   56,   56,   56,   56,   36,   56,   56,   56,   56,
   56,   47,   47,   36,   36,   36,   36,   63,   64,   65,
   66,  109,   47,   47,   47,   47,   47,   47,   33,   47,
   47,   47,   47,   47,   48,   48,   33,  114,   33,   33,
   81,   82,   83,   84,  115,   48,   48,   48,   48,   48,
   48,   34,   48,   48,   48,   48,   48,   49,   49,   34,
  116,   34,   34,  119,    2,   26,   27,   29,   49,   49,
   49,   49,   49,   49,   30,   49,   49,   49,   49,   49,
    8,   45,   45,   45,   45,   45,   45,   21,   45,   45,
   45,   45,   45,   46,   46,   46,   46,   46,   46,  108,
   46,   46,   46,   46,   46,   37,   71,  110,   77,    0,
   37,   78,   37,   37,   37,   37,   37,   38,    0,    0,
    0,    0,   38,    0,   38,   38,   38,   38,   38,   39,
    0,    0,    0,    0,   39,    0,   39,   39,   39,   39,
   39,
};
short yycheck[] = {                                      24,
   23,   53,  257,   72,  259,   72,  257,  262,  259,  257,
  269,   30,  269,  268,  258,  259,  257,  268,  277,  278,
  279,  280,  279,  280,  280,  269,   95,  279,   95,   52,
  269,  286,  287,  288,  289,  286,  287,  288,  289,  268,
  268,  296,  297,  260,  261,  296,  297,  275,  280,   72,
   69,   70,  274,  268,  276,  263,  264,  265,  266,  267,
  275,  258,  259,  115,  116,   61,   62,  119,  257,   31,
   32,  277,   95,  278,  263,  264,  265,  266,  267,  104,
  105,  106,  290,  291,  292,  293,  294,  295,   67,   68,
  284,  257,  281,  279,  283,  284,  285,  263,  264,  265,
  266,  267,  263,  264,  265,  266,  267,  269,  258,  259,
  260,  261,  268,  268,  285,  281,  275,  283,  284,  269,
  270,  271,  272,  273,  274,  269,  276,  277,  278,  279,
  280,  258,  259,  277,  278,  279,  280,  270,  271,  272,
  273,  280,  269,  270,  271,  272,  273,  274,  269,  276,
  277,  278,  279,  280,  258,  259,  277,  280,  279,  280,
   63,   64,   65,   66,  269,  269,  270,  271,  272,  273,
  274,  269,  276,  277,  278,  279,  280,  258,  259,  277,
  269,  279,  280,  282,    0,  269,  269,  269,  269,  270,
  271,  272,  273,  274,  269,  276,  277,  278,  279,  280,
  285,  269,  270,  271,  272,  273,  274,   14,  276,  277,
  278,  279,  280,  269,  270,  271,  272,  273,  274,   95,
  276,  277,  278,  279,  280,  269,   52,  102,   59,   -1,
  274,   60,  276,  277,  278,  279,  280,  269,   -1,   -1,
   -1,   -1,  274,   -1,  276,  277,  278,  279,  280,  269,
   -1,   -1,   -1,   -1,  274,   -1,  276,  277,  278,  279,
  280,
};
#define YYFINAL 12
#ifndef YYDEBUG
#define YYDEBUG 0
#endif
#define YYMAXTOKEN 297
#if YYDEBUG
char *yyname[] = {
"end-of-file",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"IDENTIFIER","PLUS","MINUS",
"STAR","SLASH","BANG","BOOL","INT","CHAR","POINTER","VOID","LPAREN","RPAREN",
"GTR","LESS","GTR_EQ","LESS_EQ","DBL_EQ","EQ","NOT_EQ","OR","AND","COMMA",
"SEMICOLON","IF","ELSE","WHILE","LBRACE","RBRACE","DECIMAL","OCTAL","HEX",
"BINARY","LIGHT_ACTUATOR","SERVO_ACTUATOR","SOUND_SENSOR","LIGHT_SENSOR",
"DISTANCE_SENSOR","TEMPERATURE_SENSOR","TRUE","FALSE",
};
char *yyrule[] = {
"$accept : program",
"program : statement_list",
"statement_list : statement",
"statement_list : statement statement_list",
"statement : device_declarator_statement",
"statement : primitive_definition_statement",
"statement : function_definition_statement",
"block_statement : LBRACE statement_list_block_level RBRACE",
"statement_list_block_level : statement_block_level",
"statement_list_block_level : statement_block_level statement_list_block_level",
"statement_block_level : primitive_definition_statement",
"statement_block_level : block_statement",
"statement_block_level : variable_set_statement",
"statement_block_level : function_invocation_statement",
"statement_block_level : if_block_statement",
"statement_block_level : while_block_statement",
"device_declarator_statement : device_type IDENTIFIER SEMICOLON",
"primitive_declarator : primitive_type IDENTIFIER",
"primitive_definition_statement : primitive_declarator EQ expression SEMICOLON",
"function_definition_statement : primitive_declarator LPAREN formal_parameter_list RPAREN block_statement",
"variable_set_statement : IDENTIFIER EQ expression SEMICOLON",
"function_invocation : IDENTIFIER LPAREN parameter_list RPAREN",
"function_invocation_statement : function_invocation SEMICOLON",
"if_block_statement : IF LPAREN expression RPAREN block_statement",
"if_block_statement : IF LPAREN expression RPAREN block_statement ELSE block_statement",
"while_block_statement : WHILE LPAREN expression RPAREN block_statement",
"formal_parameter_list :",
"formal_parameter_list : primitive_declarator",
"formal_parameter_list : primitive_declarator COMMA formal_parameter_list",
"parameter_list :",
"parameter_list : expression",
"parameter_list : expression COMMA parameter_list",
"expression : logical_expression",
"logical_expression : logical_and_expression",
"logical_expression : logical_expression OR logical_and_expression",
"logical_and_expression : equality_expression",
"logical_and_expression : logical_and_expression AND equality_expression",
"equality_expression : relational_expression",
"equality_expression : equality_expression DBL_EQ relational_expression",
"equality_expression : equality_expression NOT_EQ relational_expression",
"relational_expression : bool_expression",
"relational_expression : relational_expression GTR bool_expression",
"relational_expression : relational_expression LESS bool_expression",
"relational_expression : relational_expression GTR_EQ bool_expression",
"relational_expression : relational_expression LESS_EQ bool_expression",
"bool_expression : arithmetic_expression",
"bool_expression : BANG arithmetic_expression",
"arithmetic_expression : arithmetic_factor",
"arithmetic_expression : arithmetic_expression PLUS arithmetic_factor",
"arithmetic_expression : arithmetic_expression MINUS arithmetic_factor",
"arithmetic_factor : arithmetic_unary",
"arithmetic_factor : arithmetic_factor STAR arithmetic_unary",
"arithmetic_factor : arithmetic_factor SLASH arithmetic_unary",
"arithmetic_unary : unit",
"arithmetic_unary : MINUS arithmetic_unary",
"arithmetic_unary : LPAREN arithmetic_expression RPAREN",
"unit : IDENTIFIER",
"unit : integer_value",
"unit : bool_value",
"unit : function_invocation",
"integer_value : DECIMAL",
"integer_value : OCTAL",
"integer_value : HEX",
"integer_value : BINARY",
"bool_value : TRUE",
"bool_value : FALSE",
"primitive_type : BOOL",
"primitive_type : INT",
"primitive_type : CHAR",
"primitive_type : POINTER",
"primitive_type : VOID",
"device_type : LIGHT_ACTUATOR",
"device_type : SERVO_ACTUATOR",
"device_type : SOUND_SENSOR",
"device_type : LIGHT_SENSOR",
"device_type : DISTANCE_SENSOR",
"device_type : TEMPERATURE_SENSOR",
};
#endif
#ifndef YYSTYPE
typedef int YYSTYPE;
#endif
#ifdef YYSTACKSIZE
#undef YYMAXDEPTH
#define YYMAXDEPTH YYSTACKSIZE
#else
#ifdef YYMAXDEPTH
#define YYSTACKSIZE YYMAXDEPTH
#else
#define YYSTACKSIZE 500
#define YYMAXDEPTH 500
#endif
#endif
int yydebug;
int yynerrs;
int yyerrflag;
int yychar;
short *yyssp;
YYSTYPE *yyvsp;
YYSTYPE yyval;
YYSTYPE yylval;
short yyss[YYSTACKSIZE];
YYSTYPE yyvs[YYSTACKSIZE];
#define yystacksize YYSTACKSIZE
#line 532 "scarl_tokens.y"

void yyerror(char *s) {
	fprintf(stderr, "%s at line %i near \'%s\'\n", s, lineNumber, lastTokenText);
}
#line 352 "y.tab.c"
#define YYABORT goto yyabort
#define YYREJECT goto yyabort
#define YYACCEPT goto yyaccept
#define YYERROR goto yyerrlab
int
yyparse()
{
    register int yym, yyn, yystate;
#if YYDEBUG
    register char *yys;
    extern char *getenv();

    if (yys = getenv("YYDEBUG"))
    {
        yyn = *yys;
        if (yyn >= '0' && yyn <= '9')
            yydebug = yyn - '0';
    }
#endif

    yynerrs = 0;
    yyerrflag = 0;
    yychar = (-1);

    yyssp = yyss;
    yyvsp = yyvs;
    *yyssp = yystate = 0;

yyloop:
    if (yyn = yydefred[yystate]) goto yyreduce;
    if (yychar < 0)
    {
        if ((yychar = yylex()) < 0) yychar = 0;
#if YYDEBUG
        if (yydebug)
        {
            yys = 0;
            if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
            if (!yys) yys = "illegal-symbol";
            printf("%sdebug: state %d, reading %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
    }
    if ((yyn = yysindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: state %d, shifting to state %d\n",
                    YYPREFIX, yystate, yytable[yyn]);
#endif
        if (yyssp >= yyss + yystacksize - 1)
        {
            goto yyoverflow;
        }
        *++yyssp = yystate = yytable[yyn];
        *++yyvsp = yylval;
        yychar = (-1);
        if (yyerrflag > 0)  --yyerrflag;
        goto yyloop;
    }
    if ((yyn = yyrindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
        yyn = yytable[yyn];
        goto yyreduce;
    }
    if (yyerrflag) goto yyinrecovery;
#ifdef lint
    goto yynewerror;
#endif
yynewerror:
    yyerror("syntax error");
#ifdef lint
    goto yyerrlab;
#endif
yyerrlab:
    ++yynerrs;
yyinrecovery:
    if (yyerrflag < 3)
    {
        yyerrflag = 3;
        for (;;)
        {
            if ((yyn = yysindex[*yyssp]) && (yyn += YYERRCODE) >= 0 &&
                    yyn <= YYTABLESIZE && yycheck[yyn] == YYERRCODE)
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: state %d, error recovery shifting\
 to state %d\n", YYPREFIX, *yyssp, yytable[yyn]);
#endif
                if (yyssp >= yyss + yystacksize - 1)
                {
                    goto yyoverflow;
                }
                *++yyssp = yystate = yytable[yyn];
                *++yyvsp = yylval;
                goto yyloop;
            }
            else
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: error recovery discarding state %d\n",
                            YYPREFIX, *yyssp);
#endif
                if (yyssp <= yyss) goto yyabort;
                --yyssp;
                --yyvsp;
            }
        }
    }
    else
    {
        if (yychar == 0) goto yyabort;
#if YYDEBUG
        if (yydebug)
        {
            yys = 0;
            if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
            if (!yys) yys = "illegal-symbol";
            printf("%sdebug: state %d, error recovery discards token %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
        yychar = (-1);
        goto yyloop;
    }
yyreduce:
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: state %d, reducing by rule %d (%s)\n",
                YYPREFIX, yystate, yyn, yyrule[yyn]);
#endif
    yym = yylen[yyn];
    yyval = yyvsp[1-yym];
    switch (yyn)
    {
case 1:
#line 51 "scarl_tokens.y"
{ 
	NON_TERMINAL_PROGRAM_func(1, yyvsp[0]); /*this pushes the program onto the node stack*/
}
break;
case 2:
#line 55 "scarl_tokens.y"
{
	yyval = NON_TERMINAL_STATEMENT_LIST_func(1, yyvsp[0]);
}
break;
case 3:
#line 59 "scarl_tokens.y"
{
	/*add the statement to the existing statement list*/
	yyval = NON_TERMINAL_STATEMENT_LIST_func(2, yyvsp[0], yyvsp[-1]);
}
break;
case 4:
#line 64 "scarl_tokens.y"
{
	yyval = yyvsp[0]; /*pass through*/
}
break;
case 5:
#line 68 "scarl_tokens.y"
{
	yyval = yyvsp[0]; /*pass through*/
}
break;
case 6:
#line 72 "scarl_tokens.y"
{
	yyval = yyvsp[0]; /*pass through*/
}
break;
case 7:
#line 76 "scarl_tokens.y"
{
	struct ast_node *block_statement_node = NON_TERMINAL_BLOCK_STATEMENT_func(1, yyvsp[-1]); /*converts the type to a block statement*/
	/*closing out this scope*/
	block_statement_node->symbol_table_value = current_symbol_table;
	current_symbol_table = current_symbol_table->parentTable; /*bring it back up a level*/

	yyval = block_statement_node;
}
break;
case 8:
#line 85 "scarl_tokens.y"
{
	/*create the statement list node and add the statement to it*/
	yyval = NON_TERMINAL_STATEMENT_LIST_BLOCK_LEVEL_func(1, yyvsp[0]);
}
break;
case 9:
#line 90 "scarl_tokens.y"
{
	/*add the statement to the existing statement list*/
	yyval = NON_TERMINAL_STATEMENT_LIST_BLOCK_LEVEL_func(2, yyvsp[0], yyvsp[-1]);
}
break;
case 10:
#line 95 "scarl_tokens.y"
{ 
	yyval = yyvsp[0]; /*pass through*/
}
break;
case 11:
#line 99 "scarl_tokens.y"
{
	yyval = yyvsp[0]; /*pass through*/
}
break;
case 12:
#line 103 "scarl_tokens.y"
{
	yyval = yyvsp[0]; /*pass through*/
}
break;
case 13:
#line 107 "scarl_tokens.y"
{
	yyval = yyvsp[0]; /*pass through*/
}
break;
case 14:
#line 111 "scarl_tokens.y"
{
	yyval = yyvsp[0]; /*pass through*/
}
break;
case 15:
#line 115 "scarl_tokens.y"
{
	yyval = yyvsp[0]; /*pass through*/
}
break;
case 16:
#line 119 "scarl_tokens.y"
{
	struct ast_node *device_declarator_node = NON_TERMINAL_DEVICE_DECLARATOR_STATEMENT_func(2, yyvsp[-2], TERMINAL_IDENTIFIER_func(0));
	int device_type = 0;
	char *ident = NULL;
	struct ast_node *cur_node = device_declarator_node->leftmostChild;
	device_type = cur_node->int_value;
	cur_node = cur_node->nextSibling;
	ident = _strdup(cur_node->str_value);
	
	if (lookup_in_scope(current_symbol_table, ident, NULL, 0) == NULL) {
		declare_symbol_table_entry(
				current_symbol_table, 
				create_symbol_table_entry(
					ident,
					device_type,
					NULL,
					0,
					NULL
				));
	} else {
		fprintf(stderr, "Duplicate identifiers \'%s\' (near line %i)\n", ident, lineNumber);
		exit(0);
	}

	yyval = device_declarator_node;
}
break;
case 17:
#line 146 "scarl_tokens.y"
{
	yyval = NON_TERMINAL_PRIMITIVE_DECLARATOR_func(2, yyvsp[-1], TERMINAL_IDENTIFIER_func(0));
}
break;
case 18:
#line 150 "scarl_tokens.y"
{
	struct ast_node *prim_def_node = NON_TERMINAL_PRIMITIVE_DEFINITION_STATEMENT_func(2, yyvsp[-3], yyvsp[-1]);
		
	struct ast_node *prim_decl_node = prim_def_node->leftmostChild;
	struct ast_node *prim_info_node = prim_decl_node->leftmostChild;
	int ident_type = prim_info_node->int_value;
	char *ident = _strdup(prim_info_node->nextSibling->str_value);
	
	/*add this identifier to the symbol table*/

	if (lookup_in_scope(current_symbol_table, ident, NULL, 0) == NULL) {
		declare_symbol_table_entry(
				current_symbol_table, 
				create_symbol_table_entry(
					ident,
					ident_type,
					NULL,
					0,
					NULL
				));
	} else {
		fprintf(stderr, "Duplicate identifiers \'%s\' (near line %i)\n", ident, lineNumber);
		exit(0);
	}

	prim_info_node = prim_decl_node->nextSibling;
	/*now the prim_info_node is pointing to the expression that*/
	/*this declarator is initially set to*/

	/*TO DO: expression assignment to definition code*/
	

	yyval = prim_def_node;
}
break;
case 19:
#line 185 "scarl_tokens.y"
{
	struct ast_node *function_def_node = NON_TERMINAL_FUNCTION_DEFINITION_STATEMENT_func(3, yyvsp[-4], yyvsp[-2], yyvsp[0]);

	struct ast_node *prim_decl_node = function_def_node->leftmostChild;
	struct ast_node *info_node = prim_decl_node->leftmostChild;
	int return_type = info_node->int_value;
	char *ident = _strdup(info_node->nextSibling->str_value);
	info_node = prim_decl_node->nextSibling; /*now we are pointing to the formal parameter list*/
	
	int parameterCounter = 0;
	int *paramListConstruct = NULL;
	/*counting parameters*/
	if (info_node->leftmostChild != NULL) {
		/*counting the number of formal parameters*/
		struct ast_node *formal_param_node = info_node->leftmostChild;
		while(formal_param_node != NULL) {
			formal_param_node = formal_param_node->nextSibling;
			parameterCounter++;
		}


		/*now allocate space and fill it up with the list of types*/
		/*printf("Allocting %i bytes\n", (sizeof(int) * parameterCounter));*/

		paramListConstruct = (int*)malloc(sizeof(int) * parameterCounter);
		formal_param_node = info_node->leftmostChild;
		for (int i = 0; i < parameterCounter; i++) {
			paramListConstruct[i] = formal_param_node->leftmostChild->int_value;
			formal_param_node = formal_param_node->nextSibling;
		}
		/*complete list created*/

	} 

	/*add this identifier to the symbol table*/

	if (lookup_in_scope(current_symbol_table, ident, paramListConstruct, parameterCounter) == NULL) {
		declare_symbol_table_entry(
				current_symbol_table, 
				create_symbol_table_entry(
					ident,
					return_type,
					paramListConstruct,
					parameterCounter,
					NULL
				));
	} else {
		fprintf(stderr, "Duplicate function definition \'%s\' (near line %i)\n", ident, lineNumber);
		exit(0);
	}

	yyval = function_def_node;
}
break;
case 20:
#line 239 "scarl_tokens.y"
{
	yyval = NON_TERMINAL_VARIABLE_SET_STATEMENT_func(2, TERMINAL_IDENTIFIER_func(0), yyvsp[-1]);
}
break;
case 21:
#line 243 "scarl_tokens.y"
{
	yyval = NON_TERMINAL_FUNCTION_INVOCATION_func(2, TERMINAL_IDENTIFIER_func(0), yyvsp[-1]);
}
break;
case 22:
#line 247 "scarl_tokens.y"
{
	yyval = NON_TERMINAL_FUNCTION_INVOCATION_STATEMENT_func(1, yyvsp[-1]);
}
break;
case 23:
#line 251 "scarl_tokens.y"
{
	yyval = NON_TERMINAL_IF_BLOCK_STATEMENT_func(2, yyvsp[-2], yyvsp[0]);
}
break;
case 24:
#line 255 "scarl_tokens.y"
{ 
	yyval = NON_TERMINAL_IF_BLOCK_STATEMENT_func(3, yyvsp[-4], yyvsp[-2], yyvsp[0]);
}
break;
case 25:
#line 259 "scarl_tokens.y"
{ 
	/*expression and block statement*/
	yyval = NON_TERMINAL_WHILE_BLOCK_STATEMENT_func(2, yyvsp[-2], yyvsp[0]);
}
break;
case 26:
#line 264 "scarl_tokens.y"
{
	/*empty formal parameter list*/
	yyval = NON_TERMINAL_FORMAL_PARAMETER_LIST_func(0);
}
break;
case 27:
#line 269 "scarl_tokens.y"
{ 
	yyval = NON_TERMINAL_FORMAL_PARAMETER_LIST_func(1, yyvsp[0]);
}
break;
case 28:
#line 273 "scarl_tokens.y"
{ 
	yyval = NON_TERMINAL_FORMAL_PARAMETER_LIST_func(2, yyvsp[0], yyvsp[-2]);
}
break;
case 29:
#line 277 "scarl_tokens.y"
{ 
	/*empty parameter list*/
	yyval = NON_TERMINAL_PARAMETER_LIST_func(0);
}
break;
case 30:
#line 282 "scarl_tokens.y"
{ 
	yyval = NON_TERMINAL_PARAMETER_LIST_func(1, yyvsp[0]);
}
break;
case 31:
#line 286 "scarl_tokens.y"
{ 
	yyval = NON_TERMINAL_PARAMETER_LIST_func(2, yyvsp[0], yyvsp[-2]); /*add to existing parameter list*/
}
break;
case 32:
#line 290 "scarl_tokens.y"
{ 
	yyval = yyvsp[0];
}
break;
case 33:
#line 294 "scarl_tokens.y"
{ 
	yyval = yyvsp[0];
}
break;
case 34:
#line 298 "scarl_tokens.y"
{
	/*     logical_expression && logical_and_expression*/
	/*     logical_expression should be on the LEFT*/
	/*     logical_and_expression should be on the RIGHT*/
	/*     OR should be the parent node*/
	yyval = NON_TERMINAL_LOGICAL_EXPRESSION_func(3, yyvsp[-2], TERMINAL_OR_func(0), yyvsp[0]);
}
break;
case 35:
#line 306 "scarl_tokens.y"
{ 
	yyval = yyvsp[0]; /*pass through*/
}
break;
case 36:
#line 310 "scarl_tokens.y"
{ 
	/*     logical_and_expression && equality_expression*/
	/*     logical_and_expression should be on the LEFT*/
	/*     equality_expression should be on the RIGHT*/
	/*     AND should be the parent node*/
	yyval = NON_TERMINAL_LOGICAL_AND_EXPRESSION_func(3, yyvsp[-2], TERMINAL_AND_func(0), yyvsp[0]);

}
break;
case 37:
#line 319 "scarl_tokens.y"
{ 
	yyval = yyvsp[0]; /*pass through*/
}
break;
case 38:
#line 323 "scarl_tokens.y"
{ 
	/*     equality_expression == relational_expression*/
	/*     equality_expression should be on the LEFT*/
	/*     relational_expression should be on the RIGHT*/
	/*     NOT_EQ should be the parent node*/
	yyval = NON_TERMINAL_EQUALITY_EXPRESSION_func(3, yyvsp[-2], TERMINAL_DBL_EQ_func(0), yyvsp[0]);
}
break;
case 39:
#line 331 "scarl_tokens.y"
{ 
	/*     equality_expression != relational_expression*/
	/*     equality_expression should be on the LEFT*/
	/*     relational_expression should be on the RIGHT*/
	/*     NOT_EQ should be the parent node*/
	yyval = NON_TERMINAL_EQUALITY_EXPRESSION_func(3, yyvsp[-2], TERMINAL_NOT_EQ_func(0), yyvsp[0]);
}
break;
case 40:
#line 339 "scarl_tokens.y"
{ 
	yyval = yyvsp[0]; /*pass through*/
}
break;
case 41:
#line 343 "scarl_tokens.y"
{ 
	/*     relational_expression > bool_expression*/
	/*     relational_expression should be on the LEFT*/
	/*     bool_expression should be on the RIGHT*/
	/*     GTR should be the parent node*/
	yyval = NON_TERMINAL_RELATIONAL_EXPRESSION_func(3, yyvsp[-2], TERMINAL_GTR_func(0), yyvsp[0]);
}
break;
case 42:
#line 351 "scarl_tokens.y"
{ 
	/*     relational_expression < bool_expression*/
	/*     relational_expression should be on the LEFT*/
	/*     bool_expression should be on the RIGHT*/
	/*     LESS should be the parent node*/
	yyval = NON_TERMINAL_RELATIONAL_EXPRESSION_func(3, yyvsp[-2], TERMINAL_LESS_func(0), yyvsp[0]);
}
break;
case 43:
#line 359 "scarl_tokens.y"
{ 
	/*     relational_expression >= bool_expression*/
	/*     relational_expression should be on the LEFT*/
	/*     bool_expression should be on the RIGHT*/
	/*     GTR_EQ should be the parent node*/
	yyval = NON_TERMINAL_RELATIONAL_EXPRESSION_func(3, yyvsp[-2], TERMINAL_GTR_EQ_func(0), yyvsp[0]);
}
break;
case 44:
#line 367 "scarl_tokens.y"
{ 
	/*     relational_expression <= bool_expression*/
	/*     relational_expression should be on the LEFT*/
	/*     bool_expression should be on the RIGHT*/
	/*     LESS_EQ should be the parent node*/
	yyval = NON_TERMINAL_RELATIONAL_EXPRESSION_func(3, yyvsp[-2], TERMINAL_LESS_EQ_func(0), yyvsp[0]);
}
break;
case 45:
#line 375 "scarl_tokens.y"
{ 
	yyval = yyvsp[0]; /*pass through*/
}
break;
case 46:
#line 379 "scarl_tokens.y"
{ 
	yyval = NON_TERMINAL_BOOL_EXPRESSION_func(2, TERMINAL_BANG_func(0), yyvsp[0]);
}
break;
case 47:
#line 383 "scarl_tokens.y"
{ 
	yyval = yyvsp[0]; /*pass through*/
}
break;
case 48:
#line 387 "scarl_tokens.y"
{ 
	/*     arithmetic_expression - arithmetic_factor*/
	/*     arithmetic_expression should be on the LEFT*/
	/*     arithmetic_factor should be on the RIGHT*/
	/*     MINUS should be the parent node*/
	yyval = NON_TERMINAL_ARITHMETIC_EXPRESSION_func(3, yyvsp[-2], TERMINAL_PLUS_func(0), yyvsp[0]);
}
break;
case 49:
#line 395 "scarl_tokens.y"
{ 
	/*     arithmetic_expression - arithmetic_factor*/
	/*     arithmetic_expression should be on the LEFT*/
	/*     arithmetic_factor should be on the RIGHT*/
	/*     MINUS should be the parent node*/
	yyval = NON_TERMINAL_ARITHMETIC_EXPRESSION_func(3, yyvsp[-2], TERMINAL_MINUS_func(0), yyvsp[0]);
}
break;
case 50:
#line 403 "scarl_tokens.y"
{ 
	yyval = yyvsp[0]; /*pass through*/
}
break;
case 51:
#line 407 "scarl_tokens.y"
{ 
	/*     arithmetic_factor * arithmetic_unary*/
	/*     arithmetic_factor should be on the LEFT*/
	/*     arithmetic_unary should be on the RIGHT*/
	/*     STAR should be the parent node*/
	yyval = NON_TERMINAL_ARITHMETIC_FACTOR_func(3, yyvsp[-2], TERMINAL_STAR_func(0), yyvsp[0]);
}
break;
case 52:
#line 415 "scarl_tokens.y"
{ 
	/*     arithmetic_factor / arithmetic_unary*/
	/*     arithmetic_factor should be on the LEFT*/
	/*     arithmetic_unary should be on the RIGHT*/
	/*     SLASH should be the parent node*/
	yyval = NON_TERMINAL_ARITHMETIC_FACTOR_func(3, yyvsp[-2], TERMINAL_SLASH_func(0), yyvsp[0]);
}
break;
case 53:
#line 423 "scarl_tokens.y"
{ 
	yyval = yyvsp[0]; /*straight pass*/
}
break;
case 54:
#line 427 "scarl_tokens.y"
{ 
	yyval = NON_TERMINAL_ARITHMETIC_UNARY_func(2, TERMINAL_MINUS_func(0), yyvsp[0]);
}
break;
case 55:
#line 431 "scarl_tokens.y"
{ 
	yyval = yyvsp[-1]; /*pass the arithmetic expression as an arithmetic unary*/
}
break;
case 56:
#line 435 "scarl_tokens.y"
{ 
	yyval = TERMINAL_IDENTIFIER_func(0); /*receives identifier from ident_stack*/
}
break;
case 57:
#line 439 "scarl_tokens.y"
{ 
	yyval = yyvsp[0]; /*straight pass*/
}
break;
case 58:
#line 443 "scarl_tokens.y"
{ 
	yyval = yyvsp[0]; /*straight pass*/
}
break;
case 59:
#line 447 "scarl_tokens.y"
{ 
	yyval = yyvsp[0]; /*straight pass*/
}
break;
case 60:
#line 451 "scarl_tokens.y"
{ 
	NON_TERMINAL_INTEGER_VALUE_func(0); /*for debug printing*/

	char *str = lastTokenText;
	yyval = TERMINAL_DECIMAL_func(1, str);
}
break;
case 61:
#line 458 "scarl_tokens.y"
{ 
	NON_TERMINAL_INTEGER_VALUE_func(0); /*for debug printing*/

	char *str = lastTokenText;
	yyval = TERMINAL_OCTAL_func(1, str);
}
break;
case 62:
#line 465 "scarl_tokens.y"
{ 
	NON_TERMINAL_INTEGER_VALUE_func(0); /*for debug printing*/

	char *str = lastTokenText;
	yyval = TERMINAL_HEX_func(1, str);
}
break;
case 63:
#line 472 "scarl_tokens.y"
{ 
	NON_TERMINAL_INTEGER_VALUE_func(0); /*for debug printing*/

	char *str = lastTokenText;
	yyval = TERMINAL_BINARY_func(1, str);
}
break;
case 64:
#line 479 "scarl_tokens.y"
{ 
	yyval = NON_TERMINAL_BOOL_VALUE_func(1, 1); /* 1 being true*/
}
break;
case 65:
#line 483 "scarl_tokens.y"
{ 
	yyval = NON_TERMINAL_BOOL_VALUE_func(1, 0); /* 0 being false*/
}
break;
case 66:
#line 487 "scarl_tokens.y"
{
	yyval = NON_TERMINAL_PRIMITIVE_TYPE_func(1, BOOL);
}
break;
case 67:
#line 491 "scarl_tokens.y"
{ 
	yyval = NON_TERMINAL_PRIMITIVE_TYPE_func(1, INT);
}
break;
case 68:
#line 495 "scarl_tokens.y"
{ 
	yyval = NON_TERMINAL_PRIMITIVE_TYPE_func(1, CHAR);
}
break;
case 69:
#line 499 "scarl_tokens.y"
{ 
	yyval = NON_TERMINAL_PRIMITIVE_TYPE_func(1, POINTER);
}
break;
case 70:
#line 503 "scarl_tokens.y"
{ 
	yyval = NON_TERMINAL_PRIMITIVE_TYPE_func(1, VOID);
}
break;
case 71:
#line 507 "scarl_tokens.y"
{ 
	yyval = NON_TERMINAL_DEVICE_TYPE_func(1, LIGHT_ACTUATOR);
}
break;
case 72:
#line 511 "scarl_tokens.y"
{ 
	yyval = NON_TERMINAL_DEVICE_TYPE_func(1, SERVO_ACTUATOR);
}
break;
case 73:
#line 515 "scarl_tokens.y"
{ 
	yyval = NON_TERMINAL_DEVICE_TYPE_func(1, SOUND_SENSOR);
}
break;
case 74:
#line 519 "scarl_tokens.y"
{ 
	yyval = NON_TERMINAL_DEVICE_TYPE_func(1, LIGHT_SENSOR);
}
break;
case 75:
#line 523 "scarl_tokens.y"
{
	yyval = NON_TERMINAL_DEVICE_TYPE_func(1, DISTANCE_SENSOR);
}
break;
case 76:
#line 527 "scarl_tokens.y"
{ 
	yyval = NON_TERMINAL_DEVICE_TYPE_func(1, TEMPERATURE_SENSOR);
}
break;
#line 1125 "y.tab.c"
    }
    yyssp -= yym;
    yystate = *yyssp;
    yyvsp -= yym;
    yym = yylhs[yyn];
    if (yystate == 0 && yym == 0)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: after reduction, shifting from state 0 to\
 state %d\n", YYPREFIX, YYFINAL);
#endif
        yystate = YYFINAL;
        *++yyssp = YYFINAL;
        *++yyvsp = yyval;
        if (yychar < 0)
        {
            if ((yychar = yylex()) < 0) yychar = 0;
#if YYDEBUG
            if (yydebug)
            {
                yys = 0;
                if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
                if (!yys) yys = "illegal-symbol";
                printf("%sdebug: state %d, reading %d (%s)\n",
                        YYPREFIX, YYFINAL, yychar, yys);
            }
#endif
        }
        if (yychar == 0) goto yyaccept;
        goto yyloop;
    }
    if ((yyn = yygindex[yym]) && (yyn += yystate) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yystate)
        yystate = yytable[yyn];
    else
        yystate = yydgoto[yym];
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: after reduction, shifting from state %d \
to state %d\n", YYPREFIX, *yyssp, yystate);
#endif
    if (yyssp >= yyss + yystacksize - 1)
    {
        goto yyoverflow;
    }
    *++yyssp = yystate;
    *++yyvsp = yyval;
    goto yyloop;
yyoverflow:
    yyerror("yacc stack overflow");
yyabort:
    return (1);
yyaccept:
    return (0);
}
