#ifndef _RANDOM_H
#define _RANDOM_H

#include <global_header.h>

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
		static const std::shared_ptr<BobPhsxRandom> &getInstance();

		static std::shared_ptr<BobPhsx> ChooseHeroType();

		// Instancable class
		BobPhsxRandom();
	};
}


#endif	//#ifndef RANDOM
