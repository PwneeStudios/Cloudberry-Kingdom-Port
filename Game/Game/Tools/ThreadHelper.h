#ifndef THREADHELPER
#define THREADHELPER

#include <string>

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Threading;

namespace CloudberryKingdom
{
	class ThreadHelper
	{
	public:
		static std::shared_ptr<Thread> EasyThread( int affinity, const std::wstring &name, Action action );
	};
}


#endif	//#ifndef THREADHELPER
