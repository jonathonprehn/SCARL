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



with Ada.Text_IO;
with Robotic_Virtual_Machine; use Robotic_Virtual_Machine;
with Robotic_Virtual_Machine.Program; use Robotic_Virtual_Machine.Program;

package body Robotic_Virtual_Machine.Procedures_Labels is

	-- Registers the current instruction as the 
	-- label name. Usage should be constrained so 
	-- that only LABEL and PROC instructions are
	-- registers with label names. Goes off the
	-- current state of the machine
	procedure Register_Label(Label_Value : in ARCL_Label_Value; Address : in Integer) is
	begin
		if Label_List = null then
			Label_List := new Label_Cell'(
				Label => Label_Value,
				Address => Address,
				Next => null
			);
		else
			declare
				Current : Label_Cell_Ptr := Label_List;
			begin
				while Current.Next /= null loop
					Current := Current.Next;
				end loop;
				Current.Next := new Label_Cell'(
					Label => Label_Value,
					Address => Address,
					Next => null
				);
			end;
		end if;
		-- Ada.Text_IO.Put_Line("Registered label '" & Label_Value.all & "' for address " & Integer'Image(Address));
	end Register_Label;
	
	-- Sets the instruction pointer to 
	-- be pointing at the PROC or LABEL instruction
	-- with the given label value. This is designed
	-- to be called before the subsequent instruction
	-- pointer incrementation that takes place while
	-- the machine is executing a program
	procedure Go_To(Label_Value : in ARCL_Label_Value) is
		Current : Label_Cell_Ptr := Label_List;
		Found_Label : Boolean := False;
	begin
		while Current /= null loop
			if Current.Label.all = Label_Value.all then
				Instruction_Pointer := Current.Address;
				Found_Label := True;
				exit; -- this loop
			end if;
			Current := Current.Next;
		end loop;
		-- Nothing happens if the label is not found
		if not Found_Label then
			Ada.Text_IO.Put_Line("Could not find label '" & Label_Value.all & "'");
		end if;
	end Go_To;
	
	procedure Stack_Return_Address is
	begin
		Address_Stack_Ptr := Address_Stack_Ptr + 1;
		Return_Addresses(Address_Stack_Ptr) := Instruction_Pointer;
	end Stack_Return_Address;
	
	procedure Recall_Return_Address is
	begin
		-- Ada.Text_IO.Put_Line("Getting address at stack location" & Integer'Image(Address_Stack_Ptr));
		Instruction_Pointer := Return_Addresses(Address_Stack_Ptr);
		Address_Stack_Ptr := Address_Stack_Ptr - 1;
	end Recall_Return_Address;
	
end Robotic_Virtual_Machine.Procedures_Labels;