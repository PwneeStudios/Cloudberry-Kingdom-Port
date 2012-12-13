#ifndef GUI_TEXTBOX
#define GUI_TEXTBOX

#include <global_header.h>

namespace CloudberryKingdom
{

	struct GUI_TextBox : public GUI_Text
	{
		/// <summary>
		/// Event handler. Activated when the the user presses Enter while the textbox has focus.
		/// </summary>
	
		std::shared_ptr<Multicaster> OnEnter;
		std::shared_ptr<Multicaster> OnEscape;

		virtual void OnAdd();

	
		virtual void ReleaseBody();

	
		bool HasFocus;
	
		void GetFocus();

		void ReleaseFocus();

	
		virtual void MyPhsxStep();

	
		bool Canceled;
	
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

	
		GUI_TextBox();
		void GUI_TextBox_Construct();

		GUI_TextBox( const std::wstring &InitialText, Vector2 pos );
		void GUI_TextBox_Construct( const std::wstring &InitialText, Vector2 pos );

		GUI_TextBox( const std::wstring &InitialText, Vector2 pos, Vector2 scale, float fontscale );
		void GUI_TextBox_Construct( const std::wstring &InitialText, Vector2 pos, Vector2 scale, float fontscale );

	
		void Init( std::wstring InitialText, Vector2 pos, Vector2 scale, float fontscale );

		int SelectIndex_Start, SelectIndex_End;

		void SelectAll();

		void Unselect();

		void Clear();

		void DeleteSelected();

		void UpdateSelectQuad();

	
		virtual std::shared_ptr<EzText> MakeText( std::wstring text, bool centered, const std::shared_ptr<EzFont> &font );

	
		int MaxLength;
		bool LimitLength;

#if defined(WINDOWS)
	
		// FIXME: Related to removal of TextInput.
		//void CharEntered( const std::shared_ptr<Object> &o, const std::shared_ptr<CharacterEventArgs> &e );

		bool IsAcceptableChar( wchar_t c );
#endif

		bool IsLetter( wchar_t c );

		/// <summary>
		/// If true the text is recentered every time it is changed
		/// </summary>
	
		bool DoRecenter;

	
		void Recenter();

#if defined(WINDOWS)
		// FIXME: Related to removal of TextInput.
		//void KeyDown( const std::shared_ptr<Object> &o, const std::shared_ptr<KeyEventArgs> &e );
#endif

		void Backspace();

	
		virtual void Enter();

	
		const int getLength() const;
	
		const std::wstring getText() const;
		void setText( const std::wstring &value );

	
		void InitializeInstanceFields();
	};

#if defined(PC_VERSION)
	struct GUI_EnterName : public GUI_TextBox
	{

		GUI_EnterName();
		void GUI_EnterName_Construct();

		virtual void Enter();

	};
#endif
}


#endif	//#ifndef GUI_TEXTBOX
