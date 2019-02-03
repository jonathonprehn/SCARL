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
with Robotic_Virtual_Machine.Sensors_Actuators; use Robotic_Virtual_Machine.Sensors_Actuators;

with Ada.Command_Line; use Ada.Command_Line;
with Ada.Text_IO; use Ada.Text_IO;

-- This procedure takes an ARCL file as a program 
-- parameter and then executes it on the RVM

procedure ARCLVM is
begin
	if Argument_Count >= 1 then
		declare 
			Program_File_Name : String(1 .. Argument(1)'Last);
		begin
			Program_File_Name := Argument(1);
			
			-- We want to see if we have a pins option
			if Argument_Count = 2 then
				-- we do
				declare
					Pin_String : String(1 .. 6);
					Pin_Count : Integer := 10;
				begin
					Pin_String := Argument(2)(1 .. 6);
					if Pin_String = "-pins=" then
						Pin_Count := Integer'Value(Argument(2)(7 .. Argument(2)'Last));
					end if;
					Configure_Pin_Count(Pin_Count);
					Put_Line("Device configured for"
						& Integer'Image(Pin_Count) & " pins");
				end;
			else 
				-- we don't
				Configure_Pin_Count(10);
				Put_Line("Device configured for 10 pins");
			end if;
			
			Load_Program(Program_File_Name);
			Execute_Program;
		end;
	else
		Put_Line("Must pass in a single ARCL file to execute.");
	end if;
end ARCLVM;