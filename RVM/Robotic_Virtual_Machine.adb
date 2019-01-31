
with Ada.Text_IO;
with Robotic_Virtual_Machine.Instruction_Parsing;
with Robotic_Virtual_Machine.Procedures_Labels;
with Robotic_Virtual_Machine.Conditional;
with Robotic_Virtual_Machine.Sensors_Actuators;

package body Robotic_Virtual_Machine is

	procedure Invoke_Instruction(Instruction : in out ARCL_Instruction) is
	begin
		Instruction_Invocation_Table(Instruction.Code)(Instruction);
	end Invoke_Instruction;
	
	function Get_Code(Instruction : in ARCL_Instruction) return ARCL_Instruction_Code is
	begin
		return Instruction.Code;
	end Get_Code;
	
	function Get_Operand_1(Instruction : in ARCL_Instruction) return ARCL_Instruction_Operand_Ptr is
	begin
		return Instruction.Operand_1;
	end Get_Operand_1;
	
	function Get_Operand_2(Instruction : in ARCL_Instruction) return ARCL_Instruction_Operand_Ptr is
	begin
		return Instruction.Operand_2;
	end Get_Operand_2;

	procedure Print_RVM_State is
		use Ada.Text_IO;
	begin
		Put_Line("Registers");
		Put_Line("R0:" & Integer'Image(Register_State(R0)));
		Put_Line("R1:" & Integer'Image(Register_State(R1)));
		Put_Line("R2:" & Integer'Image(Register_State(R2)));
		Put_Line("R3:" & Integer'Image(Register_State(R3)));
		Put_Line("R4:" & Integer'Image(Register_State(R4)));
		Put_Line("R5:" & Integer'Image(Register_State(R5)));
		Put_Line("R6:" & Integer'Image(Register_State(R6)));
		Put_Line("R7:" & Integer'Image(Register_State(R7)));
		Put_Line("FRR:" & Integer'Image(Register_State(FRR)));
		New_Line;
	end Print_RVM_State;
	
	procedure Print_RVM_Stack is
		use Ada.Text_IO;
		End_At : ARCL_Memory_Offset;
		Current : ARCL_Memory_Offset := Frame_Pointer;
	begin
		-- Stack grows down so start at the top (MemoryStack.all'Last) and
		-- go down
		End_At := Memory_Stack.all'Last;
		-- Print top first and then go down
		while Current <= End_At loop
			Put_Line(Integer'Image(Integer(Memory_Stack(Current))));
			Current := Current + 1;
		end loop;
	end Print_RVM_Stack;
	
	-- Instruction parsing procedures and functions
	procedure Parse_ARCL_Instruction(Instruction : in out ARCL_Instruction; Str : String) is
		-- Not using Code_String to enable direct indexing
		Code_Str : String(Str'First .. Str'First+5) := "      ";
		Code : ARCL_Instruction_Code;
		I : Integer := Str'First;
	begin
		while I <= Str'Last and then Str(I) /= ' ' loop
			Code_Str(I) := Str(I);
			I := I + 1;
		end loop;
		-- We have the code string, determine the code
		-- the string should slide when obtaining
		-- from the index
		Code := Parse_Code_From_String(Code_Str(Str'First .. Str'First+I-2));
		
		-- Now we want to parse the operands
		-- depending on the value of 
		-- "Code"
		Robotic_Virtual_Machine.Instruction_Parsing.Operand_Parse_Table(Code)(Instruction, Str(I+1 .. Str'Last));
		Instruction.Code := Code;
	end Parse_ARCL_Instruction;
	
	function Parse_Code_From_String(Str : in String) return ARCL_Instruction_Code is
		-- TODO: use hashtable of ARCL codes to determine code
	begin	
		-- We are going to use a big if-then block for now
		if Str = "ADD" then
			return ARCL_ADD;
		elsif Str = "SUB" then
			return ARCL_SUB;
		elsif Str = "MULT" then
			return ARCL_MULT;
		elsif Str = "DIV" then
			return ARCL_DIV;
		elsif Str = "FLIP" then
			return ARCL_FLIP;
		elsif Str = "MOV" then
			return ARCL_MOV;
		elsif Str = "LOADL" then
			return ARCL_LOADL;
		elsif Str = "LOADF" then
			return ARCL_LOADF;
		elsif Str = "LOADR" then
			return ARCL_LOADR;
		elsif Str = "STORF" then
			return ARCL_STORF;
		elsif Str = "STORR" then
			return ARCL_STORR;
		elsif Str = "FRAMEU" then
			return ARCL_FRAMEU;
		elsif Str = "FRAMEO" then
			return ARCL_FRAMEO;
		elsif Str = "RSAVE" then
			return ARCL_RSAVE;
		elsif Str = "RLOAD" then
			return ARCL_RLOAD;
		elsif Str = "LABEL" then
			return ARCL_LABEL;
		elsif Str = "PROC" then
			return ARCL_PROC;
		elsif Str = "RET" then
			return ARCL_RET;
		elsif Str = "CALL" then
			return ARCL_CALL;
		elsif Str = "JMP" then
			return ARCL_JMP;
		elsif Str = "CMP" then
			return ARCL_CMP;
		elsif Str = "JPE" then
			return ARCL_JPE;
		elsif Str = "JPNE" then
			return ARCL_JPNE;
		elsif Str = "JPGR" then
			return ARCL_JPGR;
		elsif Str = "JPLS" then
			return ARCL_JPLS;
		elsif Str = "JPGE" then
			return ARCL_JPGE;
		elsif Str = "JPLE" then
			return ARCL_JPLE;
		elsif Str = "JAND" then
			return ARCL_JAND;
		elsif Str = "JOR" then
			return ARCL_JOR;
		elsif Str = "DELAY" then
			return ARCL_DELAY;
		elsif Str = "OUTPUT" then
			return ARCL_OUTPUT;
		elsif Str = "INPUT" then
			return ARCL_INPUT;
		elsif Str = "WRITE" then
			return ARCL_WRITE;
		elsif Str = "READ" then
			return ARCL_READ;
		end if;
		-- Should raise an exception or something here
		-- but for now we are using a dummy value
		return ARCL_ADD;
	end Parse_Code_From_String;
	
	function Parse_Register(Str : in String) return ARCL_Register is
		-- TO DO: use a table for faster parsing
	begin
		if Str = "R0" then
			return R0;
		elsif Str = "R1" then
			return R1;
		elsif Str = "R2" then
			return R2;
		elsif Str = "R3" then
			return R3;
		elsif Str = "R4" then
			return R4;
		elsif Str = "R5" then
			return R5;
		elsif Str = "R6" then
			return R6;
		elsif Str = "R7" then
			return R7;
		elsif Str = "FRR" then
			return FRR;
		end if;
		
		-- dummy, need an error code for this to be correct
		return R0;
	end Parse_Register;
	
	-- Instruction invocation procedures
	
	-- Expression instructions
	
	-- Add the two register, storing the result
	-- in the right hand side register
	procedure Invoke_ARCL_ADD(Instruction : in ARCL_Instruction) is
		Reg1 : ARCL_Operand_Register := ARCL_Operand_Register(Get_Operand_1(Instruction).all);
		Reg2 : ARCL_Operand_Register := ARCL_Operand_Register(Get_Operand_2(Instruction).all);
	begin
		Register_State(Reg2.Register) := Register_State(Reg1.Register) + 
											Register_State(Reg2.Register);
	end Invoke_ARCL_ADD;
	
	-- Subtract the two registers reg1 - reg2, storing
	-- the result in the right hand register
	procedure Invoke_ARCL_SUB(Instruction : in ARCL_Instruction) is
		Reg1 : ARCL_Operand_Register := ARCL_Operand_Register(Get_Operand_1(Instruction).all);
		Reg2 : ARCL_Operand_Register := ARCL_Operand_Register(Get_Operand_2(Instruction).all);
	begin
		Register_State(Reg2.Register) := Register_State(Reg1.Register) - 
											Register_State(Reg2.Register);
	end Invoke_ARCL_SUB;
	
	-- Multiply the two registers, storing the 
	-- result in the right hand register
	procedure Invoke_ARCL_MULT(Instruction : in ARCL_Instruction) is
		Reg1 : ARCL_Operand_Register := ARCL_Operand_Register(Get_Operand_1(Instruction).all);
		Reg2 : ARCL_Operand_Register := ARCL_Operand_Register(Get_Operand_2(Instruction).all);
	begin
		Register_State(Reg2.Register) := Register_State(Reg1.Register) * 
											Register_State(Reg2.Register);
	end Invoke_ARCL_MULT;
	
	-- Integer division on the two registers reg1 / reg2,
	-- storing the result in the right hand register 
	procedure Invoke_ARCL_DIV(Instruction : in ARCL_Instruction) is
		Reg1 : ARCL_Operand_Register := ARCL_Operand_Register(Get_Operand_1(Instruction).all);
		Reg2 : ARCL_Operand_Register := ARCL_Operand_Register(Get_Operand_2(Instruction).all);
	begin
		Register_State(Reg2.Register) := Register_State(Reg1.Register) / 
											Register_State(Reg2.Register);
	end Invoke_ARCL_DIV;
	
	-- Flip the sign of the value in the given register
	procedure Invoke_ARCL_FLIP(Instruction : in ARCL_Instruction) is
		Reg1 : ARCL_Operand_Register := ARCL_Operand_Register(Get_Operand_1(Instruction).all);
	begin
		Register_State(Reg1.Register) := -Register_State(Reg1.Register);
	end Invoke_ARCL_FLIP;
	
	-- Memory instructions
	
	-- Moves data from the src register to 
	-- the dst register
	procedure Invoke_ARCL_MOV(Instruction : in ARCL_Instruction) is
		Src : ARCL_Operand_Register := ARCL_Operand_Register(Get_Operand_1(Instruction).all);
		Dst : ARCL_Operand_Register := ARCL_Operand_Register(Get_Operand_2(Instruction).all);
	begin
		Register_State(Dst.Register) := Register_State(Src.Register);
	end Invoke_ARCL_MOV;
	
	-- Loads the register reg with lit
	procedure Invoke_ARCL_LOADL(Instruction : in ARCL_Instruction) is
		Reg : ARCL_Operand_Register := ARCL_Operand_Register(Get_Operand_1(Instruction).all);
		Lit : ARCL_Operand_Literal := ARCL_Operand_Literal(Get_Operand_2(Instruction).all);
	begin
		Register_State(Reg.Register) := Lit.Literal;
	end Invoke_ARCL_LOADL;
	
	-- Loads the value stored offset values 
	-- away from the top of the stack frame and
	-- loads it into register reg
	procedure Invoke_ARCL_LOADF(Instruction : in ARCL_Instruction) is
		Reg : ARCL_Operand_Register := ARCL_Operand_Register(Get_Operand_1(Instruction).all);
		Offset : ARCL_Operand_Memory_Offset := ARCL_Operand_Memory_Offset(Get_Operand_2(Instruction).all);
	begin
		-- Offset is towards the bottom of the stack (positive direction)
		Register_State(Reg.Register) := 
						Memory_Stack(Frame_Pointer + Offset.Memory_Offset);
	end Invoke_ARCL_LOADF;
	
	-- Finds the value from storage that is offset
	-- values away from the beginning of static
	-- storage and stores it into register reg
	procedure Invoke_ARCL_LOADR(Instruction : in ARCL_Instruction) is
		Reg : ARCL_Operand_Register := ARCL_Operand_Register(Get_Operand_1(Instruction).all);
		Offset : ARCL_Operand_Memory_Offset := ARCL_Operand_Memory_Offset(Get_Operand_2(Instruction).all);
	begin
		Register_State(Reg.Register) := Memory_Heap(Offset.Memory_Offset);
	end Invoke_ARCL_LOADR;
	
	-- Goes to the value located offset values 
	-- away from the top of the stack frame and
	-- changes it so that it is equal to the value 
	-- located in the register reg
	procedure Invoke_ARCL_STORF(Instruction : in ARCL_Instruction) is
		Reg : ARCL_Operand_Register := ARCL_Operand_Register(Get_Operand_1(Instruction).all);
		Offset : ARCL_Operand_Memory_Offset := ARCL_Operand_Memory_Offset(Get_Operand_2(Instruction).all);
	begin
		-- Offset is towards the bottom of the stack (positive direction)
		Memory_Stack(Frame_Pointer + Offset.Memory_Offset) := 
						Register_State(Reg.Register);
	end Invoke_ARCL_STORF;
	
	-- Loads the value in register reg into the 
	-- spot that is offset values away from the
	-- beginning of storage
	procedure Invoke_ARCL_STORR(Instruction : in ARCL_Instruction) is
		Reg : ARCL_Operand_Register := ARCL_Operand_Register(Get_Operand_1(Instruction).all);
		Offset : ARCL_Operand_Memory_Offset := ARCL_Operand_Memory_Offset(Get_Operand_2(Instruction).all);
	begin
		Memory_Heap(Offset.Memory_Offset) := Register_State(Reg.Register);
	end Invoke_ARCL_STORR;
	
	-- Push the stack frame so that it is offset values
	-- farther away. For setting up activation record
	-- space
	procedure Invoke_ARCL_FRAMEU(Instruction : in ARCL_Instruction) is
		Offset : ARCL_Operand_Memory_Offset := ARCL_Operand_Memory_Offset(Get_Operand_1(Instruction).all);
	begin
		-- Stack grows down
		Frame_Pointer := Frame_Pointer - Offset.Memory_Offset;
	end Invoke_ARCL_FRAMEU;
	
	-- Pop the stack frame so that it is offset values
	-- closer. For removing activation record space.
	procedure Invoke_ARCL_FRAMEO(Instruction : in ARCL_Instruction) is
		Offset : ARCL_Operand_Memory_Offset := ARCL_Operand_Memory_Offset(Get_Operand_1(Instruction).all);
	begin
		-- Stack grows down
		Frame_Pointer := Frame_Pointer + Offset.Memory_Offset;
	end Invoke_ARCL_FRAMEO;
	
	-- Save the current state of the machine by
	-- stacking all registers on the stack and
	-- incrementing the frame pointer.
	procedure Invoke_ARCL_RSAVE(Instruction : in ARCL_Instruction) is
	begin
		Frame_Pointer := Frame_Pointer - 8;
		Memory_Stack(Frame_Pointer + 0) := Register_State(R0);
		Memory_Stack(Frame_Pointer + 1) := Register_State(R1);
		Memory_Stack(Frame_Pointer + 2) := Register_State(R2);
		Memory_Stack(Frame_Pointer + 3) := Register_State(R3);
		Memory_Stack(Frame_Pointer + 4) := Register_State(R4);
		Memory_Stack(Frame_Pointer + 5) := Register_State(R5);
		Memory_Stack(Frame_Pointer + 6) := Register_State(R6);
		Memory_Stack(Frame_Pointer + 7) := Register_State(R7);
	end Invoke_ARCL_RSAVE;
	
	-- Recovering a previous state by unstacking
	-- previously saved registers and then 
	-- decrementing the frame pointer appropriately
	procedure Invoke_ARCL_RLOAD(Instruction : in ARCL_Instruction) is
	begin
		Register_State(R0) := Memory_Stack(Frame_Pointer + 0);
		Register_State(R1) := Memory_Stack(Frame_Pointer + 1);
		Register_State(R2) := Memory_Stack(Frame_Pointer + 2);
		Register_State(R3) := Memory_Stack(Frame_Pointer + 3);
		Register_State(R4) := Memory_Stack(Frame_Pointer + 4);
		Register_State(R5) := Memory_Stack(Frame_Pointer + 5);
		Register_State(R6) := Memory_Stack(Frame_Pointer + 6);
		Register_State(R7) := Memory_Stack(Frame_Pointer + 7);
		Frame_Pointer := Frame_Pointer + 8;
	end Invoke_ARCL_RLOAD;
	
	-- Program Control instructions
	
	-- Defines a label at this spot and calls it "label"
	procedure Invoke_ARCL_LABEL(Instruction : in ARCL_Instruction) is
		Label : ARCL_Operand_Label_Value := ARCL_Operand_Label_Value(Get_Operand_1(Instruction).all);
		use Robotic_Virtual_Machine.Procedures_Labels;
	begin
		-- Register_Label(Label.Label_Value);
		null; -- should have been registered before execution
	end Invoke_ARCL_LABEL;
	
	-- begins a procedure definition and calls it label
	procedure Invoke_ARCL_PROC(Instruction : in ARCL_Instruction) is
		Label : ARCL_Operand_Label_Value := ARCL_Operand_Label_Value(Get_Operand_1(Instruction).all);
		use Robotic_Virtual_Machine.Procedures_Labels;
	begin
		-- Register_Label(Label.Label_Value);
		null; -- should have been registered before execution
	end Invoke_ARCL_PROC;
	
	-- Returns control back to the callee from
	-- the procedure call
	procedure Invoke_ARCL_RET(Instruction : in ARCL_Instruction) is
		use Robotic_Virtual_Machine.Procedures_Labels;
	begin
		Recall_Return_Address;
	end Invoke_ARCL_RET;
	
	-- Stacks the current instruction address as a
	-- return point and then transfers control to label
	procedure Invoke_ARCL_CALL(Instruction : in ARCL_Instruction) is
		Label : ARCL_Operand_Label_Value := ARCL_Operand_Label_Value(Get_Operand_1(Instruction).all);
		use Robotic_Virtual_Machine.Procedures_Labels;
	begin
		Stack_Return_Address;
		Go_To(Label.Label_Value);
	end Invoke_ARCL_CALL;
	
	-- Jumps to the label label
	procedure Invoke_ARCL_JMP(Instruction : in ARCL_Instruction) is
		Label : ARCL_Operand_Label_Value := ARCL_Operand_Label_Value(Get_Operand_1(Instruction).all);
		use Robotic_Virtual_Machine.Procedures_Labels;
	begin
		Go_To(Label.Label_Value);
	end Invoke_ARCL_JMP;
	
	-- Compares the two registers reg1 and reg2 and
	-- changes the internal state of this ARCL machine
	procedure Invoke_ARCL_CMP(Instruction : in ARCL_Instruction) is
		Reg1 : ARCL_Operand_Register := ARCL_Operand_Register(Get_Operand_1(Instruction).all);
		Reg2 : ARCL_Operand_Register := ARCL_Operand_Register(Get_Operand_2(Instruction).all);
		use Robotic_Virtual_Machine.Conditional;
	begin
		Compare(
			Register_State(Reg1.Register),
			Register_State(Reg2.Register)
		);
	end Invoke_ARCL_CMP;
	
	-- Jump to the label if the most recent CMP had reg1 == reg2
	procedure Invoke_ARCL_JPE(Instruction : in ARCL_Instruction) is
		Label : ARCL_Operand_Label_Value := ARCL_Operand_Label_Value(Get_Operand_1(Instruction).all);
		use Robotic_Virtual_Machine.Procedures_Labels;
		use Robotic_Virtual_Machine.Conditional;
	begin
		if Get_Equals_Flag then
			Go_To(Label.Label_Value);
		end if;
	end Invoke_ARCL_JPE;
	
	-- Jump to the label if the most recent CMP had reg1 != reg2
	procedure Invoke_ARCL_JPNE(Instruction : in ARCL_Instruction) is
		Label : ARCL_Operand_Label_Value := ARCL_Operand_Label_Value(Get_Operand_1(Instruction).all);
		use Robotic_Virtual_Machine.Procedures_Labels;
		use Robotic_Virtual_Machine.Conditional;
	begin
		if not Get_Equals_Flag then
			Go_To(Label.Label_Value);
		end if;
	end Invoke_ARCL_JPNE;
	
	-- Jump to the label if the most recent CMP had reg1 > reg2
	procedure Invoke_ARCL_JPGR(Instruction : in ARCL_Instruction) is
		Label : ARCL_Operand_Label_Value := ARCL_Operand_Label_Value(Get_Operand_1(Instruction).all);
		use Robotic_Virtual_Machine.Procedures_Labels;
		use Robotic_Virtual_Machine.Conditional;
	begin
		if Get_Greater_Flag then
			Go_To(Label.Label_Value);
		end if;
	end Invoke_ARCL_JPGR;
	
	-- Jump to the label if the most recent CMP had reg1 < reg2
	procedure Invoke_ARCL_JPLS(Instruction : in ARCL_Instruction) is
		Label : ARCL_Operand_Label_Value := ARCL_Operand_Label_Value(Get_Operand_1(Instruction).all);
		use Robotic_Virtual_Machine.Procedures_Labels;
		use Robotic_Virtual_Machine.Conditional;
	begin
		if Get_Less_Flag then
			Go_To(Label.Label_Value);
		end if;
	end Invoke_ARCL_JPLS;
	
	-- Jump to the label if the most recent CMP had reg1 >= reg2
	procedure Invoke_ARCL_JPGE(Instruction : in ARCL_Instruction) is
		Label : ARCL_Operand_Label_Value := ARCL_Operand_Label_Value(Get_Operand_1(Instruction).all);
		use Robotic_Virtual_Machine.Procedures_Labels;
		use Robotic_Virtual_Machine.Conditional;
	begin
		if Get_Greater_Flag and Get_Equals_Flag then
			Go_To(Label.Label_Value);
		end if;
	end Invoke_ARCL_JPGE;
	
	-- Jump to the label if the most recent CMP had reg1 <= reg2
	procedure Invoke_ARCL_JPLE(Instruction : in ARCL_Instruction) is
		Label : ARCL_Operand_Label_Value := ARCL_Operand_Label_Value(Get_Operand_1(Instruction).all);
		use Robotic_Virtual_Machine.Procedures_Labels;
		use Robotic_Virtual_Machine.Conditional;
	begin
		if Get_Less_Flag and Get_Equals_Flag then
			Go_To(Label.Label_Value);
		end if;
	end Invoke_ARCL_JPLE;
	
	-- Jump to the label if the most recent CMP had reg1 AND reg2
	procedure Invoke_ARCL_JAND(Instruction : in ARCL_Instruction) is
		Label : ARCL_Operand_Label_Value := ARCL_Operand_Label_Value(Get_Operand_1(Instruction).all);
		use Robotic_Virtual_Machine.Procedures_Labels;
		use Robotic_Virtual_Machine.Conditional;
	begin
		if Get_And_Flag then
			Go_To(Label.Label_Value);
		end if;
	end Invoke_ARCL_JAND;
	
	-- Jump to the label if the most recent CMP had reg1 OR reg2
	procedure Invoke_ARCL_JOR(Instruction : in ARCL_Instruction) is
		Label : ARCL_Operand_Label_Value := ARCL_Operand_Label_Value(Get_Operand_1(Instruction).all);
		use Robotic_Virtual_Machine.Procedures_Labels;
		use Robotic_Virtual_Machine.Conditional;
	begin
		if Get_Or_Flag then
			Go_To(Label.Label_Value);
		end if;
	end Invoke_ARCL_JOR;
	
	-- Delays the program for the number of milliseconds
	-- as specified in reg
	procedure Invoke_ARCL_DELAY(Instruction : in ARCL_Instruction) is
		Reg : ARCL_Operand_Register := ARCL_Operand_Register(Get_Operand_1(Instruction).all);
		Milliseconds_Count : Integer := Integer(Register_State(Reg.Register));
	begin
		-- predefined keyword from Ada
		delay Duration(Float(Milliseconds_Count)/1000.0);
	end Invoke_ARCL_DELAY;
	
	-- Device Control instructions
	procedure Invoke_ARCL_OUTPUT(Instruction : in ARCL_Instruction) is
		Reg : ARCL_Operand_Register := ARCL_Operand_Register(Get_Operand_1(Instruction).all);
		use Robotic_Virtual_Machine.Sensors_Actuators;
	begin
		Configure_Pin(Natural(Register_State(Reg.Register)), Output);
	end Invoke_ARCL_OUTPUT;
	
	procedure Invoke_ARCL_INPUT(Instruction : in ARCL_Instruction) is
		Reg : ARCL_Operand_Register := ARCL_Operand_Register(Get_Operand_1(Instruction).all);
		use Robotic_Virtual_Machine.Sensors_Actuators;
	begin
		Configure_Pin(Natural(Register_State(Reg.Register)), Input);
	end Invoke_ARCL_INPUT;
	
	procedure Invoke_ARCL_WRITE(Instruction : in ARCL_Instruction) is
		RegPin : ARCL_Operand_Register := ARCL_Operand_Register(Get_Operand_1(Instruction).all);
		RegData : ARCL_Operand_Register := ARCL_Operand_Register(Get_Operand_2(Instruction).all);
		use Robotic_Virtual_Machine.Sensors_Actuators;
	begin
		Write_Pin(
			Natural(Register_State(RegPin.Register)),
			Register_State(RegData.Register)
		);
	end Invoke_ARCL_WRITE;
	
	procedure Invoke_ARCL_READ(Instruction : in ARCL_Instruction) is
		RegPin : ARCL_Operand_Register := ARCL_Operand_Register(Get_Operand_1(Instruction).all);
		RegData : ARCL_Operand_Register := ARCL_Operand_Register(Get_Operand_2(Instruction).all);
		use Robotic_Virtual_Machine.Sensors_Actuators;
	begin
		Read_Pin(
			Natural(Register_State(RegPin.Register)),
			Register_State(RegData.Register)
		);
	end Invoke_ARCL_READ;

begin
	-- Initialize the invocation table
	Instruction_Invocation_Table :=
	(
		ARCL_ADD => Invoke_ARCL_ADD'Access,
		ARCL_SUB => Invoke_ARCL_SUB'Access,
		ARCL_MULT => Invoke_ARCL_MULT'Access,
		ARCL_DIV => Invoke_ARCL_DIV'Access,
		ARCL_FLIP => Invoke_ARCL_FLIP'Access,
		ARCL_MOV => Invoke_ARCL_MOV'Access,
		ARCL_LOADL => Invoke_ARCL_LOADL'Access,
		ARCL_LOADF => Invoke_ARCL_LOADF'Access,
		ARCL_LOADR => Invoke_ARCL_LOADR'Access,
		ARCL_STORF => Invoke_ARCL_STORF'Access,
		ARCL_STORR => Invoke_ARCL_STORR'Access,
		ARCL_FRAMEU => Invoke_ARCL_FRAMEU'Access,
		ARCL_FRAMEO => Invoke_ARCL_FRAMEO'Access,
		ARCL_RSAVE => Invoke_ARCL_RSAVE'Access,
		ARCL_RLOAD => Invoke_ARCL_RLOAD'Access,
		ARCL_LABEL => Invoke_ARCL_LABEL'Access,
		ARCL_PROC => Invoke_ARCL_PROC'Access,
		ARCL_RET => Invoke_ARCL_RET'Access,
		ARCL_CALL => Invoke_ARCL_CALL'Access,
		ARCL_JMP => Invoke_ARCL_JMP'Access,
		ARCL_CMP => Invoke_ARCL_CMP'Access,
		ARCL_JPE => Invoke_ARCL_JPE'Access,
		ARCL_JPNE => Invoke_ARCL_JPNE'Access,
		ARCL_JPGR => Invoke_ARCL_JPGR'Access,
		ARCL_JPLS => Invoke_ARCL_JPLS'Access,
		ARCL_JPGE => Invoke_ARCL_JPGE'Access,
		ARCL_JPLE => Invoke_ARCL_JPLE'Access,
		ARCL_JAND => Invoke_ARCL_JAND'Access,
		ARCL_JOR => Invoke_ARCL_JOR'Access,
		ARCL_DELAY => Invoke_ARCL_DELAY'Access,
		ARCL_OUTPUT => Invoke_ARCL_OUTPUT'Access,
		ARCL_INPUT => Invoke_ARCL_INPUT'Access,
		ARCL_WRITE => Invoke_ARCL_WRITE'Access,
		ARCL_READ => Invoke_ARCL_READ'Access
	);
end Robotic_Virtual_Machine;