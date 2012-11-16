#include "EzSong.h"
#include "Game/Tools/Tools.h"

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;
using namespace Microsoft::Xna::Framework;
using namespace Microsoft::Xna::Framework::Media;

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
