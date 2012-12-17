#ifndef DOUBLE
#define DOUBLE

#include <global_header.h>

namespace CloudberryKingdom
{
	struct BobPhsxDouble : public BobPhsxNormal
	{

	
		static void InitializeStatics();

	
		virtual void Set( const boost::shared_ptr<BobPhsx> &phsx );

		static void SetDoubleObject( const boost::shared_ptr<ObjectClass> &obj, const boost::shared_ptr<BobPhsx> &phsx );

		// Singleton
	
		virtual void InitSingleton();
	
		static boost::shared_ptr<BobPhsxDouble> instance;
	
		const static boost::shared_ptr<BobPhsxDouble> &getInstance();

		// Instancable struct
		BobPhsxDouble();
	};
}


#endif	//#ifndef DOUBLE
