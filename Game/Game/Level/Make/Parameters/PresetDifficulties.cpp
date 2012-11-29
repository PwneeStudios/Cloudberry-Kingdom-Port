#include <global_header.h>

namespace CloudberryKingdom
{

	std::shared_ptr<Upgrades> PresetUpgrades::GetUpgrade1()
	{
		std::shared_ptr<Upgrades> u = std::make_shared<Upgrades>();

		switch ( Tools::GlobalRnd->Rnd->Next( 0, 14 ) )
		{
			case 0:
				u->Get( Upgrade_JUMP ) = 1;
				u->Get( Upgrade_CEILING ) = 1;
				u->Get( Upgrade_GENERAL ) = 1;
				u->Get( Upgrade_SPEED ) = 1;
				u->Get( Upgrade_ELEVATOR ) = 0;
				u->Get( Upgrade_FALLING_BLOCK ) = 0;
				u->Get( Upgrade_FIREBALL ) = 1;
				u->Get( Upgrade_FIRE_SPINNER ) = 0;
				u->Get( Upgrade_SPIKEY_GUY ) = 0;
				u->Get( Upgrade_FLY_BLOB ) = 0;
				u->Get( Upgrade_GHOST_BLOCK ) = 0;
				u->Get( Upgrade_LASER ) = 0;
				u->Get( Upgrade_MOVING_BLOCK ) = 0;
				u->Get( Upgrade_SPIKE ) = 0;
				break;

			case 1:
				u->Get( Upgrade_JUMP ) = 1;
				u->Get( Upgrade_CEILING ) = 1;
				u->Get( Upgrade_GENERAL ) = 1;
				u->Get( Upgrade_SPEED ) = 1;
				u->Get( Upgrade_ELEVATOR ) = 0;
				u->Get( Upgrade_FALLING_BLOCK ) = 0;
				u->Get( Upgrade_FIREBALL ) = 0;
				u->Get( Upgrade_FIRE_SPINNER ) = 1;
				u->Get( Upgrade_SPIKEY_GUY ) = 0;
				u->Get( Upgrade_FLY_BLOB ) = 0;
				u->Get( Upgrade_GHOST_BLOCK ) = 0;
				u->Get( Upgrade_LASER ) = 0;
				u->Get( Upgrade_MOVING_BLOCK ) = 0;
				u->Get( Upgrade_SPIKE ) = 0;
				break;

			case 2:
				u->Get( Upgrade_JUMP ) = 1;
				u->Get( Upgrade_CEILING ) = 1;
				u->Get( Upgrade_GENERAL ) = 1;
				u->Get( Upgrade_SPEED ) = 1;
				u->Get( Upgrade_ELEVATOR ) = 0;
				u->Get( Upgrade_FALLING_BLOCK ) = 0;
				u->Get( Upgrade_FIREBALL ) = 0;
				u->Get( Upgrade_FIRE_SPINNER ) = 0;
				u->Get( Upgrade_SPIKEY_GUY ) = 1;
				u->Get( Upgrade_FLY_BLOB ) = 0;
				u->Get( Upgrade_GHOST_BLOCK ) = 0;
				u->Get( Upgrade_LASER ) = 0;
				u->Get( Upgrade_MOVING_BLOCK ) = 0;
				u->Get( Upgrade_SPIKE ) = 0;
				break;

			case 3:
				u->Get( Upgrade_JUMP ) = 1;
				u->Get( Upgrade_CEILING ) = 1;
				u->Get( Upgrade_GENERAL ) = 1;
				u->Get( Upgrade_SPEED ) = 1;
				u->Get( Upgrade_ELEVATOR ) = 0;
				u->Get( Upgrade_FALLING_BLOCK ) = 0;
				u->Get( Upgrade_FIREBALL ) = 0;
				u->Get( Upgrade_FIRE_SPINNER ) = 0;
				u->Get( Upgrade_SPIKEY_GUY ) = 0;
				u->Get( Upgrade_FLY_BLOB ) = 1;
				u->Get( Upgrade_GHOST_BLOCK ) = 0;
				u->Get( Upgrade_LASER ) = 0;
				u->Get( Upgrade_MOVING_BLOCK ) = 0;
				u->Get( Upgrade_SPIKE ) = 0;
				break;

			case 4:
				u->Get( Upgrade_JUMP ) = 1;
				u->Get( Upgrade_CEILING ) = 1;
				u->Get( Upgrade_GENERAL ) = 1;
				u->Get( Upgrade_SPEED ) = 1;
				u->Get( Upgrade_ELEVATOR ) = 0;
				u->Get( Upgrade_FALLING_BLOCK ) = 0;
				u->Get( Upgrade_FIREBALL ) = 0;
				u->Get( Upgrade_FIRE_SPINNER ) = 0;
				u->Get( Upgrade_SPIKEY_GUY ) = 0;
				u->Get( Upgrade_FLY_BLOB ) = 0;
				u->Get( Upgrade_GHOST_BLOCK ) = 1;
				u->Get( Upgrade_LASER ) = 0;
				u->Get( Upgrade_MOVING_BLOCK ) = 0;
				u->Get( Upgrade_SPIKE ) = 0;
				break;

			case 5:
				u->Get( Upgrade_JUMP ) = 1;
				u->Get( Upgrade_CEILING ) = 1;
				u->Get( Upgrade_GENERAL ) = 1;
				u->Get( Upgrade_SPEED ) = 1;
				u->Get( Upgrade_ELEVATOR ) = 0;
				u->Get( Upgrade_FALLING_BLOCK ) = 0;
				u->Get( Upgrade_FIREBALL ) = 0;
				u->Get( Upgrade_FIRE_SPINNER ) = 0;
				u->Get( Upgrade_SPIKEY_GUY ) = 0;
				u->Get( Upgrade_FLY_BLOB ) = 0;
				u->Get( Upgrade_GHOST_BLOCK ) = 0;
				u->Get( Upgrade_LASER ) = 1;
				u->Get( Upgrade_MOVING_BLOCK ) = 0;
				u->Get( Upgrade_SPIKE ) = 0;
				break;

			case 6:
				u->Get( Upgrade_JUMP ) = 1;
				u->Get( Upgrade_CEILING ) = 1;
				u->Get( Upgrade_GENERAL ) = 1;
				u->Get( Upgrade_SPEED ) = 1;
				u->Get( Upgrade_ELEVATOR ) = 0;
				u->Get( Upgrade_FALLING_BLOCK ) = 0;
				u->Get( Upgrade_FIREBALL ) = 0;
				u->Get( Upgrade_FIRE_SPINNER ) = 0;
				u->Get( Upgrade_SPIKEY_GUY ) = 0;
				u->Get( Upgrade_FLY_BLOB ) = 0;
				u->Get( Upgrade_GHOST_BLOCK ) = 0;
				u->Get( Upgrade_LASER ) = 0;
				u->Get( Upgrade_MOVING_BLOCK ) = 0;
				u->Get( Upgrade_SPIKE ) = 1;
				break;

			case 7:
				u->Get( Upgrade_JUMP ) = 1;
				u->Get( Upgrade_CEILING ) = 1;
				u->Get( Upgrade_GENERAL ) = 1;
				u->Get( Upgrade_SPEED ) = 1;
				u->Get( Upgrade_ELEVATOR ) = 0;
				u->Get( Upgrade_FALLING_BLOCK ) = 0;
				u->Get( Upgrade_FIREBALL ) = 1;
				u->Get( Upgrade_FIRE_SPINNER ) = 1;
				u->Get( Upgrade_SPIKEY_GUY ) = 0;
				u->Get( Upgrade_FLY_BLOB ) = 0;
				u->Get( Upgrade_GHOST_BLOCK ) = 0;
				u->Get( Upgrade_LASER ) = 0;
				u->Get( Upgrade_MOVING_BLOCK ) = 0;
				u->Get( Upgrade_SPIKE ) = 0;
				break;

			case 8:
				u->Get( Upgrade_JUMP ) = 1;
				u->Get( Upgrade_CEILING ) = 1;
				u->Get( Upgrade_GENERAL ) = 1;
				u->Get( Upgrade_SPEED ) = 1;
				u->Get( Upgrade_ELEVATOR ) = 0;
				u->Get( Upgrade_FALLING_BLOCK ) = 0;
				u->Get( Upgrade_FIREBALL ) = 0;
				u->Get( Upgrade_FIRE_SPINNER ) = 0;
				u->Get( Upgrade_SPIKEY_GUY ) = 0;
				u->Get( Upgrade_FLY_BLOB ) = 1;
				u->Get( Upgrade_GHOST_BLOCK ) = 0;
				u->Get( Upgrade_LASER ) = 0;
				u->Get( Upgrade_MOVING_BLOCK ) = 1;
				u->Get( Upgrade_SPIKE ) = 0;
				break;

			case 9:
				u->Get( Upgrade_JUMP ) = 1;
				u->Get( Upgrade_CEILING ) = 1;
				u->Get( Upgrade_GENERAL ) = 1;
				u->Get( Upgrade_SPEED ) = 1;
				u->Get( Upgrade_ELEVATOR ) = 0;
				u->Get( Upgrade_FALLING_BLOCK ) = 0;
				u->Get( Upgrade_FIREBALL ) = 0;
				u->Get( Upgrade_FIRE_SPINNER ) = 1;
				u->Get( Upgrade_SPIKEY_GUY ) = 0;
				u->Get( Upgrade_FLY_BLOB ) = 0;
				u->Get( Upgrade_GHOST_BLOCK ) = 0;
				u->Get( Upgrade_LASER ) = 0;
				u->Get( Upgrade_MOVING_BLOCK ) = 1;
				u->Get( Upgrade_SPIKE ) = 0;
				break;

			case 10:
				u->Get( Upgrade_JUMP ) = 1;
				u->Get( Upgrade_CEILING ) = 1;
				u->Get( Upgrade_GENERAL ) = 1;
				u->Get( Upgrade_SPEED ) = 1;
				u->Get( Upgrade_ELEVATOR ) = 0;
				u->Get( Upgrade_FALLING_BLOCK ) = 1;
				u->Get( Upgrade_FIREBALL ) = 0;
				u->Get( Upgrade_FIRE_SPINNER ) = 0;
				u->Get( Upgrade_SPIKEY_GUY ) = 0;
				u->Get( Upgrade_FLY_BLOB ) = 0;
				u->Get( Upgrade_GHOST_BLOCK ) = 0;
				u->Get( Upgrade_LASER ) = 0;
				u->Get( Upgrade_MOVING_BLOCK ) = 0;
				u->Get( Upgrade_SPIKE ) = 1;
				break;

			case 11:
				u->Get( Upgrade_JUMP ) = 1;
				u->Get( Upgrade_CEILING ) = 1;
				u->Get( Upgrade_GENERAL ) = 1;
				u->Get( Upgrade_SPEED ) = 1;
				u->Get( Upgrade_ELEVATOR ) = 0;
				u->Get( Upgrade_FALLING_BLOCK ) = 0;
				u->Get( Upgrade_FIREBALL ) = 0;
				u->Get( Upgrade_FIRE_SPINNER ) = 0;
				u->Get( Upgrade_SPIKEY_GUY ) = 0;
				u->Get( Upgrade_FLY_BLOB ) = 0;
				u->Get( Upgrade_GHOST_BLOCK ) = 1;
				u->Get( Upgrade_LASER ) = 1;
				u->Get( Upgrade_MOVING_BLOCK ) = 0;
				u->Get( Upgrade_SPIKE ) = 0;
				break;

			case 12:
				u->Get( Upgrade_JUMP ) = 1;
				u->Get( Upgrade_CEILING ) = 1;
				u->Get( Upgrade_GENERAL ) = 1;
				u->Get( Upgrade_SPEED ) = 1;
				u->Get( Upgrade_ELEVATOR ) = 0;
				u->Get( Upgrade_FALLING_BLOCK ) = 0;
				u->Get( Upgrade_FIREBALL ) = 0;
				u->Get( Upgrade_FIRE_SPINNER ) = 0;
				u->Get( Upgrade_SPIKEY_GUY ) = 1;
				u->Get( Upgrade_FLY_BLOB ) = 0;
				u->Get( Upgrade_GHOST_BLOCK ) = 0;
				u->Get( Upgrade_LASER ) = 0;
				u->Get( Upgrade_MOVING_BLOCK ) = 0;
				u->Get( Upgrade_SPIKE ) = 1;
				break;

			case 13:
				u->Get( Upgrade_JUMP ) = 1;
				u->Get( Upgrade_CEILING ) = 1;
				u->Get( Upgrade_GENERAL ) = 1;
				u->Get( Upgrade_SPEED ) = 1;
				u->Get( Upgrade_ELEVATOR ) = 0;
				u->Get( Upgrade_FALLING_BLOCK ) = 0;
				u->Get( Upgrade_FIREBALL ) = 0;
				u->Get( Upgrade_FIRE_SPINNER ) = 0;
				u->Get( Upgrade_SPIKEY_GUY ) = 1;
				u->Get( Upgrade_FLY_BLOB ) = 1;
				u->Get( Upgrade_GHOST_BLOCK ) = 0;
				u->Get( Upgrade_LASER ) = 0;
				u->Get( Upgrade_MOVING_BLOCK ) = 0;
				u->Get( Upgrade_SPIKE ) = 0;
				break;
		}

		return u;
	}

	std::shared_ptr<Upgrades> PresetUpgrades::GetUpgrade2()
	{
		std::shared_ptr<Upgrades> u = std::make_shared<Upgrades>();

		switch ( Tools::GlobalRnd->Rnd->Next( 1, 17 ) )
		{
			case 1:
				u->Get( Upgrade_JUMP ) = 0;
				u->Get( Upgrade_CEILING ) = 0;
				u->Get( Upgrade_GENERAL ) = 0;
				u->Get( Upgrade_SPEED ) = 0;
				u->Get( Upgrade_ELEVATOR ) = 1;
				u->Get( Upgrade_FALLING_BLOCK ) = 1;
				u->Get( Upgrade_FIREBALL ) = 1;
				u->Get( Upgrade_FIRE_SPINNER ) = 1;
				u->Get( Upgrade_SPIKEY_GUY ) = 1;
				u->Get( Upgrade_FLY_BLOB ) = 1;
				u->Get( Upgrade_GHOST_BLOCK ) = 1;
				u->Get( Upgrade_LASER ) = 1;
				u->Get( Upgrade_MOVING_BLOCK ) = 1;
				u->Get( Upgrade_SPIKE ) = 1;
				break;

			case 2:
				u->Get( Upgrade_JUMP ) = 3;
				u->Get( Upgrade_CEILING ) = 3;
				u->Get( Upgrade_GENERAL ) = 3;
				u->Get( Upgrade_SPEED ) = 3;
				u->Get( Upgrade_ELEVATOR ) = 0;
				u->Get( Upgrade_FALLING_BLOCK ) = 0;
				u->Get( Upgrade_FIREBALL ) = 3;
				u->Get( Upgrade_FIRE_SPINNER ) = 3;
				u->Get( Upgrade_SPIKEY_GUY ) = 0;
				u->Get( Upgrade_FLY_BLOB ) = 0;
				u->Get( Upgrade_GHOST_BLOCK ) = 0;
				u->Get( Upgrade_LASER ) = 0;
				u->Get( Upgrade_MOVING_BLOCK ) = 0;
				u->Get( Upgrade_SPIKE ) = 0;
				break;

			case 3:
				u->Get( Upgrade_JUMP ) = 3;
				u->Get( Upgrade_CEILING ) = 3;
				u->Get( Upgrade_GENERAL ) = 3;
				u->Get( Upgrade_SPEED ) = 3;
				u->Get( Upgrade_ELEVATOR ) = 0;
				u->Get( Upgrade_FALLING_BLOCK ) = 0;
				u->Get( Upgrade_FIREBALL ) = 0;
				u->Get( Upgrade_FIRE_SPINNER ) = 0;
				u->Get( Upgrade_SPIKEY_GUY ) = 0;
				u->Get( Upgrade_FLY_BLOB ) = 3;
				u->Get( Upgrade_GHOST_BLOCK ) = 0;
				u->Get( Upgrade_LASER ) = 0;
				u->Get( Upgrade_MOVING_BLOCK ) = 3;
				u->Get( Upgrade_SPIKE ) = 0;
				break;

			case 4:
				u->Get( Upgrade_JUMP ) = 3;
				u->Get( Upgrade_CEILING ) = 3;
				u->Get( Upgrade_GENERAL ) = 3;
				u->Get( Upgrade_SPEED ) = 3;
				u->Get( Upgrade_ELEVATOR ) = 0;
				u->Get( Upgrade_FALLING_BLOCK ) = 0;
				u->Get( Upgrade_FIREBALL ) = 0;
				u->Get( Upgrade_FIRE_SPINNER ) = 3;
				u->Get( Upgrade_SPIKEY_GUY ) = 0;
				u->Get( Upgrade_FLY_BLOB ) = 0;
				u->Get( Upgrade_GHOST_BLOCK ) = 0;
				u->Get( Upgrade_LASER ) = 0;
				u->Get( Upgrade_MOVING_BLOCK ) = 3;
				u->Get( Upgrade_SPIKE ) = 0;
				break;

			case 5:
				u->Get( Upgrade_JUMP ) = 3;
				u->Get( Upgrade_CEILING ) = 3;
				u->Get( Upgrade_GENERAL ) = 3;
				u->Get( Upgrade_SPEED ) = 3;
				u->Get( Upgrade_ELEVATOR ) = 0;
				u->Get( Upgrade_FALLING_BLOCK ) = 3;
				u->Get( Upgrade_FIREBALL ) = 0;
				u->Get( Upgrade_FIRE_SPINNER ) = 0;
				u->Get( Upgrade_SPIKEY_GUY ) = 0;
				u->Get( Upgrade_FLY_BLOB ) = 0;
				u->Get( Upgrade_GHOST_BLOCK ) = 0;
				u->Get( Upgrade_LASER ) = 0;
				u->Get( Upgrade_MOVING_BLOCK ) = 0;
				u->Get( Upgrade_SPIKE ) = 3;
				break;

			case 6:
				u->Get( Upgrade_JUMP ) = 3;
				u->Get( Upgrade_CEILING ) = 3;
				u->Get( Upgrade_GENERAL ) = 3;
				u->Get( Upgrade_SPEED ) = 3;
				u->Get( Upgrade_ELEVATOR ) = 0;
				u->Get( Upgrade_FALLING_BLOCK ) = 0;
				u->Get( Upgrade_FIREBALL ) = 0;
				u->Get( Upgrade_FIRE_SPINNER ) = 0;
				u->Get( Upgrade_SPIKEY_GUY ) = 0;
				u->Get( Upgrade_FLY_BLOB ) = 0;
				u->Get( Upgrade_GHOST_BLOCK ) = 3;
				u->Get( Upgrade_LASER ) = 3;
				u->Get( Upgrade_MOVING_BLOCK ) = 0;
				u->Get( Upgrade_SPIKE ) = 0;
				break;

			case 7:
				u->Get( Upgrade_JUMP ) = 3;
				u->Get( Upgrade_CEILING ) = 3;
				u->Get( Upgrade_GENERAL ) = 3;
				u->Get( Upgrade_SPEED ) = 3;
				u->Get( Upgrade_ELEVATOR ) = 0;
				u->Get( Upgrade_FALLING_BLOCK ) = 0;
				u->Get( Upgrade_FIREBALL ) = 0;
				u->Get( Upgrade_FIRE_SPINNER ) = 0;
				u->Get( Upgrade_SPIKEY_GUY ) = 3;
				u->Get( Upgrade_FLY_BLOB ) = 0;
				u->Get( Upgrade_GHOST_BLOCK ) = 0;
				u->Get( Upgrade_LASER ) = 0;
				u->Get( Upgrade_MOVING_BLOCK ) = 0;
				u->Get( Upgrade_SPIKE ) = 3;
				break;

			case 8:
				u->Get( Upgrade_JUMP ) = 3;
				u->Get( Upgrade_CEILING ) = 3;
				u->Get( Upgrade_GENERAL ) = 3;
				u->Get( Upgrade_SPEED ) = 3;
				u->Get( Upgrade_ELEVATOR ) = 0;
				u->Get( Upgrade_FALLING_BLOCK ) = 0;
				u->Get( Upgrade_FIREBALL ) = 0;
				u->Get( Upgrade_FIRE_SPINNER ) = 0;
				u->Get( Upgrade_SPIKEY_GUY ) = 3;
				u->Get( Upgrade_FLY_BLOB ) = 3;
				u->Get( Upgrade_GHOST_BLOCK ) = 0;
				u->Get( Upgrade_LASER ) = 0;
				u->Get( Upgrade_MOVING_BLOCK ) = 0;
				u->Get( Upgrade_SPIKE ) = 0;
				break;

			case 9:
				u->Get( Upgrade_JUMP ) = 3;
				u->Get( Upgrade_CEILING ) = 3;
				u->Get( Upgrade_GENERAL ) = 3;
				u->Get( Upgrade_SPEED ) = 3;
				u->Get( Upgrade_ELEVATOR ) = 0;
				u->Get( Upgrade_FALLING_BLOCK ) = 3;
				u->Get( Upgrade_FIREBALL ) = 0;
				u->Get( Upgrade_FIRE_SPINNER ) = 0;
				u->Get( Upgrade_SPIKEY_GUY ) = 0;
				u->Get( Upgrade_FLY_BLOB ) = 3;
				u->Get( Upgrade_GHOST_BLOCK ) = 0;
				u->Get( Upgrade_LASER ) = 0;
				u->Get( Upgrade_MOVING_BLOCK ) = 3;
				u->Get( Upgrade_SPIKE ) = 0;
				break;

			case 10:
				u->Get( Upgrade_JUMP ) = 3;
				u->Get( Upgrade_CEILING ) = 3;
				u->Get( Upgrade_GENERAL ) = 3;
				u->Get( Upgrade_SPEED ) = 3;
				u->Get( Upgrade_ELEVATOR ) = 0;
				u->Get( Upgrade_FALLING_BLOCK ) = 0;
				u->Get( Upgrade_FIREBALL ) = 0;
				u->Get( Upgrade_FIRE_SPINNER ) = 0;
				u->Get( Upgrade_SPIKEY_GUY ) = 0;
				u->Get( Upgrade_FLY_BLOB ) = 3;
				u->Get( Upgrade_GHOST_BLOCK ) = 3;
				u->Get( Upgrade_LASER ) = 0;
				u->Get( Upgrade_MOVING_BLOCK ) = 3;
				u->Get( Upgrade_SPIKE ) = 0;
				break;

			case 11:
				u->Get( Upgrade_JUMP ) = 3;
				u->Get( Upgrade_CEILING ) = 3;
				u->Get( Upgrade_GENERAL ) = 3;
				u->Get( Upgrade_SPEED ) = 3;
				u->Get( Upgrade_ELEVATOR ) = 0;
				u->Get( Upgrade_FALLING_BLOCK ) = 3;
				u->Get( Upgrade_FIREBALL ) = 0;
				u->Get( Upgrade_FIRE_SPINNER ) = 0;
				u->Get( Upgrade_SPIKEY_GUY ) = 0;
				u->Get( Upgrade_FLY_BLOB ) = 0;
				u->Get( Upgrade_GHOST_BLOCK ) = 3;
				u->Get( Upgrade_LASER ) = 0;
				u->Get( Upgrade_MOVING_BLOCK ) = 3;
				u->Get( Upgrade_SPIKE ) = 0;
				break;

			case 12:
				u->Get( Upgrade_JUMP ) = 3;
				u->Get( Upgrade_CEILING ) = 3;
				u->Get( Upgrade_GENERAL ) = 3;
				u->Get( Upgrade_SPEED ) = 3;
				u->Get( Upgrade_ELEVATOR ) = 0;
				u->Get( Upgrade_FALLING_BLOCK ) = 0;
				u->Get( Upgrade_FIREBALL ) = 3;
				u->Get( Upgrade_FIRE_SPINNER ) = 3;
				u->Get( Upgrade_SPIKEY_GUY ) = 0;
				u->Get( Upgrade_FLY_BLOB ) = 0;
				u->Get( Upgrade_GHOST_BLOCK ) = 0;
				u->Get( Upgrade_LASER ) = 3;
				u->Get( Upgrade_MOVING_BLOCK ) = 0;
				u->Get( Upgrade_SPIKE ) = 0;
				break;

			case 13:
				u->Get( Upgrade_JUMP ) = 3;
				u->Get( Upgrade_CEILING ) = 3;
				u->Get( Upgrade_GENERAL ) = 3;
				u->Get( Upgrade_SPEED ) = 3;
				u->Get( Upgrade_ELEVATOR ) = 0;
				u->Get( Upgrade_FALLING_BLOCK ) = 0;
				u->Get( Upgrade_FIREBALL ) = 3;
				u->Get( Upgrade_FIRE_SPINNER ) = 3;
				u->Get( Upgrade_SPIKEY_GUY ) = 0;
				u->Get( Upgrade_FLY_BLOB ) = 0;
				u->Get( Upgrade_GHOST_BLOCK ) = 0;
				u->Get( Upgrade_LASER ) = 0;
				u->Get( Upgrade_MOVING_BLOCK ) = 3;
				u->Get( Upgrade_SPIKE ) = 0;
				break;

			case 14:
				u->Get( Upgrade_JUMP ) = 3;
				u->Get( Upgrade_CEILING ) = 3;
				u->Get( Upgrade_GENERAL ) = 3;
				u->Get( Upgrade_SPEED ) = 3;
				u->Get( Upgrade_ELEVATOR ) = 0;
				u->Get( Upgrade_FALLING_BLOCK ) = 3;
				u->Get( Upgrade_FIREBALL ) = 0;
				u->Get( Upgrade_FIRE_SPINNER ) = 0;
				u->Get( Upgrade_SPIKEY_GUY ) = 3;
				u->Get( Upgrade_FLY_BLOB ) = 0;
				u->Get( Upgrade_GHOST_BLOCK ) = 0;
				u->Get( Upgrade_LASER ) = 0;
				u->Get( Upgrade_MOVING_BLOCK ) = 3;
				u->Get( Upgrade_SPIKE ) = 0;
				break;

			case 15:
				u->Get( Upgrade_JUMP ) = 3;
				u->Get( Upgrade_CEILING ) = 3;
				u->Get( Upgrade_GENERAL ) = 3;
				u->Get( Upgrade_SPEED ) = 3;
				u->Get( Upgrade_ELEVATOR ) = 0;
				u->Get( Upgrade_FALLING_BLOCK ) = 3;
				u->Get( Upgrade_FIREBALL ) = 0;
				u->Get( Upgrade_FIRE_SPINNER ) = 0;
				u->Get( Upgrade_SPIKEY_GUY ) = 0;
				u->Get( Upgrade_FLY_BLOB ) = 0;
				u->Get( Upgrade_GHOST_BLOCK ) = 0;
				u->Get( Upgrade_LASER ) = 0;
				u->Get( Upgrade_MOVING_BLOCK ) = 3;
				u->Get( Upgrade_SPIKE ) = 3;
				break;

			case 16:
				u->Get( Upgrade_JUMP ) = 3;
				u->Get( Upgrade_CEILING ) = 3;
				u->Get( Upgrade_GENERAL ) = 3;
				u->Get( Upgrade_SPEED ) = 3;
				u->Get( Upgrade_ELEVATOR ) = 0;
				u->Get( Upgrade_FALLING_BLOCK ) = 0;
				u->Get( Upgrade_FIREBALL ) = 0;
				u->Get( Upgrade_FIRE_SPINNER ) = 0;
				u->Get( Upgrade_SPIKEY_GUY ) = 3;
				u->Get( Upgrade_FLY_BLOB ) = 0;
				u->Get( Upgrade_GHOST_BLOCK ) = 3;
				u->Get( Upgrade_LASER ) = 3;
				u->Get( Upgrade_MOVING_BLOCK ) = 0;
				u->Get( Upgrade_SPIKE ) = 0;
				break;
		}

		return u;
	}

	std::shared_ptr<Upgrades> PresetUpgrades::GetUpgrade3()
	{
		std::shared_ptr<Upgrades> u = std::make_shared<Upgrades>();

		switch ( Tools::GlobalRnd->Rnd->Next( 0, 25 ) )
		{
			case 0:
				u->Get( Upgrade_JUMP ) = 2;
				u->Get( Upgrade_CEILING ) = 2;
				u->Get( Upgrade_GENERAL ) = 2;
				u->Get( Upgrade_SPEED ) = 2;
				u->Get( Upgrade_ELEVATOR ) = 3;
				u->Get( Upgrade_FALLING_BLOCK ) = 3;
				u->Get( Upgrade_FIREBALL ) = 3;
				u->Get( Upgrade_FIRE_SPINNER ) = 3;
				u->Get( Upgrade_SPIKEY_GUY ) = 3;
				u->Get( Upgrade_FLY_BLOB ) = 3;
				u->Get( Upgrade_GHOST_BLOCK ) = 3;
				u->Get( Upgrade_LASER ) = 3;
				u->Get( Upgrade_MOVING_BLOCK ) = 3;
				u->Get( Upgrade_SPIKE ) = 3;
				break;

			case 1:
				u->Get( Upgrade_JUMP ) = 5;
				u->Get( Upgrade_CEILING ) = 5;
				u->Get( Upgrade_GENERAL ) = 5;
				u->Get( Upgrade_SPEED ) = 5;
				u->Get( Upgrade_ELEVATOR ) = 0;
				u->Get( Upgrade_FALLING_BLOCK ) = 5;
				u->Get( Upgrade_FIREBALL ) = 0;
				u->Get( Upgrade_FIRE_SPINNER ) = 0;
				u->Get( Upgrade_SPIKEY_GUY ) = 0;
				u->Get( Upgrade_FLY_BLOB ) = 5;
				u->Get( Upgrade_GHOST_BLOCK ) = 0;
				u->Get( Upgrade_LASER ) = 0;
				u->Get( Upgrade_MOVING_BLOCK ) = 5;
				u->Get( Upgrade_SPIKE ) = 0;
				break;

			case 2:
				u->Get( Upgrade_JUMP ) = 5;
				u->Get( Upgrade_CEILING ) = 5;
				u->Get( Upgrade_GENERAL ) = 5;
				u->Get( Upgrade_SPEED ) = 5;
				u->Get( Upgrade_ELEVATOR ) = 0;
				u->Get( Upgrade_FALLING_BLOCK ) = 0;
				u->Get( Upgrade_FIREBALL ) = 0;
				u->Get( Upgrade_FIRE_SPINNER ) = 0;
				u->Get( Upgrade_SPIKEY_GUY ) = 0;
				u->Get( Upgrade_FLY_BLOB ) = 5;
				u->Get( Upgrade_GHOST_BLOCK ) = 5;
				u->Get( Upgrade_LASER ) = 0;
				u->Get( Upgrade_MOVING_BLOCK ) = 5;
				u->Get( Upgrade_SPIKE ) = 0;
				break;

			case 3:
				u->Get( Upgrade_JUMP ) = 5;
				u->Get( Upgrade_CEILING ) = 5;
				u->Get( Upgrade_GENERAL ) = 5;
				u->Get( Upgrade_SPEED ) = 5;
				u->Get( Upgrade_ELEVATOR ) = 0;
				u->Get( Upgrade_FALLING_BLOCK ) = 5;
				u->Get( Upgrade_FIREBALL ) = 0;
				u->Get( Upgrade_FIRE_SPINNER ) = 0;
				u->Get( Upgrade_SPIKEY_GUY ) = 0;
				u->Get( Upgrade_FLY_BLOB ) = 0;
				u->Get( Upgrade_GHOST_BLOCK ) = 5;
				u->Get( Upgrade_LASER ) = 0;
				u->Get( Upgrade_MOVING_BLOCK ) = 5;
				u->Get( Upgrade_SPIKE ) = 0;
				break;

			case 4:
				u->Get( Upgrade_JUMP ) = 5;
				u->Get( Upgrade_CEILING ) = 5;
				u->Get( Upgrade_GENERAL ) = 5;
				u->Get( Upgrade_SPEED ) = 5;
				u->Get( Upgrade_ELEVATOR ) = 0;
				u->Get( Upgrade_FALLING_BLOCK ) = 0;
				u->Get( Upgrade_FIREBALL ) = 5;
				u->Get( Upgrade_FIRE_SPINNER ) = 5;
				u->Get( Upgrade_SPIKEY_GUY ) = 0;
				u->Get( Upgrade_FLY_BLOB ) = 0;
				u->Get( Upgrade_GHOST_BLOCK ) = 0;
				u->Get( Upgrade_LASER ) = 5;
				u->Get( Upgrade_MOVING_BLOCK ) = 0;
				u->Get( Upgrade_SPIKE ) = 0;
				break;

			case 5:
				u->Get( Upgrade_JUMP ) = 5;
				u->Get( Upgrade_CEILING ) = 5;
				u->Get( Upgrade_GENERAL ) = 5;
				u->Get( Upgrade_SPEED ) = 5;
				u->Get( Upgrade_ELEVATOR ) = 0;
				u->Get( Upgrade_FALLING_BLOCK ) = 0;
				u->Get( Upgrade_FIREBALL ) = 5;
				u->Get( Upgrade_FIRE_SPINNER ) = 5;
				u->Get( Upgrade_SPIKEY_GUY ) = 0;
				u->Get( Upgrade_FLY_BLOB ) = 0;
				u->Get( Upgrade_GHOST_BLOCK ) = 0;
				u->Get( Upgrade_LASER ) = 0;
				u->Get( Upgrade_MOVING_BLOCK ) = 5;
				u->Get( Upgrade_SPIKE ) = 0;
				break;

			case 6:
				u->Get( Upgrade_JUMP ) = 5;
				u->Get( Upgrade_CEILING ) = 5;
				u->Get( Upgrade_GENERAL ) = 5;
				u->Get( Upgrade_SPEED ) = 5;
				u->Get( Upgrade_ELEVATOR ) = 0;
				u->Get( Upgrade_FALLING_BLOCK ) = 5;
				u->Get( Upgrade_FIREBALL ) = 0;
				u->Get( Upgrade_FIRE_SPINNER ) = 0;
				u->Get( Upgrade_SPIKEY_GUY ) = 5;
				u->Get( Upgrade_FLY_BLOB ) = 0;
				u->Get( Upgrade_GHOST_BLOCK ) = 0;
				u->Get( Upgrade_LASER ) = 0;
				u->Get( Upgrade_MOVING_BLOCK ) = 5;
				u->Get( Upgrade_SPIKE ) = 0;
				break;

			case 7:
				u->Get( Upgrade_JUMP ) = 5;
				u->Get( Upgrade_CEILING ) = 5;
				u->Get( Upgrade_GENERAL ) = 5;
				u->Get( Upgrade_SPEED ) = 5;
				u->Get( Upgrade_ELEVATOR ) = 0;
				u->Get( Upgrade_FALLING_BLOCK ) = 5;
				u->Get( Upgrade_FIREBALL ) = 0;
				u->Get( Upgrade_FIRE_SPINNER ) = 0;
				u->Get( Upgrade_SPIKEY_GUY ) = 0;
				u->Get( Upgrade_FLY_BLOB ) = 0;
				u->Get( Upgrade_GHOST_BLOCK ) = 0;
				u->Get( Upgrade_LASER ) = 0;
				u->Get( Upgrade_MOVING_BLOCK ) = 5;
				u->Get( Upgrade_SPIKE ) = 5;
				break;

			case 8:
				u->Get( Upgrade_JUMP ) = 5;
				u->Get( Upgrade_CEILING ) = 5;
				u->Get( Upgrade_GENERAL ) = 5;
				u->Get( Upgrade_SPEED ) = 5;
				u->Get( Upgrade_ELEVATOR ) = 0;
				u->Get( Upgrade_FALLING_BLOCK ) = 0;
				u->Get( Upgrade_FIREBALL ) = 0;
				u->Get( Upgrade_FIRE_SPINNER ) = 0;
				u->Get( Upgrade_SPIKEY_GUY ) = 5;
				u->Get( Upgrade_FLY_BLOB ) = 0;
				u->Get( Upgrade_GHOST_BLOCK ) = 5;
				u->Get( Upgrade_LASER ) = 5;
				u->Get( Upgrade_MOVING_BLOCK ) = 0;
				u->Get( Upgrade_SPIKE ) = 0;
				break;

			case 9:
				u->Get( Upgrade_JUMP ) = 5;
				u->Get( Upgrade_CEILING ) = 5;
				u->Get( Upgrade_GENERAL ) = 5;
				u->Get( Upgrade_SPEED ) = 5;
				u->Get( Upgrade_ELEVATOR ) = 0;
				u->Get( Upgrade_FALLING_BLOCK ) = 5;
				u->Get( Upgrade_FIREBALL ) = 0;
				u->Get( Upgrade_FIRE_SPINNER ) = 0;
				u->Get( Upgrade_SPIKEY_GUY ) = 5;
				u->Get( Upgrade_FLY_BLOB ) = 5;
				u->Get( Upgrade_GHOST_BLOCK ) = 0;
				u->Get( Upgrade_LASER ) = 0;
				u->Get( Upgrade_MOVING_BLOCK ) = 5;
				u->Get( Upgrade_SPIKE ) = 0;
				break;

			case 10:
				u->Get( Upgrade_JUMP ) = 5;
				u->Get( Upgrade_CEILING ) = 5;
				u->Get( Upgrade_GENERAL ) = 5;
				u->Get( Upgrade_SPEED ) = 5;
				u->Get( Upgrade_ELEVATOR ) = 0;
				u->Get( Upgrade_FALLING_BLOCK ) = 0;
				u->Get( Upgrade_FIREBALL ) = 0;
				u->Get( Upgrade_FIRE_SPINNER ) = 0;
				u->Get( Upgrade_SPIKEY_GUY ) = 0;
				u->Get( Upgrade_FLY_BLOB ) = 5;
				u->Get( Upgrade_GHOST_BLOCK ) = 5;
				u->Get( Upgrade_LASER ) = 0;
				u->Get( Upgrade_MOVING_BLOCK ) = 5;
				u->Get( Upgrade_SPIKE ) = 5;
				break;

			case 11:
				u->Get( Upgrade_JUMP ) = 5;
				u->Get( Upgrade_CEILING ) = 5;
				u->Get( Upgrade_GENERAL ) = 5;
				u->Get( Upgrade_SPEED ) = 5;
				u->Get( Upgrade_ELEVATOR ) = 0;
				u->Get( Upgrade_FALLING_BLOCK ) = 5;
				u->Get( Upgrade_FIREBALL ) = 0;
				u->Get( Upgrade_FIRE_SPINNER ) = 5;
				u->Get( Upgrade_SPIKEY_GUY ) = 0;
				u->Get( Upgrade_FLY_BLOB ) = 0;
				u->Get( Upgrade_GHOST_BLOCK ) = 5;
				u->Get( Upgrade_LASER ) = 0;
				u->Get( Upgrade_MOVING_BLOCK ) = 5;
				u->Get( Upgrade_SPIKE ) = 0;
				break;

			case 12:
				u->Get( Upgrade_JUMP ) = 5;
				u->Get( Upgrade_CEILING ) = 5;
				u->Get( Upgrade_GENERAL ) = 5;
				u->Get( Upgrade_SPEED ) = 5;
				u->Get( Upgrade_ELEVATOR ) = 0;
				u->Get( Upgrade_FALLING_BLOCK ) = 0;
				u->Get( Upgrade_FIREBALL ) = 5;
				u->Get( Upgrade_FIRE_SPINNER ) = 5;
				u->Get( Upgrade_SPIKEY_GUY ) = 5;
				u->Get( Upgrade_FLY_BLOB ) = 0;
				u->Get( Upgrade_GHOST_BLOCK ) = 0;
				u->Get( Upgrade_LASER ) = 5;
				u->Get( Upgrade_MOVING_BLOCK ) = 0;
				u->Get( Upgrade_SPIKE ) = 0;
				break;

			case 13:
				u->Get( Upgrade_JUMP ) = 5;
				u->Get( Upgrade_CEILING ) = 5;
				u->Get( Upgrade_GENERAL ) = 5;
				u->Get( Upgrade_SPEED ) = 5;
				u->Get( Upgrade_ELEVATOR ) = 0;
				u->Get( Upgrade_FALLING_BLOCK ) = 5;
				u->Get( Upgrade_FIREBALL ) = 5;
				u->Get( Upgrade_FIRE_SPINNER ) = 5;
				u->Get( Upgrade_SPIKEY_GUY ) = 0;
				u->Get( Upgrade_FLY_BLOB ) = 0;
				u->Get( Upgrade_GHOST_BLOCK ) = 0;
				u->Get( Upgrade_LASER ) = 0;
				u->Get( Upgrade_MOVING_BLOCK ) = 5;
				u->Get( Upgrade_SPIKE ) = 0;
				break;

			case 14:
				u->Get( Upgrade_JUMP ) = 5;
				u->Get( Upgrade_CEILING ) = 5;
				u->Get( Upgrade_GENERAL ) = 5;
				u->Get( Upgrade_SPEED ) = 5;
				u->Get( Upgrade_ELEVATOR ) = 0;
				u->Get( Upgrade_FALLING_BLOCK ) = 5;
				u->Get( Upgrade_FIREBALL ) = 0;
				u->Get( Upgrade_FIRE_SPINNER ) = 0;
				u->Get( Upgrade_SPIKEY_GUY ) = 5;
				u->Get( Upgrade_FLY_BLOB ) = 0;
				u->Get( Upgrade_GHOST_BLOCK ) = 0;
				u->Get( Upgrade_LASER ) = 5;
				u->Get( Upgrade_MOVING_BLOCK ) = 5;
				u->Get( Upgrade_SPIKE ) = 0;
				break;

			case 15:
				u->Get( Upgrade_JUMP ) = 5;
				u->Get( Upgrade_CEILING ) = 5;
				u->Get( Upgrade_GENERAL ) = 5;
				u->Get( Upgrade_SPEED ) = 5;
				u->Get( Upgrade_ELEVATOR ) = 0;
				u->Get( Upgrade_FALLING_BLOCK ) = 5;
				u->Get( Upgrade_FIREBALL ) = 0;
				u->Get( Upgrade_FIRE_SPINNER ) = 0;
				u->Get( Upgrade_SPIKEY_GUY ) = 0;
				u->Get( Upgrade_FLY_BLOB ) = 5;
				u->Get( Upgrade_GHOST_BLOCK ) = 0;
				u->Get( Upgrade_LASER ) = 0;
				u->Get( Upgrade_MOVING_BLOCK ) = 5;
				u->Get( Upgrade_SPIKE ) = 5;
				break;

			case 16:
				u->Get( Upgrade_JUMP ) = 5;
				u->Get( Upgrade_CEILING ) = 5;
				u->Get( Upgrade_GENERAL ) = 5;
				u->Get( Upgrade_SPEED ) = 5;
				u->Get( Upgrade_ELEVATOR ) = 5;
				u->Get( Upgrade_FALLING_BLOCK ) = 0;
				u->Get( Upgrade_FIREBALL ) = 0;
				u->Get( Upgrade_FIRE_SPINNER ) = 0;
				u->Get( Upgrade_SPIKEY_GUY ) = 5;
				u->Get( Upgrade_FLY_BLOB ) = 0;
				u->Get( Upgrade_GHOST_BLOCK ) = 5;
				u->Get( Upgrade_LASER ) = 5;
				u->Get( Upgrade_MOVING_BLOCK ) = 0;
				u->Get( Upgrade_SPIKE ) = 0;
				break;

			case 17:
				u->Get( Upgrade_JUMP ) = 5;
				u->Get( Upgrade_CEILING ) = 5;
				u->Get( Upgrade_GENERAL ) = 7;
				u->Get( Upgrade_SPEED ) = 7;
				u->Get( Upgrade_ELEVATOR ) = 0;
				u->Get( Upgrade_FALLING_BLOCK ) = 7;
				u->Get( Upgrade_FIREBALL ) = 0;
				u->Get( Upgrade_FIRE_SPINNER ) = 0;
				u->Get( Upgrade_SPIKEY_GUY ) = 0;
				u->Get( Upgrade_FLY_BLOB ) = 7;
				u->Get( Upgrade_GHOST_BLOCK ) = 0;
				u->Get( Upgrade_LASER ) = 0;
				u->Get( Upgrade_MOVING_BLOCK ) = 0;
				u->Get( Upgrade_SPIKE ) = 0;
				break;

			case 18:
				u->Get( Upgrade_JUMP ) = 5;
				u->Get( Upgrade_CEILING ) = 5;
				u->Get( Upgrade_GENERAL ) = 7;
				u->Get( Upgrade_SPEED ) = 7;
				u->Get( Upgrade_ELEVATOR ) = 0;
				u->Get( Upgrade_FALLING_BLOCK ) = 0;
				u->Get( Upgrade_FIREBALL ) = 0;
				u->Get( Upgrade_FIRE_SPINNER ) = 0;
				u->Get( Upgrade_SPIKEY_GUY ) = 0;
				u->Get( Upgrade_FLY_BLOB ) = 7;
				u->Get( Upgrade_GHOST_BLOCK ) = 0;
				u->Get( Upgrade_LASER ) = 0;
				u->Get( Upgrade_MOVING_BLOCK ) = 7;
				u->Get( Upgrade_SPIKE ) = 0;
				break;

			case 19:
				u->Get( Upgrade_JUMP ) = 5;
				u->Get( Upgrade_CEILING ) = 5;
				u->Get( Upgrade_GENERAL ) = 7;
				u->Get( Upgrade_SPEED ) = 7;
				u->Get( Upgrade_ELEVATOR ) = 0;
				u->Get( Upgrade_FALLING_BLOCK ) = 3;
				u->Get( Upgrade_FIREBALL ) = 0;
				u->Get( Upgrade_FIRE_SPINNER ) = 0;
				u->Get( Upgrade_SPIKEY_GUY ) = 0;
				u->Get( Upgrade_FLY_BLOB ) = 0;
				u->Get( Upgrade_GHOST_BLOCK ) = 7;
				u->Get( Upgrade_LASER ) = 0;
				u->Get( Upgrade_MOVING_BLOCK ) = 7;
				u->Get( Upgrade_SPIKE ) = 0;
				break;

			case 20:
				u->Get( Upgrade_JUMP ) = 5;
				u->Get( Upgrade_CEILING ) = 5;
				u->Get( Upgrade_GENERAL ) = 7;
				u->Get( Upgrade_SPEED ) = 7;
				u->Get( Upgrade_ELEVATOR ) = 0;
				u->Get( Upgrade_FALLING_BLOCK ) = 0;
				u->Get( Upgrade_FIREBALL ) = 7;
				u->Get( Upgrade_FIRE_SPINNER ) = 7;
				u->Get( Upgrade_SPIKEY_GUY ) = 0;
				u->Get( Upgrade_FLY_BLOB ) = 0;
				u->Get( Upgrade_GHOST_BLOCK ) = 0;
				u->Get( Upgrade_LASER ) = 0;
				u->Get( Upgrade_MOVING_BLOCK ) = 0;
				u->Get( Upgrade_SPIKE ) = 0;
				break;

			case 21:
				u->Get( Upgrade_JUMP ) = 5;
				u->Get( Upgrade_CEILING ) = 5;
				u->Get( Upgrade_GENERAL ) = 7;
				u->Get( Upgrade_SPEED ) = 7;
				u->Get( Upgrade_ELEVATOR ) = 0;
				u->Get( Upgrade_FALLING_BLOCK ) = 0;
				u->Get( Upgrade_FIREBALL ) = 0;
				u->Get( Upgrade_FIRE_SPINNER ) = 7;
				u->Get( Upgrade_SPIKEY_GUY ) = 0;
				u->Get( Upgrade_FLY_BLOB ) = 0;
				u->Get( Upgrade_GHOST_BLOCK ) = 0;
				u->Get( Upgrade_LASER ) = 0;
				u->Get( Upgrade_MOVING_BLOCK ) = 7;
				u->Get( Upgrade_SPIKE ) = 0;
				break;

			case 22:
				u->Get( Upgrade_JUMP ) = 5;
				u->Get( Upgrade_CEILING ) = 5;
				u->Get( Upgrade_GENERAL ) = 7;
				u->Get( Upgrade_SPEED ) = 7;
				u->Get( Upgrade_ELEVATOR ) = 0;
				u->Get( Upgrade_FALLING_BLOCK ) = 7;
				u->Get( Upgrade_FIREBALL ) = 0;
				u->Get( Upgrade_FIRE_SPINNER ) = 0;
				u->Get( Upgrade_SPIKEY_GUY ) = 7;
				u->Get( Upgrade_FLY_BLOB ) = 0;
				u->Get( Upgrade_GHOST_BLOCK ) = 0;
				u->Get( Upgrade_LASER ) = 0;
				u->Get( Upgrade_MOVING_BLOCK ) = 0;
				u->Get( Upgrade_SPIKE ) = 0;
				break;

			case 23:
				u->Get( Upgrade_JUMP ) = 5;
				u->Get( Upgrade_CEILING ) = 5;
				u->Get( Upgrade_GENERAL ) = 7;
				u->Get( Upgrade_SPEED ) = 7;
				u->Get( Upgrade_ELEVATOR ) = 0;
				u->Get( Upgrade_FALLING_BLOCK ) = 7;
				u->Get( Upgrade_FIREBALL ) = 0;
				u->Get( Upgrade_FIRE_SPINNER ) = 0;
				u->Get( Upgrade_SPIKEY_GUY ) = 0;
				u->Get( Upgrade_FLY_BLOB ) = 0;
				u->Get( Upgrade_GHOST_BLOCK ) = 0;
				u->Get( Upgrade_LASER ) = 0;
				u->Get( Upgrade_MOVING_BLOCK ) = 0;
				u->Get( Upgrade_SPIKE ) = 7;
				break;

			case 24:
				u->Get( Upgrade_JUMP ) = 5;
				u->Get( Upgrade_CEILING ) = 5;
				u->Get( Upgrade_GENERAL ) = 7;
				u->Get( Upgrade_SPEED ) = 7;
				u->Get( Upgrade_ELEVATOR ) = 0;
				u->Get( Upgrade_FALLING_BLOCK ) = 0;
				u->Get( Upgrade_FIREBALL ) = 0;
				u->Get( Upgrade_FIRE_SPINNER ) = 0;
				u->Get( Upgrade_SPIKEY_GUY ) = 7;
				u->Get( Upgrade_FLY_BLOB ) = 0;
				u->Get( Upgrade_GHOST_BLOCK ) = 7;
				u->Get( Upgrade_LASER ) = 0;
				u->Get( Upgrade_MOVING_BLOCK ) = 0;
				u->Get( Upgrade_SPIKE ) = 0;
				break;


		}

		return u;
	}

	std::shared_ptr<Upgrades> PresetUpgrades::GetUpgrade4()
	{
		std::shared_ptr<Upgrades> u = std::make_shared<Upgrades>();

		switch ( Tools::GlobalRnd->Rnd->Next( 0, 25 ) )
		{
			case 0:
				u->Get( Upgrade_JUMP ) = 4;
				u->Get( Upgrade_CEILING ) = 4;
				u->Get( Upgrade_GENERAL ) = 4;
				u->Get( Upgrade_SPEED ) = 4;
				u->Get( Upgrade_ELEVATOR ) = 5;
				u->Get( Upgrade_FALLING_BLOCK ) = 5;
				u->Get( Upgrade_FIREBALL ) = 5;
				u->Get( Upgrade_FIRE_SPINNER ) = 5;
				u->Get( Upgrade_SPIKEY_GUY ) = 5;
				u->Get( Upgrade_FLY_BLOB ) = 5;
				u->Get( Upgrade_GHOST_BLOCK ) = 5;
				u->Get( Upgrade_LASER ) = 5;
				u->Get( Upgrade_MOVING_BLOCK ) = 5;
				u->Get( Upgrade_SPIKE ) = 5;
				break;

			case 1:
				u->Get( Upgrade_JUMP ) = 7;
				u->Get( Upgrade_CEILING ) = 7;
				u->Get( Upgrade_GENERAL ) = 7;
				u->Get( Upgrade_SPEED ) = 7;
				u->Get( Upgrade_ELEVATOR ) = 0;
				u->Get( Upgrade_FALLING_BLOCK ) = 7;
				u->Get( Upgrade_FIREBALL ) = 0;
				u->Get( Upgrade_FIRE_SPINNER ) = 0;
				u->Get( Upgrade_SPIKEY_GUY ) = 7;
				u->Get( Upgrade_FLY_BLOB ) = 7;
				u->Get( Upgrade_GHOST_BLOCK ) = 0;
				u->Get( Upgrade_LASER ) = 0;
				u->Get( Upgrade_MOVING_BLOCK ) = 7;
				u->Get( Upgrade_SPIKE ) = 0;
				break;

			case 2:
				u->Get( Upgrade_JUMP ) = 7;
				u->Get( Upgrade_CEILING ) = 7;
				u->Get( Upgrade_GENERAL ) = 7;
				u->Get( Upgrade_SPEED ) = 7;
				u->Get( Upgrade_ELEVATOR ) = 0;
				u->Get( Upgrade_FALLING_BLOCK ) = 0;
				u->Get( Upgrade_FIREBALL ) = 0;
				u->Get( Upgrade_FIRE_SPINNER ) = 0;
				u->Get( Upgrade_SPIKEY_GUY ) = 0;
				u->Get( Upgrade_FLY_BLOB ) = 7;
				u->Get( Upgrade_GHOST_BLOCK ) = 7;
				u->Get( Upgrade_LASER ) = 0;
				u->Get( Upgrade_MOVING_BLOCK ) = 7;
				u->Get( Upgrade_SPIKE ) = 7;
				break;

			case 3:
				u->Get( Upgrade_JUMP ) = 7;
				u->Get( Upgrade_CEILING ) = 7;
				u->Get( Upgrade_GENERAL ) = 7;
				u->Get( Upgrade_SPEED ) = 7;
				u->Get( Upgrade_ELEVATOR ) = 0;
				u->Get( Upgrade_FALLING_BLOCK ) = 7;
				u->Get( Upgrade_FIREBALL ) = 0;
				u->Get( Upgrade_FIRE_SPINNER ) = 7;
				u->Get( Upgrade_SPIKEY_GUY ) = 0;
				u->Get( Upgrade_FLY_BLOB ) = 0;
				u->Get( Upgrade_GHOST_BLOCK ) = 7;
				u->Get( Upgrade_LASER ) = 0;
				u->Get( Upgrade_MOVING_BLOCK ) = 7;
				u->Get( Upgrade_SPIKE ) = 0;
				break;

			case 4:
				u->Get( Upgrade_JUMP ) = 7;
				u->Get( Upgrade_CEILING ) = 7;
				u->Get( Upgrade_GENERAL ) = 7;
				u->Get( Upgrade_SPEED ) = 7;
				u->Get( Upgrade_ELEVATOR ) = 0;
				u->Get( Upgrade_FALLING_BLOCK ) = 0;
				u->Get( Upgrade_FIREBALL ) = 7;
				u->Get( Upgrade_FIRE_SPINNER ) = 7;
				u->Get( Upgrade_SPIKEY_GUY ) = 7;
				u->Get( Upgrade_FLY_BLOB ) = 0;
				u->Get( Upgrade_GHOST_BLOCK ) = 0;
				u->Get( Upgrade_LASER ) = 7;
				u->Get( Upgrade_MOVING_BLOCK ) = 0;
				u->Get( Upgrade_SPIKE ) = 0;
				break;

			case 5:
				u->Get( Upgrade_JUMP ) = 7;
				u->Get( Upgrade_CEILING ) = 7;
				u->Get( Upgrade_GENERAL ) = 7;
				u->Get( Upgrade_SPEED ) = 7;
				u->Get( Upgrade_ELEVATOR ) = 0;
				u->Get( Upgrade_FALLING_BLOCK ) = 7;
				u->Get( Upgrade_FIREBALL ) = 7;
				u->Get( Upgrade_FIRE_SPINNER ) = 7;
				u->Get( Upgrade_SPIKEY_GUY ) = 0;
				u->Get( Upgrade_FLY_BLOB ) = 0;
				u->Get( Upgrade_GHOST_BLOCK ) = 0;
				u->Get( Upgrade_LASER ) = 0;
				u->Get( Upgrade_MOVING_BLOCK ) = 7;
				u->Get( Upgrade_SPIKE ) = 0;
				break;

			case 6:
				u->Get( Upgrade_JUMP ) = 7;
				u->Get( Upgrade_CEILING ) = 7;
				u->Get( Upgrade_GENERAL ) = 7;
				u->Get( Upgrade_SPEED ) = 7;
				u->Get( Upgrade_ELEVATOR ) = 0;
				u->Get( Upgrade_FALLING_BLOCK ) = 7;
				u->Get( Upgrade_FIREBALL ) = 0;
				u->Get( Upgrade_FIRE_SPINNER ) = 0;
				u->Get( Upgrade_SPIKEY_GUY ) = 7;
				u->Get( Upgrade_FLY_BLOB ) = 0;
				u->Get( Upgrade_GHOST_BLOCK ) = 0;
				u->Get( Upgrade_LASER ) = 7;
				u->Get( Upgrade_MOVING_BLOCK ) = 7;
				u->Get( Upgrade_SPIKE ) = 0;
				break;

			case 7:
				u->Get( Upgrade_JUMP ) = 7;
				u->Get( Upgrade_CEILING ) = 7;
				u->Get( Upgrade_GENERAL ) = 7;
				u->Get( Upgrade_SPEED ) = 7;
				u->Get( Upgrade_ELEVATOR ) = 0;
				u->Get( Upgrade_FALLING_BLOCK ) = 7;
				u->Get( Upgrade_FIREBALL ) = 0;
				u->Get( Upgrade_FIRE_SPINNER ) = 0;
				u->Get( Upgrade_SPIKEY_GUY ) = 0;
				u->Get( Upgrade_FLY_BLOB ) = 7;
				u->Get( Upgrade_GHOST_BLOCK ) = 0;
				u->Get( Upgrade_LASER ) = 0;
				u->Get( Upgrade_MOVING_BLOCK ) = 7;
				u->Get( Upgrade_SPIKE ) = 7;
				break;

			case 8:
				u->Get( Upgrade_JUMP ) = 7;
				u->Get( Upgrade_CEILING ) = 7;
				u->Get( Upgrade_GENERAL ) = 7;
				u->Get( Upgrade_SPEED ) = 7;
				u->Get( Upgrade_ELEVATOR ) = 7;
				u->Get( Upgrade_FALLING_BLOCK ) = 0;
				u->Get( Upgrade_FIREBALL ) = 0;
				u->Get( Upgrade_FIRE_SPINNER ) = 0;
				u->Get( Upgrade_SPIKEY_GUY ) = 7;
				u->Get( Upgrade_FLY_BLOB ) = 0;
				u->Get( Upgrade_GHOST_BLOCK ) = 7;
				u->Get( Upgrade_LASER ) = 7;
				u->Get( Upgrade_MOVING_BLOCK ) = 0;
				u->Get( Upgrade_SPIKE ) = 0;
				break;

			case 9:
				u->Get( Upgrade_JUMP ) = 7;
				u->Get( Upgrade_CEILING ) = 7;
				u->Get( Upgrade_GENERAL ) = 7;
				u->Get( Upgrade_SPEED ) = 7;
				u->Get( Upgrade_ELEVATOR ) = 7;
				u->Get( Upgrade_FALLING_BLOCK ) = 7;
				u->Get( Upgrade_FIREBALL ) = 0;
				u->Get( Upgrade_FIRE_SPINNER ) = 0;
				u->Get( Upgrade_SPIKEY_GUY ) = 7;
				u->Get( Upgrade_FLY_BLOB ) = 7;
				u->Get( Upgrade_GHOST_BLOCK ) = 0;
				u->Get( Upgrade_LASER ) = 0;
				u->Get( Upgrade_MOVING_BLOCK ) = 7;
				u->Get( Upgrade_SPIKE ) = 0;
				break;

			case 10:
				u->Get( Upgrade_JUMP ) = 7;
				u->Get( Upgrade_CEILING ) = 7;
				u->Get( Upgrade_GENERAL ) = 7;
				u->Get( Upgrade_SPEED ) = 7;
				u->Get( Upgrade_ELEVATOR ) = 0;
				u->Get( Upgrade_FALLING_BLOCK ) = 7;
				u->Get( Upgrade_FIREBALL ) = 0;
				u->Get( Upgrade_FIRE_SPINNER ) = 0;
				u->Get( Upgrade_SPIKEY_GUY ) = 0;
				u->Get( Upgrade_FLY_BLOB ) = 7;
				u->Get( Upgrade_GHOST_BLOCK ) = 7;
				u->Get( Upgrade_LASER ) = 0;
				u->Get( Upgrade_MOVING_BLOCK ) = 7;
				u->Get( Upgrade_SPIKE ) = 7;
				break;

			case 11:
				u->Get( Upgrade_JUMP ) = 7;
				u->Get( Upgrade_CEILING ) = 7;
				u->Get( Upgrade_GENERAL ) = 7;
				u->Get( Upgrade_SPEED ) = 7;
				u->Get( Upgrade_ELEVATOR ) = 0;
				u->Get( Upgrade_FALLING_BLOCK ) = 7;
				u->Get( Upgrade_FIREBALL ) = 7;
				u->Get( Upgrade_FIRE_SPINNER ) = 7;
				u->Get( Upgrade_SPIKEY_GUY ) = 0;
				u->Get( Upgrade_FLY_BLOB ) = 0;
				u->Get( Upgrade_GHOST_BLOCK ) = 7;
				u->Get( Upgrade_LASER ) = 0;
				u->Get( Upgrade_MOVING_BLOCK ) = 7;
				u->Get( Upgrade_SPIKE ) = 0;
				break;

			case 12:
				u->Get( Upgrade_JUMP ) = 7;
				u->Get( Upgrade_CEILING ) = 7;
				u->Get( Upgrade_GENERAL ) = 7;
				u->Get( Upgrade_SPEED ) = 7;
				u->Get( Upgrade_ELEVATOR ) = 0;
				u->Get( Upgrade_FALLING_BLOCK ) = 0;
				u->Get( Upgrade_FIREBALL ) = 7;
				u->Get( Upgrade_FIRE_SPINNER ) = 7;
				u->Get( Upgrade_SPIKEY_GUY ) = 7;
				u->Get( Upgrade_FLY_BLOB ) = 7;
				u->Get( Upgrade_GHOST_BLOCK ) = 0;
				u->Get( Upgrade_LASER ) = 7;
				u->Get( Upgrade_MOVING_BLOCK ) = 0;
				u->Get( Upgrade_SPIKE ) = 0;
				break;

			case 13:
				u->Get( Upgrade_JUMP ) = 7;
				u->Get( Upgrade_CEILING ) = 7;
				u->Get( Upgrade_GENERAL ) = 7;
				u->Get( Upgrade_SPEED ) = 7;
				u->Get( Upgrade_ELEVATOR ) = 0;
				u->Get( Upgrade_FALLING_BLOCK ) = 7;
				u->Get( Upgrade_FIREBALL ) = 7;
				u->Get( Upgrade_FIRE_SPINNER ) = 7;
				u->Get( Upgrade_SPIKEY_GUY ) = 0;
				u->Get( Upgrade_FLY_BLOB ) = 0;
				u->Get( Upgrade_GHOST_BLOCK ) = 7;
				u->Get( Upgrade_LASER ) = 0;
				u->Get( Upgrade_MOVING_BLOCK ) = 7;
				u->Get( Upgrade_SPIKE ) = 0;
				break;

			case 14:
				u->Get( Upgrade_JUMP ) = 7;
				u->Get( Upgrade_CEILING ) = 7;
				u->Get( Upgrade_GENERAL ) = 7;
				u->Get( Upgrade_SPEED ) = 7;
				u->Get( Upgrade_ELEVATOR ) = 0;
				u->Get( Upgrade_FALLING_BLOCK ) = 7;
				u->Get( Upgrade_FIREBALL ) = 0;
				u->Get( Upgrade_FIRE_SPINNER ) = 0;
				u->Get( Upgrade_SPIKEY_GUY ) = 7;
				u->Get( Upgrade_FLY_BLOB ) = 0;
				u->Get( Upgrade_GHOST_BLOCK ) = 0;
				u->Get( Upgrade_LASER ) = 7;
				u->Get( Upgrade_MOVING_BLOCK ) = 7;
				u->Get( Upgrade_SPIKE ) = 7;
				break;

			case 15:
				u->Get( Upgrade_JUMP ) = 7;
				u->Get( Upgrade_CEILING ) = 7;
				u->Get( Upgrade_GENERAL ) = 7;
				u->Get( Upgrade_SPEED ) = 7;
				u->Get( Upgrade_ELEVATOR ) = 0;
				u->Get( Upgrade_FALLING_BLOCK ) = 7;
				u->Get( Upgrade_FIREBALL ) = 0;
				u->Get( Upgrade_FIRE_SPINNER ) = 0;
				u->Get( Upgrade_SPIKEY_GUY ) = 7;
				u->Get( Upgrade_FLY_BLOB ) = 7;
				u->Get( Upgrade_GHOST_BLOCK ) = 0;
				u->Get( Upgrade_LASER ) = 0;
				u->Get( Upgrade_MOVING_BLOCK ) = 7;
				u->Get( Upgrade_SPIKE ) = 7;
				break;

			case 16:
				u->Get( Upgrade_JUMP ) = 7;
				u->Get( Upgrade_CEILING ) = 7;
				u->Get( Upgrade_GENERAL ) = 7;
				u->Get( Upgrade_SPEED ) = 7;
				u->Get( Upgrade_ELEVATOR ) = 7;
				u->Get( Upgrade_FALLING_BLOCK ) = 0;
				u->Get( Upgrade_FIREBALL ) = 0;
				u->Get( Upgrade_FIRE_SPINNER ) = 0;
				u->Get( Upgrade_SPIKEY_GUY ) = 7;
				u->Get( Upgrade_FLY_BLOB ) = 0;
				u->Get( Upgrade_GHOST_BLOCK ) = 7;
				u->Get( Upgrade_LASER ) = 7;
				u->Get( Upgrade_MOVING_BLOCK ) = 7;
				u->Get( Upgrade_SPIKE ) = 0;
				break;

			case 17:
				u->Get( Upgrade_JUMP ) = 3;
				u->Get( Upgrade_CEILING ) = 3;
				u->Get( Upgrade_GENERAL ) = 8;
				u->Get( Upgrade_SPEED ) = 8;
				u->Get( Upgrade_ELEVATOR ) = 0;
				u->Get( Upgrade_FALLING_BLOCK ) = 9;
				u->Get( Upgrade_FIREBALL ) = 0;
				u->Get( Upgrade_FIRE_SPINNER ) = 0;
				u->Get( Upgrade_SPIKEY_GUY ) = 0;
				u->Get( Upgrade_FLY_BLOB ) = 9;
				u->Get( Upgrade_GHOST_BLOCK ) = 0;
				u->Get( Upgrade_LASER ) = 0;
				u->Get( Upgrade_MOVING_BLOCK ) = 0;
				u->Get( Upgrade_SPIKE ) = 0;
				break;

			case 18:
				u->Get( Upgrade_JUMP ) = 5;
				u->Get( Upgrade_CEILING ) = 5;
				u->Get( Upgrade_GENERAL ) = 8;
				u->Get( Upgrade_SPEED ) = 8;
				u->Get( Upgrade_ELEVATOR ) = 0;
				u->Get( Upgrade_FALLING_BLOCK ) = 0;
				u->Get( Upgrade_FIREBALL ) = 0;
				u->Get( Upgrade_FIRE_SPINNER ) = 0;
				u->Get( Upgrade_SPIKEY_GUY ) = 0;
				u->Get( Upgrade_FLY_BLOB ) = 9;
				u->Get( Upgrade_GHOST_BLOCK ) = 9;
				u->Get( Upgrade_LASER ) = 0;
				u->Get( Upgrade_MOVING_BLOCK ) = 3;
				u->Get( Upgrade_SPIKE ) = 0;
				break;

			case 19:
				u->Get( Upgrade_JUMP ) = 9;
				u->Get( Upgrade_CEILING ) = 9;
				u->Get( Upgrade_GENERAL ) = 4;
				u->Get( Upgrade_SPEED ) = 4;
				u->Get( Upgrade_ELEVATOR ) = 0;
				u->Get( Upgrade_FALLING_BLOCK ) = 9;
				u->Get( Upgrade_FIREBALL ) = 0;
				u->Get( Upgrade_FIRE_SPINNER ) = 0;
				u->Get( Upgrade_SPIKEY_GUY ) = 0;
				u->Get( Upgrade_FLY_BLOB ) = 0;
				u->Get( Upgrade_GHOST_BLOCK ) = 9;
				u->Get( Upgrade_LASER ) = 0;
				u->Get( Upgrade_MOVING_BLOCK ) = 0;
				u->Get( Upgrade_SPIKE ) = 0;
				break;

			case 20:
				u->Get( Upgrade_JUMP ) = 5;
				u->Get( Upgrade_CEILING ) = 5;
				u->Get( Upgrade_GENERAL ) = 9;
				u->Get( Upgrade_SPEED ) = 9;
				u->Get( Upgrade_ELEVATOR ) = 0;
				u->Get( Upgrade_FALLING_BLOCK ) = 0;
				u->Get( Upgrade_FIREBALL ) = 9;
				u->Get( Upgrade_FIRE_SPINNER ) = 9;
				u->Get( Upgrade_SPIKEY_GUY ) = 0;
				u->Get( Upgrade_FLY_BLOB ) = 0;
				u->Get( Upgrade_GHOST_BLOCK ) = 0;
				u->Get( Upgrade_LASER ) = 9;
				u->Get( Upgrade_MOVING_BLOCK ) = 0;
				u->Get( Upgrade_SPIKE ) = 0;
				break;

			case 21:
				u->Get( Upgrade_JUMP ) = 9;
				u->Get( Upgrade_CEILING ) = 9;
				u->Get( Upgrade_GENERAL ) = 3;
				u->Get( Upgrade_SPEED ) = 3;
				u->Get( Upgrade_ELEVATOR ) = 0;
				u->Get( Upgrade_FALLING_BLOCK ) = 0;
				u->Get( Upgrade_FIREBALL ) = 0;
				u->Get( Upgrade_FIRE_SPINNER ) = 9;
				u->Get( Upgrade_SPIKEY_GUY ) = 0;
				u->Get( Upgrade_FLY_BLOB ) = 0;
				u->Get( Upgrade_GHOST_BLOCK ) = 0;
				u->Get( Upgrade_LASER ) = 0;
				u->Get( Upgrade_MOVING_BLOCK ) = 9;
				u->Get( Upgrade_SPIKE ) = 0;
				break;

			case 22:
				u->Get( Upgrade_JUMP ) = 9;
				u->Get( Upgrade_CEILING ) = 9;
				u->Get( Upgrade_GENERAL ) = 5;
				u->Get( Upgrade_SPEED ) = 5;
				u->Get( Upgrade_ELEVATOR ) = 0;
				u->Get( Upgrade_FALLING_BLOCK ) = 9;
				u->Get( Upgrade_FIREBALL ) = 0;
				u->Get( Upgrade_FIRE_SPINNER ) = 0;
				u->Get( Upgrade_SPIKEY_GUY ) = 0;
				u->Get( Upgrade_FLY_BLOB ) = 0;
				u->Get( Upgrade_GHOST_BLOCK ) = 0;
				u->Get( Upgrade_LASER ) = 0;
				u->Get( Upgrade_MOVING_BLOCK ) = 0;
				u->Get( Upgrade_SPIKE ) = 9;
				break;

			case 23:
				u->Get( Upgrade_JUMP ) = 7;
				u->Get( Upgrade_CEILING ) = 3;
				u->Get( Upgrade_GENERAL ) = 3;
				u->Get( Upgrade_SPEED ) = 7;
				u->Get( Upgrade_ELEVATOR ) = 0;
				u->Get( Upgrade_FALLING_BLOCK ) = 9;
				u->Get( Upgrade_FIREBALL ) = 0;
				u->Get( Upgrade_FIRE_SPINNER ) = 0;
				u->Get( Upgrade_SPIKEY_GUY ) = 0;
				u->Get( Upgrade_FLY_BLOB ) = 0;
				u->Get( Upgrade_GHOST_BLOCK ) = 0;
				u->Get( Upgrade_LASER ) = 0;
				u->Get( Upgrade_MOVING_BLOCK ) = 9;
				u->Get( Upgrade_SPIKE ) = 0;
				break;

			case 24:
				u->Get( Upgrade_JUMP ) = 5;
				u->Get( Upgrade_CEILING ) = 9;
				u->Get( Upgrade_GENERAL ) = 9;
				u->Get( Upgrade_SPEED ) = 5;
				u->Get( Upgrade_ELEVATOR ) = 0;
				u->Get( Upgrade_FALLING_BLOCK ) = 0;
				u->Get( Upgrade_FIREBALL ) = 0;
				u->Get( Upgrade_FIRE_SPINNER ) = 0;
				u->Get( Upgrade_SPIKEY_GUY ) = 9;
				u->Get( Upgrade_FLY_BLOB ) = 0;
				u->Get( Upgrade_GHOST_BLOCK ) = 0;
				u->Get( Upgrade_LASER ) = 9;
				u->Get( Upgrade_MOVING_BLOCK ) = 0;
				u->Get( Upgrade_SPIKE ) = 0;
				break;
		}

		return u;
	}

	std::shared_ptr<Upgrades> PresetUpgrades::GetUpgrade5()
	{
		std::shared_ptr<Upgrades> u = std::make_shared<Upgrades>();

		switch ( Tools::GlobalRnd->Rnd->Next( 0, 30 ) )
		{
			case 0:
				u->Get( Upgrade_CEILING ) = 6;
				u->Get( Upgrade_ELEVATOR ) = 7;
				u->Get( Upgrade_FALLING_BLOCK ) = 7;
				u->Get( Upgrade_FIREBALL ) = 7;
				u->Get( Upgrade_FIRE_SPINNER ) = 7;
				u->Get( Upgrade_SPIKEY_GUY ) = 7;
				u->Get( Upgrade_FLY_BLOB ) = 7;
				u->Get( Upgrade_GENERAL ) = 6;
				u->Get( Upgrade_GHOST_BLOCK ) = 7;
				u->Get( Upgrade_JUMP ) = 6;
				u->Get( Upgrade_LASER ) = 7;
				u->Get( Upgrade_MOVING_BLOCK ) = 7;
				u->Get( Upgrade_SPEED ) = 6;
				u->Get( Upgrade_SPIKE ) = 7;
				break;

			case 1:
				u->Get( Upgrade_JUMP ) = 9;
				u->Get( Upgrade_CEILING ) = 9;
				u->Get( Upgrade_GENERAL ) = 9;
				u->Get( Upgrade_SPEED ) = 9;
				u->Get( Upgrade_ELEVATOR ) = 9;
				u->Get( Upgrade_FALLING_BLOCK ) = 9;
				u->Get( Upgrade_FIREBALL ) = 0;
				u->Get( Upgrade_FIRE_SPINNER ) = 0;
				u->Get( Upgrade_SPIKEY_GUY ) = 9;
				u->Get( Upgrade_FLY_BLOB ) = 9;
				u->Get( Upgrade_GHOST_BLOCK ) = 0;
				u->Get( Upgrade_LASER ) = 0;
				u->Get( Upgrade_MOVING_BLOCK ) = 9;
				u->Get( Upgrade_SPIKE ) = 9;
				break;

			case 2:
				u->Get( Upgrade_JUMP ) = 9;
				u->Get( Upgrade_CEILING ) = 9;
				u->Get( Upgrade_GENERAL ) = 9;
				u->Get( Upgrade_SPEED ) = 9;
				u->Get( Upgrade_ELEVATOR ) = 9;
				u->Get( Upgrade_FALLING_BLOCK ) = 9;
				u->Get( Upgrade_FIREBALL ) = 0;
				u->Get( Upgrade_FIRE_SPINNER ) = 0;
				u->Get( Upgrade_SPIKEY_GUY ) = 0;
				u->Get( Upgrade_FLY_BLOB ) = 9;
				u->Get( Upgrade_GHOST_BLOCK ) = 9;
				u->Get( Upgrade_LASER ) = 0;
				u->Get( Upgrade_MOVING_BLOCK ) = 9;
				u->Get( Upgrade_SPIKE ) = 9;
				break;

			case 3:
				u->Get( Upgrade_JUMP ) = 9;
				u->Get( Upgrade_CEILING ) = 9;
				u->Get( Upgrade_GENERAL ) = 9;
				u->Get( Upgrade_SPEED ) = 9;
				u->Get( Upgrade_ELEVATOR ) = 0;
				u->Get( Upgrade_FALLING_BLOCK ) = 9;
				u->Get( Upgrade_FIREBALL ) = 9;
				u->Get( Upgrade_FIRE_SPINNER ) = 9;
				u->Get( Upgrade_SPIKEY_GUY ) = 9;
				u->Get( Upgrade_FLY_BLOB ) = 0;
				u->Get( Upgrade_GHOST_BLOCK ) = 9;
				u->Get( Upgrade_LASER ) = 0;
				u->Get( Upgrade_MOVING_BLOCK ) = 9;
				u->Get( Upgrade_SPIKE ) = 0;
				break;

			case 4:
				u->Get( Upgrade_JUMP ) = 9;
				u->Get( Upgrade_CEILING ) = 9;
				u->Get( Upgrade_GENERAL ) = 9;
				u->Get( Upgrade_SPEED ) = 9;
				u->Get( Upgrade_ELEVATOR ) = 0;
				u->Get( Upgrade_FALLING_BLOCK ) = 9;
				u->Get( Upgrade_FIREBALL ) = 9;
				u->Get( Upgrade_FIRE_SPINNER ) = 9;
				u->Get( Upgrade_SPIKEY_GUY ) = 9;
				u->Get( Upgrade_FLY_BLOB ) = 9;
				u->Get( Upgrade_GHOST_BLOCK ) = 0;
				u->Get( Upgrade_LASER ) = 9;
				u->Get( Upgrade_MOVING_BLOCK ) = 0;
				u->Get( Upgrade_SPIKE ) = 0;
				break;

			case 5:
				u->Get( Upgrade_JUMP ) = 9;
				u->Get( Upgrade_CEILING ) = 9;
				u->Get( Upgrade_GENERAL ) = 9;
				u->Get( Upgrade_SPEED ) = 9;
				u->Get( Upgrade_ELEVATOR ) = 0;
				u->Get( Upgrade_FALLING_BLOCK ) = 9;
				u->Get( Upgrade_FIREBALL ) = 9;
				u->Get( Upgrade_FIRE_SPINNER ) = 9;
				u->Get( Upgrade_SPIKEY_GUY ) = 0;
				u->Get( Upgrade_FLY_BLOB ) = 0;
				u->Get( Upgrade_GHOST_BLOCK ) = 9;
				u->Get( Upgrade_LASER ) = 9;
				u->Get( Upgrade_MOVING_BLOCK ) = 9;
				u->Get( Upgrade_SPIKE ) = 0;
				break;

			case 6:
				u->Get( Upgrade_JUMP ) = 9;
				u->Get( Upgrade_CEILING ) = 9;
				u->Get( Upgrade_GENERAL ) = 9;
				u->Get( Upgrade_SPEED ) = 9;
				u->Get( Upgrade_ELEVATOR ) = 0;
				u->Get( Upgrade_FALLING_BLOCK ) = 9;
				u->Get( Upgrade_FIREBALL ) = 0;
				u->Get( Upgrade_FIRE_SPINNER ) = 0;
				u->Get( Upgrade_SPIKEY_GUY ) = 9;
				u->Get( Upgrade_FLY_BLOB ) = 0;
				u->Get( Upgrade_GHOST_BLOCK ) = 0;
				u->Get( Upgrade_LASER ) = 9;
				u->Get( Upgrade_MOVING_BLOCK ) = 9;
				u->Get( Upgrade_SPIKE ) = 9;
				break;

			case 7:
				u->Get( Upgrade_JUMP ) = 9;
				u->Get( Upgrade_CEILING ) = 9;
				u->Get( Upgrade_GENERAL ) = 9;
				u->Get( Upgrade_SPEED ) = 9;
				u->Get( Upgrade_ELEVATOR ) = 0;
				u->Get( Upgrade_FALLING_BLOCK ) = 9;
				u->Get( Upgrade_FIREBALL ) = 9;
				u->Get( Upgrade_FIRE_SPINNER ) = 0;
				u->Get( Upgrade_SPIKEY_GUY ) = 9;
				u->Get( Upgrade_FLY_BLOB ) = 9;
				u->Get( Upgrade_GHOST_BLOCK ) = 0;
				u->Get( Upgrade_LASER ) = 0;
				u->Get( Upgrade_MOVING_BLOCK ) = 9;
				u->Get( Upgrade_SPIKE ) = 9;
				break;

			case 8:
				u->Get( Upgrade_JUMP ) = 9;
				u->Get( Upgrade_CEILING ) = 9;
				u->Get( Upgrade_GENERAL ) = 9;
				u->Get( Upgrade_SPEED ) = 9;
				u->Get( Upgrade_ELEVATOR ) = 9;
				u->Get( Upgrade_FALLING_BLOCK ) = 0;
				u->Get( Upgrade_FIREBALL ) = 0;
				u->Get( Upgrade_FIRE_SPINNER ) = 0;
				u->Get( Upgrade_SPIKEY_GUY ) = 9;
				u->Get( Upgrade_FLY_BLOB ) = 0;
				u->Get( Upgrade_GHOST_BLOCK ) = 9;
				u->Get( Upgrade_LASER ) = 9;
				u->Get( Upgrade_MOVING_BLOCK ) = 9;
				u->Get( Upgrade_SPIKE ) = 9;
				break;

			case 9:
				u->Get( Upgrade_JUMP ) = 9;
				u->Get( Upgrade_CEILING ) = 9;
				u->Get( Upgrade_GENERAL ) = 9;
				u->Get( Upgrade_SPEED ) = 9;
				u->Get( Upgrade_ELEVATOR ) = 9;
				u->Get( Upgrade_FALLING_BLOCK ) = 9;
				u->Get( Upgrade_FIREBALL ) = 9;
				u->Get( Upgrade_FIRE_SPINNER ) = 0;
				u->Get( Upgrade_SPIKEY_GUY ) = 9;
				u->Get( Upgrade_FLY_BLOB ) = 9;
				u->Get( Upgrade_GHOST_BLOCK ) = 0;
				u->Get( Upgrade_LASER ) = 0;
				u->Get( Upgrade_MOVING_BLOCK ) = 9;
				u->Get( Upgrade_SPIKE ) = 9;
				break;

			case 10:
				u->Get( Upgrade_JUMP ) = 9;
				u->Get( Upgrade_CEILING ) = 9;
				u->Get( Upgrade_GENERAL ) = 9;
				u->Get( Upgrade_SPEED ) = 9;
				u->Get( Upgrade_ELEVATOR ) = 9;
				u->Get( Upgrade_FALLING_BLOCK ) = 9;
				u->Get( Upgrade_FIREBALL ) = 0;
				u->Get( Upgrade_FIRE_SPINNER ) = 9;
				u->Get( Upgrade_SPIKEY_GUY ) = 0;
				u->Get( Upgrade_FLY_BLOB ) = 9;
				u->Get( Upgrade_GHOST_BLOCK ) = 9;
				u->Get( Upgrade_LASER ) = 0;
				u->Get( Upgrade_MOVING_BLOCK ) = 9;
				u->Get( Upgrade_SPIKE ) = 9;
				break;

			case 11:
				u->Get( Upgrade_JUMP ) = 9;
				u->Get( Upgrade_CEILING ) = 9;
				u->Get( Upgrade_GENERAL ) = 9;
				u->Get( Upgrade_SPEED ) = 9;
				u->Get( Upgrade_ELEVATOR ) = 9;
				u->Get( Upgrade_FALLING_BLOCK ) = 9;
				u->Get( Upgrade_FIREBALL ) = 9;
				u->Get( Upgrade_FIRE_SPINNER ) = 9;
				u->Get( Upgrade_SPIKEY_GUY ) = 9;
				u->Get( Upgrade_FLY_BLOB ) = 0;
				u->Get( Upgrade_GHOST_BLOCK ) = 9;
				u->Get( Upgrade_LASER ) = 0;
				u->Get( Upgrade_MOVING_BLOCK ) = 9;
				u->Get( Upgrade_SPIKE ) = 0;
				break;

			case 12:
				u->Get( Upgrade_JUMP ) = 9;
				u->Get( Upgrade_CEILING ) = 9;
				u->Get( Upgrade_GENERAL ) = 9;
				u->Get( Upgrade_SPEED ) = 9;
				u->Get( Upgrade_ELEVATOR ) = 0;
				u->Get( Upgrade_FALLING_BLOCK ) = 9;
				u->Get( Upgrade_FIREBALL ) = 9;
				u->Get( Upgrade_FIRE_SPINNER ) = 9;
				u->Get( Upgrade_SPIKEY_GUY ) = 9;
				u->Get( Upgrade_FLY_BLOB ) = 9;
				u->Get( Upgrade_GHOST_BLOCK ) = 9;
				u->Get( Upgrade_LASER ) = 9;
				u->Get( Upgrade_MOVING_BLOCK ) = 0;
				u->Get( Upgrade_SPIKE ) = 0;
				break;

			case 13:
				u->Get( Upgrade_JUMP ) = 9;
				u->Get( Upgrade_CEILING ) = 9;
				u->Get( Upgrade_GENERAL ) = 9;
				u->Get( Upgrade_SPEED ) = 9;
				u->Get( Upgrade_ELEVATOR ) = 0;
				u->Get( Upgrade_FALLING_BLOCK ) = 9;
				u->Get( Upgrade_FIREBALL ) = 9;
				u->Get( Upgrade_FIRE_SPINNER ) = 9;
				u->Get( Upgrade_SPIKEY_GUY ) = 0;
				u->Get( Upgrade_FLY_BLOB ) = 9;
				u->Get( Upgrade_GHOST_BLOCK ) = 9;
				u->Get( Upgrade_LASER ) = 9;
				u->Get( Upgrade_MOVING_BLOCK ) = 9;
				u->Get( Upgrade_SPIKE ) = 0;
				break;

			case 14:
				u->Get( Upgrade_JUMP ) = 9;
				u->Get( Upgrade_CEILING ) = 9;
				u->Get( Upgrade_GENERAL ) = 9;
				u->Get( Upgrade_SPEED ) = 9;
				u->Get( Upgrade_ELEVATOR ) = 0;
				u->Get( Upgrade_FALLING_BLOCK ) = 9;
				u->Get( Upgrade_FIREBALL ) = 9;
				u->Get( Upgrade_FIRE_SPINNER ) = 0;
				u->Get( Upgrade_SPIKEY_GUY ) = 9;
				u->Get( Upgrade_FLY_BLOB ) = 0;
				u->Get( Upgrade_GHOST_BLOCK ) = 0;
				u->Get( Upgrade_LASER ) = 9;
				u->Get( Upgrade_MOVING_BLOCK ) = 9;
				u->Get( Upgrade_SPIKE ) = 9;
				break;

			case 15:
				u->Get( Upgrade_JUMP ) = 9;
				u->Get( Upgrade_CEILING ) = 9;
				u->Get( Upgrade_GENERAL ) = 9;
				u->Get( Upgrade_SPEED ) = 9;
				u->Get( Upgrade_ELEVATOR ) = 0;
				u->Get( Upgrade_FALLING_BLOCK ) = 9;
				u->Get( Upgrade_FIREBALL ) = 9;
				u->Get( Upgrade_FIRE_SPINNER ) = 0;
				u->Get( Upgrade_SPIKEY_GUY ) = 9;
				u->Get( Upgrade_FLY_BLOB ) = 9;
				u->Get( Upgrade_GHOST_BLOCK ) = 0;
				u->Get( Upgrade_LASER ) = 9;
				u->Get( Upgrade_MOVING_BLOCK ) = 9;
				u->Get( Upgrade_SPIKE ) = 9;
				break;

			case 16:
				u->Get( Upgrade_JUMP ) = 9;
				u->Get( Upgrade_CEILING ) = 9;
				u->Get( Upgrade_GENERAL ) = 9;
				u->Get( Upgrade_SPEED ) = 9;
				u->Get( Upgrade_ELEVATOR ) = 9;
				u->Get( Upgrade_FALLING_BLOCK ) = 0;
				u->Get( Upgrade_FIREBALL ) = 9;
				u->Get( Upgrade_FIRE_SPINNER ) = 0;
				u->Get( Upgrade_SPIKEY_GUY ) = 9;
				u->Get( Upgrade_FLY_BLOB ) = 0;
				u->Get( Upgrade_GHOST_BLOCK ) = 9;
				u->Get( Upgrade_LASER ) = 9;
				u->Get( Upgrade_MOVING_BLOCK ) = 9;
				u->Get( Upgrade_SPIKE ) = 9;
				break;

			case 17:
				u->Get( Upgrade_JUMP ) = 9;
				u->Get( Upgrade_CEILING ) = 9;
				u->Get( Upgrade_GENERAL ) = 9;
				u->Get( Upgrade_SPEED ) = 9;
				u->Get( Upgrade_ELEVATOR ) = 0;
				u->Get( Upgrade_FALLING_BLOCK ) = 9;
				u->Get( Upgrade_FIREBALL ) = 0;
				u->Get( Upgrade_FIRE_SPINNER ) = 0;
				u->Get( Upgrade_SPIKEY_GUY ) = 0;
				u->Get( Upgrade_FLY_BLOB ) = 9;
				u->Get( Upgrade_GHOST_BLOCK ) = 0;
				u->Get( Upgrade_LASER ) = 0;
				u->Get( Upgrade_MOVING_BLOCK ) = 9;
				u->Get( Upgrade_SPIKE ) = 0;
				break;

			case 18:
				u->Get( Upgrade_JUMP ) = 9;
				u->Get( Upgrade_CEILING ) = 9;
				u->Get( Upgrade_GENERAL ) = 9;
				u->Get( Upgrade_SPEED ) = 9;
				u->Get( Upgrade_ELEVATOR ) = 0;
				u->Get( Upgrade_FALLING_BLOCK ) = 0;
				u->Get( Upgrade_FIREBALL ) = 0;
				u->Get( Upgrade_FIRE_SPINNER ) = 0;
				u->Get( Upgrade_SPIKEY_GUY ) = 0;
				u->Get( Upgrade_FLY_BLOB ) = 9;
				u->Get( Upgrade_GHOST_BLOCK ) = 9;
				u->Get( Upgrade_LASER ) = 0;
				u->Get( Upgrade_MOVING_BLOCK ) = 9;
				u->Get( Upgrade_SPIKE ) = 0;
				break;

			case 19:
				u->Get( Upgrade_JUMP ) = 9;
				u->Get( Upgrade_CEILING ) = 9;
				u->Get( Upgrade_GENERAL ) = 9;
				u->Get( Upgrade_SPEED ) = 9;
				u->Get( Upgrade_ELEVATOR ) = 0;
				u->Get( Upgrade_FALLING_BLOCK ) = 9;
				u->Get( Upgrade_FIREBALL ) = 0;
				u->Get( Upgrade_FIRE_SPINNER ) = 0;
				u->Get( Upgrade_SPIKEY_GUY ) = 0;
				u->Get( Upgrade_FLY_BLOB ) = 0;
				u->Get( Upgrade_GHOST_BLOCK ) = 9;
				u->Get( Upgrade_LASER ) = 0;
				u->Get( Upgrade_MOVING_BLOCK ) = 9;
				u->Get( Upgrade_SPIKE ) = 0;
				break;

			case 20:
				u->Get( Upgrade_JUMP ) = 9;
				u->Get( Upgrade_CEILING ) = 9;
				u->Get( Upgrade_GENERAL ) = 9;
				u->Get( Upgrade_SPEED ) = 9;
				u->Get( Upgrade_ELEVATOR ) = 0;
				u->Get( Upgrade_FALLING_BLOCK ) = 0;
				u->Get( Upgrade_FIREBALL ) = 9;
				u->Get( Upgrade_FIRE_SPINNER ) = 9;
				u->Get( Upgrade_SPIKEY_GUY ) = 0;
				u->Get( Upgrade_FLY_BLOB ) = 0;
				u->Get( Upgrade_GHOST_BLOCK ) = 0;
				u->Get( Upgrade_LASER ) = 9;
				u->Get( Upgrade_MOVING_BLOCK ) = 0;
				u->Get( Upgrade_SPIKE ) = 0;
				break;

			case 21:
				u->Get( Upgrade_JUMP ) = 9;
				u->Get( Upgrade_CEILING ) = 9;
				u->Get( Upgrade_GENERAL ) = 9;
				u->Get( Upgrade_SPEED ) = 9;
				u->Get( Upgrade_ELEVATOR ) = 0;
				u->Get( Upgrade_FALLING_BLOCK ) = 0;
				u->Get( Upgrade_FIREBALL ) = 9;
				u->Get( Upgrade_FIRE_SPINNER ) = 9;
				u->Get( Upgrade_SPIKEY_GUY ) = 0;
				u->Get( Upgrade_FLY_BLOB ) = 0;
				u->Get( Upgrade_GHOST_BLOCK ) = 0;
				u->Get( Upgrade_LASER ) = 0;
				u->Get( Upgrade_MOVING_BLOCK ) = 9;
				u->Get( Upgrade_SPIKE ) = 0;
				break;

			case 22:
				u->Get( Upgrade_JUMP ) = 9;
				u->Get( Upgrade_CEILING ) = 9;
				u->Get( Upgrade_GENERAL ) = 9;
				u->Get( Upgrade_SPEED ) = 9;
				u->Get( Upgrade_ELEVATOR ) = 0;
				u->Get( Upgrade_FALLING_BLOCK ) = 9;
				u->Get( Upgrade_FIREBALL ) = 0;
				u->Get( Upgrade_FIRE_SPINNER ) = 0;
				u->Get( Upgrade_SPIKEY_GUY ) = 9;
				u->Get( Upgrade_FLY_BLOB ) = 0;
				u->Get( Upgrade_GHOST_BLOCK ) = 0;
				u->Get( Upgrade_LASER ) = 0;
				u->Get( Upgrade_MOVING_BLOCK ) = 9;
				u->Get( Upgrade_SPIKE ) = 0;
				break;

			case 23:
				u->Get( Upgrade_JUMP ) = 9;
				u->Get( Upgrade_CEILING ) = 9;
				u->Get( Upgrade_GENERAL ) = 9;
				u->Get( Upgrade_SPEED ) = 9;
				u->Get( Upgrade_ELEVATOR ) = 0;
				u->Get( Upgrade_FALLING_BLOCK ) = 9;
				u->Get( Upgrade_FIREBALL ) = 0;
				u->Get( Upgrade_FIRE_SPINNER ) = 0;
				u->Get( Upgrade_SPIKEY_GUY ) = 0;
				u->Get( Upgrade_FLY_BLOB ) = 0;
				u->Get( Upgrade_GHOST_BLOCK ) = 0;
				u->Get( Upgrade_LASER ) = 0;
				u->Get( Upgrade_MOVING_BLOCK ) = 9;
				u->Get( Upgrade_SPIKE ) = 9;
				break;

			case 24:
				u->Get( Upgrade_JUMP ) = 9;
				u->Get( Upgrade_CEILING ) = 9;
				u->Get( Upgrade_GENERAL ) = 9;
				u->Get( Upgrade_SPEED ) = 9;
				u->Get( Upgrade_ELEVATOR ) = 0;
				u->Get( Upgrade_FALLING_BLOCK ) = 0;
				u->Get( Upgrade_FIREBALL ) = 0;
				u->Get( Upgrade_FIRE_SPINNER ) = 0;
				u->Get( Upgrade_SPIKEY_GUY ) = 9;
				u->Get( Upgrade_FLY_BLOB ) = 0;
				u->Get( Upgrade_GHOST_BLOCK ) = 9;
				u->Get( Upgrade_LASER ) = 9;
				u->Get( Upgrade_MOVING_BLOCK ) = 0;
				u->Get( Upgrade_SPIKE ) = 0;
				break;

			case 25:
				u->Get( Upgrade_JUMP ) = 9;
				u->Get( Upgrade_CEILING ) = 9;
				u->Get( Upgrade_GENERAL ) = 9;
				u->Get( Upgrade_SPEED ) = 9;
				u->Get( Upgrade_ELEVATOR ) = 0;
				u->Get( Upgrade_FALLING_BLOCK ) = 0;
				u->Get( Upgrade_FIREBALL ) = 0;
				u->Get( Upgrade_FIRE_SPINNER ) = 9;
				u->Get( Upgrade_SPIKEY_GUY ) = 0;
				u->Get( Upgrade_FLY_BLOB ) = 0;
				u->Get( Upgrade_GHOST_BLOCK ) = 0;
				u->Get( Upgrade_LASER ) = 0;
				u->Get( Upgrade_MOVING_BLOCK ) = 9;
				u->Get( Upgrade_SPIKE ) = 0;
				break;

			case 26:
				u->Get( Upgrade_JUMP ) = 9;
				u->Get( Upgrade_CEILING ) = 9;
				u->Get( Upgrade_GENERAL ) = 9;
				u->Get( Upgrade_SPEED ) = 9;
				u->Get( Upgrade_ELEVATOR ) = 0;
				u->Get( Upgrade_FALLING_BLOCK ) = 9;
				u->Get( Upgrade_FIREBALL ) = 0;
				u->Get( Upgrade_FIRE_SPINNER ) = 0;
				u->Get( Upgrade_SPIKEY_GUY ) = 0;
				u->Get( Upgrade_FLY_BLOB ) = 0;
				u->Get( Upgrade_GHOST_BLOCK ) = 0;
				u->Get( Upgrade_LASER ) = 0;
				u->Get( Upgrade_MOVING_BLOCK ) = 0;
				u->Get( Upgrade_SPIKE ) = 9;
				break;

			case 27:
				u->Get( Upgrade_JUMP ) = 9;
				u->Get( Upgrade_CEILING ) = 9;
				u->Get( Upgrade_GENERAL ) = 9;
				u->Get( Upgrade_SPEED ) = 9;
				u->Get( Upgrade_ELEVATOR ) = 0;
				u->Get( Upgrade_FALLING_BLOCK ) = 0;
				u->Get( Upgrade_FIREBALL ) = 0;
				u->Get( Upgrade_FIRE_SPINNER ) = 0;
				u->Get( Upgrade_SPIKEY_GUY ) = 0;
				u->Get( Upgrade_FLY_BLOB ) = 0;
				u->Get( Upgrade_GHOST_BLOCK ) = 9;
				u->Get( Upgrade_LASER ) = 9;
				u->Get( Upgrade_MOVING_BLOCK ) = 0;
				u->Get( Upgrade_SPIKE ) = 0;
				break;

			case 28:
				u->Get( Upgrade_JUMP ) = 9;
				u->Get( Upgrade_CEILING ) = 9;
				u->Get( Upgrade_GENERAL ) = 9;
				u->Get( Upgrade_SPEED ) = 9;
				u->Get( Upgrade_ELEVATOR ) = 0;
				u->Get( Upgrade_FALLING_BLOCK ) = 0;
				u->Get( Upgrade_FIREBALL ) = 0;
				u->Get( Upgrade_FIRE_SPINNER ) = 0;
				u->Get( Upgrade_SPIKEY_GUY ) = 9;
				u->Get( Upgrade_FLY_BLOB ) = 0;
				u->Get( Upgrade_GHOST_BLOCK ) = 0;
				u->Get( Upgrade_LASER ) = 0;
				u->Get( Upgrade_MOVING_BLOCK ) = 0;
				u->Get( Upgrade_SPIKE ) = 9;
				break;

			case 29:
				u->Get( Upgrade_JUMP ) = 9;
				u->Get( Upgrade_CEILING ) = 9;
				u->Get( Upgrade_GENERAL ) = 9;
				u->Get( Upgrade_SPEED ) = 9;
				u->Get( Upgrade_ELEVATOR ) = 0;
				u->Get( Upgrade_FALLING_BLOCK ) = 0;
				u->Get( Upgrade_FIREBALL ) = 0;
				u->Get( Upgrade_FIRE_SPINNER ) = 0;
				u->Get( Upgrade_SPIKEY_GUY ) = 9;
				u->Get( Upgrade_FLY_BLOB ) = 9;
				u->Get( Upgrade_GHOST_BLOCK ) = 0;
				u->Get( Upgrade_LASER ) = 0;
				u->Get( Upgrade_MOVING_BLOCK ) = 0;
				u->Get( Upgrade_SPIKE ) = 0;
				break;
		}

		return u;
	}

	std::shared_ptr<Upgrades> PresetUpgrades::GetUpgrade6()
	{
		std::shared_ptr<Upgrades> u = std::make_shared<Upgrades>();

		switch ( Tools::GlobalRnd->Rnd->Next( 0, 0 ) )
		{
			case 0:
				u->Get( Upgrade_CEILING ) = 9;
				u->Get( Upgrade_ELEVATOR ) = 9;
				u->Get( Upgrade_FALLING_BLOCK ) = 9;
				u->Get( Upgrade_FIREBALL ) = 9;
				u->Get( Upgrade_FIRE_SPINNER ) = 9;
				u->Get( Upgrade_SPIKEY_GUY ) = 9;
				u->Get( Upgrade_FLY_BLOB ) = 9;
				u->Get( Upgrade_GENERAL ) = 9;
				u->Get( Upgrade_GHOST_BLOCK ) = 9;
				u->Get( Upgrade_JUMP ) = 9;
				u->Get( Upgrade_LASER ) = 9;
				u->Get( Upgrade_MOVING_BLOCK ) = 9;
				u->Get( Upgrade_SPEED ) = 9;
				u->Get( Upgrade_SPIKE ) = 9;
				break;
		}

		return u;
	}

	std::shared_ptr<Upgrades> PresetUpgrades::GetUpgrade( int Difficulty )
	{
		switch ( Difficulty )
		{
			default:
				return GetUpgrade1();
			case 2:
				return GetUpgrade2();
			case 3:
				return GetUpgrade3();
			case 4:
				return GetUpgrade4();
			case 5:
				return GetUpgrade5();
			case 6:
				return GetUpgrade6();
		}
	}
}
