#ifndef _RESOURCES_SOUND_H_
#define _RESOURCES_SOUND_H_

#include <vector>
#include <string>

std::vector<std::wstring> SoundList()
{
	std::vector<std::wstring> v;
	v.reserve( 800 );

	v.push_back( std::wstring( L"Sound/Bash.wav" ) );
	v.push_back( std::wstring( L"Sound/Blob_Squish.wav" ) );
	v.push_back( std::wstring( L"Sound/BouncyBlock_Bounce.wav" ) );
	v.push_back( std::wstring( L"Sound/BouncyJump.wav" ) );
	v.push_back( std::wstring( L"Sound/BouncyJump_Small.wav" ) );
	v.push_back( std::wstring( L"Sound/BoxHero_Jump.wav" ) );
	v.push_back( std::wstring( L"Sound/BoxHero_Land.wav" ) );
	v.push_back( std::wstring( L"Sound/Checkpoint.wav" ) );
	v.push_back( std::wstring( L"Sound/Coin.wav" ) );
	v.push_back( std::wstring( L"Sound/Death_Chime.wav" ) );
	v.push_back( std::wstring( L"Sound/Door_Opening.wav" ) );
	v.push_back( std::wstring( L"Sound/Door_Slamming.wav" ) );
	v.push_back( std::wstring( L"Sound/DoubleJump.wav" ) );
	v.push_back( std::wstring( L"Sound/DustCloud_Explode.wav" ) );
	v.push_back( std::wstring( L"Sound/ExtraLifeSound.wav" ) );
	v.push_back( std::wstring( L"Sound/HeroUnlockedSound.wav" ) );
	v.push_back( std::wstring( L"Sound/Jetpack.wav" ) );
	v.push_back( std::wstring( L"Sound/Jump.wav" ) );
	v.push_back( std::wstring( L"Sound/jump5.wav" ) );
	v.push_back( std::wstring( L"Sound/Menu_Back.wav" ) );
	v.push_back( std::wstring( L"Sound/Menu_Hover.wav" ) );
	v.push_back( std::wstring( L"Sound/Menu_Select.wav" ) );
	v.push_back( std::wstring( L"Sound/Menu_Tick.wav" ) );
	v.push_back( std::wstring( L"Sound/PerfectSound.wav" ) );
	v.push_back( std::wstring( L"Sound/Piece_Explosion_Small.wav" ) );
	v.push_back( std::wstring( L"Sound/Pop_1.wav" ) );
	v.push_back( std::wstring( L"Sound/Pop_2.wav" ) );
	v.push_back( std::wstring( L"Sound/Pop_3.wav" ) );
	v.push_back( std::wstring( L"Sound/Record_Scratch.wav" ) );

	return v;
}

#endif
