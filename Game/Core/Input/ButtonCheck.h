#ifndef BUTTONCHECK
#define BUTTONCHECK

#include <global_header.h>


namespace CloudberryKingdom
{
	class KeyboardExtension
	{
	public:
		static bool Freeze;
		static void FreezeInput();
		static void UnfreezeInput();

//C# TO C++ CONVERTER TODO TASK: Extension methods are not available in C++:
//ORIGINAL LINE: public static bool IsKeyDownCustom(this KeyboardState keyboard, Keys key)
		static bool IsKeyDownCustom( KeyboardState &keyboard, Keys key );
	};

	class ButtonStatistics
	{
	private:
		std::vector<int> _DownCount;

	public:
		int DownCount( ControllerButtons button );

		/// <summary>
		/// If Incr is true then the increment is increased by 1, otherwise it is set to 0.
		/// </summary>
		void IncrCount( ControllerButtons button, bool Incr );

		void IncrCount( ControllerButtons button );

		void SetCount( ControllerButtons button, int count );

	private:
		void InitializeInstanceFields();

public:
		ButtonStatistics()
		{
			InitializeInstanceFields();
		}
	};

	class ButtonStats
	{
	public:
		static std::vector<std::shared_ptr<ButtonStatistics> > Controller;
		static std::shared_ptr<ButtonStatistics> All;

	private:
		static void Init();

	public:
		static void Update();
	};

	class ButtonClass
	{
	public:
		ControllerButtons ControllerButton;
		Keys KeyboardKey;
		bool IsKeyboard;

		void Set( Keys key );
		void Set( ControllerButtons key );

	private:
		void InitializeInstanceFields();

public:
		ButtonClass()
		{
			InitializeInstanceFields();
		}
	};

	

	class ButtonData
	{
	public:
		bool Down;
		bool Pressed;
		bool Released;
		Vector2 Dir;
		float Squeeze;
		int PressingPlayer;
	};
	class ButtonCheck
	{
		/// <summary>
		/// Whether the user is using the mouse. False when the mouse hasn't been used since the arrow keys.
		/// </summary>
	public:
		static bool MouseInUse;
		static bool PrevMouseInUse;

		static void UpdateControllerAndKeyboard_StartOfStep();

		static void UpdateControllerAndKeyboard_EndOfStep( ResolutionGroup Resolution );

#if defined(PC_VERSION)
		/// <summary>
		/// Update the boolean flag MouseInUse
		/// </summary>
		static void UpdateMouseUse();
#endif

		static void KillSecondary();

		static std::shared_ptr<ButtonClass> Quickspawn_KeyboardKey, Help_KeyboardKey, QuickReset_KeyboardKey;
		static Keys Start_Secondary, Go_Secondary, Back_Secondary, ReplayPrev_Secondary, ReplayNext_Secondary, ReplayToggle_Secondary, SlowMoToggle_Secondary, Left_Secondary, Right_Secondary, Up_Secondary, Down_Secondary;

		static void Reset();

		static float ThresholdSensitivity; //.75f;

		ControllerButtons MyButton1, MyButton2;
		int MyPlayerIndex;
		MashType MyType;
	private:
		ButtonData Current, Previous;

	public:
		int GapCount, GapAllowance;
		int Dir;

		bool Satisfied;

		static int Direction( Vector2 Dir );


		static Vector2 GetDir( int Control );
		static Vector2 GetDir( int Control, bool Threshold );

		static Vector2 GetMaxDir();
		static Vector2 GetMaxDir( int Control );
		static Vector2 GetMaxDir( bool MustExist );


		static bool PreventNextInput;
		static int PreventTimeStamp;
		static void PreventInput();

		/// <summary>
		/// Check for a standard back input (B) or (Esc)
		/// </summary>
		/// <returns></returns>
		static bool Back( int Control );

		static ButtonData State( Keys Key );

#if defined(WINDOWS)
		static bool AnyMouseKey();
#endif

#if defined(WINDOWS)
		static bool AnyKeyboardKey();
#endif

		static bool AnyKey();

		static ButtonData AllState( int iPlayerIndex );

#if defined(WINDOWS)
		/// <summary>
		/// Returns true if a keyboard go key is pressed (Enter, Z, Space)
		/// </summary>
		static bool KeyboardGo();
#endif

//ORIGINAL LINE: public static ButtonData State(int iPlayerIndex, params ControllerButtons[] ButtonList)
//C# TO C++ CONVERTER TODO TASK: Use 'va_start', 'va_arg', and 'va_end' to access the parameter array within this method:
		static ButtonData State( int iPlayerIndex, const std::vector<ControllerButtons> &ButtonList );

		/// <summary>
		/// When true it is assumed that at least one player is officially logged in.
		/// When false a player index of -1 (any signed in player) will be interpreted as -1 (any player).
		/// </summary>
		static bool PreLogIn;

		static ButtonData State( const std::shared_ptr<ButtonClass> &Button, int iPlayerIndex );
	private:
		static ButtonData GetState( Keys Key, bool Prev );




	public:
		static ButtonData State( ControllerButtons Button, PlayerIndex Index );
		static ButtonData State( ControllerButtons Button, int iPlayerIndex );
		static ButtonData State( ControllerButtons Button, int iPlayerIndex, bool UseKeyboardMapping );
	private:
		static ButtonData GetState( ControllerButtons Button, int iPlayerIndex, bool Prev, bool UseKeyboardMapping );

	public:
		ButtonCheck();

		std::wstring GetString();

		void Phsx();
	};
}


#endif	//#ifndef BUTTONCHECK
