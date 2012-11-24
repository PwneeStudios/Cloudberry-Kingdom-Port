#ifndef TEXTINPUT
#define TEXTINPUT

#include <global_header.h>

#if defined(WINDOWS)


namespace CloudberryKingdom
{
	class CharacterEventArgs : public EventArgs
	{
	private:
		const wchar_t character;
		const int lParam;
	public:
		CharacterEventArgs( wchar_t character, int lParam );
		const wchar_t &getCharacter() const;
		const int &getParam() const;
		const int &getRepeatCount() const;
		const bool &getExtendedKey() const;
		const bool &getAltPressed() const;
		const bool &getPreviousState() const;
		const bool &getTransitionState() const;
	};
	class KeyEventArgs : public EventArgs
	{
	private:
		Keys keyCode;
	public:
		KeyEventArgs( Keys keyCode );
		const Keys &getKeyCode() const;
	};
	typedef void ( *CharEnteredHandler )( const std::shared_ptr<Object> &sender, const std::shared_ptr<CharacterEventArgs> &e );
	typedef void ( *KeyEventHandler )( const std::shared_ptr<Object> &sender, const std::shared_ptr<KeyEventArgs> &e );
	class EventInput
	{
		/// <summary>
		/// Event raised when a character has been entered.		
		/// </summary>
//C# TO C++ CONVERTER TODO TASK: There is no direct equivalent to .NET events in native C++:
//		public static event CharEnteredHandler CharEntered;
		/// <summary>
		/// Event raised when a key has been pressed down. May fire multiple times due to keyboard repeat.
		/// </summary>		
//C# TO C++ CONVERTER TODO TASK: There is no direct equivalent to .NET events in native C++:
//		public static event KeyEventHandler KeyDown;
		/// <summary>		
		/// Event raised when a key has been released.		
		/// </summary>		
//C# TO C++ CONVERTER TODO TASK: There is no direct equivalent to .NET events in native C++:
//		public static event KeyEventHandler KeyUp;
		typedef IntPtr ( *WndProc )( IntPtr hWnd, unsigned int msg, IntPtr wParam, IntPtr lParam );
	private:
		static bool initialized;
		static void* prevWndProc;
		static WndProc hookProcDelegate;
		static void* hIMC; //various Win32 constants that we need
		static const int GWL_WNDPROC = -4;
		static const int WM_KEYDOWN = 0x100;
		static const int WM_KEYUP = 0x101;
		static const int WM_CHAR = 0x102;
		static const int WM_IME_SETCONTEXT = 0x0281;
		static const int WM_INPUTLANGCHANGE = 0x51;
		static const int WM_GETDLGCODE = 0x87;
		static const int WM_IME_COMPOSITION = 0x10f;
		static const int DLGC_WANTALLKEYS = 4; //Win32 functions that we're using
//C# TO C++ CONVERTER NOTE: The following .NET DllImport attribute was converted using the Microsoft-specific __declspec(dllimport):
//[DllImport("Imm32.dll")]
		__declspec( dllimport ) static IntPtr ImmGetContext( IntPtr hWnd );
//C# TO C++ CONVERTER NOTE: The following .NET DllImport attribute was converted using the Microsoft-specific __declspec(dllimport):
//[DllImport("Imm32.dll")]
		__declspec( dllimport ) static IntPtr ImmAssociateContext( IntPtr hWnd, IntPtr hIMC );
//C# TO C++ CONVERTER NOTE: The following .NET DllImport attribute was converted using the Microsoft-specific __declspec(dllimport):
//[DllImport("user32.dll")]
		__declspec( dllimport ) static IntPtr CallWindowProc( IntPtr lpPrevWndFunc, IntPtr hWnd, unsigned int Msg, IntPtr wParam, IntPtr lParam );
//C# TO C++ CONVERTER NOTE: The following .NET DllImport attribute was converted using the Microsoft-specific __declspec(dllimport):
//[DllImport("user32.dll")]
		__declspec( dllimport ) static int SetWindowLong( IntPtr hWnd, int nIndex, int dwNewLong );
		/// <summary>		
		/// Initialize the TextInput with the given GameWindow.		
		/// </summary>		
		/// <param name="window">The XNA window to which text input should be linked.</param>	
	public:
		static void Initialize( const std::shared_ptr<GameWindow> &window );
	private:
		static IntPtr HookProc( IntPtr hWnd, unsigned int msg, IntPtr wParam, IntPtr lParam );
	};
}
#endif


#endif	//#ifndef TEXTINPUT
