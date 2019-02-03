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

package body Robotic_Virtual_Machine.Conditional is

	procedure Compare(Value_1, Value_2 : ARCL_Register_Value) is
begin
		-- Do a whole bunch of comparison stuff
		Equals_Flag := Value_1 = Value_2;
		Less_Flag := Value_1 < Value_2;
		Greater_Flag := Value_1 > Value_2;
		And_Flag := (Value_1 /= 0) and (Value_2 /= 0);
		Or_Flag := (Value_1 /= 0) or (Value_2 /= 0);
	end Compare;
	
	function Get_Equals_Flag return Boolean is
	begin
		return Equals_Flag;
	end Get_Equals_Flag;
	
	function Get_Less_Flag return Boolean is
	begin
		return Less_Flag;
	end Get_Less_Flag;

	function Get_Greater_Flag return Boolean is
	begin
		return Greater_Flag;
	end Get_Greater_Flag;
	
	function Get_And_Flag return Boolean is
	begin
		return And_Flag;
	end Get_And_Flag;
	
	function Get_Or_Flag return Boolean is
	begin
		return Or_Flag;
	end Get_Or_Flag;
	
end Robotic_Virtual_Machine.Conditional;