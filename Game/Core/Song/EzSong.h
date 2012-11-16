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


//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;
using namespace Microsoft::Xna::Framework;
using namespace Microsoft::Xna::Framework::Media;

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
