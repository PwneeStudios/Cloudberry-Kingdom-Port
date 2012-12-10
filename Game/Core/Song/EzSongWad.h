#ifndef EZSONGWAD
#define EZSONGWAD

#include <global_header.h>

namespace CloudberryKingdom
{
	struct EzSongWad
	{
	
		bool PlayNext, PlayerControl, DisplayInfo;
		bool Fading;
		float Fade;

		std::vector<std::shared_ptr<EzSong> > SongList;
		std::vector<std::shared_ptr<EzSong> > PlayList;

		int CurIndex;

		bool StartingSong;

		std::shared_ptr<EzText> SongInfoText;
		bool DisplayingInfo;
	
		std::shared_ptr<Camera> DefaultCam;

	
		EzSongWad();

		void FadeOut();

		void Stop();

		bool Paused;
		void Pause();

		void Unpause();

		void DisplaySongInfo( const std::shared_ptr<EzSong> &song );

		void Draw();

		void PhsxStep();

	
		void FadePhsx();

		void DisplayPhsx();

	
		void UpdateElapsedTime();

	
		double Duration, Elapsed;
		void CheckForNext();

	
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
		void SetPlayList( std::vector<std::shared_ptr<EzSong> > &songs );
		void SetPlayList( const std::wstring &name );

		/// <summary>
		/// Set the play list to a single song and start playing it.
		/// </summary>
		void SetPlayList( const std::shared_ptr<EzSong> &song );

		/// <summary>
		/// The play list currently playing
		/// (possibly different than the set play list, if it hasn't been started yet).
		/// </summary>
	
		std::vector<std::shared_ptr<EzSong> > CurrentPlayingList;

		bool SamePlayList( std::vector<std::shared_ptr<EzSong> > &list1, std::vector<std::shared_ptr<EzSong> > &list2 );

		/// <summary>
		/// Starts the play list if it ISN'T already playing
		/// </summary>
	
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

	
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef EZSONGWAD
