#include <small_header.h>
#include "Game/Objects/Game Objects/GameObjects/DoorIcon.h"

#include "Core/Graphics/Draw/DrawPile.h"
#include "Core/Graphics/Draw/Quads/QuadClass.h"
#include "Game/Objects/Game Objects/GameObjects/GUI_Panel.h"
#include "Game/Player/Hero Physics/Base.h"
#include "Game/Objects/AutoGen.h"
#include "Game/Objects/Icon.h"
#include "Game/Objects/In Game Objects/Grab/MakeData.h"
#include "Game/Level/Level.h"


#include "Hacks/Queue.h"

namespace CloudberryKingdom
{

	DoorIcon::DoorIcon( int Level_Renamed ) :
		upgrade( static_cast<Upgrade>( 0 ) ),
		Level_Renamed( 0 )
	{
	}
	boost::shared_ptr<DoorIcon> DoorIcon::DoorIcon_Construct( int Level_Renamed )
	{
		GUI_Panel::GUI_Panel_Construct();

		this->Level_Renamed = Level_Renamed;
		Init( StringConverterHelper::toString( Level_Renamed ) );

		return boost::static_pointer_cast<DoorIcon>( shared_from_this() );
	}

	DoorIcon::DoorIcon( const boost::shared_ptr<BobPhsx> &PhsxType, Vector2 pos, float Scale ) :
		upgrade( static_cast<Upgrade>( 0 ) ),
		Level_Renamed( 0 )
	{
	}
	boost::shared_ptr<DoorIcon> DoorIcon::DoorIcon_Construct( const boost::shared_ptr<BobPhsx> &PhsxType, Vector2 pos, float Scale )
	{
		GUI_Panel::GUI_Panel_Construct();

		Init( std::wstring( L"" ) );
		SetIcon( PhsxType );
		Pos->RelVal = pos;
		icon->SetScale( Scale );

		getCore()->DrawLayer = 2;

		return boost::static_pointer_cast<DoorIcon>( shared_from_this() );
	}

	void DoorIcon::SetIcon( const boost::shared_ptr<BobPhsx> &hero )
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
		boost::shared_ptr<QuadClass> Backdrop = 0;

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
		MyPile = boost::make_shared<DrawPile>();

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
		//    Tools::Write("");

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
