#ifndef BIG
#define BIG

#include <global_header.h>

namespace CloudberryKingdom
{
	struct BobPhsxBig : public BobPhsxNormal
	{

	
		static void InitializeStatics();

	
		virtual void Set( const std::shared_ptr<BobPhsx> &phsx );

		// Singleton
	
		virtual void InitSingleton();
	
		static std::shared_ptr<BobPhsxBig> instance;
	
		const static std::shared_ptr<BobPhsxBig> &getInstance();

		// Instancable struct
		BobPhsxBig();
	};
}


#endif	//#ifndef BIG
