#include "EzTexture.h"
#include "Game/Tools/Tools.h"

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::IO;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;
using namespace Microsoft::Xna::Framework;
using namespace Microsoft::Xna::Framework::Content;
using namespace Microsoft::Xna::Framework::Graphics;

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

	EzTexture::operator EzTexture*( const std::wstring &name )
	{
		return Tools::Texture( name );
	}

	void EzTexture::InitializeInstanceFields()
	{
		FromPacked = false;
		Dynamic = false;
		FromCode = false;
		BL = Vector2::Zero;
		TR = Vector2::One;
	}
}
