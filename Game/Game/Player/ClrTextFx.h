#ifndef CLRTEXTFX
#define CLRTEXTFX

#include <small_header.h>

//#include "Core/Effects/EzEffect.h"
#include "Game/Localization.h"
//#include "Core/Texture/EzTexture.h"
//#include "Game/Objects/Bob/Bob.h"
//#include "Game/Tools/Tools.h"
#include "Game/Player/Buyable.h"

namespace CloudberryKingdom
{

	struct ClrTextFx : public Buyable
	{
	
		int Guid, Price;
		int GetGuid();
		int GetPrice();

		Localization::Words Name;

		/// <summary>
		/// A function that may modify the player object.
		/// </summary>
		boost::shared_ptr<Lambda_1<boost::shared_ptr<Bob> > > ModObject;

		boost::shared_ptr<EzTexture> PicTexture;
		Vector2 PicScale;

		bool UsePaintTexture;

		bool Equals( const ClrTextFx &a );

		/// <summary>
		/// This color is used instead of a texture in situations where the texture can't be applied.
		/// Example: the Spaceship object and the colored Gamer Tags (player names)
		/// </summary>
		Color DetailColor;

		Color Clr;
		boost::shared_ptr<EzTexture> Texture;
		boost::shared_ptr<EzEffect> Effect;

		/// <summary>
		/// This matrix is used to hue rotate Bob's outfit.
		/// </summary>
		Matrix M;

		static std::vector<ClrTextFx> FullList;

		ClrTextFx();

		ClrTextFx( int Guid, int Price, Color color, Matrix M );

		ClrTextFx( int Guid, int Price, Color color, Matrix M, Localization::Words Name );

		ClrTextFx( int Guid, int Price, Color color, Color DetailColor, Matrix M, Localization::Words Name );

		ClrTextFx( int Guid, int Price, Color color, const boost::shared_ptr<EzTexture> &texture );

		ClrTextFx( int Guid, int Price, Color color, const std::wstring &texture );

		ClrTextFx( int Guid, int Price, Color color, const std::wstring &texture, bool UsePaintTexture );

		ClrTextFx( int Guid, int Price, Color color, const std::wstring &texture, bool UsePaintTexture, const boost::shared_ptr<EzTexture> &PicTexture );

		ClrTextFx( int Guid, int Price, Color color, const std::wstring &texture, bool UsePaintTexture, const std::wstring &PicTextureName );

		ClrTextFx( int Guid, int Price, Color color, const std::wstring &texture, Color DetailColor );

		ClrTextFx( int Guid, int Price, Color color, const boost::shared_ptr<EzTexture> &texture, Color DetailColor, const boost::shared_ptr<EzEffect> &effect );

		ClrTextFx( int Guid, int Price, Color color, const std::wstring &texture, Color DetailColor, const std::wstring &effect );

		bool operator == ( ClrTextFx B );

		bool operator != ( ClrTextFx B );
	};
}


#endif	//#ifndef CLRTEXTFX
