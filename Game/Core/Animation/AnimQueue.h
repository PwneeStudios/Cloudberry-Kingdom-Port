#ifndef ANIMQUEUE
#define ANIMQUEUE

#include <global_header.h>

namespace CloudberryKingdom
{
	class AnimQueueEntry
	{
	public:
		AnimQueueEntryType Type;
		float AnimSpeed, StartT, EndT, DestT;
		bool Loop;
		int anim;

		bool Initialized;

		AnimQueueEntry();
		AnimQueueEntry( const std::shared_ptr<AnimQueueEntry> &entry );
	};
}


#endif	//#ifndef ANIMQUEUE
