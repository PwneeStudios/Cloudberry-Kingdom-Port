#ifndef HELPBLURB
#define HELPBLURB

#include <small_header.h>

//#include "Core/Graphics/Draw/DrawPile.h"
//#include "Core/Graphics/Draw/Quads/QuadClass.h"
#include "Game/Localization.h"
//#include "Core/Text/EzText.h"
#include "Game/Menus/CkBaseMenu.h"


namespace CloudberryKingdom
{

	struct HelpBlurb : public CkBaseMenu
	{

		virtual ~HelpBlurb()
		{
#ifdef BOOST_BIN
			OnDestructor( "HelpBlurb" );
#endif
		}


		struct SetText_ActionHelper : public Lambda
		{
		
			boost::shared_ptr<HelpBlurb> hb;
			Localization::Words Word;

		
			SetText_ActionHelper( const boost::shared_ptr<HelpBlurb> &hb, Localization::Words Word );

			void Apply();
		};

	
		HelpBlurb();
		boost::shared_ptr<HelpBlurb> HelpBlurb_Construct();

		virtual void Init();

		boost::shared_ptr<Lambda> SetText_Action( Localization::Words Word );

		void SetText( Localization::Words Word );
	};
}


#endif	//#ifndef HELPBLURB
