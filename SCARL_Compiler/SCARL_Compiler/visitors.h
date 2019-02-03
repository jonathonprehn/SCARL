/*
 *  This file is part of the SCARL toolkit.
 *  
 *  SCARL is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *  
 *  SCARL is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *  
 *  You should have received a copy of the GNU General Public License
 *  along with SCARL.  If not, see <https://www.gnu.org/licenses/>.
 */
 
 
 #ifndef __SCARL_AST_VISITOR_FUNCTIONS_H__
#define __SCARL_AST_VISITOR_FUNCTIONS_H__

#include "scarlast.h"

struct ast_node * NON_TERMINAL_PROGRAM_func(int argc, ...);
struct ast_node * NON_TERMINAL_STATEMENT_LIST_func(int argc, ...);
struct ast_node * NON_TERMINAL_STATEMENT_func(int argc, ...);
struct ast_node * NON_TERMINAL_BLOCK_STATEMENT_func(int argc, ...);
struct ast_node * NON_TERMINAL_STATEMENT_LIST_BLOCK_LEVEL_func(int argc, ...);
struct ast_node * NON_TERMINAL_STATEMENT_BLOCK_LEVEL_func(int argc, ...);
struct ast_node * NON_TERMINAL_DEVICE_DECLARATOR_STATEMENT_func(int argc, ...);
struct ast_node * NON_TERMINAL_PRIMITIVE_DECLARATOR_func(int argc, ...);
struct ast_node * NON_TERMINAL_PRIMITIVE_DEFINITION_STATEMENT_func(int argc, ...);
struct ast_node * NON_TERMINAL_FUNCTION_DEFINITION_STATEMENT_func(int argc, ...);
struct ast_node * NON_TERMINAL_VARIABLE_SET_STATEMENT_func(int argc, ...);
struct ast_node * NON_TERMINAL_RETURN_STATEMENT_func(int argc, ...);
struct ast_node * NON_TERMINAL_FUNCTION_INVOCATION_func(int argc, ...);
struct ast_node * NON_TERMINAL_FUNCTION_INVOCATION_STATEMENT_func(int argc, ...);
struct ast_node * NON_TERMINAL_IF_BLOCK_STATEMENT_func(int argc, ...);
struct ast_node * NON_TERMINAL_WHILE_BLOCK_STATEMENT_func(int argc, ...);
struct ast_node * NON_TERMINAL_FORMAL_PARAMETER_LIST_func(int argc, ...);
struct ast_node * NON_TERMINAL_PARAMETER_LIST_func(int argc, ...);
struct ast_node * NON_TERMINAL_EXPRESSION_func(int argc, ...);
struct ast_node * NON_TERMINAL_LOGICAL_EXPRESSION_func(int argc, ...);
struct ast_node * NON_TERMINAL_LOGICAL_AND_EXPRESSION_func(int argc, ...);
struct ast_node * NON_TERMINAL_EQUALITY_EXPRESSION_func(int argc, ...);
struct ast_node * NON_TERMINAL_RELATIONAL_EXPRESSION_func(int argc, ...);
struct ast_node * NON_TERMINAL_BOOL_EXPRESSION_func(int argc, ...);
struct ast_node * NON_TERMINAL_ARITHMETIC_EXPRESSION_func(int argc, ...);
struct ast_node * NON_TERMINAL_ARITHMETIC_FACTOR_func(int argc, ...);
struct ast_node * NON_TERMINAL_ARITHMETIC_UNARY_func(int argc, ...);
struct ast_node * NON_TERMINAL_UNIT_func(int argc, ...);
struct ast_node * NON_TERMINAL_INTEGER_VALUE_func(int argc, ...);
struct ast_node * NON_TERMINAL_BOOL_VALUE_func(int argc, ...);
struct ast_node * NON_TERMINAL_PRIMITIVE_TYPE_func(int argc, ...);
struct ast_node * NON_TERMINAL_DEVICE_TYPE_func(int argc, ...);
struct ast_node * TERMINAL_IDENTIFIER_func(int argc, ...);
struct ast_node * TERMINAL_PLUS_func(int argc, ...);
struct ast_node * TERMINAL_MINUS_func(int argc, ...);
struct ast_node * TERMINAL_STAR_func(int argc, ...);
struct ast_node * TERMINAL_SLASH_func(int argc, ...);
struct ast_node * TERMINAL_BANG_func(int argc, ...);
struct ast_node * TERMINAL_BOOL_func(int argc, ...);
struct ast_node * TERMINAL_INT_func(int argc, ...);
struct ast_node * TERMINAL_CHAR_func(int argc, ...);
struct ast_node * TERMINAL_POINTER_func(int argc, ...);
struct ast_node * TERMINAL_VOID_func(int argc, ...);
struct ast_node * TERMINAL_LPAREN_func(int argc, ...);
struct ast_node * TERMINAL_RPAREN_func(int argc, ...);
struct ast_node * TERMINAL_GTR_func(int argc, ...);
struct ast_node * TERMINAL_LESS_func(int argc, ...);
struct ast_node * TERMINAL_GTR_EQ_func(int argc, ...);
struct ast_node * TERMINAL_LESS_EQ_func(int argc, ...);
struct ast_node * TERMINAL_DBL_EQ_func(int argc, ...);
struct ast_node * TERMINAL_EQ_func(int argc, ...);
struct ast_node * TERMINAL_NOT_EQ_func(int argc, ...);
struct ast_node * TERMINAL_OR_func(int argc, ...);
struct ast_node * TERMINAL_AND_func(int argc, ...);
struct ast_node * TERMINAL_COMMA_func(int argc, ...);
struct ast_node * TERMINAL_SEMICOLON_func(int argc, ...);
struct ast_node * TERMINAL_IF_func(int argc, ...);
struct ast_node * TERMINAL_ELSE_func(int argc, ...);
struct ast_node * TERMINAL_WHILE_func(int argc, ...);
struct ast_node * TERMINAL_LBRACE_func(int argc, ...);
struct ast_node * TERMINAL_RBRACE_func(int argc, ...);
struct ast_node * TERMINAL_DECIMAL_func(int argc, ...);
struct ast_node * TERMINAL_OCTAL_func(int argc, ...);
struct ast_node * TERMINAL_HEX_func(int argc, ...);
struct ast_node * TERMINAL_BINARY_func(int argc, ...);
struct ast_node * TERMINAL_LIGHT_ACTUATOR_func(int argc, ...);
struct ast_node * TERMINAL_SERVO_ACTUATOR_func(int argc, ...);
struct ast_node * TERMINAL_SOUND_SENSOR_func(int argc, ...);
struct ast_node * TERMINAL_LIGHT_SENSOR_func(int argc, ...);
struct ast_node * TERMINAL_DISTANCE_SENSOR_func(int argc, ...);
struct ast_node * TERMINAL_TEMPERATURE_SENSOR_func(int argc, ...);
struct ast_node * TERMINAL_TRUE_func(int argc, ...);
struct ast_node * TERMINAL_FALSE_func(int argc, ...);
struct ast_node * TERMINAL_RETURN_func(int argc, ...);

void print_current_state();
void init_visitor_func_parsing_constructs();

#endif