#ifndef VERIFYREMOVE
#define VERIFYREMOVE

#include <global_header.h>

namespace CloudberryKingdom
{
	struct MenuItem;
}


namespace CloudberryKingdom
{
	struct VerifyRemoveMenu : public VerifyBaseMenu
	{
	
		struct VerifyRemoveYesLambda : public Lambda_1<std::shared_ptr<MenuItem> >
		{
		
			std::shared_ptr<VerifyRemoveMenu> vrm;
		
			VerifyRemoveYesLambda( const std::shared_ptr<VerifyRemoveMenu> &vrm );

			void Apply( const std::shared_ptr<MenuItem> &_item );
		};
	
		VerifyRemoveMenu( int Control );

		virtual void Init();

	};
}


#endif	//#ifndef VERIFYREMOVE
