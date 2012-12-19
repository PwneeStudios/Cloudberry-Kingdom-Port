#ifndef STARTMENU_MW
#define STARTMENU_MW

#include <global_header.h>

namespace CloudberryKingdom
{

	struct StartMenu_MW : public StartMenu
	{

		using StartMenu::SlideOut;
		using StartMenu::SlideIn;
		using StartMenu::Call;

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

	
		virtual void OnAdd();

		virtual bool MenuReturnToCaller( const boost::shared_ptr<Menu> &menu );

		virtual void Init();

	
		boost::shared_ptr<QuadClass> BackBox;

		void BlackBox();

		void SmallBlackBox();
	};
}


#endif	//#ifndef STARTMENU_MW
