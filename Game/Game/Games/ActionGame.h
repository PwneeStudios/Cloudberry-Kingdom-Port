#ifndef ACTIONGAME
#define ACTIONGAME

#include <global_header.h>

namespace CloudberryKingdom
{
	struct ActionFactory : public GameFactory
	{
	
		virtual ~ActionFactory()
		{
#ifdef BOOST_BIN
			OnDestructor( "ActionFactory" );
#endif
		}


		virtual boost::shared_ptr<GameData> Make( const boost::shared_ptr<LevelSeedData> &data, bool MakeInBackground );
	};

	struct ActionGameData : public GameData
	{

		virtual ~ActionGameData()
		{
#ifdef BOOST_BIN
			OnDestructor( "ActionGameData" );
#endif
		}

	
		static void InitializeStatics();

	
		static boost::shared_ptr<GameFactory> Factory;

		ActionGameData();

		ActionGameData( const boost::shared_ptr<LevelSeedData> &LevelSeed, bool MakeInBackground );

	
		boost::shared_ptr<LevelSeedData> Seed;
	
		virtual void Init( const boost::shared_ptr<LevelSeedData> &LevelSeed, bool MakeInBackground );

		bool Done;
	
		bool ActionTaken;

	
		virtual void PhsxStep();

		virtual void PostDraw();

		virtual void Draw();

		virtual void Release();

	
		boost::shared_ptr<Level> MakeEmptyLevel();

	
		virtual void MakeBobs( const boost::shared_ptr<Level> &level );

		virtual void UpdateBobs();

		virtual void Reset();

   
	   void InitializeInstanceFields();
	};
}


#endif	//#ifndef ACTIONGAME
