#ifndef _XNAGAME_H_
#define _XNAGAME_H_

struct Game
{



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
