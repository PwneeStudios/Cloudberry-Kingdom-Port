#include <global_header.h>

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;

namespace CloudberryKingdom
{

	void MainClass::Main( std::vector<std::wstring&> args )
	{
		CloudberryKingdomGame::ProcessArgs( args );

		AppDomain::CurrentDomain->UnhandledException += std::make_shared<UnhandledExceptionEventHandler>( &MainClass::CurrentDomain_UnhandledException );

	#if defined(DEBUG) && defined(WINDOWS)
		AppDomain::CurrentDomain->FirstChanceException += std::make_shared<EventHandler<System::Runtime::ExceptionServices::FirstChanceExceptionEventArgs*> >( &MainClass::CurrentDomain_FirstChanceException );
	#endif

	#if defined(GAME)
//C# TO C++ CONVERTER NOTE: The following 'using' block is replaced by its C++ equivalent:
//		using (XnaGameClass game = new XnaGameClass())
		std::shared_ptr<XnaGameClass> game = std::make_shared<XnaGameClass>();
		try
		{
	#else
//C# TO C++ CONVERTER NOTE: The following 'using' block is replaced by its C++ equivalent:
//		using (Game_Editor game = new Game_Editor())
		std::shared_ptr<Game_Editor> game = std::make_shared<Game_Editor>();
		try
		{
	#endif
			game->Run();
		}
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to the exception 'finally' clause:
		finally
		{
			if ( game != 0 )
				game.Dispose();
		}
		}

#if defined(DEBUG) && defined(WINDOWS)
	void MainClass::CurrentDomain_FirstChanceException( const std::shared_ptr<Object> &sender, const std::shared_ptr<System::Runtime::ExceptionServices::FirstChanceExceptionEventArgs> &e )
	{
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
		Tools::Log( e->Exception->ToString() );
	}
#endif

	void MainClass::CurrentDomain_UnhandledException( const std::shared_ptr<Object> &sender, const std::shared_ptr<UnhandledExceptionEventArgs> &e )
	{
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
		Tools::Log( e->ExceptionObject->ToString() );
	}
	}
