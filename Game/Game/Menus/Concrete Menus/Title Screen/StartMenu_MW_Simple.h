#ifndef STARTMENU_MW_SIMPLE
#define STARTMENU_MW_SIMPLE

#include <global_header.h>

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
