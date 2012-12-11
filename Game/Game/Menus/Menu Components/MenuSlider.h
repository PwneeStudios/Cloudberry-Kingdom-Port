#ifndef MENUSLIDER
#define MENUSLIDER

#include <global_header.h>

namespace CloudberryKingdom
{
	struct MenuSlider : public MenuSliderBase
	{
	
		Vector2 SliderShift, TabOffset;

		std::shared_ptr<QuadClass> SliderBack, Slider, StartQuad, EndQuad;

		virtual void DoGrayOut();

		virtual void DoDeGrayOut();

		void Reset();

		MenuSlider( const std::shared_ptr<EzText> &Text );
		MenuSlider( const std::shared_ptr<EzText> &Text, const std::shared_ptr<EzText> &SelectedText );

	
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

	
		virtual void Draw( bool Text, const std::shared_ptr<Camera> &cam, bool Selected );

	
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef MENUSLIDER
