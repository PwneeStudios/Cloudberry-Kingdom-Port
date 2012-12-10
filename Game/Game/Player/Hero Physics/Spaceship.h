#ifndef SPACESHIP
#define SPACESHIP

#include <global_header.h>

namespace CloudberryKingdom
{
	struct BobPhsxSpaceship : public BobPhsx
	{

	
		static void InitializeStatics();

	
		static float KeepUnused( float UpgradeLevel );

		// Singleton
	
		virtual void InitSingleton();
	
		static std::shared_ptr<BobPhsxSpaceship> instance;
	
		const static std::shared_ptr<BobPhsxSpaceship> &getInstance();

		virtual std::shared_ptr<BobPhsx> Clone();
		void CopyTo( const std::shared_ptr<BobPhsxSpaceship> &bob );

		// Instancable struct
	
		int AutoMoveLength, AutoMoveType, AutoStrafeLength;
		int AutoDirLength, AutoDir;

		int RndMoveType;

	
		BobPhsxSpaceship();

		virtual void DefaultValues();

		virtual void Init( const std::shared_ptr<Bob> &bob );

		virtual void PhsxStep();

		virtual void SideHit( ColType side, const std::shared_ptr<BlockBase> &block );

		virtual void PhsxStep2();

		virtual bool CheckFor_xFlip();

		virtual void Jump();

		virtual void LandOnSomething( bool MakeReadyToJump, const std::shared_ptr<ObjectBase> &ThingLandedOn );

		virtual void HitHeadOnSomething( const std::shared_ptr<ObjectBase> &ThingHit );

	
		int Dir;
	
		void GenerateInput_Vertical( int CurPhsxStep );

		virtual void GenerateInput( int CurPhsxStep );

	
		void GenerateInput_Right( int CurPhsxStep );

	
		virtual void AnimStep();

		virtual void ToSprites( std::map<int, std::shared_ptr<SpriteAnim> > &SpriteAnims, Vector2 Padding );

		virtual void Die( BobDeathType DeathType );

		virtual void BlockInteractions();

		virtual void ModData( std::shared_ptr<MakeData> &makeData, const std::shared_ptr<StyleData> &Style );

		virtual void ModLadderPiece( const std::shared_ptr<PieceSeedData> &piece );

	
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef SPACESHIP
