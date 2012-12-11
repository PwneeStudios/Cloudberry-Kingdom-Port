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

	
		static std::vector<std::shared_ptr<SaveLoad> > ThingsToSave;

	
		static void Initialize();

		/// <summary>
		/// Wait until nothing is trying to be saved or loaded.
		/// </summary>
		static void Wait();

		/// <summary>
		/// Add an item to group. The item will be saved whenever the group is saved.
		/// </summary>
		static void Add( const std::shared_ptr<SaveLoad> &ThingToSave );

		/// <summary>
		/// Save every item that has been changed.
		/// </summary>
		static void SaveAll();

#if defined(NOT_PC)
		static std::shared_ptr<PlayerData> LoadGamer( const std::wstring &GamerName, const std::shared_ptr<PlayerData> &Data );
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

	
		static std::shared_ptr<WrappedInt> Count;
		static Mutex CountLock;

		static void Incr();
	
		static void Decr();
	};

	struct SaveLoad : public std::enable_shared_from_this<SaveLoad>
	{
	
		struct SaveLambda : public Lambda_1<std::shared_ptr<BinaryWriter> >
		{
		
			std::shared_ptr<SaveLoad> sl;
		
			SaveLambda( const std::shared_ptr<SaveLoad> &sl );

			void Apply( const std::shared_ptr<BinaryWriter> &writer );
		};

	
		struct SaveFailLambda : public Lambda
		{
		
			std::shared_ptr<SaveLoad> sl;
		
			SaveFailLambda( const std::shared_ptr<SaveLoad> &sl );

			void Apply();
		};

	
		struct LoadLambda : public Lambda_1<std::vector<unsigned char> >
		{
		
			std::shared_ptr<SaveLoad> sl;

		
			LoadLambda( const std::shared_ptr<SaveLoad> &sl );

			void Apply( const std::vector<unsigned char> &data );
		};

	
		struct LoadFailLambda : public Lambda
		{
		
			std::shared_ptr<SaveLoad> sl;

		
			LoadFailLambda( const std::shared_ptr<SaveLoad> &sl );

			void Apply();
		};

	
		bool AlwaysSave;

		bool Changed;
		std::wstring ContainerName, FileName;

	
		const std::wstring &getActualContainerName() const;

	
		void Save();

		void Load();

	
		virtual void Serialize( const std::shared_ptr<BinaryWriter> &writer );
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

	
		static std::shared_ptr<StorageDevice> Device;
		static std::shared_ptr<WrappedBool> InUse;
		static Mutex InUseLock;

	
		static bool DeviceOK();

		static void GetDevice();

		static void Save( const std::wstring &ContainerName, const std::wstring &FileName, const std::shared_ptr<Lambda_1<std::shared_ptr<BinaryWriter> > > &SaveLogic, const std::shared_ptr<Lambda> &Fail );

	
		static void SaveToContainer( const std::shared_ptr<StorageContainer> &container, const std::wstring &FileName, const std::shared_ptr<Lambda_1<BinaryWriter*> > &SaveLogic );

	
		static void Load( const std::wstring &ContainerName, const std::wstring &FileName, const std::shared_ptr<Lambda_1<std::vector<unsigned char> > > &LoadLogic, const std::shared_ptr<Lambda> &Fail );

	
		static void LoadFromContainer( const std::shared_ptr<StorageContainer> &container, const std::wstring &FileName, const std::shared_ptr<Lambda_1<std::vector<unsigned char> > > &LoadLogic, const std::shared_ptr<Lambda> &FailLogic );
	};
}


#endif	//#ifndef EZSTORAGE
