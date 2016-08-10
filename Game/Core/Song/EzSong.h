#ifndef EZSONG
#define EZSONG

#include <small_header.h>

//#include "Game/CloudberryKingdom/CloudberryKingdom.CloudberryKingdomGame.h"
//#include "Game/Tools/Tools.h"


namespace CloudberryKingdom
{
	struct EzSong : public boost::enable_shared_from_this<EzSong>
	{
	
		boost::shared_ptr<Song> song;
		std::wstring Name, SongName, ArtistName, FileName;
		bool Enabled, AlwaysLoaded;

		float Volume;

		bool DisplayInfo;

		EzSong();

		double Play( bool DisplayInfo );

	
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef EZSONG
