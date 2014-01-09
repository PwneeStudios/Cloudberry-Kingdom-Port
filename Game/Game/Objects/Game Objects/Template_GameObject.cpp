#include <small_header.h>
#include "Game/Objects/Game Objects/Template_GameObject.h"

#include "Game/Objects/Game Objects/GameObject.h"
#include "Game/Objects/In Game Objects/Grab/MakeData.h"
#include "Game/Level/Level.h"


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
