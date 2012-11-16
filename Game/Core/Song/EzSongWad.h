#ifndef EZSONGWAD
#define EZSONGWAD

#include <global_header.h>

namespace CloudberryKingdom
{
	class EzSong;
}

namespace CloudberryKingdom
{
	class EzText;
}

namespace CloudberryKingdom
{
	class Camera;
}

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
	class EzSongWad
	{
	public:
		bool PlayNext, PlayerControl, DisplayInfo;
		bool Fading;
		float Fade;

		std::vector<EzSong*> SongList;
		std::vector<EzSong*> PlayList;

		int CurIndex;

		bool StartingSong;

		std::shared_ptr<EzText> SongInfoText;
		bool DisplayingInfo;
	private:
		std::shared_ptr<Camera> DefaultCam;

	public:
		EzSongWad();

		void FadeOut();

		void Stop();

		bool Paused;
		void Pause();

		void Unpause();

		void DisplaySongInfo( const std::shared_ptr<EzSong> &song );

		void Draw();

		void PhsxStep();

	private:
		void FadePhsx();

		void DisplayPhsx();

	public:
		void UpdateElapsedTime();

	private:
		double Duration, Elapsed;
		void CheckForNext();

	public:
		bool IsPlaying();

		void Next( const std::shared_ptr<EzSong> &song );

		void Next();

		void Prev();

		void DisposeAllUnused();

		/// <summary>
		/// Shuffles the current play list
		/// </summary>
		void Shuffle();

		/// <summary>
		/// Set the play list and start playing it.
		/// </summary>
		void SetPlayList( std::vector<EzSong*> &songs );
		void SetPlayList( const std::wstring &name );

		/// <summary>
		/// Set the play list to a single song and start playing it.
		/// </summary>
		void SetPlayList( const std::shared_ptr<EzSong> &song );

		/// <summary>
		/// The play list currently playing
		/// (possibly different than the set play list, if it hasn't been started yet).
		/// </summary>
	private:
		std::vector<EzSong*> CurrentPlayingList;

		bool SamePlayList( std::vector<EzSong*> &list1, std::vector<EzSong*> &list2 );

		/// <summary>
		/// Starts the play list if it ISN'T already playing
		/// </summary>
	public:
		void Start( bool PlayNext );

		/// <summary>
		/// Starts or restarts the current song, eliminating all fading.
		/// </summary>
		void Restart( bool PlayNext );
		void Restart( bool PlayNext, bool DisplayInfo );

		void SetSong( const std::wstring &name );

		void SetSong( const std::shared_ptr<EzSong> &song );

		bool SuppressNextInfoDisplay;
		void SetSong( int Index );
		void SetSong( int Index, bool DisplayInfo );

		void Play( int Index, bool DisplayInfo );

		std::shared_ptr<EzSong> FindByName( const std::wstring &name );

		void AddSong( const std::wstring &Name );

		void AddSong( const std::shared_ptr<Song> &song, const std::wstring &Name );

		void LoopSong( const std::shared_ptr<EzSong> &song );

	private:
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef EZSONGWAD
