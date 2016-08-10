#ifndef JOINTEXT
#define JOINTEXT

#include <small_header.h>

//#include "Core/Graphics/Draw/DrawPile.h"
//#include "Core/Graphics/Draw/Quads/QuadClass.h"
//#include "Game/Localization.h"
//#include "Core/Input/ButtonCheck.h"
//#include "Core/Text/EzText.h"
#include "Game/Menus/CkBaseMenu.h"
//#include "Game/Menus/Concrete Menus/CharacterSelect/CharacterSelect.h"
//#include "Game/Menus/Concrete Menus/CharacterSelect/CharSelectManager.h"
//#include "Game/Menus/Concrete Menus/CharacterSelect/GamerTag.h"
//#include "Game/Menus/Concrete Menus/CharacterSelect/SimpleMenu.h"
//#include "Game/Tools/Resources.h"
//#include "Game/Tools/Tools.h"


#if defined(PC_VERSION)
#elif defined(XBOX) || defined(XBOX_SIGNIN)

#endif

namespace CloudberryKingdom
{
	struct JoinText : public CkBaseMenu
	{

		virtual ~JoinText()
		{
#ifdef BOOST_BIN
			OnDestructor( "JoinText" );
#endif
		}

	
		boost::shared_ptr<CharacterSelect> MyCharacterSelect;
	
		JoinText( int Control, const boost::shared_ptr<CharacterSelect> &MyCharacterSelect );
		boost::shared_ptr<JoinText> JoinText_Construct( int Control, const boost::shared_ptr<CharacterSelect> &MyCharacterSelect );

		virtual void ReleaseBody();
	
		boost::shared_ptr<EzText> Text;
	
		virtual void Init();

		static void ScaleGamerTag( const boost::shared_ptr<EzText> &GamerTag_Renamed );
	
		void SetGamerTag();

		void MyDraw();
		virtual void MyPhsxStep();

	};
}


#endif	//#ifndef JOINTEXT
