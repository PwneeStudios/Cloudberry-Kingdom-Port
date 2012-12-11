#ifndef COLORSCHEMEMANAGER
#define COLORSCHEMEMANAGER

#include <global_header.h>

namespace CloudberryKingdom
{

	struct CapeOnLambda : public Lambda_1<std::shared_ptr<Bob> >
	{
	
		CapeOnLambda();

		void Apply( const std::shared_ptr<Bob> &bob );
	};

	struct ColorSchemeManager
	{

	
		static void InitializeStatics();

	
		static std::shared_ptr<CapeOnLambda> CapeOn;


	
		static std::vector<ColorScheme> ColorSchemes, ComputerColorSchemes;

	
		static void AddScheme( ColorScheme scheme, bool ValidComputerScheme );

	
		static std::vector<std::shared_ptr<MenuListItem> > HatList, ColorList, CapeColorList, CapeOutlineColorList, TextureList, OutlineList;

		static std::vector<std::shared_ptr<Hat> > HatInfo;
		static std::vector<std::shared_ptr<Hat> > BeardInfo;

		static std::vector<std::shared_ptr<MenuListItem> > ClrList;

		static std::shared_ptr<ClrTextFx> None;

	
		static std::shared_ptr<MenuListItem> _i( int Guid, int Price, Color Clr, Matrix M, Localization::Words Name );

		static std::shared_ptr<MenuListItem> _i( int Guid, int Price, Color Clr, Color HighlightClr, Matrix M, Localization::Words Name );

		static std::shared_ptr<MenuListItem> _i( int Guid, int Price, Color Clr, Matrix M, const std::shared_ptr<EzEffect> &Effect, Localization::Words Name );

	
		static void InitColorSchemes();

		static std::vector<std::shared_ptr<MenuListItem> > MakeUnique( std::vector<std::shared_ptr<MenuListItem> > &list );
	};
}


#endif	//#ifndef COLORSCHEMEMANAGER
