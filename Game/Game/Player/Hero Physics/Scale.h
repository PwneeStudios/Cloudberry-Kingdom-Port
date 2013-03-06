#ifndef SCALE
#define SCALE

#include <global_header.h>

namespace CloudberryKingdom
{

	struct BobPhsxScale : public BobPhsxNormal
	{

		virtual ~BobPhsxScale()
		{
#ifdef BOOST_BIN
			OnDestructor( "BobPhsxScale" );
#endif
		}

	
		static void InitializeStatics();

	
		virtual void Set( const boost::shared_ptr<BobPhsx> &phsx );

		// Singleton
	
		virtual void InitSingleton();
	
		static boost::shared_ptr<BobPhsxScale> instance;
	
		const static boost::shared_ptr<BobPhsxScale> &getInstance();

		// Instancable struct
		BobPhsxScale();
	};

}


#endif	//#ifndef SCALE
