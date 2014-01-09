#include <small_header.h>
#include "Game/Objects/Game Objects/GameObjects/ChapterTitle.h"

#include "Core/Graphics/Draw/DrawPile.h"
#include "Game/Localization.h"
#include "Core/Text/EzText.h"
#include "Game/Objects/Game Objects/GameObjects/GUI_Panel.h"
#include "Game/Tools/Resources.h"
#include "Game/Tools/Tools.h"

#include "Game/Level/Level.h"

#include "ChapterTitle.h"

namespace CloudberryKingdom
{

    void ChapterTitle::OnAdd()
    {
        GUI_Panel::OnAdd();

        // Add the text
        MyPile->Add( text );

        // Slide out
		//this->SlideOut( PresetPos->Bottom, 0 );
		SlideIn( 0 );
		MyPile->setAlpha( 0 );
    }

	ChapterTitle::ChapterTitle( Localization::Words word ) : GUI_Panel() { };
	boost::shared_ptr<ChapterTitle> ChapterTitle::ChapterTitle_Construct( Localization::Words word )
	{
		Count = 0;

		GUI_Panel::GUI_Panel_Construct();

		Init( Localization::WordString( word ), Vector2(0), 1.f );

		return boost::static_pointer_cast<ChapterTitle>( shared_from_this() );
	}

    void ChapterTitle::Init( std::wstring str, Vector2 shift, float scale )
    {
		//SlideInLength = 84;

        PauseOnPause = true;

        MyPile = boost::make_shared<DrawPile>();
        EnsureFancy();
        MyPile->setPos( MyPile->getPos() + shift );

        Tools::Warning(); // May be text, rather than Localization->Words
        text = boost::make_shared<EzText>( str, Resources::Font_Grobold42, true, true );
        text->_Scale *= scale;

        text->MyFloatColor = bColor( 26, 188, 241 ).ToVector4();
        text->OutlineColor = bColor( 255, 255, 255 ).ToVector4();

        text->Shadow = true;
        text->ShadowOffset = Vector2( 10.5f, 10.5f );
        text->ShadowColor = bColor( 30, 30, 30 );
    }

    void ChapterTitle::MyPhsxStep()
    {
        GUI_Panel::MyPhsxStep();

        Count++;

        // Make sure we're on top
        if (!getCore()->Released && getCore()->MyLevel != 0 )
            getCore()->MyLevel->MoveToTopOfDrawLayer( shared_from_this() );

        // Otherwise show and hide
		if ( Count == 50 )
		{
			//SlideIn();
			MyPile->FadeIn(.02f );
		}

        if ( Count == 235 )
        {
            //SlideOut( PresetPos->Bottom, 160 );
			MyPile->FadeOut(.025f );
			//ReleaseWhenDone = true;
        }

		if ( Count == 400 )
			Release();
    }

}
