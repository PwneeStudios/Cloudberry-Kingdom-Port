#include <global_header.h>

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::IO;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;




namespace CloudberryKingdom
{

	TextureOrAnim::TextureOrAnim()
	{
		InitializeInstanceFields();
	}

	TextureOrAnim::TextureOrAnim( const std::wstring &name )
	{
		InitializeInstanceFields();
		Set( name );
	}

	void TextureOrAnim::Set( const std::wstring &name )
	{
		if ( Tools::TextureWad->AnimationDict.find( name ) != Tools::TextureWad->AnimationDict.end() )
		{
			MyAnim = Tools::TextureWad->AnimationDict[ name ];
			IsAnim = true;
		}
		else
		{
			MyTexture = Tools::Texture( name );
			IsAnim = false;
		}
	}

	TextureOrAnim::operator TextureOrAnim*( const std::shared_ptr<EzTexture> &texture )
	{
		std::shared_ptr<TextureOrAnim> t_or_a = std::make_shared<TextureOrAnim>();
		t_or_a->MyTexture = texture;
		return t_or_a;
	}

	TextureOrAnim::operator TextureOrAnim*( const std::wstring &name )
	{
		std::shared_ptr<TextureOrAnim> t_or_a = std::make_shared<TextureOrAnim>();
		t_or_a->Set( name );
		return t_or_a;
	}

	void TextureOrAnim::InitializeInstanceFields()
	{
		IsAnim = false;
	}
}
