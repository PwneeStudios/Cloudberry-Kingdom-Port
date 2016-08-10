#ifndef GLOBALS
#define GLOBALS

#include <small_header.h>



namespace CloudberryKingdom
{

	struct Globals
	{

		static void InitializeStatics();

	
		enum Upgrade
		{
			Upgrade_FIREBALL,
			Upgrade_SPIKE,
			Upgrade_FALLING_BLOCK,
			Upgrade_FLY_BLOB,
			Upgrade_FIRE_SPINNER,
			Upgrade_MOVING_BLOCK,
			Upgrade_EMIT_BLOCK,
			Upgrade_FLOATER,
			Upgrade_FLOATER_SPIN,
			Upgrade_LASER,
			Upgrade_GHOST_BLOCK,
			Upgrade_BOUNCY_BLOCK,
			Upgrade_CLOUD,
			Upgrade_GENERAL,
			Upgrade_SPEED,
			Upgrade_JUMP,
			Upgrade_CEILING
		};
	
		static std::wstring ContentDirectory;

		static std::vector<Color> OnOffBlockColors;
		static std::vector<bool> ColorSwitch;

		static std::vector<std::wstring> UpgradeString;
	};

}


#endif	//#ifndef GLOBALS
