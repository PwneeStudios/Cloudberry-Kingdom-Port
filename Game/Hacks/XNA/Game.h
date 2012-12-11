#ifndef _XNAGAME_H_
#define _XNAGAME_H_

struct Game
{

	std::shared_ptr<ContentManager> Content;

	std::shared_ptr<ContentManager> getContent()
	{
		return Content;
	}

};

#endif
