#include <global_header.h>

namespace CloudberryKingdom
{

	void SaveGroup::InitializeStatics()
	{
		SaveGroup::CountLock = boost::make_shared<Mutex>();
		SaveGroup::Count = boost::make_shared<WrappedInt>( 0 );
	}

	// Statics
	boost::shared_ptr<WrappedInt> SaveGroup::Count;
	boost::shared_ptr<Mutex> SaveGroup::CountLock;
	std::vector<boost::shared_ptr<SaveLoad> > SaveGroup::ThingsToSave;


	void EzStorage::InitializeStatics()
	{
		EzStorage::InUseLock = boost::make_shared<Mutex>();
		EzStorage::Device = 0;
		EzStorage::InUse = boost::make_shared<WrappedBool>( false );
	}

	// Statics
	boost::shared_ptr<Mutex> EzStorage::InUseLock;
	boost::shared_ptr<StorageDevice> EzStorage::Device;
	boost::shared_ptr<WrappedBool> EzStorage::InUse;


	void SaveGroup::Initialize()
	{
		ScoreDatabase::Initialize();

		// Player data
		PlayerManager::SavePlayerData = boost::make_shared<_SavePlayerData>();
		PlayerManager::SavePlayerData->ContainerName = std::wstring( L"PlayerData" );
		PlayerManager::SavePlayerData->FileName = std::wstring( L"PlayerData.hsc" );
		Add( PlayerManager::SavePlayerData );

	#if defined(PC_VERSION)
		PlayerManager::getPlayer()->ContainerName = std::wstring( L"PlayerData" );
		PlayerManager::getPlayer()->FileName = std::wstring( L"MainPlayer" );
		Add( PlayerManager::getPlayer() );
	#endif

		LoadAll();

		//PlayerManager.Player.LifetimeStats.Coins += 1000;
		//PlayerManager.Player.Awardments += 4;
		//PlayerManager.Player.Awardments += 7;
	}

	void SaveGroup::Wait()
	{
		while ( true )
		{
			//lock ( Count )
			{
				CountLock->Lock();

				if ( Count->MyInt == 0 )
				{
					CountLock->Unlock();
					return;
				}

				CountLock->Unlock();
			}

			Thread::Delay( 1 );
		}
	}

	void SaveGroup::Add( const boost::shared_ptr<SaveLoad> &ThingToSave )
	{
		ThingsToSave.push_back( ThingToSave );
	}

	void SaveGroup::SaveAll()
	{
		for ( std::vector<boost::shared_ptr<SaveLoad> >::const_iterator ThingToSave = ThingsToSave.begin(); ThingToSave != ThingsToSave.end(); ++ThingToSave )
		{
			//if (!(ThingToSave is ScoreList)) Tools.Write("!");

			Incr();
			( *ThingToSave )->Save();
			Wait();
		}

	#if defined(NOT_PC)
		// Save each player's info
		std::vector<boost::shared_ptr<PlayerData> > vec = PlayerManager::getLoggedInPlayers();
		for ( std::vector<boost::shared_ptr<PlayerData> >::const_iterator player = vec.begin(); player != vec.end(); ++player )
		{
			Incr();
			( *player )->ContainerName = std::wstring( L"Gamers" );
			( *player )->FileName = std::wstring( L"___" ) + ( *player )->GetName();
			( *player )->Save();
			Wait();
		}
	#endif
	}

#if defined(NOT_PC)
	boost::shared_ptr<PlayerData> SaveGroup::LoadGamer( const std::wstring &GamerName, const boost::shared_ptr<PlayerData> &Data )
	{
		Data->ContainerName = std::wstring( L"Gamers" );
		Data->FileName = std::wstring( L"___" ) + GamerName;

		Incr();
		Data->Load();
		Wait();

		return Data;
	}
#endif

	void SaveGroup::LoadAll()
	{
		for ( std::vector<boost::shared_ptr<SaveLoad> >::const_iterator ThingToLoad = ThingsToSave.begin(); ThingToLoad != ThingsToSave.end(); ++ThingToLoad )
		{
			Incr();
			( *ThingToLoad )->Load();
			Wait();
		}
	}

	void SaveGroup::Incr()
	{
//C# TO C++ CONVERTER TODO TASK: There is no built-in support for multithreading in native C++:
		//lock ( Count )
		{
			CountLock->Lock();

			Count->MyInt++;

			CountLock->Unlock();
		}
	}

	void SaveGroup::Decr()
	{
//C# TO C++ CONVERTER TODO TASK: There is no built-in support for multithreading in native C++:
		//lock ( Count )
		{
			CountLock->Lock();

			Count->MyInt--;

			CountLock->Unlock();
		}
	}

	SaveLoad::SaveLambda::SaveLambda( const boost::shared_ptr<SaveLoad> &sl )
	{
		this->sl = sl;
	}

	void SaveLoad::SaveLambda::Apply( const boost::shared_ptr<BinaryWriter> &writer )
	{
		sl->Serialize( writer );
		sl->Changed = false;
		SaveGroup::Decr();
	}

	SaveLoad::SaveFailLambda::SaveFailLambda( const boost::shared_ptr<SaveLoad> &sl )
	{
		this->sl = sl;
	}

	void SaveLoad::SaveFailLambda::Apply()
	{
		SaveGroup::Decr();
		sl->Changed = false;
	}

	SaveLoad::LoadLambda::LoadLambda( const boost::shared_ptr<SaveLoad> &sl )
	{
		this->sl = sl;
	}

	void SaveLoad::LoadLambda::Apply( const std::vector<unsigned char> &data )
	{
		sl->Deserialize( data );
		sl->Changed = false;
		SaveGroup::Decr();
	}

	SaveLoad::LoadFailLambda::LoadFailLambda( const boost::shared_ptr<SaveLoad> &sl )
	{
		this->sl = sl;
	}

	void SaveLoad::LoadFailLambda::Apply()
	{
		sl->FailLoad();
		SaveGroup::Decr();
		sl->Changed = false;
	}

	const std::wstring &SaveLoad::getActualContainerName() const
	{
	#if defined(PC_VERSION)
		return ContainerName;
	#else
	#if defined(WINDOWS)
		return ContainerName + std::wstring( L"_XboxVersion" );
	#else
		return ContainerName;
	#endif
	#endif
	}

	void SaveLoad::Save()
	{
		if ( Changed || AlwaysSave )
		{
			EzStorage::Save( getActualContainerName(), FileName, boost::make_shared<SaveLambda>( shared_from_this() ), boost::make_shared<SaveFailLambda>( shared_from_this() ) );
		}
		else
			SaveGroup::Decr();
	}

	void SaveLoad::Load()
	{
		EzStorage::Load( getActualContainerName(), FileName, boost::make_shared<LoadLambda>( shared_from_this() ), boost::make_shared<LoadFailLambda>( shared_from_this() ) );
	}

	void SaveLoad::Serialize( const boost::shared_ptr<BinaryWriter> &writer )
	{
	}

	void SaveLoad::Deserialize( std::vector<unsigned char> Data )
	{
	}

	void SaveLoad::FailLoad()
	{
	}

	void SaveLoad::InitializeInstanceFields()
	{
		AlwaysSave = false;
		Changed = false;
	}

	bool EzStorage::DeviceOK()
	{
		return Device != 0 && Device->IsConnected;
	}

	void EzStorage::GetDevice()
	{
		// FIXME: Implement this.
		/*boost::shared_ptr<IAsyncResult> result = StorageDevice::BeginShowSelector( 0, 0 );
		result->AsyncWaitHandle->WaitOne();

		Device = StorageDevice::EndShowSelector( result );

		result->AsyncWaitHandle->Close();*/
	}

	void EzStorage::Save( const std::wstring &ContainerName, const std::wstring &FileName, const boost::shared_ptr<Lambda_1<boost::shared_ptr<BinaryWriter> > > &SaveLogic, const boost::shared_ptr<Lambda> &Fail )
	{
		if ( !DeviceOK() )
			GetDevice();

		if ( !DeviceOK() )
		{
			if ( Fail != 0 )
				Fail->Apply();
			return;
		}

		// Check if we're already trying to use the device
		int count = 0;
		while ( InUse->MyBool && count++ < 100 )
		{
			Thread::Delay( 1 );
		}
		if ( InUse->MyBool )
		{
			if ( Fail != 0 )
				Fail->Apply();
				return;
		}

//C# TO C++ CONVERTER TODO TASK: There is no built-in support for multithreading in native C++:
		//lock ( InUse )
		{
			InUseLock->Lock();

			InUse->MyBool = true;

			InUseLock->Unlock();
		}

		// Device is hooked up and ready for us to save to

		// Open a container
		// FIXME: Implement this.
		/*boost::shared_ptr<IAsyncResult> result = Device->BeginOpenContainer(ContainerName, ContainerResult =>
		{
			if ( !ContainerResult::IsCompleted )
			{
				if ( Fail != 0 )
					Fail->Apply();
					return;
			}
			boost::shared_ptr<StorageContainer> container = Device->EndOpenContainer( ContainerResult );
			ContainerResult::AsyncWaitHandle->Close();
			if ( SaveLogic != 0 )
				SaveToContainer( container, FileName, SaveLogic );
		}
	   , 0);*/
	}

	void EzStorage::SaveToContainer( const boost::shared_ptr<StorageContainer> &container, const std::wstring &FileName, const boost::shared_ptr<Lambda_1<BinaryWriter*> > &SaveLogic )
	{
		// Check to see whether the save exists.
		if ( container->FileExists( FileName ) )
			// Delete it so that we can create one fresh.
			container->DeleteFile( FileName );

		// FIXME: Implement this.

		// Create the file.
		/*boost::shared_ptr<Stream> stream = container->CreateFile( FileName );

		// Save the data
		if ( SaveLogic != 0 )
		{
			boost::shared_ptr<BinaryWriter> writer = boost::make_shared<BinaryWriter>( stream, Encoding::UTF8 );
			SaveLogic->Apply( writer );
			writer->Close();
		}

		// Close the file.
		stream->Close();

		// Dispose the container, to commit changes.
		delete container;*/

//C# TO C++ CONVERTER TODO TASK: There is no built-in support for multithreading in native C++:
		//lock ( InUse )
		{
			InUseLock->Lock();

			InUse->MyBool = false;

			InUseLock->Unlock();
		}
	}

	void EzStorage::Load( const std::wstring &ContainerName, const std::wstring &FileName, const boost::shared_ptr<Lambda_1<std::vector<unsigned char> > > &LoadLogic, const boost::shared_ptr<Lambda> &Fail )
	{
		if ( !DeviceOK() )
			GetDevice();

		if ( !DeviceOK() )
		{
			if ( Fail != 0 )
				Fail->Apply();
			return;
		}

		// Check if we're already trying to use the device
		int count = 0;
		while ( InUse->MyBool && count++ < 100 )
		{
			Thread::Delay( 1 );
		}
		if ( InUse->MyBool )
		{
			if ( Fail != 0 )
				Fail->Apply();
				return;
		}

//C# TO C++ CONVERTER TODO TASK: There is no built-in support for multithreading in native C++:
		//lock ( InUse )
		{
			InUseLock->Lock();

			InUse->MyBool = true;

			InUseLock->Unlock();
		}

		// Device is hooked up and ready for us to load from

		// Open a container

		// FIXME: Implement this.
		/*boost::shared_ptr<IAsyncResult> result = Device->BeginOpenContainer(ContainerName, ContainerResult =>
				//if (Fail != null) Fail(); return;
		{
			if ( !ContainerResult::IsCompleted )
			{
				if ( Fail != 0 )
					Fail->Apply();
					return;
			}
			boost::shared_ptr<StorageContainer> container = Device->EndOpenContainer( ContainerResult );
			ContainerResult::AsyncWaitHandle->Close();
			if ( LoadLogic != 0 )
				LoadFromContainer( container, FileName, LoadLogic, Fail );
		}
	   , 0);*/
	}

	void EzStorage::LoadFromContainer( const boost::shared_ptr<StorageContainer> &container, const std::wstring &FileName, const boost::shared_ptr<Lambda_1<std::vector<unsigned char> > > &LoadLogic, const boost::shared_ptr<Lambda> &FailLogic )
	{
		// Fallback action if file doesn't exist
		if ( !container->FileExists( FileName ) )
		{
			// FIXME: Should never delete things.
			//delete container;

//C# TO C++ CONVERTER TODO TASK: There is no built-in support for multithreading in native C++:
			//lock ( InUse )
			{
				InUseLock->Lock();

				InUse->MyBool = false;

				InUseLock->Unlock();
			}

			if ( FailLogic != 0 )
				FailLogic->Apply();

			return;
		}

		// FIXME: Implement this.

		// Load and process the data
		/*if ( LoadLogic != 0 )
		{
			try
			{
				boost::shared_ptr<Stream> s = container->OpenFile( FileName, FileMode::Open );
				std::vector<unsigned char> Data = std::vector<unsigned char>( s->Length );
				s->Read( Data, 0, static_cast<int>( s->Length ) );

				LoadLogic->Apply( Data );
			}
			catch ( ... )
			{
				FailLogic->Apply();
			}
		}*/

		// Dispose the container, to commit changes.
		//delete container;

//C# TO C++ CONVERTER TODO TASK: There is no built-in support for multithreading in native C++:
		//lock ( InUse )
		{
			InUseLock->Lock();

			InUse->MyBool = false;

			InUseLock->Unlock();
		}
	}
}
