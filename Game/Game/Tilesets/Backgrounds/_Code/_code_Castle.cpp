#include "_code_Castle.h"
#include "Game/Tilesets/Backgrounds/_Code/CloudberryKingdom.Background.h"

using namespace Microsoft::Xna::Framework;

namespace CloudberryKingdom
{

	Background_Castle::Background_Castle( const std::wstring &Name ) : BackgroundTemplate( Name )
	{
	}

	void Background_Castle::Code( const std::shared_ptr<Background> &b )
	{
		BackgroundTemplate::Code( b );

		Background::_code_Castle( b );
	}
}
