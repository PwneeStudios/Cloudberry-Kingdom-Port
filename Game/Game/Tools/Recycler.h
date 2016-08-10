#ifndef RECYCLER
#define RECYCLER

#include <small_header.h>

//#include "Game/Objects/ObjectBase.h"
//#include "Game/Objects/Door/Door.h"
//#include "Game/Objects/In Game Objects/Blocks/BouncyBlock.h"
//#include "Game/Objects/In Game Objects/Blocks/Conveyor.h"
//#include "Game/Objects/In Game Objects/Blocks/FallingBlock.h"
//#include "Game/Objects/In Game Objects/Blocks/GhostBlock.h"
//#include "Game/Objects/In Game Objects/Blocks/Lava_Castle.h"
//#include "Game/Objects/In Game Objects/Blocks/MovingBlock.h"
//#include "Game/Objects/In Game Objects/Blocks/MovingPlatform.h"
//#include "Game/Objects/In Game Objects/Blocks/NormalBlock.h"
//#include "Game/Objects/In Game Objects/Blocks/Pendulum.h"
//#include "Game/Objects/In Game Objects/Grab/Checkpoint.h"
//#include "Game/Objects/In Game Objects/Grab/Coin.h"
//#include "Game/Objects/In Game Objects/Obstacles/BlockEmitter.h"
//#include "Game/Objects/In Game Objects/Obstacles/Boulder.h"
//#include "Game/Objects/In Game Objects/Obstacles/Cloud.h"
//#include "Game/Objects/In Game Objects/Obstacles/CloudberryKingdom.Fireball.h"
//#include "Game/Objects/In Game Objects/Obstacles/CloudberryKingdom.Firesnake.h"
//#include "Game/Objects/In Game Objects/Obstacles/FireSpinner.h"
//#include "Game/Objects/In Game Objects/Obstacles/FlyingBlob.h"
//#include "Game/Objects/In Game Objects/Obstacles/Laser.h"
//#include "Game/Objects/In Game Objects/Obstacles/LavaDrip.h"
//#include "Game/Objects/In Game Objects/Obstacles/Serpent.h"
//#include "Game/Objects/In Game Objects/Obstacles/Spike.h"
//#include "Game/Objects/In Game Objects/Obstacles/SpikeyGuy.h"
//#include "Game/Objects/In Game Objects/Obstacles/SpikeyLine.h"
//#include "Game/Objects/Special/CameraZone.h"
//#include "Game/Tools/Tools.h"


namespace CloudberryKingdom
{

	struct RecycleBin
	{
	
		ObjectType MyType;
		std::vector<boost::shared_ptr<ObjectBase> > FullObject, BoxObject;

	
		void Release();

		RecycleBin( ObjectType type );

		boost::shared_ptr<ObjectBase> GetObject( bool BoxesOnly );
	
		boost::shared_ptr<ObjectBase> GetObject_BoxesOnly();
		boost::shared_ptr<ObjectBase> GetObject_Graphical();
		boost::shared_ptr<ObjectBase> __GetObject( bool BoxesOnly );

	
		void CollectObject( const boost::shared_ptr<ObjectBase> &obj );

		boost::shared_ptr<ObjectBase> NewObject( bool BoxesOnly );
	};

	struct Recycler
	{

	
		static void InitializeStatics();

	
		static int MetaCount;
		static std::vector<boost::shared_ptr<Recycler> > MetaBin;
		static boost::shared_ptr<Mutex> MetaBinLock;
	
		static boost::shared_ptr<Recycler> GetRecycler();
		static void ReturnRecycler( const boost::shared_ptr<Recycler> &recycler );
		static void DumpMetaBin();

		//Dictionary<ObjectType, RecycleBin> Bins;
	
		std::vector<boost::shared_ptr<RecycleBin> > Bins;

	
		Recycler();

		void Init();

		boost::shared_ptr<ObjectBase> GetNewObject( ObjectType type, bool BoxesOnly );

		//boost::shared_ptr<ObjectBase> operator []( ObjectType type, bool BoxesOnly );

		boost::shared_ptr<ObjectBase> GetObject( ObjectType type, bool BoxesOnly );

		void CollectObject( const boost::shared_ptr<ObjectBase> &obj );
		void CollectObject( const boost::shared_ptr<ObjectBase> &obj, bool CollectAssociates );

		void Empty();
		void Empty( bool DoGC );
	};

}


#endif	//#ifndef RECYCLER
