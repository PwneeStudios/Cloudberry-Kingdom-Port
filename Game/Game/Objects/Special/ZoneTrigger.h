#ifndef ZONETRIGGER
#define ZONETRIGGER

#include <global_header.h>

namespace CloudberryKingdom
{
	struct ZoneTrigger : public ObjectBase
	{
	
		boost::shared_ptr<Lambda_1<boost::shared_ptr<ZoneTrigger> > > MyContainsEvent;

	
		boost::shared_ptr<AABox> Box;

	
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
