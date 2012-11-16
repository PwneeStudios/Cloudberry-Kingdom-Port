#include <global_header.h>



namespace CloudberryKingdom
{

std::wstring Globals::ContentDirectory = _T( "" );
const Color tempVector[] = { Color::LightSeaGreen, Color::BlueViolet, Color::Fuchsia, Color::Gainsboro };
std::vector<Color> Globals::OnOffBlockColors = std::vector<Color>( tempVector, tempVector + sizeof( tempVector ) / sizeof( tempVector[ 0 ] ) );
const bool tempVector2[] = { false, false, false, false };
std::vector<bool> Globals::ColorSwitch = std::vector<bool>( tempVector2, tempVector2 + sizeof( tempVector2 ) / sizeof( tempVector2[ 0 ] ) );
const std::wstring tempVector3[] = { _T( "Fireball" ), _T( "Spike" ), _T( "Falling Block" ), _T( "Flying Blob" ), _T( "Fire Spinner" ), _T( "Moving Block" ), _T( "Elevator" ), _T( "Spikey Guy" ), _T( "Spinner" ), _T( "Laser" ), _T( "Ghost Block" ), _T( "Bouncy Block" ), _T( "Cloud" ), _T( "General" ), _T( "Speed" ), _T( "Jump" ), _T( "Ceiling" ) };
std::vector<std::wstring> Globals::UpgradeString = std::vector<std::wstring>( tempVector3, tempVector3 + sizeof( tempVector3 ) / sizeof( tempVector3[ 0 ] ) );
}
