#ifndef NEWHERO
#define NEWHERO

#include <small_header.h>

//#include "Core/Graphics/Draw/DrawPile.h"
//#include "Core/Text/EzText.h"
#include "Game/Objects/Game Objects/GameObjects/GUI_Panel.h"
//#include "Game/Tools/Resources.h"
//#include "Game/Tools/Tools.h"


namespace CloudberryKingdom
{

	struct NewHero_GUI : public GUI_Panel
	{

		virtual ~NewHero_GUI()
		{
#ifdef BOOST_BIN
			OnDestructor( "NewHero_GUI" );
#endif
		}


		virtual void OnAdd();

		boost::shared_ptr<EzText> text;
		NewHero_GUI( const std::wstring &str );
		boost::shared_ptr<NewHero_GUI> NewHero_GUI_Construct( const std::wstring &str );
		NewHero_GUI( const std::wstring &str, Vector2 shift, float scale, bool perma );
		boost::shared_ptr<NewHero_GUI> NewHero_GUI_Construct( const std::wstring &str, Vector2 shift, float scale, bool perma );

		static boost::shared_ptr<NewHero_GUI> HeroTitle( const std::wstring &str );

	
		bool Perma;
		void Init( const std::wstring &str, Vector2 shift, float scale, bool perma );

		int Count;
	
		virtual void MyPhsxStep();

	
		void InitializeInstanceFields();
	};

}


#endif	//#ifndef NEWHERO
