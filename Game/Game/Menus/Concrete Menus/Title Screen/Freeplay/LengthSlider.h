#ifndef LENGTHSLIDER
#define LENGTHSLIDER

#include <global_header.h>

namespace CloudberryKingdom
{
	struct LengthSlider : public MenuSliderBase
	{

	
		using MenuItem::Draw;

	
		LengthSlider();
		LengthSlider( const std::shared_ptr<EzText> &Text );
		LengthSlider( const std::shared_ptr<EzText> &Text, const std::shared_ptr<EzText> &SelectedText );

		int PerceivedMin;

	
		std::shared_ptr<ProgressBar> LengthBar;
	
		virtual void InitializeSlider();

	
		const virtual Vector2 getBL() const;
		const virtual Vector2 getTR() const;
		const virtual Vector2 getSlider_TR() const;

		virtual void SetCallback();

	
		virtual void CalcEndPoints();

	
		virtual void Draw( bool Text, const std::shared_ptr<Camera> &cam, bool Selected );

	
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef LENGTHSLIDER
