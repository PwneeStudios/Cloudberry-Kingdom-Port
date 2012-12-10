#include <global_header.h>

#include "Hacks/List.h"

namespace CloudberryKingdom
{

	void Globals::InitializeStatics()
	{
		Globals::ContentDirectory = _T( "" );
		Color tempVector[] = { Color::LightSeaGreen, Color::BlueViolet, Color::Fuchsia, Color::Gainsboro };
		Globals::OnOffBlockColors = VecFromArray( tempVector );
		bool tempVector2[] = { false, false, false, false };
		Globals::ColorSwitch = VecFromArray( tempVector2 );
		std::wstring tempVector3[] = { _T( "Fireball" ), _T( "Spike" ), _T( "Falling Block" ), _T( "Flying Blob" ), _T( "Fire Spinner" ), _T( "Moving Block" ), _T( "Elevator" ), _T( "Spikey Guy" ), _T( "Spinner" ), _T( "Laser" ), _T( "Ghost Block" ), _T( "Bouncy Block" ), _T( "Cloud" ), _T( "General" ), _T( "Speed" ), _T( "Jump" ), _T( "Ceiling" ) };
		Globals::UpgradeString = VecFromArray( tempVector3 );
	}

	// Statics
	std::wstring Globals::ContentDirectory;
	std::vector<Color> Globals::OnOffBlockColors;
	std::vector<bool> Globals::ColorSwitch;
	std::vector<std::wstring> Globals::UpgradeString;

}
