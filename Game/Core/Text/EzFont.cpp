#include <global_header.h>

namespace CloudberryKingdom
{

	EzFont::EzFont( const std::wstring &FontName )
	{
		Font = Tools::GameClass->getContent()->Load<SpriteFont>(FontName);
		CharacterSpacing = Font->Spacing;

		//LineSpacing = Font.LineSpacing;
		LineSpacing = static_cast<int>( Font->MeasureString( std::wstring( L"abc" ) ).Y );
	}

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
		FixFont();
	}

	void EzFont::FixFont()
	{
		Font->Spacing = CharacterSpacing;
		Font->LineSpacing = LineSpacing;
	}

	void EzFont::Initialize( const std::wstring &FontName, const std::wstring &OutlineFontName, float CharacterSpacing, int LineSpacing )
	{
		this->CharacterSpacing = CharacterSpacing;
		this->LineSpacing = LineSpacing;

		Font = Tools::GameClass->getContent()->Load<SpriteFont>(FontName);
		FixFont();

		if ( OutlineFontName.length() > 1 )
		{
			OutlineFont = Tools::GameClass->getContent()->Load<SpriteFont>(OutlineFontName);
			OutlineFont->Spacing = CharacterSpacing;
			OutlineFont->LineSpacing = LineSpacing;
		}
		else
			OutlineFont.reset();

		this->LineSpacing = static_cast<int>( Font->MeasureString( std::wstring( L"abc" ) ).Y );
	}
}
