#include <global_header.h>

namespace CloudberryKingdom
{

	void BackgroundType::InitializeStatics()
	{
		BackgroundType::None = boost::make_shared<BackgroundTemplate>();
		BackgroundType::Random = boost::make_shared<BackgroundTemplate>();
		
		BackgroundType::_Sea = boost::make_shared<Background_Sea>( std::wstring( L"sea" ) );
		BackgroundType::AddTemplate( BackgroundType::_Sea->shared_from_this() );

		BackgroundType::_Sea_Rain = boost::make_shared<Background_SeaRain>( std::wstring( L"sea_rain" ) );
		BackgroundType::AddTemplate( BackgroundType::_Sea_Rain ->shared_from_this() );

		BackgroundType::_Hills = boost::make_shared<Background_Hills>( std::wstring( L"hills" ) );
		BackgroundType::AddTemplate( BackgroundType::_Hills->shared_from_this() );

		BackgroundType::_Hills_Rain = boost::make_shared<Background_HillsRain>( std::wstring( L"hills_rain" ) );
		BackgroundType::AddTemplate( BackgroundType::_Hills_Rain->shared_from_this() );

		BackgroundType::_Forest = boost::make_shared<Background_Forest>( std::wstring( L"forest" ) );
		BackgroundType::AddTemplate( BackgroundType::_Forest->shared_from_this() );

		BackgroundType::_Forest_Rain = boost::make_shared<Background_ForestSnow>( std::wstring( L"forest_snow" ) );
		BackgroundType::AddTemplate( BackgroundType::_Forest_Rain->shared_from_this() );

		BackgroundType::_Cloud = boost::make_shared<Background_Cloud>( std::wstring( L"cloud" ) );
		BackgroundType::AddTemplate( BackgroundType::_Cloud->shared_from_this() );

		BackgroundType::_Cloud_Rain = boost::make_shared<Background_CloudRain>( std::wstring( L"cloud_rain" ) );
		BackgroundType::AddTemplate( BackgroundType::_Cloud_Rain->shared_from_this() );

		BackgroundType::_Cave = boost::make_shared<Background_Cave>( std::wstring( L"cave" ) );
		BackgroundType::AddTemplate( BackgroundType::_Cave->shared_from_this() );

		BackgroundType::_Castle = boost::make_shared<Background_Castle>( std::wstring( L"castle" ) );
		BackgroundType::AddTemplate( BackgroundType::_Castle->shared_from_this() );
	}

	std::map<std::wstring, boost::shared_ptr<BackgroundTemplate> > BackgroundType::NameLookup, BackgroundType::PathLookup;
	boost::shared_ptr<BackgroundTemplate> BackgroundType::None, BackgroundType::Random, BackgroundType::_Sea, BackgroundType::_Sea_Rain, BackgroundType::_Hills, BackgroundType::_Hills_Rain, BackgroundType::_Forest, BackgroundType::_Forest_Rain, BackgroundType::_Cloud, BackgroundType::_Cloud_Rain, BackgroundType::_Cave, BackgroundType::_Castle;

	void BackgroundType::AddTemplate( const boost::shared_ptr<BackgroundTemplate> &template_Renamed )
	{
		// FIXME: These used to be AddOrOverwrite.
		NameLookup[ template_Renamed->Name ] = template_Renamed;
		PathLookup[ template_Renamed->File ] = template_Renamed;
		//NameLookup.AddOrOverwrite( template_Renamed->Name, template_Renamed );
		//PathLookup.AddOrOverwrite( template_Renamed->File, template_Renamed );
	}

	void BackgroundType::Load( const std::wstring &path )
	{
		boost::shared_ptr<BackgroundTemplate> template_Renamed;
		if ( PathLookup.find( path ) != PathLookup.end() )
		{
			template_Renamed = PathLookup[ path ];
		}
		else
		{
			template_Renamed = boost::make_shared<BackgroundTemplate>();

			std::wstring name = Tools::GetFileName( path );
			template_Renamed->Name = name;
			template_Renamed->File = path;

			AddTemplate( template_Renamed );
		}

		template_Renamed->MadeOfCode = false;
		template_Renamed->MadeOfText = true;
	}

	void BackgroundTemplate::Code( const boost::shared_ptr<Background> &b )
	{
	}

	BackgroundTemplate::BackgroundTemplate()
	{
		InitializeInstanceFields();
	}

	BackgroundTemplate::BackgroundTemplate( const std::wstring &Name )
	{
		InitializeInstanceFields();
		this->Name = this->File = Name;
		this->MadeOfCode = true;
		this->MadeOfText = false;

		//BackgroundType::AddTemplate( shared_from_this() );
	}

	boost::shared_ptr<Background> BackgroundTemplate::MakeInstanceOf()
	{
		boost::shared_ptr<RegularBackground> b = boost::make_shared<RegularBackground>();
		b->MyTemplate = shared_from_this();

		if ( MadeOfCode || File == std::wstring( L"" ) )
			return b;

		return b;
	}

	void BackgroundTemplate::InitializeInstanceFields()
	{
		MadeOfCode = true;
		MadeOfText = false;
		File = std::wstring( L"" );
	}

	RegularBackground::RegularBackground()
	{
		InitializeInstanceFields();
	}

	void RegularBackground::Init( const boost::shared_ptr<Level> &level )
	{
		MyLevel = level;
		MyCollection = boost::make_shared<BackgroundCollection>( MyLevel );
		TR = Vector2( 5000, 2000 );
		BL = Vector2( -2000, -2000 );

		if ( MyTemplate != 0 )
		{
			if ( MyTemplate->MadeOfCode )
				UseCode( MyTemplate, shared_from_this() );
			else if ( MyTemplate->MadeOfText )
				Load( MyTemplate->File );
		}
	}

	void RegularBackground::Draw()
	{
		Tools::QDrawer->Flush();
		boost::shared_ptr<Camera> Cam = MyLevel->getMainCamera();
		Cam->SetVertexCamera();

		if ( MyLevel->IndependentDeltaT > 0 )
			MyCollection->PhsxStep();

		MyCollection->Draw();

		Tools::QDrawer->Flush();
	}

	void RegularBackground::DrawForeground()
	{
		Tools::QDrawer->Flush();
		boost::shared_ptr<Camera> Cam = MyLevel->getMainCamera();
		Cam->SetVertexCamera();

		MyCollection->Draw( 1, true );

		Tools::QDrawer->Flush();
	}

	void RegularBackground::InitializeInstanceFields()
	{
		MyTemplate = 0;
	}
}
