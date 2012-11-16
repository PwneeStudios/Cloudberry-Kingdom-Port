#ifndef PROTOTYPES
#define PROTOTYPES

#include <global_header.h>

namespace CloudberryKingdom
{
	class ObjectClass;
}

namespace CloudberryKingdom
{
	class FlyingBlob;
}

namespace CloudberryKingdom
{
	class BobPhsx;
}

namespace CloudberryKingdom
{
	class Bob;
}

namespace CloudberryKingdom
{
	class Spike;
}

namespace CloudberryKingdom
{
	class SimpleObject;
}





namespace CloudberryKingdom
{
	class Prototypes
	{
	private:
		static std::shared_ptr<ObjectClass> LoadAnimObj;
	public:
		static void LoadAnimation( const std::wstring &path );

	private:
		static void SetTigarLoaded( const std::shared_ptr<ObjectClass> &obj );

		static std::shared_ptr<ObjectClass> MakeObj();

	public:
		static std::shared_ptr<FlyingBlob> FlyingBlobObj;
		static std::shared_ptr<FlyingBlob> goomba;
		static std::unordered_map<BobPhsx*, Bob*> bob;
		static std::shared_ptr<Spike> SpikeObj;
//C# TO C++ CONVERTER NOTE: The variable Door was renamed since it is named the same as a user-defined type:
		static std::shared_ptr<SimpleObject> GhostBlockObj, CheckpointObj, Door_Renamed, GrassDoor, ArrowObj;

		static std::shared_ptr<ObjectClass> Hero;

		static std::shared_ptr<ObjectClass> PlaceBob;

		static std::shared_ptr<SimpleObject> LoadSimple( const std::wstring &file );

		static std::shared_ptr<ObjectClass> LoadObject( const std::wstring &file );

		static void LoadObjects();
	};
}


#endif	//#ifndef PROTOTYPES
