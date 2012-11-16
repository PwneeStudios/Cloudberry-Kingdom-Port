#include <global_header.h>















namespace CloudberryKingdom
{

	AnimQueueEntry::AnimQueueEntry()
	{
	}

	AnimQueueEntry::AnimQueueEntry( const std::shared_ptr<AnimQueueEntry> &entry )
	{
		Type = entry->Type;
		AnimSpeed = entry->AnimSpeed;
		StartT = entry->StartT;
		EndT = entry->EndT;
		DestT = entry->DestT;
		Loop = entry->Loop;
		anim = entry->anim;
		Initialized = entry->Initialized;
	}
}
