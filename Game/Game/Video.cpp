#include <global_header.h>

#include "Hacks/NET/Path.h"

#include <Game/CloudberryKingdom/CloudberryKingdom.CloudberryKingdomGame.h>

#include "Video.h"
#include <Core/Tools/Set.h>
#include <Core.h>
#include <Graphics/QuadDrawer.h>

namespace CloudberryKingdom
{

	void MainVideo::InitializeStatics()
	{
		MainVideo::Content = 0;
		MainVideo::Playing = false;
#if defined( CAFE )
		MainVideo::CurrentVideo = boost::make_shared< Video >();
#else
		MainVideo::CurrentVideo = 0;
#endif
		MainVideo::VPlayer = 0;
		MainVideo::VEZTexture = boost::make_shared<EzTexture>();
		MainVideo::Duration = 0;
		MainVideo::Elapsed = 0;
		MainVideo::CanSkip = false;
		MainVideo::LengthUntilUserCanSkip = 0;
		MainVideo::Subtitles;
		MainVideo::SubtitleIndex = 0;
		MainVideo::SubtitleText = 0;
	}

	// Statics
	boost::shared_ptr<ContentManager> MainVideo::Content;
	bool MainVideo::Playing;
	boost::shared_ptr<Video> MainVideo::CurrentVideo;
	boost::shared_ptr<VideoPlayer> MainVideo::VPlayer;
	boost::shared_ptr<EzTexture> MainVideo::VEZTexture;
	double MainVideo::Duration, MainVideo::Elapsed;
	bool MainVideo::CanSkip;
	float MainVideo::LengthUntilUserCanSkip;
	std::vector<boost::shared_ptr<SubtitleAction> > MainVideo::Subtitles;
	int MainVideo::SubtitleIndex;
	boost::shared_ptr<EzText> MainVideo::SubtitleText;


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

	// NOTE: This overrides functionality of MainVideo::UpdateElapsedTime()
	// in order to be used from the WiiU video player.
	static void UpdateElapsedTimeProxy( float amount, bool reset )
	{
		if( reset )
			MainVideo::Elapsed = 0.f;
		else
			MainVideo::Elapsed += amount;
	}

	// Helper method to draw subtitles from the other thread.
	static void DrawSubtitles()
	{
		Tools::Render->SetStandardRenderStates();

		Tools::QDrawer->SetInitialState();

		Tools::EffectWad->SetCameraPosition(
			Vector4( 0, 0, 0.001, 0.001 )
		);

		// FIXME: Get this from a variable.
		Tools::SetDefaultEffectParams( 1.77778f );

		Tools::Render->SetStandardRenderStates();

		QUAD_DRAWER->SetEffect( Tools::BasicEffect->effect );

		// FIXME: This ensures that the subtitle is never displayed when a movie is killed.
		if( MainVideo::Elapsed < 500000.f )
			MainVideo::Subtitle();

		/*Tools::QDrawer->DrawString( Resources::Font_Grobold42->HFont, ToString( MainVideo::Elapsed ),  Vector2( 0 ), Vector4( 1 ), Vector2( 1 ) );
		Tools::QDrawer->Flush();*/
	}

	void MainVideo::StartVideo( const std::wstring &MovieName, bool CanSkipVideo, float LengthUntilCanSkip )
	{
#if DEBUG
		CanSkipVideo = true;
#endif

		Subtitles = Localization::GetSubtitles( MovieName );

        if (Subtitles.size() > 0)
        {
            SubtitleIndex = 0;
        }

        if (SubtitleText != 0)
        {
            SubtitleText->Release();
            SubtitleText.reset();
        }

		if ( Content == 0 )
		{
			Content = boost::make_shared<ContentManager>( std::wstring( L"Content" ) );
		}

		CanSkip = CanSkipVideo;
		LengthUntilUserCanSkip = LengthUntilCanSkip;

		UserPowers::WatchedVideo.Add( MovieName );
		UserPowers::SetToSave();

		Playing = true;
		Cleaned = false;

		//CurrentVideo = Tools::GameClass.Content.Load<Video>(Path.Combine("Movies", MovieName));
#if defined( CAFE )
		// I cry a little more.
		if( MovieName == L"Cutscene_1" )
		{
			CurrentVideo->Path = "/vol/content/Movies/Cutscene_1.mp4";
			CurrentVideo->Duration.TotalSeconds = 64.083333f;
		}
		else if( MovieName == L"Cutscene_2" )
		{
			CurrentVideo->Path = "/vol/content/Movies/Cutscene_2.mp4";
			CurrentVideo->Duration.TotalSeconds = 34.0416666f;
		}
		else if( MovieName == L"Cutscene_3" )
		{
			CurrentVideo->Path = "/vol/content/Movies/Cutscene_3.mp4";
			CurrentVideo->Duration.TotalSeconds = 30.8333333f;
		}
		else if( MovieName == L"Cutscene_4" )
		{
			CurrentVideo->Path = "/vol/content/Movies/Cutscene_4.mp4";
			CurrentVideo->Duration.TotalSeconds = 40.25f;
		}
		else if( MovieName == L"Cutscene_5" )
		{
			CurrentVideo->Path = "/vol/content/Movies/Cutscene_5.mp4";
			CurrentVideo->Duration.TotalSeconds = 55.29166666f;
		}
		else if( MovieName == L"Cutscene_6" )
		{
			CurrentVideo->Path = "/vol/content/Movies/Cutscene_6.mp4";
			CurrentVideo->Duration.TotalSeconds = 206.875f;
		}
		else if( MovieName == L"Credits" )
		{
			CurrentVideo->Path = "/vol/content/Movies/Credits.mp4";
			CurrentVideo->Duration.TotalSeconds = 142.0833333f;
		}
		else if( MovieName == L"LogoSalad" )
		{
			CurrentVideo->Path = "/vol/content/Movies/LogoSalad.mp4";
			CurrentVideo->Duration.TotalSeconds = 9.933333333f;
		}
#elif defined( PC_VERSION ) || defined( PS3 )
		//CurrentVideo = Content->Load<Video>( Path::Combine( std::wstring( L"Movies" ), MovieName ) );
		// FIXME
		Tools::Warning();
		CurrentVideo.reset();
		Duration = 1;
		Elapsed = 0;
		return;
#endif


		
		Duration = CurrentVideo->Duration.TotalSeconds;
		Elapsed = 0;

#ifdef CAFE
		VPlayer = boost::make_shared<VideoPlayer>( UpdateElapsedTimeProxy, DrawSubtitles );
#else
		VPlayer = boost::make_shared<VideoPlayer>();
#endif
		VPlayer->IsLooped = false;
		VPlayer->SetVolume( __max( Tools::SoundVolume->getVal(), Tools::MusicVolume->getVal() ) );
		VPlayer->Play( CurrentVideo );

		VPlayer->SetVolume( __max( Tools::MusicVolume->getVal(), Tools::SoundVolume->getVal() ) );

	}

    void MainVideo::UpdateElapsedTime()
    {
        Elapsed += Tools::TheGame->DeltaT;
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

		// FIXME: Uncomment this or people will be able to skip movie accidentally!
		if ( CanSkip && PlayerManager::Players.size() > 0 && Elapsed > 0.3f || Elapsed > LengthUntilUserCanSkip )
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

        if ( SubtitleText != 0 )
        {
            SubtitleText->Draw( Tools::getCurCamera() );
            Tools::QDrawer->Flush();
        }

		if ( SubtitleIndex >= static_cast<int>( Subtitles.size() ) )
			return;

		boost::shared_ptr<SubtitleAction> NextSubtitle = Subtitles[ SubtitleIndex ];
		if ( Elapsed > NextSubtitle->Time )
		{
			switch ( NextSubtitle->MyAction )
			{
				case SubtitleAction::ActionType_SHOW:
                    SubtitleText = boost::make_shared<EzText>( NextSubtitle->Text, Resources::Font_Grobold42, 1433.333f, true, true, .666f );
                    SubtitleText->Show = true;
                    SubtitleText->_Scale = .4000f;
                    SubtitleText->setPos( Vector2(0, -830 + SubtitleText->Height / 2) );
                    SubtitleText->MyFloatColor = ColorHelper::Gray(.925f);
                    SubtitleText->OutlineColor = ColorHelper::Gray(.100f);
					break;

				case SubtitleAction::ActionType_HIDE:
                    SubtitleText->Show = false;
                    SubtitleText->Release();
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

		Tools::EffectWad->SetCameraPosition( Vector4( 0.f, 0.f, .001f, .001f ) );

		Tools::TheGame->MyGraphicsDevice->Clear( Color::Black );

#ifndef CAFE
		UpdateElapsedTime();
#endif
 		UserInput();

        if ( Elapsed > Duration )
            Playing = false;

#if defined( PC_VERSION ) || defined( PS3 )
		// FIXME: PC version should draw the video
		return true;
#else
		VPlayer->DrawFrame();
#endif
		/*VEZTexture->setTex( VPlayer->GetTexture() );
		VEZTexture->Width = VEZTexture->getTex()->Width;
		VEZTexture->Height = VEZTexture->getTex()->Height;

		Vector2 Pos = Vector2(0);
		//Vector2 Pos = Tools::getCurCamera()->getPos();
		Tools::QDrawer->DrawToScaleQuad( Pos, Color::White, 3580, VEZTexture, Tools::BasicEffect );
		Tools::QDrawer->Flush();*/

		// FIXME: Need to put subtitles back.
		//Subtitle();

	//#if WINDOWS && DEBUG
	//                Tools::StartSpriteBatch();
	//                Tools::Render.MySpriteBatch.DrawString(Resources::LilFont.Font,
	//                        ElapsedTime().ToString(),
	//                        Tools::CurCamera.Pos + new Vector2(900, 100),
	//                        Color.Orange, 0, Vector2.Zero, 1.5f, SpriteEffects.None, 0);
	//                Tools::Render.EndSpriteBatch();
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
		VPlayer.reset();
		//CurrentVideo.reset();

		Cleaned = true;
	}
}
