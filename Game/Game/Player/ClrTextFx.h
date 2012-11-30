#ifndef CLRTEXTFX
#define CLRTEXTFX

#include <global_header.h>

namespace CloudberryKingdom
{

	class ClrTextFx : public Buyable
	{
	public:
		int Guid, Price;
		int GetGuid();
		int GetPrice();

		Localization::Words Name;

		/// <summary>
		/// A function that may modify the player object.
		/// </summary>
		std::shared_ptr<Lambda_1<std::shared_ptr<Bob> > > ModObject;

		std::shared_ptr<EzTexture> PicTexture;
		Vector2 PicScale;

		bool UsePaintTexture;

		bool Equals( ClrTextFx a );

		/// <summary>
		/// This color is used instead of a texture in situations where the texture can't be applied.
		/// Example: the Spaceship object and the colored Gamer Tags (player names)
		/// </summary>
		Color DetailColor;

		Color Clr;
		std::shared_ptr<EzTexture> Texture;
		std::shared_ptr<EzEffect> Effect;

		/// <summary>
		/// This matrix is used to hue rotate Bob's outfit.
		/// </summary>
		Matrix M;

		static std::vector<ClrTextFx> FullList;

		ClrTextFx( int Guid, int Price, Color color, Matrix M );

		ClrTextFx( int Guid, int Price, Color color, Matrix M, Localization::Words Name );

		ClrTextFx( int Guid, int Price, Color color, Color DetailColor, Matrix M, Localization::Words Name );

		ClrTextFx( int Guid, int Price, Color color, const std::shared_ptr<EzTexture> &texture );

		ClrTextFx( int Guid, int Price, Color color, const std::wstring &texture );

		ClrTextFx( int Guid, int Price, Color color, const std::wstring &texture, bool UsePaintTexture );

		ClrTextFx( int Guid, int Price, Color color, const std::wstring &texture, bool UsePaintTexture, const std::shared_ptr<EzTexture> &PicTexture );

		ClrTextFx( int Guid, int Price, Color color, const std::wstring &texture, bool UsePaintTexture, const std::wstring &PicTextureName );

		ClrTextFx( int Guid, int Price, Color color, const std::wstring &texture, Color DetailColor );

		ClrTextFx( int Guid, int Price, Color color, const std::shared_ptr<EzTexture> &texture, Color DetailColor, const std::shared_ptr<EzEffect> &effect );

		ClrTextFx( int Guid, int Price, Color color, const std::wstring &texture, Color DetailColor, const std::wstring &effect );

		bool operator == ( ClrTextFx B );

		bool operator != ( ClrTextFx B );
	};
}


#endif	//#ifndef CLRTEXTFX
