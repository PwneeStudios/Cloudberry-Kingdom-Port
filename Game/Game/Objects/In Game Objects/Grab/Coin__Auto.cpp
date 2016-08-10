#include <small_header.h>
#include "Game/Objects/In Game Objects/Grab/Coin__Auto.h"

#include "Game/Level/Level.h"
#include "Core/Tools/Random.h"
#include "Game/Tools/Recycler.h"
#include "Game/Objects/In Game Objects/Grab/Coin.h"
#include "Game/Objects/Bob/Bob.h"
#include "Game/Collision Detection/AABox.h"
#include "Game/Tools/Camera.h"

#include "Hacks/List.h"

namespace CloudberryKingdom
{

	Vector2 Coin_Parameters::SnapToGrid( Vector2 pos )
	{
		pos.X = static_cast<int>( pos.X / GridSpacing.X ) * GridSpacing.X;
		pos.Y = static_cast<int>( pos.Y / GridSpacing.Y ) * GridSpacing.Y;

		return pos;
	}

	bool Coin_Parameters::Regular_ReadyToPlace( const boost::shared_ptr<Level> &level, const boost::shared_ptr<Bob> &bob, int Step )
	{
		return ( Step % Regular_Period == Regular_Offset && Step / 50 % Regular_Period2 == Regular_Offset2 && ( Step / 90 ) % level->Bobs.size() == IndexOf( level->Bobs, bob) );
	}

	void Coin_Parameters::SetParameters( const boost::shared_ptr<PieceSeedData> &PieceSeed, const boost::shared_ptr<Level> &level )
	{
		AutoGen_Parameters::SetParameters( PieceSeed, level );

		MinDist = Param( PieceSeed );
		MinDist.SetVal( 200 );

		PlaceDelay = Param( PieceSeed );
		PlaceDelay.SetVal( 15 );

		StartFrame = 60;

		Grid = true;

		Regular_Period = 15;
		Regular_Offset = level->getRnd()->RndInt(0, Regular_Period - 1);
		Regular_Period2 = 2;
		Regular_Offset2 = level->getRnd()->RndInt(0, Regular_Period2 - 1);

		BL_Bound_Mod = Vector2( 80, -120 );
		TR_Bound_Mod = Vector2( 550, 320 );
	}

	void Coin_Parameters::InitializeInstanceFields()
	{
		Red = false;
		FillType = FillTypes_REGULAR;
		GridSpacing = Vector2( 80, 80 );
		DoCleanup = true;
		CoinPlaced = false;
	}

	Coin_Parameters::Coin_Parameters() :
		Red( false ),
		FillType( FillTypes_NONE ),
		Grid( false ),
		DoCleanup( false ),
		StartFrame( 0 ),
		Regular_Period( 0 ),
		Regular_Offset( 0 ),
		Regular_Period2( 0 ),
		Regular_Offset2( 0 ),
		CoinPlaced( false )
	{
		InitializeInstanceFields();
	}

boost::shared_ptr<Coin_AutoGen> Coin_AutoGen::instance = boost::make_shared<Coin_AutoGen>();

	const boost::shared_ptr<Coin_AutoGen> &Coin_AutoGen::getInstance()
	{
		return instance;
	}

	Coin_AutoGen::Coin_AutoGen() :
		offset( 0 )
	{
		Do_ActiveFill_1 = true;
	}

	boost::shared_ptr<AutoGen_Parameters> Coin_AutoGen::SetParameters( const boost::shared_ptr<PieceSeedData> &data, const boost::shared_ptr<Level> &level )
	{
		boost::shared_ptr<Coin_Parameters> Params = boost::make_shared<Coin_Parameters>();
		Params->SetParameters( data, level );

		return boost::static_pointer_cast<AutoGen_Parameters>( Params );
	}

	void Coin_AutoGen::Cleanup_2( const boost::shared_ptr<Level> &level, Vector2 BL, Vector2 TR )
	{
		AutoGen::Cleanup_2( level, BL, TR );
		level->CleanupCoins( BL, TR );

		// Get Coin parameters
		boost::shared_ptr<Coin_Parameters> Params = boost::static_pointer_cast<Coin_Parameters>( level->getStyle()->FindParams( Coin_AutoGen::getInstance() ) );
	}

	boost::shared_ptr<ObjectBase> Coin_AutoGen::CreateAt( const boost::shared_ptr<Level> &level, Vector2 pos )
	{
		return CreateAt( level, pos, true );
	}

	boost::shared_ptr<ObjectBase> Coin_AutoGen::CreateAt( const boost::shared_ptr<Level> &level, Vector2 pos, bool NewOffset )
	{
		// Get Coin parameters
		boost::shared_ptr<Coin_Parameters> Params = boost::static_pointer_cast<Coin_Parameters>( level->getStyle()->FindParams( Coin_AutoGen::getInstance() ) );

		// Snap the coins to a grid
		if ( Params->Grid )
			pos = Params->SnapToGrid( pos );

		// Get the new Coin
		boost::shared_ptr<Coin> NewCoin = boost::static_pointer_cast<Coin>( level->getRecycle()->GetObject(ObjectType_COIN, true) );

		NewCoin->getCore()->GenData.Used = true;
		NewCoin->getCore()->GenData.LimitGeneralDensity = false;

		level->AddObject( NewCoin );

		// Position
		if ( Params->Red )
		{
			if ( NewOffset )
				offset = level->getRnd()->RandomSnap(NewCoin->Period, 3);
			NewCoin->Offset = offset;

			NewCoin->SetType( Coin::CoinType_RED );
			Vector2 curpos = NewCoin->GetPos();
			NewCoin->Move( pos - curpos );
		}
		else
		{
			NewCoin->SetType( Coin::CoinType_BLUE );
			NewCoin->Move( pos - NewCoin->getCore()->Data.Position );
		}

		return NewCoin;
	}

	Vector2 Coin_AutoGen::CalcPos( const boost::shared_ptr<Bob> &bob, Vector2 BL, Vector2 TR, BobPos pos )
	{
		Vector2 center = bob->getCore()->Data.Position;
		Vector2 top = Vector2( center.X, bob->Box->TR.Y );
		Vector2 bottom = Vector2( center.X, bob->Box->BL.Y );
		Vector2 avg = ( top + bottom ) / 2;
		switch ( pos )
		{
			case BobPos_CENTER:
				return avg;
			case BobPos_HIGH:
				return.9f * top + .1f * avg;
			case BobPos_LOW:
				return.9f * bottom + .1f * avg;
			default:
				return ( center + bob->Box->TR ) / 2;
		}
	}

	void Coin_AutoGen::ActiveFill_1( const boost::shared_ptr<Level> &level, Vector2 BL, Vector2 TR )
	{
		//return;

		AutoGen::ActiveFill_1( level, BL, TR );

		// Get Coin parameters
		boost::shared_ptr<Coin_Parameters> Params = boost::static_pointer_cast<Coin_Parameters>( level->getStyle()->FindParams( Coin_AutoGen::getInstance() ) );

		if ( !Params->DoStage2Fill )
			return;

		int Step = level->GetPhsxStep();

		if ( Step < Params->StartFrame )
			return;

		for ( BobVec::const_iterator bob = level->Bobs.begin(); bob != level->Bobs.end(); ++bob )
		{
			if ( !level->getMainCamera()->OnScreen((*bob)->getCore()->Data.Position, Vector2(-200, -240)) || level->getStyle()->Masochistic )
				continue;

			Vector2 pos = ( *bob )->getCore()->Data.Position;

			boost::shared_ptr<Coin> coin;
			switch ( Params->FillType )
			{
				case Coin_Parameters::FillTypes_REGULAR:
					if ( Params->Regular_ReadyToPlace( level, *bob, Step ) )
						coin = boost::static_pointer_cast<Coin>( CreateAt( level, CalcPos( *bob, BL, TR, BobPos_REGULAR ) ) );
					break;

				case Coin_Parameters::FillTypes_RUSH:
					if ( Step % 15 == 0 )
						coin = boost::static_pointer_cast<Coin>( CreateAt( level, CalcPos( *bob, BL, TR, BobPos_REGULAR ) ) );
					break;

				case Coin_Parameters::FillTypes_COIN_GRAB:
					if ( Step % Params->Regular_Period == 0 && ( ( *bob )->getPos().X > (*bob)->LastPlacedCoin.X + 40 || !Params->CoinPlaced ) )
					{
						Params->CoinPlaced = true;
						( *bob )->LastPlacedCoin = ( *bob )->getPos();

						coin = boost::static_pointer_cast<Coin>( CreateAt( level, CalcPos( *bob, BL, TR, BobPos_HIGH ) ) );
						coin = boost::static_pointer_cast<Coin>( CreateAt( level, CalcPos( *bob, BL, TR, BobPos_CENTER ), false ) );
						coin = boost::static_pointer_cast<Coin>( CreateAt( level, CalcPos( *bob, BL, TR, BobPos_LOW ), false ) );
					}
					break;

				default:
					break;
			}
		}
	}
}
