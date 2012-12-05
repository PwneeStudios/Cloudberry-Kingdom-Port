#ifndef VERIFYREMOVE
#define VERIFYREMOVE

#include <global_header.h>

namespace CloudberryKingdom
{
	class MenuItem;
}


namespace CloudberryKingdom
{
	class VerifyRemoveMenu : public VerifyBaseMenu
	{
	private:
		class VerifyRemoveYesLambda : public Lambda_1<std::shared_ptr<MenuItem> >
		{
		private:
			std::shared_ptr<VerifyRemoveMenu> vrm;
		public:
			VerifyRemoveYesLambda( const std::shared_ptr<VerifyRemoveMenu> &vrm );

			void Apply( const std::shared_ptr<MenuItem> &_item );
		};
	public:
		VerifyRemoveMenu( int Control );

		virtual void Init();

	};
}


#endif	//#ifndef VERIFYREMOVE
