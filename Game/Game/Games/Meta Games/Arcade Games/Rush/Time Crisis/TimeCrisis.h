#ifndef TIMECRISIS
#define TIMECRISIS

#include <global_header.h>

namespace CloudberryKingdom
{
	class Challenge_TimeCrisis : public Challenge_HeroRush
	{

	public:
		static void InitializeStatics();

	private:
		class OnSwapLambda : public Lambda_1<std::shared_ptr<LevelSeedData> >
		{
		private:
			std::shared_ptr<Challenge_TimeCrisis> ch;
		public:
			OnSwapLambda( const std::shared_ptr<Challenge_TimeCrisis> &ch );

			void Apply( const std::shared_ptr<LevelSeedData> &data );
		};
	private:
		static std::shared_ptr<Challenge_TimeCrisis> instance;
	public:
		const static std::shared_ptr<Challenge_TimeCrisis> &getInstance();

	public:
		Challenge_TimeCrisis();

	protected:
		virtual std::shared_ptr<BobPhsx> GetHero( int i );

		virtual void PreStart_Tutorial( bool TemporarySkip );

	};
}


#endif	//#ifndef TIMECRISIS
