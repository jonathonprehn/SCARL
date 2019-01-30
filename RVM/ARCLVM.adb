
with Robotic_Virtual_Machine; use Robotic_Virtual_Machine;
with Robotic_Virtual_Machine.Program; use Robotic_Virtual_Machine.Program; 

with Ada.Command_Line; use Ada.Command_Line;
with Ada.Text_IO; use Ada.Text_IO;

-- This procedure takes an ARCL file as a program 
-- parameter and then executes it on the RVM

procedure ARCLVM is
begin
	if Argument_Count = 1 then
		declare 
			Program_File_Name : String(1 .. Argument(1)'Last);
		begin
			Program_File_Name := Argument(1);
			Load_Program(Program_File_Name);
			Execute_Program;
		end;
	else
		Put_Line("Must pass in a single ARCL file to execute.");
	end if;
end ARCLVM;