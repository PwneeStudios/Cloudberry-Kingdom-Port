#include <global_header.h>

#include "Hacks/String.h"
#include "Hacks/Parse.h"

#include "Hacks/NET/File.h"
#include "Hacks/NET/Path.h"
#include "Hacks/FileReader.h"

namespace CloudberryKingdom
{

	LanguageInfo::LanguageInfo( Localization::Language MyLanguage, const std::wstring &MyDirectory )
	{
		this->MyLanguage = MyLanguage;
		this->MyDirectory = MyDirectory;
	}

	SubtitleAction::SubtitleAction( ActionType MyAction, float Time, const std::shared_ptr<EzTexture> &MyTexture )
	{
		this->MyAction = MyAction;
		this->Time = Time;
		this->MyTexture = MyTexture;
	}

	std::shared_ptr<ContentManager> Localization::Content;
	std::vector<std::shared_ptr<SubtitleAction> > Localization::Subtitles;

	const int Localization::NumLanguages = 10;
	std::map<Localization::Language, std::shared_ptr<LanguageInfo> > Localization::Languages;
	std::shared_ptr<LanguageInfo> Localization::CurrentLanguage;
	std::map<Localization::Language, std::map<Localization::Words, std::wstring> > Localization::Text;

	void Localization::ReadTranslationGrid( const std::wstring &path )
	{
		if ( !File::Exists( path ) )
			return;

		// Create new dictionaries for each language
		//Text = std::map<Language, std::map<Words, std::wstring> >();
		//for ( int i = 0; i < NumLanguages; i++ )
		//	Text.insert( std::make_pair( static_cast<Language>( i ), std::map<Words, std::wstring>() ) );
		Text = std::map<Language, std::map<Words, std::wstring> >();
		for ( int i = 0; i < NumLanguages; i++ )
			Text.insert( std::make_pair( static_cast<Language>( i ), std::map<Words, std::wstring>() ) );

		// Open the giant translation file
		Tools::UseInvariantCulture();
		//std::shared_ptr<FileStream> stream = File->Open( path, FileMode::Open, FileAccess::Read, FileShare::None );
		//std::shared_ptr<StreamReader> reader = std::make_shared<StreamReader>( stream );
		std::shared_ptr<FileReader> reader = std::make_shared<FileReader>( path );

		std::wstring line;

		// Read the file, adding translations to the corresponding dictionaries
		line = reader->ReadLine();
		int LineCount = 0;

		while ( line != _T( "" ) )
		{
			//var bits = line.Split('|');
			std::vector<std::wstring> bits = Split( line, L'\t' );

			for ( int i = 0; i < NumLanguages; i++ )
				Text[ static_cast<Language>( i ) ].insert( std::make_pair( static_cast<Words>( LineCount ), bits[ i + 2 ] ) );

			line = reader->ReadLine();
			LineCount++;
		}

		//reader->Close();
		//stream->Close();
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
		return Format( _T( "{{p{1},?,{0}}}" ), Size, WordToTextureName( Word ) );
	}

	std::wstring Localization::WordMarkup( Words Word, int Size )
	{
		return Format( _T( "{{p{1},{0},?}}" ), Size, WordToTextureName( Word ) );
	}

	// FIXME: preinitialize the map with a fixed size?
	//std::map<Localization::Language, std::shared_ptr<LanguageInfo> > Localization::Languages = std::map<Localization::Language, std::shared_ptr<LanguageInfo> >( NumLanguages );

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
		/*Content = std::make_shared<ContentManager>( Tools::GameClass->getServices(), Path::Combine(_T("Content"), _T("Localization")) );*/
		Content = std::make_shared<ContentManager>( Path::Combine(_T("Content"), _T("Localization")) );

		Languages.insert( std::make_pair( Language_CHINESE, std::make_shared<LanguageInfo>( Language_CHINESE, _T( "Chinese" ) ) ) );
		Languages.insert( std::make_pair( Language_ENGLISH, std::make_shared<LanguageInfo>( Language_ENGLISH, _T( "English" ) ) ) );
		Languages.insert( std::make_pair( Language_FRENCH, std::make_shared<LanguageInfo>( Language_FRENCH, _T( "French" ) ) ) );
		Languages.insert( std::make_pair( Language_GERMAN, std::make_shared<LanguageInfo>( Language_GERMAN, _T( "German" ) ) ) );
		Languages.insert( std::make_pair( Language_ITALIAN, std::make_shared<LanguageInfo>( Language_ITALIAN, _T( "Italian" ) ) ) );
		Languages.insert( std::make_pair( Language_JAPANESE, std::make_shared<LanguageInfo>( Language_JAPANESE, _T( "Japanese" ) ) ) );
		Languages.insert( std::make_pair( Language_KOREAN, std::make_shared<LanguageInfo>( Language_KOREAN, _T( "Korean" ) ) ) );
		Languages.insert( std::make_pair( Language_PORTUGUESE, std::make_shared<LanguageInfo>( Language_PORTUGUESE, _T( "Portuguese" ) ) ) );
		Languages.insert( std::make_pair( Language_RUSSIAN, std::make_shared<LanguageInfo>( Language_PORTUGUESE, _T( "Russian" ) ) ) );
		Languages.insert( std::make_pair( Language_SPANISH, std::make_shared<LanguageInfo>( Language_SPANISH, _T( "English" ) ) ) );

		std::wstring path = Path::Combine( Content->RootDirectory, _T( "Localization.tsv" ) );
		ReadTranslationGrid( path );
	}

	void Localization::ReadSubtitleInfo( const std::wstring &VideoName )
	{
		std::wstring path = Path::Combine( _T( "Content" ), _T( "Localization" ), _T( "Subtitles" ), VideoName ) + _T( ".txt" );

		ReadSubtitles( path );
	}

	std::vector<std::shared_ptr<SubtitleAction> > Localization::GetSubtitles( const std::wstring &VideoName )
	{
		Subtitles.clear();
		ReadSubtitleInfo( VideoName );

		return Subtitles;
	}

	void Localization::ReadSubtitles( const std::wstring &path )
	{
		if ( !File::Exists( path ) )
			return;

		Subtitles = std::vector<std::shared_ptr<SubtitleAction> >( 50 );

		Tools::UseInvariantCulture();
		//std::shared_ptr<FileStream> stream = File->Open( path, FileMode::Open, FileAccess::Read, FileShare::None );
		//std::shared_ptr<StreamReader> reader = std::make_shared<StreamReader>( stream );
		std::shared_ptr<FileReader> reader = std::make_shared<FileReader>( path );

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

			if ( identifier == _T( "show" ) )
			{
					std::shared_ptr<CloudberryKingdom::EzTexture> SubtitleTexture = Tools::Texture( Format( _T( "Chunk_{0}" ), Index ) );
					Subtitles.push_back( std::make_shared<SubtitleAction>( SubtitleAction::ActionType_SHOW, ParseFloat( data ), SubtitleTexture ) );

					Index++;


			}
			else if ( identifier == _T( "hide" ) )
			{
					Subtitles.push_back( std::make_shared<SubtitleAction>( SubtitleAction::ActionType_HIDE, ParseFloat( data ), std::shared_ptr<EzTexture>() ) );
			}

			line = reader->ReadLine();
		}

		//reader->Close();
		//stream->Close();
	}
}
