#ifndef RECYCLER
#define RECYCLER

#include <global_header.h>

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
		static Mutex MetaBinLock;
	
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
