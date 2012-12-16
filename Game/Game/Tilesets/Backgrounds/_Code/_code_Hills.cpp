#include <global_header.h>

namespace CloudberryKingdom
{

	Background_Hills::Background_Hills( const std::wstring &Name ) : BackgroundTemplate( Name )
	{
	}

	void Background_Hills::Code( const boost::shared_ptr<Background> &b )
	{
		BackgroundTemplate::Code( b );

		Background::_code_Hills( b );
	}

	Background_HillsRain::Background_HillsRain( const std::wstring &Name ) : BackgroundTemplate( Name )
	{
	}

	void Background_HillsRain::Code( const boost::shared_ptr<Background> &b )
	{
		BackgroundTemplate::Code( b );

		Background::_code_Hills( b );
		Background::AddRainLayer( b );
	}
}
