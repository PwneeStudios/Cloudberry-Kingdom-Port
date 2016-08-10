#ifndef VERIFYDELETESEEDS
#define VERIFYDELETESEEDS

#include <small_header.h>

//#include "Core/Graphics/Draw/Quads/QuadClass.h"
//#include "Game/Localization.h"
//#include "Core/Text/EzText.h"
#include "Game/Menus/Concrete Menus/InGameStartMenus/Verify/VerifyBase.h"
//#include "Game/Menus/Menu Components/MenuItem.h"


namespace CloudberryKingdom
{

	struct VerifyDeleteSeeds : public VerifyBaseMenu
	{

		virtual ~VerifyDeleteSeeds()
		{
#ifdef BOOST_BIN
			OnDestructor( "VerifyDeleteSeeds" );
#endif
		}

	
		struct VerifyDeleteYesGoLambda : public Lambda_1<boost::shared_ptr<MenuItem> >
		{
		
			boost::shared_ptr<VerifyDeleteSeeds> vds;
		
			VerifyDeleteYesGoLambda( const boost::shared_ptr<VerifyDeleteSeeds> &vds );

			void Apply( const boost::shared_ptr<MenuItem> &item );
		};

	
		struct VerifyDeleteOnXLambda : public LambdaFunc_1<boost::shared_ptr<Menu> , bool>
		{
		
			boost::shared_ptr<VerifyDeleteSeeds> vds;
		
			VerifyDeleteOnXLambda( const boost::shared_ptr<VerifyDeleteSeeds> &vds );

			bool Apply( const boost::shared_ptr<Menu> &item );
		};

	
		struct VerifyDeleteNoGoLambda : public Lambda_1<boost::shared_ptr<MenuItem> >
		{
		
			boost::shared_ptr<VerifyDeleteSeeds> vds;
		
			VerifyDeleteNoGoLambda( const boost::shared_ptr<VerifyDeleteSeeds> &vds );

			void Apply( const boost::shared_ptr<MenuItem> &item );
		};
	
		int NumSeeds;
	
		VerifyDeleteSeeds( int Control, int NumSeeds, bool DoEnableBounce );
		boost::shared_ptr<VerifyDeleteSeeds> VerifyDeleteSeeds_Construct( int Control, int NumSeeds, bool DoEnableBounce );

		virtual void Init();

	};
}


#endif	//#ifndef VERIFYDELETESEEDS
