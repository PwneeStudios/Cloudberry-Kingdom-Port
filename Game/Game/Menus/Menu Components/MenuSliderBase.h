#ifndef MENUSLIDERBASE
#define MENUSLIDERBASE

#include "MenuItem.h"
#include "../Core/Lambdas/Lambda.h"
#include "../Game/Objects/Game Objects/GameObjects/ExplodeBobs.h"
#include <string>
#include <cmath>
#include <tchar.h>
#include "stringconverter.h"

namespace CloudberryKingdom
{
	class Lambda;
}

namespace CloudberryKingdom
{
	class WrappedFloat;
}

namespace CloudberryKingdom
{
	class EzText;
}


//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;

using namespace Microsoft::Xna::Framework;

namespace CloudberryKingdom
{
	/// <summary>
	/// The base class for all derived MenuSlider classes
	/// </summary>
	class MenuSliderBase : public MenuItem
	{
	private:
		class SetCallbackProxy : public Lambda
		{
		private:
			std::shared_ptr<MenuSliderBase> Msb;

		public:
			SetCallbackProxy( const std::shared_ptr<MenuSliderBase> &msb );

			void Apply();
		};

		/// <summary>
		/// Called when the user explicitly manipulates the slider.
		/// </summary>
	public:
		std::shared_ptr<Lambda> OnSlide;

		/// <summary>
		/// Called whenever the slider value is set.
		/// </summary>
		std::shared_ptr<Lambda> OnSetValue;

		const bool &getIsMaxed() const;

	protected:
		void Slide();

	public:
		int DelayToSlideSound;
		int DelayToSlideSoundCount;

		const virtual Vector2 &getBL() const;
		const virtual Vector2 &getTR() const;
		const virtual Vector2 &getSlider_TR() const;

		const float &getVal() const;
		void setVal( const float &value );

		std::shared_ptr<WrappedFloat> _MyFloat;
		const std::shared_ptr<WrappedFloat> &getMyFloat() const;
		void setMyFloat( const std::shared_ptr<WrappedFloat> &value );

		float InitialSlideSpeed;
		float MaxSlideSpeed;
		float Acceleration;
	private:
		float Speed;

	public:
		bool Discrete;
	private:
		static const int SelectDelay = 8;
		int DelayCount;

	public:
		MenuSliderBase();

		MenuSliderBase( const std::shared_ptr<EzText> &Text );
		MenuSliderBase( const std::shared_ptr<EzText> &Text, const std::shared_ptr<EzText> &SelectedText );

	private:
		std::wstring BaseString;
	protected:
		virtual void InitializeSlider();

	public:
		virtual void SetCallback();

		virtual void Release();

#if defined(PC_VERSION)
		Vector2 BL_HitPadding, TR_HitPadding;
		virtual bool HitTest( Vector2 pos, Vector2 padding );
#endif

	protected:
		Vector2 Start, End;
		virtual void CalcEndPoints();

	public:
		virtual std::wstring ToString();

	private:
		bool ShowText;
		void UpdateText();

	public:
		void SetToShowText();

		bool Inverted;
#if defined(PC_VERSION)
	protected:
		virtual void PC_OnLeftMouseDown();
#endif

	private:
		Vector2 PrevDir;
	public:
		virtual void PhsxStep( bool Selected );

	private:
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef MENUSLIDERBASE
