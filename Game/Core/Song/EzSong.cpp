#include <global_header.h>



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
			Tools::SongWad->DisplaySongInfo( this );

		return song->Duration.TotalSeconds;
	}

	void EzSong::InitializeInstanceFields()
	{
		DisplayInfo = true;
	}
}
