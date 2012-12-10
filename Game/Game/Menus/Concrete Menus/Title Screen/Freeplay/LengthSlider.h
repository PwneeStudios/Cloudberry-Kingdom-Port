#ifndef LENGTHSLIDER
#define LENGTHSLIDER

#include <global_header.h>

namespace CloudberryKingdom
{
	class LengthSlider : public MenuSliderBase
	{

	public:
		using MenuItem::Draw;

	public:
		LengthSlider();
		LengthSlider( const std::shared_ptr<EzText> &Text );
		LengthSlider( const std::shared_ptr<EzText> &Text, const std::shared_ptr<EzText> &SelectedText );

		int PerceivedMin;

	private:
		std::shared_ptr<ProgressBar> LengthBar;
	protected:
		virtual void InitializeSlider();

	public:
		const virtual Vector2 getBL() const;
		const virtual Vector2 getTR() const;
		const virtual Vector2 getSlider_TR() const;

		virtual void SetCallback();

	protected:
		virtual void CalcEndPoints();

	public:
		virtual void Draw( bool Text, const std::shared_ptr<Camera> &cam, bool Selected );

	private:
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef LENGTHSLIDER
