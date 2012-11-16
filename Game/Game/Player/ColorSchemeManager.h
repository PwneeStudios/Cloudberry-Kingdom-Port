#ifndef COLORSCHEMEMANAGER
#define COLORSCHEMEMANAGER

#include <global_header.h>

namespace CloudberryKingdom
{
	class Bob;
}

namespace CloudberryKingdom
{
	class MenuListItem;
}

namespace CloudberryKingdom
{
	class Hat;
}

namespace CloudberryKingdom
{
	class EzEffect;
}










namespace CloudberryKingdom
{
	class ColorSchemeManager
	{
	private:
		class CapeOnLambda : public Lambda_1<Bob*>
		{
		public:
			CapeOnLambda();

			void Apply( const std::shared_ptr<Bob> &bob );
		};

	private:
		static std::shared_ptr<CapeOnLambda> CapeOn;


	public:
		static std::vector<ColorScheme> ColorSchemes, ComputerColorSchemes;

	private:
		static void AddScheme( ColorScheme scheme, bool ValidComputerScheme );

	public:
		static std::vector<MenuListItem*> HatList, ColorList, CapeColorList, CapeOutlineColorList, TextureList, OutlineList;

		static std::vector<Hat*> HatInfo;
		static std::vector<Hat*> BeardInfo;

		static std::vector<MenuListItem*> ClrList;

		static ClrTextFx None;

	private:
		static std::shared_ptr<MenuListItem> _i( int Guid, int Price, Color Clr, Matrix M, Localization::Words Name );

		static std::shared_ptr<MenuListItem> _i( int Guid, int Price, Color Clr, Color HighlightClr, Matrix M, Localization::Words Name );

		static std::shared_ptr<MenuListItem> _i( int Guid, int Price, Color Clr, Matrix M, const std::shared_ptr<EzEffect> &Effect, Localization::Words Name );

	public:
		static void InitColorSchemes();

		static std::vector<MenuListItem*> MakeUnique( std::vector<MenuListItem*> &list );
	};
}


#endif	//#ifndef COLORSCHEMEMANAGER
