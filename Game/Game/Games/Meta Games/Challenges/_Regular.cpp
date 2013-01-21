#include <global_header.h>

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

	boost::shared_ptr<LevelSeedData> RegularLevel::HeroLevel( float Difficulty, const boost::shared_ptr<BobPhsx> &Hero, int Length )
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
		boost::shared_ptr<Lambda_1<boost::shared_ptr<PieceSeedData> > > custom = DifficultyGroups::FixedPieceMod( Difficulty, data );
		data->Initialize( NormalGameData::Factory, LevelGeometry_RIGHT, 1, Length, custom );

		return data;
	}
}
