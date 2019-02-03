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

package Robotic_Virtual_Machine.Program is

	-- Variables to use 
	type ARCL_Program_Array is array (Integer range <>) of ARCL_Instruction;
	type ARCL_Program is access ARCL_Program_Array;

	procedure Load_Program(File_Name : in String);
	function Program_Instruction_Count return Integer;
	function Has_Program_Loaded return Boolean;
	procedure Execute_Program;
	
	-- public access to the instruction pointer
	Instruction_Pointer : Integer := 0;
	
private
	
	Loaded_Program : ARCL_Program;
	Loaded_Program_Length : Integer;
	Program_Is_Loaded : Boolean;
		
end Robotic_Virtual_Machine.Program;