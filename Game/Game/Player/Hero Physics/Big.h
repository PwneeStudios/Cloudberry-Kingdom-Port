#ifndef BIG
#define BIG

#include <small_header.h>

//#include "Game/Localization.h"
//#include "Game/Player/Hero Physics/Base.h"
//#include "Game/Objects/Icon.h"
//#include "Game/Player/Cape.h"
#include "Game/Player/Hero Physics/Normal.h"
//#include "Game/Player/Hero Physics/Wheel.h"
//#include "Game/Tools/Tools.h"


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
