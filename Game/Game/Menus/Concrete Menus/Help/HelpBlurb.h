#ifndef HELPBLURB
#define HELPBLURB

#include <global_header.h>

namespace CloudberryKingdom
{

	struct HelpBlurb : public CkBaseMenu
	{
	
		struct SetText_ActionHelper : public Lambda
		{
		
			std::shared_ptr<HelpBlurb> hb;
			Localization::Words Word;

		
			SetText_ActionHelper( const std::shared_ptr<HelpBlurb> &hb, Localization::Words Word );

			void Apply();
		};

	
		HelpBlurb();
		std::shared_ptr<HelpBlurb> HelpBlurb_Construct();

		virtual void Init();

		std::shared_ptr<Lambda> SetText_Action( Localization::Words Word );

		void SetText( Localization::Words Word );
	};
}


#endif	//#ifndef HELPBLURB
