#include <global_header.h>

#include <Game/CloudberryKingdom/CloudberryKingdom.CloudberryKingdomGame.h>
#include <Utility/Log.h>
#include <Utility/Error.h>
#include <Hacks/String.h>

#include <Core/Tools/Set.h>

#ifdef PS3
#include <stdio.h>
#include <stdlib.h>
#include <vector>

#include <cell/cell_fs.h>
#include <sys/ppu_thread.h>
#include <sysutil/sysutil_savedata.h>
#include <sysutil/sysutil_gamecontent.h>
#include <np.h>

#define SCEA
//#define SCEE

#if	  defined(SCEA)
	#define AUTOSAVEDATA_DIRNAME "NPUB31177-AUTO"
#elif defined(SCEE)
	#define AUTOSAVEDATA_DIRNAME "NPEB01312-AUTO"
#endif

#define AUTOSAVE_FILENAME "SYS-DATA"
#define AUTOSAVE_PARAMSFO_TITLE "Cloudberry Kingdom"
#define AUTOSAVE_PARAMSFO_DETAIL "Cloudberry Kingdom"

#define AUTOSAVE_SIZE (256 * 1024)

#define ICON0_SIZE (101151)
static void *ICON0_DATA = NULL;

enum {
	FILE_INDEX_MUSTEXIST = 0,
	FILE_INDEX_ICON0 = 1,
	FILE_INDEX_END
};

static void *_file_buffer = NULL;
static bool _save_done = false;
static bool _load_done = false;

const char secureFileId[ CELL_SAVEDATA_SECUREFILEID_SIZE ] = {
	//0x1, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7, 0x8, 0x9, 0xa, 0xb, 0xc, 0xd, 0xe, 0xf, 0xff
	0xa0, 0x68, 0xa4, 0xa5, 0xf0, 0xae, 0xee, 0xaa, 0x6a, 0x23, 0xd7, 0x88, 0x45, 0x8c, 0x84, 0xd5
};

extern std::string PS3_PATH_PREFIX;

static bool saveInFlight = false;
static bool loadInFlight = false;
bool SavingDisabled = false;

// Do trophy registration.  Defined in CorePS3.cpp.
extern void RegisterTrophyContextThread( uint64_t context );

// Has the context been registered?  Defined in CorePS3.cpp.
extern bool gTrophyContextRegistered;

// Get current trophy context and handle.  Defined in CorePS3.cpp.
extern void ForceGetTrophyContext( SceNpTrophyContext &context, SceNpTrophyHandle &handle );

void WaitForSaveLoad()
{
	while( loadInFlight )
	{
		int ret = cellSysutilCheckCallback();
		if( ret )
			LOG_WRITE( "cellSysutilCheckCallback() = 0x%x\n", ret );

		sys_ppu_thread_yield();
	}
	while( saveInFlight )
	{
		int ret = cellSysutilCheckCallback();
		if( ret )
			LOG_WRITE( "cellSysutilCheckCallback() = 0x%x\n", ret );

		sys_ppu_thread_yield();
	}
}

void SaveAllOnExit()
{
	if( CloudberryKingdom::CloudberryKingdomGame::CurrentPresence == CloudberryKingdom::Presence_Campaign )
	{
		CloudberryKingdom::SaveGroup::SaveAll();
	}
}

#endif

#if defined( VITA )
#include <Utility/Save.h>
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

	void SynchronizeAll()
	{
		int _max_CampaignLevel = 0, _max_CampaignCoins = 0, _max_CampaignIndex = 0;
		int _max_LastPlayerLevelUpload = 0;

		// Find the maxes
		for ( int i = 0; i < 4; ++i )
		{
			if ( PlayerManager::Players[ i ] == 0 ) continue;
			const boost::shared_ptr<PlayerData> &p = PlayerManager::Players[ i ];

			_max_CampaignLevel = __max( _max_CampaignLevel, p->CampaignLevel );
			_max_CampaignCoins = __max( _max_CampaignCoins, p->CampaignCoins );
			_max_CampaignIndex = __max( _max_CampaignIndex, p->CampaignIndex );
			_max_LastPlayerLevelUpload = __max( _max_LastPlayerLevelUpload, p->LastPlayerLevelUpload );
		}

		// Push maxes to everyone
		for ( int i = 0; i < 4; ++i )
		{
			if ( PlayerManager::Players[ i ] == 0 ) continue;
			const boost::shared_ptr<PlayerData> &p = PlayerManager::Players[ i ];

			p->CampaignLevel = _max_CampaignLevel;
			p->CampaignCoins = _max_CampaignCoins;
			p->CampaignIndex = _max_CampaignIndex;
			p->LastPlayerLevelUpload = _max_LastPlayerLevelUpload;
		}

		// Make master awardment set
		Set<int> awardments;
		for ( int i = 0; i < 4; ++i )
		{
			if ( PlayerManager::Players[ i ] == 0 ) continue;
			const boost::shared_ptr<PlayerData> &p = PlayerManager::Players[ i ];

			for ( std::map<int, bool>::const_iterator guid = p->Awardments_Renamed->dict.begin(); guid != p->Awardments_Renamed->dict.end(); ++guid )
				awardments.Add( guid->first );
		}

		// Push awardments to everyone
		for ( int i = 0; i < 4; ++i )
		{
			if ( PlayerManager::Players[ i ] == 0 ) continue;
			const boost::shared_ptr<PlayerData> &p = PlayerManager::Players[ i ];

			for ( std::map<int, bool>::const_iterator guid = awardments.dict.begin(); guid != awardments.dict.end(); ++guid )
				p->Awardments_Renamed->Add( guid->first );
		}

		// Calculate max highscores
		std::map<int, boost::shared_ptr<ScoreEntry> > MaxHighScores;
		for ( int i = 0; i < 4; ++i )
		{
			if ( PlayerManager::Players[ i ] == 0 ) continue;
			const boost::shared_ptr<PlayerData> &p = PlayerManager::Players[ i ];

			for ( std::map<int, boost::shared_ptr<ScoreEntry> >::const_iterator
					HighScore = p->HighScores.begin();
					HighScore != p->HighScores.end();
					++HighScore )
			{
				if ( Contains( MaxHighScores, HighScore->first ) )
				{
					MaxHighScores[ HighScore->first ] = boost::make_shared<ScoreEntry>(
						std::wstring( L"" ),
						HighScore->second->GameId,
						__max( HighScore->second->Value, MaxHighScores[ HighScore->first ]->Value ),
						__max( HighScore->second->Score, MaxHighScores[ HighScore->first ]->Score ),
						__max( HighScore->second->Level_Renamed, MaxHighScores[ HighScore->first ]->Level_Renamed ),
						__min( HighScore->second->Attempts, MaxHighScores[ HighScore->first ]->Attempts ),
						__min( HighScore->second->Time, MaxHighScores[ HighScore->first ]->Time ),
						__max( HighScore->second->Date, MaxHighScores[ HighScore->first ]->Date ) );
				}
				else
				{
					MaxHighScores[ HighScore->first ] = HighScore->second;
				}
			}
		}

		// Push highscores to every player
		for ( int i = 0; i < 4; ++i )
		{
			if ( PlayerManager::Players[ i ] == 0 ) continue;
			const boost::shared_ptr<PlayerData> &p = PlayerManager::Players[ i ];

			for ( std::map<int, boost::shared_ptr<ScoreEntry> >::const_iterator
					HighScore = MaxHighScores.begin();
					HighScore != MaxHighScores.end();
					++HighScore )
			{
				p->HighScores[ HighScore->first ] = boost::make_shared<ScoreEntry>(
					std::wstring( L"" ),
					HighScore->second->GameId,
					HighScore->second->Value,
					HighScore->second->Score,
					HighScore->second->Level_Renamed,
					HighScore->second->Attempts,
					HighScore->second->Time,
					HighScore->second->Date );
			}
		}

		// Fuck these stats
		//boost::shared_ptr<PlayerStats> LifetimeStats, GameStats, LevelStats, TempStats;
		//boost::shared_ptr<PlayerStats> CampaignStats;
	}

	void SaveGroup::SaveAll()
	{
#if PC_VERSION
		// FIXME: save/load on PC version
		return;
#endif

		if ( !CloudberryKingdomGame::CanSave() ) return;

		CloudberryKingdomGame::CampaignProgressMade = false;

		for ( std::vector<boost::shared_ptr<SaveLoad> >::const_iterator ThingToSave = ThingsToSave.begin(); ThingToSave != ThingsToSave.end(); ++ThingToSave )
		{
			//if (!(ThingToSave is ScoreList)) Tools::Write("!");

			Incr();
			( *ThingToSave )->Save();
			Wait();
		}

#if PS3
		CloudberryKingdomGame::ShowSaving();
#elif CAFE
		CloudberryKingdomGame::ShowSaving();
#endif

	#if defined(NOT_PC)
		// Save each player's info
		//std::vector<boost::shared_ptr<PlayerData> > vec = PlayerManager::getLoggedInPlayers();
		//for ( std::vector<boost::shared_ptr<PlayerData> >::const_iterator player = vec.begin(); player != vec.end(); ++player )
		//{
		//	Incr();
		//	( *player )->ContainerName = std::wstring( L"Gamers" );
		//	( *player )->FileName = std::wstring( L"___" ) + ( *player )->GetName();
		//	( *player )->Save();
		//	Wait();
		//}
		SynchronizeAll();
		Incr();
		PlayerManager::Players[ 0 ]->ContainerName = std::wstring( L"Gamers" );
		PlayerManager::Players[ 0 ]->FileName = std::wstring( L"___" ) + PlayerManager::Players[ 0 ]->GetName();
		PlayerManager::Players[ 0 ]->Save();
		Wait();
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
#ifndef PS3
		SynchronizeAll();
#endif
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
		LOG_WRITE( "Save( ContainerName = %s, FileName = %s );\n", WstringToUtf8( ContainerName ).c_str(), WstringToUtf8( FileName ).c_str() );
		
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
		
		if( !SavingDisabled )
		{
			ret = sys_ppu_thread_create( &tid, SaveToContainerThread, reinterpret_cast< uint64_t >( args ), 1001, 16 * 1024, 0, "SaveToContainerThread" );

			if( ret != 0 )
				Fail->Apply();
		}
		else
		{
			Fail->Apply();
		}
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
	enum {
		OperationState_SaveIcon,
		OperationState_SaveAutosave
	} SaveOperationState;

	void CallbackDataStatusSave( CellSaveDataCBResult *result, CellSaveDataStatGet *get, CellSaveDataStatSet *set )
	{
		set->reCreateMode = CELL_SAVEDATA_RECREATE_YES_RESET_OWNER;
		set->setParam = &get->getParam;
		set->indicator = NULL;

		if( get->isNewData )
		{
			LOG_WRITE( "Save data %s does NOT exists.\n", get->dir.dirName );

			int sizeKb = get->sysSizeKB + AUTOSAVE_SIZE / 1024 + ICON0_SIZE / 1024;
			int neededKb = get->hddFreeSizeKB - sizeKb;

			LOG_WRITE( "hddFreeSizeKB = %d, sizeKb = %d, neededKb = %d\n", get->hddFreeSizeKB, sizeKb, neededKb );
			if( neededKb < 0 )
			{
				LOG_WRITE( "Not enough space to save! Need %d more KB.\n", -neededKb );

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

		//ICON0_DATA = NULL;
		SaveOperationState = OperationState_SaveIcon;

		result->result = CELL_SAVEDATA_CBRESULT_OK_NEXT;
	}

	/* Load binary from file to memory */
	int fileAllocLoad(const char *filePath, void **buf, unsigned int *size)
	{
		if( *buf )
			return 0;
		else
			*buf = malloc( ICON0_SIZE );

		int ret;
		int fd;
		CellFsStat status;
		uint64_t readlen;

		//*buf = NULL;
		*size = 0;

		ret = cellFsOpen(filePath, CELL_FS_O_RDONLY, &fd, NULL, 0);
		if(ret != CELL_FS_SUCCEEDED){
			free(*buf);
			*buf = NULL;
			return -1;
		}

		ret = cellFsFstat(fd, &status);
		if(ret != CELL_FS_SUCCEEDED){
			cellFsClose(fd);
			free(*buf);
			*buf = NULL;
			return -1;
		}

		//*buf = malloc( (size_t)status.st_size );
		if( *buf == NULL ) {
			cellFsClose(fd);
			return -1;
		}

		if( status.st_size > ICON0_SIZE )
		{
			cellFsClose(fd);
			free( *buf );
			*buf = NULL;
			return -1;
		}

		ret = cellFsRead(fd, *buf, status.st_size, &readlen);
		if(ret != CELL_FS_SUCCEEDED || status.st_size != readlen ) {
			cellFsClose(fd);
			free(*buf);
			*buf = NULL;
			return -1;
		}

		ret = cellFsClose(fd);
		if(ret != CELL_FS_SUCCEEDED){
			free(*buf);
			*buf = NULL;
			return -1;
		}

		*size = status.st_size;

		return 0;
	}

	void CallbackFileOperationSave( CellSaveDataCBResult *result, CellSaveDataFileGet *get, CellSaveDataFileSet *set )
	{
		unsigned int fileSize;

		switch( SaveOperationState )
		{
		case OperationState_SaveIcon:
			if( fileAllocLoad( ( PS3_PATH_PREFIX + "ContentPS3/SaveMeta/ICON0.PNG" ).c_str(), &ICON0_DATA, &fileSize ) == 0 )
			{
				LOG_WRITE( "File size %d, expected size %d\n", fileSize, ICON0_SIZE );
				set->fileOperation = CELL_SAVEDATA_FILEOP_WRITE;
				set->fileBuf = ICON0_DATA;
				set->fileBufSize = ICON0_SIZE;
				set->fileSize = ICON0_SIZE;
				set->fileOffset = 0;
				set->fileType = CELL_SAVEDATA_FILETYPE_CONTENT_ICON0;
				set->reserved = NULL;
				
				SaveOperationState = OperationState_SaveAutosave;
				result->result = CELL_SAVEDATA_CBRESULT_OK_NEXT;
			}
			else
			{
				result->result = CELL_SAVEDATA_CBRESULT_ERR_FAILURE;
			}

			break;
		case OperationState_SaveAutosave:
			/*if( ICON0_DATA )
			{
				free( ICON0_DATA );
				ICON0_DATA = NULL;
			}*/
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
			break;
		}
	}
#endif

	void EzStorage::SaveToContainer( const boost::shared_ptr<StorageContainer> &container, const std::wstring &FileName, const boost::shared_ptr<Lambda_1<boost::shared_ptr< BinaryWriter > > > &SaveLogic, const boost::shared_ptr<Lambda> &Fail )
	{
		std::string path = WstringToUtf8( FileName );
		LOG_WRITE( "Save( FileName = %s );\n", path.c_str() );

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
		setBuf.bufSize = FILE_INDEX_END * sizeof( CellSaveDataFileStat );
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
		LOG_WRITE( "Buffer length: %d < %d\n", bufferLength, AUTOSAVE_SIZE );
		// FIXME: Write checksum here.
		unsigned int checksum = Checksum( &saveData[ 0 ], bufferLength );
		memcpy( reinterpret_cast< char * >( _file_buffer ) + sizeof( unsigned int ), &checksum, sizeof( unsigned int ) );

		// Write the rest of the save data.
		memcpy( reinterpret_cast< char * >( _file_buffer ) + 2 * sizeof( unsigned int ), &saveData[ 0 ], saveData.size() );

		int ret = cellSaveDataAutoSave2(
			CELL_SAVEDATA_VERSION_420,
			dirName,
			CELL_SAVEDATA_ERRDIALOG_NONE,
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

		SynchronizeAll();

		delete args;

		sys_ppu_thread_exit( 0 );
	}
#endif

	void EzStorage::Load( const std::wstring &ContainerName, const std::wstring &FileName, const boost::shared_ptr<Lambda_1<std::vector<unsigned char> > > &LoadLogic, const boost::shared_ptr<Lambda> &Fail )
	{
		LOG_WRITE( "Load( ContainerName = %s, FileName = %s );\n", WstringToUtf8( ContainerName ).c_str(), WstringToUtf8( FileName ).c_str() );
		
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

	static bool NotEnoughSaveSpace = false;
	static uint64_t TotalRequiredSpace = 0;

	void CallbackDataStatusLoad( CellSaveDataCBResult *result, CellSaveDataStatGet *get, CellSaveDataStatSet *set )
	{
		NotEnoughSaveSpace = false;
		TotalRequiredSpace = 0;

		// Check if there is any data to load.
		if( get->isNewData || RequiredTrophySpace > 0 )
		{
			LOG_WRITE( "NO SAVE DATA FOUND!\n" );

			int sizeKb = 0;
			if( get->isNewData )
			{
				sizeKb += get->sysSizeKB;
				sizeKb += ( ( AUTOSAVE_SIZE / 1024 ) + ( ICON0_SIZE / 1024 ) );
			}
			if( RequiredTrophySpace > 0 )
				sizeKb += static_cast< int >( RequiredTrophySpace / 1024 );

			int neededKb = get->hddFreeSizeKB - sizeKb;

			LOG_WRITE( "hddFreeSizeKB = %d, sizeKb = %d, neededKb = %d\n", get->hddFreeSizeKB, sizeKb, neededKb );
			
			if( neededKb < 0 )
			{
				LOG_WRITE( "Not enough space to save! Need %d more KB.\n", -neededKb );

				TotalRequiredSpace = -neededKb;
				NotEnoughSaveSpace = true;
				/*std::wstring error = Format( Localization::WordString( Localization::Words_Err_PS3_NotEnoughSpace ).c_str(), -neededKb );
				DisplayError( ErrorType( WstringToUtf8( error ), NULL, ErrorType::NONE, NULL, true ) );*/

				result->errNeedSizeKB = -neededKb;
				result->result = CELL_SAVEDATA_CBRESULT_ERR_NOSPACE;
				return;
			}

			if( get->isNewData )
			{
				result->result = CELL_SAVEDATA_CBRESULT_ERR_NODATA;
				return;
			}
		}

		// First check if the data belongs to the current user.
		if( get->bind & CELL_SAVEDATA_BINDSTAT_ERR_OWNER )
		{
			SavingDisabled = true;
			LOG_WRITE( "WRONG OWNER!\n" );
			DisplayError( ErrorType( WstringToUtf8( Localization::WordString( Localization::Words_Err_PS3_SaveDataNotUsed ) ) ) );
			result->result = CELL_SAVEDATA_CBRESULT_ERR_FAILURE;
			return;
		}

		// There is some data!
		if( get->fileListNum < get->fileNum )
		{
			LOG_WRITE( "MORE FILES THAN EXPECTED!\n" );
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
					LOG_WRITE( "Save file is of the wrong size! Expected %d but got %d.\n", AUTOSAVE_SIZE, get->fileList[ i ].st_size );
					DisplayError( ErrorType( WstringToUtf8( Localization::WordString( Localization::Words_Err_PS3_CorruptLoad ) ) ) );
					result->result = CELL_SAVEDATA_CBRESULT_ERR_BROKEN;
					return;
				}

				foundAutosave = true;
			}
		}

		if( !foundAutosave )
		{
			LOG_WRITE( "Save file %s missing!\n", AUTOSAVE_FILENAME );
			DisplayError( ErrorType( WstringToUtf8( Localization::WordString( Localization::Words_Err_PS3_CorruptLoad ) ) ) );
			result->result = CELL_SAVEDATA_CBRESULT_ERR_BROKEN;
			return;
		}

		set->reCreateMode = CELL_SAVEDATA_RECREATE_NO_NOBROKEN;
		set->setParam = NULL;
		set->indicator = NULL;

		result->result = CELL_SAVEDATA_CBRESULT_OK_NEXT;
		result->userdata = NULL;
		LOG_WRITE( "CallbackDataStatusLoad end.\n" );
	}

	void CallbackFileOperationLoad( CellSaveDataCBResult *result, CellSaveDataFileGet *get, CellSaveDataFileSet *set )
	{
		result->result = _load_done ? CELL_SAVEDATA_CBRESULT_OK_LAST : CELL_SAVEDATA_CBRESULT_OK_NEXT;

		LOG_WRITE( "FileOperationLoad, _load_done = %d\n", _load_done );

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
		LOG_WRITE( "Load( FileName = %s );\n", path.c_str() );

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

		loadInFlight = true;

		// Get the space needed for save data.
		// FIXME: The trophy initialization function does its own check for available space.
		SceNpTrophyContext context;
		SceNpTrophyHandle handle;
		ForceGetTrophyContext( context, handle );
		if( sceNpTrophyGetRequiredDiskSpace( context, handle, &RequiredTrophySpace, 0 ) < 0 )
			RequiredTrophySpace = 0;
		//RequiredTrophySpace = 0;

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

		LOG_WRITE( "cellSaveDataAutoLoad2 returned 0x%x\n", ret );
		LOG_WRITE( "_file_buffer = 0x%x\n", _file_buffer );

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
		else if( ret == CELL_SAVEDATA_ERROR_BROKEN )
		{
			CloudberryKingdomGame::ShowError_LoadError();

			FailLogic->Apply();
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

		static bool trophyRegistrationExecuted = false;
		if( NotEnoughSaveSpace )
		{
			LOG_WRITE( "Before cellGameContentErrorDialog: space = %d KB\n", TotalRequiredSpace );
			cellGameContentErrorDialog( CELL_GAME_ERRDIALOG_NOSPACE_EXIT, TotalRequiredSpace, NULL );
			LOG_WRITE( "After cellGameContentErrorDialog\n" );
		}
		else if( !trophyRegistrationExecuted )
		{
			// This was the first load so we want to register trophies now.
			trophyRegistrationExecuted = true;

			gTrophyContextRegistered = false;

			sys_ppu_thread_t tid;
			ret = sys_ppu_thread_create( &tid, RegisterTrophyContextThread, 0,
				1001, 16 * 1024, 0, "RegisterTrophyContextThread" );
			if( ret != 0 )
				LOG_WRITE( "Failed to start RegisterTrophyContextThread: 0x%x\n", ret );
		}

		loadInFlight = false;
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
