#ifndef _GAME_LOOP_H_
#define _GAME_LOOP_H_

/**
 * Application entry point.
 */
class GameLoop
{

public:

	virtual ~GameLoop() { }

	/// Initialize the game.
	virtual void Initialize() = 0;

	/// Update a single frame.
	virtual void Update() = 0;

};

#endif
