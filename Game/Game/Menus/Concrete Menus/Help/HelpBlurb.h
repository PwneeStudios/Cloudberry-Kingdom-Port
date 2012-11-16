#ifndef HELPBLURB
#define HELPBLURB

#include "../Game/Menus/CkBaseMenu.h"
#include "../Core/Lambdas/Lambda.h"
#include "../Game/Localization.h"
#include <tchar.h>

namespace CloudberryKingdom
{
	class Lambda;
}


//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
using namespace Microsoft::Xna::Framework;

namespace CloudberryKingdom
{
	class HelpBlurb : public CkBaseMenu
	{
	private:
		class SetText_ActionHelper : public Lambda
		{
		private:
			std::shared_ptr<HelpBlurb> hb;
			Localization::Words Word;

		public:
			SetText_ActionHelper( const std::shared_ptr<HelpBlurb> &hb, Localization::Words Word );

			void Apply();
		};

	public:
		HelpBlurb();

		virtual void Init();

		std::shared_ptr<Lambda> SetText_Action( Localization::Words Word );

		void SetText( Localization::Words Word );
	};
}


#endif	//#ifndef HELPBLURB
