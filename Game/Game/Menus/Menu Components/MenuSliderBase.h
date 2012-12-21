#ifndef MENUSLIDERBASE
#define MENUSLIDERBASE

#include <global_header.h>

namespace CloudberryKingdom
{

	/// <summary>
	/// The base struct for all derived MenuSlider classes
	/// </summary>
	struct MenuSliderBase : public MenuItem
	{
	
		struct SetCallbackProxy : public Lambda
		{
		
			boost::shared_ptr<MenuSliderBase> Msb;

		
			SetCallbackProxy( const boost::shared_ptr<MenuSliderBase> &msb );

			void Apply();
		};

		/// <summary>
		/// Called when the user explicitly manipulates the slider.
		/// </summary>
	
		boost::shared_ptr<Lambda> OnSlide;

		/// <summary>
		/// Called whenever the slider value is set.
		/// </summary>
		boost::shared_ptr<Lambda> OnSetValue;

		const bool getIsMaxed() const;

	
		void Slide();

	
		int DelayToSlideSound;
		int DelayToSlideSoundCount;

		const virtual Vector2 getBL() const;
		const virtual Vector2 getTR() const;
		const virtual Vector2 getSlider_TR() const;

		const float getVal() const;
		void setVal( const float &value );

		boost::shared_ptr<WrappedFloat> _MyFloat;
		const boost::shared_ptr<WrappedFloat> &getMyFloat() const;
		void setMyFloat( const boost::shared_ptr<WrappedFloat> &value );

		float InitialSlideSpeed;
		float MaxSlideSpeed;
		float Acceleration;
	
		float Speed;

	
		bool Discrete;
	
		static const int SelectDelay = 8;
		int DelayCount;

	
		MenuSliderBase();
		MenuSliderBase( const boost::shared_ptr<EzText> &Text );
		MenuSliderBase( const boost::shared_ptr<EzText> &Text, const boost::shared_ptr<EzText> &SelectedText );

		boost::shared_ptr<MenuSliderBase> MenuSliderBase_Construct();
		boost::shared_ptr<MenuSliderBase> MenuSliderBase_Construct( const boost::shared_ptr<EzText> &Text );
		boost::shared_ptr<MenuSliderBase> MenuSliderBase_Construct( const boost::shared_ptr<EzText> &Text, const boost::shared_ptr<EzText> &SelectedText );
	
		std::wstring BaseString;
	
		virtual void InitializeSlider();

	
		virtual void SetCallback();

		virtual void Release();

#if defined(PC_VERSION)
		Vector2 BL_HitPadding, TR_HitPadding;
		virtual bool HitTest( Vector2 pos, Vector2 padding );
#endif

	
		Vector2 Start, End;
		virtual void CalcEndPoints();

	
		virtual std::wstring ToString();

	
		bool ShowText;
		void UpdateText();

	
		void SetToShowText();

		bool Inverted;
#if defined(PC_VERSION)
	
		virtual void PC_OnLeftMouseDown();
#endif

	
		Vector2 PrevDir;
	
		virtual void PhsxStep( bool Selected );

	
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef MENUSLIDERBASE
