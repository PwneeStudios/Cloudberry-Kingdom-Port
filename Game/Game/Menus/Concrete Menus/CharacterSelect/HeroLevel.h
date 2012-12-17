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
	
		boost::shared_ptr<CharacterSelect> MyCharacterSelect;
	
		HeroLevel( int Control, const boost::shared_ptr<CharacterSelect> &MyCharacterSelect );
		boost::shared_ptr<HeroLevel> HeroLevel_Construct( int Control, const boost::shared_ptr<CharacterSelect> &MyCharacterSelect );

	
		virtual void ReleaseBody();

	
		boost::shared_ptr<EzText> Text;
	
		virtual void Init();

		bool ShowHeroLevel;
	
		void SetHeroLevel();

	
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef HEROLEVEL
