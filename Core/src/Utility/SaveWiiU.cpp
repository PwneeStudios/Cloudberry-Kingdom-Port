#include <Utility/Save.h>

#include <nn/act.h>
#include <nn/save.h>
#include <Utility/Error.h>
#include <Utility/Log.h>

bool initializeCalled = false;
bool isInitialized = false;

bool InitializeSave()
{
	if( initializeCalled )
		return isInitialized;

	initializeCalled = true;

	// FIXME: Docs say to delay this as much as possible.
	SAVEInit();
	nn::act::Initialize();

	u8 accountSlot = nn::act::GetSlotNo();
	u32 persistentId = nn::act::GetPersistentIdEx( accountSlot );

	if( nn::act::IsSlotOccupied( accountSlot ) )
	{
		LOG.Write( "Creating account for slot %d with id 0x%X\n", accountSlot, persistentId );

		if( SAVEInitSaveDir( accountSlot ) != SAVE_STATUS_OK )
		{
			LOG.Write( "Failed to create save directory.\n" );
			isInitialized = false;
			
			// There was not enough free space to create save data.
			DisplayError( 1550100 );

			return false;
		}
	}

	/*GLOBAL_ACCOUNT_NAME = LOCAL_ACCOUNT_NAME;
	memset( LOCAL_ACCOUNT_NAME, 0, sizeof( LOCAL_ACCOUNT_NAME ) );
	sprintf( LOCAL_ACCOUNT_NAME, "Errorberry" );
	nn::act::GetAccountId( LOCAL_ACCOUNT_NAME );*/
	
	LOG.Write( "Creating global directory\n" );
	if( SAVEInitSaveDir( ACT_SLOT_NO_COMMON ) != SAVE_STATUS_OK )
	{
		LOG.Write( "Failed to create common directory.\n" );
		isInitialized = false;

		// There was not enough free space to create save data.
		DisplayError( ErrorType( 1550100 ) );

		return false;
	}

	isInitialized = true;
	return true;
}