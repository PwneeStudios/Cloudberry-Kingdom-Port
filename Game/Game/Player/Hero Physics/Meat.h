#ifndef MEAT
#define MEAT

#include <global_header.h>

namespace CloudberryKingdom
{
	struct BobPhsxMeat : public BobPhsxNormal
	{

	
		static void InitializeStatics();

	
		virtual void Release();

		virtual void Set( const std::shared_ptr<BobPhsx> &phsx );
		void Set( const std::shared_ptr<BobPhsx> &phsx, Vector2 modsize );

		// Singleton
	
		virtual void InitSingleton();
	
		static std::shared_ptr<BobPhsxMeat> instance;
	
		const static std::shared_ptr<BobPhsxMeat> &getInstance();

		virtual std::shared_ptr<BobPhsx> Clone();
		void CopyTo( const std::shared_ptr<BobPhsxMeat> &bob );

		// Instancable struct
		BobPhsxMeat();

		virtual void Init( const std::shared_ptr<Bob> &bob );

	
		bool LastJumpWasSticky;
	
		int StepsSinceSide, StepsOnSide;
		int StickyDuration;
	
		ColType StickySide;
		std::shared_ptr<BlockBase> LastStickyBlock;
		bool IsStuck;
	
		virtual void SideHit( ColType side, const std::shared_ptr<BlockBase> &block );

		virtual void LandOnSomething( bool MakeReadyToJump, const std::shared_ptr<ObjectBase> &ThingLandedOn );

	
		bool CanWallJump;
	
		int WallJumpCount;
	
		int StickyGracePeriod;
	
		float Max_yVel_ForWallJump;

	
		int SideJumpLength;
		float SideJumpStr;

	
		virtual void Jump();

	
		float SideToDir( ColType side );

		float getStickyDir();

	
		virtual void PhsxStep();

		virtual void DoXAccel();

		virtual float GetXAccel();

	
		virtual void DoJump();

	
		virtual bool ShouldStartJumpAnim();

	
		virtual void SetTarget( const std::shared_ptr<RichLevelGenData> &GenData );

	
		Vector2 PrefferedDir;
		void NewTarget();

	
		bool WantToLandOnTop;
	
		Vector2 Target;
		Vector2 AlwaysForward;
		int StraightUpDuration;
		float yVelCutoff;
	
		virtual void GenerateInput( int CurPhsxStep );

		virtual bool IsTopCollision( ColType Col, const std::shared_ptr<AABox> &box, const std::shared_ptr<BlockBase> &block );

		virtual bool IsBottomCollision( ColType Col, const std::shared_ptr<AABox> &box, const std::shared_ptr<BlockBase> &block );

		virtual void ModData( std::shared_ptr<MakeData> &makeData, const std::shared_ptr<StyleData> &Style );

	
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef MEAT
