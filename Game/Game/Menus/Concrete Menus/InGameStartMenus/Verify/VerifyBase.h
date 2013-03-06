#ifndef VERIFYBASE
#define VERIFYBASE

#include <global_header.h>

#include "Core/Lambdas/Multicaster_1.h"

namespace CloudberryKingdom
{

	struct VerifyBaseMenu : public CkBaseMenu
	{

		virtual ~VerifyBaseMenu()
		{
#ifdef BOOST_BIN
			OnDestructor( "VerifyBaseMenu" );
#endif
		}


		/// <summary>
		/// Called when the user chooses yes/no.
		/// Bool is set to the user's choice.
		/// </summary>
	
		boost::shared_ptr<Multicaster_1<bool> > OnSelect;

	
		void DoSelect( bool choice );

		virtual void ReleaseBody();

	
		VerifyBaseMenu();
		boost::shared_ptr<VerifyBaseMenu> VerifyBaseMenu_Construct();

		VerifyBaseMenu( int Control, bool DoEnableBounce );
		boost::shared_ptr<VerifyBaseMenu> VerifyBaseMenu_Construct( int Control, bool DoEnableBounce );

		VerifyBaseMenu( bool CallBaseConstructor );
		boost::shared_ptr<VerifyBaseMenu> VerifyBaseMenu_Construct( bool CallBaseConstructor );

	
		virtual void SetHeaderProperties( const boost::shared_ptr<EzText> &text );

		boost::shared_ptr<QuadClass> Backdrop;
	
		virtual void MakeBackdrop();

	
		Vector2 HeaderPos;
	
		virtual void Init();

	
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef VERIFYBASE
