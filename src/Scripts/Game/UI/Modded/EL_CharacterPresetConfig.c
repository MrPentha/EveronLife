[BaseContainerProps(configRoot: true)]
class EL_CharacterPresetConfig : SCR_GameCoreBase
{
	[Attribute(desc: "EL Character Prefab", params: "et")]
	ref array<ref ResourceName> m_characters;
	
	void ~EL_CharacterPresetConfig()
	{
		m_characters = null;
	}
	
	ref array<ref ResourceName> GetCharacterPrefabs(){
		return m_characters;
	}
}