#include <global_header.h>

namespace CloudberryKingdom
{

	Background_Sea::Background_Sea( const std::wstring &Name ) : BackgroundTemplate( Name )
	{
	}

	void Background_Sea::Code( const boost::shared_ptr<Background> &b )
	{
		BackgroundTemplate::Code( b );

		Background::_code_Sea( b );
	}

	Background_SeaRain::Background_SeaRain( const std::wstring &Name ) : BackgroundTemplate( Name )
	{
	}

	void Background_SeaRain::Code( const boost::shared_ptr<Background> &b )
	{
		BackgroundTemplate::Code( b );

		Background::_code_Sea( b );
		Background::AddRainLayer( b );
	}
}
