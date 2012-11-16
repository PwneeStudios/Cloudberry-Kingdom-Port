#ifndef ANIMQUEUE
#define ANIMQUEUE

#include "../Game/Objects/Game Objects/GameObjects/Listener.h"
#include "../Game/Tools/Oscillate.h"

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
