#ifndef LENGTHSLIDER
#define LENGTHSLIDER

#include <global_header.h>

namespace CloudberryKingdom
{

	struct LengthSlider : public MenuSliderBase
	{
	
		virtual ~LengthSlider()
		{
#ifdef BOOST_BIN
			OnDestructor( "LengthSlider" );
#endif
		}


		using MenuItem::Draw;
	
		LengthSlider();
		LengthSlider( const boost::shared_ptr<EzText> &Text );
		LengthSlider( const boost::shared_ptr<EzText> &Text, const boost::shared_ptr<EzText> &SelectedText );

		boost::shared_ptr<LengthSlider> LengthSlider_Construct();
		boost::shared_ptr<LengthSlider> LengthSlider_Construct( const boost::shared_ptr<EzText> &Text );
		boost::shared_ptr<LengthSlider> LengthSlider_Construct( const boost::shared_ptr<EzText> &Text, const boost::shared_ptr<EzText> &SelectedText );

		int PerceivedMin;

		boost::shared_ptr<ProgressBar> LengthBar;
	
		virtual void InitializeSlider();

		const virtual Vector2 getBL() const;
		const virtual Vector2 getTR() const;
		const virtual Vector2 getSlider_TR() const;

		virtual void SetCallback();

		virtual void CalcEndPoints();
	
		virtual void Draw( bool Text, const boost::shared_ptr<Camera> &cam, bool Selected );
	
		void InitializeInstanceFields();

	};

}

#endif	//#ifndef LENGTHSLIDER
