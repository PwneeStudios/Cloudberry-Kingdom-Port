#ifndef GUI_TIMER_BASE
#define GUI_TIMER_BASE

#include <global_header.h>

namespace CloudberryKingdom
{
	struct GUI_Timer_Base : public GUI_Panel
	{
	
		int _Time;

		/// <summary>
		/// The time in number of frames
		/// </summary> 
	
		const int &getTime() const;
		void setTime( const int &value );

		const int getMinutes() const;

		const int getSeconds() const;

		const int getMilliseconds() const;

	
		std::shared_ptr<StringBuilder> MyString;

		/// <summary>
		/// Return a string representation of the time
		/// </summary>
		/// <returns></returns>
	
		std::shared_ptr<StringBuilder> BuildString();

	
		bool AddedOnce;
	
		virtual void OnAdd();

		virtual void Hide();

		float Intensity;
		virtual void Show();

		void ShowInstant();

	
		virtual void ReleaseBody();

	
		const Vector2 getApparentPos() const;

	
		std::shared_ptr<EzText> TimerText;
		void UpdateTimerText();

	
		GUI_Timer_Base();
		std::shared_ptr<GUI_Timer_Base> GUI_Timer_Base_Construct();

	
		virtual void MyDraw();

	
		std::shared_ptr<Multicaster_1<std::shared_ptr<GUI_Timer_Base> > > OnTimeExpired;

		/// <summary>
		/// When true the timer will continue to count down even when every player is dead.
		/// </summary>
		bool CountDownWhileDead;

	
		virtual void MyPhsxStep();

	
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef GUI_TIMER_BASE
