#include <global_header.h>

#include "Hacks/XNA/MediaPlayer.h"

namespace CloudberryKingdom
{

	EzSong::EzSong()
	{
		InitializeInstanceFields();
		Volume = 1;
		Enabled = true;
	}

	double EzSong::Play( bool DisplayInfo )
	{
		Tools::CurSongVolume = Volume;

		MediaPlayer::Stop();
		MediaPlayer::Play( song );

		if ( DisplayInfo )
			Tools::SongWad->DisplaySongInfo( shared_from_this() );

		return song->Duration.TotalSeconds;
	}

	void EzSong::InitializeInstanceFields()
	{
		Enabled = false; AlwaysLoaded = false;
		Volume = 0;
		DisplayInfo = false;

		DisplayInfo = true;
	}
}
