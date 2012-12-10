#include <global_header.h>

namespace CloudberryKingdom
{

	void MainVideo::InitializeStatics()
	{
		MainVideo::Content = 0;
		MainVideo::Playing = false;
		MainVideo::CurrentVideo = 0;
		MainVideo::VPlayer = 0;
		MainVideo::VEZTexture = std::make_shared<EzTexture>();
		MainVideo::Duration = 0;
		MainVideo::StartTime;
		MainVideo::CanSkip = false;
		MainVideo::LengthUntilUserCanSkip = 0;
		MainVideo::Subtitles;
		MainVideo::SubtitleIndex = 0;
		MainVideo::SubtitleQuad = std::make_shared<QuadClass>();
	}

	// Statics
	std::shared_ptr<ContentManager> MainVideo::Content;
	bool MainVideo::Playing;
	std::shared_ptr<Video> MainVideo::CurrentVideo;
	std::shared_ptr<VideoPlayer> MainVideo::VPlayer;
	std::shared_ptr<EzTexture> MainVideo::VEZTexture;
	double MainVideo::Duration;
	DateTime MainVideo::StartTime;
	bool MainVideo::CanSkip;
	float MainVideo::LengthUntilUserCanSkip;
	std::vector<std::shared_ptr<SubtitleAction> > MainVideo::Subtitles;
	int MainVideo::SubtitleIndex;
	std::shared_ptr<QuadClass> MainVideo::SubtitleQuad = std::make_shared<QuadClass>();


	void MainVideo::StartVideo_CanSkipIfWatched( const std::wstring &MovieName )
	{
	#if defined(DEBUG)
		bool CanSkip = true;
	#else
		bool CanSkip = UserPowers::WatchedVideo[ MovieName ];
	#endif
		StartVideo( MovieName, CanSkip, 100000 );
	}

	void MainVideo::StartVideo_CanSkipIfWatched_OrCanSkipAfterXseconds( const std::wstring &MovieName, float LengthUntilCanSkip )
	{
		bool CanSkip = UserPowers::WatchedVideo[ MovieName ];
		StartVideo( MovieName, CanSkip, LengthUntilCanSkip );
	}

	void MainVideo::StartVideo( const std::wstring &MovieName, bool CanSkipVideo, float LengthUntilCanSkip )
	{
		Subtitles = Localization::GetSubtitles( MovieName );
		SubtitleIndex = 0;
		SubtitleQuad->Show = false;

		if ( Content == 0 )
		{
			Content = std::make_shared<ContentManager>( Tools::GameClass->getServices(), _T("Content") );
		}

		CanSkip = CanSkipVideo;
		LengthUntilUserCanSkip = LengthUntilCanSkip;

		UserPowers::WatchedVideo.Add( MovieName );
		UserPowers::SetToSave();

		Playing = true;
		Cleaned = false;

		//CurrentVideo = Tools.GameClass.Content.Load<Video>(Path.Combine("Movies", MovieName));
		CurrentVideo = Content->Load<Video>( Path::Combine( _T( "Movies" ), MovieName ) );

		VPlayer = std::make_shared<VideoPlayer>();
		VPlayer->IsLooped = false;
		VPlayer->Play( CurrentVideo );

		Duration = CurrentVideo->Duration.TotalSeconds;
		StartTime = DateTime::Now();
	}

	double MainVideo::ElapsedTime()
	{
		return ( DateTime::Now() - StartTime ).TotalSeconds;
	}

bool MainVideo::Paused = false;

	void MainVideo::UserInput()
	{
		ButtonCheck::UpdateControllerAndKeyboard_StartOfStep();

	//#if WINDOWS && DEBUG
	//            if (ButtonCheck.State(Keys.P).Pressed)
	//            {
	//                if (Paused)
	//                    VPlayer.Resume();
	//                else
	//                    VPlayer.Pause();

	//                Paused = !Paused;
	//            }

	//            if (!(ButtonCheck.State(Keys.P).Down))
	//#endif

		// End the video if the user presses a key
		if ( CanSkip && PlayerManager::Players.size() > 0 && ElapsedTime() > 0.3f || ElapsedTime() > LengthUntilUserCanSkip )
		{
			// Update songs
			if ( Tools::SongWad != 0 )
				Tools::SongWad->PhsxStep();

			if ( ButtonCheck::AnyKey() )
				Playing = false;
		}

		ButtonCheck::UpdateControllerAndKeyboard_EndOfStep( Tools::TheGame->Resolution );
	}

	void MainVideo::Subtitle()
	{
		if ( Subtitles.empty() )
			return;

		SubtitleQuad->Draw();
		Tools::QDrawer->Flush();

		if ( SubtitleIndex >= static_cast<int>( Subtitles.size() ) )
			return;

		std::shared_ptr<SubtitleAction> NextSubtitle = Subtitles[ SubtitleIndex ];
		if ( ElapsedTime() > NextSubtitle->Time )
		{
			switch ( NextSubtitle->MyAction )
			{
				case SubtitleAction::ActionType_SHOW:
					SubtitleQuad->Show = true;
					SubtitleQuad->Quad_Renamed.setMyTexture( NextSubtitle->MyTexture );
					SubtitleQuad->ScaleToTextureSize();
					SubtitleQuad->Scale( 1.445f );
					SubtitleQuad->Update();
					SubtitleQuad->setPos( Vector2( 0, -700.f - SubtitleQuad->Quad_Renamed.getHeight() / 2.f ) );
					break;

				case SubtitleAction::ActionType_HIDE:
					SubtitleQuad->Show = false;
					break;
			}

			SubtitleIndex++;
		}
	}

	bool MainVideo::Draw()
	{
		if ( !Playing )
		{
			Finish();
			return false;
		}

		Tools::TheGame->MyGraphicsDevice->Clear( Color::Black );

		UserInput();

		if ( ElapsedTime() > Duration )
			Playing = false;

		VEZTexture->setTex( VPlayer->GetTexture() );
		VEZTexture->Width = VEZTexture->getTex()->Width;
		VEZTexture->Height = VEZTexture->getTex()->Height;

		Vector2 Pos = Tools::getCurCamera()->getPos();
		Tools::QDrawer->DrawToScaleQuad( Pos, Color::White, 3580, VEZTexture, Tools::BasicEffect );
		Tools::QDrawer->Flush();

		Subtitle();

	//#if WINDOWS && DEBUG
	//                Tools.StartSpriteBatch();
	//                Tools.Render.MySpriteBatch.DrawString(Resources.LilFont.Font,
	//                        ElapsedTime().ToString(),
	//                        Tools.CurCamera.Pos + new Vector2(900, 100),
	//                        Color.Orange, 0, Vector2.Zero, 1.5f, SpriteEffects.None, 0);
	//                Tools.Render.EndSpriteBatch();
	//#endif

		return true;
	}

bool MainVideo::Cleaned = true;

	void MainVideo::Finish()
	{
		Playing = false;

		if ( Cleaned )
			return;

		// FIXME: No deleting.
		//delete VPlayer;
		CurrentVideo.reset();

		Cleaned = true;
	}
}
