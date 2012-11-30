#include <global_header.h>


namespace CloudberryKingdom
{

	Challenge_HeroRush2::OnSwapLambda::OnSwapLambda( const std::shared_ptr<Challenge_HeroRush2> &ch )
	{
		this->ch = ch;
	}

	void Challenge_HeroRush2::OnSwapLambda::Apply( const std::shared_ptr<LevelSeedData> &data )
	{
		data->MyGame->AddGameObject( std::make_shared<HeroRush2_Tutorial>( ch ) );
	}

	std::vector<HeroSpec> Challenge_HeroRush2::HeroList = std::vector<HeroSpec>( 100 );
	const std::shared_ptr<Challenge_HeroRush2> Challenge_HeroRush2::instance = std::make_shared<Challenge_HeroRush2>();

	const std::shared_ptr<Challenge_HeroRush2> &Challenge_HeroRush2::getInstance()
	{
		return instance;
	}

	const Vector2 IconPos[][3] =
	{
		{ Vector2( 240, 400 ), Vector2(),			Vector2() },
		{ Vector2( 255, 310 ), Vector2( 255, 650 ), Vector2() },
		{ Vector2( 255, 310 ), Vector2( 255, 650 ), Vector2( 10, 512 ) }
	};

	const float IconScale[] = { .8f,.8f,.8f };

	void Challenge_HeroRush2::MakeExitDoorIcon( int levelindex )
	{
		HeroSpec spec = HeroList[ ( levelindex + 1 - StartIndex ) % HeroList.size() ];
		std::shared_ptr<GameData> game = Tools::CurGameData;
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
			game->AddGameObject( std::make_shared<DoorIcon>( BobPhsxNormal::getInstance(), pos + IconPos[ 0 ][ 0 ], IconScale[ 0 ] ) );
			return;
		}

		int Count = 0;
		if ( spec.basetype != Hero_BaseType_CLASSIC )
		{
			game->AddGameObject( std::make_shared<DoorIcon>( BobPhsx::GetPhsx_Base( spec.basetype ), pos + IconPos[ Total - 1 ][ Count ], IconScale[ Total - 1 ] ) );
			Count++;
		}

		if ( spec.move != Hero_MoveMod_CLASSIC )
		{
			game->AddGameObject( std::make_shared<DoorIcon>( BobPhsx::GetPhsx_Move( spec.move ), pos + IconPos[ Total - 1 ][ Count ], IconScale[ Total - 1 ] ) );
			Count++;
		}

		if ( spec.shape != Hero_Shape_CLASSIC )
		{
			game->AddGameObject( std::make_shared<DoorIcon>( BobPhsx::GetPhsx_Shape( spec.shape ), pos + IconPos[ Total - 1 ][ Count ], IconScale[ Total - 1 ] ) );
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

	std::shared_ptr<BobPhsx> Challenge_HeroRush2::GetHero( int i )
	{
		//return BobPhsx.MakeCustom(HeroList[i % NumHeros]);
		return BobPhsx::MakeCustom( HeroList[ i % HeroList.size() ] );
	}

	void Challenge_HeroRush2::PreStart_Tutorial( bool TemporarySkip )
	{
		HeroRush_Tutorial::TemporarySkip = TemporarySkip;
		MyStringWorld->OnSwapToFirstLevel->Add( std::make_shared<OnSwapLambda>( std::static_pointer_cast<Challenge_HeroRush2>( shared_from_this() ) ) );
	}
}
