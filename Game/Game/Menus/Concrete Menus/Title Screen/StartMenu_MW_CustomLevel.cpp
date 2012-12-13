#include <global_header.h>

namespace CloudberryKingdom
{

	StartMenu_MW_CustomLevel::StartMenu_MW_CustomLevel( const std::shared_ptr<TitleGameData_MW> &Title ) : CustomLevel_GUI() { }
	std::shared_ptr<StartMenu_MW_CustomLevel> StartMenu_MW_CustomLevel::StartMenu_MW_CustomLevel_Construct( const std::shared_ptr<TitleGameData_MW> &Title )
	{
		CustomLevel_GUI::CustomLevel_GUI_Construct();

		this->Title = Title;

		return std::static_pointer_cast<StartMenu_MW_CustomLevel>( shared_from_this() );
	}

	void StartMenu_MW_CustomLevel::SlideIn( int Frames )
	{
		Title->BackPanel->SetState( StartMenu_MW_Backpanel::State_SCENE_BLUR_DARK );

		//base.SlideIn(0);
		CustomLevel_GUI::SlideIn( Frames );
	}

	void StartMenu_MW_CustomLevel::SlideOut( const PresetPos &Preset, int Frames )
	{
		//base.SlideOut(Preset, 0);
		CustomLevel_GUI::SlideOut( Preset, Frames );
	}

	void StartMenu_MW_CustomLevel::SetItemProperties( const std::shared_ptr<MenuItem> &item )
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
		MyMenu->OnB = std::make_shared<MenuReturnToCallerLambdaFunc>( std::static_pointer_cast<GUI_Panel>( shared_from_this() ) );
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
