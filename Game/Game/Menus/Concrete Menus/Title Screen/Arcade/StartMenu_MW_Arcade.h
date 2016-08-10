#ifndef STARTMENU_MW_ARCADE
#define STARTMENU_MW_ARCADE

#include <small_header.h>

//#include "Core/Graphics/Draw/Quads/QuadClass.h"
//#include "Game/Localization.h"
//#include "Game/CloudberryKingdom/CloudberryKingdom.CloudberryKingdomGame.h"
//#include "Core/Text/EzText.h"
//#include "Game/Games/Meta Games/Challenges/Challenge_Base.h"
//#include "Game/Games/Meta Games/Arcade Games/Escalate/Escalation.h"
//#include "Game/Games/Meta Games/Arcade Games/Rush/Time Crisis/TimeCrisis.h"
//#include "Game/Player/PlayerManager.h"
//#include "Game/Menus/Menu Components/MenuItem.h"
//#include "Game/Menus/Concrete Menus/Title Screen/StartMenu.h"
//#include "Game/Menus/Concrete Menus/Title Screen/StartMenu_MW_Backpanel.h"
//#include "Game/Menus/Concrete Menus/Title Screen/TitleGame_MW.h"
#include "Game/Menus/Concrete Menus/Title Screen/Arcade/ArcadeMenu.h"
//#include "Game/Menus/Concrete Menus/Title Screen/Arcade/StartLevelMenu.h"
//#include "Game/Menus/Concrete Menus/Title Screen/Arcade/Hero Select/StartMenu_MW_HeroSelect.h"
//#include "Game/Tools/Tools.h"


namespace CloudberryKingdom
{
	struct StartMenu_MW_Arcade : public ArcadeMenu
	{

		virtual ~StartMenu_MW_Arcade()
		{
#ifdef BOOST_BIN
			OnDestructor( "StartMenu_MW_Arcade" );
#endif
		}


		using ArcadeMenu::SlideOut;
		using ArcadeMenu::SlideIn;
		using ArcadeMenu::Call;

		boost::shared_ptr<TitleGameData_MW> Title;
		StartMenu_MW_Arcade( const boost::shared_ptr<TitleGameData_MW> &Title );
		boost::shared_ptr<StartMenu_MW_Arcade> StartMenu_MW_Arcade_Construct( const boost::shared_ptr<TitleGameData_MW> &Title );

		virtual void SlideIn( int Frames );

		virtual void SlideOut( PresetPos Preset, int Frames );

	
		virtual void SetItemProperties( const boost::shared_ptr<MenuItem> &item );

	
		virtual void Go( const boost::shared_ptr<MenuItem> &item );

		virtual void OnAdd();

		virtual void Init();

	
		void SetPos();
	};
}


#endif	//#ifndef STARTMENU_MW_ARCADE
