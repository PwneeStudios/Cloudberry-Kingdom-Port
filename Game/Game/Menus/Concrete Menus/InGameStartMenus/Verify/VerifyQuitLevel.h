#ifndef VERIFYQUITLEVEL
#define VERIFYQUITLEVEL

#include <small_header.h>

//#include "Core/Graphics/Draw/Quads/QuadClass.h"
//#include "Game/Localization.h"
//#include "Core/Text/EzText.h"
#include "Game/Menus/Concrete Menus/InGameStartMenus/Verify/VerifyBase.h"
//#include "Game/Games/Meta Games/Challenges/Challenge_Base.h"
//#include "Game/Menus/Menu.h"
//#include "Game/Menus/Menu Components/MenuItem.h"
//#include "Game/Tools/Tools.h"


namespace CloudberryKingdom
{

	struct VerifyQuitLevelMenu : public VerifyBaseMenu
	{
	
		virtual ~VerifyQuitLevelMenu()
		{
#ifdef BOOST_BIN
			OnDestructor( "VerifyQuitLevelMenu" );
#endif
		}


		struct VerifyQuitOkLambda : public Lambda_1<boost::shared_ptr<MenuItem> >
		{
		
			VerifyQuitOkLambda();

			void Apply( const boost::shared_ptr<MenuItem> &item );
		};

	
		VerifyQuitLevelMenu( bool CallBaseConstructor );
		boost::shared_ptr<VerifyQuitLevelMenu> VerifyQuitLevelMenu_Construct( bool CallBaseConstructor );
		VerifyQuitLevelMenu( int Control );
		boost::shared_ptr<VerifyQuitLevelMenu> VerifyQuitLevelMenu_Construct( int Control );

		virtual void Init();

	
		void SetPos();
	};
}


#endif	//#ifndef VERIFYQUITLEVEL
