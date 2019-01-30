with Robotic_Virtual_Machine; use Robotic_Virtual_Machine;
with Ada.Text_IO; use Ada.Text_IO;

package body Robotic_Virtual_Machine.Program is

	-- helper
	function Get_Line_Count_From_File(File_Name : in String) return Integer is
		Line_Count : Integer := 0;
		Line_Length : Integer := 0;
		Line : String(1 .. 40);
		The_File : File_Type;
	begin
		Open(The_File, In_File, File_Name);
		Set_Input(The_File);
		while not End_Of_File(The_File) loop
			Get_Line(Line, Line_Length);
			if Line_Length > 0 then
				Line_Count := Line_Count + 1;
			end if;
		end loop;
		Set_Input(Standard_Input);
		Close(The_File);
		return Line_Count;
	end Get_Line_Count_From_File;

	procedure Load_Program(File_Name : in String) is
		Line_Count : Integer := 0;
		Line_Length : Integer := 0;
		Line_Number : Integer := 1;
		Line : String(1 .. 40);
		Program_File : File_Type;
	begin
		-- First we want to count the number of non-empty lines
		-- so we know how many instructions the program is
		-- going to have
		
		Line_Count := Get_Line_Count_From_File(File_Name);
		-- Now we know how big to make the instructions array
		Loaded_Program := new ARCL_Program_Array(1 .. Line_Count);
		Loaded_Program.all := (others => (ARCL_ADD, null, null));
		
		-- Load instructions using Parse_ARCL_Instruction procedure
		Open(Program_File, In_File, File_Name);
		Set_Input(Program_File);
		while not End_Of_File(Program_File) loop
			Get_Line(Line, Line_Length);
			-- Put_Line("Parsing '" & Line(1 .. Line_Length) & "' (Line length" & Integer'Image(Line_Length) & ")");
			if Line_Length > 0 then
				-- Parse the lines
				Parse_ARCL_Instruction(Loaded_Program(Line_Number), Line(1 .. Line_Length));
				Line_Number := Line_Number + 1;
			end if;
		end loop;
		Set_Input(Standard_Input);
		Close(Program_File);
		
		Put_Line("Loaded ARCL program with" & Integer'Image(Line_Count) & " lines");
		
	end Load_Program;
	
	function Program_Instruction_Count return Integer is
	begin
		return Loaded_Program_Length;
	end Program_Instruction_Count;
	
	function Has_Program_Loaded return Boolean is
	begin
		return Program_Is_Loaded;
	end Has_Program_Loaded;
	
	procedure Execute_Program is
	begin
		-- Use program counter, execute with main package
		Instruction_Pointer := 1;
		Put_Line("Executing" & Integer'Image(Loaded_Program.all'Last) & " instructions");
		while Instruction_Pointer <= Loaded_Program.all'Last loop
			Invoke_Instruction(Loaded_Program(Instruction_Pointer));
			Instruction_Pointer := Instruction_Pointer + 1;
		end loop;
		
		-- Print machine status at the end of executing
		New_Line;
		Put_Line("Machine Status:");
		Print_RVM_State;
	end Execute_Program;

begin
	Program_Is_Loaded := False;
	Loaded_Program_Length := 0;
end Robotic_Virtual_Machine.Program;