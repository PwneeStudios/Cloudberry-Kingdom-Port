#ifndef CHEER
#define CHEER

#include <small_header.h>

//#include "Core/Graphics/Draw/DrawPile.h"
//#include "Core/Graphics/Draw/Quads/QuadClass.h"
#include "Game/Objects/Game Objects/GameObject.h"
//#include "Game/Objects/In Game Objects/Grab/MakeData.h"
//#include "Game/Level/Level.h"


namespace CloudberryKingdom
{

	struct Cheer : public GameObject
	{
	
		virtual ~Cheer()
		{
#ifdef BOOST_BIN
			OnDestructor( "Cheer" );
#endif
		}


		boost::shared_ptr<DrawPile> MyPile;

	
		boost::shared_ptr<QuadClass> Berry;
		Cheer();

		virtual void OnAdd();

	
		virtual void MyDraw();

		virtual void MyPhsxStep();

	
		void InitializeInstanceFields();
	};

}


#endif	//#ifndef CHEER
