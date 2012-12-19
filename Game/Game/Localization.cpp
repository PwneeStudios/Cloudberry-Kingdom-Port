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

	SubtitleAction::SubtitleAction( ActionType MyAction, float Time, const boost::shared_ptr<EzTexture> &MyTexture )
	{
		this->MyAction = MyAction;
		this->Time = Time;
		this->MyTexture = MyTexture;
	}

	boost::shared_ptr<ContentManager> Localization::Content;
	std::vector<boost::shared_ptr<SubtitleAction> > Localization::Subtitles;

	const int Localization::NumLanguages = 10;
	std::map<Localization::Language, boost::shared_ptr<LanguageInfo> > Localization::Languages;
	boost::shared_ptr<LanguageInfo> Localization::CurrentLanguage;
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
		//boost::shared_ptr<FileStream> stream = File->Open( path, FileMode::Open, FileAccess::Read, FileShare::None );
		//boost::shared_ptr<StreamReader> reader = boost::make_shared<StreamReader>( stream );
		boost::shared_ptr<FileReader> reader = boost::make_shared<FileReader>( path );

		std::wstring line;

		// Read the file, adding translations to the corresponding dictionaries
		line = reader->ReadLine();
		int LineCount = 0;

		while ( line != std::wstring( L"" ) )
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
		return std::wstring( L"white" );
	}

	std::wstring Localization::WordMarkup( Words Word )
	{
		int Size = 80;
		return Format( _T( "{p%ls,?,%d}" ), WordToTextureName( Word ).c_str(), Size );
	}

	std::wstring Localization::WordMarkup( Words Word, int Size )
	{
		return Format( _T( "{p%ls,%d,?}" ), WordToTextureName( Word ).c_str(), Size );
	}

	// FIXME: preinitialize the map with a fixed size?
	//std::map<Localization::Language, boost::shared_ptr<LanguageInfo> > Localization::Languages = std::map<Localization::Language, boost::shared_ptr<LanguageInfo> >( NumLanguages );

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

		// FIXME: Load subtitles another way.
		/*std::wstring path = Path::Combine( Content->RootDirectory, std::wstring( L"Subtitles" ), CurrentLanguage->MyDirectory );
		std::vector<std::wstring> files = Tools::GetFiles( path, false );

		for ( std::vector<std::wstring>::const_iterator file = files.begin(); file != files.end(); ++file )
		{
			if ( Tools::GetFileExt( path, *file ) == std::wstring( L"xnb" ) )
			{
				//var texture = Tools.TextureWad.AddTexture(null, Tools.GetFileName(path, file));
				boost::shared_ptr<CloudberryKingdom::EzTexture> texture = Tools::TextureWad->AddTexture( 0, Tools::GetFileName( std::wstring( L"Content" ), *file ) );
				texture->Load();
			}
		}*/
	}

	void Localization::Initialize()
	{
		/*Content = boost::make_shared<ContentManager>( Tools::GameClass->getServices(), Path::Combine(_T("Content"), _T("Localization")) );*/
#if defined(PC_VERSION)
		Content = boost::make_shared<ContentManager>( Path::Combine(_T("Content"), _T("Localization")) );
#else
		Content = boost::make_shared<ContentManager>( _T("Localization") );
#endif

		Languages.insert( std::make_pair( Language_CHINESE, boost::make_shared<LanguageInfo>( Language_CHINESE, std::wstring( L"Chinese" ) ) ) );
		Languages.insert( std::make_pair( Language_ENGLISH, boost::make_shared<LanguageInfo>( Language_ENGLISH, std::wstring( L"English" ) ) ) );
		Languages.insert( std::make_pair( Language_FRENCH, boost::make_shared<LanguageInfo>( Language_FRENCH, std::wstring( L"French" ) ) ) );
		Languages.insert( std::make_pair( Language_GERMAN, boost::make_shared<LanguageInfo>( Language_GERMAN, std::wstring( L"German" ) ) ) );
		Languages.insert( std::make_pair( Language_ITALIAN, boost::make_shared<LanguageInfo>( Language_ITALIAN, std::wstring( L"Italian" ) ) ) );
		Languages.insert( std::make_pair( Language_JAPANESE, boost::make_shared<LanguageInfo>( Language_JAPANESE, std::wstring( L"Japanese" ) ) ) );
		Languages.insert( std::make_pair( Language_KOREAN, boost::make_shared<LanguageInfo>( Language_KOREAN, std::wstring( L"Korean" ) ) ) );
		Languages.insert( std::make_pair( Language_PORTUGUESE, boost::make_shared<LanguageInfo>( Language_PORTUGUESE, std::wstring( L"Portuguese" ) ) ) );
		Languages.insert( std::make_pair( Language_RUSSIAN, boost::make_shared<LanguageInfo>( Language_PORTUGUESE, std::wstring( L"Russian" ) ) ) );
		Languages.insert( std::make_pair( Language_SPANISH, boost::make_shared<LanguageInfo>( Language_SPANISH, std::wstring( L"English" ) ) ) );

		std::wstring path = Path::Combine( Content->RootDirectory, std::wstring( L"Localization.tsv" ) );
		ReadTranslationGrid( path );
	}

	void Localization::ReadSubtitleInfo( const std::wstring &VideoName )
	{
		std::wstring path = Path::Combine( std::wstring( L"Content" ), std::wstring( L"Localization" ), std::wstring( L"Subtitles" ), VideoName ) + std::wstring( L".txt" );

		ReadSubtitles( path );
	}

	std::vector<boost::shared_ptr<SubtitleAction> > Localization::GetSubtitles( const std::wstring &VideoName )
	{
		Subtitles.clear();
		ReadSubtitleInfo( VideoName );

		return Subtitles;
	}

	void Localization::ReadSubtitles( const std::wstring &path )
	{
		if ( !File::Exists( path ) )
			return;

		Subtitles = std::vector<boost::shared_ptr<SubtitleAction> >();
		Subtitles.reserve( 50 );

		Tools::UseInvariantCulture();
		//boost::shared_ptr<FileStream> stream = File->Open( path, FileMode::Open, FileAccess::Read, FileShare::None );
		//boost::shared_ptr<StreamReader> reader = boost::make_shared<StreamReader>( stream );
		boost::shared_ptr<FileReader> reader = boost::make_shared<FileReader>( path );

		std::wstring line;

		int Index = 0;

		line = reader->ReadLine();
		while ( line != std::wstring( L"" ) )
		{
			line = Tools::RemoveComment_DashStyle( line );
			if ( line == std::wstring( L"" ) || line.length() <= 1 )
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
				data = std::wstring( L"" );
			}

			if ( identifier == std::wstring( L"show" ) )
			{
					boost::shared_ptr<CloudberryKingdom::EzTexture> SubtitleTexture = Tools::Texture( Format( _T( "Chunk_%d" ), Index ) );
					Subtitles.push_back( boost::make_shared<SubtitleAction>( SubtitleAction::ActionType_SHOW, ParseFloat( data ), SubtitleTexture ) );

					Index++;


			}
			else if ( identifier == std::wstring( L"hide" ) )
			{
					Subtitles.push_back( boost::make_shared<SubtitleAction>( SubtitleAction::ActionType_HIDE, ParseFloat( data ), boost::shared_ptr<EzTexture>() ) );
			}

			line = reader->ReadLine();
		}

		//reader->Close();
		//stream->Close();
	}
}
