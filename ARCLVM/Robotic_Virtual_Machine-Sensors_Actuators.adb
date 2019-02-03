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

-- A package for the configuration of the input/output
-- characteristics of this software device. This is
-- mostly for pretend but will be essential for 
-- implementing an RVM that interfaces directly with
-- some kind of physical device

package body Robotic_Virtual_Machine.Sensors_Actuators is
	
	procedure Configure_Pin_Count(Pin_Count : in Natural) is
	begin
		Pins := new Pins_Set_Array(1 .. Pin_Count);
		Pins_Mode := new Pins_Configuration_Array(1 .. Pin_Count);
	end Configure_Pin_Count;
	
	procedure Configure_Pin(Pin : in Natural; Mode : Pin_Mode) is
	begin
		Pins_Mode(Pin) := Mode;
	end Configure_Pin;
	
	procedure Read_Pin(Pin : in Natural; Value : out ARCL_Register_Value) is
	begin
		if Pins_Mode(Pin) = Input then
			Value := Pins(Pin);
		else
			Value := -1;
		end if;
	end Read_Pin;
	
	procedure Write_Pin(Pin : in Natural; Value : in ARCL_Register_Value) is
	begin
		if Pins_Mode(Pin) = Output then
			Pins(Pin) := Value;
		else
			null;
		end if;
	end Write_Pin;
	
end Robotic_Virtual_Machine.Sensors_Actuators;