#include <Utility/ConsoleInformation.h>

#include <Utility/Log.h>

#include <cafe.h>
#include <cafe/gx2.h>
#include <cafe/sci/sciEnum.h>
#include <cafe/sci/sciPublicApi.h>
#include <nn/erreula.h>

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

void SetErrorLanguage( ConsoleLanguage language )
{
	LOG_WRITE( "Ignoring SetErrorLanguage\n" );
	/*SCIPlatformRegion region;
	SCIStatus status = SCIGetPlatformRegion( &region );
	if( status != SCI_STATUS_SUCCESS )
		region = SCI_PLATFORM_REGION_USA;

	SCICafeLanguage internalLanguage = SCI_CAFE_LANGUAGE_ENGLISH;
	switch( language )
	{
	case ConsoleLanguage_JAPANESE:
		internalLanguage = SCI_CAFE_LANGUAGE_JAPANESE;
		break;
	case ConsoleLanguage_ENGLISH:
		break;
	case ConsoleLanguage_FRENCH:
		internalLanguage = SCI_CAFE_LANGUAGE_FRENCH;
		break;
	case ConsoleLanguage_GERMAN:
		internalLanguage = SCI_CAFE_LANGUAGE_GERMAN;
		break;
	case ConsoleLanguage_ITALIAN:
		internalLanguage = SCI_CAFE_LANGUAGE_ITALIAN;
		break;
	case ConsoleLanguage_SPANISH:
		internalLanguage = SCI_CAFE_LANGUAGE_SPANISH;
		break;
	case ConsoleLanguage_CHINESE:
		internalLanguage = SCI_CAFE_LANGUAGE_CHINESE;
		break;
	case ConsoleLanguage_KOREAN:
		internalLanguage = SCI_CAFE_LANGUAGE_KOREAN;
		break;
	case ConsoleLanguage_DUTCH:
		internalLanguage = SCI_CAFE_LANGUAGE_DUTCH;
		break;
	case ConsoleLanguage_PORTUGUESE:
		internalLanguage = SCI_CAFE_LANGUAGE_PORTUGUESE;
		break;
	case ConsoleLanguage_RUSSIAN:
		internalLanguage = SCI_CAFE_LANGUAGE_RUSSIAN;
		break;
	case ConsoleLanguage_TAIWANESE:
		internalLanguage = SCI_CAFE_LANGUAGE_TAIWANESE;
		break;
	}

	if( region == SCI_PLATFORM_REGION_JPN
		&& ( internalLanguage != SCI_CAFE_LANGUAGE_JAPANESE ) )
		internalLanguage = SCI_CAFE_LANGUAGE_JAPANESE;
	else if( region == SCI_PLATFORM_REGION_USA )
	{
		switch( internalLanguage )
		{
		case SCI_CAFE_LANGUAGE_ENGLISH:
		case SCI_CAFE_LANGUAGE_FRENCH:
		case SCI_CAFE_LANGUAGE_SPANISH:
		case SCI_CAFE_LANGUAGE_PORTUGUESE:
			break;
		default:
			internalLanguage = SCI_CAFE_LANGUAGE_ENGLISH;
		}
	}
	else if( region == SCI_PLATFORM_REGION_EUR
		|| ( region == SCI_PLATFORM_REGION_AUS ) )
	{
		switch( internalLanguage )
		{
		case SCI_CAFE_LANGUAGE_ENGLISH:
		case SCI_CAFE_LANGUAGE_FRENCH:
		case SCI_CAFE_LANGUAGE_SPANISH:
		case SCI_CAFE_LANGUAGE_PORTUGUESE:
		case SCI_CAFE_LANGUAGE_GERMAN:
		case SCI_CAFE_LANGUAGE_ITALIAN:
		case SCI_CAFE_LANGUAGE_DUTCH:
		case SCI_CAFE_LANGUAGE_RUSSIAN:
			break;
		default:
			internalLanguage = SCI_CAFE_LANGUAGE_ENGLISH;
		}
	}

	nn::erreula::ChangeLangError( static_cast< nn::erreula::LangType >( internalLanguage ) );*/
}

bool IsOnlineContentRestricted()
{
	return false;
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
	return false;
}

bool IsAspect4by3()
{
	return GX2GetSystemTVAspectRatio() == GX2_ASPECT_RATIO_4_BY_3;
}