#include "_code_Hills.h"
#include "Game/Tilesets/Backgrounds/_Code/CloudberryKingdom.Background.h"

using namespace Microsoft::Xna::Framework;

namespace CloudberryKingdom
{

	Background_Hills::Background_Hills( const std::wstring &Name ) : BackgroundTemplate( Name )
	{
	}

	void Background_Hills::Code( const std::shared_ptr<Background> &b )
	{
		BackgroundTemplate::Code( b );

		Background::_code_Hills( b );
	}

	Background_HillsRain::Background_HillsRain( const std::wstring &Name ) : BackgroundTemplate( Name )
	{
	}

	void Background_HillsRain::Code( const std::shared_ptr<Background> &b )
	{
		BackgroundTemplate::Code( b );

		Background::_code_Hills( b );
		Background::AddRainLayer( b );
	}
}
