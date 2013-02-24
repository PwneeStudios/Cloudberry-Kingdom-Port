#ifndef _CONSOLE_INFORMATION_H_
#define _CONSOLE_INFORMATION_H_

enum ConsoleRegion
{
	ConsoleRegion_JPN,
	ConsoleRegion_USA,
	ConsoleRegion_EUR,
	ConsoleRegion_AUS,
	ConsoleRegion_CHN,
	ConsoleRegion_KOR,
	ConsoleRegion_TWN,
	ConsoleRegion_NUM_REGIONS,
};

enum ConsoleLanguage
{
	ConsoleLanguage_JAPANESE,
	ConsoleLanguage_ENGLISH,
	ConsoleLanguage_FRENCH,
	ConsoleLanguage_GERMAN,
	ConsoleLanguage_ITALIAN,
	ConsoleLanguage_SPANISH,
	ConsoleLanguage_CHINESE,
	ConsoleLanguage_KOREAN,
	ConsoleLanguage_DUTCH,
	ConsoleLanguage_PORTUGUESE,
	ConsoleLanguage_RUSSIAN,
	ConsoleLanguage_TAIWANESE,
	ConsoleLanguage_NUM_LANGUAGES,
};

/// Get console region.
/**
 * If no region is available, ConsoleRegion_USA is assumed.
 *
 * @returns Current console region.
 */
ConsoleRegion GetConsoleRegion();

/// Get console language.
/**
 * If no language is available, ConsoleLanguage_ENGLISH is assumed.
 *
 * @returns Current language.
 */
ConsoleLanguage GetConsoleLanguage();

/// Return level of parental control.
/**
 * A return value of 0 means there is no parental control.
 *
 * @returns Level of parental control. -1 if there was an error.
 */
int GetParentalControlLevel();

#endif
