--  This file is part of the SCARL toolkit.
--  
--  SCARL is free software: you can redistribute it and/or modify
--  it under the terms of the GNU General Public License as published by
--  the Free Software Foundation, either version 3 of the License, or
--  (at your option) any later version.
--  
--  SCARL is distributed in the hope that it will be useful,
--  but WITHOUT ANY WARRANTY; without even the implied warranty of
--  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
--  GNU General Public License for more details.
--  
--  You should have received a copy of the GNU General Public License
--  along with SCARL.  If not, see <https://www.gnu.org/licenses/>.



with Ada.Strings; use Ada.Strings;
with Ada.Strings.Fixed; use Ada.Strings.Fixed;
with Ada.Text_IO;

package body Robotic_Virtual_Machine.Instruction_Parsing is
	
	procedure Parse_Operands_ARCL_ADD(Instruction : in out ARCL_Instruction; Operand_String : in String) is
		Register_1 : ARCL_Register;
		Register_2 : ARCL_Register;
		Space_Loc : Integer;
	begin
		Space_Loc := Index(Operand_String, " ");
		Register_1 := Parse_Register(Operand_String(Operand_String'First .. Space_Loc - 1));
		Register_2 := Parse_Register(Operand_String(Space_Loc + 1 .. Operand_String'Last));
		Instruction.Operand_1 := new ARCL_Operand_Register'(Register => Register_1);
		Instruction.Operand_2 := new ARCL_Operand_Register'(Register => Register_2);
	end Parse_Operands_ARCL_ADD;

	procedure Parse_Operands_ARCL_SUB(Instruction : in out ARCL_Instruction; Operand_String : in String) is
		Register_1 : ARCL_Register;
		Register_2 : ARCL_Register;
		Space_Loc : Integer;
	begin
		Space_Loc := Index(Operand_String, " ");
		Register_1 := Parse_Register(Operand_String(Operand_String'First .. Space_Loc - 1));
		Register_2 := Parse_Register(Operand_String(Space_Loc + 1 .. Operand_String'Last));
		Instruction.Operand_1 := new ARCL_Operand_Register'(Register => Register_1);
		Instruction.Operand_2 := new ARCL_Operand_Register'(Register => Register_2);
	end Parse_Operands_ARCL_SUB;

	procedure Parse_Operands_ARCL_MULT(Instruction : in out ARCL_Instruction; Operand_String : in String) is
		Register_1 : ARCL_Register;
		Register_2 : ARCL_Register;
		Space_Loc : Integer;
	begin
		Space_Loc := Index(Operand_String, " ");
		Register_1 := Parse_Register(Operand_String(Operand_String'First .. Space_Loc - 1));
		Register_2 := Parse_Register(Operand_String(Space_Loc + 1 .. Operand_String'Last));
		Instruction.Operand_1 := new ARCL_Operand_Register'(Register => Register_1);
		Instruction.Operand_2 := new ARCL_Operand_Register'(Register => Register_2);
	end Parse_Operands_ARCL_MULT;

	procedure Parse_Operands_ARCL_DIV(Instruction : in out ARCL_Instruction; Operand_String : in String) is
		Register_1 : ARCL_Register;
		Register_2 : ARCL_Register;
		Space_Loc : Integer;
	begin
		Space_Loc := Index(Operand_String, " ");
		Register_1 := Parse_Register(Operand_String(Operand_String'First .. Space_Loc - 1));
		Register_2 := Parse_Register(Operand_String(Space_Loc + 1 .. Operand_String'Last));
		Instruction.Operand_1 := new ARCL_Operand_Register'(Register => Register_1);
		Instruction.Operand_2 := new ARCL_Operand_Register'(Register => Register_2);
	end Parse_Operands_ARCL_DIV;

	procedure Parse_Operands_ARCL_FLIP(Instruction : in out ARCL_Instruction; Operand_String : in String) is
		Register_1 : ARCL_Register;
	begin
		Register_1 := Parse_Register(Operand_String);
		Instruction.Operand_1 := new ARCL_Operand_Register'(Register => Register_1);
	end Parse_Operands_ARCL_FLIP;

	procedure Parse_Operands_ARCL_MOV(Instruction : in out ARCL_Instruction; Operand_String : in String) is
		Register_1 : ARCL_Register;
		Register_2 : ARCL_Register;
		Space_Loc : Integer;
	begin
		Space_Loc := Index(Operand_String, " ");
		Register_1 := Parse_Register(Operand_String(Operand_String'First .. Space_Loc - 1));
		Register_2 := Parse_Register(Operand_String(Space_Loc + 1 .. Operand_String'Last));
		Instruction.Operand_1 := new ARCL_Operand_Register'(Register => Register_1);
		Instruction.Operand_2 := new ARCL_Operand_Register'(Register => Register_2);
	end Parse_Operands_ARCL_MOV;

	procedure Parse_Operands_ARCL_LOADL(Instruction : in out ARCL_Instruction; Operand_String : in String) is
		Register_1 : ARCL_Register;
		Literal_2 : ARCL_Register_Value;
		Space_Loc : Integer;
	begin
		Space_Loc := Index(Operand_String, " ");
		Register_1 := Parse_Register(Operand_String(Operand_String'First .. Space_Loc - 1));
		Literal_2 := Integer'Value(Operand_String(Space_Loc + 1 .. Operand_String'Last));
		-- Ada.Text_IO.Put_Line("Load Register " & Operand_String(Operand_String'First .. Space_Loc - 1) & " with literal " & Operand_String(Space_Loc + 1 .. Operand_String'Last));
		Instruction.Operand_1 := new ARCL_Operand_Register'(Register => Register_1);
		Instruction.Operand_2 := new ARCL_Operand_Literal'(Literal => Literal_2);
	end Parse_Operands_ARCL_LOADL;

	procedure Parse_Operands_ARCL_LOADF(Instruction : in out ARCL_Instruction; Operand_String : in String) is
		Register_1 : ARCL_Register;
		Offset_2 : ARCL_Memory_Offset;
		Space_Loc : Integer;
	begin
		Space_Loc := Index(Operand_String, " ");
		Register_1 := Parse_Register(Operand_String(Operand_String'First .. Space_Loc - 1));
		Offset_2 := ARCL_Memory_Offset(Integer'Value(Operand_String(Space_Loc + 1 .. Operand_String'Last)));
		Instruction.Operand_1 := new ARCL_Operand_Register'(Register => Register_1);
		Instruction.Operand_2 := new ARCL_Operand_Memory_Offset'(Memory_Offset => Offset_2);
	end Parse_Operands_ARCL_LOADF;

	procedure Parse_Operands_ARCL_LOADR(Instruction : in out ARCL_Instruction; Operand_String : in String) is
		Register_1 : ARCL_Register;
		Offset_2 : ARCL_Memory_Offset;
		Space_Loc : Integer;
	begin
		Space_Loc := Index(Operand_String, " ");
		Register_1 := Parse_Register(Operand_String(Operand_String'First .. Space_Loc - 1));
		Offset_2 := ARCL_Memory_Offset(Integer'Value(Operand_String(Space_Loc + 1 .. Operand_String'Last)));
		Instruction.Operand_1 := new ARCL_Operand_Register'(Register => Register_1);
		Instruction.Operand_2 := new ARCL_Operand_Memory_Offset'(Memory_Offset => Offset_2);
	end Parse_Operands_ARCL_LOADR;

	procedure Parse_Operands_ARCL_STORF(Instruction : in out ARCL_Instruction; Operand_String : in String) is
		Register_1 : ARCL_Register;
		Offset_2 : ARCL_Memory_Offset;
		Space_Loc : Integer;
	begin
		Space_Loc := Index(Operand_String, " ");
		Register_1 := Parse_Register(Operand_String(Operand_String'First .. Space_Loc - 1));
		Offset_2 := ARCL_Memory_Offset(Integer'Value(Operand_String(Space_Loc + 1 .. Operand_String'Last)));
		Instruction.Operand_1 := new ARCL_Operand_Register'(Register => Register_1);
		Instruction.Operand_2 := new ARCL_Operand_Memory_Offset'(Memory_Offset => Offset_2);
	end Parse_Operands_ARCL_STORF;

	procedure Parse_Operands_ARCL_STORR(Instruction : in out ARCL_Instruction; Operand_String : in String) is
		Register_1 : ARCL_Register;
		Offset_2 : ARCL_Memory_Offset;
		Space_Loc : Integer;
	begin
		Space_Loc := Index(Operand_String, " ");
		Register_1 := Parse_Register(Operand_String(Operand_String'First .. Space_Loc - 1));
		Offset_2 := ARCL_Memory_Offset(Integer'Value(Operand_String(Space_Loc + 1 .. Operand_String'Last)));
		Instruction.Operand_1 := new ARCL_Operand_Register'(Register => Register_1);
		Instruction.Operand_2 := new ARCL_Operand_Memory_Offset'(Memory_Offset => Offset_2);
	end Parse_Operands_ARCL_STORR;

	procedure Parse_Operands_ARCL_FRAMEU(Instruction : in out ARCL_Instruction; Operand_String : in String) is
		Offset_1 : ARCL_Memory_Offset;
	begin
		Offset_1 := ARCL_Memory_Offset(Integer'Value(Operand_String));
		Instruction.Operand_1 := new ARCL_Operand_Memory_Offset'(Memory_Offset => Offset_1);
	end Parse_Operands_ARCL_FRAMEU;

	procedure Parse_Operands_ARCL_FRAMEO(Instruction : in out ARCL_Instruction; Operand_String : in String) is
		Offset_1 : ARCL_Memory_Offset;
	begin
		Offset_1 := ARCL_Memory_Offset(Integer'Value(Operand_String));
		Instruction.Operand_1 := new ARCL_Operand_Memory_Offset'(Memory_Offset => Offset_1);
	end Parse_Operands_ARCL_FRAMEO;

	procedure Parse_Operands_ARCL_RSAVE(Instruction : in out ARCL_Instruction; Operand_String : in String) is
	begin
		-- No operands
		null;
	end Parse_Operands_ARCL_RSAVE;

	procedure Parse_Operands_ARCL_RLOAD(Instruction : in out ARCL_Instruction; Operand_String : in String) is
	begin
		-- No operands
		null;
	end Parse_Operands_ARCL_RLOAD;

	procedure Parse_Operands_ARCL_LABEL(Instruction : in out ARCL_Instruction; Operand_String : in String) is
		Label_1 : ARCL_Label_Value;
	begin
		Label_1 := new String'(Operand_String);
		Instruction.Operand_1 := new ARCL_Operand_Label_Value'(Label_Value => Label_1);
	end Parse_Operands_ARCL_LABEL;

	procedure Parse_Operands_ARCL_PROC(Instruction : in out ARCL_Instruction; Operand_String : in String) is
		Label_1 : ARCL_Label_Value;
	begin
		Label_1 := new String'(Operand_String);
		Instruction.Operand_1 := new ARCL_Operand_Label_Value'(Label_Value => Label_1);
	end Parse_Operands_ARCL_PROC;

	procedure Parse_Operands_ARCL_RET(Instruction : in out ARCL_Instruction; Operand_String : in String) is
	begin
		-- No operands
		null;
	end Parse_Operands_ARCL_RET;

	procedure Parse_Operands_ARCL_CALL(Instruction : in out ARCL_Instruction; Operand_String : in String) is
		Label_1 : ARCL_Label_Value;
	begin
		Label_1 := new String'(Operand_String);
		Instruction.Operand_1 := new ARCL_Operand_Label_Value'(Label_Value => Label_1);
	end Parse_Operands_ARCL_CALL;

	procedure Parse_Operands_ARCL_JMP(Instruction : in out ARCL_Instruction; Operand_String : in String) is
		Label_1 : ARCL_Label_Value;
	begin
		Label_1 := new String'(Operand_String);
		Instruction.Operand_1 := new ARCL_Operand_Label_Value'(Label_Value => Label_1);
	end Parse_Operands_ARCL_JMP;

	procedure Parse_Operands_ARCL_CMP(Instruction : in out ARCL_Instruction; Operand_String : in String) is
		Register_1 : ARCL_Register;
		Register_2 : ARCL_Register;
		Space_Loc : Integer;
	begin
		Space_Loc := Index(Operand_String, " ");
		Register_1 := Parse_Register(Operand_String(Operand_String'First .. Space_Loc - 1));
		Register_2 := Parse_Register(Operand_String(Space_Loc + 1 .. Operand_String'Last));
		Instruction.Operand_1 := new ARCL_Operand_Register'(Register => Register_1);
		Instruction.Operand_2 := new ARCL_Operand_Register'(Register => Register_2);
	end Parse_Operands_ARCL_CMP;

	procedure Parse_Operands_ARCL_JPE(Instruction : in out ARCL_Instruction; Operand_String : in String) is
		Label_1 : ARCL_Label_Value;
	begin
		Label_1 := new String'(Operand_String);
		Instruction.Operand_1 := new ARCL_Operand_Label_Value'(Label_Value => Label_1);
	end Parse_Operands_ARCL_JPE;

	procedure Parse_Operands_ARCL_JPNE(Instruction : in out ARCL_Instruction; Operand_String : in String) is
		Label_1 : ARCL_Label_Value;
	begin
		Label_1 := new String'(Operand_String);
		Instruction.Operand_1 := new ARCL_Operand_Label_Value'(Label_Value => Label_1);
	end Parse_Operands_ARCL_JPNE;

	procedure Parse_Operands_ARCL_JPGR(Instruction : in out ARCL_Instruction; Operand_String : in String) is
		Label_1 : ARCL_Label_Value;
	begin
		Label_1 := new String'(Operand_String);
		Instruction.Operand_1 := new ARCL_Operand_Label_Value'(Label_Value => Label_1);
	end Parse_Operands_ARCL_JPGR;

	procedure Parse_Operands_ARCL_JPLS(Instruction : in out ARCL_Instruction; Operand_String : in String) is
		Label_1 : ARCL_Label_Value;
	begin
		Label_1 := new String'(Operand_String);
		Instruction.Operand_1 := new ARCL_Operand_Label_Value'(Label_Value => Label_1);
	end Parse_Operands_ARCL_JPLS;

	procedure Parse_Operands_ARCL_JPGE(Instruction : in out ARCL_Instruction; Operand_String : in String) is
		Label_1 : ARCL_Label_Value;
	begin
		Label_1 := new String'(Operand_String);
		Instruction.Operand_1 := new ARCL_Operand_Label_Value'(Label_Value => Label_1);
	end Parse_Operands_ARCL_JPGE;

	procedure Parse_Operands_ARCL_JPLE(Instruction : in out ARCL_Instruction; Operand_String : in String) is
		Label_1 : ARCL_Label_Value;
	begin
		Label_1 := new String'(Operand_String);
		Instruction.Operand_1 := new ARCL_Operand_Label_Value'(Label_Value => Label_1);
	end Parse_Operands_ARCL_JPLE;

	procedure Parse_Operands_ARCL_JAND(Instruction : in out ARCL_Instruction; Operand_String : in String) is
		Label_1 : ARCL_Label_Value;
	begin
		Label_1 := new String'(Operand_String);
		Instruction.Operand_1 := new ARCL_Operand_Label_Value'(Label_Value => Label_1);
	end Parse_Operands_ARCL_JAND;

	procedure Parse_Operands_ARCL_JOR(Instruction : in out ARCL_Instruction; Operand_String : in String) is
		Label_1 : ARCL_Label_Value;
	begin
		Label_1 := new String'(Operand_String);
		Instruction.Operand_1 := new ARCL_Operand_Label_Value'(Label_Value => Label_1);
	end Parse_Operands_ARCL_JOR;

	procedure Parse_Operands_ARCL_DELAY(Instruction : in out ARCL_Instruction; Operand_String : in String) is
		Register_1 : ARCL_Register;
	begin
		Register_1 := Parse_Register(Operand_String);
		Instruction.Operand_1 := new ARCL_Operand_Register'(Register => Register_1);
	end Parse_Operands_ARCL_DELAY;

	procedure Parse_Operands_ARCL_OUTPUT(Instruction : in out ARCL_Instruction; Operand_String : in String) is
		Register_1 : ARCL_Register;
	begin
		Register_1 := Parse_Register(Operand_String);
		Instruction.Operand_1 := new ARCL_Operand_Register'(Register => Register_1);
	end Parse_Operands_ARCL_OUTPUT;

	procedure Parse_Operands_ARCL_INPUT(Instruction : in out ARCL_Instruction; Operand_String : in String) is
		Register_1 : ARCL_Register;
	begin
		Register_1 := Parse_Register(Operand_String);
		Instruction.Operand_1 := new ARCL_Operand_Register'(Register => Register_1);
	end Parse_Operands_ARCL_INPUT;

	procedure Parse_Operands_ARCL_WRITE(Instruction : in out ARCL_Instruction; Operand_String : in String) is
		Register_1 : ARCL_Register;
		Register_2 : ARCL_Register;
		Space_Loc : Integer;
	begin
		Space_Loc := Index(Operand_String, " ");
		Register_1 := Parse_Register(Operand_String(Operand_String'First .. Space_Loc - 1));
		Register_2 := Parse_Register(Operand_String(Space_Loc + 1 .. Operand_String'Last));
		Instruction.Operand_1 := new ARCL_Operand_Register'(Register => Register_1);
		Instruction.Operand_2 := new ARCL_Operand_Register'(Register => Register_2);
	end Parse_Operands_ARCL_WRITE;

	procedure Parse_Operands_ARCL_READ(Instruction : in out ARCL_Instruction; Operand_String : in String) is
		Register_1 : ARCL_Register;
		Register_2 : ARCL_Register;
		Space_Loc : Integer;
	begin
		Space_Loc := Index(Operand_String, " ");
		Register_1 := Parse_Register(Operand_String(Operand_String'First .. Space_Loc - 1));
		Register_2 := Parse_Register(Operand_String(Space_Loc + 1 .. Operand_String'Last));
		Instruction.Operand_1 := new ARCL_Operand_Register'(Register => Register_1);
		Instruction.Operand_2 := new ARCL_Operand_Register'(Register => Register_2);
	end Parse_Operands_ARCL_READ;

begin
	Operand_Parse_Table := (
		ARCL_ADD => Parse_Operands_ARCL_ADD'Access,
		ARCL_SUB => Parse_Operands_ARCL_SUB'Access,
		ARCL_MULT => Parse_Operands_ARCL_MULT'Access,
		ARCL_DIV => Parse_Operands_ARCL_DIV'Access,
		ARCL_FLIP => Parse_Operands_ARCL_FLIP'Access,
		ARCL_MOV => Parse_Operands_ARCL_MOV'Access,
		ARCL_LOADL => Parse_Operands_ARCL_LOADL'Access,
		ARCL_LOADF => Parse_Operands_ARCL_LOADF'Access,
		ARCL_LOADR => Parse_Operands_ARCL_LOADR'Access,
		ARCL_STORF => Parse_Operands_ARCL_STORF'Access,
		ARCL_STORR => Parse_Operands_ARCL_STORR'Access,
		ARCL_FRAMEU => Parse_Operands_ARCL_FRAMEU'Access,
		ARCL_FRAMEO => Parse_Operands_ARCL_FRAMEO'Access,
		ARCL_RSAVE => Parse_Operands_ARCL_RSAVE'Access,
		ARCL_RLOAD => Parse_Operands_ARCL_RLOAD'Access,
		ARCL_LABEL => Parse_Operands_ARCL_LABEL'Access,
		ARCL_PROC => Parse_Operands_ARCL_PROC'Access,
		ARCL_RET => Parse_Operands_ARCL_RET'Access,
		ARCL_CALL => Parse_Operands_ARCL_CALL'Access,
		ARCL_JMP => Parse_Operands_ARCL_JMP'Access,
		ARCL_CMP => Parse_Operands_ARCL_CMP'Access,
		ARCL_JPE => Parse_Operands_ARCL_JPE'Access,
		ARCL_JPNE => Parse_Operands_ARCL_JPNE'Access,
		ARCL_JPGR => Parse_Operands_ARCL_JPGR'Access,
		ARCL_JPLS => Parse_Operands_ARCL_JPLS'Access,
		ARCL_JPGE => Parse_Operands_ARCL_JPGE'Access,
		ARCL_JPLE => Parse_Operands_ARCL_JPLE'Access,
		ARCL_JAND => Parse_Operands_ARCL_JAND'Access,
		ARCL_JOR => Parse_Operands_ARCL_JOR'Access,
		ARCL_DELAY => Parse_Operands_ARCL_DELAY'Access,
		ARCL_OUTPUT => Parse_Operands_ARCL_OUTPUT'Access,
		ARCL_INPUT => Parse_Operands_ARCL_INPUT'Access,
		ARCL_WRITE => Parse_Operands_ARCL_WRITE'Access,
		ARCL_READ => Parse_Operands_ARCL_READ'Access
	);
end Robotic_Virtual_Machine.Instruction_Parsing;