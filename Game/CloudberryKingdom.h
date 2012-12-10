#ifndef _CLOUDBERRY_KINGDOM_H_
#define _CLOUDBERRY_KINGDOM_H_

#include <GameLoop.h>

/**
 * Cloudberry Kingdom game.
 */
struct CloudberryKingdomWrapper : public GameLoop
{
	


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
