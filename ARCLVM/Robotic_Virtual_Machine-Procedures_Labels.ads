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



with Robotic_Virtual_Machine; use Robotic_Virtual_Machine;
with Robotic_Virtual_Machine.Program; use Robotic_Virtual_Machine.Program;

package Robotic_Virtual_Machine.Procedures_Labels is

	-- Registers the current instruction as the 
	-- label name. Usage should be constrained so 
	-- that only LABEL and PROC instructions are
	-- registers with label names. Goes off the
	-- current state of the machine
	procedure Register_Label(Label_Value : in ARCL_Label_Value; Address : in Integer);
	
	-- Sets the instruction pointer to 
	-- be pointing at the PROC or LABEL instruction
	-- with the given label value. This is designed
	-- to be called before the subsequent instruction
	-- pointer incrementation that takes place while
	-- the machine is executing a program
	procedure Go_To(Label_Value : in ARCL_Label_Value);

	procedure Stack_Return_Address;
	procedure Recall_Return_Address;
	
private

	type Label_Cell;
	type Label_Cell_Ptr is access Label_Cell;
	type Label_Cell is 
		record
			Label : ARCL_Label_Value;
			Address : Integer;
			Next : Label_Cell_Ptr;
		end record;

	type Return_Address_Stack is array (Integer range 1 .. 128) of Integer;
	Address_Stack_Ptr : Integer := 0;
	Return_Addresses : Return_Address_Stack;
		
	-- The list of registered labels
	Label_List : Label_Cell_Ptr := null;
	
end Robotic_Virtual_Machine.Procedures_Labels;