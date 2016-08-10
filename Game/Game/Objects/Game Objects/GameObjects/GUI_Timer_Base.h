#ifndef GUI_TIMER_BASE
#define GUI_TIMER_BASE

#include <small_header.h>

//#include "Core/Graphics/Draw/DrawPile.h"
//#include "Core/Text/EzFont.h"
//#include "Core/Text/EzText.h"
#include "Game/Objects/Game Objects/GameObjects/GUI_Panel.h"
//#include "Game/Player/PlayerManager.h"
//#include "Game/Tools/Resources.h"
//#include "Game/Tools/Tools.h"


namespace CloudberryKingdom
{

	struct GUI_Timer_Base : public GUI_Panel
	{

		virtual ~GUI_Timer_Base()
		{
#ifdef BOOST_BIN
			OnDestructor( "GUI_Timer_Base" );
#endif
		}

	
		using GUI_Panel::SlideOut;
		using GUI_Panel::SlideIn;
		using GUI_Panel::Call;

		int _Time;

		/// <summary>
		/// The time in number of frames
		/// </summary> 
	
		const int &getTime() const;
		void setTime( const int &value );

		const int getMinutes() const;

		const int getSeconds() const;

		const int getMilliseconds() const;

	
		boost::shared_ptr<StringBuilder> MyString;

		/// <summary>
		/// Return a string representation of the time
		/// </summary>
		/// <returns></returns>
	
		boost::shared_ptr<StringBuilder> BuildString();

	
		bool AddedOnce;
	
		virtual void OnAdd();

		virtual void Hide();

		float Intensity;
		virtual void Show();

		void ShowInstant();

	
		virtual void ReleaseBody();

	
		const Vector2 getApparentPos() const;

	
		boost::shared_ptr<EzText> TimerText;
		void UpdateTimerText();

	
		GUI_Timer_Base();
		boost::shared_ptr<GUI_Timer_Base> GUI_Timer_Base_Construct();

	
		virtual void MyDraw();

	
		boost::shared_ptr<Multicaster_1<boost::shared_ptr<GUI_Timer_Base> > > OnTimeExpired;

		/// <summary>
		/// When true the timer will continue to count down even when every player is dead.
		/// </summary>
		bool CountDownWhileDead;

	
		virtual void MyPhsxStep();

	
		void InitializeInstanceFields();
	};

}


#endif	//#ifndef GUI_TIMER_BASE
