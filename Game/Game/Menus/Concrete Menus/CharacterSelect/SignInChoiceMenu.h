#ifndef SIGNINCHOICEMENU
#define SIGNINCHOICEMENU

#include "../Game/Menus/CkBaseMenu.h"
#include "../Core/Lambdas/Lambda_1.h"
#include <string>
#include <tchar.h>

namespace CloudberryKingdom
{
	class MenuItem;
}

namespace CloudberryKingdom
{
	class CharacterSelect;
}


//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;
using namespace Microsoft::Xna::Framework;

#if defined(PC_VERSION)
#elif defined(XBOX) || defined(XBOX_SIGNIN)
using namespace Microsoft::Xna::Framework::GamerServices;
#endif



namespace CloudberryKingdom
{
#if defined(NOT_PC) && (defined(XBOX) || defined(XBOX_SIGNIN))
	class SignInMenu : public CkBaseMenu
	{
	private:
		class SignInNoLambda : public Lambda_1<MenuItem*>
		{
		private:
			std::shared_ptr<SignInMenu> sim;
		public:
			SignInNoLambda( const std::shared_ptr<SignInMenu> &sim );

			void Apply( const std::shared_ptr<MenuItem> &item );
		};

	private:
		class SignInYesLambda : public Lambda_1<MenuItem*>
		{
		private:
			std::shared_ptr<SignInMenu> sim;
		public:
			SignInYesLambda( const std::shared_ptr<SignInMenu> &sim );

			void Apply( const std::shared_ptr<MenuItem> &item );
		};

	private:
		std::shared_ptr<CharacterSelect> MyCharacterSelect;
	public:
		SignInMenu( int Control, const std::shared_ptr<CharacterSelect> &MyCharacterSelect );

	protected:
		virtual void ReleaseBody();

	public:
		virtual void Init();

	private:
		void MakeSignInChoiceMenu();

		void SetPos();

#if defined(XBOX) || defined(XBOX_SIGNIN)
		bool GamerGuideUp;
		bool GuideUpPhsxStep();
#endif

	protected:
		virtual void MyPhsxStep();

	private:
		void InitializeInstanceFields();
	};
#endif
}


#endif	//#ifndef SIGNINCHOICEMENU
