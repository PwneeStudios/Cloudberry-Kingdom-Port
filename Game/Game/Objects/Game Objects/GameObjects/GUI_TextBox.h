#ifndef GUI_TEXTBOX
#define GUI_TEXTBOX

#include <global_header.h>

namespace CloudberryKingdom
{

	struct GUI_TextBox : public GUI_Text
	{

		virtual ~GUI_TextBox()
		{
#ifdef BOOST_BIN
			OnDestructor( "GUI_TextBox" );
#endif
		}


		/// <summary>
		/// Event handler. Activated when the the user presses Enter while the textbox has focus.
		/// </summary>
		boost::shared_ptr<Multicaster> OnEnter;
		boost::shared_ptr<Multicaster> OnEscape;

		virtual void OnAdd();

	
		virtual void ReleaseBody();

	
		bool HasFocus;
	
		void GetFocus();

		void ReleaseFocus();

		void PosCaret();
		void ScaleTextToFit();
	
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

		boost::shared_ptr<QuadClass> Backdrop, SelectQuad;
		boost::shared_ptr<EzText> Caret;

	
		GUI_TextBox();
		boost::shared_ptr<GUI_TextBox> GUI_TextBox_Construct();

		GUI_TextBox( const std::wstring &InitialText, Vector2 pos );
		boost::shared_ptr<GUI_TextBox> GUI_TextBox_Construct( const std::wstring &InitialText, Vector2 pos );

		GUI_TextBox( const std::wstring &InitialText, Vector2 pos, Vector2 scale, float fontscale );
		boost::shared_ptr<GUI_TextBox> GUI_TextBox_Construct( const std::wstring &InitialText, Vector2 pos, Vector2 scale, float fontscale );

	
		void Init( std::wstring InitialText, Vector2 pos, Vector2 scale, float fontscale );

		int SelectIndex_Start, SelectIndex_End;

		void SelectAll();

		void Unselect();

		void Clear();

		void DeleteSelected();

		void UpdateSelectQuad();

	
		virtual boost::shared_ptr<EzText> MakeText( std::wstring text, bool centered, const boost::shared_ptr<EzFont> &font );

	
		int MaxLength;
		bool LimitLength;

#if defined(WINDOWS)
	
		// FIXME: Related to removal of TextInput.
		//void CharEntered( const boost::shared_ptr<Object> &o, const boost::shared_ptr<CharacterEventArgs> &e );

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
		//void KeyDown( const boost::shared_ptr<Object> &o, const boost::shared_ptr<KeyEventArgs> &e );
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

		virtual ~GUI_EnterName()
		{
#ifdef BOOST_BIN
			OnDestructor( "GUI_EnterName" );
#endif
		}


		GUI_EnterName();
		boost::shared_ptr<GUI_EnterName> GUI_EnterName_Construct();

		virtual void Enter();

	};
#endif
}


#endif	//#ifndef GUI_TEXTBOX
