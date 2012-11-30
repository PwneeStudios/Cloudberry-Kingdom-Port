#ifndef EZSONG
#define EZSONG

#include <global_header.h>

namespace CloudberryKingdom
{
	class EzSong : std::enable_shared_from_this<EzSong>
	{
	public:
		std::shared_ptr<Song> song;
		std::wstring Name, SongName, ArtistName, FileName;
		bool Enabled, AlwaysLoaded;

		float Volume;

		bool DisplayInfo;

		EzSong();

		double Play( bool DisplayInfo );

	private:
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef EZSONG
