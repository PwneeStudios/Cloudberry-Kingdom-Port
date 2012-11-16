#ifndef RESOURCES
#define RESOURCES

#include <global_header.h>

namespace CloudberryKingdom
{
	class WrappedBool;
}

namespace CloudberryKingdom
{
	class WrappedFloat;
}

namespace CloudberryKingdom
{
	class EzFont;
}


//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Reflection;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Threading;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::IO;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Text;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Linq;








namespace CloudberryKingdom
{
	class Resources
	{
		/// <summary>
		/// True when we are still loading resources during the game's initial load.
		/// This is wrapped in a class so that it can be used as a lock.
		/// </summary>
	public:
		static std::shared_ptr<WrappedBool> LoadingResources;

		/// <summary>
		/// Tracks how many resources have been loaded.
		/// This is wrapped in a class so that it can be used as a lock.
		/// </summary>
		static std::shared_ptr<WrappedFloat> ResourceLoadedCountRef;

		static std::shared_ptr<EzFont> Font_Grobold42, Font_Grobold42_2;
		static std::shared_ptr<EzFont> LilFont;

		/// <summary>
		/// Load the necessary fonts.
		/// </summary>
	private:
		static void FontLoad();

		static void LoadInfo();

		static void LoadMusic( bool CreateNewWad );

		static void LoadSound( bool CreateNewWad );

	public:
		static void LoadAssets( bool CreateNewWads );

	private:
		static void PreloadArt();

	public:
		static void LoadResources();

		static std::shared_ptr<Thread> LoadThread;
	private:
		static void _LoadThread();
	};
}


#endif	//#ifndef RESOURCES
