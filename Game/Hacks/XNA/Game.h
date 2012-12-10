#ifndef _XNAGAME_H_
#define _XNAGAME_H_

class Game
{

public:

	std::shared_ptr<ContentManager> getContent()
	{
		return std::shared_ptr<ContentManager>();
	}

	std::shared_ptr<GameServiceContainer> getServices()
	{
		return std::shared_ptr<GameServiceContainer>();
	}

};

#endif
