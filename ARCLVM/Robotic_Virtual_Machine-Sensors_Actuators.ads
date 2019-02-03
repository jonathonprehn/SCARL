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

package Robotic_Virtual_Machine.Sensors_Actuators is
	
	type Pin_Mode is (Input, Output);
	
	procedure Configure_Pin_Count(Pin_Count : in Natural);
	procedure Configure_Pin(Pin : in Natural; Mode : Pin_Mode);
	procedure Read_Pin(Pin : in Natural; Value : out ARCL_Register_Value);
	procedure Write_Pin(Pin : in Natural; Value : in ARCL_Register_Value);
	
private
	
	type Pins_Set_Array is array (Integer range <>) of ARCL_Register_Value;
	type Pins_Configuration_Array is array (Integer range <>) of Pin_Mode;
	type Pins_Set is access Pins_Set_Array;
	type Pins_Configuration is access Pins_Configuration_Array;
	Pins : Pins_Set := null;
	Pins_Mode : Pins_Configuration := null;
	
end Robotic_Virtual_Machine.Sensors_Actuators;