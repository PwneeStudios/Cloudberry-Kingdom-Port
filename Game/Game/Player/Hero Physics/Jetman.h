#ifndef JETMAN
#define JETMAN

#include <global_header.h>

namespace CloudberryKingdom
{
	struct BobPhsxJetman : public BobPhsxNormal
	{

	
		static void InitializeStatics();

	
		virtual void Set( const boost::shared_ptr<BobPhsx> &phsx );

		static void SetJetmanObject( const boost::shared_ptr<ObjectClass> &obj );

		// Singleton
	
		virtual void InitSingleton();
	
		static boost::shared_ptr<BobPhsxJetman> instance;
	
		const static boost::shared_ptr<BobPhsxJetman> &getInstance();

		// Instancable struct
		BobPhsxJetman();
	};
}


#endif	//#ifndef JETMAN
