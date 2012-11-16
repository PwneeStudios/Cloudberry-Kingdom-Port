#include <global_header.h>

#if defined(WINDOWS)
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
#endif
#if defined(WINDOWS)
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Runtime::InteropServices;
#endif
#if defined(WINDOWS)
using namespace Microsoft::Xna::Framework;
#endif
#if defined(WINDOWS)
using namespace Microsoft::Xna::Framework::Input;
#endif

namespace CloudberryKingdom
{

#if defined(WINDOWS)
	CharacterEventArgs::CharacterEventArgs( wchar_t character, int lParam ) : character( character ), lParam( lParam )
	{
	}
#endif

#if defined(WINDOWS)
	const wchar_t &CharacterEventArgs::getCharacter() const
	{
		return character;
	}
#endif

#if defined(WINDOWS)
	const int &CharacterEventArgs::getParam() const
	{
		return lParam;
	}
#endif

#if defined(WINDOWS)
	const int &CharacterEventArgs::getRepeatCount() const
	{
		return lParam & 0xffff;
	}
#endif

#if defined(WINDOWS)
	const bool &CharacterEventArgs::getExtendedKey() const
	{
		return ( lParam & ( 1 << 24 ) ) > 0;
	}
#endif

#if defined(WINDOWS)
	const bool &CharacterEventArgs::getAltPressed() const
	{
		return ( lParam & ( 1 << 29 ) ) > 0;
	}
#endif

#if defined(WINDOWS)
	const bool &CharacterEventArgs::getPreviousState() const
	{
		return ( lParam & ( 1 << 30 ) ) > 0;
	}
#endif

#if defined(WINDOWS)
	const bool &CharacterEventArgs::getTransitionState() const
	{
		return ( lParam & ( 1 << 31 ) ) > 0;
	}
#endif

#if defined(WINDOWS)
	KeyEventArgs::KeyEventArgs( Keys keyCode )
	{
		this->keyCode = keyCode;
	}
#endif

#if defined(WINDOWS)
	const Microsoft::Xna::Framework::Input::Keys &KeyEventArgs::getKeyCode() const
	{
		return keyCode;
	}
#endif

#if defined(WINDOWS)
bool EventInput::initialized = false;
#endif

#if defined(WINDOWS)
IntPtr EventInput::prevWndProc = 0;
#endif

#if defined(WINDOWS)
WndProc EventInput::hookProcDelegate = 0;
#endif

#if defined(WINDOWS)
IntPtr EventInput::hIMC = 0;
#endif

#if defined(WINDOWS)
	void EventInput::Initialize( const std::shared_ptr<GameWindow> &window )
	{
		if ( initialized )
			throw InvalidOperationException( _T( "TextInput.Initialize can only be called once!" ) );
		hookProcDelegate = std::make_shared<WndProc>( &HookProc );
		prevWndProc = static_cast<void*>( SetWindowLong( window->Handle, GWL_WNDPROC, static_cast<int>( Marshal::GetFunctionPointerForDelegate( hookProcDelegate ) ) ) );
		hIMC = ImmGetContext( window->Handle );
		initialized = true;
	}
#endif

#if defined(WINDOWS)
	IntPtr EventInput::HookProc( IntPtr hWnd, unsigned int msg, IntPtr wParam, IntPtr lParam )
	{
		void* returnCode = CallWindowProc( prevWndProc, hWnd, msg, wParam, lParam );
		switch ( msg )
		{
			case WM_GETDLGCODE:
				returnCode = static_cast<void*>( returnCode.ToInt32() | DLGC_WANTALLKEYS );
				break;
			case WM_KEYDOWN:
				KeyDown( 0, std::make_shared<KeyEventArgs>( static_cast<Keys>( wParam ) ) );
				break;
			case WM_KEYUP:
				KeyUp( 0, std::make_shared<KeyEventArgs>( static_cast<Keys>( wParam ) ) );
				break;
			case WM_CHAR:
				CharEntered( 0, std::make_shared<CharacterEventArgs>( static_cast<wchar_t>( wParam ), lParam.ToInt32() ) );
				break;
			case WM_IME_SETCONTEXT:
				if ( wParam.ToInt32() == 1 )
					ImmAssociateContext( hWnd, hIMC );
				break;
			case WM_INPUTLANGCHANGE:
				ImmAssociateContext( hWnd, hIMC );
				returnCode = static_cast<void*>( 1 );
				break;
		}
		return returnCode;
	}
#endif
}
