#include "AnimQueue.h"

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Text;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;
using namespace Microsoft::Xna::Framework;
using namespace Microsoft::Xna::Framework::Audio;
using namespace Microsoft::Xna::Framework::Content;
using namespace Microsoft::Xna::Framework::Graphics;
using namespace Microsoft::Xna::Framework::Input;
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
