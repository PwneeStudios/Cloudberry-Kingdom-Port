#include <small_header.h>
#include "Game/Menus/Concrete Menus/Title Screen/Arcade/Hero Select/HeroDoll.h"

#include "Core/PhsxData.h"
#include "Core/Graphics/Draw/DrawPile.h"
#include "Game/Menus/CkBaseMenu.h"
#include "Game/Player/PlayerManager.h"
#include "Game/Player/Hero Physics/Base.h"
#include "Game/Objects/Bob/Bob.h"
#include "Game/Player/Cape.h"
#include "Game/Player/PlayerData.h"
#include "Game/Player/Hero Physics/Normal.h"
#include "Game/Player/Hero Physics/BobPhsxCharSelect.h"
#include "Game/Tools/Camera.h"
#include "Game/Tools/Tools.h"

#include "Game/Level/Level.h"
#include "Game/Games/GameType.h"

#include "Hacks/List.h"

#include <MasterHack.h>

namespace CloudberryKingdom
{

	HeroDoll::HeroDoll( int Control ) : CkBaseMenu( false ) { }
	boost::shared_ptr<HeroDoll> HeroDoll::HeroDoll_Construct( int Control )
	{
		CkBaseMenu::CkBaseMenu_Construct( false );

		this->setControl( Control );

		Constructor();

		return boost::static_pointer_cast<HeroDoll>( shared_from_this() );
	}

	void HeroDoll::ReleaseBody()
	{
		CkBaseMenu::ReleaseBody();

		if ( MyDoll != 0 )
		{
			Remove( MyDoll->getCore()->MyLevel->Bobs, MyDoll );
			MyDoll->Release();
			MyDoll.reset();
		}
	}

	void HeroDoll::Init()
	{
		CkBaseMenu::Init();

		getCore()->DrawLayer++;

		SlideInLength = 0;
		SlideOutLength = 0;
		CallDelay = 0;
		ReturnToCallerDelay = 0;

		MyPile = boost::make_shared<DrawPile>();
		EnsureFancy();
	}

	void HeroDoll::OnAdd()
	{
		 CkBaseMenu::OnAdd();

		MakeHeroDoll( BobPhsxNormal::getInstance() );
	}

	void HeroDoll::MakeHeroDoll( const boost::shared_ptr<BobPhsx> &hero )
	{
		boost::shared_ptr<Bob> current_bob = MyGame->MyLevel->Bobs.empty() ? 0 : MyGame->MyLevel->Bobs[ 0 ];
		Vector2 current_pos = current_bob == 0 ? Vector2() : current_bob->getPos();

		// Grab cape
		boost::shared_ptr<Cape> PrevCape = 0;
		if ( current_bob != 0 )
		{
			PrevCape = current_bob->MyCape;
			current_bob->MyCape = 0;
		}

		// Get rid of old bobs.
		for ( BobVec::const_iterator bob = MyGame->MyLevel->Bobs.begin(); bob != MyGame->MyLevel->Bobs.end(); ++bob )
			( *bob )->Release();
		MyGame->MyLevel->Bobs.clear();

		// Get an existing player
		player = PlayerManager::Players[ PlayerManager::GetFirstPlayer() ];

		// Make doll
		MyDoll = boost::make_shared<Bob>( hero, false );
		Bob_PostConstruct( MyDoll, hero, false );
		MyDoll->MyPlayerIndex = player->MyPlayerIndex;
		MyDoll->MyPiece = Tools::CurLevel->CurPiece;
		MyDoll->CharacterSelect_Renamed = true;
		MyDoll->CharacterSelect2 = true;
		MyDoll->AffectsCamera = false;
		MyDoll->Immortal = true;
		MyDoll->CompControl = true;
		MyDoll->DrawWithLevel = false;

		PhsxData data = PhsxData();
		MyDoll->Init( false, data, Tools::CurGameData );

		MyDoll->SetHeroPhsx( hero );
		MyDoll->MyPhsx->DollInitialize();

		MyDoll->Move( current_pos - MyDoll->getPos() );
		MyGame->MyLevel->AddBob( MyDoll );

		for ( int i = 0; i < 20; i++ )
		{
			float Zoom = 2 * MyDoll->MyPhsx->DollCamZoomMod;
			Vector2 Pos = MyPile->getPos();
			Vector2 CurHeroDollPos = Pos / Zoom + Tools::CurGameData->getCamPos();
			MyDoll->Move( CurHeroDollPos - MyDoll->getPos() );

			MyDoll->AnimAndUpdate();
			MyDoll->PhsxStep();
			MyDoll->PhsxStep2();
			MyPhsxStep();
		}


		// Swap out old cape for the new one.
		//if (MyDoll.MyCape != null && PrevCape != null && MyDoll.MyCape.MyType == PrevCape.MyType)
		//{
		//    MyDoll.MyCape.Copy(PrevCape);
		//    PrevCape.Release();
		//}
		//else
		{
			if ( PrevCape != 0 )
				PrevCape->Release();
		}

		UpdateColorScheme();

		SetPos();
	}

	void HeroDoll::SetPos()
	{
		MyPile->setPos( Vector2( -983.3336f, 433.3333f ) );
	}

	void HeroDoll::SetPhsx()
	{
		//MyDoll.PlayerObject.EnqueueAnimation("Stand", 0, true, true);
		//MyDoll.PlayerObject.DequeueTransfers();
	}

	void HeroDoll::UpdateColorScheme()
	{
		MyDoll->SetColorScheme( player->ColorScheme_Renamed );
	}

	void HeroDoll::MyPhsxStep()
	{
		CkBaseMenu::MyPhsxStep();

		boost::shared_ptr<BobPhsxCharSelect> HeroDollPhsx = boost::dynamic_pointer_cast<BobPhsxCharSelect>( MyDoll->MyPhsx );

		MyDoll->CapeWind = Cape::SineWind( Vector2( -1.25f, -.1f ),.5f,.05f, Tools::t ) *.7f;
		MyDoll->MyPhsx->OnGround = true;
		MyDoll->MyPhsx->setVel( Vector2() );
	}

	void HeroDoll::DrawBob()
	{
		boost::shared_ptr<Camera> cam = Tools::CurLevel->getMainCamera();
		Vector2 HoldZoom = cam->getZoom();

		cam->FancyPos->AbsVal = cam->FancyPos->RelVal = cam->Data.Position;

		// Draw the stickmen
		float Zoom = 2 * MyDoll->MyPhsx->DollCamZoomMod;
		cam->SetVertexZoom( Vector2( Zoom ) );

		Vector2 Pos = MyPile->getPos() + MyDoll->MyPhsx->HeroDollShift;
		Vector2 CurHeroDollPos = Pos / Zoom + Tools::CurGameData->getCamPos();

		MyDoll->Move( CurHeroDollPos - MyDoll->getPos() );
		MyDoll->Draw();

		Tools::QDrawer->Flush();

		cam->setZoom( HoldZoom );
		cam->SetVertexCamera();
	}

	void HeroDoll::MyDraw()
	{
		CkBaseMenu::MyDraw();

		if ( !getCore()->Show || getCore()->Released || Hid )
			return;

		DrawBob();
	}
}
