#ifndef COLORSCHEMEMANAGER
#define COLORSCHEMEMANAGER

#include <small_header.h>

//#include "Core/Effects/EzEffect.h"
//#include "Core/Graphics/Draw/Object/ObjectClass.h"
#include "Game/Localization.h"
//#include "Core/Tools/ColorHelper.h"
//#include "Game/Player/Buyable.h"
//#include "Game/Player/ClrTextFx.h"
#include "Game/Player/ColorScheme.h"
//#include "Game/Objects/Bob/Bob.h"
//#include "Game/Objects/In Game Objects/Obstacles/CloudberryKingdom.Fireball.h"
//#include "Game/Tools/Tools.h"


namespace CloudberryKingdom
{

	struct CapeOnLambda : public Lambda_1<boost::shared_ptr<Bob> >
	{
	
		CapeOnLambda();

		void Apply( const boost::shared_ptr<Bob> &bob );
	};

	struct ColorSchemeManager
	{

	
		static void InitializeStatics();

	
		static boost::shared_ptr<CapeOnLambda> CapeOn;


	
		static std::vector<ColorScheme> ColorSchemes, ComputerColorSchemes;

	
		static void AddScheme( ColorScheme scheme, bool ValidComputerScheme );

	
		static std::vector<boost::shared_ptr<MenuListItem> > HatList, ColorList, CapeColorList, CapeOutlineColorList, TextureList, OutlineList;

		static std::vector<boost::shared_ptr<Hat> > HatInfo;
		static std::vector<boost::shared_ptr<Hat> > BeardInfo;

		static std::vector<boost::shared_ptr<MenuListItem> > ClrList;

		static boost::shared_ptr<ClrTextFx> None;

	
		static boost::shared_ptr<MenuListItem> _i( int Guid, int Price, Color Clr, Matrix M, Localization::Words Name );

		static boost::shared_ptr<MenuListItem> _i( int Guid, int Price, Color Clr, Color HighlightClr, Matrix M, Localization::Words Name );

		static boost::shared_ptr<MenuListItem> _i( int Guid, int Price, Color Clr, Matrix M, const boost::shared_ptr<EzEffect> &Effect, Localization::Words Name );

	
		static void InitColorSchemes();

		static std::vector<boost::shared_ptr<MenuListItem> > MakeUnique( std::vector<boost::shared_ptr<MenuListItem> > &list );
	};
}


#endif	//#ifndef COLORSCHEMEMANAGER
