#ifndef RECYCLER
#define RECYCLER

#include <global_header.h>

namespace CloudberryKingdom
{
	class ObjectBase;
}


#define XBOX



namespace CloudberryKingdom
{
	enum ObjectType
	{
								ObjectType_UNDEFINED,
								ObjectType_COIN,
								ObjectType_CHECKPOINT,
								ObjectType_BERRY_BUBBLE,
								ObjectType_FLYING_BLOB,
								ObjectType_BLOCK_EMITTER,
								ObjectType_SPIKE,
								ObjectType_FIREBALL,
								ObjectType_FIRE_SPINNER,
								ObjectType_BOULDER,
								ObjectType_LASER,
								ObjectType_NORMAL_BLOCK,
								ObjectType_FALLING_BLOCK,
								ObjectType_LAVA_BLOCK,
								ObjectType_MOVING_PLATFORM,
								ObjectType_MOVING_BLOCK,
								ObjectType_GHOST_BLOCK,
								ObjectType_CLOUD,
								ObjectType_BOUNCY_BLOCK,
								ObjectType_SPIKEY_GUY,
								ObjectType_SPIKEY_LINE,
								ObjectType_PENDULUM,
								ObjectType_SERPENT,
								ObjectType_LAVA_DRIP,
								ObjectType_FIRESNAKE,
								ObjectType_CONVEYOR_BLOCK,
								ObjectType_DOOR,
								ObjectType_WALL,
								ObjectType_ZONE_TRIGGER,
								ObjectType_CAMERA_ZONE
	};

	class RecycleBin
	{
	private:
		ObjectType MyType;
		std::stack<ObjectBase*> FullObject, BoxObject;

	public:
		void Release();

		RecycleBin( ObjectType type );

		std::shared_ptr<ObjectBase> GetObject( bool BoxesOnly );
	private:
		std::shared_ptr<ObjectBase> GetObject_BoxesOnly();
		std::shared_ptr<ObjectBase> GetObject_Graphical();
		std::shared_ptr<ObjectBase> __GetObject( bool BoxesOnly );

	public:
		void CollectObject( const std::shared_ptr<ObjectBase> &obj );

		std::shared_ptr<ObjectBase> NewObject( bool BoxesOnly );
	};

	class Recycler
	{
	private:
		static int MetaCount;
		static std::stack<Recycler*> MetaBin;
	public:
		static std::shared_ptr<Recycler> GetRecycler();
		static void ReturnRecycler( const std::shared_ptr<Recycler> &recycler );
		static void DumpMetaBin();

		//Dictionary<ObjectType, RecycleBin> Bins;
	private:
		std::vector<RecycleBin*> Bins;

	public:
		Recycler();

		void Init();

		std::shared_ptr<ObjectBase> GetNewObject( ObjectType type, bool BoxesOnly );

		std::shared_ptr < ObjectBase *operator []( ObjectType type, bool BoxesOnly );

		std::shared_ptr<ObjectBase> GetObject( ObjectType type, bool BoxesOnly );

		void CollectObject( const std::shared_ptr<ObjectBase> &obj );
		void CollectObject( const std::shared_ptr<ObjectBase> &obj, bool CollectAssociates );

		void Empty();
		void Empty( bool DoGC );
	};
}


#endif	//#ifndef RECYCLER
