#include <small_header.h>
#include "Game/Games/Meta Games/Challenges/_Regular.h"

#include "Game/Games/NormalGame.h"
#include "Game/Level/Make/LockableBool.h"
#include "Game/Level/Make/DifficultyGroups.h"
#include "Game/Level/Make/LevelSeedData.h"
#include "Game/Level/Make/PieceSeedData.h"
#include "Game/Level/Make/Parameters/Upgrades.h"
#include "Game/Menus/Concrete Menus/Title Screen/Arcade/ArcadeMenu.h"
#include "Game/Player/Hero Physics/Base.h"
#include "Game/Objects/AutoGen.h"
#include "Game/Player/Hero Physics/Normal.h"
#include "Game/Tools/Tools.h"

#include "Core/Tools/Random.h"

namespace CloudberryKingdom
{

	RegularLevel::RegularLevel()
	{
	}

	void RegularLevel::StandardInit( const boost::shared_ptr<LevelSeedData> &data )
	{
		data->setSeed( data->Rnd->Rnd->Next() );

		data->SetTileSet( boost::shared_ptr<TileSet>( 0 ) );

		data->DefaultHeroType = BobPhsxNormal::getInstance();
	}

	boost::shared_ptr<LevelSeedData> RegularLevel::HeroLevel( float Difficulty, const boost::shared_ptr<BobPhsx> &Hero, int Length, bool ScreenSaver)
	{
		if (Hero == ArcadeMenu::Ultimate)
		{
			Length *= 2;
			Difficulty *= 2;
		}

		boost::shared_ptr<LevelSeedData> data = boost::make_shared<LevelSeedData>();

		StandardInit( data );

		data->DefaultHeroType = Hero;

		//LevelSeedData.CustomDifficulty custom = DifficultyGroups.FixedPieceMod(Difficulty, data);
		boost::shared_ptr<Lambda_1<boost::shared_ptr<PieceSeedData> > > custom = DifficultyGroups::FixedPieceMod( Difficulty, data, ScreenSaver );
		data->Initialize( NormalGameData::Factory, LevelGeometry_RIGHT, 1, Length, custom );

		return data;
	}
}
