#include <global_header.h>

#include "Hacks/List.h"

namespace CloudberryKingdom
{

	int RndDifficulty::ChoosePaths( const std::shared_ptr<PieceSeedData> &data )
	{
		float JumpDifficulty = data->MyUpgrades1->Get( Upgrade_JUMP );

		double p = data->getRnd()->Rnd->NextDouble();
		if ( p < .75f + .25f *.1f * JumpDifficulty )
			return 1;
		//else if (p < .9f + .1f * .1f * JumpDifficulty) return 2;
		//else return 3;
		else
			return 2;
	}

	LadderType RndDifficulty::ChooseLadder( int Difficulty )
	{
		//if (Difficulty < 30)
		//    return Level.LadderType.Simple2;
		//else
			return LadderType_DOUBLE_MOVING;
	}

	void RndDifficulty::ZeroUpgrades( const std::shared_ptr<Upgrades> &upgrades )
	{
		for ( int i = 0; i < Tools::UpgradeTypes; i++ )
			upgrades->UpgradeLevels[ i ] = 0;
	}

	void RndDifficulty::EnforceLevelCap( const std::shared_ptr<Upgrades> &upgrades, int Cap, int LowerCap )
	{
		for ( int i = 0; i < Tools::UpgradeTypes; i++ )
			upgrades->UpgradeLevels[ i ] = __max( LowerCap, __min( Cap, upgrades->UpgradeLevels[ i ] ) );
	}

	void RndDifficulty::UseUpgrades( const std::shared_ptr<PieceSeedData> &Seed, const std::shared_ptr<Upgrades> &u )
	{
		ZeroUpgrades( Seed->MyUpgrades1 );
		Seed->MyUpgrades1->CopyFrom( u );
		Seed->MyUpgrades1->CalcGenData( Seed->MyGenData->gen1, Seed->Style );

		ZeroUpgrades( Seed->MyUpgrades2 );
		Seed->MyUpgrades2->CopyFrom( u );
		Seed->MyUpgrades2->CalcGenData( Seed->MyGenData->gen2, Seed->Style );
	}

	void RndDifficulty::IntToDifficulty( const std::shared_ptr<PieceSeedData> &Seed, const std::shared_ptr<TileSet> &TileType )
	{
		ZeroUpgrades( Seed->MyUpgrades1 );
		Seed->MyUpgrades1->Get( Upgrade_FIRE_SPINNER ) = 10;
		Seed->MyUpgrades1->Get( Upgrade_GENERAL ) = 10;
		Seed->MyUpgrades1->CalcGenData( Seed->MyGenData->gen1, Seed->Style );

		ZeroUpgrades( Seed->MyUpgrades2 );
		/*Seed->MyUpgrades1->UpgradeLevels.CopyTo( Seed->MyUpgrades2->UpgradeLevels, 0 );*/
		CopyFromTo( Seed->MyUpgrades1->UpgradeLevels, Seed->MyUpgrades2->UpgradeLevels );
		Seed->MyUpgrades2->CalcGenData( Seed->MyGenData->gen2, Seed->Style );

		/*
		int Types;
		if (Difficulty == 0) Types = 0;
		else Types = MyLevel.Rnd.Rnd.Next(Math.Min(Tools.UpgradeTypes - 1, Generic.MinTypes),
		                            Math.Min(Tools.UpgradeTypes - 1, Generic.MaxTypes));
	
		int[] UpgradeChoices = ChooseUpgrades(Types);
	
		ZeroUpgrades(Seed.MyUpgrades1);
		UpgradeUpgrades(Seed.MyUpgrades1, UpgradeChoices, Difficulty / 5);
		EnforceLevelCap(Seed.MyUpgrades1, Generic.MaxLevel / 2, Generic.MinLevel / 2);
		Seed.MyUpgrades1.CalcGenData(Seed.MyGenData.gen1, Seed.Style);
	
		ZeroUpgrades(Seed.MyUpgrades2);
		UpgradeUpgrades(Seed.MyUpgrades2, UpgradeChoices, Difficulty);
		EnforceLevelCap(Seed.MyUpgrades2, Generic.MaxLevel, Generic.MinLevel);
		Seed.MyUpgrades2.CalcGenData(Seed.MyGenData.gen2, Seed.Style);
	
		Seed.MyUpgrades1.UpgradeLevels.CopyTo(Seed.MyUpgrades2.UpgradeLevels, 0);*/
	}
}
