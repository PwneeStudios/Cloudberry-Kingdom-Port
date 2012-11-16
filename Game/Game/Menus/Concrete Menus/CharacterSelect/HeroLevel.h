#ifndef HEROLEVEL
#define HEROLEVEL

#include <global_header.h>

namespace CloudberryKingdom
{
	class CharacterSelect;
}

namespace CloudberryKingdom
{
	class EzText;
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
	class HeroLevel : public CkBaseMenu
	{
	private:
		std::shared_ptr<CharacterSelect> MyCharacterSelect;
	public:
		HeroLevel( int Control, const std::shared_ptr<CharacterSelect> &MyCharacterSelect );

	protected:
		virtual void ReleaseBody();

	private:
		std::shared_ptr<EzText> Text;
	public:
		virtual void Init();

		bool ShowHeroLevel;
	private:
		void SetHeroLevel();

	private:
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef HEROLEVEL
