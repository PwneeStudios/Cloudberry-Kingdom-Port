#include <small_header.h>
#include "Core/Texture/EzTextureWad.h"

#include "Core/Animation/AnimationData_Integer.h"
#include "Game/CloudberryKingdom/CloudberryKingdom.CloudberryKingdomGame.h"
#include "Game/Tilesets/Backgrounds/Background.h"
#include "Core/Texture/EzTexture.h"
#include "Core/Texture/PackedTexture.h"
#include "Core/Texture/TextureOrAnim.h"
#include "Game/Tilesets/TileSet.h"
#include "Game/Tools/Globals.h"
#include "Game/Tools/Prototypes.h"
#include "Game/Tools/Tools.h"
#include "Game/Tilesets/TileSetInfo.h"
#include "Game/Objects/IBounded.h"

#include <Hacks\String.h>
#include <Hacks\Dict.h>

namespace CloudberryKingdom
{

	boost::shared_ptr<TextureOrAnim> EzTextureWad::FindTextureOrAnim( const std::wstring &name )
	{
		if ( name == std::wstring( L"null" ) )
			return 0;

		boost::shared_ptr<TextureOrAnim> t_or_a = boost::make_shared<TextureOrAnim>();
		t_or_a->Set( name );
		return t_or_a;
	}

	void EzTextureWad::Add( const boost::shared_ptr<AnimationData_Texture> &anim, const std::wstring &name )
	{
		//AnimationDict.AddOrOverwrite( name, anim );
		//AnimationDict[ name ] = anim;
		::Add( AnimationDict, name, anim );
	}

	void EzTextureWad::Add( const boost::shared_ptr<PackedTexture> &packed )
	{
		for ( std::vector<SubTexture>::const_iterator sub = packed->SubTextures.begin(); sub != packed->SubTextures.end(); ++sub )
		{
			boost::shared_ptr<EzTexture> texture = FindByName( ( *sub ).name );
			texture->FromPacked = true;
			texture->TR = ( *sub ).TR;
			texture->BL = ( *sub ).BL;
			texture->Packed = packed->MyTexture;
		}
	}

	EzTextureWad::EzTextureWad()
	{
		InitializeInstanceFields();
		const int Size = 2000;

		TextureList = std::vector<boost::shared_ptr<EzTexture> >();
		TextureList.reserve( Size );
		TextureListByFolder = std::map<std::wstring, std::vector<boost::shared_ptr<EzTexture> > >();

		AnimationDict = std::map<std::wstring, boost::shared_ptr<AnimationData_Texture> >();

		NameDict = std::map<std::wstring, boost::shared_ptr<EzTexture> >();
	}

	boost::shared_ptr<EzTexture> EzTextureWad::FindOrLoad( const boost::shared_ptr<ContentManager> &Content, const std::wstring &name, const std::wstring &path )
	{
		boost::shared_ptr<EzTexture> texture = FindByName( name );

		if ( texture != Tools::TextureWad->DefaultTexture )
			return texture;

		return Tools::TextureWad->AddTexture( Content->Load<Texture2D>( path ), name );
	}

	boost::shared_ptr<EzTexture> EzTextureWad::FindByPathOrName( const std::wstring &path )
	{
		// Look for the texture with the full path
		boost::shared_ptr<EzTexture> PathTexture = FindByName( path );

		// If nothing but white was found
		if ( PathTexture == 0 || PathTexture == TextureList[ 0 ] )
		{
			// Get the name from the path
			int i = path.rfind( std::wstring( L"/" ) );

			// If the name is the path then try a backslash
			if ( i <= 0 )
			{
				i = path.rfind( std::wstring( L"\\" ) );
				if ( i <= 0 )
					return PathTexture;
			}

			// Otherwise find the name and return the result
			std::wstring name = path.substr( i + 1 );
			return FindByName( name );
		}
		else
			return PathTexture;
	}

	boost::shared_ptr<EzTexture> EzTextureWad::FindByName( const std::wstring &name )
	{
		boost::shared_ptr<EzTexture> texture = _FindByName( name );

		if ( texture == 0 )
			return 0;

		if ( texture->getTex() == 0 )
		{
			texture->Load();
		}

		return texture;
	}

	boost::shared_ptr<EzTexture> EzTextureWad::_FindByName( const std::wstring &name )
	{
		if ( name == std::wstring( L"" ) )
			return DefaultTexture;

		return Find( name );
	}

	boost::shared_ptr<EzTexture> EzTextureWad::Find( const std::wstring &name )
	{
		std::wstring lowercaseName = ToLower( name );

		if ( NameDict.find( lowercaseName ) != NameDict.end() )
            return NameDict[ lowercaseName ];
            
        return DefaultTexture;

		//if ( lowercaseName.find( std::wstring( L"/" ) ) != std::string::npos && BigNameDict.find( lowercaseName ) != BigNameDict.end() )
		//	return BigNameDict[ lowercaseName ];
		//else if ( PathDict.find( lowercaseName ) != PathDict.end() )
		//	return PathDict[ lowercaseName ];
		//else if ( NameDict.find( lowercaseName ) != NameDict.end() )
		//	return NameDict[ lowercaseName ];

		//return DefaultTexture;
	}

	void EzTextureWad::AddEzTexture( const boost::shared_ptr<EzTexture> &NewTex )
	{
		TextureList.push_back( NewTex );

		std::wstring name = ToLower( NewTex->Name );
		if ( NameDict.find( name ) == NameDict.end() )
			::Add( NameDict, name, NewTex );
	}

	boost::shared_ptr<EzTexture> EzTextureWad::AddTexture( const boost::shared_ptr<Texture2D> &Tex, const std::wstring &Name )
	{
		if ( Tex == 0 )
			return AddTexture( Tex, Name, 0, 0 );
		else
			return AddTexture( Tex, Name, Tex->Width, Tex->Height );
	}

	boost::shared_ptr<EzTexture> EzTextureWad::AddTexture( const boost::shared_ptr<Texture2D> &Tex, const std::wstring &Name, int Width, int Height )
	{
		boost::shared_ptr<EzTexture> NewTex = 0;

		/*
		bool OneFound = false;
		for ( std::vector<boost::shared_ptr<EzTexture> >::const_iterator texture = TextureList.begin(); texture != TextureList.end(); ++texture )
		{
			if ( CompareIgnoreCase( ( *texture )->Path, Name ) == 0 )
			{
				OneFound = true;

				NewTex = FindByName( Name );

				// Override pre-existing texture?
				if ( Tex != 0 )
				{
					// Get rid of old texture if it was dynamic.

					// FIXME: We shouldn't be deleting things.
					//if ( NewTex->Dynamic && NewTex->getTex() != 0 && !NewTex->getTex()->IsDisposed )
					//	delete NewTex->getTex();

					NewTex->setTex( Tex );
				}
			}
		}

		if ( !OneFound )*/
		{
			NewTex = boost::make_shared<EzTexture>();
			NewTex->Path = Name;
			NewTex->setTex( Tex );

			NewTex->Name = Tools::StripPath( Name );

			TextureList.push_back( NewTex );

			std::wstring name = ToLower( NewTex->Name );
			if ( NameDict.find( name ) == NameDict.end() )
				NameDict[ name ] = NewTex;

			// Add to folder
			//std::wstring folder = Tools::FirstFolder( Name, std::wstring( L"Art/" ) );
			//if ( TextureListByFolder.find( folder ) == TextureListByFolder.end() )
			//	TextureListByFolder.insert( make_pair( folder, std::vector<boost::shared_ptr<EzTexture> >() ) );
			//TextureListByFolder[  folder ].push_back( NewTex );
		}

		NewTex->Width = Width;
		NewTex->Height = Height;

		return NewTex;
	}

	boost::shared_ptr<EzTexture> EzTextureWad::AddTexture_Fast( const boost::shared_ptr<Texture2D> &Tex, const std::wstring &Name, int Width, int Height )
	{
		return 0;
	}

	boost::shared_ptr<EzTexture> EzTextureWad::AddTexture_Fast( const boost::shared_ptr<Texture2D> &Tex, const std::wstring &Name, int Width, int Height, const std::wstring &StrippedName, const std::wstring &LowerName, const std::wstring &Folder )
	{
		boost::shared_ptr<EzTexture> NewTex = 0;

		NewTex = boost::make_shared<EzTexture>();
		NewTex->Path = Name;
		NewTex->setTex( Tex );

		NewTex->Name = StrippedName;

		TextureList.push_back( NewTex );

		NameDict.insert( make_pair( LowerName, NewTex ) );

		// Add to folder
		if ( TextureListByFolder.find( Folder ) == TextureListByFolder.end() )
			TextureListByFolder.insert( make_pair( Folder, std::vector<boost::shared_ptr<EzTexture> >() ) );
		TextureListByFolder[ Folder ].push_back( NewTex );

		NewTex->Width = Width;
		NewTex->Height = Height;

		return NewTex;
	}

	void EzTextureWad::InitializeInstanceFields()
	{
		PackedDict = std::map<std::wstring, boost::shared_ptr<PackedTexture> >();
	}
}
