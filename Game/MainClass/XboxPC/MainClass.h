#ifndef MAINCLASS
#define MAINCLASS

#include <global_header.h>




namespace CloudberryKingdom
{
	class MainClass
	{
		/// <summary>
		/// The main entry point for the application.
		/// </summary>
#if defined(WINDOWS)
#if defined(PC)
#endif
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[STAThread]
#endif

		static void Main( std::vector<std::wstring&> args );

#if defined(DEBUG) && defined(WINDOWS)
	private:
		static void CurrentDomain_FirstChanceException( const std::shared_ptr<Object> &sender, const std::shared_ptr<System::Runtime::ExceptionServices::FirstChanceExceptionEventArgs> &e );
#endif

		static void CurrentDomain_UnhandledException( const std::shared_ptr<Object> &sender, const std::shared_ptr<UnhandledExceptionEventArgs> &e );
	};
}



#endif	//#ifndef MAINCLASS
