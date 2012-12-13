#ifndef GUI_TEXT
#define GUI_TEXT

#include <global_header.h>

namespace CloudberryKingdom
{
	struct GUI_Text : public GUI_Panel
	{
	
		enum Style
		{
			Style_BUBBLE,
			Style_FADE,
			Style_NONE
		};
	
		Style MyStyle;

		std::shared_ptr<EzText> MyText;

		static std::shared_ptr<GUI_Text> SimpleTitle( Localization::Words word );
		static std::shared_ptr<GUI_Text> SimpleTitle( Localization::Words word, Style style );

		GUI_Text();
		void GUI_Text_Construct();

		GUI_Text( Localization::Words word, Vector2 pos );
		void GUI_Text_Construct( Localization::Words word, Vector2 pos );

		GUI_Text( Localization::Words word, Vector2 pos, bool centered );
		void GUI_Text_Construct( Localization::Words word, Vector2 pos, bool centered );

		GUI_Text( Localization::Words word, Vector2 pos, Style style );
		void GUI_Text_Construct( Localization::Words word, Vector2 pos, Style style );

		GUI_Text( const std::wstring &text, Vector2 pos );
		void GUI_Text_Construct( const std::wstring &text, Vector2 pos );

		GUI_Text( const std::wstring &text, Vector2 pos, bool centered );
		void GUI_Text_Construct( const std::wstring &text, Vector2 pos, bool centered );

		GUI_Text( const std::wstring &text, Vector2 pos, bool centered, const std::shared_ptr<EzFont> &font );
		void GUI_Text_Construct( const std::wstring &text, Vector2 pos, bool centered, const std::shared_ptr<EzFont> &font );

		void Init( Localization::Words word, Vector2 pos, bool centered, Style style, const std::shared_ptr<EzFont> &font );

		void Init( const std::wstring &text, Vector2 pos, bool centered, Style style, const std::shared_ptr<EzFont> &font );

	
		virtual std::shared_ptr<EzText> MakeText( Localization::Words word, bool centered, const std::shared_ptr<EzFont> &font );

		virtual std::shared_ptr<EzText> MakeText( const std::wstring &text, bool centered, const std::shared_ptr<EzFont> &font );

	
		void Kill();
		void Kill( bool sound );

		/// <summary>
		/// When true the position is not modified by the phsx update.
		/// </summary>
		bool NoPosMod; //false;

//C# TO C++ CONVERTER NOTE: The variable Oscillate was renamed since it is named the same as a user-defined type:
		bool Oscillate_Renamed;
	
		float OscillationHeight; // 4.65f;
		float OscillationSpeed;
		virtual void MyPhsxStep();

		virtual void MyDraw();

	
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef GUI_TEXT
