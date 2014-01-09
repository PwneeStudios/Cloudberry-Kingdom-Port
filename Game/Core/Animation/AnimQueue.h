#ifndef ANIMQUEUE
#define ANIMQUEUE

#include <small_header.h>



namespace CloudberryKingdom
{
	struct AnimQueueEntry
	{
	
		AnimQueueEntryType Type;
		float AnimSpeed, StartT, EndT, DestT;
		bool Loop;
		int anim;

		bool Initialized;

		AnimQueueEntry();
		AnimQueueEntry( const boost::shared_ptr<AnimQueueEntry> &entry );

	};
}


#endif	//#ifndef ANIMQUEUE
