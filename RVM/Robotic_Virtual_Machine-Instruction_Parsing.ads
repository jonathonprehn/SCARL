
with Robotic_Virtual_Machine; use Robotic_Virtual_Machine;

package Robotic_Virtual_Machine.Instruction_Parsing is

	-- To ensure Operand_Parse_Table is initialized on Elaboration of this package
	pragma Elaborate_Body(Robotic_Virtual_Machine.Instruction_Parsing);

	type ARCL_Instruction_Parsing_Proc is access procedure (Instruction : in out ARCL_Instruction; Operand_String : in String);
	type ARCL_Instruction_Parsing_Table is array (ARCL_Instruction_Code) of ARCL_Instruction_Parsing_Proc;

	Operand_Parse_Table : ARCL_Instruction_Parsing_Table;
	
	procedure Parse_Operands_ARCL_ADD(Instruction : in out ARCL_Instruction; Operand_String : in String);
	procedure Parse_Operands_ARCL_SUB(Instruction : in out ARCL_Instruction; Operand_String : in String);
	procedure Parse_Operands_ARCL_MULT(Instruction : in out ARCL_Instruction; Operand_String : in String);
	procedure Parse_Operands_ARCL_DIV(Instruction : in out ARCL_Instruction; Operand_String : in String);
	procedure Parse_Operands_ARCL_FLIP(Instruction : in out ARCL_Instruction; Operand_String : in String);
	procedure Parse_Operands_ARCL_MOV(Instruction : in out ARCL_Instruction; Operand_String : in String);
	procedure Parse_Operands_ARCL_LOADL(Instruction : in out ARCL_Instruction; Operand_String : in String);
	procedure Parse_Operands_ARCL_LOADF(Instruction : in out ARCL_Instruction; Operand_String : in String);
	procedure Parse_Operands_ARCL_LOADR(Instruction : in out ARCL_Instruction; Operand_String : in String);
	procedure Parse_Operands_ARCL_STORF(Instruction : in out ARCL_Instruction; Operand_String : in String);
	procedure Parse_Operands_ARCL_STORR(Instruction : in out ARCL_Instruction; Operand_String : in String);
	procedure Parse_Operands_ARCL_FRAMEU(Instruction : in out ARCL_Instruction; Operand_String : in String);
	procedure Parse_Operands_ARCL_FRAMEO(Instruction : in out ARCL_Instruction; Operand_String : in String);
	procedure Parse_Operands_ARCL_RSAVE(Instruction : in out ARCL_Instruction; Operand_String : in String);
	procedure Parse_Operands_ARCL_RLOAD(Instruction : in out ARCL_Instruction; Operand_String : in String);
	procedure Parse_Operands_ARCL_LABEL(Instruction : in out ARCL_Instruction; Operand_String : in String);
	procedure Parse_Operands_ARCL_PROC(Instruction : in out ARCL_Instruction; Operand_String : in String);
	procedure Parse_Operands_ARCL_RET(Instruction : in out ARCL_Instruction; Operand_String : in String);
	procedure Parse_Operands_ARCL_CALL(Instruction : in out ARCL_Instruction; Operand_String : in String);
	procedure Parse_Operands_ARCL_JMP(Instruction : in out ARCL_Instruction; Operand_String : in String);
	procedure Parse_Operands_ARCL_CMP(Instruction : in out ARCL_Instruction; Operand_String : in String);
	procedure Parse_Operands_ARCL_JPE(Instruction : in out ARCL_Instruction; Operand_String : in String);
	procedure Parse_Operands_ARCL_JPNE(Instruction : in out ARCL_Instruction; Operand_String : in String);
	procedure Parse_Operands_ARCL_JPGR(Instruction : in out ARCL_Instruction; Operand_String : in String);
	procedure Parse_Operands_ARCL_JPLS(Instruction : in out ARCL_Instruction; Operand_String : in String);
	procedure Parse_Operands_ARCL_JPGE(Instruction : in out ARCL_Instruction; Operand_String : in String);
	procedure Parse_Operands_ARCL_JPLE(Instruction : in out ARCL_Instruction; Operand_String : in String);
	procedure Parse_Operands_ARCL_JAND(Instruction : in out ARCL_Instruction; Operand_String : in String);
	procedure Parse_Operands_ARCL_JOR(Instruction : in out ARCL_Instruction; Operand_String : in String);
	procedure Parse_Operands_ARCL_DELAY(Instruction : in out ARCL_Instruction; Operand_String : in String);
	procedure Parse_Operands_ARCL_OUTPUT(Instruction : in out ARCL_Instruction; Operand_String : in String);
	procedure Parse_Operands_ARCL_INPUT(Instruction : in out ARCL_Instruction; Operand_String : in String);
	procedure Parse_Operands_ARCL_WRITE(Instruction : in out ARCL_Instruction; Operand_String : in String);
	procedure Parse_Operands_ARCL_READ(Instruction : in out ARCL_Instruction; Operand_String : in String);
	
end Robotic_Virtual_Machine.Instruction_Parsing;