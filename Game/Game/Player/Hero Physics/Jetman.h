#ifndef JETMAN
#define JETMAN

#include <global_header.h>

namespace CloudberryKingdom
{
	struct BobPhsxJetman : public BobPhsxNormal
	{

	
		static void InitializeStatics();

	
		virtual void Set( const std::shared_ptr<BobPhsx> &phsx );

		static void SetJetmanObject( const std::shared_ptr<ObjectClass> &obj );

		// Singleton
	
		virtual void InitSingleton();
	
		static std::shared_ptr<BobPhsxJetman> instance;
	
		const static std::shared_ptr<BobPhsxJetman> &getInstance();

		// Instancable struct
		BobPhsxJetman();
	};
}


#endif	//#ifndef JETMAN
