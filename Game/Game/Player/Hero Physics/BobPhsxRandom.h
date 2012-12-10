#ifndef BOB_PHSX_RANDOM_H
#define BOB_PHSX_RANDOM_H

#include <global_header.h>

namespace CloudberryKingdom
{
	struct BobPhsxRandom : public BobPhsx
	{

	
		static void InitializeStatics();

	
		// Singleton
		virtual void InitSingleton();
	
		static std::shared_ptr<BobPhsxRandom> instance;
	
		static const std::shared_ptr<BobPhsxRandom> &getInstance();

		static std::shared_ptr<BobPhsx> ChooseHeroType();

		virtual std::shared_ptr<BobPhsx> Clone();
		void CopyTo( const std::shared_ptr<BobPhsxRandom> &bob );

		// Instancable struct
		BobPhsxRandom();
	};
}


#endif	//#ifndef RANDOM
