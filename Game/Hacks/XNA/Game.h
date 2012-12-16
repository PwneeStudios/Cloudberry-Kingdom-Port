#ifndef _XNAGAME_H_
#define _XNAGAME_H_


struct Game
{

	boost::shared_ptr<ContentManager> Content;

	boost::shared_ptr<ContentManager> getContent()
	{
		return Content;
	}

};

#endif
