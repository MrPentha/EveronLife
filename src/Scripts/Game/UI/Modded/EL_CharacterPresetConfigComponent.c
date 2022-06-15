[ComponentEditorProps(category: "GameScripted/GameMode/Components", description: "Component for character prefab config selection")]
class EL_CharacterPresetConfigComponentClass : ScriptComponentClass
{}

class EL_CharacterPresetConfigComponent : ScriptComponent
{
	[Attribute("", UIWidgets.ResourceNamePicker, desc: "EL_CharacterPrefab config", params: "conf")]
	protected ResourceName m_sConfigPath;

	private Resource m_selectedCharacter;
	
	ResourceName GetConfigPath()
	{
		return m_sConfigPath;
	}
	
	void SetSelectedCharacter(Resource char)
	{
		m_selectedCharacter = char;
	}
	
	Resource GetSelectedCharacter()
	{
		return m_selectedCharacter;
	}
}