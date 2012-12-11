#ifndef DOUBLE
#define DOUBLE

#include <global_header.h>

namespace CloudberryKingdom
{
	struct BobPhsxDouble : public BobPhsxNormal
	{

	
		static void InitializeStatics();

	
		virtual void Set( const std::shared_ptr<BobPhsx> &phsx );

		static void SetDoubleObject( const std::shared_ptr<ObjectClass> &obj, const std::shared_ptr<BobPhsx> &phsx );

		// Singleton
	
		virtual void InitSingleton();
	
		static std::shared_ptr<BobPhsxDouble> instance;
	
		const static std::shared_ptr<BobPhsxDouble> &getInstance();

		// Instancable struct
		BobPhsxDouble();
	};
}


#endif	//#ifndef DOUBLE
