//------------------------------------------------------------------------------------------------
modded class SCR_RespawnSystemComponentClass: RespawnSystemComponentClass
{
};

//! Scripted implementation that handles spawning and respawning of players.
//! Should be attached to a GameMode entity.
[ComponentEditorProps(icon: HYBRID_COMPONENT_ICON)]
modded class SCR_RespawnSystemComponent : RespawnSystemComponent
{
	override static MenuBase OpenRespawnMenu()
	{
		MenuManager pMenuManager = GetGame().GetMenuManager();
		if (!pMenuManager)
			return null;

		return pMenuManager.OpenMenu(ChimeraMenuPreset.CharacterSelectionOverviewMenu);
	}

	//------------------------------------------------------------------------------------------------
	//! Close all menus operated by Respawn System
	override static void CloseRespawnMenu()
	{
		MenuManager pMenuManager = GetGame().GetMenuManager();
		if (!pMenuManager)
			return;

		MenuBase menu = pMenuManager.FindMenuByPreset(ChimeraMenuPreset.CharacterSelectionOverviewMenu);
		if (menu)
			pMenuManager.CloseMenu(menu);
	}

	//------------------------------------------------------------------------------------------------
	//! Simple getter for other
	override static bool IsRespawnMenuOpened()
	{
		MenuManager pMenuManager = GetGame().GetMenuManager();
		if (!pMenuManager)
			return false;

		return (pMenuManager.FindMenuByPreset(ChimeraMenuPreset.CharacterSelectionOverviewMenu) != null);
	}
};