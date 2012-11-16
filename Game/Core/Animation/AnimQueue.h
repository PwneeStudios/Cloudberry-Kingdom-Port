#ifndef ANIMQUEUE
#define ANIMQUEUE

#include <global_header.h>






namespace CloudberryKingdom
{
	enum AnimQueueEntryType
	{
		AnimQueueEntryType_PLAY,
		AnimQueueEntryType_PLAY_UNTIL,
		AnimQueueEntryType_TRANSFER
	};
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
