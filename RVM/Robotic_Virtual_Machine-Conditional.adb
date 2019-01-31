
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