#include <global_header.h>


namespace CloudberryKingdom
{

	int ClrTextFx::GetGuid()
	{
		return Guid;
	}

	int ClrTextFx::GetPrice()
	{
		return Price;
	}

	bool ClrTextFx::Equals( const ClrTextFx &a )
	{
		if ( a.Name == Name )
			return true;
		else
			return false;
	}

std::vector<ClrTextFx> ClrTextFx::FullList = std::vector<ClrTextFx>();

	ClrTextFx::ClrTextFx() :
		Guid( 0 ),
		Price( 0 ),
		Name( Localization::Words_NONE ),
		UsePaintTexture( true )
	{
	}

	ClrTextFx::ClrTextFx( int Guid, int Price, Color color, Matrix M )
	{
		this->M = M;

		this->Guid = Guid;
		this->Price = Price;
		UsePaintTexture = true;

		ModObject.reset();
		PicTexture.reset();
		PicScale = Vector2(1);
		Name = Localization::Words_NONE;

		this->Clr = this->DetailColor = color;
		Texture = Tools::TextureWad->TextureList[ 0 ];
		Effect = Tools::BasicEffect;
	}

	ClrTextFx::ClrTextFx( int Guid, int Price, Color color, Matrix M, Localization::Words Name )
	{
		this->M = M;
		this->Name = Name;

		this->Guid = Guid;
		this->Price = Price;
		UsePaintTexture = true;

		ModObject.reset();
		PicTexture.reset();
		PicScale = Vector2(1);
		Name = Localization::Words_NONE;

		this->Clr = this->DetailColor = color;
		Texture = Tools::TextureWad->TextureList[ 0 ];
		Effect = Tools::BasicEffect;
		;
	}

	ClrTextFx::ClrTextFx( int Guid, int Price, Color color, Color DetailColor, Matrix M, Localization::Words Name )
	{
		this->M = M;
		this->Name = Name;

		this->Guid = Guid;
		this->Price = Price;
		UsePaintTexture = true;

		ModObject.reset();
		PicTexture.reset();
		PicScale = Vector2(1);
		Name = Localization::Words_NONE;

		this->Clr = color;
		this->DetailColor = DetailColor;
		Texture = Tools::TextureWad->TextureList[ 0 ];
		Effect = Tools::BasicEffect;
	}

	ClrTextFx::ClrTextFx( int Guid, int Price, Color color, const std::shared_ptr<EzTexture> &texture )
	{
		this->M = Matrix::Identity();

		this->Guid = Guid;
		this->Price = Price;
		UsePaintTexture = true;

		ModObject.reset();
		PicTexture.reset();
		PicScale = Vector2(1);
		Name = Localization::Words_NONE;

		this->Clr = this->DetailColor = color;
		this->Texture = texture;
		Effect = Tools::BasicEffect;
	}

	ClrTextFx::ClrTextFx( int Guid, int Price, Color color, const std::wstring &texture )
	{
		this->M = Matrix::Identity();

		this->Guid = Guid;
		this->Price = Price;
		UsePaintTexture = true;

		ModObject.reset();
		PicTexture.reset();
		PicScale = Vector2(1);
		Name = Localization::Words_NONE;

		this->Clr = this->DetailColor = color;
		this->Texture = Tools::TextureWad->FindByName( texture );
		Effect = Tools::BasicEffect;
	}

	ClrTextFx::ClrTextFx( int Guid, int Price, Color color, const std::wstring &texture, bool UsePaintTexture )
	{
		this->M = Matrix::Identity();

		this->Guid = Guid;
		this->Price = Price;
		this->UsePaintTexture = UsePaintTexture;

		ModObject.reset();
		PicTexture.reset();
		PicScale = Vector2(1);
		Name = Localization::Words_NONE;

		this->Clr = this->DetailColor = color;
		this->Texture = Tools::TextureWad->FindByName( texture );
		Effect = Tools::BasicEffect;
	}

	ClrTextFx::ClrTextFx( int Guid, int Price, Color color, const std::wstring &texture, bool UsePaintTexture, const std::shared_ptr<EzTexture> &PicTexture )
	{
		this->M = Matrix::Identity();

		this->Guid = Guid;
		this->Price = Price;
		this->UsePaintTexture = UsePaintTexture;
		this->PicTexture = PicTexture;

		ModObject.reset();
		PicScale = Vector2(1);
		Name = Localization::Words_NONE;

		this->Clr = this->DetailColor = color;
		this->Texture = Tools::TextureWad->FindByName( texture );
		Effect = Tools::BasicEffect;
	}

	ClrTextFx::ClrTextFx( int Guid, int Price, Color color, const std::wstring &texture, bool UsePaintTexture, const std::wstring &PicTextureName )
	{
		this->M = Matrix::Identity();

		this->Guid = Guid;
		this->Price = Price;
		this->UsePaintTexture = UsePaintTexture;
		this->PicTexture = Tools::TextureWad->FindByName( PicTextureName );

		ModObject.reset();
		PicScale = Vector2(1);
		Name = Localization::Words_NONE;

		this->Clr = this->DetailColor = color;
		this->Texture = Tools::TextureWad->FindByName( texture );
		Effect = Tools::BasicEffect;
	}

	ClrTextFx::ClrTextFx( int Guid, int Price, Color color, const std::wstring &texture, Color DetailColor )
	{
		this->M = Matrix::Identity();

		this->Guid = Guid;
		this->Price = Price;
		UsePaintTexture = true;

		ModObject.reset();
		PicTexture.reset();
		PicScale = Vector2(1);
		Name = Localization::Words_NONE;

		this->Clr = color;
		this->Texture = Tools::TextureWad->FindByName( texture );
		this->DetailColor = DetailColor;
		Effect = Tools::BasicEffect;
	}

	ClrTextFx::ClrTextFx( int Guid, int Price, Color color, const std::shared_ptr<EzTexture> &texture, Color DetailColor, const std::shared_ptr<EzEffect> &effect )
	{
		this->M = Matrix::Identity();

		this->Guid = Guid;
		this->Price = Price;
		UsePaintTexture = true;

		ModObject.reset();
		PicTexture.reset();
		PicScale = Vector2(1);
		Name = Localization::Words_NONE;

		this->Clr = color;
		this->Texture = texture;
		this->DetailColor = DetailColor;
		this->Effect = effect;
	}

	ClrTextFx::ClrTextFx( int Guid, int Price, Color color, const std::wstring &texture, Color DetailColor, const std::wstring &effect )
	{
		this->M = Matrix::Identity();

		this->Guid = Guid;
		this->Price = Price;
		UsePaintTexture = true;

		ModObject.reset();
		PicTexture.reset();
		PicScale = Vector2(1);
		Name = Localization::Words_NONE;

		this->Clr = color;
		this->Texture = Tools::TextureWad->FindByName( texture );
		this->DetailColor = DetailColor;
		Effect = Tools::EffectWad->FindByName( effect );
	}

	bool ClrTextFx::operator == ( ClrTextFx B )
	{
		if ( this->ModObject != B.ModObject )
			return false;
		if ( this->Clr != B.Clr )
			return false;
		if ( this->Effect != B.Effect )
			return false;
		if ( this->Texture != B.Texture )
			return false;
		return true;
	}

	bool ClrTextFx::operator != ( ClrTextFx B )
	{
		return !( *this == B );
	}
}
