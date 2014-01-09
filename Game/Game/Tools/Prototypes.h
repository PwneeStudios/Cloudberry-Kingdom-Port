#ifndef PROTOTYPES
#define PROTOTYPES

#include <small_header.h>

//#include "Core/Animation/AnimationData_Integer.h"
//#include "Core/Graphics/Draw/Object/ObjectClass.h"
//#include "Core/Graphics/Draw/Quads/BaseQuad.h"
//#include "Core/Graphics/Draw/Quads/Quad.h"
//#include "Core/Graphics/Draw/Simple/SimpleObject.h"
//#include "Core/Texture/EzTexture.h"
//#include "Game/Menus/Concrete Menus/Title Screen/Freeplay/CustomLevel_GUI.h"
//#include "Game/Menus/Concrete Menus/Title Screen/Arcade/ArcadeMenu.h"
//#include "Game/Player/Hero Physics/Base.h"
//#include "Game/Objects/Bob/Bob.h"
//#include "Game/Objects/In Game Objects/Obstacles/CloudberryKingdom.Fireball.h"
//#include "Game/Objects/In Game Objects/Obstacles/FlyingBlob.h"
//#include "Game/Objects/In Game Objects/Obstacles/Spike.h"
//#include "Game/Player/Hero Physics/Normal.h"
//#include "Game/Player/Hero Physics/Big.h"
//#include "Game/Player/Hero Physics/Bouncy.h"
//#include "Game/Player/Hero Physics/Box.h"
//#include "Game/Player/Hero Physics/Double.h"
//#include "Game/Player/Hero Physics/Invert.h"
//#include "Game/Player/Hero Physics/Jetman.h"
//#include "Game/Player/Hero Physics/Meat.h"
//#include "Game/Player/Hero Physics/Rocketbox.h"
//#include "Game/Player/Hero Physics/Scale.h"
//#include "Game/Player/Hero Physics/Small.h"
//#include "Game/Player/Hero Physics/Spaceship.h"
//#include "Game/Player/Hero Physics/Timeship.h"
//#include "Game/Player/Hero Physics/Time.h"
//#include "Game/Player/Hero Physics/Wheel.h"
//#include "Game/Tools/Globals.h"
//#include "Game/Tools/Recycler.h"
//#include "Game/Tools/Resources.h"
//#include "Game/Tools/Tools.h"


namespace CloudberryKingdom
{

	struct Prototypes
	{
	
		static boost::shared_ptr<ObjectClass> LoadAnimObj;
	
		static void LoadAnimation( const std::wstring &path );

	
		static void SetTigarLoaded( const boost::shared_ptr<ObjectClass> &obj );

		static boost::shared_ptr<ObjectClass> MakeObj();

	
		static boost::shared_ptr<FlyingBlob> FlyingBlobObj;
		static boost::shared_ptr<FlyingBlob> goomba;
		static std::map<boost::shared_ptr<BobPhsx>, boost::shared_ptr<Bob> > bob;
		static boost::shared_ptr<Spike> SpikeObj;
//C# TO C++ CONVERTER NOTE: The variable Door was renamed since it is named the same as a user-defined type:
		static boost::shared_ptr<SimpleObject> GhostBlockObj, CheckpointObj, Door_Renamed, GrassDoor, ArrowObj;

		static boost::shared_ptr<ObjectClass> Hero;

		static boost::shared_ptr<ObjectClass> PlaceBob;

		static boost::shared_ptr<SimpleObject> LoadSimple( const std::wstring &file );

		static boost::shared_ptr<ObjectClass> LoadObject( const std::wstring &file );

		static void LoadObjects();
	};

}


#endif	//#ifndef PROTOTYPES
