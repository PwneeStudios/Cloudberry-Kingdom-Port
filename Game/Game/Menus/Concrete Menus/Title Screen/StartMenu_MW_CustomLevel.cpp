#include <small_header.h>
#include "Game/Menus/Concrete Menus/Title Screen/StartMenu_MW_CustomLevel.h"

#include "Game/Menus/Menu Components/MenuItem.h"
#include "Game/Menus/Concrete Menus/Title Screen/StartMenu.h"
#include "Game/Menus/Concrete Menus/Title Screen/StartMenu_MW_Backpanel.h"
#include "Game/Menus/Concrete Menus/Title Screen/Freeplay/CustomLevel_GUI.h"
#include "Game/Menus/Concrete Menus/Title Screen/TitleGame_MW.h"

#include "Core/Text/EzText.h"
#include "Game/Menus/Menu.h"

namespace CloudberryKingdom
{

	StartMenu_MW_CustomLevel::StartMenu_MW_CustomLevel( const boost::shared_ptr<TitleGameData_MW> &Title ) : CustomLevel_GUI() { }
	boost::shared_ptr<StartMenu_MW_CustomLevel> StartMenu_MW_CustomLevel::StartMenu_MW_CustomLevel_Construct( const boost::shared_ptr<TitleGameData_MW> &Title )
	{
		CustomLevel_GUI::CustomLevel_GUI_Construct();

		this->Title = Title;

		return boost::static_pointer_cast<StartMenu_MW_CustomLevel>( shared_from_this() );
	}

	void StartMenu_MW_CustomLevel::SlideIn( int Frames )
	{
		Title->BackPanel->SetState( StartMenu_MW_Backpanel::State_SCENE_BLUR_DARK );

		//base.SlideIn(0);
		CustomLevel_GUI::SlideIn( Frames );
	}

	void StartMenu_MW_CustomLevel::SlideOut( PresetPos Preset, int Frames )
	{
		//base.SlideOut(Preset, 0);
		CustomLevel_GUI::SlideOut( Preset, Frames );
	}

	void StartMenu_MW_CustomLevel::SetItemProperties( const boost::shared_ptr<MenuItem> &item )
	{
		CustomLevel_GUI::SetItemProperties( item );

		StartMenu::SetItemProperties_Red( item );

		if ( item->MyText == 0 )
			return;
		item->MySelectedText->Shadow = item->MyText->Shadow = false;
	}

	void StartMenu_MW_CustomLevel::Init()
	{
		 CustomLevel_GUI::Init();

		CallDelay = 0;
		ReturnToCallerDelay = 0;
		//ReturnToCallerDelay = 10;
		MyMenu->OnB = boost::make_shared<MenuReturnToCallerLambdaFunc>( boost::static_pointer_cast<GUI_Panel>( shared_from_this() ) );
	}

	void StartMenu_MW_CustomLevel::ReturnToCaller()
	{
		//Active = false;
		//SlideOutLength = 0;
		//Hide();
		//MyGame.PartialFade_InAndOut(0, .5f, 2, 2, base.ReturnToCaller);

		SlideOutLength = 0;
		CustomLevel_GUI::ReturnToCaller();
	}
}
