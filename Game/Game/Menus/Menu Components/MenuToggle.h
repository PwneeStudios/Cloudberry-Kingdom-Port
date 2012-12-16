#ifndef MENUTOGGLE
#define MENUTOGGLE

#include <global_header.h>

namespace CloudberryKingdom
{
	struct MenuToggle : public MenuItem
	{
	
		MenuToggle( const boost::shared_ptr<EzFont> &Font );

	
		bool MyState;
	
		void Toggle( bool state );

		boost::shared_ptr<Lambda_1<bool> > OnToggle;
		virtual void PhsxStep( bool Selected );

	
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef MENUTOGGLE
