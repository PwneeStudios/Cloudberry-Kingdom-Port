#ifndef STARTMENU_MW_SIMPLE
#define STARTMENU_MW_SIMPLE

#include <small_header.h>

//#include "Core/Graphics/Draw/Quads/QuadClass.h"
//#include "Game/Localization.h"
//#include "Game/CloudberryKingdom/CloudberryKingdom.CloudberryKingdomGame.h"
//#include "Game/Player/LeaderboardView.h"
//#include "Core/Text/EzText.h"
//#include "Core/Tools/ColorHelper.h"
//#include "Game/Menus/Menu Components/MenuItem.h"
#include "Game/Menus/Concrete Menus/Title Screen/StartMenu_MW.h"
//#include "Game/Menus/Concrete Menus/Title Screen/TitleGame_MW.h"


namespace CloudberryKingdom
{

	struct StartMenu_MW_Simple : public StartMenu_MW
	{

		virtual ~StartMenu_MW_Simple()
		{
#ifdef BOOST_BIN
			OnDestructor( "StartMenu_MW_Simple" );
#endif
		}


		using StartMenu::SlideOut;
		using StartMenu::SlideIn;
		using StartMenu::Call;

		void MenuGo_Leaderboards( boost::shared_ptr<MenuItem> item );

		struct MenuGo_LeaderboardsProxy : public Lambda_1<boost::shared_ptr<MenuItem> >
		{
			boost::shared_ptr<StartMenu_MW_Simple> sm;

			MenuGo_LeaderboardsProxy( boost::shared_ptr<StartMenu_MW_Simple> sm )
			{
				this->sm = sm;
			}

			void Apply( const boost::shared_ptr<MenuItem> &item )
			{
				sm->MenuGo_Leaderboards( item );
			}
		};
		

		StartMenu_MW_Simple( boost::shared_ptr<TitleGameData_MW> Title );
		boost::shared_ptr<StartMenu_MW_Simple> StartMenu_MW_Simple_Construct( boost::shared_ptr<TitleGameData_MW> Title );
		void MakeMenu();
		void SetPos();

	};

}


#endif	//#ifndef STARTMENU_MW_SIMPLE
