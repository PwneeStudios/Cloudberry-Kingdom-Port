#ifndef STARTMENU_MW_CUSTOMLEVEL
#define STARTMENU_MW_CUSTOMLEVEL

#include <small_header.h>

//#include "Game/Menus/Menu Components/MenuItem.h"
//#include "Game/Menus/Concrete Menus/Title Screen/StartMenu.h"
//#include "Game/Menus/Concrete Menus/Title Screen/StartMenu_MW_Backpanel.h"
#include "Game/Menus/Concrete Menus/Title Screen/Freeplay/CustomLevel_GUI.h"
//#include "Game/Menus/Concrete Menus/Title Screen/TitleGame_MW.h"


namespace CloudberryKingdom
{
	struct StartMenu_MW_CustomLevel : public CustomLevel_GUI
	{

		virtual ~StartMenu_MW_CustomLevel()
		{
#ifdef BOOST_BIN
			OnDestructor( "StartMenu_MW_CustomLevel" );
#endif
		}


		using CustomLevel_GUI::SlideOut;
		using CustomLevel_GUI::SlideIn;
		using CustomLevel_GUI::Call;

		boost::shared_ptr<TitleGameData_MW> Title;
		StartMenu_MW_CustomLevel( const boost::shared_ptr<TitleGameData_MW> &Title );
		boost::shared_ptr<StartMenu_MW_CustomLevel> StartMenu_MW_CustomLevel_Construct( const boost::shared_ptr<TitleGameData_MW> &Title );

		virtual void SlideIn( int Frames );

		virtual void SlideOut( PresetPos Preset, int Frames );

	
		virtual void SetItemProperties( const boost::shared_ptr<MenuItem> &item );

	
		virtual void Init();

		virtual void ReturnToCaller();
	};
}


#endif	//#ifndef STARTMENU_MW_CUSTOMLEVEL
