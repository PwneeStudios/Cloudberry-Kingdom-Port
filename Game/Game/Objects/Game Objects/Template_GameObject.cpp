#include "Template_GameObject.h"
#include "Game/Objects/In Game Objects/Grab/CloudberryKingdom.Level.h"

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
		std::shared_ptr<Level> level = getCore()->MyLevel;
	}
}
