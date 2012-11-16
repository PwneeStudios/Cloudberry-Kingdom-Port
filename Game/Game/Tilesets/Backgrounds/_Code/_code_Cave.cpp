#include <global_header.h>

using namespace Microsoft::Xna::Framework;

namespace CloudberryKingdom
{

	Background_Cave::Background_Cave( const std::wstring &Name ) : BackgroundTemplate( Name )
	{
	}

	void Background_Cave::Code( const std::shared_ptr<Background> &b )
	{
		BackgroundTemplate::Code( b );

		Background::_code_Cave( b );
	}
}
