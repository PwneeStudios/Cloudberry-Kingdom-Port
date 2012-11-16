#ifndef VERIFYREMOVE
#define VERIFYREMOVE

#include "VerifyBase.h"
#include "../Core/Lambdas/Lambda_1.h"
#include <string>

namespace CloudberryKingdom
{
	class MenuItem;
}


namespace CloudberryKingdom
{
	class VerifyRemoveMenu : public VerifyBaseMenu
	{
	private:
		class VerifyRemoveYesLambda : public Lambda_1<MenuItem*>
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
