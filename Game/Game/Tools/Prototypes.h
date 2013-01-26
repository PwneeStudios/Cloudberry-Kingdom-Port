#ifndef PROTOTYPES
#define PROTOTYPES

#include <global_header.h>

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
