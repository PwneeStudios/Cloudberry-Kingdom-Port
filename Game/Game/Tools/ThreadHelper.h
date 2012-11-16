#ifndef THREADHELPER
#define THREADHELPER

#include <global_header.h>

namespace CloudberryKingdom
{
	class ThreadHelper
	{
	public:
		static std::shared_ptr<Thread> EasyThread( int affinity, const std::wstring &name, Action action );
	};
}


#endif	//#ifndef THREADHELPER
