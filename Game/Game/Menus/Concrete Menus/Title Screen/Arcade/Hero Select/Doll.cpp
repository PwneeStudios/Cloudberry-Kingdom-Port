#include <global_header.h>

#if ! defined(PC_VERSION) && (defined(XBOX) || defined(XBOX_SIGNIN))

#endif

namespace CloudberryKingdom
{

	HeroDoll::HeroDoll( int Control ) : CkBaseMenu( false )
	{
		this->setControl( Control );

		Constructor();
	}

	void HeroDoll::ReleaseBody()
	{
		CkBaseMenu::ReleaseBody();

		if ( MyDoll != 0 )
		{
			MyDoll->getCore()->MyLevel->Bobs.Remove(MyDoll);
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

		MyPile = std::make_shared<DrawPile>();
		EnsureFancy();
	}

	void HeroDoll::OnAdd()
	{
		 CkBaseMenu::OnAdd();

		MakeHeroDoll( BobPhsxNormal::getInstance() );
	}

	void HeroDoll::MakeHeroDoll( const std::shared_ptr<BobPhsx> &hero )
	{
//C# TO C++ CONVERTER TODO TASK: There is no equivalent to implicit typing in C++ unless the C++11 inferred typing option is selected:
		var current_bob = MyGame->MyLevel->Bobs.empty() ? 0 : MyGame->MyLevel->Bobs[ 0 ];
		std::shared_ptr<CloudberryKingdom::FancyVector2> current_pos = current_bob == 0 ? Vector2::Zero : current_bob->Pos;

		// Grab cape
		std::shared_ptr<Cape> PrevCape = 0;
		if ( current_bob != 0 )
		{
			PrevCape = current_bob->MyCape;
			current_bob->MyCape = 0;
		}

		// Get rid of old bobs.
//C# TO C++ CONVERTER TODO TASK: There is no equivalent to implicit typing in C++ unless the C++11 inferred typing option is selected:
		for ( std::vector<Bob*>::const_iterator bob = MyGame->MyLevel->Bobs.begin(); bob != MyGame->MyLevel->Bobs.end(); ++bob )
			( *bob )->Release();
		MyGame->MyLevel->Bobs.clear();

		// Get an existing player
		player = PlayerManager::Players[ PlayerManager::GetFirstPlayer() ];

		// Make doll
		MyDoll = std::make_shared<Bob>( hero, false );
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

		std::shared_ptr<BobPhsxCharSelect> HeroDollPhsx = dynamic_cast<BobPhsxCharSelect*>( MyDoll->MyPhsx );

		MyDoll->CapeWind = Cape::SineWind( Vector2( -1.25f, -.1f ),.5f,.05f, Tools::t ) *.7f;
		MyDoll->MyPhsx->OnGround = true;
		MyDoll->MyPhsx->setVel( Vector2::Zero );
	}

	void HeroDoll::DrawBob()
	{
		std::shared_ptr<Camera> cam = Tools::CurLevel->getMainCamera();
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
