#ifndef HEROLEVEL
#define HEROLEVEL

#include <small_header.h>

//#include "Core/Graphics/Draw/DrawPile.h"
//#include "Core/Text/EzText.h"
#include "Game/Menus/CkBaseMenu.h"
//#include "Game/Menus/Concrete Menus/CharacterSelect/CharacterSelect.h"
//#include "Game/Tools/Resources.h"
//#include "Game/Tools/Tools.h"


#if defined(PC_VERSION)
#elif defined(XBOX) || defined(XBOX_SIGNIN)

#endif

namespace CloudberryKingdom
{

	struct HeroLevel : public CkBaseMenu
	{

		virtual ~HeroLevel()
		{
#ifdef BOOST_BIN
			OnDestructor( "HeroLevel" );
#endif
		}

	
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
