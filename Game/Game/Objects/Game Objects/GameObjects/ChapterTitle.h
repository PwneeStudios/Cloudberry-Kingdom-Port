#ifndef CHAPTERTITLE
#define CHAPTERTITLE

#include <small_header.h>

//#include "Core/Graphics/Draw/DrawPile.h"
#include "Game/Localization.h"
//#include "Core/Text/EzText.h"
#include "Game/Objects/Game Objects/GameObjects/GUI_Panel.h"
//#include "Game/Tools/Resources.h"
//#include "Game/Tools/Tools.h"


namespace CloudberryKingdom
{

	struct ChapterTitle : public GUI_Panel
	{
	
		virtual ~ChapterTitle()
		{
#ifdef BOOST_BIN
			OnDestructor( "ChapterTitle" );
#endif
		}


		void OnAdd();

		boost::shared_ptr<EzText> text;

		ChapterTitle( Localization::Words word );
		boost::shared_ptr<ChapterTitle> ChapterTitle_Construct( Localization::Words word );

		void Init( std::wstring str, Vector2 shift, float scale );

        int Count;
        void MyPhsxStep();

	};

}


#endif	//#ifndef CHAPTERTITLE
