#ifndef MEAT
#define MEAT

#include <global_header.h>

namespace CloudberryKingdom
{

	struct BobPhsxMeat : public BobPhsxNormal
	{

		virtual ~BobPhsxMeat()
		{
#ifdef BOOST_BIN
			OnDestructor( "BobPhsxMeat" );
#endif
		}

	
		static void InitializeStatics();

	
		virtual void Release();

		virtual void Set( const boost::shared_ptr<BobPhsx> &phsx );
		void Set( const boost::shared_ptr<BobPhsx> &phsx, Vector2 modsize );

		// Singleton
	
		virtual void InitSingleton();
	
		static boost::shared_ptr<BobPhsxMeat> instance;
	
		const static boost::shared_ptr<BobPhsxMeat> &getInstance();

		virtual boost::shared_ptr<BobPhsx> Clone();
		void CopyTo( const boost::shared_ptr<BobPhsxMeat> &bob );

		// Instancable struct
		BobPhsxMeat();

		virtual void Init( const boost::shared_ptr<Bob> &bob );

	
		bool LastJumpWasSticky;
	
		int StepsSinceSide, StepsOnSide;
		int StickyDuration;
	
		ColType StickySide;
		boost::shared_ptr<BlockBase> LastStickyBlock;
		bool IsStuck;
	
		virtual void SideHit( ColType side, const boost::shared_ptr<BlockBase> &block );

		virtual void LandOnSomething( bool MakeReadyToJump, const boost::shared_ptr<ObjectBase> &ThingLandedOn );

	
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

	
		virtual void SetTarget( const boost::shared_ptr<RichLevelGenData> &GenData );

	
		Vector2 PrefferedDir;
		void NewTarget();

	
		bool WantToLandOnTop;
	
		Vector2 Target;
		Vector2 AlwaysForward;
		int StraightUpDuration;
		float yVelCutoff;
	
		virtual void GenerateInput( int CurPhsxStep );

		virtual bool IsTopCollision( ColType Col, const boost::shared_ptr<AABox> &box, const boost::shared_ptr<BlockBase> &block );

		virtual bool IsBottomCollision( ColType Col, const boost::shared_ptr<AABox> &box, const boost::shared_ptr<BlockBase> &block );

		virtual void ModData( boost::shared_ptr<MakeData> &makeData, const boost::shared_ptr<StyleData> &Style );

	
		void InitializeInstanceFields();
	};

}


#endif	//#ifndef MEAT
