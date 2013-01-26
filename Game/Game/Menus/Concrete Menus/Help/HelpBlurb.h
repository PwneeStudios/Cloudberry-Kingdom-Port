#ifndef HELPBLURB
#define HELPBLURB

#include <global_header.h>

namespace CloudberryKingdom
{

	struct HelpBlurb : public CkBaseMenu
	{

		virtual ~HelpBlurb() { }

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
