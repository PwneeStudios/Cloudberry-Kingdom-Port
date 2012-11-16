#ifndef TIMECRISIS
#define TIMECRISIS

#include <global_header.h>

namespace CloudberryKingdom
{
	class LevelSeedData;
}

namespace CloudberryKingdom
{
	class BobPhsx;
}








namespace CloudberryKingdom
{
	class Challenge_TimeCrisis : public Challenge_HeroRush
	{
	private:
		class OnSwapLambda : public Lambda_1<LevelSeedData*>
		{
		private:
			std::shared_ptr<Challenge_TimeCrisis> ch;
		public:
			OnSwapLambda( const std::shared_ptr<Challenge_TimeCrisis> &ch );

			void Apply( const std::shared_ptr<LevelSeedData> &data );
		};
	private:
		static const std::shared_ptr<Challenge_TimeCrisis> instance;
	public:
		const static std::shared_ptr<Challenge_TimeCrisis> &getInstance() const;

	protected:
		Challenge_TimeCrisis();

		virtual std::shared_ptr<BobPhsx> GetHero( int i );

		virtual void PreStart_Tutorial( bool TemporarySkip );

	};
}


#endif	//#ifndef TIMECRISIS
