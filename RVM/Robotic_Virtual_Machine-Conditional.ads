
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