#include <global_header.h>

#include "Hacks/List.h"

namespace CloudberryKingdom
{

	Challenge_HeroRush2::OnSwapLambda::OnSwapLambda( const boost::shared_ptr<Challenge_HeroRush2> &ch )
	{
		this->ch = ch;
	}

	void Challenge_HeroRush2::OnSwapLambda::Apply( const boost::shared_ptr<LevelSeedData> &data )
	{
		data->MyGame->AddGameObject( boost::make_shared<HeroRush2_Tutorial>( ch ) );
	}

	std::vector<HeroSpec> Challenge_HeroRush2::HeroList;
	boost::shared_ptr<Challenge_HeroRush2> Challenge_HeroRush2::instance;

	const boost::shared_ptr<Challenge_HeroRush2> &Challenge_HeroRush2::getInstance()
	{
		return instance;
	}

	Vector2 __IconPos1[] = { Vector2(   0, 470 ), Vector2(),		      Vector2() };
	Vector2 __IconPos2[] = { Vector2(   0, 450 ), Vector2( 255, 630 ), Vector2() };
	Vector2 __IconPos3[] = { Vector2( -10, 350 ), Vector2( -10, 690 ), Vector2( 235, 552 ) };
	std::vector<Vector2> _IconPos1 = VecFromArray( __IconPos1 );
	std::vector<Vector2> _IconPos2 = VecFromArray( __IconPos2 );
	std::vector<Vector2> _IconPos3 = VecFromArray( __IconPos3 );
	std::vector<Vector2> _IconPos[] = { _IconPos1, _IconPos2, _IconPos3 };

	std::vector<std::vector<Vector2> > Challenge_HeroRush2::IconPos = VecFromArray( _IconPos );


	float _IconScale[] = { .8f,.8f,.8f };
	std::vector<float> Challenge_HeroRush2::IconScale = VecFromArray( _IconScale );

	void Challenge_HeroRush2::MakeExitDoorIcon( int levelindex )
	{
		HeroSpec spec = HeroList[ ( levelindex + 1 - StartIndex ) % HeroList.size() ];
		boost::shared_ptr<GameData> game = Tools::CurGameData;
		Vector2 pos = Tools::CurLevel->getFinalDoor()->getPos();

		// Count number of icons needed
		int Total = 0;
		if ( spec.basetype != Hero_BaseType_CLASSIC )
			Total++;
		if ( spec.move != Hero_MoveMod_CLASSIC )
			Total++;
		if ( spec.shape != Hero_Shape_CLASSIC )
			Total++;

		// Make the icons
		if ( Total == 0 )
		{
			game->AddGameObject( MakeMagic( DoorIcon, ( BobPhsxNormal::getInstance(), pos + IconPos[ 0 ][ 0 ], IconScale[ 0 ] ) ) );
			return;
		}

		int Count = 0;
		if ( spec.basetype != Hero_BaseType_CLASSIC )
		{
			game->AddGameObject( MakeMagic( DoorIcon, ( BobPhsx::GetPhsx_Base( spec.basetype ), pos + IconPos[ Total - 1 ][ Count ], IconScale[ Total - 1 ] ) ) );
			Count++;
		}

		if ( spec.move != Hero_MoveMod_CLASSIC )
		{
			game->AddGameObject( MakeMagic( DoorIcon, ( BobPhsx::GetPhsx_Move( spec.move ), pos + IconPos[ Total - 1 ][ Count ], IconScale[ Total - 1 ] ) ) );
			Count++;
		}

		if ( spec.shape != Hero_Shape_CLASSIC )
		{
			game->AddGameObject( MakeMagic( DoorIcon, ( BobPhsx::GetPhsx_Shape( spec.shape ), pos + IconPos[ Total - 1 ][ Count ], IconScale[ Total - 1 ] ) ) );
			Count++;
		}
	}

	Challenge_HeroRush2::Challenge_HeroRush2()
	{
		GameTypeId = 1;
		MenuName = Name = Localization::Words_HYBRID_RUSH;

		// Create the list of custom heros
		int _BaseTypes[] = { Hero_BaseType_BOUNCY, Hero_BaseType_BOX, Hero_BaseType_CLASSIC, Hero_BaseType_SPACESHIP, Hero_BaseType_WHEEL };
		std::vector<int> BaseTypes = VecFromArray( _BaseTypes );
		int _ShapeTypes[] = { Hero_Shape_CLASSIC, Hero_Shape_SMALL, Hero_Shape_OSCILLATE, Hero_Shape_BIG };
		std::vector<int> ShapeTypes = VecFromArray( _ShapeTypes );
		int _MoveTypes[] = { Hero_MoveMod_CLASSIC, Hero_MoveMod_DOUBLE, Hero_MoveMod_JETPACK };
		std::vector<int> MoveTypes = VecFromArray( _MoveTypes );

		for ( std::vector<int>::const_iterator basetype = BaseTypes.begin(); basetype != BaseTypes.end(); ++basetype )
			for ( std::vector<int>::const_iterator shape = ShapeTypes.begin(); shape != ShapeTypes.end(); ++shape )
				for ( std::vector<int>::const_iterator move = MoveTypes.begin(); move != MoveTypes.end(); ++move )
				{
					// Spaceships can only have their shape modified
					if ( *basetype == Hero_BaseType_SPACESHIP && *move != Hero_MoveMod_CLASSIC )
						continue;

					// Normal bob is added later (to make sure it is first)
					if ( *basetype == Hero_BaseType_CLASSIC && *shape == Hero_Shape_CLASSIC && *move == Hero_MoveMod_CLASSIC )
						continue;

					// Bouncey can not be double jump
					if ( *basetype == Hero_BaseType_BOUNCY && *move == Hero_MoveMod_DOUBLE )
						continue;

					//HeroList[NumHeros++] = new HeroSpec(basetype, shape, move);
					HeroList.push_back( HeroSpec( *basetype, *shape, *move ) );
				}
	}

	void Challenge_HeroRush2::ShuffleHeros()
	{
		// Shuffle the non-classic heros
		HeroList = Tools::GlobalRnd->Shuffle( HeroList );

		// The first hero is always classic
		HeroList.insert(HeroList.begin(), HeroSpec( Hero_BaseType_CLASSIC, Hero_Shape_CLASSIC, Hero_MoveMod_CLASSIC ) );
	}

	void Challenge_HeroRush2::Start( int StartLevel )
	{
		ShuffleHeros();

		Challenge_HeroRush::Start( StartLevel );
	}

	boost::shared_ptr<BobPhsx> Challenge_HeroRush2::GetHero( int i )
	{
		//return BobPhsx.MakeCustom(HeroList[i % NumHeros]);
		return BobPhsx::MakeCustom( HeroList[ i % HeroList.size() ] );
	}

	void Challenge_HeroRush2::PreStart_Tutorial( bool TemporarySkip )
	{
		HeroRush_Tutorial::TemporarySkip = TemporarySkip;
		MyStringWorld->OnSwapToFirstLevel->Add( boost::make_shared<OnSwapLambda>( boost::static_pointer_cast<Challenge_HeroRush2>( shared_from_this() ) ) );
	}
}
