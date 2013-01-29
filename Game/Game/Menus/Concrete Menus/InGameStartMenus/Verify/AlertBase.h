#ifndef ALERTBASE
#define ALERTBASE

#include <global_header.h>

namespace CloudberryKingdom
{

	struct AlertBaseMenu : public CkBaseMenu
	{

		virtual ~AlertBaseMenu() { }
	
		struct OkProxy : public Lambda
		{
		
			boost::shared_ptr<AlertBaseMenu> abm;

		
			OkProxy( const boost::shared_ptr<AlertBaseMenu> &abm );

			void Apply();
		};

		/// <summary>
		/// Called when the user presses OK.
		/// </summary>
	
		boost::shared_ptr<Lambda> OnOk;

	
		void Ok();

		virtual void ReleaseBody();

	
		AlertBaseMenu();
		boost::shared_ptr<AlertBaseMenu> AlertBaseMenu_Construct();

	
		Localization::Words Message, OkText;
	
		AlertBaseMenu( int Control, Localization::Words Message, Localization::Words OkText );
		boost::shared_ptr<AlertBaseMenu> AlertBaseMenu_Construct( int Control, Localization::Words Message, Localization::Words OkText );

		AlertBaseMenu( bool CallBaseConstructor );
		boost::shared_ptr<AlertBaseMenu> AlertBaseMenu_Construct( bool CallBaseConstructor );

	
		virtual void SetHeaderProperties( const boost::shared_ptr<EzText> &text );

		boost::shared_ptr<QuadClass> Backdrop;
	
		virtual void MakeBackdrop();

		virtual void Init();
	};
}


#endif	//#ifndef ALERTBASE
