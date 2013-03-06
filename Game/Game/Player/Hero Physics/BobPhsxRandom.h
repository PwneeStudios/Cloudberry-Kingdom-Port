#ifndef BOB_PHSX_RANDOM_H
#define BOB_PHSX_RANDOM_H

#include <global_header.h>

namespace CloudberryKingdom
{

	struct BobPhsxRandom : public BobPhsx
	{
	
		virtual ~BobPhsxRandom()
		{
#ifdef BOOST_BIN
			OnDestructor( "BobPhsxRandom" );
#endif
		}


		static void InitializeStatics();

	
		// Singleton
		virtual void InitSingleton();
	
		static boost::shared_ptr<BobPhsxRandom> instance;
	
		static const boost::shared_ptr<BobPhsxRandom> &getInstance();

		static boost::shared_ptr<BobPhsx> ChooseHeroType();

		virtual boost::shared_ptr<BobPhsx> Clone();
		void CopyTo( const boost::shared_ptr<BobPhsxRandom> &bob );

		// Instancable struct
		BobPhsxRandom();
	};

}


#endif	//#ifndef RANDOM
