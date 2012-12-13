#ifndef ALERTBASE
#define ALERTBASE

#include <global_header.h>

namespace CloudberryKingdom
{

	struct AlertBaseMenu : public CkBaseMenu
	{
	
		struct OkProxy : public Lambda
		{
		
			std::shared_ptr<AlertBaseMenu> abm;

		
			OkProxy( const std::shared_ptr<AlertBaseMenu> &abm );

			void Apply();
		};

		/// <summary>
		/// Called when the user presses OK.
		/// </summary>
	
		std::shared_ptr<Lambda> OnOk;

	
		void Ok();

		virtual void ReleaseBody();

	
		AlertBaseMenu();
		void AlertBaseMenu_Construct();

	
		Localization::Words Message, OkText;
	
		AlertBaseMenu( int Control, Localization::Words Message, Localization::Words OkText );
		void AlertBaseMenu_Construct( int Control, Localization::Words Message, Localization::Words OkText );

		AlertBaseMenu( bool CallBaseConstructor );
		void AlertBaseMenu_Construct( bool CallBaseConstructor );

	
		virtual void SetHeaderProperties( const std::shared_ptr<EzText> &text );

		std::shared_ptr<QuadClass> Backdrop;
	
		virtual void MakeBackdrop();

		virtual void Init();
	};
}


#endif	//#ifndef ALERTBASE
