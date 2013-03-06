#ifndef BIG
#define BIG

#include <global_header.h>

namespace CloudberryKingdom
{
	
	struct BobPhsxBig : public BobPhsxNormal
	{

		virtual ~BobPhsxBig()
		{
#ifdef BOOST_BIN
			OnDestructor( "BobPhsxBig" );
#endif
		}

	
		static void InitializeStatics();

	
		virtual void Set( const boost::shared_ptr<BobPhsx> &phsx );

		// Singleton
	
		virtual void InitSingleton();
	
		static boost::shared_ptr<BobPhsxBig> instance;
	
		const static boost::shared_ptr<BobPhsxBig> &getInstance();

		// Instancable struct
		BobPhsxBig();
	};

}


#endif	//#ifndef BIG
