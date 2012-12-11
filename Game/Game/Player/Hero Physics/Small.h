#ifndef SMALL
#define SMALL

#include <global_header.h>

namespace CloudberryKingdom
{
	struct BobPhsxSmall : public BobPhsxNormal
	{

	
		static void InitializeStatics();

	
		virtual void Set( const std::shared_ptr<BobPhsx> &phsx );
		void Set( const std::shared_ptr<BobPhsx> &phsx, Vector2 modsize );

		// Singleton
	
		virtual void InitSingleton();
	
		static std::shared_ptr<BobPhsxSmall> instance;
	
		const static std::shared_ptr<BobPhsxSmall> &getInstance();

		// Instancable struct
		BobPhsxSmall();
	};
}


#endif	//#ifndef SMALL
