#include <Utility/ConsoleInformation.h>
#include <Utility/Log.h>

#include <np.h>

#include <Ratings.h>

ConsoleRegion GetConsoleRegion()
{
	return ConsoleRegion_USA;
}

ConsoleLanguage GetConsoleLanguage()
{
	return ConsoleLanguage_ENGLISH;
}

void SetErrorLanguage( ConsoleLanguage language )
{
}

int GetParentalControlLevel()
{
	return 0;
}

bool IsOnlineContentRestricted()
{
	int isRestricted;
	int age;

	int ret = sceNpManagerGetContentRatingFlag( &isRestricted, &age );
	if( ret < 0 )
	{
		LOG_WRITE( "sceNpManagerGetContentRatingFlag failed: 0x%x\n", ret );
		return true;
	}

	//if( age >= ONLINE_AGE_CUTOFF )
	//{
	//	isRestricted = false;
	//}

	return isRestricted;
}

bool IsAsianButtonConfiguration()
{
	return false;
}

bool IsCustomMusicPlaying()
{
	return false;
}

bool GLOBAL_SYSTEM_MENU_OPEN = false;

bool IsSystemMenuVisible()
{
	return GLOBAL_SYSTEM_MENU_OPEN;
}

bool IsAspect4by3()
{
	return false;
}
