#ifndef STARTMENU_MW_PRESSSTART
#define STARTMENU_MW_PRESSSTART

#include <small_header.h>

//#include "Core/Graphics/Draw/DrawPile.h"
//#include "Game/Localization.h"
//#include "Game/CloudberryKingdom/CloudberryKingdom.CloudberryKingdomGame.h"
//#include "Game/Menus/Concrete Menus/Title Screen/StartMenu_MW_Pre.h"
//#include "Game/Menus/Concrete Menus/Title Screen/StartMenu_MW_Simple.h"
//#include "Core/Input/ButtonCheck.h"
//#include "Core/Text/EzText.h"
//#include "Core/Tools/CoreMath.h"
#include "Game/Menus/CkBaseMenu.h"
//#include "Game/Menus/Concrete Menus/Title Screen/StartMenu_MW_Backpanel.h"
//#include "Game/Menus/Concrete Menus/Title Screen/TitleGame_MW.h"
//#include "Game/Tools/Resources.h"
//#include "Game/Tools/Tools.h"


namespace CloudberryKingdom
{
	struct StartMenu_MW_PressStart : public CkBaseMenu
	{

		virtual ~StartMenu_MW_PressStart()
		{
#ifdef BOOST_BIN
			OnDestructor( "StartMenu_MW_PressStart" );
#endif
		}


		using CkBaseMenu::SlideOut;
		using CkBaseMenu::SlideIn;
		using CkBaseMenu::Call;

		boost::shared_ptr<TitleGameData_MW> Title;
		StartMenu_MW_PressStart( const boost::shared_ptr<TitleGameData_MW> &Title );
		boost::shared_ptr<StartMenu_MW_PressStart> StartMenu_MW_PressStart_Construct( const boost::shared_ptr<TitleGameData_MW> &Title );

		virtual void SlideIn( int Frames );

		virtual void SlideOut( PresetPos Preset, int Frames );

		virtual void OnAdd();

	
		boost::shared_ptr<EzText> Text;
		int DelayToAllowInput;
	
		virtual void Init();

	
		void SetPos();

	
		virtual void MyPhsxStep();

	
		float t;
	
		virtual void MyDraw();

	
		virtual void OnReturnTo();

	
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef STARTMENU_MW_PRESSSTART
