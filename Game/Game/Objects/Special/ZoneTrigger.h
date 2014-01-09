#ifndef ZONETRIGGER
#define ZONETRIGGER

#include <small_header.h>

//#include "Game/Collision Detection/AABox.h"
//#include "Game/Collision Detection/Phsx.h"
#include "Game/Objects/ObjectBase.h"
//#include "Game/Objects/Bob/Bob.h"
//#include "Game/Tools/Recycler.h"


namespace CloudberryKingdom
{

	struct ZoneTrigger : public ObjectBase
	{

		virtual ~ZoneTrigger()
		{
#ifdef BOOST_BIN
			OnDestructor( "ZoneTrigger" );
#endif
		}

	
		boost::shared_ptr<Lambda_1<boost::shared_ptr<ZoneTrigger> > > MyContainsEvent;

	
		boost::shared_ptr<AABox> Box;

		virtual void Release();
	
		virtual void MakeNew();

		ZoneTrigger();

		void Init( Vector2 center, Vector2 size );

		void Update();

		virtual void Reset( bool BoxesOnly );

		virtual void Move( Vector2 shift );

		virtual void Interact( const boost::shared_ptr<Bob> &bob );


		virtual void Draw();

		virtual void Clone( const boost::shared_ptr<ObjectBase> &A );
	};

}


#endif	//#ifndef ZONETRIGGER
