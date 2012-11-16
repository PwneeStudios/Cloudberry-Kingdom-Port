#ifndef GUI_TIMER_BASE
#define GUI_TIMER_BASE

#include <global_header.h>

namespace CloudberryKingdom
{
	class EzText;
}

namespace CloudberryKingdom
{
	class Multicaster_1;
}


//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Text;

using namespace Microsoft::Xna::Framework;

namespace CloudberryKingdom
{
	class GUI_Timer_Base : public GUI_Panel
	{
	private:
		int _Time;

		/// <summary>
		/// The time in number of frames
		/// </summary> 
	public:
		const int &getTime() const;
		void setTime( const int &value );

		const int &getMinutes() const;

		const int &getSeconds() const;

		const int &getMilliseconds() const;

	private:
		std::shared_ptr<StringBuilder> MyString;

		/// <summary>
		/// Return a string representation of the time
		/// </summary>
		/// <returns></returns>
	public:
		std::shared_ptr<StringBuilder> BuildString();

	private:
		bool AddedOnce;
	public:
		virtual void OnAdd();

		virtual void Hide();

		float Intensity;
		virtual void Show();

		void ShowInstant();

	protected:
		virtual void ReleaseBody();

	public:
		const Vector2 &getApparentPos() const;

	private:
		std::shared_ptr<EzText> TimerText;
		void UpdateTimerText();

	public:
		GUI_Timer_Base();

	protected:
		virtual void MyDraw();

	public:
		std::shared_ptr<Multicaster_1<GUI_Timer_Base*> > OnTimeExpired;

		/// <summary>
		/// When true the timer will continue to count down even when every player is dead.
		/// </summary>
		bool CountDownWhileDead;

	protected:
		virtual void MyPhsxStep();

	private:
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef GUI_TIMER_BASE
