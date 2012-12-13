#ifndef HEROLEVEL
#define HEROLEVEL

#include <global_header.h>

#if defined(PC_VERSION)
#elif defined(XBOX) || defined(XBOX_SIGNIN)

#endif

namespace CloudberryKingdom
{

	struct HeroLevel : public CkBaseMenu
	{
	
		std::shared_ptr<CharacterSelect> MyCharacterSelect;
	
		HeroLevel( int Control, const std::shared_ptr<CharacterSelect> &MyCharacterSelect );
		void HeroLevel_Construct( int Control, const std::shared_ptr<CharacterSelect> &MyCharacterSelect );

	
		virtual void ReleaseBody();

	
		std::shared_ptr<EzText> Text;
	
		virtual void Init();

		bool ShowHeroLevel;
	
		void SetHeroLevel();

	
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef HEROLEVEL
