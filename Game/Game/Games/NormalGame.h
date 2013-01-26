#ifndef NORMALGAME
#define NORMALGAME

#include <global_header.h>

namespace CloudberryKingdom
{
	struct NormalFactory : public GameFactory
	{
	
		virtual ~NormalFactory() { }
		virtual boost::shared_ptr<GameData> Make( const boost::shared_ptr<LevelSeedData> &data, bool MakeInBackground );

	};

	struct NormalGameData : public GameData
	{
	
		virtual ~NormalGameData() { }

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
