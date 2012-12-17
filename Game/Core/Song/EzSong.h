#ifndef EZSONG
#define EZSONG

#include <global_header.h>

#include "Hacks/XNA/Song.h"

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
