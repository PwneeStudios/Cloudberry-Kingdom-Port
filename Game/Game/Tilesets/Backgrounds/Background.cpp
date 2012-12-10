#include <global_header.h>

namespace CloudberryKingdom
{

	void BackgroundType::InitializeStatics()
	{
		BackgroundType::None = std::make_shared<BackgroundTemplate>();
		BackgroundType::Random = std::make_shared<BackgroundTemplate>();
		
		BackgroundType::_Sea = std::make_shared<Background_Castle>( _T( "sea" ) );
		BackgroundType::_Sea_Rain = std::make_shared<Background_Castle>( _T( "sea_rain" ) );
		BackgroundType::_Hills = std::make_shared<Background_Castle>( _T( "hills" ) );
		BackgroundType::_Hills_Rain = std::make_shared<Background_Castle>( _T( "hills_rain" ) );
		BackgroundType::_Forest = std::make_shared<Background_Castle>( _T( "forest" ) );
		BackgroundType::_Forest_Rain = std::make_shared<Background_Castle>( _T( "forest_snow" ) );
		BackgroundType::_Cloud = std::make_shared<Background_Castle>( _T( "cloud" ) );
		BackgroundType::_Cloud_Rain = std::make_shared<Background_Castle>( _T( "cloud_rain" ) );
		BackgroundType::_Cave = std::make_shared<Background_Castle>( _T( "cave" ) );
		BackgroundType::_Castle = std::make_shared<Background_Castle>( _T( "castle" ) );
	}

	std::map<std::wstring, std::shared_ptr<BackgroundTemplate> > BackgroundType::NameLookup, BackgroundType::PathLookup;
	std::shared_ptr<BackgroundTemplate> BackgroundType::None, BackgroundType::Random, BackgroundType::_Sea, BackgroundType::_Sea_Rain, BackgroundType::_Hills, BackgroundType::_Hills_Rain, BackgroundType::_Forest, BackgroundType::_Forest_Rain, BackgroundType::_Cloud, BackgroundType::_Cloud_Rain, BackgroundType::_Cave, BackgroundType::_Castle;

	void BackgroundType::AddTemplate( const std::shared_ptr<BackgroundTemplate> &template_Renamed )
	{
		// FIXME: These used to be AddOrOverwrite.
		NameLookup[ template_Renamed->Name ] = template_Renamed;
		PathLookup[ template_Renamed->File ] = template_Renamed;
		//NameLookup.AddOrOverwrite( template_Renamed->Name, template_Renamed );
		//PathLookup.AddOrOverwrite( template_Renamed->File, template_Renamed );
	}

	void BackgroundType::Load( const std::wstring &path )
	{
		std::shared_ptr<BackgroundTemplate> template_Renamed;
		if ( PathLookup.find( path ) != PathLookup.end() )
		{
			template_Renamed = PathLookup[ path ];
		}
		else
		{
			template_Renamed = std::make_shared<BackgroundTemplate>();

			std::wstring name = Tools::GetFileName( path );
			template_Renamed->Name = name;
			template_Renamed->File = path;

			AddTemplate( template_Renamed );
		}

		template_Renamed->MadeOfCode = false;
		template_Renamed->MadeOfText = true;
	}

	void BackgroundTemplate::Code( const std::shared_ptr<Background> &b )
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

		BackgroundType::AddTemplate( shared_from_this() );
	}

	std::shared_ptr<Background> BackgroundTemplate::MakeInstanceOf()
	{
		std::shared_ptr<RegularBackground> b = std::make_shared<RegularBackground>();
		b->MyTemplate = shared_from_this();

		if ( MadeOfCode || File == _T( "" ) )
			return b;

		return b;
	}

	void BackgroundTemplate::InitializeInstanceFields()
	{
		MadeOfCode = true;
		MadeOfText = false;
		File = _T( "" );
	}

	RegularBackground::RegularBackground()
	{
		InitializeInstanceFields();
	}

	void RegularBackground::Init( const std::shared_ptr<Level> &level )
	{
		MyLevel = level;
		MyCollection = std::make_shared<BackgroundCollection>( MyLevel );
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
		std::shared_ptr<Camera> Cam = MyLevel->getMainCamera();
		Cam->SetVertexCamera();

		if ( MyLevel->IndependentDeltaT > 0 )
			MyCollection->PhsxStep();

		MyCollection->Draw();

		Tools::QDrawer->Flush();
	}

	void RegularBackground::DrawForeground()
	{
		Tools::QDrawer->Flush();
		std::shared_ptr<Camera> Cam = MyLevel->getMainCamera();
		Cam->SetVertexCamera();

		MyCollection->Draw( 1, true );

		Tools::QDrawer->Flush();
	}

	void RegularBackground::InitializeInstanceFields()
	{
		MyTemplate = 0;
	}
}
