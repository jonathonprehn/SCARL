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
#include "scarl_symboltable.h"
#include "devices_placeholders.h"

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

#line 50 "y.tab.c"
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
#define RETURN 298
#define YYERRCODE 256
short yylhs[] = {                                        -1,
    0,    1,    1,    2,    2,    2,    6,    7,    7,    8,
    8,    8,    8,    8,    8,    8,    3,   15,    4,    5,
    9,   10,   19,   11,   12,   12,   13,   18,   18,   18,
   20,   20,   20,   17,   21,   21,   22,   22,   23,   23,
   23,   24,   24,   24,   24,   24,   25,   25,   26,   26,
   26,   27,   27,   27,   28,   28,   28,   29,   29,   29,
   29,   30,   30,   30,   30,   31,   31,   16,   16,   16,
   16,   16,   14,   14,   14,   14,   14,   14,
};
short yylen[] = {                                         2,
    1,    1,    2,    1,    1,    1,    3,    1,    2,    1,
    1,    1,    1,    1,    1,    1,    3,    2,    4,    5,
    4,    3,    4,    2,    5,    7,    5,    0,    1,    3,
    0,    1,    3,    1,    1,    3,    1,    3,    1,    3,
    3,    1,    3,    3,    3,    3,    1,    2,    1,    3,
    3,    1,    3,    3,    1,    2,    3,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,
};
short yydefred[] = {                                      0,
   68,   69,   70,   71,   72,   73,   74,   75,   76,   77,
   78,    0,    1,    0,    4,    5,    6,    0,    0,    0,
    3,    0,    0,    0,   18,   17,    0,    0,    0,    0,
    0,    0,   62,   63,   64,   65,   66,   67,    0,   61,
    0,    0,    0,    0,   42,    0,    0,   52,   55,   59,
   60,    0,    0,    0,   56,    0,    0,   19,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
   30,    0,   20,    0,    0,   57,    0,    0,    0,    0,
   43,   44,   45,   46,    0,    0,   53,   54,    0,    0,
    0,    0,   10,   11,    0,    0,   12,   13,   14,   15,
   16,    0,    0,    0,   23,    0,    0,    0,    0,    7,
    9,   24,   33,    0,    0,    0,   22,   21,    0,    0,
    0,   27,    0,   26,
};
short yydgoto[] = {                                      12,
   13,   14,   15,   16,   17,   94,   95,   96,   97,   98,
   99,  100,  101,   18,   19,   20,   74,   28,   40,   75,
   41,   42,   43,   44,   45,   46,   47,   48,   49,   50,
   51,
};
short yysindex[] = {                                   -175,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0, -175,    0,    0,    0, -235, -209, -230,
    0, -240, -158, -210,    0,    0, -231, -212, -206, -233,
 -233, -233,    0,    0,    0,    0,    0,    0, -213,    0,
 -202, -193, -251, -264,    0, -220, -217,    0,    0,    0,
    0, -158, -185, -210,    0, -220, -198,    0, -210, -210,
 -210, -210, -210, -210, -210, -210, -233, -233, -233, -233,
    0, -247,    0, -165, -126,    0, -193, -251, -264, -264,
    0,    0,    0,    0, -217, -217,    0,    0, -203,  -86,
  -83, -210,    0,    0,  -99, -247,    0,    0,    0,    0,
    0, -109,  -93, -210,    0, -210, -210, -210,  -92,    0,
    0,    0,    0,  -91,  -73,  -61,    0,    0, -185, -185,
  -66,    0, -185,    0,
};
short yyrindex[] = {                                      0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,  215,    0,    0,    0,    0,    0,    0,
    0,    0,  -49,    0,    0,    0,  -40,    0, -148,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
  -52,  -96, -142,  -55,    0, -176, -125,    0,    0,    0,
    0,  -49,    0,  -39,    0,  -67,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,  -37,    0,    0,  -27, -119,  -43,  -31,
    0,    0,    0,    0, -102,  -79,    0,    0,    0,    0,
    0,    0,    0,    0,    0,  -46,    0,    0,    0,    0,
    0,    0,    0,  -39,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
 -252,    0,    0,    0,
};
short yygindex[] = {                                      0,
  204,    0,    0,  -68,    0,  -50,  144,    0,    0,    0,
    0,    0,    0,    0,  -22,    0,  -24,  189,  -51,  140,
    0,  192,  194,   19,   76,  131,   97,  -28,    0,    0,
    0,
};
#define YYTABLESIZE 254
short yytable[] = {                                      39,
   27,   55,   73,   93,   25,   63,   64,   65,   66,   89,
   25,   25,   25,   25,   25,    1,    2,    3,    4,    5,
  103,   22,   61,   29,   62,   30,   25,   93,   25,   27,
   25,   25,   25,   90,   32,   91,   72,   67,   68,   26,
   87,   88,   69,   70,  103,   25,   29,   52,   30,  102,
   92,   31,   33,   34,   35,   36,   53,   32,   23,   67,
   68,   54,   37,   38,   54,   24,   58,  109,  121,  122,
   76,  106,  124,  102,   59,   33,   34,   35,   36,   79,
   80,  114,  115,  116,   60,   37,   38,    1,    2,    3,
    4,    5,   47,   47,   47,   47,   47,   47,   72,   47,
   47,   47,   47,   47,    1,    2,    3,    4,    5,   58,
   58,   58,   58,  104,    6,    7,    8,    9,   10,   11,
   58,   58,   58,   58,   58,   58,   37,   58,   58,   58,
   58,   58,   49,   49,   37,   37,   37,   37,   81,   82,
   83,   84,  105,   49,   49,   49,   49,   49,   49,   38,
   49,   49,   49,   49,   49,   50,   50,   38,   38,   38,
   38,   56,   57,   85,   86,   24,   50,   50,   50,   50,
   50,   50,   35,   50,   50,   50,   50,   50,   51,   51,
   35,  107,   35,   35,  108,  110,  112,  117,  118,   51,
   51,   51,   51,   51,   51,  119,   51,   51,   51,   51,
   51,   48,   48,   48,   48,   48,   48,  120,   48,   48,
   48,   48,   48,   39,    2,  123,   34,   21,   39,   28,
   39,   39,   39,   39,   39,   40,   34,   34,   29,   31,
   40,   32,   40,   40,   40,   40,   40,   41,    8,  111,
   71,   36,   41,  113,   41,   41,   41,   41,   41,   36,
   77,   36,   36,   78,
};
short yycheck[] = {                                      24,
   23,   30,   53,   72,  257,  270,  271,  272,  273,  257,
  263,  264,  265,  266,  267,  263,  264,  265,  266,  267,
   72,  257,  274,  257,  276,  259,  257,   96,  281,   52,
  283,  284,  285,  281,  268,  283,  284,  258,  259,  280,
   69,   70,  260,  261,   96,  298,  257,  279,  259,   72,
  298,  262,  286,  287,  288,  289,  269,  268,  268,  258,
  259,  268,  296,  297,  268,  275,  280,   92,  119,  120,
  269,  275,  123,   96,  277,  286,  287,  288,  289,   61,
   62,  106,  107,  108,  278,  296,  297,  263,  264,  265,
  266,  267,  269,  270,  271,  272,  273,  274,  284,  276,
  277,  278,  279,  280,  263,  264,  265,  266,  267,  258,
  259,  260,  261,  279,  290,  291,  292,  293,  294,  295,
  269,  270,  271,  272,  273,  274,  269,  276,  277,  278,
  279,  280,  258,  259,  277,  278,  279,  280,   63,   64,
   65,   66,  269,  269,  270,  271,  272,  273,  274,  269,
  276,  277,  278,  279,  280,  258,  259,  277,  278,  279,
  280,   31,   32,   67,   68,  275,  269,  270,  271,  272,
  273,  274,  269,  276,  277,  278,  279,  280,  258,  259,
  277,  268,  279,  280,  268,  285,  280,  280,  280,  269,
  270,  271,  272,  273,  274,  269,  276,  277,  278,  279,
  280,  269,  270,  271,  272,  273,  274,  269,  276,  277,
  278,  279,  280,  269,    0,  282,  269,   14,  274,  269,
  276,  277,  278,  279,  280,  269,  279,  280,  269,  269,
  274,  269,  276,  277,  278,  279,  280,  269,  285,   96,
   52,  269,  274,  104,  276,  277,  278,  279,  280,  277,
   59,  279,  280,   60,
};
#define YYFINAL 12
#ifndef YYDEBUG
#define YYDEBUG 0
#endif
#define YYMAXTOKEN 298
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
"DISTANCE_SENSOR","TEMPERATURE_SENSOR","TRUE","FALSE","RETURN",
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
"statement_block_level : return_statement",
"statement_block_level : function_invocation_statement",
"statement_block_level : if_block_statement",
"statement_block_level : while_block_statement",
"device_declarator_statement : device_type IDENTIFIER SEMICOLON",
"primitive_declarator : primitive_type IDENTIFIER",
"primitive_definition_statement : primitive_declarator EQ expression SEMICOLON",
"function_definition_statement : primitive_declarator LPAREN formal_parameter_list RPAREN block_statement",
"variable_set_statement : IDENTIFIER EQ expression SEMICOLON",
"return_statement : RETURN expression SEMICOLON",
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
#line 565 "scarl_tokens.y"

void yyerror(char *s) {
	fprintf(stderr, "%s at line %i near \'%s\'\n", s, lineNumber, lastTokenText);
}
#line 360 "y.tab.c"
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
#line 54 "scarl_tokens.y"
{ 
	NON_TERMINAL_PROGRAM_func(1, yyvsp[0]); /*this pushes the program onto the node stack*/
}
break;
case 2:
#line 58 "scarl_tokens.y"
{
	yyval = NON_TERMINAL_STATEMENT_LIST_func(1, yyvsp[0]);
}
break;
case 3:
#line 62 "scarl_tokens.y"
{
	/*add the statement to the existing statement list*/
	yyval = NON_TERMINAL_STATEMENT_LIST_func(2, yyvsp[0], yyvsp[-1]);
}
break;
case 4:
#line 67 "scarl_tokens.y"
{
	yyval = yyvsp[0]; /*pass through*/
}
break;
case 5:
#line 71 "scarl_tokens.y"
{
	yyval = yyvsp[0]; /*pass through*/
}
break;
case 6:
#line 75 "scarl_tokens.y"
{
	yyval = yyvsp[0]; /*pass through*/
}
break;
case 7:
#line 79 "scarl_tokens.y"
{
	struct ast_node *block_statement_node = NON_TERMINAL_BLOCK_STATEMENT_func(1, yyvsp[-1]); /*converts the type to a block statement*/
	/*closing out this scope*/
	block_statement_node->symbol_table_value = current_symbol_table;
	
	/*frame size should be correctly calculated for the child symbol table*/
	current_symbol_table->parentTable->frameSize += current_symbol_table->frameSize;

	current_symbol_table = current_symbol_table->parentTable; /*bring it back up a level*/
	yyval = block_statement_node;
}
break;
case 8:
#line 91 "scarl_tokens.y"
{
	/*create the statement list node and add the statement to it*/
	yyval = NON_TERMINAL_STATEMENT_LIST_BLOCK_LEVEL_func(1, yyvsp[0]);
}
break;
case 9:
#line 96 "scarl_tokens.y"
{
	/*add the statement to the existing statement list*/
	yyval = NON_TERMINAL_STATEMENT_LIST_BLOCK_LEVEL_func(2, yyvsp[0], yyvsp[-1]);
}
break;
case 10:
#line 101 "scarl_tokens.y"
{ 
	yyval = yyvsp[0]; /*pass through*/
}
break;
case 11:
#line 105 "scarl_tokens.y"
{
	yyval = yyvsp[0]; /*pass through*/
}
break;
case 12:
#line 109 "scarl_tokens.y"
{
	yyval = yyvsp[0]; /*pass through*/
}
break;
case 13:
#line 113 "scarl_tokens.y"
{
	yyval = yyvsp[0]; /*pass through*/
}
break;
case 14:
#line 117 "scarl_tokens.y"
{
	yyval = yyvsp[0]; /*pass through*/
}
break;
case 15:
#line 121 "scarl_tokens.y"
{
	yyval = yyvsp[0]; /*pass through*/
}
break;
case 16:
#line 125 "scarl_tokens.y"
{
	yyval = yyvsp[0]; /*pass through*/
}
break;
case 17:
#line 129 "scarl_tokens.y"
{
	struct ast_node *device_declarator_node = NON_TERMINAL_DEVICE_DECLARATOR_STATEMENT_func(2, yyvsp[-2], TERMINAL_IDENTIFIER_func(0));
	int device_type = 0;
	char *ident = NULL;
	struct ast_node *cur_node = device_declarator_node->leftmostChild;
	device_type = cur_node->int_value;
	cur_node = cur_node->nextSibling;
	ident = _strdup(cur_node->str_value);
	
	if (lookup(current_symbol_table, ident, NULL, 0) == NULL) {
		declare_symbol_table_entry(
				current_symbol_table, 
				create_symbol_table_entry(
					ident,
					device_type,
					NULL,
					0,
					NULL
				));


		/*we also want to include the functions that*/
		/*will be used for the functionality of this particular device*/
		add_device_functions_to_symbol_table(ident, device_type, current_symbol_table);
		/*how will these functions be implemented??*/
	} else {
		fprintf(stderr, "Duplicate identifiers \'%s\' (near line %i)\n", ident, lineNumber);
		exit(0);
	}

	yyval = device_declarator_node;
}
break;
case 18:
#line 162 "scarl_tokens.y"
{
	yyval = NON_TERMINAL_PRIMITIVE_DECLARATOR_func(2, yyvsp[-1], TERMINAL_IDENTIFIER_func(0));
}
break;
case 19:
#line 166 "scarl_tokens.y"
{
	struct ast_node *prim_def_node = NON_TERMINAL_PRIMITIVE_DEFINITION_STATEMENT_func(2, yyvsp[-3], yyvsp[-1]);
		
	struct ast_node *prim_decl_node = prim_def_node->leftmostChild;
	struct ast_node *prim_info_node = prim_decl_node->leftmostChild;
	int ident_type = prim_info_node->int_value;
	char *ident = _strdup(prim_info_node->nextSibling->str_value);
	
	/*add this identifier to the symbol table*/

	if (lookup(current_symbol_table, ident, NULL, 0) == NULL) {
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

	yyval = prim_def_node;
}
break;
case 20:
#line 198 "scarl_tokens.y"
{
	struct ast_node *function_def_node = NON_TERMINAL_FUNCTION_DEFINITION_STATEMENT_func(3, yyvsp[-4], yyvsp[-2], yyvsp[0]);

	struct ast_node *prim_decl_node = function_def_node->leftmostChild;
	struct ast_node *info_node = prim_decl_node->leftmostChild;
	int return_type = info_node->int_value;
	char *ident = _strdup(info_node->nextSibling->str_value);
	info_node = prim_decl_node->nextSibling; /*now we are pointing to the formal parameter list*/
	
	int parameterCounter = 0;
	int *paramListConstruct = NULL;
	char **paramIdentifiersList = NULL;
	formal_parameter_node_to_parameter_list(info_node, &parameterCounter, &paramListConstruct, &paramIdentifiersList);

	/*add this identifier to the symbol table*/

	if (lookup(current_symbol_table, ident, paramListConstruct, parameterCounter) == NULL) {
		struct scarl_symbol_table *function_symbol_table = info_node->nextSibling->symbol_table_value;
		struct scarl_symbol_table_entry *function_entry_to_declare = create_symbol_table_entry(
					ident,
					return_type,
					paramListConstruct,
					parameterCounter,
					function_symbol_table
				);
		function_entry_to_declare->parameterIdentifiers = paramIdentifiersList;
		/*add in the identifiers too*/


		declare_symbol_table_entry(
				current_symbol_table, 
				function_entry_to_declare
		);

				/*add the formal parameters to the symbol table of this function*/
				/*the frame offsets of these parameters are handled differently*/
				/*than the other local variables*/
				/*this is implicit with the construction of the function (?)*/
				/*this needs testing*/
				struct ast_node *formal_param_list = yyvsp[-2];
				struct ast_node *fp = formal_param_list->leftmostChild;
				while(fp != NULL) {
					char *fp_ident = fp->leftmostChild->nextSibling->str_value;
					if (lookup(function_symbol_table, fp_ident, NULL, 0) == NULL) {
						declare_symbol_table_entry(
						function_symbol_table, 
						create_symbol_table_entry(
							fp_ident,
							fp->leftmostChild->int_value,
							NULL,
							0,
							NULL
						));
					}
					else {
						fprintf(stderr, "Duplicate variable declaration from formal parameters in function %s (parameters %s)\n", ident, fp_ident);
						exit(0);
					}			
					fp = fp->nextSibling;
				}
	} else {
		fprintf(stderr, "Duplicate function definition \'%s\' (near line %i)\n", ident, lineNumber);
		exit(0);
	}

	
	yyval = function_def_node;
}
break;
case 21:
#line 267 "scarl_tokens.y"
{
	yyval = NON_TERMINAL_VARIABLE_SET_STATEMENT_func(2, TERMINAL_IDENTIFIER_func(0), yyvsp[-1]);
}
break;
case 22:
#line 271 "scarl_tokens.y"
{
	yyval = NON_TERMINAL_RETURN_STATEMENT_func(1, yyvsp[-1]);
}
break;
case 23:
#line 275 "scarl_tokens.y"
{
	yyval = NON_TERMINAL_FUNCTION_INVOCATION_func(2, TERMINAL_IDENTIFIER_func(0), yyvsp[-1]);
}
break;
case 24:
#line 279 "scarl_tokens.y"
{
	yyval = NON_TERMINAL_FUNCTION_INVOCATION_STATEMENT_func(1, yyvsp[-1]);
}
break;
case 25:
#line 283 "scarl_tokens.y"
{
	yyval = NON_TERMINAL_IF_BLOCK_STATEMENT_func(2, yyvsp[-2], yyvsp[0]);
}
break;
case 26:
#line 287 "scarl_tokens.y"
{ 
	yyval = NON_TERMINAL_IF_BLOCK_STATEMENT_func(3, yyvsp[-4], yyvsp[-2], yyvsp[0]);
}
break;
case 27:
#line 291 "scarl_tokens.y"
{ 
	/*expression and block statement*/
	yyval = NON_TERMINAL_WHILE_BLOCK_STATEMENT_func(2, yyvsp[-2], yyvsp[0]);
}
break;
case 28:
#line 296 "scarl_tokens.y"
{
	/*empty formal parameter list*/
	yyval = NON_TERMINAL_FORMAL_PARAMETER_LIST_func(0);
}
break;
case 29:
#line 301 "scarl_tokens.y"
{ 
	yyval = NON_TERMINAL_FORMAL_PARAMETER_LIST_func(1, yyvsp[0]);
}
break;
case 30:
#line 305 "scarl_tokens.y"
{ 
	yyval = NON_TERMINAL_FORMAL_PARAMETER_LIST_func(2, yyvsp[0], yyvsp[-2]);

}
break;
case 31:
#line 310 "scarl_tokens.y"
{ 
	/*empty parameter list*/
	yyval = NON_TERMINAL_PARAMETER_LIST_func(0);
}
break;
case 32:
#line 315 "scarl_tokens.y"
{ 
	yyval = NON_TERMINAL_PARAMETER_LIST_func(1, yyvsp[0]);
}
break;
case 33:
#line 319 "scarl_tokens.y"
{ 
	yyval = NON_TERMINAL_PARAMETER_LIST_func(2, yyvsp[0], yyvsp[-2]); /*add to existing parameter list*/
}
break;
case 34:
#line 323 "scarl_tokens.y"
{ 
	yyval = yyvsp[0];
}
break;
case 35:
#line 327 "scarl_tokens.y"
{ 
	yyval = yyvsp[0];
}
break;
case 36:
#line 331 "scarl_tokens.y"
{
	/*     logical_expression && logical_and_expression*/
	/*     logical_expression should be on the LEFT*/
	/*     logical_and_expression should be on the RIGHT*/
	/*     OR should be the parent node*/
	yyval = NON_TERMINAL_LOGICAL_EXPRESSION_func(3, yyvsp[-2], TERMINAL_OR_func(0), yyvsp[0]);
}
break;
case 37:
#line 339 "scarl_tokens.y"
{ 
	yyval = yyvsp[0]; /*pass through*/
}
break;
case 38:
#line 343 "scarl_tokens.y"
{ 
	/*     logical_and_expression && equality_expression*/
	/*     logical_and_expression should be on the LEFT*/
	/*     equality_expression should be on the RIGHT*/
	/*     AND should be the parent node*/
	yyval = NON_TERMINAL_LOGICAL_AND_EXPRESSION_func(3, yyvsp[-2], TERMINAL_AND_func(0), yyvsp[0]);

}
break;
case 39:
#line 352 "scarl_tokens.y"
{ 
	yyval = yyvsp[0]; /*pass through*/
}
break;
case 40:
#line 356 "scarl_tokens.y"
{ 
	/*     equality_expression == relational_expression*/
	/*     equality_expression should be on the LEFT*/
	/*     relational_expression should be on the RIGHT*/
	/*     NOT_EQ should be the parent node*/
	yyval = NON_TERMINAL_EQUALITY_EXPRESSION_func(3, yyvsp[-2], TERMINAL_DBL_EQ_func(0), yyvsp[0]);
}
break;
case 41:
#line 364 "scarl_tokens.y"
{ 
	/*     equality_expression != relational_expression*/
	/*     equality_expression should be on the LEFT*/
	/*     relational_expression should be on the RIGHT*/
	/*     NOT_EQ should be the parent node*/
	yyval = NON_TERMINAL_EQUALITY_EXPRESSION_func(3, yyvsp[-2], TERMINAL_NOT_EQ_func(0), yyvsp[0]);
}
break;
case 42:
#line 372 "scarl_tokens.y"
{ 
	yyval = yyvsp[0]; /*pass through*/
}
break;
case 43:
#line 376 "scarl_tokens.y"
{ 
	/*     relational_expression > bool_expression*/
	/*     relational_expression should be on the LEFT*/
	/*     bool_expression should be on the RIGHT*/
	/*     GTR should be the parent node*/
	yyval = NON_TERMINAL_RELATIONAL_EXPRESSION_func(3, yyvsp[-2], TERMINAL_GTR_func(0), yyvsp[0]);
}
break;
case 44:
#line 384 "scarl_tokens.y"
{ 
	/*     relational_expression < bool_expression*/
	/*     relational_expression should be on the LEFT*/
	/*     bool_expression should be on the RIGHT*/
	/*     LESS should be the parent node*/
	yyval = NON_TERMINAL_RELATIONAL_EXPRESSION_func(3, yyvsp[-2], TERMINAL_LESS_func(0), yyvsp[0]);
}
break;
case 45:
#line 392 "scarl_tokens.y"
{ 
	/*     relational_expression >= bool_expression*/
	/*     relational_expression should be on the LEFT*/
	/*     bool_expression should be on the RIGHT*/
	/*     GTR_EQ should be the parent node*/
	yyval = NON_TERMINAL_RELATIONAL_EXPRESSION_func(3, yyvsp[-2], TERMINAL_GTR_EQ_func(0), yyvsp[0]);
}
break;
case 46:
#line 400 "scarl_tokens.y"
{ 
	/*     relational_expression <= bool_expression*/
	/*     relational_expression should be on the LEFT*/
	/*     bool_expression should be on the RIGHT*/
	/*     LESS_EQ should be the parent node*/
	yyval = NON_TERMINAL_RELATIONAL_EXPRESSION_func(3, yyvsp[-2], TERMINAL_LESS_EQ_func(0), yyvsp[0]);
}
break;
case 47:
#line 408 "scarl_tokens.y"
{ 
	yyval = yyvsp[0]; /*pass through*/
}
break;
case 48:
#line 412 "scarl_tokens.y"
{ 
	yyval = NON_TERMINAL_BOOL_EXPRESSION_func(2, TERMINAL_BANG_func(0), yyvsp[0]);
}
break;
case 49:
#line 416 "scarl_tokens.y"
{ 
	yyval = yyvsp[0]; /*pass through*/
}
break;
case 50:
#line 420 "scarl_tokens.y"
{ 
	/*     arithmetic_expression - arithmetic_factor*/
	/*     arithmetic_expression should be on the LEFT*/
	/*     arithmetic_factor should be on the RIGHT*/
	/*     MINUS should be the parent node*/
	yyval = NON_TERMINAL_ARITHMETIC_EXPRESSION_func(3, yyvsp[-2], TERMINAL_PLUS_func(0), yyvsp[0]);
}
break;
case 51:
#line 428 "scarl_tokens.y"
{ 
	/*     arithmetic_expression - arithmetic_factor*/
	/*     arithmetic_expression should be on the LEFT*/
	/*     arithmetic_factor should be on the RIGHT*/
	/*     MINUS should be the parent node*/
	yyval = NON_TERMINAL_ARITHMETIC_EXPRESSION_func(3, yyvsp[-2], TERMINAL_MINUS_func(0), yyvsp[0]);
}
break;
case 52:
#line 436 "scarl_tokens.y"
{ 
	yyval = yyvsp[0]; /*pass through*/
}
break;
case 53:
#line 440 "scarl_tokens.y"
{ 
	/*     arithmetic_factor * arithmetic_unary*/
	/*     arithmetic_factor should be on the LEFT*/
	/*     arithmetic_unary should be on the RIGHT*/
	/*     STAR should be the parent node*/
	yyval = NON_TERMINAL_ARITHMETIC_FACTOR_func(3, yyvsp[-2], TERMINAL_STAR_func(0), yyvsp[0]);
}
break;
case 54:
#line 448 "scarl_tokens.y"
{ 
	/*     arithmetic_factor / arithmetic_unary*/
	/*     arithmetic_factor should be on the LEFT*/
	/*     arithmetic_unary should be on the RIGHT*/
	/*     SLASH should be the parent node*/
	yyval = NON_TERMINAL_ARITHMETIC_FACTOR_func(3, yyvsp[-2], TERMINAL_SLASH_func(0), yyvsp[0]);
}
break;
case 55:
#line 456 "scarl_tokens.y"
{ 
	yyval = yyvsp[0]; /*straight pass*/
}
break;
case 56:
#line 460 "scarl_tokens.y"
{ 
	yyval = NON_TERMINAL_ARITHMETIC_UNARY_func(2, TERMINAL_MINUS_func(0), yyvsp[0]);
}
break;
case 57:
#line 464 "scarl_tokens.y"
{ 
	yyval = yyvsp[-1]; /*pass the arithmetic expression as an arithmetic unary*/
}
break;
case 58:
#line 468 "scarl_tokens.y"
{ 
	yyval = TERMINAL_IDENTIFIER_func(0); /*receives identifier from ident_stack*/
}
break;
case 59:
#line 472 "scarl_tokens.y"
{ 
	yyval = yyvsp[0]; /*straight pass*/
}
break;
case 60:
#line 476 "scarl_tokens.y"
{ 
	yyval = yyvsp[0]; /*straight pass*/
}
break;
case 61:
#line 480 "scarl_tokens.y"
{ 
	yyval = yyvsp[0]; /*straight pass*/
}
break;
case 62:
#line 484 "scarl_tokens.y"
{ 
	NON_TERMINAL_INTEGER_VALUE_func(0); /*for debug printing*/

	char *str = lastTokenText;
	yyval = TERMINAL_DECIMAL_func(1, str);
}
break;
case 63:
#line 491 "scarl_tokens.y"
{ 
	NON_TERMINAL_INTEGER_VALUE_func(0); /*for debug printing*/

	char *str = lastTokenText;
	yyval = TERMINAL_OCTAL_func(1, str);
}
break;
case 64:
#line 498 "scarl_tokens.y"
{ 
	NON_TERMINAL_INTEGER_VALUE_func(0); /*for debug printing*/

	char *str = lastTokenText;
	yyval = TERMINAL_HEX_func(1, str);
}
break;
case 65:
#line 505 "scarl_tokens.y"
{ 
	NON_TERMINAL_INTEGER_VALUE_func(0); /*for debug printing*/

	char *str = lastTokenText;
	yyval = TERMINAL_BINARY_func(1, str);
}
break;
case 66:
#line 512 "scarl_tokens.y"
{ 
	yyval = NON_TERMINAL_BOOL_VALUE_func(1, 1); /* 1 being true*/
}
break;
case 67:
#line 516 "scarl_tokens.y"
{ 
	yyval = NON_TERMINAL_BOOL_VALUE_func(1, 0); /* 0 being false*/
}
break;
case 68:
#line 520 "scarl_tokens.y"
{
	yyval = NON_TERMINAL_PRIMITIVE_TYPE_func(1, BOOL);
}
break;
case 69:
#line 524 "scarl_tokens.y"
{ 
	yyval = NON_TERMINAL_PRIMITIVE_TYPE_func(1, INT);
}
break;
case 70:
#line 528 "scarl_tokens.y"
{ 
	yyval = NON_TERMINAL_PRIMITIVE_TYPE_func(1, CHAR);
}
break;
case 71:
#line 532 "scarl_tokens.y"
{ 
	yyval = NON_TERMINAL_PRIMITIVE_TYPE_func(1, POINTER);
}
break;
case 72:
#line 536 "scarl_tokens.y"
{ 
	yyval = NON_TERMINAL_PRIMITIVE_TYPE_func(1, VOID);
}
break;
case 73:
#line 540 "scarl_tokens.y"
{ 
	yyval = NON_TERMINAL_DEVICE_TYPE_func(1, LIGHT_ACTUATOR);
}
break;
case 74:
#line 544 "scarl_tokens.y"
{ 
	yyval = NON_TERMINAL_DEVICE_TYPE_func(1, SERVO_ACTUATOR);
}
break;
case 75:
#line 548 "scarl_tokens.y"
{ 
	yyval = NON_TERMINAL_DEVICE_TYPE_func(1, SOUND_SENSOR);
}
break;
case 76:
#line 552 "scarl_tokens.y"
{ 
	yyval = NON_TERMINAL_DEVICE_TYPE_func(1, LIGHT_SENSOR);
}
break;
case 77:
#line 556 "scarl_tokens.y"
{
	yyval = NON_TERMINAL_DEVICE_TYPE_func(1, DISTANCE_SENSOR);
}
break;
case 78:
#line 560 "scarl_tokens.y"
{ 
	yyval = NON_TERMINAL_DEVICE_TYPE_func(1, TEMPERATURE_SENSOR);
}
break;
#line 1167 "y.tab.c"
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
