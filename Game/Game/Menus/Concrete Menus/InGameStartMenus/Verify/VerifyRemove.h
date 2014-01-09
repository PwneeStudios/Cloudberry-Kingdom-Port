#ifndef VERIFYREMOVE
#define VERIFYREMOVE

#include <small_header.h>

//#include "Core/Graphics/Draw/Quads/QuadClass.h"
//#include "Game/Localization.h"
//#include "Core/Text/EzText.h"
#include "Game/Menus/Concrete Menus/InGameStartMenus/Verify/VerifyBase.h"
//#include "Game/Menus/Menu.h"
//#include "Game/Tools/EzStorage.h"
//#include "Game/Player/PlayerManager.h"
//#include "Game/Menus/Menu Components/MenuItem.h"
//#include "Game/Tools/Tools.h"


namespace CloudberryKingdom
{

	struct VerifyRemoveMenu : public VerifyBaseMenu
	{
	
		virtual ~VerifyRemoveMenu()
		{
#ifdef BOOST_BIN
			OnDestructor( "VerifyRemoveMenu" );
#endif
		}


		struct VerifyRemoveYesLambda : public Lambda_1<boost::shared_ptr<MenuItem> >
		{
		
			boost::shared_ptr<VerifyRemoveMenu> vrm;
		
			VerifyRemoveYesLambda( const boost::shared_ptr<VerifyRemoveMenu> &vrm );

			void Apply( const boost::shared_ptr<MenuItem> &_item );
		};
	
		VerifyRemoveMenu( int Control );
		boost::shared_ptr<VerifyRemoveMenu> VerifyRemoveMenu_Construct( int Control );

		virtual void Init();

		void SetPos();

		static bool YesChosen;

        void _Yes( boost::shared_ptr<MenuItem> _item );

	};
}


#endif	//#ifndef VERIFYREMOVE
