#include <global_header.h>

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;
using namespace Microsoft::Xna::Framework;

namespace CloudberryKingdom
{

	BackgroundFloater_Stationary::BackgroundFloater_Stationary( const std::shared_ptr<Level> &level ) : BackgroundFloater( level )
	{
	}

	void BackgroundFloater_Stationary::PhsxStep( const std::shared_ptr<BackgroundFloaterList> &list )
	{
	}

	void BackgroundFloater_Stationary::Draw()
	{
		Tools::QDrawer->DrawQuad( MyQuad->Quad_Renamed );
	}
}
