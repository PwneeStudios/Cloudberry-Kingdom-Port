#include <global_header.h>

namespace CloudberryKingdom
{

	std::shared_ptr<TextureOrAnim> EzTextureWad::FindTextureOrAnim( const std::wstring &name )
	{
		if ( name == _T( "null" ) )
			return 0;

		std::shared_ptr<TextureOrAnim> t_or_a = std::make_shared<TextureOrAnim>();
		t_or_a->Set( name );
		return t_or_a;
	}

	void EzTextureWad::Add( const std::shared_ptr<AnimationData_Texture> &anim, const std::wstring &name )
	{
		AnimationDict.AddOrOverwrite( name, anim );
	}

	void EzTextureWad::Add( const std::shared_ptr<PackedTexture> &packed )
	{
		for ( std::vector<SubTexture*>::const_iterator sub = packed->SubTextures.begin(); sub != packed->SubTextures.end(); ++sub )
		{
			std::shared_ptr<EzTexture> texture = FindByName( ( *sub ).name );
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

		TextureList = std::vector<EzTexture*>( Size );
		TextureListByFolder = std::unordered_map<std::wstring, std::vector<EzTexture*> >( Size );

		AnimationDict = std::unordered_map<std::wstring, AnimationData_Texture*>( Size, StringComparer::CurrentCultureIgnoreCase );

		PathDict = std::unordered_map<std::wstring, EzTexture*>( Size, StringComparer::CurrentCultureIgnoreCase );
		NameDict = std::unordered_map<std::wstring, EzTexture*>( Size, StringComparer::CurrentCultureIgnoreCase );
		BigNameDict = std::unordered_map<std::wstring, EzTexture*>( Size, StringComparer::CurrentCultureIgnoreCase );
	}

	void EzTextureWad::LoadFolder( const std::shared_ptr<ContentManager> &Content, const std::wstring &Folder )
	{
		for ( std::vector<EzTexture*>::const_iterator Tex = TextureListByFolder[ Folder ].begin(); Tex != TextureListByFolder[ Folder ].end(); ++Tex )
		{
			// If texture hasn't been loaded yet, load it
			if ( ( *Tex )->getTex() == 0 && !(*Tex)->FromCode )
			{
				( *Tex )->setTex( Content->Load<Texture2D*>( ( *Tex )->Path ) );
				( *Tex )->Width = ( *Tex )->getTex()->Width;
				( *Tex )->Height = ( *Tex )->getTex()->Height;

	#if defined(EDITOR)
	#else
				Resources::ResourceLoadedCountRef->setVal( Resources::ResourceLoadedCountRef->getVal() + 1 );
	#endif
			}
		}
	}

	std::shared_ptr<EzTexture> EzTextureWad::FindOrLoad( const std::shared_ptr<ContentManager> &Content, const std::wstring &name )
	{
		std::shared_ptr<EzTexture> texture = FindByName( name );

		if ( texture != Tools::TextureWad->DefaultTexture )
			return texture;

		return Tools::TextureWad->AddTexture( Content->Load<Texture2D*>( name ), name );
	}

	std::shared_ptr<EzTexture> EzTextureWad::FindByPathOrName( const std::wstring &path )
	{
		// Look for the texture with the full path
		std::shared_ptr<CloudberryKingdom::EzTexture> PathTexture = FindByName( path );

		// If nothing but white was found
		if ( PathTexture == 0 || PathTexture == TextureList[ 0 ] )
		{
			// Get the name from the path
			int i = path.rfind( _T( "\\" ) );

			// If the name is the path, return what we found
			if ( i <= 0 )
				return PathTexture;

			// Otherwise find the name and return the result
			std::wstring name = path.substr( i + 1 );
			return FindByName( name );
		}
		else
			return PathTexture;
	}

	std::shared_ptr<EzTexture> EzTextureWad::FindByName( const std::wstring &name )
	{
		std::shared_ptr<EzTexture> texture = _FindByName( name );

		if ( texture == 0 )
			return 0;

		if ( texture->getTex() == 0 )
		{
			texture->Load();
		}

		return texture;
	}

	std::shared_ptr<EzTexture> EzTextureWad::_FindByName( const std::wstring &name )
	{
		if ( name == _T( "" ) )
			return DefaultTexture;

		return Find( name );
	}

	std::shared_ptr<EzTexture> EzTextureWad::Find( const std::wstring &name )
	{
		if ( name.find( _T( "\\" ) ) != string::npos && BigNameDict.find( name ) != BigNameDict.end() )
			return BigNameDict[ name ];
		else if ( PathDict.find( name ) != PathDict.end() )
			return PathDict[ name ];
		else if ( NameDict.find( name ) != NameDict.end() )
			return NameDict[ name ];

		return DefaultTexture;
	}

	void EzTextureWad::AddEzTexture( const std::shared_ptr<EzTexture> &NewTex )
	{
		TextureList.push_back( NewTex );

		std::wstring name = NewTex->Name->ToLower();
		if ( !NameDict.find( name ) != NameDict.end() )
			NameDict.AddOrOverwrite( name, NewTex );

		if ( NewTex->Path != _T( "" ) )
		{
			PathDict.AddOrOverwrite( NewTex->Path.ToLower(), NewTex );
			BigNameDict.AddOrOverwrite( Tools::GetFileBigName( NewTex->Path ).ToLower(), NewTex );
		}
	}

	std::shared_ptr<EzTexture> EzTextureWad::AddTexture( const std::shared_ptr<Texture2D> &Tex, const std::wstring &Name )
	{
		if ( Tex == 0 )
			return AddTexture( Tex, Name, 0, 0 );
		else
			return AddTexture( Tex, Name, Tex->Width, Tex->Height );
	}

	std::shared_ptr<EzTexture> EzTextureWad::AddTexture( const std::shared_ptr<Texture2D> &Tex, const std::wstring &Name, int Width, int Height )
	{
		std::shared_ptr<EzTexture> NewTex = 0;

		bool OneFound = false;
//C# TO C++ CONVERTER TODO TASK: There is no equivalent to implicit typing in C++ unless the C++11 inferred typing option is selected:
		for ( std::vector<EzTexture*>::const_iterator texture = TextureList.begin(); texture != TextureList.end(); ++texture )
		{
//C# TO C++ CONVERTER TODO TASK: The following .NET 'String.Compare' reference is not converted:
			if ( std::wstring::Compare( ( *texture )->Path, Name, StringComparison::OrdinalIgnoreCase ) == 0 )
			{
				OneFound = true;

				NewTex = FindByName( Name );

				// Override pre-existing texture?
				if ( Tex != 0 )
				{
					// Get rid of old texture if it was dynamic.
					if ( NewTex->Dynamic && NewTex->getTex() != 0 && !NewTex->getTex()->IsDisposed )
						delete NewTex->getTex();

					NewTex->setTex( Tex );
				}
			}
		}

		if ( !OneFound )
		{
			NewTex = std::make_shared<EzTexture>();
			NewTex->Path = Name;
			NewTex->setTex( Tex );

			NewTex->Name = Tools::StripPath( Name );

			TextureList.push_back( NewTex );

			std::wstring name = NewTex->Name->ToLower();
			if ( !NameDict.find( name ) != NameDict.end() )
				NameDict.AddOrOverwrite( name, NewTex );
			PathDict.AddOrOverwrite( NewTex->Path.ToLower(), NewTex );

			BigNameDict.AddOrOverwrite( Tools::GetFileBigName( NewTex->Path ).ToLower(), NewTex );

			// Add to folder
			std::wstring folder = Tools::FirstFolder( Name, _T( "Art\\" ) );
			if ( !TextureListByFolder.find( folder ) != TextureListByFolder.end() )
				TextureListByFolder.insert( make_pair( folder, std::vector<EzTexture*>() ) );
			TextureListByFolder[ folder ].push_back( NewTex );
		}

		NewTex->Width = Width;
		NewTex->Height = Height;

		return NewTex;
	}

	std::shared_ptr<EzTexture> EzTextureWad::AddTexture_Fast( const std::shared_ptr<Texture2D> &Tex, const std::wstring &Name, int Width, int Height )
	{
		return 0;
	}

	std::shared_ptr<EzTexture> EzTextureWad::AddTexture_Fast( const std::shared_ptr<Texture2D> &Tex, const std::wstring &Name, int Width, int Height, const std::wstring &StrippedName, const std::wstring &LowerName, const std::wstring &LowerPath, const std::wstring &BigName, const std::wstring &Folder )
	{
		std::shared_ptr<EzTexture> NewTex = 0;

		NewTex = std::make_shared<EzTexture>();
		NewTex->Path = Name;
		NewTex->setTex( Tex );

		NewTex->Name = StrippedName;

		TextureList.push_back( NewTex );

		NameDict.insert( make_pair( LowerName, NewTex ) );
		PathDict.insert( make_pair( LowerPath, NewTex ) );

		BigNameDict.insert( make_pair( BigName, NewTex ) );

		// Add to folder
		if ( !TextureListByFolder.find( Folder ) != TextureListByFolder.end() )
			TextureListByFolder.insert( make_pair( Folder, std::vector<EzTexture*>() ) );
		TextureListByFolder[ Folder ].push_back( NewTex );

		NewTex->Width = Width;
		NewTex->Height = Height;

		return NewTex;
	}

	void EzTextureWad::InitializeInstanceFields()
	{
		PackedDict = std::unordered_map<std::wstring, PackedTexture*>();
	}
}
