#include <CorePS3.h>

#include <Architecture/Scheduler.h>
#include <Audio/MediaPlayer.h>
#include <Content/Wad.h>
#include <cstdlib>
#include <Utility/Limits.h>
#include <GameLoop.h>
#include <Graphics/QuadDrawer.h>
#include <Graphics/TextDrawer.h>
#include <Input/GamePad.h>
#include <Input/Keyboard.h>

// Private.
CorePS3::CorePS3( const CorePS3 &other ) :
	game_( other.game_ ),
	qd_( other.qd_ ),
	content_( other.content_ )
{

}

// Private.
CorePS3 &CorePS3::operator = ( const CorePS3 &rhs )
{
	return *this;
}

CorePS3::CorePS3( GameLoop &game ) :
	running_( false ),
	game_( game ),
	qd_( 0 ),
	content_( 0 ),
	scheduler_( 0 )
{
	scheduler_ = new Scheduler;

	content_ = new Wad( "Content/" );

	qd_ = new QuadDrawer;

	td_ = new TextDrawer;

	GamePad::Initialize();
	MediaPlayer::Initialize();
}

CorePS3::~CorePS3()
{
	MediaPlayer::Shutdown();
	GamePad::Shutdown();

	delete td_;

	delete qd_;

	delete content_;

	delete scheduler_;
}

int CorePS3::Run()
{
	running_ = true;

	game_.Initialize();

	while( running_ )
	{
		GamePad::Update();
		Keyboard::Update();

		scheduler_->MainThread();

		game_.Update();

		qd_->Flush();
	}

	return 0;
}

void CorePS3::Exit()
{
	running_ = false;
}
