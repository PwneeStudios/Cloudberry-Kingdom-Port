#include <global_header.h>

namespace CloudberryKingdom
{

	Template_GameObject::Template_GameObject()
	{
	}

	void Template_GameObject::Init()
	{
		GameObject::Init();
	}

	void Template_GameObject::MyDraw()
	{
	}

	void Template_GameObject::MyPhsxStep()
	{
		boost::shared_ptr<Level> level = getCore()->MyLevel;
	}

}
