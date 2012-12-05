#ifndef MENUSLIDER
#define MENUSLIDER

#include <global_header.h>

namespace CloudberryKingdom
{
	class MenuSlider : public MenuSliderBase
	{
	public:
		Vector2 SliderShift, TabOffset;

		std::shared_ptr<QuadClass> SliderBack, Slider, StartQuad, EndQuad;

		virtual void DoGrayOut();

		virtual void DoDeGrayOut();

		void Reset();

		MenuSlider( const std::shared_ptr<EzText> &Text );
		MenuSlider( const std::shared_ptr<EzText> &Text, const std::shared_ptr<EzText> &SelectedText );

	protected:
		virtual void InitializeSlider();

	public:
		const Vector2 getSliderBackSize() const;
		void setSliderBackSize( const Vector2 &value );

		const Vector2 getSliderSize() const;
		void setSliderSize( const Vector2 &value );

		virtual float Height();

		virtual float Width();

	protected:
		virtual void CalcEndPoints();

	public:
		bool CustomEndPoints;
		Vector2 CustomStart, CustomEnd;

	private:
		Vector2 RelStart, RelEnd;
		void CalcRelEndPoints();

	public:
		virtual void Draw( bool Text, const std::shared_ptr<Camera> &cam, bool Selected );

	private:
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef MENUSLIDER
