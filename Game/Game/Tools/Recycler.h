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

		//std::shared_ptr<ObjectBase> operator []( ObjectType type, bool BoxesOnly );

		std::shared_ptr<ObjectBase> GetObject( ObjectType type, bool BoxesOnly );

		void CollectObject( const std::shared_ptr<ObjectBase> &obj );
		void CollectObject( const std::shared_ptr<ObjectBase> &obj, bool CollectAssociates );

		void Empty();
		void Empty( bool DoGC );
	};
}


#endif	//#ifndef RECYCLER
