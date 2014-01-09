#ifndef CONTROLSCREEN
#define CONTROLSCREEN

#include <small_header.h>

//#include "Core/Graphics/Draw/DrawPile.h"
//#include "Core/Graphics/Draw/Quads/QuadClass.h"
//#include "Game/Localization.h"
//#include "Core/Input/ButtonCheck.h"
//#include "Core/Text/EzText.h"
//#include "Core/Tools/ColorHelper.h"
#include "Game/Menus/CkBaseMenu.h"
//#include "Game/Games/CampaignHelper.h"
//#include "Game/Menus/Menu.h"
//#include "Game/Menus/Concrete Menus/InGameStartMenus/Sub Menus/CustomControls.h"
//#include "Game/Tools/Resources.h"
//#include "Game/Tools/Tools.h"


namespace CloudberryKingdom
{

	struct ControlScreen : public CkBaseMenu
	{
	
		virtual ~ControlScreen()
		{
#ifdef BOOST_BIN
			OnDestructor( "ControlScreen" );
#endif
		}


		boost::shared_ptr<QuadClass> BackgroundQuad;

	
		ControlScreen( int Control );
		boost::shared_ptr<ControlScreen> ControlScreen_Construct( int Control );

#if defined(PC_VERSION)
		boost::shared_ptr<QuadClass> MakeQuad( Keys key );
#endif
	
		virtual void Init();

		void SetPos();
	
		virtual void MyPhsxStep();
	};
}


#endif	//#ifndef CONTROLSCREEN
