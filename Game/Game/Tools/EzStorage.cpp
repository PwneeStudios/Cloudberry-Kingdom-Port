#include <global_header.h>

#include <Game/CloudberryKingdom/CloudberryKingdom.CloudberryKingdomGame.h>
#include <Utility/Error.h>
#include <Hacks/String.h>

#ifdef PS3
#include <stdio.h>
#include <stdlib.h>
#include <vector>

#include <sys/ppu_thread.h>
#include <sysutil/sysutil_savedata.h>
#include <np.h>

#define SCEA

#ifdef SCEA
#define AUTOSAVEDATA_DIRNAME "NPUB31177-AUTO-"
#endif

#define AUTOSAVE_FILENAME "SYS-DATA"
#define AUTOSAVE_PARAMSFO_TITLE "Cloudberry Kingdom Save File"
#define AUTOSAVE_PARAMSFO_DETAIL "Progress through Cloudberry Kingdom."

#define AUTOSAVE_SIZE (10 * 1024)
enum {
	FILE_INDEX_MUSTEXIST = 0,
	FILE_INDEX_END
};

static void *_file_buffer = NULL;
static bool _save_done = false;
static bool _load_done = false;

const char secureFileId[ CELL_SAVEDATA_SECUREFILEID_SIZE ] = {
	0x1, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7, 0x8, 0x9, 0xa, 0xb, 0xc, 0xd, 0xe, 0xf, 0xff
};

extern bool ForceGetTrophyContext( SceNpTrophyContext &context, SceNpTrophyHandle &handle );

#endif

#if defined( CAFE ) || defined( PS3 )
#include <Utility/Save.h>

static unsigned int Checksum(const unsigned char *buffer, int length)
{
	int val = 0;
	for( int i = 0; i < length; i++ )
	{
		val += ( ( int )buffer[ i ] + 13 ) * ( i + 10 );
	}

	return val;
}

#endif

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

		// FIXME: This is called later after everything is loaded.
		//LoadAll();

		//PlayerManager::Player.LifetimeStats.Coins += 1000;
		//PlayerManager::Player.Awardments += 4;
		//PlayerManager::Player.Awardments += 7;
	}

	void SaveGroup::Wait()
	{
		// FIXME: This should be used when loading/saving is asynchronous.
		/*while ( true )
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
		}*/
	}

	void SaveGroup::Add( const boost::shared_ptr<SaveLoad> &ThingToSave )
	{
		ThingsToSave.push_back( ThingToSave );
	}

	void SaveGroup::SaveAll()
	{
#if PC_VERSION
		// FIXME: save/load on PC version
		return;
#endif

		if ( !CloudberryKingdomGame::CanSave() ) return;

		for ( std::vector<boost::shared_ptr<SaveLoad> >::const_iterator ThingToSave = ThingsToSave.begin(); ThingToSave != ThingsToSave.end(); ++ThingToSave )
		{
			//if (!(ThingToSave is ScoreList)) Tools::Write("!");

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
#if PC_VERSION
		// FIXME: save/load on PC version
		return;
#else
		if( !InitializeSave() )
			return;
#endif

		for ( std::vector<boost::shared_ptr<SaveLoad> >::const_iterator ThingToLoad = ThingsToSave.begin(); ThingToLoad != ThingsToSave.end(); ++ThingToLoad )
		{
			Incr();
			( *ThingToLoad )->Load();
			Wait();
		}

		PlayerManager::Players[ 0 ]->Load();
	}

	void SaveGroup::Incr()
	{
//C# TO C++ CONVERTER TODO TASK: There is no built-in support for multithreading in native C++:
		//lock ( Count )
		/*{
			CountLock->Lock();

			Count->MyInt++;

			CountLock->Unlock();
		}*/
	}

	void SaveGroup::Decr()
	{
//C# TO C++ CONVERTER TODO TASK: There is no built-in support for multithreading in native C++:
		//lock ( Count )
		/*{
			CountLock->Lock();

			Count->MyInt--;

			CountLock->Unlock();
		}*/
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

#ifdef PS3
	struct SaveToContainerArgs
	{
		boost::shared_ptr<StorageContainer> Container;
		std::wstring FileName;
		boost::shared_ptr<Lambda_1<boost::shared_ptr< BinaryWriter > > > SaveLogic;
		boost::shared_ptr<Lambda> Fail;
	};

	void SaveToContainerThread( uint64_t context )
	{
		SaveToContainerArgs *args = reinterpret_cast< SaveToContainerArgs * >( context );

		EzStorage::SaveToContainer( args->Container, args->FileName, args->SaveLogic, args->Fail );

		delete args;

		sys_ppu_thread_exit( 0 );
	}
#endif

	void EzStorage::Save( const std::wstring &ContainerName, const std::wstring &FileName, const boost::shared_ptr<Lambda_1<boost::shared_ptr<BinaryWriter> > > &SaveLogic, const boost::shared_ptr<Lambda> &Fail )
	{
		printf( "Save( ContainerName = %s, FileName = %s );\n", WstringToUtf8( ContainerName ).c_str(), WstringToUtf8( FileName ).c_str() );
		
		/*if ( !DeviceOK() )
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
		}*/


		boost::shared_ptr< StorageContainer > container = boost::make_shared< StorageContainer >();

#if defined( PS3 )
		int ret;
		sys_ppu_thread_t tid;

		SaveToContainerArgs *args = new SaveToContainerArgs;
		args->Container = container;
		args->FileName = FileName;
		args->SaveLogic = SaveLogic;
		args->Fail = Fail;

		ret = sys_ppu_thread_create( &tid, SaveToContainerThread, reinterpret_cast< uint64_t >( args ), 1001, 16 * 1024, 0, "SaveToContainerThread" );

		if( ret != 0 )
			Fail->Apply();
#else
		SaveToContainer( container, FileName, SaveLogic, Fail );
#endif

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

#ifdef PS3
	void CallbackDataStatusSave( CellSaveDataCBResult *result, CellSaveDataStatGet *get, CellSaveDataStatSet *set )
	{
		set->reCreateMode = CELL_SAVEDATA_RECREATE_NO;
		set->setParam = &get->getParam;
		set->indicator = NULL;

		if( get->isNewData )
		{
			printf( "Save data %s does NOT exists.\n", get->dir.dirName );

			int sizeKb = get->sysSizeKB + AUTOSAVE_SIZE / 1024;
			int neededKb = get->hddFreeSizeKB - sizeKb;

			printf( "hddFreeSizeKB = %d, sizeKb = %d, neededKb = %d\n", get->hddFreeSizeKB, sizeKb, neededKb );
			if( neededKb < 0 )
			{
				printf( "Not enough space to save! Need %d more KB.\n", -neededKb );

				std::wstring error = Format( Localization::WordString( Localization::Words_Err_PS3_NotEnoughSpace ).c_str(), -neededKb );
				DisplayError( ErrorType( WstringToUtf8( error ), NULL, ErrorType::NONE, NULL, true ) );

				result->errNeedSizeKB = neededKb;
				result->result = CELL_SAVEDATA_CBRESULT_ERR_NOSPACE;
				return;
			}

			memset( set->setParam->title, 0, CELL_SAVEDATA_SYSP_TITLE_SIZE );
			strncpy( set->setParam->title, AUTOSAVE_PARAMSFO_TITLE, CELL_SAVEDATA_SYSP_TITLE_SIZE );

			memset( set->setParam->subTitle, 0, CELL_SAVEDATA_SYSP_SUBTITLE_SIZE );
			strncpy( set->setParam->subTitle, AUTOSAVE_PARAMSFO_DETAIL, CELL_SAVEDATA_SYSP_SUBTITLE_SIZE );

			memset( set->setParam->reserved, 0, sizeof( set->setParam->reserved ) );
			memset( set->setParam->reserved2, 0, sizeof( set->setParam->reserved2 ) );
		}

		result->result = CELL_SAVEDATA_CBRESULT_OK_NEXT;
	}

	void CallbackFileOperationSave( CellSaveDataCBResult *result, CellSaveDataFileGet *get, CellSaveDataFileSet *set )
	{
		result->result = _save_done ? CELL_SAVEDATA_CBRESULT_OK_LAST : CELL_SAVEDATA_CBRESULT_OK_NEXT;

		if( _save_done )
			return;

		set->fileOperation = CELL_SAVEDATA_FILEOP_WRITE;
		set->fileBuf = _file_buffer;
		set->fileBufSize = AUTOSAVE_SIZE;
		set->fileName = AUTOSAVE_FILENAME;
		set->fileSize = AUTOSAVE_SIZE;
		set->fileOffset = 0;

		set->fileType = CELL_SAVEDATA_FILETYPE_SECUREFILE;
		memcpy( set->secureFileId, secureFileId, CELL_SAVEDATA_SECUREFILEID_SIZE );
		set->reserved = NULL;

		_save_done = true;
	}
#endif

	void EzStorage::SaveToContainer( const boost::shared_ptr<StorageContainer> &container, const std::wstring &FileName, const boost::shared_ptr<Lambda_1<boost::shared_ptr< BinaryWriter > > > &SaveLogic, const boost::shared_ptr<Lambda> &Fail )
	{
		std::string path = WstringToUtf8( FileName );
		printf( "Save( FileName = %s );\n", path.c_str() );

		// Check to see whether the save exists.
		/*if ( container->FileExists( FileName ) )
			// Delete it so that we can create one fresh.
			container->DeleteFile( FileName );*/

#ifdef PS3

		if( FileName == L"HighScores" || FileName == L"PlayerData.hsc" )
		{
			if( Fail )
				Fail->Apply();
			return;
		}

		// FIXME: Allow more than one save operation in flight.
		static bool saveInFlight = false;
		
		if( saveInFlight )
			return;

		saveInFlight = true;
		_save_done = false;

		path = "SaveData.bam";

		char dirName[ CELL_SAVEDATA_DIRNAME_SIZE + 1 ];
		
		strncpy( dirName, AUTOSAVEDATA_DIRNAME, CELL_SAVEDATA_DIRNAME_SIZE );
		dirName[ CELL_SAVEDATA_DIRNAME_SIZE ] = 0;

		CellSaveDataSetBuf setBuf;
		setBuf.dirListMax = 0;
		setBuf.fileListMax = FILE_INDEX_END;
		memset( setBuf.reserved, 0, sizeof( setBuf.reserved ) );
		setBuf.bufSize = sizeof( CellSaveDataFileStat );
		setBuf.buf = malloc( setBuf.bufSize );

		assert( setBuf.buf );

		boost::shared_ptr< MemoryBinaryWriter > writer = boost::make_shared< MemoryBinaryWriter >( 64 * 1024 );
		SaveLogic->Apply( writer );

		_file_buffer = malloc( AUTOSAVE_SIZE );

		assert( _file_buffer );

		const std::vector< unsigned char > &saveData = writer->GetBuffer();
		memset( _file_buffer, 0, AUTOSAVE_SIZE );
		unsigned int bufferLength = saveData.size();

		// The first 4 bytes are the length of the buffer.
		memcpy( _file_buffer, &bufferLength, sizeof( unsigned int ) );

		// FIXME: Write checksum here.
		unsigned int checksum = Checksum( &saveData[ 0 ], bufferLength );
		memcpy( reinterpret_cast< char * >( _file_buffer ) + sizeof( unsigned int ), &checksum, sizeof( unsigned int ) );

		// Write the rest of the save data.
		memcpy( reinterpret_cast< char * >( _file_buffer ) + 2 * sizeof( unsigned int ), &saveData[ 0 ], saveData.size() );

		int ret = cellSaveDataAutoSave2(
			CELL_SAVEDATA_VERSION_420,
			dirName,
			CELL_SAVEDATA_ERRDIALOG_ALWAYS,
			&setBuf,
			CallbackDataStatusSave,
			CallbackFileOperationSave,
			SYS_MEMORY_CONTAINER_ID_INVALID,
			NULL
		);

		if( _file_buffer )
		{
			free( _file_buffer );
			_file_buffer = NULL;
		}

		saveInFlight = false;
#endif

#ifdef CAFE
		if( SaveLogic != 0 )
		{
			bool global = false;

			if( FileName == L"HighScores" )
			{
				global = true;
			}
			else if( FileName == L"PlayerData.hsc" )
			{
				global = false;
			}
			else
			{
				path = "PlayerProgress";
				global = false;
			}

			boost::shared_ptr< SaveWriterWiiU > writer = boost::make_shared< SaveWriterWiiU >( path, global );

			if( !writer->IsOpen() )
			{
				if( Fail != 0 )
					Fail->Apply();
			}
			else
				SaveLogic->Apply( writer );
			
			//writer->Close();

		}
#endif

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
		/*{
			InUseLock->Lock();

			InUse->MyBool = false;

			InUseLock->Unlock();
		}*/
	}

#ifdef PS3
	struct LoadFromContainerArgs
	{
		boost::shared_ptr< StorageContainer > Container;
		std::wstring FileName;
		boost::shared_ptr<Lambda_1<std::vector<unsigned char> > > LoadLogic;
		boost::shared_ptr<Lambda> Fail;
	};

	void LoadFromContainerThread( uint64_t context )
	{
		LoadFromContainerArgs *args = reinterpret_cast< LoadFromContainerArgs * >( context );

		EzStorage::LoadFromContainer( args->Container, args->FileName, args->LoadLogic, args->Fail );

		delete args;

		sys_ppu_thread_exit( 0 );
	}
#endif

	void EzStorage::Load( const std::wstring &ContainerName, const std::wstring &FileName, const boost::shared_ptr<Lambda_1<std::vector<unsigned char> > > &LoadLogic, const boost::shared_ptr<Lambda> &Fail )
	{
		printf( "Load( ContainerName = %s, FileName = %s );\n", WstringToUtf8( ContainerName ).c_str(), WstringToUtf8( FileName ).c_str() );
		
		/*if ( !DeviceOK() )
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
		}*/

		boost::shared_ptr< StorageContainer > container = boost::make_shared< StorageContainer >();

#if defined( PS3 )
		int ret;
		sys_ppu_thread_t tid;

		LoadFromContainerArgs *args = new LoadFromContainerArgs;
		args->Container = container;
		args->FileName = FileName;
		args->LoadLogic = LoadLogic;
		args->Fail = Fail;

		ret = sys_ppu_thread_create( &tid, LoadFromContainerThread, reinterpret_cast< uint64_t >( args ), 1001, 16 * 1024, 0, "LoadFromContainerThread" );

		if( ret != 0 )
			Fail->Apply();
#else
		LoadFromContainer( container, FileName, LoadLogic, Fail );
#endif
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

#ifdef PS3
	uint64_t RequiredTrophySpace = 0;

	void CallbackDataStatusLoad( CellSaveDataCBResult *result, CellSaveDataStatGet *get, CellSaveDataStatSet *set )
	{
		// Check if there is any data to load.
		if( get->isNewData || RequiredTrophySpace > 0 )
		{
			printf( "NO SAVE DATA FOUND!\n" );

			int sizeKb = get->sysSizeKB;
			if( get->isNewData )
				sizeKb += AUTOSAVE_SIZE / 1024;
			if( RequiredTrophySpace > 0 )
				sizeKb += static_cast< int >( RequiredTrophySpace / 1024 );

			int neededKb = get->hddFreeSizeKB - sizeKb;

			printf( "hddFreeSizeKB = %d, sizeKb = %d, neededKb = %d\n", get->hddFreeSizeKB, sizeKb, neededKb );
			if( neededKb < 0 )
			{
				printf( "Not enough space to save! Need %d more KB.\n", -neededKb );

				std::wstring error = Format( Localization::WordString( Localization::Words_Err_PS3_NotEnoughSpace ).c_str(), -neededKb );
				DisplayError( ErrorType( WstringToUtf8( error ), NULL, ErrorType::NONE, NULL, true ) );

				result->errNeedSizeKB = -neededKb;
				result->result = CELL_SAVEDATA_CBRESULT_ERR_NOSPACE;
				return;
			}

			result->result = CELL_SAVEDATA_CBRESULT_ERR_NODATA;
			return;
		}

		// There is some data!
		if( get->fileListNum < get->fileNum )
		{
			printf( "MORE FILES THAN EXPECTED!\n" );
			DisplayError( ErrorType( WstringToUtf8( Localization::WordString( Localization::Words_Err_PS3_CorruptLoad ) ) ) );
			result->result = CELL_SAVEDATA_CBRESULT_ERR_BROKEN;
			return;
		}

		bool foundAutosave = false;
		for( unsigned int i = 0; i < get->fileListNum; ++i )
		{
			if( strcmp( get->fileList[ i ].fileName, AUTOSAVE_FILENAME ) == 0 )
			{
				if( get->fileList[ i ].st_size != AUTOSAVE_SIZE )
				{
					printf( "Save file is of the wrong size! Expected %d but got %d.\n", AUTOSAVE_SIZE, get->fileList[ i ].st_size );
					DisplayError( ErrorType( WstringToUtf8( Localization::WordString( Localization::Words_Err_PS3_CorruptLoad ) ) ) );
					result->result = CELL_SAVEDATA_CBRESULT_ERR_BROKEN;
					return;
				}

				foundAutosave = true;
			}
		}

		if( !foundAutosave )
		{
			printf( "Save file %s missing!\n", AUTOSAVE_FILENAME );
			DisplayError( ErrorType( WstringToUtf8( Localization::WordString( Localization::Words_Err_PS3_CorruptLoad ) ) ) );
			result->result = CELL_SAVEDATA_CBRESULT_ERR_BROKEN;
			return;
		}

		set->reCreateMode = CELL_SAVEDATA_RECREATE_NO_NOBROKEN;
		set->setParam = NULL;
		set->indicator = NULL;

		result->result = CELL_SAVEDATA_CBRESULT_OK_NEXT;
		result->userdata = NULL;
		printf( "CallbackDataStatusLoad end.\n" );
	}

	void CallbackFileOperationLoad( CellSaveDataCBResult *result, CellSaveDataFileGet *get, CellSaveDataFileSet *set )
	{
		result->result = _load_done ? CELL_SAVEDATA_CBRESULT_OK_LAST : CELL_SAVEDATA_CBRESULT_OK_NEXT;

		if( _load_done )
			return;

		if( _file_buffer )
			free( _file_buffer );

		_file_buffer = malloc( AUTOSAVE_SIZE );

		set->fileOperation = CELL_SAVEDATA_FILEOP_READ;
		set->fileBuf = _file_buffer;
		set->fileBufSize = AUTOSAVE_SIZE;
		set->fileOffset = 0;
		set->fileName = AUTOSAVE_FILENAME;
		set->fileSize = AUTOSAVE_SIZE;
		set->fileType = CELL_SAVEDATA_FILETYPE_SECUREFILE;
		memcpy( set->secureFileId, secureFileId, CELL_SAVEDATA_SECUREFILEID_SIZE );
		set->reserved = NULL;

		_load_done = true;
	}
#endif

	void EzStorage::LoadFromContainer( const boost::shared_ptr<StorageContainer> &container, const std::wstring &FileName, const boost::shared_ptr<Lambda_1<std::vector<unsigned char> > > &LoadLogic, const boost::shared_ptr<Lambda> &FailLogic )
	{
		std::string path = WstringToUtf8( FileName );
		printf( "Load( FileName = %s );\n", path.c_str() );

		// Fallback action if file doesn't exist
		/*if ( !container->FileExists( FileName ) )
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
		}*/

#ifdef PS3
		if( FileName == L"HighScores" || FileName == L"PlayerData.hsc" )
		{
			FailLogic->Apply();
			return;
		}

		path = "SaveData.bam";

		_load_done = false;

		// Get the space needed for save data.
		SceNpTrophyContext context;
		SceNpTrophyHandle handle;
		ForceGetTrophyContext( context, handle );
		if( sceNpTrophyGetRequiredDiskSpace( context, handle, &RequiredTrophySpace, 0 ) < 0 )
			RequiredTrophySpace = 0;

		char dirName[ CELL_SAVEDATA_PREFIX_SIZE ];
		CellSaveDataSetBuf setBuf;

		strncpy( dirName, AUTOSAVEDATA_DIRNAME, CELL_SAVEDATA_PREFIX_SIZE );
		dirName[ CELL_SAVEDATA_PREFIX_SIZE - 1 ] = 0;

		setBuf.dirListMax = 0;
		setBuf.fileListMax = FILE_INDEX_END;
		memset( setBuf.reserved, 0, sizeof( setBuf.reserved ) );
		setBuf.bufSize = FILE_INDEX_END * sizeof( CellSaveDataFileStat );
		setBuf.buf = malloc( setBuf.bufSize );

		assert( setBuf.buf );

		int ret = cellSaveDataAutoLoad2(
			CELL_SAVEDATA_VERSION_420,
			dirName,
			CELL_SAVEDATA_ERRDIALOG_NONE,
			&setBuf,
			CallbackDataStatusLoad,
			CallbackFileOperationLoad,
			SYS_MEMORY_CONTAINER_ID_INVALID,
			NULL
		);

		if( ret == CELL_SAVEDATA_RET_OK && _file_buffer )
		{
			unsigned int *intPtr = reinterpret_cast< unsigned int * >( _file_buffer );
			unsigned int bufferSize = *intPtr++;
			unsigned int checksum = *intPtr++;

			unsigned int ourChecksum = Checksum( reinterpret_cast< unsigned char * >( intPtr ), bufferSize );

			if( bufferSize > 0 && bufferSize < ( AUTOSAVE_SIZE - 2 * sizeof( unsigned int ) )
				&& ourChecksum == checksum )
			{
				std::vector< unsigned char > data;
				data.reserve( AUTOSAVE_SIZE );
				data.assign( reinterpret_cast< unsigned char * >( intPtr ),
					reinterpret_cast< unsigned char * >( intPtr ) + bufferSize );
				LoadLogic->Apply( data );
			}
			else
			{
				CloudberryKingdomGame::ShowError_LoadError();

				FailLogic->Apply();
			}
		}
		else
			FailLogic->Apply();

		if( setBuf.buf )
			free( setBuf.buf );

		if( _file_buffer )
		{
			free( _file_buffer );
			_file_buffer = NULL;
		}
#endif

#ifdef CAFE
		if( LoadLogic != 0 )
		{
			std::string path = WstringToUtf8( FileName );

			bool global = false;

			if( FileName == L"HighScores" )
			{
				global = true;
			}
			else if( FileName == L"PlayerData.hsc" )
			{
				global = false;
			}
			else
			{
				path = "PlayerProgress";
				global = false;
			}

			boost::shared_ptr< SaveReaderWiiU > reader = boost::make_shared< SaveReaderWiiU >( path, global );
			std::vector< unsigned char > data;
			if( reader->ReadEverything( data ) )
			{
				LoadLogic->Apply( data );
			}
			else
			{
				FailLogic->Apply();
			}
		}
#endif

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
#ifndef CAFE
		{
			InUseLock->Lock();

			InUse->MyBool = false;

			InUseLock->Unlock();
		}
#endif
	}

}
