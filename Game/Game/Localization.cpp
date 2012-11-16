#include <global_header.h>

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::IO;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Linq;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Text;





namespace CloudberryKingdom
{

	Localization::LanguageInfo::LanguageInfo( Language MyLanguage, const std::wstring &MyDirectory )
	{
		this->MyLanguage = MyLanguage;
		this->MyDirectory = MyDirectory;
	}

	Localization::SubtitleAction::SubtitleAction( ActionType MyAction, float Time, const std::shared_ptr<EzTexture> &MyTexture )
	{
		this->MyAction = MyAction;
		this->Time = Time;
		this->MyTexture = MyTexture;
	}

std::unordered_map<Language, std::unordered_map<Words, std::wstring> > Localization::Text = 0;

	void Localization::ReadTranslationGrid( const std::wstring &path )
	{
		if ( !File::Exists( path ) )
			return;

		// Create new dictionaries for each language
		Text = std::unordered_map<Language, std::unordered_map<Words, std::wstring> >();
		for ( int i = 0; i < NumLanguages; i++ )
			Text.insert( make_pair( static_cast<Language>( i ), std::unordered_map<Words, std::wstring>() ) );

		// Open the giant translation file
		Tools::UseInvariantCulture();
		std::shared_ptr<FileStream> stream = File->Open( path, FileMode::Open, FileAccess::Read, FileShare::None );
		std::shared_ptr<StreamReader> reader = std::make_shared<StreamReader>( stream );

		std::wstring line;

		// Read the file, adding translations to the corresponding dictionaries
		line = reader->ReadLine();
		int LineCount = 0;

		while ( line != _T( "" ) )
		{
			//var bits = line.Split('|');
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'Split' method:
			std::vector<std::wstring> bits = line.Split( L'\t' );

			for ( int i = 0; i < NumLanguages; i++ )
				Text[ static_cast<Language>( i ) ].insert( make_pair( static_cast<Words>( LineCount ), bits[ i + 2 ] ) );

			line = reader->ReadLine();
			LineCount++;
		}

		reader->Close();
		stream->Close();
	}

	std::wstring Localization::WordString( Words Word )
	{
		//return Text[Language.Portuguese][Word];
		return Text[ CurrentLanguage->MyLanguage ][ Word ];
		//return "boob";
	}

	std::wstring Localization::WordToTextureName( Words Word )
	{
		return _T( "white" );
	}

	std::wstring Localization::WordMarkup( Words Word )
	{
		int Size = 80;
		return std::wstring::Format( _T( "{{p{1},?,{0}}}" ), Size, WordToTextureName( Word ) );
	}

	std::wstring Localization::WordMarkup( Words Word, int Size )
	{
		return std::wstring::Format( _T( "{{p{1},{0},?}}" ), Size, WordToTextureName( Word ) );
	}

std::unordered_map<Language, LanguageInfo*> Localization::Languages = std::unordered_map<Language, LanguageInfo*>( NumLanguages );
std::shared_ptr<ContentManager> Localization::Content = 0;
std::shared_ptr<LanguageInfo> Localization::CurrentLanguage = 0;

	void Localization::SetLanguage( Language SelectedLanguage )
	{
		if ( Content == 0 )
		{
			Initialize();
		}
		else
		{
			Content->Unload();
		}

		CurrentLanguage = Languages[ SelectedLanguage ];

		std::wstring path = Path::Combine( Content->RootDirectory, _T( "Subtitles" ), CurrentLanguage->MyDirectory );
		std::vector<std::wstring> files = Tools::GetFiles( path, false );

		for ( std::vector<std::wstring>::const_iterator file = files.begin(); file != files.end(); ++file )
		{
			if ( Tools::GetFileExt( path, *file ) == _T( "xnb" ) )
			{
				//var texture = Tools.TextureWad.AddTexture(null, Tools.GetFileName(path, file));
				std::shared_ptr<CloudberryKingdom::EzTexture> texture = Tools::TextureWad->AddTexture( 0, Tools::GetFileName( _T( "Content" ), *file ) );
				texture->Load();
			}
		}
	}

	void Localization::Initialize()
	{
		Content = std::make_shared<ContentManager>( Tools::GameClass->getServices(), Path::Combine(_T("Content"), _T("Localization")) );

		Languages.insert( make_pair( Language_CHINESE, std::make_shared<LanguageInfo>( Language_CHINESE, _T( "Chinese" ) ) ) );
		Languages.insert( make_pair( Language_ENGLISH, std::make_shared<LanguageInfo>( Language_ENGLISH, _T( "English" ) ) ) );
		Languages.insert( make_pair( Language_FRENCH, std::make_shared<LanguageInfo>( Language_FRENCH, _T( "French" ) ) ) );
		Languages.insert( make_pair( Language_GERMAN, std::make_shared<LanguageInfo>( Language_GERMAN, _T( "German" ) ) ) );
		Languages.insert( make_pair( Language_ITALIAN, std::make_shared<LanguageInfo>( Language_ITALIAN, _T( "Italian" ) ) ) );
		Languages.insert( make_pair( Language_JAPANESE, std::make_shared<LanguageInfo>( Language_JAPANESE, _T( "Japanese" ) ) ) );
		Languages.insert( make_pair( Language_KOREAN, std::make_shared<LanguageInfo>( Language_KOREAN, _T( "Korean" ) ) ) );
		Languages.insert( make_pair( Language_PORTUGUESE, std::make_shared<LanguageInfo>( Language_PORTUGUESE, _T( "Portuguese" ) ) ) );
		Languages.insert( make_pair( Language_RUSSIAN, std::make_shared<LanguageInfo>( Language_PORTUGUESE, _T( "Russian" ) ) ) );
		Languages.insert( make_pair( Language_SPANISH, std::make_shared<LanguageInfo>( Language_SPANISH, _T( "English" ) ) ) );

		std::wstring path = Path::Combine( Content->RootDirectory, _T( "Localization.tsv" ) );
		ReadTranslationGrid( path );
	}

	void Localization::ReadSubtitleInfo( const std::wstring &VideoName )
	{
		std::wstring path = Path::Combine( _T( "Content" ), _T( "Localization" ), _T( "Subtitles" ), VideoName ) + _T( ".txt" );

		ReadSubtitles( path );
	}

	std::vector<SubtitleAction*> Localization::GetSubtitles( const std::wstring &VideoName )
	{
		Subtitles.clear();
		ReadSubtitleInfo( VideoName );

		return Subtitles;
	}

std::vector<SubtitleAction*> Localization::Subtitles = 0;

	void Localization::ReadSubtitles( const std::wstring &path )
	{
		if ( !File::Exists( path ) )
			return;

		Subtitles = std::vector<SubtitleAction*>( 50 );

		Tools::UseInvariantCulture();
		std::shared_ptr<FileStream> stream = File->Open( path, FileMode::Open, FileAccess::Read, FileShare::None );
		std::shared_ptr<StreamReader> reader = std::make_shared<StreamReader>( stream );

		std::wstring line;

		int Index = 0;

		line = reader->ReadLine();
		while ( line != _T( "" ) )
		{
			line = Tools::RemoveComment_DashStyle( line );
			if ( line == _T( "" ) || line.length() <= 1 )
			{
				line = reader->ReadLine();
				continue;
			}

			int space = line.find( L' ' );
			std::wstring identifier, data;
			if ( space > 0 )
			{
				identifier = line.substr( 0, space );
				data = line.substr( space + 1 );
			}
			else
			{
				identifier = line;
				data = _T( "" );
			}

//C# TO C++ CONVERTER NOTE: The following 'switch' operated on a string variable and was converted to C++ 'if-else' logic:
//			switch (identifier)
//ORIGINAL LINE: case "show":
			if ( identifier == _T( "show" ) )
			{
					std::shared_ptr<CloudberryKingdom::EzTexture> SubtitleTexture = Tools::Texture( std::wstring::Format( _T( "Chunk_{0}" ), Index ) );
					Subtitles.push_back( std::make_shared<SubtitleAction>( SubtitleAction::ActionType_SHOW, float::Parse( data ), SubtitleTexture ) );

					Index++;


			}
//ORIGINAL LINE: case "hide":
			else if ( identifier == _T( "hide" ) )
			{
					Subtitles.push_back( std::make_shared<SubtitleAction>( SubtitleAction::ActionType_HIDE, float::Parse( data ), 0 ) );
			}

			line = reader->ReadLine();
		}

		reader->Close();
		stream->Close();
	}
}
