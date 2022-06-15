[BaseContainerProps(configRoot:true)]
class EL_SpawnpointConfig
{
	[Attribute("", UIWidgets.Object)]
	protected ref array<ref EL_Spawnpoint> m_spawnpoints;
	
	void ~EL_SpawnpointConfig()
	{
		m_spawnpoints = null;
	}
	
	ref array<ref EL_Spawnpoint> GetSpawnpoints(){
		return m_spawnpoints;
	}
}