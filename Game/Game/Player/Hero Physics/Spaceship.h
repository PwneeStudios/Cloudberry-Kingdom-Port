#ifndef SPACESHIP
#define SPACESHIP

#include <global_header.h>

namespace CloudberryKingdom
{
	class BobPhsxSpaceship : public BobPhsx
	{
	public:
		static float KeepUnused( float UpgradeLevel );

		// Singleton
	protected:
		virtual void InitSingleton();
	private:
		static const std::shared_ptr<BobPhsxSpaceship> instance;
	public:
		const static std::shared_ptr<BobPhsxSpaceship> &getInstance();

		// Instancable class
	private:
		int AutoMoveLength, AutoMoveType, AutoStrafeLength;
		int AutoDirLength, AutoDir;

		int RndMoveType;

	public:
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

	private:
		int Dir;
	public:
		void GenerateInput_Vertical( int CurPhsxStep );

		virtual void GenerateInput( int CurPhsxStep );

	private:
		void GenerateInput_Right( int CurPhsxStep );

	public:
		virtual void AnimStep();

		virtual void ToSprites( std::map<int, SpriteAnim*> &SpriteAnims, Vector2 Padding );

		virtual void Die( BobDeathType DeathType );

		virtual void BlockInteractions();

		virtual void ModData( std::shared_ptr<MakeData> &makeData, const std::shared_ptr<StyleData> &Style );

		virtual void ModLadderPiece( const std::shared_ptr<PieceSeedData> &piece );

	private:
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef SPACESHIP
