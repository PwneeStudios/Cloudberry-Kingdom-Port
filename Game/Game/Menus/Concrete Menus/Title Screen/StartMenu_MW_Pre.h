#ifndef STARTMENU_MW_PRE
#define STARTMENU_MW_PRE

#include <global_header.h>

namespace CloudberryKingdom
{

	struct StartMenu_MW_Pre : public StartMenu
	{

		virtual ~StartMenu_MW_Pre() { }

		using StartMenu::SlideOut;
		using StartMenu::SlideIn;
		using StartMenu::Call;
		using StartMenu::Hide;

		bool CallingOptionsMenu;
		boost::shared_ptr<QuadClass> BackBox;
		boost::shared_ptr<TitleGameData_MW> Title;



		struct MenuGo_PlayProxy : public Lambda_1<boost::shared_ptr<MenuItem> >
		{
			boost::shared_ptr<StartMenu_MW_Pre> sm;

			MenuGo_PlayProxy( boost::shared_ptr<StartMenu_MW_Pre> sm )
			{
				this->sm = sm;
			}

			void Apply( const boost::shared_ptr<MenuItem> &item )
			{
				sm->MenuGo_Play( item );
			}
		};

		struct MenuGo_AchievementsProxy : public Lambda_1<boost::shared_ptr<MenuItem> >
		{
			boost::shared_ptr<StartMenu_MW_Pre> sm;

			MenuGo_AchievementsProxy( boost::shared_ptr<StartMenu_MW_Pre> sm )
			{
				this->sm = sm;
			}

			void Apply( const boost::shared_ptr<MenuItem> &item )
			{
				sm->MenuGo_Achievements( item );
			}
		};

		struct MenuGo_LeaderboardsProxy : public Lambda_1<boost::shared_ptr<MenuItem> >
		{
			boost::shared_ptr<StartMenu_MW_Pre> sm;

			MenuGo_LeaderboardsProxy( boost::shared_ptr<StartMenu_MW_Pre> sm )
			{
				this->sm = sm;
			}

			void Apply( const boost::shared_ptr<MenuItem> &item )
			{
				sm->MenuGo_Leaderboards( item );
			}
		};

		struct MenuGo_BuyGameProxy : public Lambda_1<boost::shared_ptr<MenuItem> >
		{
			boost::shared_ptr<StartMenu_MW_Pre> sm;

			MenuGo_BuyGameProxy( boost::shared_ptr<StartMenu_MW_Pre> sm )
			{
				this->sm = sm;
			}

			void Apply( const boost::shared_ptr<MenuItem> &item )
			{
				sm->MenuGo_BuyGame( item );
			}
		};

		struct MenuGo_OptionsProxy : public Lambda_1<boost::shared_ptr<MenuItem> >
		{
			boost::shared_ptr<StartMenu_MW_Pre> sm;

			MenuGo_OptionsProxy( boost::shared_ptr<StartMenu_MW_Pre> sm )
			{
				this->sm = sm;
			}

			void Apply( const boost::shared_ptr<MenuItem> &item )
			{
				sm->MenuGo_Options( item );
			}
		};

		struct MenuGo_ExitProxy : public Lambda_1<boost::shared_ptr<MenuItem> >
		{
			boost::shared_ptr<StartMenu_MW_Pre> sm;

			MenuGo_ExitProxy( boost::shared_ptr<StartMenu_MW_Pre> sm )
			{
				this->sm = sm;
			}

			void Apply( const boost::shared_ptr<MenuItem> &item )
			{
				sm->MenuGo_Exit( item );
			}
		};


		void MenuGo_Options( boost::shared_ptr<MenuItem> item );
		void Exit();
		void BringNextMenu();
		StartMenu_MW_Pre( boost::shared_ptr<TitleGameData_MW> Title );
		boost::shared_ptr<StartMenu_MW_Pre> StartMenu_MW_Pre_Construct( boost::shared_ptr<TitleGameData_MW> Title );
		void SlideIn( int Frames );
		void SlideOut( PresetPos Preset, int Frames );
		void SetItemProperties( boost::shared_ptr<MenuItem> item );
		void OnAdd();
		void OnReturnTo();
		bool MenuReturnToCaller( boost::shared_ptr<Menu> menu );
		void Init();
		void MenuGo_Play( boost::shared_ptr<MenuItem> item );
		void MenuGo_Leaderboards( boost::shared_ptr<MenuItem> item );
		void MenuGo_Achievements( boost::shared_ptr<MenuItem> item );
		void MenuGo_BuyGame( boost::shared_ptr<MenuItem> item );
		void MakeMenu();
		void SetPos();

	};

}


#endif	//#ifndef STARTMENU_MW_PRE
