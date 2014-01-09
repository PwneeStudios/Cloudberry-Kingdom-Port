#ifndef DOUBLE
#define DOUBLE

#include <small_header.h>

//#include "Core/Graphics/Draw/Object/ObjectClass.h"
//#include "Game/Localization.h"
//#include "Game/Player/Hero Physics/Base.h"
//#include "Game/Objects/Icon.h"
//#include "Game/Player/Cape.h"
#include "Game/Player/Hero Physics/Normal.h"
//#include "Game/Tools/Tools.h"


namespace CloudberryKingdom
{

	struct BobPhsxDouble : public BobPhsxNormal
	{

		virtual ~BobPhsxDouble()
		{
#ifdef BOOST_BIN
			OnDestructor( "BobPhsxDouble" );
#endif
		}

	
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
