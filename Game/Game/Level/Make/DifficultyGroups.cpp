#include <global_header.h>

#include "Hacks/List.h"

namespace CloudberryKingdom
{

	void DifficultyGroups::UpgradeSequenceSingle::Apply( const boost::shared_ptr<PieceSeedData> &Piece, float Difficulty )
	{
		float d = Difficulty;

		float val = 0;
		if ( d < 0 )
			val = CoreMath::LerpRestrict( static_cast<float>( 0 ), static_cast<float>( Values[ 0 ] ), d - -1 );
		else if ( d < 1 )
			val = CoreMath::SpecialLerp( static_cast<float>( Values[ 0 ] ), static_cast<float>( Values[ 1 ] ), d - 0 );
		else if ( d < 2 )
			val = CoreMath::SpecialLerp( static_cast<float>( Values[ 1 ] ), static_cast<float>( Values[ 2 ] ), d - 1 );
		else if ( d < 3 )
			val = CoreMath::SpecialLerp( static_cast<float>( Values[ 2 ] ), static_cast<float>( Values[ 3 ] ), d - 2 );
		else
			val = CoreMath::SpecialLerpRestrict( static_cast<float>( Values[ 3 ] ), static_cast<float>( Values[ 4 ] ), d - 3 );

		Piece->getu()->Get( MyUpgrade ) = val;
	}

	DifficultyGroups::UpgradeSequenceSingle::UpgradeSequenceSingle( Upgrade MyUpgrade, double v0, double v1, double v2, double v3, double v4 )
	{
		this->MyUpgrade = MyUpgrade;

		Values = std::vector<double>( 5 );
		//for ( int i = 0; i < 5; i++ )
		//	Values[ i ] = values[ i ];
		Values[ 0 ] = v0;
		Values[ 1 ] = v1;
		Values[ 2 ] = v2;
		Values[ 3 ] = v3;
		Values[ 4 ] = v4;
	}

	void DifficultyGroups::UpgradeSequence::Apply( const boost::shared_ptr<PieceSeedData> &Piece, float Difficulty )
	{
		for ( std::vector<UpgradeSequenceSingle>::iterator upgrade = UpgradeList.begin(); upgrade != UpgradeList.end(); ++upgrade )
		{
			( *upgrade ).Apply( Piece, Difficulty );
		}
	}

	DifficultyGroups::UpgradeSequence::UpgradeSequence(
		DifficultyGroups::UpgradeSequenceSingle s1,
		DifficultyGroups::UpgradeSequenceSingle s2,
		DifficultyGroups::UpgradeSequenceSingle s3,
		DifficultyGroups::UpgradeSequenceSingle s4,
		DifficultyGroups::UpgradeSequenceSingle s5,
		DifficultyGroups::UpgradeSequenceSingle s6,
		DifficultyGroups::UpgradeSequenceSingle s7,
		DifficultyGroups::UpgradeSequenceSingle s8,
		DifficultyGroups::UpgradeSequenceSingle s9,
		DifficultyGroups::UpgradeSequenceSingle s10 )
	{
		UpgradeList = std::vector<UpgradeSequenceSingle>();

		UpgradeList.push_back( s1 );
		UpgradeList.push_back( s2 );
		UpgradeList.push_back( s3 );
		UpgradeList.push_back( s4 );
		UpgradeList.push_back( s5 );
		UpgradeList.push_back( s6 );
		UpgradeList.push_back( s7 );
		UpgradeList.push_back( s8 );
		UpgradeList.push_back( s9 );
		UpgradeList.push_back( s10 );
	}

	DifficultyGroups::UpgradeSequence::UpgradeSequence(
		DifficultyGroups::UpgradeSequenceSingle s1,
		DifficultyGroups::UpgradeSequenceSingle s2,
		DifficultyGroups::UpgradeSequenceSingle s3,
		DifficultyGroups::UpgradeSequenceSingle s4,
		DifficultyGroups::UpgradeSequenceSingle s5,
		DifficultyGroups::UpgradeSequenceSingle s6,
		DifficultyGroups::UpgradeSequenceSingle s7,
		DifficultyGroups::UpgradeSequenceSingle s8,
		DifficultyGroups::UpgradeSequenceSingle s9 )
	{
		UpgradeList = std::vector<UpgradeSequenceSingle>();

		UpgradeList.push_back( s1 );
		UpgradeList.push_back( s2 );
		UpgradeList.push_back( s3 );
		UpgradeList.push_back( s4 );
		UpgradeList.push_back( s5 );
		UpgradeList.push_back( s6 );
		UpgradeList.push_back( s7 );
		UpgradeList.push_back( s8 );
		UpgradeList.push_back( s9 );
	}

	DifficultyGroups::UpgradeSequence::UpgradeSequence(
		DifficultyGroups::UpgradeSequenceSingle s1,
		DifficultyGroups::UpgradeSequenceSingle s2,
		DifficultyGroups::UpgradeSequenceSingle s3,
		DifficultyGroups::UpgradeSequenceSingle s4,
		DifficultyGroups::UpgradeSequenceSingle s5,
		DifficultyGroups::UpgradeSequenceSingle s6,
		DifficultyGroups::UpgradeSequenceSingle s7,
		DifficultyGroups::UpgradeSequenceSingle s8 )
	{
		UpgradeList = std::vector<UpgradeSequenceSingle>();

		UpgradeList.push_back( s1 );
		UpgradeList.push_back( s2 );
		UpgradeList.push_back( s3 );
		UpgradeList.push_back( s4 );
		UpgradeList.push_back( s5 );
		UpgradeList.push_back( s6 );
		UpgradeList.push_back( s7 );
		UpgradeList.push_back( s8 );
	}

	DifficultyGroups::UpgradeSequence::UpgradeSequence(
		DifficultyGroups::UpgradeSequenceSingle s1,
		DifficultyGroups::UpgradeSequenceSingle s2,
		DifficultyGroups::UpgradeSequenceSingle s3,
		DifficultyGroups::UpgradeSequenceSingle s4,
		DifficultyGroups::UpgradeSequenceSingle s5,
		DifficultyGroups::UpgradeSequenceSingle s6,
		DifficultyGroups::UpgradeSequenceSingle s7 )
	{
		UpgradeList = std::vector<UpgradeSequenceSingle>();

		UpgradeList.push_back( s1 );
		UpgradeList.push_back( s2 );
		UpgradeList.push_back( s3 );
		UpgradeList.push_back( s4 );
		UpgradeList.push_back( s5 );
		UpgradeList.push_back( s6 );
		UpgradeList.push_back( s7 );
	}


	DifficultyGroups::UpgradeSequence::UpgradeSequence(
		DifficultyGroups::UpgradeSequenceSingle s1,
		DifficultyGroups::UpgradeSequenceSingle s2,
		DifficultyGroups::UpgradeSequenceSingle s3,
		DifficultyGroups::UpgradeSequenceSingle s4,
		DifficultyGroups::UpgradeSequenceSingle s5,
		DifficultyGroups::UpgradeSequenceSingle s6 )
	{
		UpgradeList = std::vector<UpgradeSequenceSingle>();

		UpgradeList.push_back( s1 );
		UpgradeList.push_back( s2 );
		UpgradeList.push_back( s3 );
		UpgradeList.push_back( s4 );
		UpgradeList.push_back( s5 );
		UpgradeList.push_back( s6 );
	}

	DifficultyGroups::UpgradeSequence::UpgradeSequence(
		DifficultyGroups::UpgradeSequenceSingle s1,
		DifficultyGroups::UpgradeSequenceSingle s2,
		DifficultyGroups::UpgradeSequenceSingle s3,
		DifficultyGroups::UpgradeSequenceSingle s4,
		DifficultyGroups::UpgradeSequenceSingle s5 )
	{
		UpgradeList = std::vector<UpgradeSequenceSingle>();

		UpgradeList.push_back( s1 );
		UpgradeList.push_back( s2 );
		UpgradeList.push_back( s3 );
		UpgradeList.push_back( s4 );
		UpgradeList.push_back( s5 );
	}

	DifficultyGroups::UpgradeSequence::UpgradeSequence(
		DifficultyGroups::UpgradeSequenceSingle s1,
		DifficultyGroups::UpgradeSequenceSingle s2,
		DifficultyGroups::UpgradeSequenceSingle s3,
		DifficultyGroups::UpgradeSequenceSingle s4 )
	{
		UpgradeList = std::vector<UpgradeSequenceSingle>();

		UpgradeList.push_back( s1 );
		UpgradeList.push_back( s2 );
		UpgradeList.push_back( s3 );
		UpgradeList.push_back( s4 );
	}

	DifficultyGroups::UpgradeSequence::UpgradeSequence(
		DifficultyGroups::UpgradeSequenceSingle s1,
		DifficultyGroups::UpgradeSequenceSingle s2,
		DifficultyGroups::UpgradeSequenceSingle s3 )
	{
		UpgradeList = std::vector<UpgradeSequenceSingle>();

		UpgradeList.push_back( s1 );
		UpgradeList.push_back( s2 );
		UpgradeList.push_back( s3 );
	}

	DifficultyGroups::UpgradeSequence::UpgradeSequence(
		DifficultyGroups::UpgradeSequenceSingle s1,
		DifficultyGroups::UpgradeSequenceSingle s2 )
	{
		UpgradeList = std::vector<UpgradeSequenceSingle>();

		UpgradeList.push_back( s1 );
		UpgradeList.push_back( s2 );
	}

	DifficultyGroups::UpgradeSequence::UpgradeSequence(
		DifficultyGroups::UpgradeSequenceSingle s1 )
	{
		UpgradeList = std::vector<UpgradeSequenceSingle>();

		UpgradeList.push_back( s1 );
	}

	DifficultyGroups::FixedPieceModHelper::FixedPieceModHelper( float Difficulty, const boost::shared_ptr<LevelSeedData> &LevelSeed, bool ScreenSaver )
	{
		this->Difficulty = Difficulty;
		this->LevelSeed = LevelSeed;
		this->ScreenSaver = ScreenSaver;
	}

	void DifficultyGroups::FixedPieceModHelper::Apply( const boost::shared_ptr<PieceSeedData> &piece )
	{
		DifficultyGroups::FixedPieceSeed( piece, Difficulty, LevelSeed->DefaultHeroType, ScreenSaver );
	}

	boost::shared_ptr<Lambda_1<boost::shared_ptr<PieceSeedData> > > DifficultyGroups::FixedPieceMod( float Difficulty, const boost::shared_ptr<LevelSeedData> &LevelSeed, bool ScreenSaver )
	{
		return boost::make_shared<FixedPieceModHelper>( Difficulty, LevelSeed, ScreenSaver );
	}

	float DifficultyGroups::HeroDifficultyMod( float Difficulty, const boost::shared_ptr<BobPhsx> &hero )
	{
		if ( boost::dynamic_pointer_cast<BobPhsxBox>( hero ) != 0 )
			return -.235f;
		if ( boost::dynamic_pointer_cast<BobPhsxWheel>( hero ) != 0 )
			return -.1f;
		if ( boost::dynamic_pointer_cast<BobPhsxRocketbox>( hero ) != 0 )
			return -.33f;
		if ( boost::dynamic_pointer_cast<BobPhsxSmall>( hero ) != 0 )
			return -.1f;
		if ( boost::dynamic_pointer_cast<BobPhsxSpaceship>( hero ) != 0 )
			return -.065f;
		if ( boost::dynamic_pointer_cast<BobPhsxDouble>( hero ) != 0 )
			return 0;
		if ( boost::dynamic_pointer_cast<BobPhsxBouncy>( hero ) != 0 )
			return -0.435f;

		return 0;
	}

	void DifficultyGroups::FixedPieceSeed( const boost::shared_ptr<PieceSeedData> &piece, float Difficulty, const boost::shared_ptr<BobPhsx> &hero, bool ScreenSaver )
	{
		InitFixedUpgrades();

		// Up level
		if ( piece->GeometryType == LevelGeometry_UP )
			piece->getRnd()->Choose( UpUpgrades ).Apply(piece, Difficulty);
		// Down level
		else if ( piece->GeometryType == LevelGeometry_DOWN )
			piece->getRnd()->Choose(DownUpgrades).Apply(piece, Difficulty);
		// Cart level
		else if ( boost::dynamic_pointer_cast<BobPhsxRocketbox>( hero ) != 0 )
		{
			if ( Difficulty < .5f )
				Difficulty -= .8f;
			else
				Difficulty -= 1.35f;

			piece->getRnd()->Choose(CartUpgrades).Apply(piece, Difficulty);
		}
		// Generic hero level
		else
		{
			Difficulty += HeroDifficultyMod( Difficulty, hero );

			// FIXME: port the new difficulty levels and then uncomment this
			//if ( ScreenSaver )
			//{
			//	switch ( static_cast<int>( Difficulty ) )
			//	{
			//		case 0:
			//			Tools::GlobalRnd->Choose(EasyUpgrades_SS).Apply(piece, Difficulty);
			//			break;
			//		case 1:
			//			Tools::GlobalRnd->Choose(NormalUpgrades_SS).Apply(piece, Difficulty);
			//			break;
			//		case 2:
			//			Tools::GlobalRnd->Choose(AbusiveUpgrades_SS).Apply(piece, Difficulty);
			//			break;
			//		default:
			//			Tools::GlobalRnd->Choose(HardcoreUpgrades_SS).Apply(piece, Difficulty);
			//			break;
			//	}
			//}
			//else
			{
				switch ( static_cast<int>( Difficulty ) )
				{
					case 0:
						Tools::GlobalRnd->Choose(EasyUpgrades).Apply(piece, Difficulty);
						break;
					case 1:
						Tools::GlobalRnd->Choose(NormalUpgrades).Apply(piece, Difficulty);
						break;
					case 2:
						Tools::GlobalRnd->Choose(AbusiveUpgrades).Apply(piece, Difficulty);
						break;
					default:
						Tools::GlobalRnd->Choose(HardcoreUpgrades).Apply(piece, Difficulty);
						break;
				}
			}
		}

		// Mod upgrades to test things here
		//piece.MyUpgrades1->Get(Upgrade.Elevator) = 5;
		//piece.MyUpgrades1.CalcGenData(piece.MyGenData.gen1, piece.Style);
		//piece.MyUpgrades2->Get( Upgrade.Elevator ) = 5;
		//piece.MyUpgrades2.CalcGenData(piece.MyGenData.gen1, piece.Style);


		// Extra masochistic
		if (Difficulty > 4.5f)
		{
			float s = CoreMath::RestrictVal( 0.0f, 1.0f, (Difficulty - 4.5f) / 1.5f );

			float rnd = Tools::GlobalRnd->RndFloat(0, 100);
			if (rnd > 80)
				piece->MyUpgrades1->Get( Upgrade_SERPENT ) = CoreMath.Lerp(piece->MyUpgrades1->Get( Upgrade_SERPENT ), 10.0f, s);
			else if (rnd > 60)
				piece->MyUpgrades1->Get( Upgrade_LAVA_DRIP ) = CoreMath.Lerp(piece->MyUpgrades1->Get( Upgrade_LAVA_DRIP ), 10.0f, s);
			else if (rnd > 40)
				piece->MyUpgrades1->Get( Upgrade_FIREBALL ) = CoreMath.Lerp(piece->MyUpgrades1->Get( Upgrade_FIREBALL ), 10.0f, s);

			rnd = Tools::GlobalRnd->RndFloat(0, 100);
			if (rnd > 50)
				piece->MyUpgrades1->Get( Upgrade_CEILING ) = CoreMath.Lerp(piece->MyUpgrades1->Get( Upgrade_CEILING ), 10.0f, s);

			piece->MyUpgrades1->Get( Upgrade_SPIKEY_GUY ) = CoreMath.Lerp(piece->MyUpgrades1->Get( Upgrade_SPIKEY_GUY ), 10.0f, s);
			piece->MyUpgrades1->Get( Upgrade_PINKY ) = CoreMath.Lerp(piece->MyUpgrades1->Get( Upgrade_PINKY ), 10.0f, s);
			piece->MyUpgrades1->Get( Upgrade_SPIKEY_LINE ) = CoreMath.Lerp(piece->MyUpgrades1->Get( Upgrade_SPIKEY_LINE ), 10.0f, s);
			piece->MyUpgrades1->Get( Upgrade_SPIKE ) = CoreMath.Lerp(piece->MyUpgrades1->Get( Upgrade_SPIKE ), 10.0f, s);
				
			piece->MyUpgrades1->Get( Upgrade_SPEED ) = CoreMath.Lerp(piece->MyUpgrades1->Get( Upgrade_SPEED ), 10.0f, s);
		}

		piece->StandardClose();
	}

	void DifficultyGroups::InitFixedUpgrades()
	{
		if ( EasyUpgrades.size() > 0 )
			return;

		EasyUpgrades = std::vector<UpgradeSequence>();
		EasyUpgrades_SS = std::vector<UpgradeSequence>();

		// Difficulties
		MakeEasyUpgrades();
		MakeNormalUpgrades();
		MakeAbusiveUpgrades();
		MakeHardcoreUpgrades();

		MakeEasyUpgrades_SS();
		MakeNormalUpgrades_SS();
		MakeAbusiveUpgrades_SS();
		MakeHardcoreUpgrades_SS();

		// Special hero overrides
		MakeCartUpgrades();

		// Up/down overrides
		MakeUpUpgrades();
		MakeDownUpgrades();
	}

	std::vector<DifficultyGroups::UpgradeSequence> DifficultyGroups::UpUpgrades;

	void DifficultyGroups::MakeUpUpgrades()
	{
		std::vector<UpgradeSequence> &f = UpUpgrades;

		f.push_back( UpgradeSequence( UpgradeSequenceSingle( Upgrade_FLY_BLOB, 0, 2, 5, 7.5, 10 ) ) );

		f.push_back( UpgradeSequence( UpgradeSequenceSingle( Upgrade_FLY_BLOB, 0, 2, 5, 7.5, 10 ), UpgradeSequenceSingle( Upgrade_FALLING_BLOCK, 1, 3.5, 5, 7.5, 10 ), UpgradeSequenceSingle( Upgrade_MOVING_BLOCK, 1, 3.5, 5, 7.5, 10 ), UpgradeSequenceSingle( Upgrade_GHOST_BLOCK, 1, 3.5, 5, 7.5, 10 ), UpgradeSequenceSingle( Upgrade_JUMP, 0, 3, 5, 7.5, 8 ), UpgradeSequenceSingle( Upgrade_SPEED, 0, 3, 5, 8.5, 15 ) ) );
	}

	std::vector<DifficultyGroups::UpgradeSequence> DifficultyGroups::DownUpgrades;

	void DifficultyGroups::MakeDownUpgrades()
	{
		std::vector<UpgradeSequence> &f = DownUpgrades;

		f.push_back( UpgradeSequence( UpgradeSequenceSingle( Upgrade_FLY_BLOB, 0, 2, 5, 7.5, 10 ), UpgradeSequenceSingle( Upgrade_FALLING_BLOCK, 1, 3.5, 5, 7.5, 10 ), UpgradeSequenceSingle( Upgrade_MOVING_BLOCK, 1, 3.5, 5, 7.5, 10 ), UpgradeSequenceSingle( Upgrade_GHOST_BLOCK, 1, 3.5, 5, 7.5, 10 ), UpgradeSequenceSingle( Upgrade_JUMP, 0, 3, 5, 7.5, 10 ), UpgradeSequenceSingle( Upgrade_SPEED, 0, 3, 4, 7, 10 ), UpgradeSequenceSingle( Upgrade_LASER, 0, 1, 2, 5, 7.3 ) ) );

		f.push_back( UpgradeSequence( UpgradeSequenceSingle( Upgrade_FLY_BLOB, 0, 2, 5, 7.5, 10 ), UpgradeSequenceSingle( Upgrade_FALLING_BLOCK, 1, 3.5, 5, 7.5, 10 ), UpgradeSequenceSingle( Upgrade_MOVING_BLOCK, 1, 3.5, 5, 7.5, 10 ), UpgradeSequenceSingle( Upgrade_GHOST_BLOCK, 1, 3.5, 5, 7.5, 10 ), UpgradeSequenceSingle( Upgrade_JUMP, 0, 3, 5, 7.5, 10 ), UpgradeSequenceSingle( Upgrade_SPEED, 0, 3, 4, 7, 10 ), UpgradeSequenceSingle( Upgrade_SPIKEY_LINE, 0, 1, 2, 5, 7.3 ) ) );
	}

	std::vector<DifficultyGroups::UpgradeSequence> DifficultyGroups::CartUpgrades;

	void DifficultyGroups::MakeCartUpgrades()
	{
		std::vector<UpgradeSequence> &f = CartUpgrades;

		f.push_back( UpgradeSequence( UpgradeSequenceSingle( Upgrade_JUMP, 0, 1, 2, 3, 4 ), UpgradeSequenceSingle( Upgrade_SPEED, 1, 2, 3, 4, 5 ), UpgradeSequenceSingle( Upgrade_FALLING_BLOCK, 1, 2, 3, 6, 9 ), UpgradeSequenceSingle( Upgrade_FIRE_SPINNER, 1, 3, 7, 9, 10 ), UpgradeSequenceSingle( Upgrade_SPIKEY_LINE, 0, 2, 3.6, 7, 9 ), UpgradeSequenceSingle( Upgrade_LASER, 1, 3, 6, 7, 8.5 ) ) );
			//new UpgradeSequenceSingle(Upgrade.MovingBlock, 1, 2, 3, 6, 9),

		f.push_back( UpgradeSequence( UpgradeSequenceSingle( Upgrade_JUMP, 0, 1, 2, 3, 4 ), UpgradeSequenceSingle( Upgrade_SPEED, 1, 2, 3, 4, 5 ), UpgradeSequenceSingle( Upgrade_GHOST_BLOCK, 1, 2, 3, 6, 9 ), UpgradeSequenceSingle( Upgrade_FALLING_BLOCK, 1, 2, 3, 6, 9 ), UpgradeSequenceSingle( Upgrade_SPIKEY_GUY, 1, 2, 3.6, 7, 9 ), UpgradeSequenceSingle( Upgrade_SPIKE, 2, 3, 7, 9, 9 ), UpgradeSequenceSingle( Upgrade_LASER, 0, 3, 5, 7, 8.5 ) ) );

		f.push_back( UpgradeSequence( UpgradeSequenceSingle( Upgrade_JUMP, 0, 1, 2, 3, 4 ), UpgradeSequenceSingle( Upgrade_SPEED, 1, 2, 3, 4, 5 ), UpgradeSequenceSingle( Upgrade_BOUNCY_BLOCK, 1, 2, 3, 6, 9 ), UpgradeSequenceSingle( Upgrade_LASER, 0, 3, 5, 7, 8.5 ), UpgradeSequenceSingle( Upgrade_SPIKEY_LINE, 1, 2, 3.6, 7, 9 ), UpgradeSequenceSingle( Upgrade_PINKY, 1, 3, 7, 8, 8.5 ) ) );

		f.push_back( UpgradeSequence( UpgradeSequenceSingle( Upgrade_JUMP, 0, 1, 2, 3, 4 ), UpgradeSequenceSingle( Upgrade_SPEED, 1, 2, 3, 4, 5 ), UpgradeSequenceSingle( Upgrade_GHOST_BLOCK, 1, 2, 3, 6, 9 ), UpgradeSequenceSingle( Upgrade_FIRE_SPINNER, 1, 3, 7, 9, 10 ), UpgradeSequenceSingle( Upgrade_SPIKEY_LINE, 0, 2, 3.6, 7, 9 ), UpgradeSequenceSingle( Upgrade_PINKY, 1, 3, 6, 7, 8.5 ), UpgradeSequenceSingle( Upgrade_SPIKE, 1, 3, 6, 7, 8.5 ) ) );
			//new UpgradeSequenceSingle(Upgrade.FlyBlob, 1, 2, 2, 2, 8),
			//new UpgradeSequenceSingle(Upgrade.MovingBlock, 1, 2, 3, 6, 9),
	}

	std::vector<DifficultyGroups::UpgradeSequence> DifficultyGroups::EasyUpgrades;

	void DifficultyGroups::MakeEasyUpgrades()
	{
		std::vector<UpgradeSequence> &f = EasyUpgrades;

		f.push_back( UpgradeSequence( UpgradeSequenceSingle( Upgrade_JUMP, 2, 5, 5, 5, 5 ), UpgradeSequenceSingle( Upgrade_SPEED, 1, 2, 3, 5, 11 ), UpgradeSequenceSingle( Upgrade_MOVING_BLOCK, 1, 1, 2.2, 3, 3 ), UpgradeSequenceSingle( Upgrade_FALLING_BLOCK, 1, 1, 2.2, 3, 3 ), UpgradeSequenceSingle( Upgrade_FLY_BLOB, 1, 1, 2.2, 2.2, 2.2 ), UpgradeSequenceSingle( Upgrade_FIRE_SPINNER, 1, 3, 5, 7, 9 ), UpgradeSequenceSingle( Upgrade_SPIKEY_LINE, 0, 3, 5, 7, 9 ) ) );

		f.push_back( UpgradeSequence( UpgradeSequenceSingle( Upgrade_JUMP, 2, 5, 5, 5, 5 ), UpgradeSequenceSingle( Upgrade_SPEED, 1, 2, 3, 5, 11 ), UpgradeSequenceSingle( Upgrade_MOVING_BLOCK, 1, 1, 2.2, 3, 3 ), UpgradeSequenceSingle( Upgrade_FALLING_BLOCK, 1, 1, 2.2, 3, 3 ), UpgradeSequenceSingle( Upgrade_FIRE_SPINNER, 1, 3, 5, 7, 10 ), UpgradeSequenceSingle( Upgrade_SPIKE, 1, 3, 5, 7, 10 ), UpgradeSequenceSingle( Upgrade_LASER, 0, 0, 0, 3, 6 ) ) );

		f.push_back( UpgradeSequence( UpgradeSequenceSingle( Upgrade_JUMP, 2, 5, 5, 5, 5 ), UpgradeSequenceSingle( Upgrade_SPEED, 1, 2, 3, 5, 11 ), UpgradeSequenceSingle( Upgrade_MOVING_BLOCK, 1, 1, 2.2, 3, 3 ), UpgradeSequenceSingle( Upgrade_FALLING_BLOCK, 1, 1, 2.2, 3, 3 ), UpgradeSequenceSingle( Upgrade_FLY_BLOB, 1, 1, 2.2, 2.2, 2.2 ), UpgradeSequenceSingle( Upgrade_PINKY,.75f, 3, 5, 7, 9 ), UpgradeSequenceSingle( Upgrade_SPIKE, 1, 3, 5, 7, 9 ), UpgradeSequenceSingle( Upgrade_FIRE_SPINNER, 0, 2, 3, 4, 7 ) ) );


		f.push_back( UpgradeSequence( UpgradeSequenceSingle( Upgrade_JUMP, 2, 5, 5, 5, 5 ), UpgradeSequenceSingle( Upgrade_SPEED, 1, 2, 3, 5, 11 ), UpgradeSequenceSingle( Upgrade_MOVING_BLOCK, 1, 1, 2.2, 3, 3 ), UpgradeSequenceSingle( Upgrade_BOUNCY_BLOCK, 1, 1, 2.2, 3, 3 ), UpgradeSequenceSingle( Upgrade_GHOST_BLOCK, 1, 1, 2.2, 2.2, 2.2 ), UpgradeSequenceSingle( Upgrade_PINKY,.75f, 3, 5, 7, 9 ), UpgradeSequenceSingle( Upgrade_SPIKE, 1, 3, 5, 7, 9 ), UpgradeSequenceSingle( Upgrade_FIRE_SPINNER, 0, 2, 3, 4, 7 ) ) );




		// Older

		f.push_back( UpgradeSequence( UpgradeSequenceSingle( Upgrade_JUMP, 2, 5, 5, 5, 5 ), UpgradeSequenceSingle( Upgrade_SPEED, 1, 2, 3, 5, 11 ), UpgradeSequenceSingle( Upgrade_MOVING_BLOCK, 1, 1, 2.2, 3, 3 ), UpgradeSequenceSingle( Upgrade_BOUNCY_BLOCK, 1, 1, 2.2, 3, 3 ), UpgradeSequenceSingle( Upgrade_ELEVATOR, 1, 1, 2.2, 2.2, 2.2 ), UpgradeSequenceSingle( Upgrade_PINKY,.8f, 3, 5, 7, 9 ), UpgradeSequenceSingle( Upgrade_SPIKE, 1, 3, 5, 7, 9 ), UpgradeSequenceSingle( Upgrade_LASER, 0, 2, 3, 4, 7 ) ) );

		f.push_back( UpgradeSequence( UpgradeSequenceSingle( Upgrade_JUMP, 2, 4.8, 7.0, 8.4, 10 ), UpgradeSequenceSingle( Upgrade_SPEED, 1, 2, 8.2, 9.1, 11 ), UpgradeSequenceSingle( Upgrade_MOVING_BLOCK, 1, 1, 2.2, 8, 10 ), UpgradeSequenceSingle( Upgrade_FALLING_BLOCK, 1, 1, 2.2, 7, 10 ), UpgradeSequenceSingle( Upgrade_FLY_BLOB, 1, 1, 2.2, 7, 10 ) ) );
			//u[Upgrade.Fireball] =       D(0,   0,   0,   0,   4);

		f.push_back( UpgradeSequence( UpgradeSequenceSingle( Upgrade_SPIKEY_GUY, 2, 4, 5.2, 8, 10 ), UpgradeSequenceSingle( Upgrade_JUMP, 3, 2.5, 2, 4, 4.5 ), UpgradeSequenceSingle( Upgrade_SPIKE, 0, 3, 7.5, 9, 10 ), UpgradeSequenceSingle( Upgrade_SPEED, 0, 2, 5.5, 8.8, 10 ) ) );

		f.push_back( UpgradeSequence( UpgradeSequenceSingle( Upgrade_JUMP, 3.5f, 1, 0, 0, 0 ), UpgradeSequenceSingle( Upgrade_SPIKEY_GUY, 0, 3.2, 5.5, 8, 10 ), UpgradeSequenceSingle( Upgrade_PINKY, 1.2f, 3, 5.5, 8, 10 ), UpgradeSequenceSingle( Upgrade_SPIKE, 0, 0, 0, 4, 10 ), UpgradeSequenceSingle( Upgrade_SPEED, 2, 3, 4, 8.8, 10 ), UpgradeSequenceSingle( Upgrade_CEILING, 1, 2, 4, 7, 10 ) ) );

		f.push_back( UpgradeSequence( UpgradeSequenceSingle( Upgrade_LASER, 2.5, 4, 5.5, 7.9, 10 ), UpgradeSequenceSingle( Upgrade_SPEED, 0, 0, 0, 1, 5 ), UpgradeSequenceSingle( Upgrade_CEILING, 1, 2, 4, 4, 4 ) ) );

		f.push_back( UpgradeSequence( UpgradeSequenceSingle( Upgrade_JUMP, 3.6, 2, 0, 0, 0 ), UpgradeSequenceSingle( Upgrade_SPEED, 0, 0, 0, 1, 3 ), UpgradeSequenceSingle( Upgrade_FIRE_SPINNER, 0, 1.5, 4, 6, 9 ), UpgradeSequenceSingle( Upgrade_PINKY, 0, 1.5, 3.6, 5.7, 8 ), UpgradeSequenceSingle( Upgrade_FALLING_BLOCK, 0, 1, 4, 6, 8 ), UpgradeSequenceSingle( Upgrade_CLOUD, 2, 2.5, 4, 6, 9 ), UpgradeSequenceSingle( Upgrade_SPIKEY_GUY, 2, 3, 3.5, 5.6, 10 ), UpgradeSequenceSingle( Upgrade_BOUNCY_BLOCK, 0, 0, 4, 6, 8 ) ) );

		f.push_back( UpgradeSequence( UpgradeSequenceSingle( Upgrade_LASER, 2, 3.5, 4.2, 6, 9 ), UpgradeSequenceSingle( Upgrade_SPEED, 0, 1, 1.7, 3, 3 ), UpgradeSequenceSingle( Upgrade_ELEVATOR, 2.8f, 5, 7, 9, 9 ), UpgradeSequenceSingle( Upgrade_MOVING_BLOCK, 1.8f, 3, 3, 3, 3 ) ) );

		f.push_back( UpgradeSequence( UpgradeSequenceSingle( Upgrade_SPIKEY_LINE,.7f, 2, 4, 8.4, 9.5 ), UpgradeSequenceSingle( Upgrade_SPEED, 0, 2, 3, 4.5, 10 ), UpgradeSequenceSingle( Upgrade_ELEVATOR, 2, 3, 3, 4, 10 ), UpgradeSequenceSingle( Upgrade_MOVING_BLOCK, 0, 2, 4, 4, 4 ), UpgradeSequenceSingle( Upgrade_FLY_BLOB, 0, 2, 4, 4, 4 ), UpgradeSequenceSingle( Upgrade_FIRE_SPINNER, 0, 2, 4, 4, 4 ), UpgradeSequenceSingle( Upgrade_JUMP, 1, 3, 4, 4, 4 ), UpgradeSequenceSingle( Upgrade_CLOUD, 0, 1, 2, 3, 4 ), UpgradeSequenceSingle( Upgrade_CEILING, 1, 2, 4, 7, 10 ) ) );

		f.push_back( UpgradeSequence( UpgradeSequenceSingle( Upgrade_SPIKEY_GUY,.7f, 3, 4.5, 7.6, 9.5 ), UpgradeSequenceSingle( Upgrade_SPEED,.7f, 3, 3.5, 8, 10 ), UpgradeSequenceSingle( Upgrade_ELEVATOR, 3, 6, 7, 9, 9 ), UpgradeSequenceSingle( Upgrade_LASER, 0, 0, 0, 0, 4 ), UpgradeSequenceSingle( Upgrade_CEILING, 1, 2, 4, 7, 10 ) ) );

		f.push_back( UpgradeSequence( UpgradeSequenceSingle( Upgrade_BOUNCY_BLOCK, 3.6f, 8.2, 9, 9, 10 ), UpgradeSequenceSingle( Upgrade_SPIKE, 2, 7.5, 8.5, 9, 10 ), UpgradeSequenceSingle( Upgrade_FALLING_BLOCK, 4, 2, 2, 3, 4 ), UpgradeSequenceSingle( Upgrade_SPEED, 0, 0, 2, 5, 10 ), UpgradeSequenceSingle( Upgrade_FIRE_SPINNER, 0, 1, 3, 6, 9 ), UpgradeSequenceSingle( Upgrade_PINKY, 0, 0, 0, 0, 6 ) ) );

		f.push_back( UpgradeSequence( UpgradeSequenceSingle( Upgrade_LASER, 1.8f, 3, 4, 6, 9.5 ), UpgradeSequenceSingle( Upgrade_SPEED, 0, 0, 0, 1, 3 ), UpgradeSequenceSingle( Upgrade_FIRE_SPINNER, 1, 3, 6, 9, 9 ), UpgradeSequenceSingle( Upgrade_JUMP, 3, 4, 4, 0, 0 ) ) );

		f.push_back( UpgradeSequence( UpgradeSequenceSingle( Upgrade_BOUNCY_BLOCK, 4, 8.2, 9, 9, 10 ), UpgradeSequenceSingle( Upgrade_SPIKE, 0, 7.5, 8.5, 9, 10 ), UpgradeSequenceSingle( Upgrade_MOVING_BLOCK, 0, 2, 2, 4, 9 ), UpgradeSequenceSingle( Upgrade_SPEED, 0, 0, 2, 6, 10 ), UpgradeSequenceSingle( Upgrade_SPIKEY_LINE, 0, 0, 0, 0, 4 ) ) );
			//u[Upgrade.Fireball] =       D(0,   0,   0,  .5,   4);

		f.push_back( UpgradeSequence( UpgradeSequenceSingle( Upgrade_FIRE_SPINNER, 1, 1.5, 2.5, 4, 8 ), UpgradeSequenceSingle( Upgrade_PINKY, 1, 2, 3.5, 6, 10 ), UpgradeSequenceSingle( Upgrade_MOVING_BLOCK, 1, 3, 4, 9, 10 ), UpgradeSequenceSingle( Upgrade_CEILING, 1, 2, 4, 7, 10 ) ) );
	}

	std::vector<DifficultyGroups::UpgradeSequence> DifficultyGroups::NormalUpgrades;

	void DifficultyGroups::MakeNormalUpgrades()
	{
		std::vector<UpgradeSequence> &f = NormalUpgrades;
		AddRange( f, EasyUpgrades );

		f.push_back( UpgradeSequence( UpgradeSequenceSingle( Upgrade_JUMP, -1, 4.8, 7.5, 9, 10 ), UpgradeSequenceSingle( Upgrade_SPEED, -1, 0, 6, 9, 10 ), UpgradeSequenceSingle( Upgrade_MOVING_BLOCK, -1, 2, 2, 6, 10 ), UpgradeSequenceSingle( Upgrade_GHOST_BLOCK, -1, 2, 2, 6, 10 ), UpgradeSequenceSingle( Upgrade_BOUNCY_BLOCK, -1, 2, 2, 4, 10 ), UpgradeSequenceSingle( Upgrade_FLY_BLOB, -1, 2, 2, 4, 10 ), UpgradeSequenceSingle( Upgrade_SPIKE, -1, 2, 2, 9, 10 ) ) );

		f.push_back( UpgradeSequence( UpgradeSequenceSingle( Upgrade_JUMP, -1, 4, 4, 4, 4 ), UpgradeSequenceSingle( Upgrade_SPEED, -1, 2, 2, 5, 10 ), UpgradeSequenceSingle( Upgrade_MOVING_BLOCK, -1, 2, 4, 7, 10 ), UpgradeSequenceSingle( Upgrade_BOUNCY_BLOCK, -1, 2, 4, 7, 10 ), UpgradeSequenceSingle( Upgrade_FIRE_SPINNER, -1, 2, 4, 8, 10 ), UpgradeSequenceSingle( Upgrade_LASER, -1, 0, 0, 0, 5.5 ) ) );

		/*
		f.Add(new UpgradeSequence(
		    u[Upgrade.Speed] =       D(-1, 2, 4, 7, 10);
		    u[Upgrade.Fireball] =    D(-1, 2, 4, 7, 10);
		    u[Upgrade.Laser] =       D(-1, 2, 3, 4, 8);
		    new UpgradeSequenceSingle(Upgrade.FireSpinner, -1, 2, 4, 7, 10),
		    u[Upgrade.Spike] =       D(-1, 2, 4, 7, 10);
		});*/

		f.push_back( UpgradeSequence( UpgradeSequenceSingle( Upgrade_MOVING_BLOCK, -1, 6, 8.5, 9, 10 ), UpgradeSequenceSingle( Upgrade_JUMP, -1, 4, 2, 0, 0 ), UpgradeSequenceSingle( Upgrade_SPEED, -1, 3, 5.5, 9, 9 ), UpgradeSequenceSingle( Upgrade_FIRE_SPINNER, -1, 0, 5, 9, 9 ), UpgradeSequenceSingle( Upgrade_SPIKE, -1, 0, 0, 3, 9 ), UpgradeSequenceSingle( Upgrade_CEILING, 1, 2, 4, 7, 10 ) ) );

		f.push_back( UpgradeSequence( UpgradeSequenceSingle( Upgrade_JUMP, -1, 0, 0, 5, 8 ), UpgradeSequenceSingle( Upgrade_FLY_BLOB, -1, 2, 4, 7, 10 ), UpgradeSequenceSingle( Upgrade_FALLING_BLOCK, -1, 2, 3, 4, 10 ), UpgradeSequenceSingle( Upgrade_SPEED, -1, 4, 6, 9, 10 ), UpgradeSequenceSingle( Upgrade_GHOST_BLOCK, -1, 5, 6, 9, 10 ) ) );
			//u[Upgrade.Fireball] =       D(-1, 0, 0, 0, 5);

		f.push_back( UpgradeSequence( UpgradeSequenceSingle( Upgrade_MOVING_BLOCK, -1, 2, 4, 7, 10 ), UpgradeSequenceSingle( Upgrade_FLY_BLOB, -1, 2, 4, 7, 10 ), UpgradeSequenceSingle( Upgrade_FALLING_BLOCK, -1, 2, 4, 7, 10 ), UpgradeSequenceSingle( Upgrade_SPIKEY_GUY, -1, 1, 3, 6, 10 ), UpgradeSequenceSingle( Upgrade_FIRE_SPINNER, -1, 1, 4, 7, 10 ), UpgradeSequenceSingle( Upgrade_PINKY, -1, 1, 3, 6, 10 ), UpgradeSequenceSingle( Upgrade_SPEED, -1, 0, 0, 2, 9 ) ) );

		/*
		f.Add(new UpgradeSequence(
		    u[Upgrade.Speed] =       D(-1, 0, 1, 3, 10);
		    u[Upgrade.Jump] =        D(-1, 3, 5, 8, 10);
		    u[Upgrade.Fireball] =    D(-1, 2, 4, 7, 10);
		    u[Upgrade.Pinky] =       D(-1, 2, 4, 8, 10);
		    u[Upgrade.FlyBlob] =     D(-1, 2, 4, 7, 10);
		});
	
		f.Add(new UpgradeSequence(
		    u[Upgrade.Speed] =       D(-1, 0, 1, 3, 10);
		    u[Upgrade.Fireball] =    D(-1, 2, 4, 7, 10);
		    u[Upgrade.Pinky] =       D(-1, 2, 4, 8, 10);
		    new UpgradeSequenceSingle(Upgrade.BouncyBlock, -1, 2, 4, 7, 10)
		));
	
		f.Add(new UpgradeSequence(
		    u[Upgrade.Speed] =       D(-1, 3, 4, 7, 10);
		    u[Upgrade.Fireball] =    D(-1, 5, 7, 9, 10);
		    u[Upgrade.Spike] =       D(-1, 0, 0, 0, 10);
		});*/

		f.push_back( UpgradeSequence( UpgradeSequenceSingle( Upgrade_JUMP, -1, 2, 4, 7, 10 ), UpgradeSequenceSingle( Upgrade_SPEED, -1, 2, 3, 5, 10 ), UpgradeSequenceSingle( Upgrade_MOVING_BLOCK, -1, 4, 5, 7, 10 ), UpgradeSequenceSingle( Upgrade_SPIKEY_GUY, -1, 1.2, 2.7, 6, 10 ), UpgradeSequenceSingle( Upgrade_FIRE_SPINNER, -1, 1.5, 4, 8, 10 ) ) );
		/*
		f.Add(new UpgradeSequence(
		    u[Upgrade.Fireball] =    D(-1, 2,   4,   7,   10);
		    new UpgradeSequenceSingle(Upgrade.FireSpinner, -1, 2,   3,   7,   10),
		    u[Upgrade.FlyBlob] =     D(-1, 2,   4,   7,   10);
		    new UpgradeSequenceSingle(Upgrade.MovingBlock, -1, 4,   6,   9,   10),
		    u[Upgrade.Speed] =       D(-1, 0,   1,   3.5,  7);
		});*/

		f.push_back( UpgradeSequence( UpgradeSequenceSingle( Upgrade_JUMP, -1, 5.1, 7.5, 9, 10 ), UpgradeSequenceSingle( Upgrade_GHOST_BLOCK, -1, 2, 7, 9, 10 ), UpgradeSequenceSingle( Upgrade_SPEED, -1, 0, 2, 3.5, 10 ) ) );
			//u[Upgrade.Fireball] =   D(-1,   0, 0,     4,   7);

		f.push_back( UpgradeSequence( UpgradeSequenceSingle( Upgrade_JUMP, -1, 5, 7.5, 9, 10 ), UpgradeSequenceSingle( Upgrade_SPEED, -1, 2, 4, 6, 7 ), UpgradeSequenceSingle( Upgrade_LASER, -1, 1, 4, 6, 8.5 ), UpgradeSequenceSingle( Upgrade_FALLING_BLOCK, -1, 6.5, 9, 9, 10 ), UpgradeSequenceSingle( Upgrade_FLY_BLOB, -1, 2, 2, 9, 10 ), UpgradeSequenceSingle( Upgrade_CEILING, 1, 2, 3, 3, 4 ) ) );


		f.push_back( UpgradeSequence( UpgradeSequenceSingle( Upgrade_BOUNCY_BLOCK, -1, 2, 4, 7, 10 ), UpgradeSequenceSingle( Upgrade_FLY_BLOB, -1, 2, 4, 7, 10 ), UpgradeSequenceSingle( Upgrade_SPIKE, -1, 2, 4, 9, 10 ), UpgradeSequenceSingle( Upgrade_SPEED, -1, 0, 0, 6, 10 ), UpgradeSequenceSingle( Upgrade_FIRE_SPINNER, -1, 0, 0, 4, 10 ), UpgradeSequenceSingle( Upgrade_SPIKEY_LINE, -1, 0, 0, 3, 6 ) ) );
	}

	std::vector<DifficultyGroups::UpgradeSequence> DifficultyGroups::AbusiveUpgrades;

	void DifficultyGroups::MakeAbusiveUpgrades()
	{
		std::vector<UpgradeSequence> &f = AbusiveUpgrades;
		AddRange( f, NormalUpgrades );

		f.push_back( UpgradeSequence( UpgradeSequenceSingle( Upgrade_JUMP, -1, -1, 4, 6, 9 ), UpgradeSequenceSingle( Upgrade_SPEED, -1, -1, 4, 6, 9 ), UpgradeSequenceSingle( Upgrade_MOVING_BLOCK, -1, -1, 4, 4, 4 ), UpgradeSequenceSingle( Upgrade_GHOST_BLOCK, -1, -1, 3, 4, 4 ), UpgradeSequenceSingle( Upgrade_FLY_BLOB, -1, -1, 4, 4, 4 ), UpgradeSequenceSingle( Upgrade_PINKY, -1, -1, 2, 4, 7 ), UpgradeSequenceSingle( Upgrade_LASER, -1, -1, 2, 4, 5.5 ) ) );

		f.push_back( UpgradeSequence( UpgradeSequenceSingle( Upgrade_CLOUD, -1, -1, 2, 2, 4 ), UpgradeSequenceSingle( Upgrade_FIRE_SPINNER, -1, -1, 4, 8, 10 ), UpgradeSequenceSingle( Upgrade_FLY_BLOB, -1, -1, 5, 8, 10 ), UpgradeSequenceSingle( Upgrade_JUMP, -1, -1, 4, 6, 9 ), UpgradeSequenceSingle( Upgrade_SPEED, -1, -1, 2, 4, 6 ), UpgradeSequenceSingle( Upgrade_MOVING_BLOCK, -1, -1, 4, 4, 4 ), UpgradeSequenceSingle( Upgrade_CEILING, -1, -1, 4, 7, 10 ) ) );

		f.push_back( UpgradeSequence( UpgradeSequenceSingle( Upgrade_JUMP, -1, -1, 7, 9, 9 ), UpgradeSequenceSingle( Upgrade_SPEED, -1, -1, 4, 8, 9 ), UpgradeSequenceSingle( Upgrade_SPIKEY_GUY, -1, -1, 5.4, 8.5, 10 ), UpgradeSequenceSingle( Upgrade_FALLING_BLOCK, -1, -1, 9, 9, 9 ), UpgradeSequenceSingle( Upgrade_FLY_BLOB, -1, -1, 2, 6, 9 ) ) );

		f.push_back( UpgradeSequence( UpgradeSequenceSingle( Upgrade_JUMP, -1, -1, 7, 9, 10 ), UpgradeSequenceSingle( Upgrade_SPEED, -1, -1, 4, 6, 9 ), UpgradeSequenceSingle( Upgrade_FALLING_BLOCK, -1, -1, 9, 9, 9 ), UpgradeSequenceSingle( Upgrade_BOUNCY_BLOCK, -1, -1, 8, 9, 9 ), UpgradeSequenceSingle( Upgrade_SPIKEY_GUY, -1, -1, 3, 6, 10 ), UpgradeSequenceSingle( Upgrade_PINKY, -1, -1, 4, 7, 10 ) ) );

		f.push_back( UpgradeSequence( UpgradeSequenceSingle( Upgrade_FIRE_SPINNER, -1, -1, 2, 5, 9 ), UpgradeSequenceSingle( Upgrade_FLY_BLOB, -1, -1, 2, 2, 2 ), UpgradeSequenceSingle( Upgrade_LASER, -1, -1, 2, 4, 6 ), UpgradeSequenceSingle( Upgrade_GHOST_BLOCK, -1, -1, 2, 7, 9 ), UpgradeSequenceSingle( Upgrade_SPEED, -1, -1, 6, 8, 9 ), UpgradeSequenceSingle( Upgrade_CEILING, -1, -1, 4, 7, 10 ) ) );
	}

	std::vector<DifficultyGroups::UpgradeSequence> DifficultyGroups::HardcoreUpgrades;

	void DifficultyGroups::MakeHardcoreUpgrades()
	{
		std::vector<UpgradeSequence> &f = HardcoreUpgrades;
		AddRange( f, AbusiveUpgrades );

		f.push_back( UpgradeSequence( UpgradeSequenceSingle( Upgrade_FIRE_SPINNER, -1, -1, -1, 9, 10 ), UpgradeSequenceSingle( Upgrade_SPEED, -1, -1, -1, 5, 8 ), UpgradeSequenceSingle( Upgrade_MOVING_BLOCK, -1, -1, -1, 2, 2 ) ) );
	}
}
