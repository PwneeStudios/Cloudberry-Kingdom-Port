#include "small_header.h"

#include "CloudberryKingdom.h"
#include "MainClass/XboxPC/CloudberryKingdom.XnaGameClass.h"

#include <Content/Texture.h>
#include <Content/Wad.h>
#include <Core.h>
#include <cstdlib>
#include <Utility/Limits.h>
#include <Graphics/QuadDrawer.h>
#include <Graphics/TextDrawer.h>
#include <Graphics/Types.h>
#include <Utility/Log.h>
#include <vector>

static boost::shared_ptr<GameTime> gt = boost::make_shared<GameTime>();

void CloudberryKingdomWrapper::Initialize()
{
	game = boost::make_shared<CloudberryKingdom::XnaGameClass>();

	CloudberryKingdom::Tools::GameClass = game;

	game->Initialize();
	game->LoadContent();

	gt->ElapsedGameTime.TotalSeconds = 0.016f;
	gt->TotalGameTime = TimeSpan( 0, 0, 0 );
	LOG_WRITE( "Initialize done\n" );
}

void CloudberryKingdomWrapper::Update()
{
	game->Update( gt );
	game->Draw( gt );

	gt->TotalGameTime.TotalSeconds += gt->ElapsedGameTime.TotalSeconds;
}
