#ifndef STARTMENU_MW
#define STARTMENU_MW

#include <global_header.h>

namespace CloudberryKingdom
{
	struct StartMenu_MW : public StartMenu
	{
	
		virtual void MenuGo_Options( const std::shared_ptr<MenuItem> &item );

		virtual void Exit();

	
		virtual void BringNextMenu();

		std::shared_ptr<TitleGameData_MW> Title;
		StartMenu_MW( const std::shared_ptr<TitleGameData_MW> &Title );
		void StartMenu_MW_Construct( const std::shared_ptr<TitleGameData_MW> &Title );

		virtual void SlideIn( int Frames );

		virtual void SlideOut( const PresetPos &Preset, int Frames );

	
		virtual void BringCampaign();

		virtual void BringArcade();

		virtual void BringFreeplay();

		virtual void SetItemProperties( const std::shared_ptr<MenuItem> &item );

	
		virtual void OnAdd();

		virtual bool MenuReturnToCaller( const std::shared_ptr<Menu> &menu );

		virtual void Init();

	
		std::shared_ptr<QuadClass> BackBox;

		void BlackBox();

		void SmallBlackBox();
	};
}


#endif	//#ifndef STARTMENU_MW
