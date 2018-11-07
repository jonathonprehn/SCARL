#ifndef __SCARL_AST_VISITOR_FUNCTIONS_H__
#define __SCARL_AST_VISITOR_FUNCTIONS_H__

#include "scarlast.h"

void NON_TERMINAL_PROGRAM_func(int argc, ...);
void NON_TERMINAL_STATEMENT_LIST_func(int argc, ...);
void NON_TERMINAL_STATEMENT_func(int argc, ...);
void NON_TERMINAL_BLOCK_STATEMENT_func(int argc, ...);
void NON_TERMINAL_STATEMENT_LIST_BLOCK_LEVEL_func(int argc, ...);
void NON_TERMINAL_STATEMENT_BLOCK_LEVEL_func(int argc, ...);
void NON_TERMINAL_DEVICE_DECLARATOR_STATEMENT_func(int argc, ...);
void NON_TERMINAL_PRIMITIVE_DECLARATOR_func(int argc, ...);
void NON_TERMINAL_PRIMITIVE_DEFINITION_STATEMENT_func(int argc, ...);
void NON_TERMINAL_FUNCTION_DEFINITION_STATEMENT_func(int argc, ...);
void NON_TERMINAL_VARIABLE_SET_STATEMENT_func(int argc, ...);
void NON_TERMINAL_FUNCTION_INVOCATION_func(int argc, ...);
void NON_TERMINAL_FUNCTION_INVOCATION_STATEMENT_func(int argc, ...);
void NON_TERMINAL_IF_BLOCK_STATEMENT_func(int argc, ...);
void NON_TERMINAL_WHILE_BLOCK_STATEMENT_func(int argc, ...);
void NON_TERMINAL_FORMAL_PARAMETER_LIST_func(int argc, ...);
void NON_TERMINAL_PARAMETER_LIST_func(int argc, ...);
void NON_TERMINAL_EXPRESSION_func(int argc, ...);
void NON_TERMINAL_LOGICAL_EXPRESSION_func(int argc, ...);
void NON_TERMINAL_LOGICAL_AND_EXPRESSION_func(int argc, ...);
void NON_TERMINAL_EQUALITY_EXPRESSION_func(int argc, ...);
void NON_TERMINAL_RELATIONAL_EXPRESSION_func(int argc, ...);
void NON_TERMINAL_BOOL_EXPRESSION_func(int argc, ...);
void NON_TERMINAL_ARITHMETIC_EXPRESSION_func(int argc, ...);
void NON_TERMINAL_ARITHMETIC_FACTOR_func(int argc, ...);
void NON_TERMINAL_ARITHMETIC_UNARY_func(int argc, ...);
void NON_TERMINAL_UNIT_func(int argc, ...);
void NON_TERMINAL_INTEGER_VALUE_func(int argc, ...);
void NON_TERMINAL_BOOL_VALUE_func(int argc, ...);
void NON_TERMINAL_PRIMITIVE_TYPE_func(int argc, ...);
void NON_TERMINAL_DEVICE_TYPE_func(int argc, ...);
void TERMINAL_IDENTIFIER_func(int argc, ...);
void TERMINAL_PLUS_func(int argc, ...);
void TERMINAL_MINUS_func(int argc, ...);
void TERMINAL_STAR_func(int argc, ...);
void TERMINAL_SLASH_func(int argc, ...);
void TERMINAL_BANG_func(int argc, ...);
void TERMINAL_BOOL_func(int argc, ...);
void TERMINAL_INT_func(int argc, ...);
void TERMINAL_CHAR_func(int argc, ...);
void TERMINAL_POINTER_func(int argc, ...);
void TERMINAL_VOID_func(int argc, ...);
void TERMINAL_LPAREN_func(int argc, ...);
void TERMINAL_RPAREN_func(int argc, ...);
void TERMINAL_GTR_func(int argc, ...);
void TERMINAL_LESS_func(int argc, ...);
void TERMINAL_GTR_EQ_func(int argc, ...);
void TERMINAL_LESS_EQ_func(int argc, ...);
void TERMINAL_DBL_EQ_func(int argc, ...);
void TERMINAL_EQ_func(int argc, ...);
void TERMINAL_NOT_EQ_func(int argc, ...);
void TERMINAL_OR_func(int argc, ...);
void TERMINAL_AND_func(int argc, ...);
void TERMINAL_COMMA_func(int argc, ...);
void TERMINAL_SEMICOLON_func(int argc, ...);
void TERMINAL_IF_func(int argc, ...);
void TERMINAL_ELSE_func(int argc, ...);
void TERMINAL_WHILE_func(int argc, ...);
void TERMINAL_LBRACE_func(int argc, ...);
void TERMINAL_RBRACE_func(int argc, ...);
void TERMINAL_DECIMAL_func(int argc, ...);
void TERMINAL_OCTAL_func(int argc, ...);
void TERMINAL_HEX_func(int argc, ...);
void TERMINAL_BINARY_func(int argc, ...);
void TERMINAL_LIGHT_ACTUATOR_func(int argc, ...);
void TERMINAL_SERVO_ACTUATOR_func(int argc, ...);
void TERMINAL_SOUND_SENSOR_func(int argc, ...);
void TERMINAL_LIGHT_SENSOR_func(int argc, ...);
void TERMINAL_DISTANCE_SENSOR_func(int argc, ...);
void TERMINAL_TEMPERATURE_SENSOR_func(int argc, ...);
void TERMINAL_TRUE_func(int argc, ...);
void TERMINAL_FALSE_func(int argc, ...);

void print_current_state();
void init_visitor_func_parsing_constructs();

#endif