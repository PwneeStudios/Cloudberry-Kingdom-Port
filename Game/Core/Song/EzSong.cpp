#include <global_header.h>

#include <Audio/MediaPlayer.h>
#include <Audio/Song.h>

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

		if ( Tools::SongWad->SuppressNextInfoDisplay )
			Tools::SongWad->SuppressNextInfoDisplay = DisplayInfo = false;

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
