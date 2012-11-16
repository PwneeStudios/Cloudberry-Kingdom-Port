#include "HeroRush2.h"
#include "Game/Level/Make/CloudberryKingdom.LevelSeedData.h"
#include "Game/Games/Meta Games/Arcade Games/Rush/Hero Rush 2/HeroRush2_Tutorial.h"
#include "Game/Player/Hero Physics/Base.h"
#include "Game/Games/GameType.h"
#include "Game/Tools/Tools.h"
#include "Game/Objects/ObjectBase.h"
#include "Game/Objects/Door/Sign.h"
#include "Game/Objects/Game Objects/GameObjects/DoorIcon.h"
#include "Game/Player/Hero Physics/Normal.h"
#include "Game/Localization.h"
#include "Game/Games/Meta Games/Arcade Games/Rush/Hero Rush/HeroRush_Tutorial.h"

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;
using namespace Microsoft::Xna::Framework;

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

	const std::shared_ptr<Challenge_HeroRush2> &Challenge_HeroRush2::getInstance() const
	{
		return instance;
	}

const std::vector<Vector2> tempVector[] = { std::vector<Vector2> { Vector2( 240, 400 ) }, std::vector<Vector2> { Vector2( 255, 310 ), Vector2( 255, 650 ) }, std::vector<Vector2> { Vector2( 255, 310 ), Vector2( 255, 650 ), Vector2( 10, 512 ) } };
std::vector<std::vector<Vector2> > Challenge_HeroRush2::IconPos = std::vector<std::vector<Vector2> >( tempVector, tempVector + sizeof( tempVector ) / sizeof( tempVector[ 0 ] ) );
const float tempVector2[] = { .8f,.8f,.8f };
std::vector<float> Challenge_HeroRush2::IconScale = std::vector<float>( tempVector2, tempVector2 + sizeof( tempVector2 ) / sizeof( tempVector2[ 0 ] ) );

	void Challenge_HeroRush2::MakeExitDoorIcon( int levelindex )
	{
		const std::vector<Vector2> tempVector3[] = { std::vector<Vector2> { Vector2( 0, 470 ) }, std::vector<Vector2> { Vector2( 0, 450 ), Vector2( 255, 630 ) }, std::vector<Vector2> { Vector2( -10, 350 ), Vector2( -10, 690 ), Vector2( 235, 552 ) } };
		IconPos = std::vector<std::vector<Vector2> >( tempVector3, tempVector3 + sizeof( tempVector3 ) / sizeof( tempVector3[ 0 ] ) );


		HeroSpec spec = HeroList[ ( levelindex + 1 - StartIndex ) % HeroList.size() ];
		std::shared_ptr<GameData> game = Tools::CurGameData;
		Vector2 pos = Tools::CurLevel->getFinalDoor()->getPos();

		// Delete the exit sign
		for ( std::vector<ObjectBase*>::const_iterator obj = Tools::CurLevel->Objects.begin(); obj != Tools::CurLevel->Objects.end(); ++obj )
			if ( dynamic_cast<Sign*>( *obj ) != 0 )
				( *obj )->getCore()->MarkedForDeletion = true;

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
			game->AddGameObject( std::make_shared<DoorIcon>( BobPhsx::GetPhsx( spec.basetype ), pos + IconPos[ Total - 1 ][ Count ], IconScale[ Total - 1 ] ) );
			Count++;
		}

		if ( spec.move != Hero_MoveMod_CLASSIC )
		{
			game->AddGameObject( std::make_shared<DoorIcon>( BobPhsx::GetPhsx( spec.move ), pos + IconPos[ Total - 1 ][ Count ], IconScale[ Total - 1 ] ) );
			Count++;
		}

		if ( spec.shape != Hero_Shape_CLASSIC )
		{
			game->AddGameObject( std::make_shared<DoorIcon>( BobPhsx::GetPhsx( spec.shape ), pos + IconPos[ Total - 1 ][ Count ], IconScale[ Total - 1 ] ) );
			Count++;
		}
	}

	Challenge_HeroRush2::Challenge_HeroRush2()
	{
		GameTypeId = 1;
		MenuName = Name = Localization::Words_HYBRID_RUSH;

		// Create the list of custom heros
		const Hero_BaseType tempVector4[] = { Hero_BaseType_BOUNCY, Hero_BaseType_BOX, Hero_BaseType_CLASSIC, Hero_BaseType_SPACESHIP, Hero_BaseType_WHEEL };
		std::vector<Hero_BaseType> BaseTypes = std::vector<Hero_BaseType>( tempVector4, tempVector4 + sizeof( tempVector4 ) / sizeof( tempVector4[ 0 ] ) );

		const Hero_MoveMod tempVector5[] = { Hero_MoveMod_CLASSIC, Hero_MoveMod_DOUBLE, Hero_MoveMod_JETPACK };
		std::vector<Hero_MoveMod> MoveTypes = std::vector<Hero_MoveMod>( tempVector5, tempVector5 + sizeof( tempVector5 ) / sizeof( tempVector5[ 0 ] ) );

		for ( std::vector<CloudberryKingdom::Hero_BaseType>::const_iterator basetype = BaseTypes.begin(); basetype != BaseTypes.end(); ++basetype )
			for ( IEnumerable<T*>::const_iterator shape = Tools::GetValues<Hero_Shape>()->begin(); shape != Tools::GetValues<Hero_Shape>()->end(); ++shape )
				for ( std::vector<CloudberryKingdom::Hero_MoveMod>::const_iterator move = MoveTypes.begin(); move != MoveTypes.end(); ++move )
				{
					// Spaceships can only have their shape modified
					if ( *basetype == Hero_BaseType_SPACESHIP && move != Hero_MoveMod_CLASSIC )
						continue;

					// Normal bob is added later (to make sure it is first)
					if ( *basetype == Hero_BaseType_CLASSIC && shape == Hero_Shape_CLASSIC && move == Hero_MoveMod_CLASSIC )
						continue;

					// Bouncey can not be double jump
					if ( *basetype == Hero_BaseType_BOUNCY && move == Hero_MoveMod_DOUBLE )
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
		HeroList.Insert( 0, HeroSpec( Hero_BaseType_CLASSIC, Hero_Shape_CLASSIC, Hero_MoveMod_CLASSIC ) );
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
		MyStringWorld->OnSwapToFirstLevel->Add( std::make_shared<OnSwapLambda>( this ) );
	}
}
