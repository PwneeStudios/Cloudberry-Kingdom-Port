#include <global_header.h>

#include "Hacks/String.h"
#include "Hacks/Parse.h"

#include "Hacks/NET/File.h"
#include "Hacks/NET/Path.h"
#include "Hacks/FileReader.h"
#include <Utility/Error.h>
#include <Utility/ConsoleInformation.h>

#ifdef PS3
#include <Content/Texture.h>
#include <PSGL/psgl.h>
#include <PSGL/psglu.h>

#include "../../Core/src/Content/PS3/psglGtfLoader.h"
#include <Content/TexturePS3Internal.h>


extern std::string PS3_PATH_PREFIX;
extern ErrorType GLOBAL_NP_DISCONNECT_MESSAGE;

#endif

namespace CloudberryKingdom
{

	LanguageInfo::LanguageInfo( Localization::Language MyLanguage, const std::wstring &MyDirectory, const std::wstring &FontSuffix )
	{
		this->MyLanguage = MyLanguage;
		this->MyDirectory = MyDirectory;
		this->FontSuffix = FontSuffix;
	}

#ifdef PS3
	// Global font texture.
	static ::Texture GlobalFontTexture;

	// Holder for font texture.
	static ResourceHolder GlobalFontHolder;

	static boost::shared_ptr< Texture2D > GlobalIntermediateTextureContainer;
	static boost::shared_ptr< EzTexture > GlobalFontEzTexture;
#endif
    void Localization::LoadFont()
    {
		std::wstring name = L"Grobold_" + CurrentLanguage->FontSuffix;
		
#ifdef PS3
		std::string path = PS3_PATH_PREFIX + "ContentPS3/Fonts/" + WstringToUtf8( name ) + ".gtf";

		// FIXME: This makes sure that the font textures are always loaded in the same block of memory.
		psglCreateTextureReferenceFromGTFFileToPreallocatedPBO( path.c_str(),
			true, false, GlobalFontTexture.impl_.internal_->Ref.textureID,
			GlobalFontTexture.impl_.internal_->Ref.bufferID, GlobalFontEzTexture->Width,
			GlobalFontEzTexture->Height );

		boost::shared_ptr< EzTexture > ez_t = GlobalFontEzTexture;
#else
        boost::shared_ptr<EzTexture> ez_t = Tools::Texture(name);
#endif
        FontTexture = ez_t->getTex(); //Content->Load<Texture2D>( Path::Combine( L"Fonts", name ) );
		FontTexture->Width = ez_t->Width;
		FontTexture->Height = ez_t->Height;

        Resources::hf = boost::make_shared<HackFont>( WstringToUtf8( name )  );
            
        if ( Resources::Font_Grobold42 != 0 )
        {
            Resources::Font_Grobold42->HFont->font = Resources::hf;
            Resources::Font_Grobold42->HOutlineFont->font = Resources::hf;
            Resources::Font_Grobold42_2->HFont->font = Resources::hf;
            Resources::Font_Grobold42_2->HOutlineFont->font = Resources::hf;
        }
    }

	SubtitleAction::SubtitleAction( ActionType MyAction, float Time, const std::wstring &Text )
	{
		this->MyAction = MyAction;
		this->Time = Time;

		this->Text = Text;
		Replace( this->Text, std::wstring( L"\\n" ), std::wstring( L"\n" ) );
	}

	boost::shared_ptr<ContentManager> Localization::Content;
	std::vector<boost::shared_ptr<SubtitleAction> > Localization::Subtitles;

	const int Localization::NumLanguages = 10;
	std::map<Localization::Language, boost::shared_ptr<LanguageInfo> > Localization::Languages;
	boost::shared_ptr<LanguageInfo> Localization::CurrentLanguage;
	boost::shared_ptr<Texture2D> Localization::FontTexture;
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

		//std::wstring bpath = L"C:/Users/Ezra/Desktop/Dir/Pwnee/CK/Source/CloudberryKingdomPort/Cloudberry-Kingdom-Port/Content/Localization/Test.lcl";
		//BinaryReader breader = BinaryReader( bpath );
		//std::wstring s1 = breader.ReadString();
		//std::wstring s2 = breader.ReadString();
		//std::wstring s3 = breader.ReadString();
		//std::wstring s4 = breader.ReadString();

		// Open the giant translation file
		Tools::UseInvariantCulture();
		//boost::shared_ptr<FileStream> stream = File->Open( path, FileMode::Open, FileAccess::Read, FileShare::None );
		//boost::shared_ptr<StreamReader> reader = boost::make_shared<StreamReader>( stream );
		boost::shared_ptr<FileReader> reader = boost::make_shared<FileReader>( path );

		std::wstring line;

		// Read the file, adding translations to the corresponding dictionaries
		int LineCount = 0;

		for ( int i = 0; i < Words_EnumLength; i++)
		{
			line = reader->ReadLine();

			Replace( line, std::wstring( L"\\n" ), std::wstring( L"\n" ) );
			std::vector<std::wstring> bits = Split( line, L'\t' );

			for ( int i = 0; i < NumLanguages; i++ )
				Text[ static_cast<Language>( i ) ].insert( std::make_pair( static_cast<Words>( LineCount ), bits[ i ] ) );

			LineCount++;
		}

		//reader->Close();
		//stream->Close();
	}

    std::wstring Localization::LanguageName(Language language)
    {
        return Text[ language ][ Words_Identifier ];
    }

	std::wstring Localization::WordString( Words Word )
	{
		return Text[ CurrentLanguage->MyLanguage ][ Word ];
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

	bool IsWestern( Localization::Language language )
	{
		return
			language == Localization::Language_ENGLISH || language == Localization::Language_GERMAN ||
			language == Localization::Language_FRENCH  || language == Localization::Language_SPANISH ||
			language == Localization::Language_ITALIAN || language == Localization::Language_PORTUGUESE ||
			language == Localization::Language_RUSSIAN;
	}

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

		bool NeedToReloadFont = 
					CurrentLanguage == 0 ||
					IsWestern( SelectedLanguage ) && !IsWestern( CurrentLanguage->MyLanguage ) ||
					!IsWestern( SelectedLanguage ) && SelectedLanguage != CurrentLanguage->MyLanguage;

		CurrentLanguage = Languages[ SelectedLanguage ];

        // Load font. Lock first if it alread exists.
        if ( Resources::hf == 0 )
        {
            LoadFont();
        }
        else
        {
			if ( NeedToReloadFont )
			{
				Resources::hf_Mutex->Lock();
				{
					LoadFont();
				}
				Resources::hf_Mutex->Unlock();
			}
        }

		ConsoleLanguage errorLanguage = ConsoleLanguage_ENGLISH;
		switch( SelectedLanguage )
		{
		case Language_ENGLISH:
			errorLanguage = ConsoleLanguage_ENGLISH;
			break;
		case Language_JAPANESE:
			errorLanguage = ConsoleLanguage_JAPANESE;
			break;
		case Language_GERMAN:
			errorLanguage = ConsoleLanguage_GERMAN;
			break;
		case Language_PORTUGUESE:
			errorLanguage = ConsoleLanguage_PORTUGUESE;
			break;
		case Language_ITALIAN:
			errorLanguage = ConsoleLanguage_ITALIAN;
			break;
		case Language_FRENCH:
			errorLanguage = ConsoleLanguage_FRENCH;
			break;
		case Language_SPANISH:
			errorLanguage = ConsoleLanguage_SPANISH;
			break;
		case Language_RUSSIAN:
			errorLanguage = ConsoleLanguage_RUSSIAN;
			break;
		case Language_KOREAN:
			errorLanguage = ConsoleLanguage_KOREAN;
			break;
		case Language_CHINESE:
			errorLanguage = ConsoleLanguage_CHINESE;
			break;
		}
		SetErrorLanguage( errorLanguage );

#ifdef PS3
		GLOBAL_NP_DISCONNECT_MESSAGE = ErrorType(
			WstringToUtf8( WordString( Words_Err_PS3_PsnLoggedOut ) )
		);
#endif
	}

	void Localization::Initialize()
	{
		/*Content = boost::make_shared<ContentManager>( Tools::GameClass->getServices(), Path::Combine(std::wstring( L"Content" ), std::wstring( L"Localization" )) );*/
#if defined(PC_VERSION)
		Content = boost::make_shared<ContentManager>( std::wstring( L"Content" ) );
#else
		Content = boost::make_shared<ContentManager>( std::wstring( L"" ) );
#endif

		Languages.insert( std::make_pair( Language_CHINESE, boost::make_shared<LanguageInfo>( Language_CHINESE, std::wstring( L"Chinese" ), std::wstring( L"Chinese" ) ) ) );
		Languages.insert( std::make_pair( Language_ENGLISH, boost::make_shared<LanguageInfo>( Language_ENGLISH, std::wstring( L"English" ), std::wstring( L"Western" ) ) ) );
		Languages.insert( std::make_pair( Language_FRENCH, boost::make_shared<LanguageInfo>( Language_FRENCH, std::wstring( L"French" ), std::wstring( L"Western" ) ) ) );
		Languages.insert( std::make_pair( Language_GERMAN, boost::make_shared<LanguageInfo>( Language_GERMAN, std::wstring( L"German" ), std::wstring( L"Western" ) ) ) );
		Languages.insert( std::make_pair( Language_ITALIAN, boost::make_shared<LanguageInfo>( Language_ITALIAN, std::wstring( L"Italian" ), std::wstring( L"Western" ) ) ) );
		Languages.insert( std::make_pair( Language_JAPANESE, boost::make_shared<LanguageInfo>( Language_JAPANESE, std::wstring( L"Japanese" ), std::wstring( L"Japanese" ) ) ) );
		Languages.insert( std::make_pair( Language_KOREAN, boost::make_shared<LanguageInfo>( Language_KOREAN, std::wstring( L"Korean" ), std::wstring( L"Korean" ) ) ) );
		Languages.insert( std::make_pair( Language_PORTUGUESE, boost::make_shared<LanguageInfo>( Language_PORTUGUESE, std::wstring( L"Portuguese" ), std::wstring( L"Western" ) ) ) );
		Languages.insert( std::make_pair( Language_RUSSIAN, boost::make_shared<LanguageInfo>( Language_RUSSIAN, std::wstring( L"Russian" ), std::wstring( L"Western" ) ) ) );
		Languages.insert( std::make_pair( Language_SPANISH, boost::make_shared<LanguageInfo>( Language_SPANISH, std::wstring( L"Spanish" ), std::wstring( L"Western" ) ) ) );

		std::wstring path = Path::Combine( Content->RootDirectory, Path::Combine( std::wstring( L"Localization" ), std::wstring( L"LocalizationCpp.tsv" ) ) );
		ReadTranslationGrid( path );

#ifdef PS3
		GlobalFontHolder = ResourceHolder( &GlobalFontTexture );

		GLuint pbo, tex;
		glGenBuffers( 1, &pbo );
		glBindBuffer( GL_TEXTURE_REFERENCE_BUFFER_SCE, pbo );
		glBufferData( GL_TEXTURE_REFERENCE_BUFFER_SCE, 27 * 1024 * 1024, NULL, GL_STATIC_DRAW );
		glBindBuffer( GL_TEXTURE_REFERENCE_BUFFER_SCE, 0 );

		glGenTextures( 1, &tex );
		glBindTexture( GL_TEXTURE_2D, tex );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_ALLOCATION_HINT_SCE, GL_TEXTURE_TILED_GPU_SCE );
		glBindTexture( GL_TEXTURE_2D, 0 );

		GlobalFontTexture.impl_.internal_->Ref.bufferID = pbo;
		GlobalFontTexture.impl_.internal_->Ref.textureID = tex;

		GlobalIntermediateTextureContainer = boost::make_shared< Texture2D >( NULL, 0, 0 );
		GlobalIntermediateTextureContainer->texture_ = ResourcePtr< Texture >( &GlobalFontHolder );
		GlobalFontEzTexture = boost::make_shared< EzTexture >();
		GlobalFontEzTexture->setTex( GlobalIntermediateTextureContainer );
#endif
	}

        float Localization::ParseTime( const std::wstring &s )
        {
            std::vector<std::wstring> data = Split( s, L':' );

			float output = 0;
            float seconds = ParseFloat( data[2], output ) ? output : -1;
            float minutes = ParseFloat( data[1], output ) ? output : -1;

            return seconds + minutes * 60;
        }

	void Localization::ReadSubtitleInfo( const std::wstring &VideoName )
	{
		// FIXME: THIS IS WHERE VIDEOS WITH NO SUBTITLES GO.
		if( VideoName == L"LogoSalad" )
			return;
		else if( VideoName == L"LogoSalad_ESRB" )
			return;
		else if( VideoName == L"Credits" )
			return;

		std::wstring path = Path::Combine(
#if defined( CAFE ) || defined( PS3 )
			std::wstring(),
#else
			std::wstring( L"Content" ),
#endif
			Path::Combine( std::wstring( L"Localization" ),
				Path::Combine( std::wstring( L"Subtitles" ),
					Path::Combine( CurrentLanguage->MyDirectory, VideoName ) ) ) ) + L".tsv";

		if ( !File::Exists( path ) ) return;

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

		float timeval = 0;

		line = reader->ReadLine();
		while ( line != std::wstring( L"" ) )
		{
			line = Tools::RemoveComment_DashStyle( line );
			if ( line == std::wstring( L"" ) || line.length() <= 1 )
			{
				line = reader->ReadLine();
				continue;
			}

			std::vector<std::wstring> data = Split( line, L'\t' );

            if ( data.size() <= 1 ) continue;
			
			std::wstring identifier = data[1];

			if ( identifier == std::wstring( L"+" ) )
			{
				if (data.size() < 3) continue;

                Subtitles.push_back(boost::make_shared<SubtitleAction>(SubtitleAction::ActionType_SHOW, ParseTime( data[0] ), data[2] ) );
                        
                Index++;
			}
			else if ( identifier == std::wstring( L"-" ) )
			{
				Subtitles.push_back(boost::make_shared<SubtitleAction>(SubtitleAction::ActionType_HIDE, ParseTime( data[0] ), L"" ) );
			}

			line = reader->ReadLine();
		}

		//reader->Close();
		//stream->Close();
	}
}
