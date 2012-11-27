#include <global_header.h>

namespace CloudberryKingdom
{

	const std::shared_ptr<Texture2D> &EzTexture::getTex() const
	{
		return _Tex;
	}

	void EzTexture::setTex( const std::shared_ptr<Texture2D> &value )
	{
		_Tex = value;
	}

	const float &EzTexture::getAspectRatio() const
	{
		return static_cast<float>( Width ) / static_cast<float>( Height );
	}

#if defined(EDITOR)
std::shared_ptr<Game> EzTexture::game = 0;
#endif

#if defined(EDITOR)
	bool EzTexture::Load()
	{
		if ( getTex() == 0 && Path != _T("") )
			setTex( game->Content->Load<Texture2D*>( Path ) );

		return getTex() != 0;
	}
#endif

#if ! defined(EDITOR)
	bool EzTexture::Load()
	{
		if ( _Tex == 0 && Path != _T( "" ) )
		{
			_Tex = Tools::GameClass->getContent()->Load<Texture2D*>(Path);
			Width = _Tex->Width;
			Height = _Tex->Height;
		}

		return _Tex != 0;
	}
#endif

	std::wstring EzTexture::ToString()
	{
		return Name;
	}

	void EzTexture::InitializeInstanceFields()
	{
		FromPacked = false;
		Dynamic = false;
		FromCode = false;
		BL = Vector2();
		TR = Vector2(1);
	}
}
