#include <Utility/ConsoleInformation.h>

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
	return -1;
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
