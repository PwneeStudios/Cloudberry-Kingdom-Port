#ifndef GUI_TEXT
#define GUI_TEXT

#include "GUI_Panel.h"
#include "../Game/Objects/In Game Objects/Blocks/Ceiling__Auto.h"
#include "../Game/Objects/In Game Objects/Obstacles/BlockEmitter__Auto.h"
#include "../Core/Text/EzText.h"
#include "../Game/Localization.h"
#include "../Game/Tools/Oscillate.h"
#include <string>
#include <cmath>

namespace CloudberryKingdom
{
	class EzText;
}

namespace CloudberryKingdom
{
	class EzFont;
}


using namespace Microsoft::Xna::Framework;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;

namespace CloudberryKingdom
{
	class GUI_Text : public GUI_Panel
	{
	public:
		enum Style
		{
			Style_BUBBLE,
			Style_FADE,
			Style_NONE
		};
	public:
		Style MyStyle;

		std::shared_ptr<EzText> MyText;

		static std::shared_ptr<GUI_Text> SimpleTitle( Localization::Words word );
		static std::shared_ptr<GUI_Text> SimpleTitle( Localization::Words word, Style style );

		GUI_Text( Localization::Words word, Vector2 pos );

		GUI_Text( Localization::Words word, Vector2 pos, bool centered );

		GUI_Text( Localization::Words word, Vector2 pos, Style style );

		GUI_Text( const std::wstring &text, Vector2 pos );

		GUI_Text( const std::wstring &text, Vector2 pos, bool centered );

		GUI_Text( const std::wstring &text, Vector2 pos, bool centered, const std::shared_ptr<EzFont> &font );

		void Init( Localization::Words word, Vector2 pos, bool centered, Style style, const std::shared_ptr<EzFont> &font );

		void Init( const std::wstring &text, Vector2 pos, bool centered, Style style, const std::shared_ptr<EzFont> &font );

	protected:
		virtual std::shared_ptr<EzText> MakeText( Localization::Words word, bool centered, const std::shared_ptr<EzFont> &font );

		virtual std::shared_ptr<EzText> MakeText( const std::wstring &text, bool centered, const std::shared_ptr<EzFont> &font );

	public:
		void Kill();
		void Kill( bool sound );

		/// <summary>
		/// When true the position is not modified by the phsx update.
		/// </summary>
		bool NoPosMod; //false;

//C# TO C++ CONVERTER NOTE: The variable Oscillate was renamed since it is named the same as a user-defined type:
		bool Oscillate_Renamed;
	protected:
		float OscillationHeight; // 4.65f;
		float OscillationSpeed;
		virtual void MyPhsxStep();

		virtual void MyDraw();

	private:
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef GUI_TEXT
