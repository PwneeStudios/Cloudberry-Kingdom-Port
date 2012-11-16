#include <global_header.h>






namespace CloudberryKingdom
{

	RegularLevel::RegularLevel()
	{
	}

	void RegularLevel::StandardInit( const std::shared_ptr<LevelSeedData> &data )
	{
		data->setSeed( data->Rnd->Rnd->Next() );

		data->SetTileSet( 0 );

		data->DefaultHeroType = BobPhsxNormal::getInstance();
	}

	std::shared_ptr<LevelSeedData> RegularLevel::HeroLevel( float Difficulty, const std::shared_ptr<BobPhsx> &Hero, int Length )
	{
		std::shared_ptr<LevelSeedData> data = std::make_shared<LevelSeedData>();

		StandardInit( data );

		data->DefaultHeroType = Hero;

		//LevelSeedData.CustomDifficulty custom = DifficultyGroups.FixedPieceMod(Difficulty, data);
		std::shared_ptr<Lambda_1<PieceSeedData*> > custom = DifficultyGroups::FixedPieceMod( Difficulty, data );
		data->Initialize( NormalGameData::Factory, LevelGeometry_RIGHT, 1, Length, custom );

		return data;
	}
}
