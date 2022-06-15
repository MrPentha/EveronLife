class EL_CharacterSelectionOverviewClass: ChimeraMenuBase
{
	private Widget m_wRoot;
	private HorizontalLayoutWidget m_layout;
	private TextWidget m_counterText;
	private ButtonWidget m_addCharacterBtn;
	private ButtonWidget m_joinServerBtn;
	private int m_characterCount = 0;
	private ref Resource m_selectedCharacter;
	
	void EL_CharacterSelectionOverviewClass()
	{
	}
	
	override void OnMenuOpen()
	{
		m_wRoot = GetRootWidget();
		m_counterText = TextWidget.Cast(m_wRoot.FindAnyWidget("HorizontalLayout3").FindAnyWidget("Text0"));
		m_addCharacterBtn = ButtonWidget.Cast(m_wRoot.FindAnyWidget("HorizontalLayout0").FindAnyWidget("AddCharacterButton2"));
		m_joinServerBtn = ButtonWidget.Cast(m_wRoot.FindAnyWidget("HorizontalLayout2").FindAnyWidget("JoinGameButton"));

		m_counterText.SetText(m_characterCount.ToString() + "/3");
		
		SCR_ButtonComponent addCharHandler = SCR_ButtonComponent.Cast(m_addCharacterBtn.FindHandler(SCR_ButtonComponent));
		SCR_ButtonComponent joinServerHandler = SCR_ButtonComponent.Cast(m_joinServerBtn.FindHandler(SCR_ButtonComponent));
		
		addCharHandler.m_OnClicked.Insert(OnAddCharacterClicked);
		joinServerHandler.m_OnClicked.Insert(OnJoinServerClicked);
		
		CreateCharacterBoxes();
	}
	
	void OnAddCharacterClicked()
	{
		OpenCharacterCreationMenu();
	}
	
	
	//Todo::Laden der Charaktere
	void LoadCharacters(Resource resource, string name)
	{			
		ItemPreviewWidget renderPreview = ItemPreviewWidget.Cast(m_wRoot.FindAnyWidget("VerticalLayout0").FindAnyWidget("HorizontalLayout0").FindAnyWidget("Character0").FindAnyWidget("SizeLayout0").FindAnyWidget("Overlay0").FindAnyWidget("ItemPreview0"));
		TextWidget nameText = TextWidget.Cast(m_wRoot.FindAnyWidget("VerticalLayout0").FindAnyWidget("HorizontalLayout0").FindAnyWidget("Character0").FindAnyWidget("SizeLayout0").FindAnyWidget("Overlay0").FindAnyWidget("Text0"));
		ButtonWidget char1 = ButtonWidget.Cast(m_wRoot.FindAnyWidget("VerticalLayout0").FindAnyWidget("HorizontalLayout0").FindAnyWidget("Character0"));
		PanelWidget namePanel = PanelWidget.Cast(m_wRoot.FindAnyWidget("VerticalLayout0").FindAnyWidget("HorizontalLayout0").FindAnyWidget("Character0").FindAnyWidget("SizeLayout0").FindAnyWidget("Overlay0").FindAnyWidget("Panel0"));
		
		
		nameText.SetText(name);
		char1.SetOpacity(1);
		char1.SetEnabled(true);
		namePanel.SetVisible(true);
		
		if (!renderPreview)
			return;
		
		IEntity currentEntity = GetGame().SpawnEntityPrefabLocal(resource, null, null);
		if (!currentEntity)
			return;

		ItemPreviewManagerEntity manager = GetGame().GetItemPreviewManager();
		
		if (!manager)
			return;
		m_selectedCharacter = resource;
	
		manager.SetPreviewItem(renderPreview, currentEntity);
		m_characterCount++;
		m_counterText.SetText(m_characterCount.ToString() + "/3");
	}
	
	MenuBase OpenCharacterCreationMenu()
	{
		if(m_characterCount < 4){
			m_characterCount++;
			m_counterText.SetText(m_characterCount.ToString() + "/3");
		}
		
		MenuManager pMenuManager = GetGame().GetMenuManager();
		if (!pMenuManager)
			return null;

		return pMenuManager.OpenMenu(ChimeraMenuPreset.CharacterCreationOverviewMenu);
	}
	
	void CreateCharacterBoxes()
	{
		for(int x = 0; x < m_characterCount; x++)
		{
			m_characterCount++;
		}
	}
	
	void OnJoinServerClicked()
	{
		//SpawnPlayer();
		MenuManager pMenuManager = GetGame().GetMenuManager();
		if (!pMenuManager)
			return;

		SetSelectedCharacter();
		//pMenuManager.CloseAllMenus();
		pMenuManager.OpenMenu(ChimeraMenuPreset.SpawnpointSelectionOverviewMenu)
	}
	
	void SetSelectedCharacter()
	{
		BaseGameMode gameMode = GetGame().GetGameMode();
		if (!gameMode)
			return;
		
		EL_CharacterPresetConfigComponent configComp = EL_CharacterPresetConfigComponent.Cast(gameMode.FindComponent(EL_CharacterPresetConfigComponent));
		if (!configComp)
			return;
		
		configComp.SetSelectedCharacter(m_selectedCharacter);
	}
	
	void SpawnPlayer()
	{
		vector pos = {0,0,0};
		vector rot = {0,0,0};
		
		SCR_RespawnSystemComponent respawner = SCR_RespawnSystemComponent.Cast(GetGame().GetGameMode().FindComponent(SCR_RespawnSystemComponent));
		
		int playerId = GetGame().GetPlayerController().GetPlayerId();
		int factionIndex = GetGame().GetFactionManager().GetFactionByKey("LIFE");
		
		respawner.DoSetPlayerFaction(playerId, factionIndex);
		array<SCR_SpawnPoint> spawnpointsForFaction = SCR_SpawnPoint.GetSpawnPointsForFaction("LIFE");
		spawnpointsForFaction[0].GetPositionAndRotation(pos,rot);
		GameEntity player = GameEntity.Cast(respawner.CustomRespawn(playerId, m_selectedCharacter.GetResource().GetResourceName(), pos, rot));
	}
}

modded enum ChimeraMenuPreset {
	CharacterSelectionOverviewMenu
}