#ifndef MENUSCROLLBAR
#define MENUSCROLLBAR

#include <small_header.h>

//#include "Core/Graphics/Draw/Quads/QuadClass.h"
//#include "Core/Text/EzText.h"
//#include "Core/Texture/EzTexture.h"
#include "Game/Menus/Menu Components/MenuSlider.h"
//#include "Game/Tools/Camera.h"
//#include "Game/Tools/Resources.h"
//#include "Game/Tools/Tools.h"


namespace CloudberryKingdom
{

	struct MenuScrollBar : public MenuSlider
	{

		virtual ~MenuScrollBar()
		{
#ifdef BOOST_BIN
			OnDestructor( "MenuScrollBar" );
#endif
		}

	
		MenuScrollBar();
		boost::shared_ptr<MenuScrollBar> MenuScrollBar_Construct();

		boost::shared_ptr<EzTexture> Normal, Held;
	
		virtual void InitializeSlider();
	
		Vector2 StartPlus;
		Vector2 EndPlus;
		bool DrawEnds;
		virtual void Draw( bool Text, const boost::shared_ptr<Camera> &cam, bool Selected );

	
		void InitializeInstanceFields();

	};
}


#endif	//#ifndef MENUSCROLLBAR
