#include <global_header.h>



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
		float max = MyGame->getCam()->GetWidth() - 400;
		if ( size.X > max )
			text->setScale( text->getScale() * max / size.X );

		// Slide out
		this->SlideOut( PresetPos_BOTTOM, 0 );

		if ( Perma )
			this->SlideIn( 0 );
	}

	MultiplierUp::MultiplierUp()
	{
		InitializeInstanceFields();
		Init( Vector2::Zero, 1, false );
	}

	MultiplierUp::MultiplierUp( Vector2 shift, float scale, bool perma )
	{
		InitializeInstanceFields();
		Init( shift, scale, perma );
	}

	void MultiplierUp::Init( Vector2 shift, float scale, bool perma )
	{
		SlideInLength = 84;

		this->Perma = perma;

		//Core.DrawLayer++; // Draw above cheering berries
		PauseOnPause = true;

		MyPile = std::make_shared<DrawPile>();
		EnsureFancy();
		MyPile->setPos( MyPile->getPos() + shift );

		text = std::make_shared<EzText>( Localization::Words_MULTIPLIER_INCREASED, Resources::Font_Grobold42, true, true );
		text->setScale( text->getScale() * scale );

		//// Happy Blue
		//text.MyFloatColor = new Color(26, 188, 241).ToVector4();
		//text.OutlineColor = new Color(255, 255, 255).ToVector4();

		// Red
		CkColorHelper::_x_x_Red( text );

		text->Shadow = true;
		text->ShadowOffset = Vector2( 10.5f, 10.5f );
		text->ShadowColor = Color( 30, 30, 30 );
	}

	void MultiplierUp::MyPhsxStep()
	{
		GUI_Panel::MyPhsxStep();

		Count++;

		// Make sure we're on top
		if ( !getCore()->Released && getCore()->MyLevel != 0 )
			getCore()->MyLevel->MoveToTopOfDrawLayer(this);

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
