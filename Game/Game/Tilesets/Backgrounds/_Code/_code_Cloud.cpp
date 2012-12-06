#include <global_header.h>

namespace CloudberryKingdom
{

	Background_Cloud::Background_Cloud( const std::wstring &Name ) : BackgroundTemplate( Name )
	{
	}

	void Background_Cloud::Code( const std::shared_ptr<Background> &b )
	{
		BackgroundTemplate::Code( b );

		Background::_code_Cloud( b );
	}

	Background_CloudRain::Background_CloudRain( const std::wstring &Name ) : BackgroundTemplate( Name )
	{
	}

	void Background_CloudRain::Code( const std::shared_ptr<Background> &b )
	{
		BackgroundTemplate::Code( b );

		Background::_code_Cloud( b );
		Background::AddRainLayer( b );
	}
}
