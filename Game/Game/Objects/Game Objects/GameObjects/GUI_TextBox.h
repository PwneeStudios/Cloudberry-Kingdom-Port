#ifndef GUI_TEXTBOX
#define GUI_TEXTBOX

#include <global_header.h>

namespace CloudberryKingdom
{
	class Multicaster;
}

namespace CloudberryKingdom
{
	class QuadClass;
}

namespace CloudberryKingdom
{
	class EzText;
}

namespace CloudberryKingdom
{
	class EzFont;
}

namespace CloudberryKingdom
{
	class CharacterEventArgs;
}

namespace CloudberryKingdom
{
	class KeyEventArgs;
}








namespace CloudberryKingdom
{
#if defined(PC_VERSION)
	class GUI_EnterName : public GUI_TextBox
	{
	public:
		GUI_EnterName();

		virtual void Enter();
	};
#endif

	class GUI_TextBox : public GUI_Text
	{
		/// <summary>
		/// Event handler. Activated when the the user presses Enter while the textbox has focus.
		/// </summary>
	public:
		std::shared_ptr<Multicaster> OnEnter;
		std::shared_ptr<Multicaster> OnEscape;

		virtual void OnAdd();

	protected:
		virtual void ReleaseBody();

	private:
		bool HasFocus;
	public:
		void GetFocus();

		void ReleaseFocus();

	protected:
		virtual void MyPhsxStep();

	public:
		bool Canceled;
	private:
		void Cancel();

		void GamepadInteract();

#if defined(WINDOWS)
		void Paste();

		void Copy();
#endif

		wchar_t IncrChar( wchar_t c );
		wchar_t DecrChar( wchar_t c );

		std::shared_ptr<QuadClass> Backdrop, SelectQuad;
		std::shared_ptr<EzText> Caret;

	public:
		GUI_TextBox( const std::wstring &InitialText, Vector2 pos );

		GUI_TextBox( const std::wstring &InitialText, Vector2 pos, Vector2 scale, float fontscale );

	private:
		void Init( const std::wstring &InitialText, Vector2 pos, Vector2 scale, float fontscale );

		int SelectIndex_Start, SelectIndex_End;

		void SelectAll();

		void Unselect();

		void Clear();

		void DeleteSelected();

		void UpdateSelectQuad();

	protected:
		virtual std::shared_ptr<EzText> MakeText( const std::wstring &text, bool centered, const std::shared_ptr<EzFont> &font );

	public:
		int MaxLength;
		bool LimitLength;

#if defined(WINDOWS)
	private:
		void CharEntered( const std::shared_ptr<Object> &o, const std::shared_ptr<CharacterEventArgs> &e );

		bool IsAcceptableChar( wchar_t c );
#endif

		bool IsLetter( wchar_t c );

		/// <summary>
		/// If true the text is recentered every time it is changed
		/// </summary>
	public:
		bool DoRecenter;

	private:
		void Recenter();

#if defined(WINDOWS)
		void KeyDown( const std::shared_ptr<Object> &o, const std::shared_ptr<KeyEventArgs> &e );
#endif

		void Backspace();

	public:
		virtual void Enter();

	protected:
		const int &getLength() const;
	public:
		const std::wstring &getText() const;
		void setText( const std::wstring &value );

	private:
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef GUI_TEXTBOX
