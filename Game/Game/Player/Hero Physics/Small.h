#ifndef SMALL
#define SMALL

#include <global_header.h>

namespace CloudberryKingdom
{

	struct BobPhsxSmall : public BobPhsxNormal
	{

		virtual ~BobPhsxSmall()
		{
#ifdef BOOST_BIN
			OnDestructor( "BobPhsxSmall" );
#endif
		}

	
		static void InitializeStatics();

	
		virtual void Set( const boost::shared_ptr<BobPhsx> &phsx );
		void Set( const boost::shared_ptr<BobPhsx> &phsx, Vector2 modsize );

		// Singleton
	
		virtual void InitSingleton();
	
		static boost::shared_ptr<BobPhsxSmall> instance;
	
		const static boost::shared_ptr<BobPhsxSmall> &getInstance();

		// Instancable struct
		BobPhsxSmall();
	};

}


#endif	//#ifndef SMALL
