#ifndef EZFONT
#define EZFONT

#include <string>
#include <tchar.h>

namespace Microsoft
{
	namespace Xna
	{
		namespace Framework
		{
			namespace Graphics
			{
				class SpriteFont;
			}
		}
	}
}


using namespace Microsoft::Xna::Framework::Graphics;

namespace CloudberryKingdom
{
	class EzFont
	{
	public:
		std::shared_ptr<SpriteFont> Font, OutlineFont;
		float CharacterSpacing;
		int LineSpacing;

		EzFont( const std::wstring &FontName );

		EzFont( const std::wstring &FontName, float CharacterSpacing, int LineSpacing );

		EzFont( const std::wstring &FontName, const std::wstring &OutlineFontName, float CharacterSpacing, int LineSpacing );

		EzFont( const std::wstring &FontName, const std::wstring &OutlineFontName, float CharacterSpacing, float LineSpacingMod );

		void FixFont();

	private:
		void Initialize( const std::wstring &FontName, const std::wstring &OutlineFontName, float CharacterSpacing, int LineSpacing );
	};
}


#endif	//#ifndef EZFONT
