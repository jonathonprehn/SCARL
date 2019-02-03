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

package Robotic_Virtual_Machine.Conditional is

	procedure Compare(Value_1, Value_2 : ARCL_Register_Value);
	function Get_Equals_Flag return Boolean;
	function Get_Less_Flag return Boolean;
	function Get_Greater_Flag return Boolean;
	function Get_And_Flag return Boolean;
	function Get_Or_Flag return Boolean;

private
	
	-- Conditional flags
	Equals_Flag : Boolean := False;
	Less_Flag : Boolean := False;
	Greater_Flag : Boolean := False;
	And_Flag : Boolean := False;
	Or_Flag : Boolean := False;
	
end Robotic_Virtual_Machine.Conditional;