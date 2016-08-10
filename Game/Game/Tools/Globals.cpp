#include <small_header.h>
#include "Game/Tools/Globals.h"



#include "Hacks/List.h"

namespace CloudberryKingdom
{

	void Globals::InitializeStatics()
	{
		Globals::ContentDirectory = std::wstring( L"" );
		Color tempVector[] = { Color::LightSeaGreen, Color::BlueViolet, Color::Fuchsia, Color::Gainsboro };
		Globals::OnOffBlockColors = VecFromArray( tempVector );
		bool tempVector2[] = { false, false, false, false };
		Globals::ColorSwitch = VecFromArray( tempVector2 );
		std::wstring tempVector3[] = { std::wstring( L"Fireball" ), std::wstring( L"Spike" ), std::wstring( L"Falling Block" ), std::wstring( L"Flying Blob" ), std::wstring( L"Fire Spinner" ), std::wstring( L"Moving Block" ), std::wstring( L"Elevator" ), std::wstring( L"Spikey Guy" ), std::wstring( L"Spinner" ), std::wstring( L"Laser" ), std::wstring( L"Ghost Block" ), std::wstring( L"Bouncy Block" ), std::wstring( L"Cloud" ), std::wstring( L"General" ), std::wstring( L"Speed" ), std::wstring( L"Jump" ), std::wstring( L"Ceiling" ) };
		Globals::UpgradeString = VecFromArray( tempVector3 );
	}

	// Statics
	std::wstring Globals::ContentDirectory;
	std::vector<Color> Globals::OnOffBlockColors;
	std::vector<bool> Globals::ColorSwitch;
	std::vector<std::wstring> Globals::UpgradeString;

}
