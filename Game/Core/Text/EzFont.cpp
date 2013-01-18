#include <global_header.h>

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

	EzFont::EzFont( const std::wstring &FontName, const std::wstring &OutlineFontName, float CharacterSpacing, float LineSpacingMod )
	{
		Initialize( FontName, OutlineFontName, CharacterSpacing, LineSpacing );
		LineSpacing = static_cast<int>( LineSpacing * LineSpacingMod );
	}

	void EzFont::Initialize( const std::wstring &FontName, const std::wstring &OutlineFontName, float CharacterSpacing, int LineSpacing )
	{
		this->CharacterSpacing = CharacterSpacing;
		this->LineSpacing = LineSpacing;

		this->LineSpacing = 133;
	}
}
