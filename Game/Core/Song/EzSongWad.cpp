#include <global_header.h>

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;
using namespace Microsoft::Xna::Framework;
using namespace Microsoft::Xna::Framework::Media;

namespace CloudberryKingdom
{

	EzSongWad::EzSongWad()
	{
		InitializeInstanceFields();
		SongList = std::vector<EzSong*>();

		CurIndex = 0;

		StartingSong = false;

		DefaultCam = std::make_shared<Camera>();

		MediaPlayer->IsRepeating = false;
	}

	void EzSongWad::FadeOut()
	{
		Fading = true;
	}

	void EzSongWad::Stop()
	{
		MediaPlayer::Stop();
		PlayNext = false;
	}

	void EzSongWad::Pause()
	{
		Paused = true;
		MediaPlayer::Pause();
	}

	void EzSongWad::Unpause()
	{
		Paused = false;
		MediaPlayer::Resume();
	}

	void EzSongWad::DisplaySongInfo( const std::shared_ptr<EzSong> &song )
	{
		if ( !DisplayInfo )
			return;
		if ( !song->DisplayInfo )
			return;

		SongInfoText = std::make_shared<EzText>( song->SongName + _T( "\n" ) + song->ArtistName, Resources::LilFont, true, true );
		SongInfoText->_Pos = Vector2( -850, -790 );
		SongInfoText->MyFloatColor = Vector4( 1, 1, 1, 4.5f );
		SongInfoText->Alpha = -.45f;
		SongInfoText->FixedToCamera = true;

		DisplayingInfo = true;
	}

	void EzSongWad::Draw()
	{
		if ( CloudberryKingdomGame::ShowSongInfo && DisplayInfo && DisplayingInfo && SongInfoText != 0 && !Tools::ShowLoadingScreen && Tools::CurGameData != 0 && !Tools::CurGameData->PauseGame && !Tools::CurGameData->SuppressSongInfo )
		{
			SongInfoText->Draw( DefaultCam );
		}
	}

	void EzSongWad::PhsxStep()
	{
		if ( Paused && MediaPlayer::State != MediaState::Paused )
			Pause();

		FadePhsx();

		DisplayPhsx();

		CheckForNext();
	}

	void EzSongWad::FadePhsx()
	{
		if ( Fading )
		{
			Fade -= .015f;
			if ( Fade <= 0 )
			{
				PlayNext = false;
				MediaPlayer::Stop();
				Fading = false;
			}
		}

		Tools::setVolumeFade( Fade );
	}

	void EzSongWad::DisplayPhsx()
	{
		if ( DisplayingInfo && SongInfoText != 0 )
		{
			SongInfoText->MyFloatColor.W -= .02f;

			if ( SongInfoText->Alpha < 1 )
				SongInfoText->Alpha += .03f;
			if ( SongInfoText->MyFloatColor.W <= 0 )
				DisplayingInfo = false;
		}
	}

	void EzSongWad::UpdateElapsedTime()
	{
		Elapsed += Tools::TheGame->DeltaT;
	}

	void EzSongWad::CheckForNext()
	{
		if ( StartingSong )
		{
			if ( MediaPlayer->State == MediaState::Playing )
				StartingSong = false;
			else
				return;
		}

		UpdateElapsedTime();
		if ( !Fading )
		{
			// Whether the player can change the current song
			bool CanControl = PlayerControl;
			if ( CanControl )
				if ( PlayList.empty() || PlayList.size() <= 1 )
					CanControl = false;

			if ( CanControl && ButtonCheck::State( ControllerButtons_RT, -1 ).Pressed )
				Next();
			else if ( CanControl && ButtonCheck::State( ControllerButtons_LT, -1 ).Pressed )
				Prev();

			// Switch to the next song if the current song is over
			else if ( PlayNext && Elapsed > Duration )
				Next();
		}
	}

	bool EzSongWad::IsPlaying()
	{
		if ( MediaPlayer->State == MediaState::Playing )
			return true;
		else
			return false;
	}

	void EzSongWad::Next( const std::shared_ptr<EzSong> &song )
	{
		CurIndex = PlayList.find( song );
		if ( CurIndex < 0 )
			CurIndex = 0;

		SetSong( CurIndex );
	}

	void EzSongWad::Next()
	{
		CurIndex++;

		if ( CurIndex < 0 )
			CurIndex = PlayList.size() - 1;
		if ( CurIndex >= PlayList.size() )
			CurIndex = 0;

		SetSong( CurIndex );
	}

	void EzSongWad::Prev()
	{
		CurIndex--;

		if ( CurIndex < 0 )
			CurIndex = PlayList.size() - 1;
		if ( CurIndex >= PlayList.size() )
			CurIndex = 0;

		SetSong( CurIndex );
	}

	void EzSongWad::DisposeAllUnused()
	{
		for ( std::vector<EzSong*>::const_iterator song = SongList.begin(); song != SongList.end(); ++song )
			if ( ( *song )->song != 0 && SongList[ CurIndex ] != *song && !SongList[ CurIndex ]->AlwaysLoaded )
			{
				delete ( *song )->song;
				( *song )->song.reset();
			}
	}

	void EzSongWad::Shuffle()
	{
		PlayList = Tools::GlobalRnd->Shuffle( PlayList );
	}

	void EzSongWad::SetPlayList( std::vector<EzSong*> &songs )
	{
		PlayList = std::vector<EzSong*>( songs );
	}

	void EzSongWad::SetPlayList( const std::wstring &name )
	{
		SetPlayList( FindByName( name ) );
	}

	void EzSongWad::SetPlayList( const std::shared_ptr<EzSong> &song )
	{
		std::vector<EzSong*> list = std::vector<EzSong*>();
		list.push_back( song );

		SetPlayList( list );
		CurIndex = 0;
	}

	bool EzSongWad::SamePlayList( std::vector<EzSong*> &list1, std::vector<EzSong*> &list2 )
	{
		if ( list1 == list2 )
			return true;

		if ( list1.empty() || list2.empty() )
			return false;

		if ( list1.size() == 1 && list2.size() == 1 && list1[ 0 ] == list2[ 0 ] )
			return true;

		return false;
	}

	void EzSongWad::Start( bool PlayNext )
	{
		Unpause();

		this->PlayNext = PlayNext;

		if ( !SamePlayList( CurrentPlayingList, PlayList ) )
		{
			CurrentPlayingList = PlayList;
			CurIndex = 0;
			Restart( PlayNext );
			return;
		}

		if ( !IsPlaying() )
		{
			Restart( PlayNext );
			return;
		}
	}

	void EzSongWad::Restart( bool PlayNext )
	{
		Restart( PlayNext, true );
	}

	void EzSongWad::Restart( bool PlayNext, bool DisplayInfo )
	{
		this->PlayNext = PlayNext;
		CurrentPlayingList = PlayList;
		SetSong( CurIndex, DisplayInfo );
		Fading = false;
		Tools::setVolumeFade( 1 );
	Fade = Tools::getVolumeFade();
	}

	void EzSongWad::SetSong( const std::wstring &name )
	{
		SetSong( PlayList.find( FindByName( name ) ) );
	}

	void EzSongWad::SetSong( const std::shared_ptr<EzSong> &song )
	{
		SetSong( PlayList.find( song ) );
	}

	void EzSongWad::SetSong( int Index )
	{
		SetSong( Index, true );
	}

	void EzSongWad::SetSong( int Index, bool DisplayInfo )
	{
		CurIndex = Index;
		StartingSong = true;
		Fade = 1;
		Fading = false;

		MediaPlayer::Stop();

		// Suppress next info display
		if ( DisplayInfo && SuppressNextInfoDisplay )
			DisplayInfo = SuppressNextInfoDisplay = false;

		Play( Index, DisplayInfo );
	}

	void EzSongWad::Play( int Index, bool DisplayInfo )
	{
		if ( PlayList[ CurIndex ]->song == 0 )
			PlayList[ CurIndex ]->song = Tools::GameClass->getContent()->Load<Song*>(_T("Music\\") + PlayList[ CurIndex ]->FileName);

		Elapsed = 0;
		Duration = PlayList[ CurIndex ]->Play( DisplayInfo );
	}

	std::shared_ptr<EzSong> EzSongWad::FindByName( const std::wstring &name )
	{
		for ( std::vector<EzSong*>::const_iterator Sng = SongList.begin(); Sng != SongList.end(); ++Sng )
//C# TO C++ CONVERTER TODO TASK: The following .NET 'String.Compare' reference is not converted:
			if ( std::wstring::Compare( ( *Sng )->Name, name, StringComparison::OrdinalIgnoreCase ) == 0 )
				return Sng;

	#if defined(DEBUG)
		Tools::Break();
	#endif

		return SongList[ 0 ];
	}

	void EzSongWad::AddSong( const std::wstring &Name )
	{
		std::shared_ptr<EzSong> NewSong = std::make_shared<EzSong>();

		int Index = Name.find( _T( "^" ) );

		std::wstring SongName, AristName;
		if ( Index > 0 )
		{
			SongName = Name.substr( 0, Index );
			AristName = Name.substr( Index + 1, Name.length() - Index - 1 );
		}
		else
		{
			SongName = Name;
			AristName = _T( "Unknown artist" );
		}

		NewSong->FileName = Name;
		NewSong->Name = Name;
		NewSong->SongName = SongName;
		NewSong->ArtistName = AristName;
		NewSong->song.reset();
		NewSong->AlwaysLoaded = false;

		SongList.push_back( NewSong );
	}

	void EzSongWad::AddSong( const std::shared_ptr<Song> &song, const std::wstring &Name )
	{
		std::shared_ptr<EzSong> NewSong = std::make_shared<EzSong>();

		int Index = Name.find( _T( "^" ) );

		std::wstring SongName, AristName;
		if ( Index > 0 )
		{
			SongName = Name.substr( 0, Index );
			AristName = Name.substr( Index + 1, Name.length() - Index - 1 );
		}
		else
		{
			SongName = Name;
			AristName = _T( "Unknown artist" );
		}

		NewSong->Name = Name;
		NewSong->SongName = SongName;
		NewSong->ArtistName = AristName;
		NewSong->song = song;
		NewSong->AlwaysLoaded = true;

		SongList.push_back( NewSong );
	}

	void EzSongWad::LoopSong( const std::shared_ptr<EzSong> &song )
	{
		Stop();
		SetPlayList( song );
		Start( true );
	}

	void EzSongWad::InitializeInstanceFields()
	{
		PlayNext = false;
		Paused = false;
		Duration = 0;
		Elapsed = 0;
		CurrentPlayingList = 0;
		SuppressNextInfoDisplay = false;
	}
}
