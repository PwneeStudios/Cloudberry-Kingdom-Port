#include <small_header.h>
#include "Core/Text/EzFont.h"

#include "Core/Graphics/QuadDrawer.h"


namespace CloudberryKingdom
{

	EzFont::EzFont( const std::wstring &FontName, float CharacterSpacing, int LineSpacing )
	{
		Initialize( FontName, std::wstring( L"" ), CharacterSpacing, LineSpacing );
	}

	EzFont::EzFont( const std::wstring &FontName, const std::wstring &OutlineFontName, float CharacterSpacing, int LineSpacing )
	{
		Initialize( FontName, OutlineFontName, CharacterSpacing, LineSpacing );
	}

	void EzFont::Initialize( const std::wstring &FontName, const std::wstring &OutlineFontName, float CharacterSpacing, int LineSpacing )
	{
		this->CharacterSpacing = CharacterSpacing;
		this->LineSpacing = LineSpacing;

		this->LineSpacing = 133;
	}
}
