#ifndef VERIFYREMOVE
#define VERIFYREMOVE

#include <global_header.h>

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
