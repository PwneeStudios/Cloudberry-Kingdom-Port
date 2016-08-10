#include <small_header.h>
#include "Game/Objects/Game Objects/GameObjects/MultiplierUp.h"

#include "Core/Graphics/Draw/DrawPile.h"
#include "Game/Localization.h"
#include "Core/Text/EzText.h"
#include "Game/Objects/Game Objects/GameObjects/GUI_Panel.h"
#include "Game/Tools/CkColorHelper.h"
#include "Game/Tools/Resources.h"

#include "Game/Games/GameType.h"
#include "Game/Tools/Camera.h"
#include "Game/Level/Level.h"

namespace CloudberryKingdom
{

	void MultiplierUp::OnAdd()
	{
		GUI_Panel::OnAdd();

		Vector2 shift = Vector2( 0, -800 );

		// Add the text
		//text.Pos = shift;
		MyPile->setPos( shift );
		MyPile->Add( text );

		// Scale to fit
		Vector2 size = text->GetWorldSize();
		float max = MyGame->getCam()->GetWidth() - 1150;
		if ( size.X > max )
			text->setScale( text->getScale() * max / size.X );

		// Slide out
		this->SlideOut( PresetPos_BOTTOM, 0 );

		if ( Perma )
			this->SlideIn( 0 );
	}

	MultiplierUp::MultiplierUp() :
		Perma( false ),
		Count( 0 )
	{
	}
	boost::shared_ptr<MultiplierUp> MultiplierUp::MultiplierUp_Construct()
	{
		InitializeInstanceFields();
		GUI_Panel::GUI_Panel_Construct();

		Init( Vector2(), 1, false );

		return boost::static_pointer_cast<MultiplierUp>( shared_from_this() );
	}

	MultiplierUp::MultiplierUp( Vector2 shift, float scale, bool perma ) :
		Perma( false ),
		Count( 0 )
	{
	}
	boost::shared_ptr<MultiplierUp> MultiplierUp::MultiplierUp_Construct( Vector2 shift, float scale, bool perma )
	{
		InitializeInstanceFields();
		GUI_Panel::GUI_Panel_Construct();

		Init( shift, scale, perma );

		return boost::static_pointer_cast<MultiplierUp>( shared_from_this() );
	}

	void MultiplierUp::Init( Vector2 shift, float scale, bool perma )
	{
		SlideInLength = 84;

		this->Perma = perma;

		//Core.DrawLayer++; // Draw above cheering berries
		PauseOnPause = true;

		MyPile = boost::make_shared<DrawPile>();
		EnsureFancy();
		MyPile->setPos( MyPile->getPos() + shift );

		text = boost::make_shared<EzText>( Localization::Words_MultiplierIncreased, Resources::Font_Grobold42, true, true );
		text->setScale( text->getScale() * scale );

		//// Happy Blue
		//text.MyFloatColor = new bColor(26, 188, 241).ToVector4();
		//text.OutlineColor = new bColor(255, 255, 255).ToVector4();

		// Red
		CkColorHelper::_x_x_Red( text );

		text->Shadow = true;
		text->ShadowOffset = Vector2( 10.5f, 10.5f );
		text->ShadowColor = bColor( 30, 30, 30 );
	}

	void MultiplierUp::MyPhsxStep()
	{
		GUI_Panel::MyPhsxStep();

		Count++;

		// Make sure we're on top
		if ( !getCore()->Released && getCore()->MyLevel != 0 )
			getCore()->MyLevel->MoveToTopOfDrawLayer( shared_from_this() );

		// Do nothing if this is permanent
		if ( Perma )
			return;

		// Otherwise show and hide
		if ( Count == 4 )
		{
			SlideIn( 0 );
			MyPile->BubbleUp( false );
		}

		if ( Count == 180 )
		{
			SlideOut( PresetPos_BOTTOM, 160 );
			ReleaseWhenDone = true;
		}
	}

	void MultiplierUp::InitializeInstanceFields()
	{
		Count = 0;
	}
}
