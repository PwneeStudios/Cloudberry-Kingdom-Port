#ifndef EZSTORAGE
#define EZSTORAGE

#include <global_header.h>

#include "Hacks/NET/TimeSpan.h"

#include "Hacks/XNA/StorageDevice.h"
#include "Hacks/XNA/StorageContainer.h"

namespace CloudberryKingdom
{
	struct SaveGroup
	{

	
		static void InitializeStatics();

	
		static std::vector<boost::shared_ptr<SaveLoad> > ThingsToSave;

	
		static void Initialize();

		/// <summary>
		/// Wait until nothing is trying to be saved or loaded.
		/// </summary>
		static void Wait();

		/// <summary>
		/// Add an item to group. The item will be saved whenever the group is saved.
		/// </summary>
		static void Add( const boost::shared_ptr<SaveLoad> &ThingToSave );

		/// <summary>
		/// Save every item that has been changed.
		/// </summary>
		static void SaveAll();

#if defined(NOT_PC)
		static boost::shared_ptr<PlayerData> LoadGamer( const std::wstring &GamerName, const boost::shared_ptr<PlayerData> &Data );
#endif

		//public static void LoadRes()
		//{
		//    Incr();
		//    PlayerManager.SavePlayerData = new _SavePlayerData();
		//    PlayerManager.SavePlayerData.Load();
		//    Wait();
		//}

		/// <summary>
		/// Load every item.
		/// </summary>
		static void LoadAll();

	
		static boost::shared_ptr<WrappedInt> Count;
		static boost::shared_ptr<Mutex> CountLock;

		static void Incr();
	
		static void Decr();
	};

	struct SaveLoad : public boost::enable_shared_from_this<SaveLoad>
	{
	
		struct SaveLambda : public Lambda_1<boost::shared_ptr<BinaryWriter> >
		{
		
			boost::shared_ptr<SaveLoad> sl;
		
			SaveLambda( const boost::shared_ptr<SaveLoad> &sl );

			void Apply( const boost::shared_ptr<BinaryWriter> &writer );
		};

	
		struct SaveFailLambda : public Lambda
		{
		
			boost::shared_ptr<SaveLoad> sl;
		
			SaveFailLambda( const boost::shared_ptr<SaveLoad> &sl );

			void Apply();
		};

	
		struct LoadLambda : public Lambda_1<std::vector<unsigned char> >
		{
		
			boost::shared_ptr<SaveLoad> sl;

		
			LoadLambda( const boost::shared_ptr<SaveLoad> &sl );

			void Apply( const std::vector<unsigned char> &data );
		};

	
		struct LoadFailLambda : public Lambda
		{
		
			boost::shared_ptr<SaveLoad> sl;

		
			LoadFailLambda( const boost::shared_ptr<SaveLoad> &sl );

			void Apply();
		};

	
		bool AlwaysSave;

		bool Changed;
		std::wstring ContainerName, FileName;

	
		const std::wstring &getActualContainerName() const;

	
		void Save();

		void Load();

	
		virtual void Serialize( const boost::shared_ptr<BinaryWriter> &writer );
		virtual void Deserialize( std::vector<unsigned char> Data );
		virtual void FailLoad();

	
		void InitializeInstanceFields();


		SaveLoad()
		{
			InitializeInstanceFields();
		}
	};

	struct EzStorage
	{

	
		static void InitializeStatics();

	
		static boost::shared_ptr<StorageDevice> Device;
		static boost::shared_ptr<WrappedBool> InUse;
		static boost::shared_ptr<Mutex> InUseLock;

	
		static bool DeviceOK();

		static void GetDevice();

		static void Save( const std::wstring &ContainerName, const std::wstring &FileName, const boost::shared_ptr<Lambda_1<boost::shared_ptr<BinaryWriter> > > &SaveLogic, const boost::shared_ptr<Lambda> &Fail );

	
		static void SaveToContainer( const boost::shared_ptr<StorageContainer> &container, const std::wstring &FileName, const boost::shared_ptr<Lambda_1<BinaryWriter*> > &SaveLogic );

	
		static void Load( const std::wstring &ContainerName, const std::wstring &FileName, const boost::shared_ptr<Lambda_1<std::vector<unsigned char> > > &LoadLogic, const boost::shared_ptr<Lambda> &Fail );

	
		static void LoadFromContainer( const boost::shared_ptr<StorageContainer> &container, const std::wstring &FileName, const boost::shared_ptr<Lambda_1<std::vector<unsigned char> > > &LoadLogic, const boost::shared_ptr<Lambda> &FailLogic );
	};
}


#endif	//#ifndef EZSTORAGE
