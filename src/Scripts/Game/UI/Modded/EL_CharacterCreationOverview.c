class EL_CharacterCreationOverviewClass: ChimeraMenuBase
{
	private IEntity m_currentEntity;
	private IEntity m_char;
	private ItemPreviewWidget m_renderPreview;
	private TextWidget m_bodyText;
	private Widget m_wRoot;
	private ButtonWidget m_saveBtn;
	private ButtonWidget m_bodySwitchForwardBtn;
	private SCR_ButtonComponent m_bodySwitchForwardHandler;
	private SCR_ButtonComponent m_bodySwitchBackwardHandler;
	private ButtonWidget m_bodySwitchBackwardBtn;
	private SCR_ButtonComponent m_saveCharHandler;
	private EditBoxWidget m_firstNameWidget;
	private EditBoxWidget m_lastNameWidget
	private int m_currentResourceIndex;
	private ref array<ref Resource> m_resources = new array<ref Resource>;
	
	void EL_CharacterSelectionOverviewClass()
	{
	}
	
	override void OnMenuOpen()
	{
		GetWidgets();	
		AssignEvents();
		
		if (!m_renderPreview)
			return;
		
		LoadResources();
		
		m_bodyText.SetText("0");	

		m_currentEntity = GetGame().SpawnEntityPrefabLocal(m_resources[0], null, null);
		if (!m_currentEntity)
			return;

		ItemPreviewManagerEntity manager = GetGame().GetItemPreviewManager();
		if (!manager)
			return;


		manager.SetPreviewItem(m_renderPreview, m_currentEntity);
	}
	
	private void GetWidgets()
	{
		m_wRoot = GetRootWidget();
		m_saveBtn = ButtonWidget.Cast(m_wRoot.FindAnyWidget("PropertyLayout0").FindAnyWidget("PropertyLayoutFrame").FindAnyWidget("PropertyLayout1").FindAnyWidget("SaveButton"));
		m_saveCharHandler = SCR_ButtonComponent.Cast(m_saveBtn.FindHandler(SCR_ButtonComponent));	
		m_renderPreview = ItemPreviewWidget.Cast(m_wRoot.FindAnyWidget("VerticalLayout1").FindAnyWidget("HorizontalLayout0").FindAnyWidget("ItemPreview0"));
		m_bodySwitchForwardBtn = ButtonWidget.Cast(m_wRoot.FindAnyWidget("PropertyLayout0").FindAnyWidget("PropertyLayoutFrame").FindAnyWidget("PropertyLayout1").FindAnyWidget("BodyLayout").FindAnyWidget("BodySwitchForward"));
		m_bodySwitchForwardHandler = SCR_ButtonComponent.Cast(m_bodySwitchForwardBtn.FindHandler(SCR_ButtonComponent));	
		m_bodySwitchBackwardBtn = ButtonWidget.Cast(m_wRoot.FindAnyWidget("PropertyLayout0").FindAnyWidget("PropertyLayoutFrame").FindAnyWidget("PropertyLayout1").FindAnyWidget("BodyLayout").FindAnyWidget("BodySwitchBackward"));
		m_bodySwitchBackwardHandler = SCR_ButtonComponent.Cast(m_bodySwitchBackwardBtn.FindHandler(SCR_ButtonComponent));	
		m_bodyText = TextWidget.Cast(m_wRoot.FindAnyWidget("PropertyLayout0").FindAnyWidget("PropertyLayoutFrame").FindAnyWidget("PropertyLayout1").FindAnyWidget("BodyLayout").FindAnyWidget("SelectedBodyText"));
		m_firstNameWidget = EditBoxWidget.Cast(m_wRoot.FindAnyWidget("PropertyLayout0").FindAnyWidget("PropertyLayoutFrame").FindAnyWidget("PropertyLayout1").FindAnyWidget("HorizontalLayout0").FindAnyWidget("EditBox0"));
		m_lastNameWidget = EditBoxWidget.Cast(m_wRoot.FindAnyWidget("PropertyLayout0").FindAnyWidget("PropertyLayoutFrame").FindAnyWidget("PropertyLayout1").FindAnyWidget("HorizontalLayout1").FindAnyWidget("EditBox0"));
	}
	
	private void AssignEvents()
	{
		m_bodySwitchForwardHandler.m_OnClicked.Insert(OnSwitchBodyForward);
		m_bodySwitchBackwardHandler.m_OnClicked.Insert(OnSwitchBodyBackward);
		m_saveCharHandler.m_OnClicked.Insert(SaveCharacter);
	}
	
	private void OnSwitchBodyForward()
	{	
		LoadResources();
		if(m_currentResourceIndex < m_resources.Count() - 1){
			m_currentResourceIndex++;
			SwitchBody(m_currentResourceIndex);
		}		
	}
	
	private void OnSwitchBodyBackward()
	{					
		LoadResources();
		if(m_currentResourceIndex > 0){
			m_currentResourceIndex--;
			SwitchBody(m_currentResourceIndex);
		}		
	}
	
	private void SwitchBody(int index)
	{	
		LoadResources();
		m_bodyText.SetText(index.ToString());	
		m_currentEntity = GetGame().SpawnEntityPrefabLocal(m_resources[index], null, null);
		
		RerenderItemPreview(m_currentEntity);
	}
	
	private void RerenderItemPreview(IEntity previewEntity)
	{
		ItemPreviewManagerEntity manager = GetGame().GetItemPreviewManager();
		if (!manager)
			return;


		manager.SetPreviewItem(m_renderPreview, previewEntity);
	}
	
	private void SaveCharacter()
	{
		LoadResources();
		
		EL_CharacterSelectionOverviewClass menu = EL_CharacterSelectionOverviewClass.Cast(CloseMenu());
		
		string fullName = m_firstNameWidget.GetText() + " " + m_lastNameWidget.GetText();
		
		menu.LoadCharacters(m_resources[m_currentResourceIndex], fullName);
	}
	
	private MenuBase CloseMenu()
	{
		MenuManager pMenuManager = GetGame().GetMenuManager();
		if (!pMenuManager)
			return null;
		
		pMenuManager.CloseMenu(this);

		return pMenuManager.OpenMenu(ChimeraMenuPreset.CharacterSelectionOverviewMenu);
	}
	
	private void LoadResources()
	{	
		if(m_resources.Count() > 0)
		{
			m_resources.Clear();
		}
		
		BaseGameMode gameMode = GetGame().GetGameMode();
		if (!gameMode)
			return;
		
		EL_CharacterPresetConfigComponent configComp = EL_CharacterPresetConfigComponent.Cast(gameMode.FindComponent(EL_CharacterPresetConfigComponent));
		if (!configComp)
			return;
		
		ResourceName path = configComp.GetConfigPath();
		if (path.IsEmpty())
			return;
			
		Resource container = BaseContainerTools.LoadContainer(path);
		if (!container)
			return;
					
		EL_CharacterPresetConfig config = EL_CharacterPresetConfig.Cast( BaseContainerTools.CreateInstanceFromContainer( container.GetResource().ToBaseContainer() ) );
		foreach(ResourceName name : config.GetCharacterPrefabs())
		{
			Resource resource = Resource.Load(name);
			m_resources.Insert(resource);
		}
	}
}

modded enum ChimeraMenuPreset {
	CharacterCreationOverviewMenu
}