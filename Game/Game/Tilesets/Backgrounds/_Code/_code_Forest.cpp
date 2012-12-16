#include <global_header.h>

namespace CloudberryKingdom
{

	Background_Forest::Background_Forest( const std::wstring &Name ) : BackgroundTemplate( Name )
	{
	}

	void Background_Forest::Code( const boost::shared_ptr<Background> &b )
	{
		BackgroundTemplate::Code( b );

		Background::_code_Forest( b );
		Background::TurnOffSnow( b );
	}

	Background_ForestSnow::Background_ForestSnow( const std::wstring &Name ) : BackgroundTemplate( Name )
	{
	}

	void Background_ForestSnow::Code( const boost::shared_ptr<Background> &b )
	{
		BackgroundTemplate::Code( b );

		Background::_code_Forest( b );
		Background::TurnOnSnow( b );
	}
}
