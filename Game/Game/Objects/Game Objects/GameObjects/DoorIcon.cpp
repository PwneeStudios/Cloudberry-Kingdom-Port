#include <global_header.h>


namespace CloudberryKingdom
{

	DoorIcon::DoorIcon( int Level_Renamed )
	{
		this->Level_Renamed = Level_Renamed;
		Init( StringConverterHelper::toString( Level_Renamed ) );
	}

	DoorIcon::DoorIcon( const std::shared_ptr<BobPhsx> &PhsxType, Vector2 pos, float Scale )
	{
		Init( _T( "" ) );
		SetIcon( PhsxType );
		Pos->RelVal = pos;
		icon->SetScale( Scale );

		getCore()->DrawLayer = 2;
	}

	void DoorIcon::SetIcon( const std::shared_ptr<BobPhsx> &hero )
	{
		this->hero = hero;
		SetIcon( IconType_HERO );
	}

	void DoorIcon::SetIcon( Upgrade upgrade )
	{
		this->upgrade = upgrade;
		SetIcon( IconType_OBSTACLE );
	}

	void DoorIcon::SetIcon( IconType type )
	{
		MyPile->Clear();
		std::shared_ptr<QuadClass> Backdrop = 0;

		switch ( type )
		{
			case IconType_OBSTACLE:
				icon = ObjectIcon::CreateIcon( upgrade );
				break;

			case IconType_HERO:
				icon = hero->Icon->Clone( ObjectIcon::IconScale_NEARLY_FULL );
				break;
		}

		if ( Backdrop != 0 )
			MyPile->Add( Backdrop );
	}

	void DoorIcon::Init( const std::wstring &text )
	{
		FixedToCamera = false;
		getCore()->DrawLayer = 9;

		s = text;
		MyPile = std::make_shared<DrawPile>();

		SetIcon( IconType_NUMBER );

		//MyPile.BubbleUp(true);
		Active = true;
		Hid = false;
	}

	void DoorIcon::Kill()
	{
		Kill( true );
	}

	void DoorIcon::Kill( bool sound )
	{
		MyPile->BubbleDownAndFade( sound );
		ReleaseWhenDoneScaling = true;
	}

	void DoorIcon::MyPhsxStep()
	{
		GUI_Panel::MyPhsxStep();

		if ( !Active )
			return;
	}

	void DoorIcon::MyDraw()
	{
		//if (Level == 201)
		//    Tools.Write("");

		if ( Hid )
			return;

		GUI_Panel::MyDraw();
		if ( !IsOnScreen )
			return;

		if ( icon != 0 )
		{
			// Flip if level is flipped
			if ( getCore()->MyLevel != 0 && getCore()->MyLevel->ModZoom.X < 0 )
				icon->Flipped = true;

			icon->setPos( MyPile->FancyPos->Update() );
			icon->Draw( false );
		}
	}
}
