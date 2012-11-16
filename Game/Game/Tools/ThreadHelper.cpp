#include <global_header.h>






namespace CloudberryKingdom
{

	std::shared_ptr<Thread> ThreadHelper::EasyThread( int affinity, const std::wstring &name, Action action )
	{
	#if defined(XBOX) && !defined(WINDOWS)
//C# TO C++ CONVERTER TODO TASK: Lambda expressions and anonymous methods are not converted to native C++ unless the option to convert to C++11 lambdas is selected:
		std::shared_ptr<Thread> NewThread = std::make_shared<Thread>(std::make_shared<ThreadStart>(delegate
		{
			const int tempVector[] = { affinity };
			Thread::CurrentThread->SetProcessorAffinity( std::vector<int>( tempVector, tempVector + sizeof( tempVector ) / sizeof( tempVector[ 0 ] ) ) );
			std::shared_ptr<System::Threading::Thread> ThisThread = Thread::CurrentThread;
//C# TO C++ CONVERTER TODO TASK: Lambda expressions and anonymous methods are not converted to native C++ unless the option to convert to C++11 lambdas is selected:
			EventHandler<EventArgs*> abort = ( s, e ) =>
			{
				if ( ThisThread != 0 )
				{
					ThisThread->Abort();
				}
			};
			Tools::TheGame->Exiting += abort;
			action();
			Tools::TheGame->Exiting -= abort;
		}
	   ))
	#else
//C# TO C++ CONVERTER TODO TASK: Lambda expressions and anonymous methods are not converted to native C++ unless the option to convert to C++11 lambdas is selected:
		std::shared_ptr<Thread> NewThread = std::make_shared<Thread>(std::make_shared<ThreadStart>(delegate
		{
			std::shared_ptr<System::Threading::Thread> ThisThread = Thread::CurrentThread;
//C# TO C++ CONVERTER TODO TASK: Lambda expressions and anonymous methods are not converted to native C++ unless the option to convert to C++11 lambdas is selected:
			EventHandler<EventArgs*> abort = ( s, e ) =>
			{
				if ( ThisThread != 0 )
				{
					ThisThread->Abort();
				}
			};
			Tools::TheGame->Exiting += abort;
			action();
			Tools::TheGame->Exiting -= abort;
		}
	   ))
	#endif


	   {
	#if defined(WINDOWS)
			//Priority = ThreadPriority.Highest,
			Name = name,Priority = ThreadPriority::Lowest,
	#else
			Name = name,
	#endif
	   };

		NewThread->Start();

		return NewThread;
	}
}
