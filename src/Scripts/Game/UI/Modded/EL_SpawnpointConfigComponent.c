[ComponentEditorProps(category: "GameScripted/GameMode/Components", description: "Component for character prefab config selection")]
class EL_SpawnpointConfigComponentClass : ScriptComponentClass
{}

class EL_SpawnpointConfigComponent : ScriptComponent
{
	[Attribute("", UIWidgets.ResourceNamePicker, desc: "EL_Spawnpoint.conf Path", params: "conf")]
	protected ResourceName m_sConfigPath;
	
	ResourceName GetConfigPath()
	{
		return m_sConfigPath;
	}
}