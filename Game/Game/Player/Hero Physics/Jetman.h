#ifndef JETMAN
#define JETMAN

#include <small_header.h>

//#include "Core/Graphics/Draw/Object/ObjectClass.h"
//#include "Game/Localization.h"
//#include "Game/Player/Hero Physics/Base.h"
//#include "Game/Objects/Icon.h"
//#include "Game/Player/Cape.h"
#include "Game/Player/Hero Physics/Normal.h"
//#include "Game/Player/Hero Physics/Wheel.h"
//#include "Game/Tools/Tools.h"


namespace CloudberryKingdom
{

	struct BobPhsxJetman : public BobPhsxNormal
	{

		virtual ~BobPhsxJetman()
		{
#ifdef BOOST_BIN
			OnDestructor( "BobPhsxJetman" );
#endif
		}

	
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
