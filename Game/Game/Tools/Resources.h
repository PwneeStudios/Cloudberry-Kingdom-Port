#ifndef RESOURCES
#define RESOURCES

#include <global_header.h>

#include "Hacks/NET/Thread.h"

namespace CloudberryKingdom
{

	struct Resources
	{
		/// <summary>
		/// True when we are still loading resources during the game's initial load.
		/// This is wrapped in a struct so that it can be used as a lock.
		/// </summary>
		static boost::shared_ptr<WrappedBool> LoadingResources;

		/// <summary>
		/// Tracks how many resources have been loaded.
		/// This is wrapped in a struct so that it can be used as a lock.
		/// </summary>
		static boost::shared_ptr<WrappedFloat> ResourceLoadedCountRef;

		static boost::shared_ptr<EzFont> Font_Grobold42, Font_Grobold42_2;
		static boost::shared_ptr<EzFont> LilFont;

		static boost::shared_ptr<HackFont> hf;
		static boost::shared_ptr<Mutex> hf_Mutex;

		/// <summary>
		/// Load the necessary fonts.
		/// </summary>
	
		static void FontLoad();

		static void LoadInfo();

		static void LoadMusic( bool CreateNewWad );

		static void LoadSound( bool CreateNewWad );

	
		static void LoadAssets( bool CreateNewWads );

	
		static void PreloadArt();

	
		static void LoadResources();

		static boost::shared_ptr<Thread> LoadThread;
	
		static void _LoadThread();
	};

}


#endif	//#ifndef RESOURCES
