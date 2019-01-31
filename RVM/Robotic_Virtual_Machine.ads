
package Robotic_Virtual_Machine is
	
	type ARCL_Instruction_Code is
		(
			ARCL_ADD,
			ARCL_SUB,
			ARCL_MULT,
			ARCL_DIV,
			ARCL_FLIP,
			ARCL_MOV,
			ARCL_LOADL,
			ARCL_LOADF,
			ARCL_LOADR,
			ARCL_STORF,
			ARCL_STORR,
			ARCL_FRAMEU,
			ARCL_FRAMEO,
			ARCL_RSAVE,
			ARCL_RLOAD,
			ARCL_LABEL,
			ARCL_PROC,
			ARCL_RET,
			ARCL_CALL,
			ARCL_JMP,
			ARCL_CMP,
			ARCL_JPE,
			ARCL_JPNE,
			ARCL_JPGR,
			ARCL_JPLS,
			ARCL_JPGE,
			ARCL_JPLE,
			ARCL_JAND,
			ARCL_JOR,
			ARCL_DELAY,
			ARCL_OUTPUT,
			ARCL_INPUT,
			ARCL_WRITE,
			ARCL_READ
		);
	type ARCL_Register is (R0, R1, R2, R3, R4, R5, R6, R7, FRR); -- enumeration
	subtype ARCL_Register_Value is Integer range -65536 .. 65535; -- subtype
	type ARCL_Register_State is array (ARCL_Register) of ARCL_Register_Value;
	type ARCL_Memory_Offset is new Integer;
	type ARCL_Label_Value is access String; -- to an arbitrarily sized string

	RVM_Stack_Space : constant ARCL_Memory_Offset := 256;
	RVM_Heap_Space : constant ARCL_Memory_Offset := 256;
	type RVM_Memory_Stack is private;
	type RVM_Memory_Heap is private;
	
	type ARCL_Instruction is private;
	type ARCL_Instruction_Operand is abstract tagged null record;

	-- An access type to use polymorphism
	type ARCL_Instruction_Operand_Ptr is access all ARCL_Instruction_Operand'Class;	
	
	-- Operands may be literals, registers, label
	-- values or memory offsets
	type ARCL_Operand_Literal is new ARCL_Instruction_Operand with
		record
			Literal : ARCL_Register_Value;
		end record;

	type ARCL_Operand_Register is new ARCL_Instruction_Operand with
		record
			Register : ARCL_Register;
		end record;
		
	type ARCL_Operand_Memory_Offset is new ARCL_Instruction_Operand with
		record
			Memory_Offset : ARCL_Memory_Offset;
		end record;
	
	type ARCL_Operand_Label_Value is new ARCL_Instruction_Operand with
		record
			Label_Value : ARCL_Label_Value;
		end record;

	-- General purpose instruction subprograms
	procedure Invoke_Instruction(Instruction : in out ARCL_Instruction);
	function Get_Code(Instruction : in ARCL_Instruction) return ARCL_Instruction_Code;
	function Get_Operand_1(Instruction : in ARCL_Instruction) return ARCL_Instruction_Operand_Ptr;
	function Get_Operand_2(Instruction : in ARCL_Instruction) return ARCL_Instruction_Operand_Ptr;
	procedure Print_RVM_State;
	procedure Print_RVM_Stack;
	procedure Parse_ARCL_Instruction(Instruction : in out ARCL_Instruction; Str : String);
	function Parse_Code_From_String(Str : in String) return ARCL_Instruction_Code;
	function Parse_Register(Str : in String) return ARCL_Register;
	
private

	type ARCL_Instruction is
		record
			Code : ARCL_Instruction_Code;
			Operand_1 : ARCL_Instruction_Operand_Ptr;
			Operand_2 : ARCL_Instruction_Operand_Ptr;			
		end record;
			
		-- Procedures and tables for invoking instructions appropriately
	type ARCL_Instruction_Invocation_Proc is access procedure (Instruction : in ARCL_Instruction);
	type ARCL_Instruction_Invocation_Table is array (ARCL_Instruction_Code) of ARCL_Instruction_Invocation_Proc;
	
	-- The table to be used for invoking instructions 
	Instruction_Invocation_Table : ARCL_Instruction_Invocation_Table;
	
	procedure Invoke_ARCL_ADD(Instruction : in ARCL_Instruction);
	procedure Invoke_ARCL_SUB(Instruction : in ARCL_Instruction);
	procedure Invoke_ARCL_MULT(Instruction : in ARCL_Instruction);
	procedure Invoke_ARCL_DIV(Instruction : in ARCL_Instruction);
	procedure Invoke_ARCL_FLIP(Instruction : in ARCL_Instruction);
	procedure Invoke_ARCL_MOV(Instruction : in ARCL_Instruction);
	procedure Invoke_ARCL_LOADL(Instruction : in ARCL_Instruction);
	procedure Invoke_ARCL_LOADF(Instruction : in ARCL_Instruction);
	procedure Invoke_ARCL_LOADR(Instruction : in ARCL_Instruction);
	procedure Invoke_ARCL_STORF(Instruction : in ARCL_Instruction);
	procedure Invoke_ARCL_STORR(Instruction : in ARCL_Instruction);
	procedure Invoke_ARCL_FRAMEU(Instruction : in ARCL_Instruction);
	procedure Invoke_ARCL_FRAMEO(Instruction : in ARCL_Instruction);
	procedure Invoke_ARCL_RSAVE(Instruction : in ARCL_Instruction);
	procedure Invoke_ARCL_RLOAD(Instruction : in ARCL_Instruction);
	procedure Invoke_ARCL_LABEL(Instruction : in ARCL_Instruction);
	procedure Invoke_ARCL_PROC(Instruction : in ARCL_Instruction);
	procedure Invoke_ARCL_RET(Instruction : in ARCL_Instruction);
	procedure Invoke_ARCL_CALL(Instruction : in ARCL_Instruction);
	procedure Invoke_ARCL_JMP(Instruction : in ARCL_Instruction);
	procedure Invoke_ARCL_CMP(Instruction : in ARCL_Instruction);
	procedure Invoke_ARCL_JPE(Instruction : in ARCL_Instruction);
	procedure Invoke_ARCL_JPNE(Instruction : in ARCL_Instruction);
	procedure Invoke_ARCL_JPGR(Instruction : in ARCL_Instruction);
	procedure Invoke_ARCL_JPLS(Instruction : in ARCL_Instruction);
	procedure Invoke_ARCL_JPGE(Instruction : in ARCL_Instruction);
	procedure Invoke_ARCL_JPLE(Instruction : in ARCL_Instruction);
	procedure Invoke_ARCL_JAND(Instruction : in ARCL_Instruction);
	procedure Invoke_ARCL_JOR(Instruction : in ARCL_Instruction);
	procedure Invoke_ARCL_DELAY(Instruction : in ARCL_Instruction);
	procedure Invoke_ARCL_OUTPUT(Instruction : in ARCL_Instruction);
	procedure Invoke_ARCL_INPUT(Instruction : in ARCL_Instruction);
	procedure Invoke_ARCL_WRITE(Instruction : in ARCL_Instruction);
	procedure Invoke_ARCL_READ(Instruction : in ARCL_Instruction);
	
	-- Memory 
	type RVM_Memory_Stack is array (ARCL_Memory_Offset range 0 .. RVM_Stack_Space) of ARCL_Register_Value;
	type RVM_Memory_Heap is array (ARCL_Memory_Offset range 0 .. RVM_Heap_Space) of ARCL_Register_Value;
	
	-- Procedures to interact with memory directly (used by instruction invocations)
	
	-- RVM state variables
	Register_State : ARCL_Register_State := (others => 0);
	Memory_Stack : access RVM_Memory_Stack := new RVM_Memory_Stack'(others => 0);
	Memory_Heap : access RVM_Memory_Heap := new RVM_Memory_Heap'(others => 0);
	Frame_Pointer : ARCL_Memory_Offset := Memory_Stack.all'Last; -- Stack grows down
	
end Robotic_Virtual_Machine;