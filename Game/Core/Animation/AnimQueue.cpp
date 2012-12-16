#include <global_header.h>

namespace CloudberryKingdom
{

	AnimQueueEntry::AnimQueueEntry()
	{
		Type = static_cast<AnimQueueEntryType>( 0 );
		AnimSpeed = 0;
		StartT = 0;
		EndT = 0;
		DestT = 0;
		Loop = false;
		anim = 0;
		Initialized = false;
	}

	AnimQueueEntry::AnimQueueEntry( const boost::shared_ptr<AnimQueueEntry> &entry )
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
