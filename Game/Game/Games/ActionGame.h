#ifndef ACTIONGAME
#define ACTIONGAME

#include <global_header.h>

namespace CloudberryKingdom
{
	struct ActionFactory : public GameFactory
	{
	
		virtual std::shared_ptr<GameData> Make( const std::shared_ptr<LevelSeedData> &data, bool MakeInBackground );
	};

	struct ActionGameData : public GameData
	{

	
		static void InitializeStatics();

	
		static std::shared_ptr<GameFactory> Factory;

		ActionGameData();

		ActionGameData( const std::shared_ptr<LevelSeedData> &LevelSeed, bool MakeInBackground );

	
		std::shared_ptr<LevelSeedData> Seed;
	
		virtual void Init( const std::shared_ptr<LevelSeedData> &LevelSeed, bool MakeInBackground );

		bool Done;
	
		bool ActionTaken;

	
		virtual void PhsxStep();

		virtual void PostDraw();

		virtual void Draw();

		virtual void Release();

	
		std::shared_ptr<Level> MakeEmptyLevel();

	
		virtual void MakeBobs( const std::shared_ptr<Level> &level );

		virtual void UpdateBobs();

		virtual void Reset();

   
	   void InitializeInstanceFields();
	};
}


#endif	//#ifndef ACTIONGAME
