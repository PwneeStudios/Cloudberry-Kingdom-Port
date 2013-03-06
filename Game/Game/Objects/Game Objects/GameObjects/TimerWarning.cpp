#include <global_header.h>

namespace CloudberryKingdom
{

	void TimerWarning::OnAdd()
	{
		GameObject::OnAdd();

		Fullscreen->FullScreen( MyGame->MyLevel->getMainCamera() );
	}

	void TimerWarning::ReleaseBody()
	{
		GameObject::ReleaseBody();
	}

	TimerWarning::TimerWarning() :
		t( 0 ),
		Threshhold( 0 ),
		SubThreshholdCount( 0 )
	{
		// Object is carried over through multiple levels, so prevent it from being released.
		InitializeInstanceFields();
		PreventRelease = true;

		PauseOnPause = true;

		// Make a quad to fill the whole screen
		Fullscreen = boost::make_shared<QuadClass>();
	}

	void TimerWarning::MyDraw()
	{
		GameObject::MyDraw();

		if ( SubThreshholdCount == 0 )
			return;

		Fullscreen->setPos( Tools::CurLevel->getMainCamera()->getPos() );
		Fullscreen->Draw();
	}

	void TimerWarning::MyPhsxStep()
	{
		GameObject::MyPhsxStep();

		if ( getCore()->MyLevel->Watching || getCore()->MyLevel->Finished )
			return;

		// Is time running out?
		if ( MyTimer->getTime() < Threshhold )
		{
			float target_t = ( Threshhold - MyTimer->getTime() ) / static_cast<float>(Threshhold);

			if ( MyTimer->getTime() < 30 )
				target_t = 0;

			t = .8f * t + .2f * target_t;

			//int Period = 90;
			int Period = Threshhold + 15 + 1;

			// Do something dramatic every second
			if ( SubThreshholdCount % Period == 15 )
			{
	#if defined(XBOX)
				float LeftIntensity = CoreMath::Restrict( .4f,.4f, t );
				float RightIntensity = CoreMath::Restrict( .1f,.3f, t );

				std::vector<boost::shared_ptr<PlayerData> > vec = PlayerManager::getAlivePlayers();
				for ( std::vector<boost::shared_ptr<PlayerData> >::const_iterator player = vec.begin(); player != vec.end(); ++player )
					Tools::SetVibration( ( *player )->MyPlayerIndex, LeftIntensity, LeftIntensity, 30 );
	#endif
			}

			// Flash the screen
			float h = static_cast<float>( cos( 2 * M_PI * static_cast<float>( SubThreshholdCount - 15 ) / Period ) );
			//h = CoreMath::Restrict(.5f, 1f, h) - .5f;
			//h = (CoreMath::Restrict(.35f, 1f, h) - .35f) * .4f;
			h = ( CoreMath::RestrictVal( .65f, 1.f, h ) - .65f ) * 1.5f;

			SetAlpha( h );


			SubThreshholdCount++;
		}
		else
		{
			SetAlpha( 0 );
			SubThreshholdCount = 0;
		}
	}

	void TimerWarning::SetAlpha( float alpha )
	{
		Fullscreen->Quad_Renamed.SetColor( Vector4( .8f,.4f,.4f, alpha ) );
	}

	void TimerWarning::InitializeInstanceFields()
	{
		Threshhold = 106;
		SubThreshholdCount = 0;
	}
}
