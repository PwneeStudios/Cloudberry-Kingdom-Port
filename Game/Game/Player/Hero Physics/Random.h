#ifndef RANDOM
#define RANDOM

#include "Base.h"

namespace CloudberryKingdom
{
	class BobPhsx;
}


namespace CloudberryKingdom
{
	class BobPhsxRandom : public BobPhsx
	{
		// Singleton
	protected:
		virtual void InitSingleton();
	private:
		static const std::shared_ptr<BobPhsxRandom> instance;
	public:
		const static std::shared_ptr<BobPhsxRandom> &getInstance() const;

		static std::shared_ptr<BobPhsx> ChooseHeroType();

		// Instancable class
		BobPhsxRandom();
	};
}


#endif	//#ifndef RANDOM
