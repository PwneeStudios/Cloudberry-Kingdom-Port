#ifndef SCALE
#define SCALE

#include <global_header.h>

namespace CloudberryKingdom
{
	struct BobPhsxScale : public BobPhsxNormal
	{

	
		static void InitializeStatics();

	
		virtual void Set( const std::shared_ptr<BobPhsx> &phsx );

		// Singleton
	
		virtual void InitSingleton();
	
		static std::shared_ptr<BobPhsxScale> instance;
	
		const static std::shared_ptr<BobPhsxScale> &getInstance();

		// Instancable struct
		BobPhsxScale();
	};
}


#endif	//#ifndef SCALE
