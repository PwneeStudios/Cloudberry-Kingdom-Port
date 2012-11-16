#ifndef EZSTORAGE
#define EZSTORAGE

#include <global_header.h>

namespace CloudberryKingdom
{
	class SaveLoad;
}

namespace CloudberryKingdom
{
	class PlayerData;
}

namespace CloudberryKingdom
{
	class WrappedInt;
}

namespace Microsoft
{
	namespace Xna
	{
		namespace Framework
		{
			namespace Storage
			{
				class StorageDevice;
			}
		}
	}
}

namespace CloudberryKingdom
{
	class WrappedBool;
}

namespace CloudberryKingdom
{
	class Lambda_1;
}

namespace CloudberryKingdom
{
	class Lambda;
}

namespace Microsoft
{
	namespace Xna
	{
		namespace Framework
		{
			namespace Storage
			{
				class StorageContainer;
			}
		}
	}
}


//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::IO;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Text;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Threading;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;
using namespace Microsoft::Xna::Framework::Storage;

namespace CloudberryKingdom
{
	class SaveGroup
	{
	private:
		static std::vector<SaveLoad*> ThingsToSave;

	public:
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

	private:
		static std::shared_ptr<WrappedInt> Count;
		static void Incr();
	public:
		static void Decr();
	};

	class SaveLoad
	{
	private:
		class SaveLambda : public Lambda_1<BinaryWriter*>
		{
		private:
			std::shared_ptr<SaveLoad> sl;
		public:
			SaveLambda( const std::shared_ptr<SaveLoad> &sl );

			void Apply( const std::shared_ptr<BinaryWriter> &writer );
		};

	private:
		class SaveFailLambda : public Lambda
		{
		private:
			std::shared_ptr<SaveLoad> sl;
		public:
			SaveFailLambda( const std::shared_ptr<SaveLoad> &sl );

			void Apply();
		};

	private:
		class LoadLambda : public Lambda_1<std::vector<unsigned char> >
		{
		private:
			std::shared_ptr<SaveLoad> sl;

		public:
			LoadLambda( const std::shared_ptr<SaveLoad> &sl );

			void Apply( std::vector<unsigned char> data );
		};

	private:
		class LoadFailLambda : public Lambda
		{
		private:
			std::shared_ptr<SaveLoad> sl;

		public:
			LoadFailLambda( const std::shared_ptr<SaveLoad> &sl );

			void Apply();
		};

	public:
		bool AlwaysSave;

		bool Changed;
		std::wstring ContainerName, FileName;

	private:
		const std::wstring &getActualContainerName() const;

	public:
		void Save();

		void Load();

	protected:
		virtual void Serialize( const std::shared_ptr<BinaryWriter> &writer );
		virtual void Deserialize( std::vector<unsigned char> Data );
		virtual void FailLoad();

	private:
		void InitializeInstanceFields();

public:
		SaveLoad()
		{
			InitializeInstanceFields();
		}
	};

	class EzStorage
	{
	private:
		static std::shared_ptr<StorageDevice> Device;
		static std::shared_ptr<WrappedBool> InUse;

	public:
		static bool DeviceOK();

		static void GetDevice();

		static void Save( const std::wstring &ContainerName, const std::wstring &FileName, const std::shared_ptr<Lambda_1<BinaryWriter*> > &SaveLogic, const std::shared_ptr<Lambda> &Fail );

	private:
		static void SaveToContainer( const std::shared_ptr<StorageContainer> &container, const std::wstring &FileName, const std::shared_ptr<Lambda_1<BinaryWriter*> > &SaveLogic );

	public:
		static void Load( const std::wstring &ContainerName, const std::wstring &FileName, const std::shared_ptr<Lambda_1<std::vector<unsigned char> > > &LoadLogic, const std::shared_ptr<Lambda> &Fail );

	private:
		static void LoadFromContainer( const std::shared_ptr<StorageContainer> &container, const std::wstring &FileName, const std::shared_ptr<Lambda_1<std::vector<unsigned char> > > &LoadLogic, const std::shared_ptr<Lambda> &FailLogic );
	};
}


#endif	//#ifndef EZSTORAGE
