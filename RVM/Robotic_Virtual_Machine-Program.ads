
with Robotic_Virtual_Machine; use Robotic_Virtual_Machine;

package Robotic_Virtual_Machine.Program is

	-- Variables to use 
	type ARCL_Program_Array is array (Integer range <>) of ARCL_Instruction;
	type ARCL_Program is access ARCL_Program_Array;

	procedure Load_Program(File_Name : in String);
	function Program_Instruction_Count return Integer;
	function Has_Program_Loaded return Boolean;
	procedure Execute_Program;
	
private
	
	Loaded_Program : ARCL_Program;
	Loaded_Program_Length : Integer;
	Program_Is_Loaded : Boolean;
	Instruction_Pointer : Integer;
		
end Robotic_Virtual_Machine.Program;