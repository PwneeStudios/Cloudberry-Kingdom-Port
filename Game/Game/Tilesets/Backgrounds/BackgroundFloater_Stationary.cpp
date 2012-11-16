#include <global_header.h>


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
