#ifndef ACTIONGAME
#define ACTIONGAME

#include <global_header.h>

namespace CloudberryKingdom
{
	class GameData;
}

namespace CloudberryKingdom
{
	class LevelSeedData;
}

namespace CloudberryKingdom
{
	class GameFactory;
}

namespace CloudberryKingdom
{
	class Level;
}


using namespace Microsoft::Xna::Framework;

namespace CloudberryKingdom
{
	class ActionFactory : public GameFactory
	{
	public:
		virtual std::shared_ptr<GameData> Make( const std::shared_ptr<LevelSeedData> &data, bool MakeInBackground );
	};

	class ActionGameData : public GameData
	{
	public:
		static std::shared_ptr<GameFactory> Factory;

		ActionGameData();

		ActionGameData( const std::shared_ptr<LevelSeedData> &LevelSeed, bool MakeInBackground );

	private:
		std::shared_ptr<LevelSeedData> Seed;
	public:
		virtual void Init( const std::shared_ptr<LevelSeedData> &LevelSeed, bool MakeInBackground );

		bool Done;
	private:
		bool ActionTaken;

	public:
		virtual void PhsxStep();

		virtual void PostDraw();

		virtual void Draw();

		virtual void Release();

	private:
		std::shared_ptr<Level> MakeEmptyLevel();

	public:
		virtual void MakeBobs( const std::shared_ptr<Level> &level );

		virtual void UpdateBobs();

		virtual void Reset();

   private:
	   void InitializeInstanceFields();
	};
}


#endif	//#ifndef ACTIONGAME
