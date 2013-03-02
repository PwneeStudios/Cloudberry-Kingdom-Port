#include <Utility/ConsoleInformation.h>

#include <cafe.h>
#include <cafe/sci/sciEnum.h>
#include <cafe/sci/sciPublicApi.h>

ConsoleRegion GetConsoleRegion()
{
	SCIPlatformRegion region;
	SCIStatus status = SCIGetPlatformRegion( &region );
	if( status == SCI_STATUS_SUCCESS )
	{
		switch( region )
		{
		case SCI_PLATFORM_REGION_JPN:
			return ConsoleRegion_JPN;
		case SCI_PLATFORM_REGION_USA:
			return ConsoleRegion_USA;
		case SCI_PLATFORM_REGION_EUR:
			return ConsoleRegion_EUR;
		//case SCI_PLATFORM_REGION_AUS: // Obsolete.
		case SCI_PLATFORM_REGION_CHN:
			return ConsoleRegion_CHN;
		case SCI_PLATFORM_REGION_KOR:
			return ConsoleRegion_KOR;
		case SCI_PLATFORM_REGION_TWN:
			return ConsoleRegion_TWN;
		default:
			// By default the region is US.
			break;
		}
	}

	return ConsoleRegion_USA;
}

ConsoleLanguage GetConsoleLanguage()
{
	SCICafeLanguage language;
	SCIStatus status = SCIGetCafeLanguage( &language );
	if( status == SCI_STATUS_SUCCESS )
	{
		switch( language )
		{			
		case SCI_CAFE_LANGUAGE_JAPANESE:
			return ConsoleLanguage_JAPANESE;
		case SCI_CAFE_LANGUAGE_ENGLISH:
			return ConsoleLanguage_ENGLISH;
		case SCI_CAFE_LANGUAGE_FRENCH:
			return ConsoleLanguage_FRENCH;
		case SCI_CAFE_LANGUAGE_GERMAN:
			return ConsoleLanguage_GERMAN;
		case SCI_CAFE_LANGUAGE_ITALIAN:
			return ConsoleLanguage_ITALIAN;
		case SCI_CAFE_LANGUAGE_SPANISH:
			return ConsoleLanguage_SPANISH;
		case SCI_CAFE_LANGUAGE_CHINESE:
			return ConsoleLanguage_CHINESE;
		case SCI_CAFE_LANGUAGE_KOREAN:
			return ConsoleLanguage_KOREAN;
		case SCI_CAFE_LANGUAGE_DUTCH:
			return ConsoleLanguage_DUTCH;
		case SCI_CAFE_LANGUAGE_PORTUGUESE:
			return ConsoleLanguage_PORTUGUESE;
		case SCI_CAFE_LANGUAGE_RUSSIAN:
			return ConsoleLanguage_RUSSIAN;
		case SCI_CAFE_LANGUAGE_TAIWANESE:
			return ConsoleLanguage_TAIWANESE;
		default:
			break;
		}
	}

	return ConsoleLanguage_ENGLISH;
}

bool IsAsianButtonConfiguration()
{
	return false;
}

bool IsCustomMusicPlaying()
{
	return false;
}

bool IsSystemMenuVisible()
{
	return false
}