#ifndef _RESOURCES_MUSIC_H_
#define _RESOURCES_MUSIC_H_

#include <vector>
#include <string>

std::vector<std::wstring> MusicList()
{
	std::vector<std::wstring> v;
	v.reserve( 800 );

	v.push_back( _T( "Content\\Music\\140_Mph_in_the_Fog^Blind_Digital.wma" ) );
	v.push_back( _T( "Content\\Music\\Blue_Chair^Blind_Digital.wma" ) );
	v.push_back( _T( "Content\\Music\\Evidence^Blind_Digital.wma" ) );
	v.push_back( _T( "Content\\Music\\Get_a_Grip^Peacemaker.wma" ) );
	v.push_back( _T( "Content\\Music\\Happy.wma" ) );
	v.push_back( _T( "Content\\Music\\House^Blind_Digital.wma" ) );
	v.push_back( _T( "Content\\Music\\Nero's_Law^Peacemaker.wma" ) );
	v.push_back( _T( "Content\\Music\\Ripcurl^Blind_Digital.wma" ) );
	v.push_back( _T( "Content\\Music\\The_Fat_is_in_the_Fire^Peacemaker.wma" ) );
	v.push_back( _T( "Content\\Music\\The_Heavens_Opened^Peacemaker.wma" ) );
	v.push_back( _T( "Content\\Music\\Tidy_Up^Peacemaker.wma" ) );
	v.push_back( _T( "Content\\Music\\Writer's_Block^Peacemaker.wma" ) );

	return v;
}

#endif
