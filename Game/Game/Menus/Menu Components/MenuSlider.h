#ifndef MENUSLIDER
#define MENUSLIDER

#include <small_header.h>

//#include "Core/Graphics/Draw/Quads/QuadClass.h"
//#include "Core/Text/EzText.h"
//#include "Game/Menus/Menu.h"
#include "Game/Menus/Menu Components/MenuSliderBase.h"
//#include "Game/Tools/Camera.h"
//#include "Game/Tools/Tools.h"


namespace CloudberryKingdom
{

	struct MenuSlider : public MenuSliderBase
	{

		virtual ~MenuSlider()
		{
#ifdef BOOST_BIN
			OnDestructor( "MenuSlider" );
#endif
		}

	
		Vector2 SliderShift, TabOffset;

		boost::shared_ptr<QuadClass> SliderBack, Slider, StartQuad, EndQuad;

		virtual void DoGrayOut();

		virtual void DoDeGrayOut();

		void Reset();

		MenuSlider( const boost::shared_ptr<EzText> &Text );
		MenuSlider( const boost::shared_ptr<EzText> &Text, const boost::shared_ptr<EzText> &SelectedText );

		boost::shared_ptr<MenuSlider> MenuSlider_Construct( const boost::shared_ptr<EzText> &Text );
		boost::shared_ptr<MenuSlider> MenuSlider_Construct( const boost::shared_ptr<EzText> &Text, const boost::shared_ptr<EzText> &SelectedText );
	
		virtual void InitializeSlider();

	
		Vector2 getSliderBackSize() const;
		void setSliderBackSize( const Vector2 &value );

		Vector2 getSliderSize() const;
		void setSliderSize( const Vector2 &value );

		virtual float Height();

		virtual float Width();

	
		virtual void CalcEndPoints();

	
		bool CustomEndPoints;
		Vector2 CustomStart, CustomEnd;

	
		Vector2 RelStart, RelEnd;
		void CalcRelEndPoints();

	
		virtual void Draw( bool Text, const boost::shared_ptr<Camera> &cam, bool Selected );

	
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef MENUSLIDER
