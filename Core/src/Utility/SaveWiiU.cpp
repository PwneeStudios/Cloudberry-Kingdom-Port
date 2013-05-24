#include <Utility/Save.h>

#include <Hacks/String.h>
#include <nn/act.h>
#include <nn/save.h>
#include <Utility/Error.h>
#include <Utility/Log.h>

bool initializeCalled = false;
bool isInitialized = false;

char *GLOBAL_ACCOUNT_NAME = NULL;
static char LOCAL_ACCOUNT_NAME[ ACT_ACCOUNT_ID_SIZE ];

// Show saving message.  Defined in CloudberryKingdomGame.cpp.
extern void GlobalShowSaving();

bool InitializeSave()
{
	nn::act::Initialize();
	return false;

	if( initializeCalled )
		return isInitialized;

	initializeCalled = true;

	// FIXME: Docs say to delay this as much as possible.
	SAVEInit();
	nn::act::Initialize();

	FSClient client;
	FSCmdBlock cmd;

	FSAddClient( &client, FS_RET_NO_ERROR );
	FSInitCmdBlock( &cmd );

	u8 accountSlot = nn::act::GetSlotNo();
	u32 persistentId = nn::act::GetPersistentIdEx( accountSlot );
	if( nn::act::IsSlotOccupied( accountSlot ) )
	{
		// First try to stat the directory to see if it exists.
		FSStat dirStat;
		FSStatus status = SAVEGetStat( &client, &cmd, accountSlot, ".", &dirStat, FS_RET_ALL_ERROR );

		if( status != FS_STATUS_OK )
		{
			LOG_WRITE( "Creating account for slot %d with id 0x%X\n", accountSlot, persistentId );

			if( SAVEInitSaveDir( accountSlot ) != SAVE_STATUS_OK )
			{
				LOG_WRITE( "Failed to create save directory.\n" );
				isInitialized = false;
			
				// There was not enough free space to create save data.
				DisplayError( 1550100 );

				FSDelClient( &client, FS_RET_NO_ERROR );
				return false;
			}
			else
				GlobalShowSaving();
		}
		else
		{
			LOG_WRITE( "Directory for slot %d already exists\n", accountSlot );
		}
	}

	nn::Result r;
	GLOBAL_ACCOUNT_NAME = LOCAL_ACCOUNT_NAME;
	memset( LOCAL_ACCOUNT_NAME, 0, sizeof( LOCAL_ACCOUNT_NAME ) );
	sprintf( LOCAL_ACCOUNT_NAME, "Errorberry" );
	r = nn::act::GetAccountId( LOCAL_ACCOUNT_NAME );
	
	// First try to stat the directory to see if it exists.
	FSStat dirStat;
	FSStatus status = SAVEGetStat( &client, &cmd, ACT_SLOT_NO_COMMON, ".", &dirStat, FS_RET_ALL_ERROR );

	if( status != FS_STATUS_OK )
	{
		LOG_WRITE( "Creating global directory\n" );
		if( SAVEInitSaveDir( ACT_SLOT_NO_COMMON ) != SAVE_STATUS_OK )
		{
			LOG_WRITE( "Failed to create common directory.\n" );
			isInitialized = false;

			// There was not enough free space to create save data.
			DisplayError( ErrorType( 1550100 ) );
		
			FSDelClient( &client, FS_RET_NO_ERROR );
			return false;
		}
		else
			GlobalShowSaving();
	}
	else
	{
		LOG_WRITE( "Common directory alerady exists.\n" );
	}

	isInitialized = true;
	
	FSDelClient( &client, FS_RET_NO_ERROR );
	
	return true;
}