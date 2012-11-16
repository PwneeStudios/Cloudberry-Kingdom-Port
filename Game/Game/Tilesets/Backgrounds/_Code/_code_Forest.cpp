#include <global_header.h>

using namespace Microsoft::Xna::Framework;

namespace CloudberryKingdom
{

	Background_Forest::Background_Forest( const std::wstring &Name ) : BackgroundTemplate( Name )
	{
	}

	void Background_Forest::Code( const std::shared_ptr<Background> &b )
	{
		BackgroundTemplate::Code( b );

		Background::_code_Forest( b );
		Background::TurnOffSnow( b );
	}

	Background_ForestSnow::Background_ForestSnow( const std::wstring &Name ) : BackgroundTemplate( Name )
	{
	}

	void Background_ForestSnow::Code( const std::shared_ptr<Background> &b )
	{
		BackgroundTemplate::Code( b );

		Background::_code_Forest( b );
		Background::TurnOnSnow( b );
	}
}
