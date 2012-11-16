#include <global_header.h>













namespace CloudberryKingdom
{

std::vector<SaveLoad*> SaveGroup::ThingsToSave = std::vector<SaveLoad*>();

	void SaveGroup::Initialize()
	{
		ScoreDatabase::Initialize();

		// Player data
		PlayerManager::SavePlayerData = std::make_shared<_SavePlayerData>();
		PlayerManager::SavePlayerData->ContainerName = _T( "PlayerData" );
		PlayerManager::SavePlayerData->FileName = _T( "PlayerData.hsc" );
		Add( PlayerManager::SavePlayerData );

	#if defined(PC_VERSION)
		PlayerManager::getPlayer()->ContainerName = _T("PlayerData");
		PlayerManager::getPlayer()->FileName = _T("MainPlayer");
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
//C# TO C++ CONVERTER TODO TASK: There is no built-in support for multithreading in native C++:
			lock ( Count )
			{
				if ( Count->MyInt == 0 )
					return;
			}

			delay( 1 );
		}
	}

	void SaveGroup::Add( const std::shared_ptr<SaveLoad> &ThingToSave )
	{
		ThingsToSave.push_back( ThingToSave );
	}

	void SaveGroup::SaveAll()
	{
		for ( std::vector<SaveLoad*>::const_iterator ThingToSave = ThingsToSave.begin(); ThingToSave != ThingsToSave.end(); ++ThingToSave )
		{
			//if (!(ThingToSave is ScoreList)) Tools.Write("!");

			Incr();
			( *ThingToSave )->Save();
			Wait();
		}

	#if defined(NOT_PC)
		// Save each player's info
		for ( std::vector<PlayerData*>::const_iterator player = PlayerManager::getLoggedInPlayers().begin(); player != PlayerManager::getLoggedInPlayers().end(); ++player )
		{
			Incr();
			( *player )->ContainerName = _T( "Gamers" );
			( *player )->FileName = _T( "___" ) + ( *player )->GetName();
			( *player )->Save();
			Wait();
		}
	#endif
	}

#if defined(NOT_PC)
	std::shared_ptr<PlayerData> SaveGroup::LoadGamer( const std::wstring &GamerName, const std::shared_ptr<PlayerData> &Data )
	{
		Data->ContainerName = _T( "Gamers" );
		Data->FileName = _T( "___" ) + GamerName;

		Incr();
		Data->Load();
		Wait();

		return Data;
	}
#endif

	void SaveGroup::LoadAll()
	{
		for ( std::vector<SaveLoad*>::const_iterator ThingToLoad = ThingsToSave.begin(); ThingToLoad != ThingsToSave.end(); ++ThingToLoad )
		{
			Incr();
			( *ThingToLoad )->Load();
			Wait();
		}
	}

std::shared_ptr<WrappedInt> SaveGroup::Count = std::make_shared<WrappedInt>( 0 );

	void SaveGroup::Incr()
	{
//C# TO C++ CONVERTER TODO TASK: There is no built-in support for multithreading in native C++:
		lock ( Count )
		{
			Count->MyInt++;
		}
	}

	void SaveGroup::Decr()
	{
//C# TO C++ CONVERTER TODO TASK: There is no built-in support for multithreading in native C++:
		lock ( Count )
		{
			Count->MyInt--;
		}
	}

	SaveLoad::SaveLambda::SaveLambda( const std::shared_ptr<SaveLoad> &sl )
	{
		this->sl = sl;
	}

	void SaveLoad::SaveLambda::Apply( const std::shared_ptr<BinaryWriter> &writer )
	{
		sl->Serialize( writer );
		sl->Changed = false;
		SaveGroup::Decr();
	}

	SaveLoad::SaveFailLambda::SaveFailLambda( const std::shared_ptr<SaveLoad> &sl )
	{
		this->sl = sl;
	}

	void SaveLoad::SaveFailLambda::Apply()
	{
		SaveGroup::Decr();
		sl->Changed = false;
	}

	SaveLoad::LoadLambda::LoadLambda( const std::shared_ptr<SaveLoad> &sl )
	{
		this->sl = sl;
	}

	void SaveLoad::LoadLambda::Apply( std::vector<unsigned char> data )
	{
		sl->Deserialize( data );
		sl->Changed = false;
		SaveGroup::Decr();
	}

	SaveLoad::LoadFailLambda::LoadFailLambda( const std::shared_ptr<SaveLoad> &sl )
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
		return ContainerName + _T( "_XboxVersion" );
	#else
		return ContainerName;
	#endif
	#endif
	}

	void SaveLoad::Save()
	{
		if ( Changed || AlwaysSave )
		{
			EzStorage::Save( getActualContainerName(), FileName, std::make_shared<SaveLambda>(this), std::make_shared<SaveFailLambda>(this) );
		}
		else
			SaveGroup::Decr();
	}

	void SaveLoad::Load()
	{
		EzStorage::Load( getActualContainerName(), FileName, std::make_shared<LoadLambda>(this), std::make_shared<LoadFailLambda>(this) );
	}

	void SaveLoad::Serialize( const std::shared_ptr<BinaryWriter> &writer )
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

std::shared_ptr<StorageDevice> EzStorage::Device = 0;
std::shared_ptr<WrappedBool> EzStorage::InUse = std::make_shared<WrappedBool>( false );

	bool EzStorage::DeviceOK()
	{
		return Device != 0 && Device->IsConnected;
	}

	void EzStorage::GetDevice()
	{
		std::shared_ptr<IAsyncResult> result = StorageDevice::BeginShowSelector( 0, 0 );
		result->AsyncWaitHandle->WaitOne();

		Device = StorageDevice::EndShowSelector( result );

		result->AsyncWaitHandle->Close();
	}

	void EzStorage::Save( const std::wstring &ContainerName, const std::wstring &FileName, const std::shared_ptr<Lambda_1<BinaryWriter*> > &SaveLogic, const std::shared_ptr<Lambda> &Fail )
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
			delay( 1 );
		}
		if ( InUse->MyBool )
		{
			if ( Fail != 0 )
				Fail->Apply();
				return;
		}

//C# TO C++ CONVERTER TODO TASK: There is no built-in support for multithreading in native C++:
		lock ( InUse )
		{
			InUse->MyBool = true;
		}

		// Device is hooked up and ready for us to save to

		// Open a container
//C# TO C++ CONVERTER TODO TASK: Lambda expressions and anonymous methods are not converted to native C++ unless the option to convert to C++11 lambdas is selected:
		std::shared_ptr<IAsyncResult> result = Device->BeginOpenContainer(ContainerName, ContainerResult =>
		{
			if ( !ContainerResult::IsCompleted )
			{
				if ( Fail != 0 )
					Fail->Apply();
					return;
			}
			std::shared_ptr<StorageContainer> container = Device->EndOpenContainer( ContainerResult );
			ContainerResult::AsyncWaitHandle->Close();
			if ( SaveLogic != 0 )
				SaveToContainer( container, FileName, SaveLogic );
		}
	   , 0);
	}

	void EzStorage::SaveToContainer( const std::shared_ptr<StorageContainer> &container, const std::wstring &FileName, const std::shared_ptr<Lambda_1<BinaryWriter*> > &SaveLogic )
	{
		// Check to see whether the save exists.
		if ( container->FileExists( FileName ) )
			// Delete it so that we can create one fresh.
			container->DeleteFile( FileName );

		// Create the file.
		std::shared_ptr<Stream> stream = container->CreateFile( FileName );

		// Save the data
		if ( SaveLogic != 0 )
		{
			std::shared_ptr<BinaryWriter> writer = std::make_shared<BinaryWriter>( stream, Encoding::UTF8 );
			SaveLogic->Apply( writer );
			writer->Close();
		}

		// Close the file.
		stream->Close();

		// Dispose the container, to commit changes.
		delete container;

//C# TO C++ CONVERTER TODO TASK: There is no built-in support for multithreading in native C++:
		lock ( InUse )
		{
			InUse->MyBool = false;
		}
	}

	void EzStorage::Load( const std::wstring &ContainerName, const std::wstring &FileName, const std::shared_ptr<Lambda_1<std::vector<unsigned char> > > &LoadLogic, const std::shared_ptr<Lambda> &Fail )
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
			delay( 1 );
		}
		if ( InUse->MyBool )
		{
			if ( Fail != 0 )
				Fail->Apply();
				return;
		}

//C# TO C++ CONVERTER TODO TASK: There is no built-in support for multithreading in native C++:
		lock ( InUse )
		{
			InUse->MyBool = true;
		}

		// Device is hooked up and ready for us to load from

		// Open a container
//C# TO C++ CONVERTER TODO TASK: Lambda expressions and anonymous methods are not converted to native C++ unless the option to convert to C++11 lambdas is selected:
		std::shared_ptr<IAsyncResult> result = Device->BeginOpenContainer(ContainerName, ContainerResult =>
				//if (Fail != null) Fail(); return;
		{
			if ( !ContainerResult::IsCompleted )
			{
				if ( Fail != 0 )
					Fail->Apply();
					return;
			}
			std::shared_ptr<StorageContainer> container = Device->EndOpenContainer( ContainerResult );
			ContainerResult::AsyncWaitHandle->Close();
			if ( LoadLogic != 0 )
				LoadFromContainer( container, FileName, LoadLogic, Fail );
		}
	   , 0);
	}

	void EzStorage::LoadFromContainer( const std::shared_ptr<StorageContainer> &container, const std::wstring &FileName, const std::shared_ptr<Lambda_1<std::vector<unsigned char> > > &LoadLogic, const std::shared_ptr<Lambda> &FailLogic )
	{
		// Fallback action if file doesn't exist
		if ( !container->FileExists( FileName ) )
		{
			delete container;

//C# TO C++ CONVERTER TODO TASK: There is no built-in support for multithreading in native C++:
			lock ( InUse )
			{
				InUse->MyBool = false;
			}

			if ( FailLogic != 0 )
				FailLogic->Apply();

			return;
		}

		// Load and process the data
		if ( LoadLogic != 0 )
		{
			try
			{
				std::shared_ptr<Stream> s = container->OpenFile( FileName, FileMode::Open );
				std::vector<unsigned char> Data = std::vector<unsigned char>( s->Length );
				s->Read( Data, 0, static_cast<int>( s->Length ) );

				LoadLogic->Apply( Data );
			}
			catch ( ... )
			{
				FailLogic->Apply();
			}
		}

		// Dispose the container, to commit changes.
		delete container;

//C# TO C++ CONVERTER TODO TASK: There is no built-in support for multithreading in native C++:
		lock ( InUse )
		{
			InUse->MyBool = false;
		}
	}
}
