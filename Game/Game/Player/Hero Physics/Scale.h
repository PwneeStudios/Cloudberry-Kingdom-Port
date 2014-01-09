#ifndef SCALE
#define SCALE

#include <small_header.h>

//#include "Game/Localization.h"
//#include "Game/Player/Hero Physics/Base.h"
//#include "Game/Objects/Icon.h"
//#include "Game/Player/Cape.h"
#include "Game/Player/Hero Physics/Normal.h"
//#include "Game/Tools/Tools.h"


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
