#ifndef MENUTOGGLE
#define MENUTOGGLE

#include <global_header.h>

namespace CloudberryKingdom
{
	class EzFont;
}

namespace CloudberryKingdom
{
	class Lambda_1;
}
namespace CloudberryKingdom
{
	class MenuToggle : public MenuItem
	{
	public:
		MenuToggle( const std::shared_ptr<EzFont> &Font );

	private:
		bool MyState;
	public:
		void Toggle( bool state );

		std::shared_ptr<Lambda_1<bool> > OnToggle;
		virtual void PhsxStep( bool Selected );

	private:
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef MENUTOGGLE
