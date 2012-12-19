#ifndef _RESOURCES_SOUND_H_
#define _RESOURCES_SOUND_H_

#include <vector>
#include <string>

std::vector<std::wstring> SoundList()
{
	std::vector<std::wstring> v;
	v.reserve( 800 );

	v.push_back( std::wstring( L"Content/Sound/Bash.wav" ) );
	v.push_back( std::wstring( L"Content/Sound/Blob_Squish.wav" ) );
	v.push_back( std::wstring( L"Content/Sound/BouncyBlock_Bounce.wav" ) );
	v.push_back( std::wstring( L"Content/Sound/BouncyJump.wav" ) );
	v.push_back( std::wstring( L"Content/Sound/BouncyJump_Small.wav" ) );
	v.push_back( std::wstring( L"Content/Sound/BoxHero_Jump.wav" ) );
	v.push_back( std::wstring( L"Content/Sound/BoxHero_Land.wav" ) );
	v.push_back( std::wstring( L"Content/Sound/Checkpoint.wav" ) );
	v.push_back( std::wstring( L"Content/Sound/Coin.wav" ) );
	v.push_back( std::wstring( L"Content/Sound/Death_Chime.wav" ) );
	v.push_back( std::wstring( L"Content/Sound/Door_Opening.wav" ) );
	v.push_back( std::wstring( L"Content/Sound/Door_Slamming.wav" ) );
	v.push_back( std::wstring( L"Content/Sound/DoubleJump.wav" ) );
	v.push_back( std::wstring( L"Content/Sound/DustCloud_Explode.wav" ) );
	v.push_back( std::wstring( L"Content/Sound/ExtraLifeSound.wav" ) );
	v.push_back( std::wstring( L"Content/Sound/HeroUnlockedSound.wav" ) );
	v.push_back( std::wstring( L"Content/Sound/Jetpack.wav" ) );
	v.push_back( std::wstring( L"Content/Sound/Jump.wav" ) );
	v.push_back( std::wstring( L"Content/Sound/jump5.wav" ) );
	v.push_back( std::wstring( L"Content/Sound/Menu_Back.wav" ) );
	v.push_back( std::wstring( L"Content/Sound/Menu_Hover.wav" ) );
	v.push_back( std::wstring( L"Content/Sound/Menu_Select.wav" ) );
	v.push_back( std::wstring( L"Content/Sound/Menu_Tick.wav" ) );
	v.push_back( std::wstring( L"Content/Sound/PerfectSound.wav" ) );
	v.push_back( std::wstring( L"Content/Sound/Piece_Explosion_Small.wav" ) );
	v.push_back( std::wstring( L"Content/Sound/Pop_1.wav" ) );
	v.push_back( std::wstring( L"Content/Sound/Pop_2.wav" ) );
	v.push_back( std::wstring( L"Content/Sound/Pop_3.wav" ) );
	v.push_back( std::wstring( L"Content/Sound/Record_Scratch.wav" ) );

	return v;
}

#endif
