#ifndef VERIFYDELETESEEDS
#define VERIFYDELETESEEDS

#include <global_header.h>

namespace CloudberryKingdom
{

	struct VerifyDeleteSeeds : public VerifyBaseMenu
	{
	
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
	
		VerifyDeleteSeeds( int Control, int NumSeeds );
		boost::shared_ptr<VerifyDeleteSeeds> VerifyDeleteSeeds_Construct( int Control, int NumSeeds );

		virtual void Init();

	};
}


#endif	//#ifndef VERIFYDELETESEEDS
