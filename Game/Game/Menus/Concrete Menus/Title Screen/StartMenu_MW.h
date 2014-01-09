#ifndef STARTMENU_MW
#define STARTMENU_MW

#include <small_header.h>

//#include "Core/Graphics/Draw/Quads/QuadClass.h"
//#include "Game/Localization.h"
//#include "Game/CloudberryKingdom/CloudberryKingdom.CloudberryKingdomGame.h"
//#include "Core/Text/EzText.h"
//#include "Core/Tools/ColorHelper.h"
//#include "Game/Objects/Game Objects/GameObjects/GUI_Panel.h"
//#include "Game/Menus/Menu Components/MenuItem.h"
#include "Game/Menus/Concrete Menus/Title Screen/StartMenu.h"
//#include "Game/Menus/Concrete Menus/Title Screen/StartMenu_MW_Backpanel.h"
//#include "Game/Menus/Concrete Menus/Title Screen/StartMenu_MW_CustomLevel.h"
//#include "Game/Menus/Concrete Menus/Title Screen/StartMenu_MW_Exit.h"
//#include "Game/Menus/Concrete Menus/Title Screen/StartMenu_MW_Options.h"
//#include "Game/Menus/Concrete Menus/Title Screen/TitleGame_MW.h"
//#include "Game/Menus/Concrete Menus/Title Screen/Arcade/StartMenu_MW_Arcade.h"
//#include "Game/Menus/Concrete Menus/Title Screen/Story/StartMenu_MW_Campaign.h"


namespace CloudberryKingdom
{

	struct StartMenu_MW : public StartMenu
	{

		virtual ~StartMenu_MW()
		{
#ifdef BOOST_BIN
			OnDestructor( "StartMenu_MW" );
#endif
		}


		using StartMenu::SlideOut;
		using StartMenu::SlideIn;
		using StartMenu::Call;

		virtual void Call( const boost::shared_ptr<GUI_Panel> &child, int Delay );
		void MenuGo_Campaign( const boost::shared_ptr<MenuItem> &item );

		bool CallingOptionsMenu;

		virtual void MenuGo_Options( const boost::shared_ptr<MenuItem> &item );

		virtual void Exit();

	
		virtual void BringNextMenu();

		boost::shared_ptr<TitleGameData_MW> Title;
		StartMenu_MW( const boost::shared_ptr<TitleGameData_MW> &Title );
		boost::shared_ptr<StartMenu_MW> StartMenu_MW_Construct( const boost::shared_ptr<TitleGameData_MW> &Title );

		virtual void SlideIn( int Frames );

		virtual void SlideOut( PresetPos Preset, int Frames );

	
		virtual void BringCampaign();

		virtual void BringArcade();

		virtual void BringFreeplay();

		virtual void SetItemProperties( const boost::shared_ptr<MenuItem> &item );

		virtual void OnReturnTo();

		virtual void OnAdd();

		virtual void ReturnToCaller();

		virtual void Init();

		void MakeMenu();
	
		boost::shared_ptr<QuadClass> BackBox;

		void SetPos();

	};

}


#endif	//#ifndef STARTMENU_MW
