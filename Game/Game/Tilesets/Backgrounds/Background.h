#ifndef BACKGROUND
#define BACKGROUND

#include <global_header.h>

#include "Game/Tilesets/Backgrounds/_Code/CloudberryKingdom.Background.h"

namespace CloudberryKingdom
{

	struct BackgroundType
	{

	
		static void InitializeStatics();

	
		static std::map<std::wstring, boost::shared_ptr<BackgroundTemplate> > NameLookup, PathLookup;

		static boost::shared_ptr<BackgroundTemplate> None, Random, _Sea, _Sea_Rain, _Hills, _Hills_Rain, _Forest, _Forest_Rain, _Cloud, _Cloud_Rain, _Cave, _Castle;

			//_Sea = new BackgroundTemplate("sea", Background._code_Sea),
			//_Sea_Rain = new BackgroundTemplate("sea_rain", Background._code_Sea, Background.AddRainLayer),
			//_Hills = new BackgroundTemplate("hills", Background._code_Hills),
			//_Hills_Rain = new BackgroundTemplate("hills_rain", Background._code_Hills, Background.AddRainLayer),
			//_Forest = new BackgroundTemplate("forest", Background._code_Forest, Background.TurnOffSnow),
			//_Forest_Snow = new BackgroundTemplate("forest_snow", Background._code_Forest, Background.TurnOnSnow),
			//_Cloud = new BackgroundTemplate("cloud", Background._code_Cloud),
			//_Cloud_Rain = new BackgroundTemplate("cloud_rain", Background._code_Cloud, Background.AddRainLayer),
			//_Cave = new BackgroundTemplate("cave", Background._code_Cave),
			//_Castle = new BackgroundTemplate("castle", Background._code_Castle);

		static void AddTemplate( const boost::shared_ptr<BackgroundTemplate> &template_Renamed );

		static void Load( const std::wstring &path );
	};

	struct BackgroundTemplate : public boost::enable_shared_from_this<BackgroundTemplate>
	{
	
		std::wstring Name;
		bool MadeOfCode;
		bool MadeOfText;
		std::wstring File;

		virtual void Code( const boost::shared_ptr<Background> &b );

		BackgroundTemplate();

		BackgroundTemplate( const std::wstring &Name );

		boost::shared_ptr<Background> MakeInstanceOf();

	
		void InitializeInstanceFields();
	};

	struct RegularBackground : public Background
	{
	
		boost::shared_ptr<BackgroundTemplate> MyTemplate;

		RegularBackground();

		virtual void Init( const boost::shared_ptr<Level> &level );

		virtual void Draw();

		virtual void DrawForeground();

	
		void InitializeInstanceFields();
	};

}


#endif	//#ifndef BACKGROUND
