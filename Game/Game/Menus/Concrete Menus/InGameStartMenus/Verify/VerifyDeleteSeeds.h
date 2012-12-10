#ifndef VERIFYDELETESEEDS
#define VERIFYDELETESEEDS

#include <global_header.h>

namespace CloudberryKingdom
{
	struct MenuItem;
}

namespace CloudberryKingdom
{
	struct Menu;
}


namespace CloudberryKingdom
{
	struct VerifyDeleteSeeds : public VerifyBaseMenu
	{
	
		struct VerifyDeleteYesGoLambda : public Lambda_1<std::shared_ptr<MenuItem> >
		{
		
			std::shared_ptr<VerifyDeleteSeeds> vds;
		
			VerifyDeleteYesGoLambda( const std::shared_ptr<VerifyDeleteSeeds> &vds );

			void Apply( const std::shared_ptr<MenuItem> &item );
		};

	
		struct VerifyDeleteOnXLambda : public LambdaFunc_1<std::shared_ptr<Menu> , bool>
		{
		
			std::shared_ptr<VerifyDeleteSeeds> vds;
		
			VerifyDeleteOnXLambda( const std::shared_ptr<VerifyDeleteSeeds> &vds );

			bool Apply( const std::shared_ptr<Menu> &item );
		};

	
		struct VerifyDeleteNoGoLambda : public Lambda_1<std::shared_ptr<MenuItem> >
		{
		
			std::shared_ptr<VerifyDeleteSeeds> vds;
		
			VerifyDeleteNoGoLambda( const std::shared_ptr<VerifyDeleteSeeds> &vds );

			void Apply( const std::shared_ptr<MenuItem> &item );
		};
	
		int NumSeeds;
	
		VerifyDeleteSeeds( int Control, int NumSeeds );

		virtual void Init();

	};
}


#endif	//#ifndef VERIFYDELETESEEDS
