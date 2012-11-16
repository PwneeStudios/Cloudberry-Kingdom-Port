#include <global_header.h>

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;

#if ! defined(PC_VERSION) && (defined(XBOX) || defined(XBOX_SIGNIN))

#endif

namespace CloudberryKingdom
{

	Doll::Doll( int Control, const std::shared_ptr<CharacterSelect> &MyCharacterSelect ) : CkBaseMenu( false )
	{
		InitializeInstanceFields();
		this->Tags += Tag_CHAR_SELECT;
		this->setControl( Control );
		this->MyCharacterSelect = MyCharacterSelect;

		Constructor();
	}

	void Doll::ReleaseBody()
	{
		CkBaseMenu::ReleaseBody();

		MyCharacterSelect.reset();

		if ( MyDoll != 0 )
		{
			MyDoll->getCore()->MyLevel->Bobs.Remove(MyDoll);
			MyDoll->Release();
			MyDoll.reset();
		}
	}

	void Doll::Init()
	{
		CkBaseMenu::Init();

		SlideInLength = 0;
		SlideOutLength = 0;
		CallDelay = 0;
		ReturnToCallerDelay = 0;

		MakeDoll();
	}

	void Doll::MakeDoll()
	{
		MyPile = std::make_shared<DrawPile>();
		EnsureFancy();

		MyDoll = std::make_shared<Bob>( BobPhsxNormal::getInstance(), false );
		MyDoll->MyPlayerIndex = MyCharacterSelect->getPlayer()->MyPlayerIndex;
		MyDoll->MyPiece = Tools::CurLevel->CurPiece;
		MyDoll->MyPieceIndex = MyCharacterSelect->PlayerIndex;
		MyDoll->CharacterSelect_Renamed = true;
		MyDoll->CharacterSelect2 = true;
		MyDoll->AffectsCamera = false;
		MyDoll->Immortal = true;
		MyDoll->CompControl = true;
		MyDoll->DrawWithLevel = false;

		PhsxData data = PhsxData();
		MyDoll->Init( false, data, Tools::CurGameData );

		MyDoll->SetColorScheme( MyCharacterSelect->getPlayer()->ColorScheme_Renamed );

		MyDoll->PlayerObject->EnqueueAnimation( _T( "Stand" ), 0, true, true );
		MyDoll->PlayerObject->DequeueTransfers();

		Tools::CurLevel->AddBob( MyDoll );
	}

	void Doll::UpdateColorScheme()
	{
		MyDoll->SetColorScheme( MyCharacterSelect->getPlayer()->ColorScheme_Renamed );
	}

	int Doll::FindClrIndex( std::vector<MenuListItem*> &list, ClrTextFx clr )
	{
		int Index = 0;
//C# TO C++ CONVERTER TODO TASK: There is no equivalent to implicit typing in C++ unless the C++11 inferred typing option is selected:
		for ( std::vector<MenuListItem*>::const_iterator item = list.begin(); item != list.end(); ++item )
		{
			if ( static_cast<ClrTextFx>( ( *item )->obj ) == clr )
				return Index;
			Index++;
		}
		return 0;
	}

	int Doll::FindHatIndex( std::vector<Hat*> &list, const std::shared_ptr<Hat> &hat )
	{
		int Index = 0;
//C# TO C++ CONVERTER TODO TASK: There is no equivalent to implicit typing in C++ unless the C++11 inferred typing option is selected:
		for ( std::vector<Hat*>::const_iterator item = list.begin(); item != list.end(); ++item )
		{
			if ( *item == hat )
				return Index;
			Index++;
		}
		return 0;
	}

	void Doll::GetIndices( std::vector<int> ItemIndex, std::vector<std::vector<MenuListItem*>&> ItemList )
	{
		ItemIndex[ 0 ] = FindClrIndex( ItemList[ 0 ], MyDoll->MyColorScheme.SkinColor );

		ItemIndex[ 1 ] = FindHatIndex( ColorSchemeManager::BeardInfo, MyDoll->MyColorScheme.BeardData );
		ItemIndex[ 2 ] = FindHatIndex( ColorSchemeManager::HatInfo, MyDoll->MyColorScheme.HatData );

		ItemIndex[ 3 ] = FindClrIndex( ItemList[ 3 ], MyDoll->MyColorScheme.CapeColor );
		ItemIndex[ 4 ] = FindClrIndex( ItemList[ 4 ], MyDoll->MyColorScheme.CapeOutlineColor );

		for ( int i = 0; i < 5; i++ )
			if ( ItemIndex[ i ] < 0 )
				ItemIndex[ i ] = 0;
	}

	void Doll::MyPhsxStep()
	{
		CkBaseMenu::MyPhsxStep();

		std::shared_ptr<BobPhsxCharSelect> DollPhsx = dynamic_cast<BobPhsxCharSelect*>( MyDoll->MyPhsx );

		MyDoll->CapeWind = Cape::SineWind( Vector2( -1.25f, -.1f ),.5f,.05f, Tools::t ) *.7f;
		MyDoll->MyPhsx->OnGround = true;
	}

	void Doll::DrawBob()
	{
		if ( ShowBob )
		{
			MyPile->setPos( Vector2( -10, 260 ) );

			Vector2 Pos = CharacterSelect::Centers[ getControl() ] + MyPile->getPos();
			Vector2 CurDollPos = Pos / ( CharacterSelectManager::BobZoom / CharacterSelectManager::ZoomMod ) + Tools::CurGameData->getCamPos();

			MyDoll->Move( CurDollPos - MyDoll->getCore()->Data.Position );
			MyDoll->Draw();
		}
	}

	void Doll::InitializeInstanceFields()
	{
		ShowBob = false;
	}
}
