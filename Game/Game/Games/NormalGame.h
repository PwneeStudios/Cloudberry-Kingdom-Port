#ifndef NORMALGAME
#define NORMALGAME

#include <small_header.h>

//#include "Core/Sound/EzSound.h"
#include "Game/Games/GameType.h"
//#include "Game/Level/Make/LockableBool.h"
//#include "Game/Level/Make/LevelSeedData.h"
//#include "Game/Objects/Bob/Bob.h"
//#include "Game/Objects/In Game Objects/Grab/MakeData.h"
//#include "Game/Level/Level.h"
//#include "Game/Tools/Tools.h"


namespace CloudberryKingdom
{
	struct NormalFactory : public GameFactory
	{
	
		virtual ~NormalFactory()
		{
#ifdef BOOST_BIN
			OnDestructor( "NormalFactory" );
#endif
		}

		virtual boost::shared_ptr<GameData> Make( const boost::shared_ptr<LevelSeedData> &data, bool MakeInBackground );

	};

	struct NormalGameData : public GameData
	{
	
		virtual ~NormalGameData()
		{
#ifdef BOOST_BIN
			OnDestructor( "NormalGameData" );
#endif
		}


		virtual void SetCreatedBobParameters( const boost::shared_ptr<Bob> &bob );

		virtual void SetAdditionalLevelParameters();

		static boost::shared_ptr<GameFactory> Factory;

		NormalGameData();

		NormalGameData( const boost::shared_ptr<LevelSeedData> &LevelSeed, bool MakeInBackground );

		virtual void Init( const boost::shared_ptr<LevelSeedData> &LevelSeed, bool MakeInBackground );

		boost::shared_ptr<LevelSeedData> _MakeThreadLevelSeed;
		bool _MakeThreadMakeInBackground;
		void _MakeThreadFunc();

		virtual void PhsxStep();

		virtual void PostDraw();

		virtual void AdditionalReset();

		virtual void BobDie( const boost::shared_ptr<Level> &level, const boost::shared_ptr<Bob> &bob );

		virtual void BobDoneDying( const boost::shared_ptr<Level> &level, const boost::shared_ptr<Bob> &bob );
	};
}


#endif	//#ifndef NORMALGAME
