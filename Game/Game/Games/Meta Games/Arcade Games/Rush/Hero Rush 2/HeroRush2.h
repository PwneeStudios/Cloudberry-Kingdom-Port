#ifndef HERORUSH2
#define HERORUSH2

#include <global_header.h>

namespace CloudberryKingdom
{
	class LevelSeedData;
}

namespace CloudberryKingdom
{
	class HeroSpec;
}

namespace Microsoft
{
	namespace Xna
	{
		namespace Framework
		{
			class Vector2;
		}
	}
}

namespace CloudberryKingdom
{
	class BobPhsx;
}



namespace CloudberryKingdom
{
	class Challenge_HeroRush2 : public Challenge_HeroRush
	{
	private:
		class OnSwapLambda : public Lambda_1<LevelSeedData*>
		{
		private:
			std::shared_ptr<Challenge_HeroRush2> ch;
		public:
			OnSwapLambda( const std::shared_ptr<Challenge_HeroRush2> &ch );

			void Apply( const std::shared_ptr<LevelSeedData> &data );
		};
	public:
		static std::vector<HeroSpec> HeroList;

	private:
		static const std::shared_ptr<Challenge_HeroRush2> instance;
	public:
		const static std::shared_ptr<Challenge_HeroRush2> &getInstance() const;

	private:
		static std::vector<std::vector<Vector2> > IconPos;

		static std::vector<float> IconScale;

	protected:
		virtual void MakeExitDoorIcon( int levelindex );

		Challenge_HeroRush2();

	private:
		void ShuffleHeros();

	public:
		virtual void Start( int StartLevel );

	protected:
		virtual std::shared_ptr<BobPhsx> GetHero( int i );

		virtual void PreStart_Tutorial( bool TemporarySkip );

	};
}


#endif	//#ifndef HERORUSH2
