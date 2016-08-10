#ifndef _CLOUDBERRY_KINGDOM_H_
#define _CLOUDBERRY_KINGDOM_H_

#include <GameLoop.h>

#include <forward_declarations.h>

#include <Game/CloudberryKingdom/CloudberryKingdom.CloudberryKingdomGame.h>
#include <MainClass/XboxPC/CloudberryKingdom.XnaGameClass.h>

/**
 * Cloudberry Kingdom game.
 */
struct CloudberryKingdomWrapper : public GameLoop
{
	
	boost::shared_ptr<CloudberryKingdom::XnaGameClass> game;

	/**
	 * @see GameLoop::Initialize
	 */
	void Initialize();

	/**
	 * @see GameLoop::Update
	 */
	void Update();

};

#endif
