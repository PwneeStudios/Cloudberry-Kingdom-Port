#ifndef RESOURCES
#define RESOURCES

#include <small_header.h>

//#include "Core/Animation/AnimationData_Integer.h"
//#include "Core/Graphics/QuadDrawer.h"
//#include "Core/Graphics/Draw/Quads/PieceQuad.h"
//#include "Core/Graphics/Draw/Quads/QuadClass.h"
//#include "Game/CloudberryKingdom/CloudberryKingdom.CloudberryKingdomGame.h"
//#include "Core/Particle Effects/Specific Effects/CloudberryKingdom.ParticleEffects.h"
//#include "Core/Song/EzSongWad.h"
//#include "Core/Sound/EzSound.h"
//#include "Core/Sound/EzSoundWad.h"
//#include "Core/Text/EzFont.h"
//#include "Core/Texture/EzTexture.h"
//#include "Game/Tilesets/TileSet.h"
//#include "Game/Games/ScreenSaver.h"
//#include "Game/Objects/Icon.h"
//#include "Game/Objects/In Game Objects/Obstacles/CloudberryKingdom.Fireball.h"
//#include "Game/Player/Awardments/Awardment.h"
//#include "Game/Tilesets/BlockGroup.h"
//#include "Game/Tools/Globals.h"
//#include "Game/Tools/Prototypes.h"
//#include "Game/Tools/Tools.h"
//#include "Game/Tools/WrappedFloat.h"
//#include "Game/Tilesets/TileSetInfo.h"


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

		/// The final flag to determine if loading resources is finished or not.
		static bool FinalLoadDone;

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
