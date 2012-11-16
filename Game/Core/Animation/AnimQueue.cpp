#include <global_header.h>

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Text;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;





//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::IO;

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
