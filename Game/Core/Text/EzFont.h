#ifndef EZFONT
#define EZFONT

#include <global_header.h>

#include "Hacks/XNA/SpriteFont.h"

namespace CloudberryKingdom
{
	struct EzFont
	{
	
		boost::shared_ptr<HackSpriteFont> HFont, HOutlineFont;
		float CharacterSpacing;
		int LineSpacing;

		EzFont( const std::wstring &FontName, float CharacterSpacing, int LineSpacing );

		EzFont( const std::wstring &FontName, const std::wstring &OutlineFontName, float CharacterSpacing, int LineSpacing );

		void Initialize( const std::wstring &FontName, const std::wstring &OutlineFontName, float CharacterSpacing, int LineSpacing );
	};
}


#endif	//#ifndef EZFONT
