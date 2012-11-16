#include <global_header.h>


namespace CloudberryKingdom
{

	Region::Region( Vector2 pos, Vector2 size )
	{
		Init( pos, size );
	}

	void Region::Init( Vector2 pos, Vector2 size )
	{
		FixedToCamera = false;
		getCore()->DrawLayer = 9;

		MyPile = std::make_shared<DrawPile>();

		//QuadClass Backdrop = new QuadClass("White");
		std::shared_ptr<QuadClass> Backdrop = std::make_shared<QuadClass>( _T( "dungeon_smoke_thick" ) );
		MyPile->Add( Backdrop );

		//Backdrop.Quad.SetColor(Color.Black);
		Backdrop->setSize( size );

		//MyPile.Pos = pos + new Vector2(0, 1500);
		float shift = -1250;
		MyPile->setPos( pos + Vector2( 0, shift ) );

		Box = std::make_shared<AABox>( pos + Vector2( 0, shift - 2430 ), size );

		Active = true;
		Hid = false;
	}

	void Region::MyPhsxStep()
	{
		if ( AttemptToReAdd() )
			return;

		GUI_Panel::MyPhsxStep();

		if ( !Active )
			return;

		for ( std::vector<Bob*>::const_iterator bob = getCore()->MyLevel->Bobs.begin(); bob != getCore()->MyLevel->Bobs.end(); ++bob )
			if ( ( *bob )->getCanDie() && Phsx::BoxBoxOverlap((*bob)->Box, Box) )
				if ( AttachedDoor != 0 )
				{
					Active = false;
					AttachedDoor->HaveBobUseDoor( *bob );
				}
	}

	bool Region::OnScreen()
	{
		//return base.OnScreen();
		return true;
	}

	void Region::MyDraw()
	{
		if ( AttemptToReAdd() )
			return;

		GUI_Panel::MyDraw();
	}
}
