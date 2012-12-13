#ifndef VERIFYQUITLEVEL
#define VERIFYQUITLEVEL

#include <global_header.h>

namespace CloudberryKingdom
{

	struct VerifyQuitLevelMenu : public VerifyBaseMenu
	{
	
		struct VerifyQuitOkLambda : public Lambda_1<std::shared_ptr<MenuItem> >
		{
		
			VerifyQuitOkLambda();

			void Apply( const std::shared_ptr<MenuItem> &item );
		};

	
		VerifyQuitLevelMenu( bool CallBaseConstructor );
		std::shared_ptr<VerifyQuitLevelMenu> VerifyQuitLevelMenu_Construct( bool CallBaseConstructor );
		VerifyQuitLevelMenu( int Control );
		std::shared_ptr<VerifyQuitLevelMenu> VerifyQuitLevelMenu_Construct( int Control );

		virtual void Init();

	
		void SetPos();
	};
}


#endif	//#ifndef VERIFYQUITLEVEL
