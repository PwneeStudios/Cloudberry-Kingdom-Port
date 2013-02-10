#ifndef _RESOURCES_MUSIC_H_
#define _RESOURCES_MUSIC_H_

#include <vector>
#include <string>

std::vector<std::wstring> MusicList()
{
	std::vector<std::wstring> v;
	v.reserve( 25 );

#if defined( PS3 ) || defined( CAFE )	
	v.push_back( std::wstring( L"Music/140_Mph_in_the_Fog^Blind_Digital.mp3" ) );
	v.push_back( std::wstring( L"Music/Blue_Chair^Blind_Digital.mp3" ) );
	v.push_back( std::wstring( L"Music/Evidence^Blind_Digital.mp3" ) );
	v.push_back( std::wstring( L"Music/Get_a_Grip^Peacemaker.mp3" ) );
	v.push_back( std::wstring( L"Music/Happy^James_Stant.mp3" ) );
	v.push_back( std::wstring( L"Music/House^Blind_Digital.mp3" ) );
	v.push_back( std::wstring( L"Music/Nero's_Law^Peacemaker.mp3" ) );
	v.push_back( std::wstring( L"Music/Ripcurl^Blind_Digital.mp3" ) );
	v.push_back( std::wstring( L"Music/The_Fat_is_in_the_Fire^Peacemaker.mp3" ) );
	v.push_back( std::wstring( L"Music/The_Heavens_Opened^Peacemaker.mp3" ) );
	v.push_back( std::wstring( L"Music/Tidy_Up^Peacemaker.mp3" ) );
	v.push_back( std::wstring( L"Music/Writer's_Block^Peacemaker.mp3" ) );
#else
	v.push_back( std::wstring( L"Music/140_Mph_in_the_Fog^Blind_Digital.wma" ) );
	v.push_back( std::wstring( L"Music/Blue_Chair^Blind_Digital.wma" ) );
	v.push_back( std::wstring( L"Music/Evidence^Blind_Digital.wma" ) );
	v.push_back( std::wstring( L"Music/Get_a_Grip^Peacemaker.wma" ) );
	v.push_back( std::wstring( L"Music/Happy.wma" ) );
	v.push_back( std::wstring( L"Music/House^Blind_Digital.wma" ) );
	v.push_back( std::wstring( L"Music/Nero's_Law^Peacemaker.wma" ) );
	v.push_back( std::wstring( L"Music/Ripcurl^Blind_Digital.wma" ) );
	v.push_back( std::wstring( L"Music/The_Fat_is_in_the_Fire^Peacemaker.wma" ) );
	v.push_back( std::wstring( L"Music/The_Heavens_Opened^Peacemaker.wma" ) );
	v.push_back( std::wstring( L"Music/Tidy_Up^Peacemaker.wma" ) );
	v.push_back( std::wstring( L"Music/Writer's_Block^Peacemaker.wma" ) );
#endif

	return v;
}

#endif
