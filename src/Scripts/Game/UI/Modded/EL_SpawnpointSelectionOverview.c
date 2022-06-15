class EL_SpawnpointSelectionOverviewClass : ChimeraMenuBase
{
	private Widget m_wRoot;
	private ButtonWidget m_spawnButton;
	private XComboBoxWidget m_spawnBox;
	private SCR_ButtonComponent m_spawnButtonHandler;
	private ref array<ref EL_Spawnpoint> m_spawnpoints;
	
	override void OnMenuOpen()
	{
		if(!GetWidgets())
			return;
		
		AssignEvents();
		
		m_spawnpoints = GetSpawnpointsFromConfig();		
		if(!m_spawnpoints)
			return;
		
		foreach(EL_Spawnpoint spawnpoint : m_spawnpoints)
		{
			m_spawnBox.AddItem(spawnpoint.GetDisplayName());
		}	
	}
	
	private bool GetWidgets()
	{
		m_wRoot = GetRootWidget();
		if(!m_wRoot)
			return false;
		
		m_spawnButton = ButtonWidget.Cast(m_wRoot.FindAnyWidget("VerticalLayout1").FindAnyWidget("Button0"));		
		m_spawnBox = XComboBoxWidget.Cast(m_wRoot.FindAnyWidget("VerticalLayout1").FindAnyWidget("XComboBox0"));
		m_spawnButtonHandler = SCR_ButtonComponent.Cast(m_spawnButton.FindHandler(SCR_ButtonComponent));
		if(!m_spawnBox || !m_spawnButton || !m_spawnButtonHandler)
			return false;
		
		return true;
	}
	
	private void AssignEvents()
	{
		m_spawnButtonHandler.m_OnClicked.Insert(OnSpawnClicked);
	}
	
	private void OnSpawnClicked()
	{
		EL_Spawnpoint selectedSpawnpoint = m_spawnpoints[m_spawnBox.GetCurrentItem()];
		if(!selectedSpawnpoint)
			return;
		
		SpawnPlayer(selectedSpawnpoint.GetPosition(), selectedSpawnpoint.GetRotation());
		CloseAllMenus();
	}
	
	private void CloseAllMenus()
	{
		MenuManager pMenuManager = GetGame().GetMenuManager();
		if (!pMenuManager)
			return;
		pMenuManager.CloseAllMenus();
	}
	
	void SpawnPlayer(vector pos, vector rot)
	{	
		BaseGameMode gameMode = GetGame().GetGameMode();
		if (!gameMode)
			return;
		
		EL_CharacterPresetConfigComponent configComp = EL_CharacterPresetConfigComponent.Cast(gameMode.FindComponent(EL_CharacterPresetConfigComponent));
		if (!configComp)
			return;
		
		SCR_RespawnSystemComponent respawner = SCR_RespawnSystemComponent.Cast(GetGame().GetGameMode().FindComponent(SCR_RespawnSystemComponent));
		
		int playerId = GetGame().GetPlayerController().GetPlayerId();
		int factionIndex = GetGame().GetFactionManager().GetFactionByKey("LIFE");
		
		respawner.DoSetPlayerFaction(playerId, factionIndex);
		GameEntity player = GameEntity.Cast(respawner.CustomRespawn(playerId, configComp.GetSelectedCharacter().GetResource().GetResourceName(), pos, rot));
	}
	
	private ref array<ref EL_Spawnpoint> GetSpawnpointsFromConfig()
	{
		BaseGameMode gameMode = GetGame().GetGameMode();
		if (!gameMode)
			return null;
		
		EL_SpawnpointConfigComponent configComp = EL_SpawnpointConfigComponent.Cast(gameMode.FindComponent(EL_SpawnpointConfigComponent));
		if (!configComp)
			return null;
		
		ResourceName path = configComp.GetConfigPath();
		if (path.IsEmpty())
			return null;
			
		Resource container = BaseContainerTools.LoadContainer(path);
		if (!container)
			return null;
					
		EL_SpawnpointConfig config = EL_SpawnpointConfig.Cast( BaseContainerTools.CreateInstanceFromContainer( container.GetResource().ToBaseContainer() ) );
		
		return config.GetSpawnpoints();
	}
}

modded enum ChimeraMenuPreset {
	SpawnpointSelectionOverviewMenu
}