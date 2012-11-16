#ifndef EZSONG
#define EZSONG

#include <global_header.h>

namespace Microsoft
{
	namespace Xna
	{
		namespace Framework
		{
			namespace Media
			{
				class Song;
			}
		}
	}
}









namespace CloudberryKingdom
{
	class EzSong
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
