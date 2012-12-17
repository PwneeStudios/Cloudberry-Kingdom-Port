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
	
		static boost::shared_ptr<BobPhsxSpaceship> instance;
	
		const static boost::shared_ptr<BobPhsxSpaceship> &getInstance();

		virtual boost::shared_ptr<BobPhsx> Clone();
		void CopyTo( const boost::shared_ptr<BobPhsxSpaceship> &bob );

		// Instancable struct
	
		int AutoMoveLength, AutoMoveType, AutoStrafeLength;
		int AutoDirLength, AutoDir;

		int RndMoveType;

	
		BobPhsxSpaceship();

		virtual void DefaultValues();

		virtual void Init( const boost::shared_ptr<Bob> &bob );

		virtual void PhsxStep();

		virtual void SideHit( ColType side, const boost::shared_ptr<BlockBase> &block );

		virtual void PhsxStep2();

		virtual bool CheckFor_xFlip();

		virtual void Jump();

		virtual void LandOnSomething( bool MakeReadyToJump, const boost::shared_ptr<ObjectBase> &ThingLandedOn );

		virtual void HitHeadOnSomething( const boost::shared_ptr<ObjectBase> &ThingHit );

	
		int Dir;
	
		void GenerateInput_Vertical( int CurPhsxStep );

		virtual void GenerateInput( int CurPhsxStep );

	
		void GenerateInput_Right( int CurPhsxStep );

	
		virtual void AnimStep();

		virtual void ToSprites( std::map<int, boost::shared_ptr<SpriteAnim> > &SpriteAnims, Vector2 Padding );

		virtual void Die( BobDeathType DeathType );

		virtual void BlockInteractions();

		virtual void ModData( boost::shared_ptr<MakeData> &makeData, const boost::shared_ptr<StyleData> &Style );

		virtual void ModLadderPiece( const boost::shared_ptr<PieceSeedData> &piece );

	
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef SPACESHIP
