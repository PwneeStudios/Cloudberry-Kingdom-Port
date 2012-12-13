#ifndef VERIFYBASE
#define VERIFYBASE

#include <global_header.h>

namespace CloudberryKingdom
{
	struct VerifyBaseMenu : public CkBaseMenu
	{
		/// <summary>
		/// Called when the user chooses yes/no.
		/// Bool is set to the user's choice.
		/// </summary>
	
		std::shared_ptr<Multicaster_1<bool> > OnSelect;

	
		void DoSelect( bool choice );

		virtual void ReleaseBody();

	
		VerifyBaseMenu();
		std::shared_ptr<VerifyBaseMenu> VerifyBaseMenu_Construct();

		VerifyBaseMenu( int Control );
		std::shared_ptr<VerifyBaseMenu> VerifyBaseMenu_Construct( int Control );

		VerifyBaseMenu( bool CallBaseConstructor );
		std::shared_ptr<VerifyBaseMenu> VerifyBaseMenu_Construct( bool CallBaseConstructor );

	
		virtual void SetHeaderProperties( const std::shared_ptr<EzText> &text );

		std::shared_ptr<QuadClass> Backdrop;
	
		virtual void MakeBackdrop();

	
		Vector2 HeaderPos;
	
		virtual void Init();

	
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef VERIFYBASE
