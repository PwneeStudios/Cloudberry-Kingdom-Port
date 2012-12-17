#ifndef MENUSCROLLBAR
#define MENUSCROLLBAR

#include <global_header.h>

namespace CloudberryKingdom
{
	struct MenuScrollBar : public MenuSlider
	{
	
		MenuScrollBar();

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
