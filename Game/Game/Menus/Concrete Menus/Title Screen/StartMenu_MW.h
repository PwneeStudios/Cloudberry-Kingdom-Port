#ifndef STARTMENU_MW
#define STARTMENU_MW

#include <global_header.h>

namespace CloudberryKingdom
{

	struct StartMenu_MW : public StartMenu
	{

		virtual ~StartMenu_MW() { }

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
