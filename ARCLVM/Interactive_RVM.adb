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
with Ada.Text_IO; use Ada.Text_IO;

procedure Interactive_RVM is
	Instruction : ARCL_Instruction;
	Line : String(1 .. 80);
	Last : Natural;
	Running : Boolean;
begin
	Running := True;
	
	Put_Line("Welcome to the Interactive RVM. Type "
		& "commands here and press ENTER to submit."
		& " Type 'quit' to quit. Type 'help' for "
		& "more commands.");
	New_Line;
	Put(">");
	
	Main_Loop:
	while Running loop
		Get_Line(Line, Last);
		-- Put_Line(Line(1  .. Last));
		if Line(1 .. Last) = "quit" then
			Running := False;
			Put_Line("Goodbye.");
		elsif Line(1 .. Last) = "help" then
			Put_Line("quit -- quit the interactive RVM");
			Put_Line("registers -- see the status of the registers");
			Put_Line("stack -- see the stack");
			Put(">");
		elsif Line(1 .. Last) = "registers" then
			Print_RVM_State;
			Put(">");
		elsif Line(1 .. Last) = "stack" then
			Print_RVM_Stack;
			Put(">");
		else
			Parse_ARCL_Instruction(Instruction, Line(1 .. Last));
			Invoke_Instruction(Instruction);
			Put(">");
		end if;
	end loop Main_Loop;
end Interactive_RVM;