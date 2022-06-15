[BaseContainerProps(), SCR_BaseContainerCustomTitleResourceName("m_displayName", true)]
class EL_Spawnpoint 
{
	[Attribute(desc: "Name", UIWidgets.EditBox)]
	protected string m_displayName;
	
	[Attribute(desc: "Position", UIWidgets.Coords)]
	protected vector m_position;
	
	[Attribute(desc: "Rotation", UIWidgets.Coords)]
	protected vector m_rotation;
	
	string GetDisplayName()
	{
		return m_displayName;
	}
	
	vector GetPosition()
	{
		return m_position;
	}
	
	vector GetRotation()
	{
		return m_rotation;
	}
	
	void EL_Spawnpoint()
	{
		
	}
}