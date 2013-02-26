#include <Utility/ConsoleInformation.h>

#include <sysutil/sysutil_common.h>
#include <sysutil/sysutil_licensearea.h>
#include <sysutil/sysutil_sysparam.h>

ConsoleRegion GetConsoleRegion()
{
	int licenseArea = cellSysutilGetLicenseArea();

	switch( licenseArea )
	{
	case CELL_SYSUTIL_LICENSE_AREA_J:
		return ConsoleRegion_JPN;
	case CELL_SYSUTIL_LICENSE_AREA_A:
		return ConsoleRegion_USA;
	case CELL_SYSUTIL_LICENSE_AREA_E:
		return ConsoleRegion_EUR;
	case CELL_SYSUTIL_LICENSE_AREA_H:
		return ConsoleRegion_TWN;		// FIXME: Check to make sure this mapping is correct.
	case CELL_SYSUTIL_LICENSE_AREA_K:
		return ConsoleRegion_KOR;
	case CELL_SYSUTIL_LICENSE_AREA_C:
		return ConsoleRegion_CHN;		// FIXME: Make sure this mapping is right too.
	default:
		break;
	}

	return ConsoleRegion_USA;
}

ConsoleLanguage GetConsoleLanguage()
{
	int language = 0;

	if( cellSysutilGetSystemParamInt( CELL_SYSUTIL_SYSTEMPARAM_ID_LANG, &language ) < 0 )
		return ConsoleLanguage_ENGLISH;

	switch( language )
	{
	case CELL_SYSUTIL_LANG_JAPANESE:
		return ConsoleLanguage_JAPANESE;
	case CELL_SYSUTIL_LANG_ENGLISH_US:
		return ConsoleLanguage_ENGLISH;
	case CELL_SYSUTIL_LANG_FRENCH:
		return ConsoleLanguage_FRENCH;
	case CELL_SYSUTIL_LANG_GERMAN:
		return ConsoleLanguage_GERMAN;
	case CELL_SYSUTIL_LANG_ITALIAN:
		return ConsoleLanguage_ITALIAN;
	case CELL_SYSUTIL_LANG_SPANISH:
		return ConsoleLanguage_SPANISH;
	case CELL_SYSUTIL_LANG_CHINESE_S:
		return ConsoleLanguage_CHINESE;
	case CELL_SYSUTIL_LANG_KOREAN:
		return ConsoleLanguage_KOREAN;
	case CELL_SYSUTIL_LANG_DUTCH:
		return ConsoleLanguage_DUTCH;
	case CELL_SYSUTIL_LANG_PORTUGUESE_PT:	// FIXME: Should these be the same languages?
	case CELL_SYSUTIL_LANG_PORTUGUESE_BR:
		return ConsoleLanguage_PORTUGUESE;
	case CELL_SYSUTIL_LANG_RUSSIAN:
		return ConsoleLanguage_RUSSIAN;
	default:
		break;
	}

	return ConsoleLanguage_ENGLISH;
}

int GetParentalControlLevel()
{
	int controlLevel;

	if( cellSysutilGetSystemParamInt( CELL_SYSUTIL_SYSTEMPARAM_ID_GAME_PARENTAL_LEVEL, &controlLevel ) < 0 )
		return -1;

	return controlLevel;
}

bool IsAsianButtonConfiguration()
{
	int assignButton;

	if( cellSysutilGetSystemParamInt( CELL_SYSUTIL_SYSTEMPARAM_ID_ENTER_BUTTON_ASSIGN, &assignButton ) < 0 )
		return false;

	switch( assignButton )
	{
	case CELL_SYSUTIL_ENTER_BUTTON_ASSIGN_CIRCLE:
		return true;
	case CELL_SYSUTIL_ENTER_BUTTON_ASSIGN_CROSS:
		break;
	}

	return false;
}