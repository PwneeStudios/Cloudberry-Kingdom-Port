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
		void VerifyBaseMenu_Construct();

		VerifyBaseMenu( int Control );
		void VerifyBaseMenu_Construct( int Control );

		VerifyBaseMenu( bool CallBaseConstructor );
		void VerifyBaseMenu_Construct( bool CallBaseConstructor );

	
		virtual void SetHeaderProperties( const std::shared_ptr<EzText> &text );

		std::shared_ptr<QuadClass> Backdrop;
	
		virtual void MakeBackdrop();

	
		Vector2 HeaderPos;
	
		virtual void Init();

	
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef VERIFYBASE
