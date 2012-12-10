#ifndef NORMALGAME
#define NORMALGAME

#include <global_header.h>

namespace CloudberryKingdom
{
	struct NormalFactory : public GameFactory
	{
	
		virtual std::shared_ptr<GameData> Make( const std::shared_ptr<LevelSeedData> &data, bool MakeInBackground );
	};

	struct NormalGameData : public GameData
	{
	
		virtual void SetCreatedBobParameters( const std::shared_ptr<Bob> &bob );

		virtual void SetAdditionalLevelParameters();

		static std::shared_ptr<GameFactory> Factory;

		NormalGameData();

		NormalGameData( const std::shared_ptr<LevelSeedData> &LevelSeed, bool MakeInBackground );

		virtual void Init( const std::shared_ptr<LevelSeedData> &LevelSeed, bool MakeInBackground );

	
		std::shared_ptr<LevelSeedData> _MakeThreadLevelSeed;
		bool _MakeThreadMakeInBackground;
		void _MakeThreadFunc();


	
		virtual void PhsxStep();

		virtual void PostDraw();

		virtual void AdditionalReset();

		virtual void BobDie( const std::shared_ptr<Level> &level, const std::shared_ptr<Bob> &bob );

		virtual void BobDoneDying( const std::shared_ptr<Level> &level, const std::shared_ptr<Bob> &bob );
	};
}


#endif	//#ifndef NORMALGAME
