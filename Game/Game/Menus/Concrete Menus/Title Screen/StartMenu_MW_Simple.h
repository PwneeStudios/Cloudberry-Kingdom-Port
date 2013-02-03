#ifndef STARTMENU_MW_SIMPLE
#define STARTMENU_MW_SIMPLE

#include <global_header.h>

namespace CloudberryKingdom
{

	struct StartMenu_MW_Simple : public StartMenu_MW
	{

		virtual ~StartMenu_MW_Simple() { }

		using StartMenu::SlideOut;
		using StartMenu::SlideIn;
		using StartMenu::Call;

		StartMenu_MW_Simple( boost::shared_ptr<TitleGameData_MW> Title );
		boost::shared_ptr<StartMenu_MW_Simple> StartMenu_MW_Simple_Construct( boost::shared_ptr<TitleGameData_MW> Title );
		void MakeMenu();
		void SetPos();

	};

}


#endif	//#ifndef STARTMENU_MW_SIMPLE
