#ifndef MEAT
#define MEAT

#include <global_header.h>

namespace CloudberryKingdom
{
	class BobPhsx;
}

namespace CloudberryKingdom
{
	class Bob;
}

namespace CloudberryKingdom
{
	class BlockBase;
}

namespace CloudberryKingdom
{
	class ObjectBase;
}

namespace CloudberryKingdom
{
	class RichLevelGenData;
}

namespace CloudberryKingdom
{
	class AABox;
}

namespace CloudberryKingdom
{
	class StyleData;
}

namespace CloudberryKingdom
{
	class Level;
}




//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;

namespace CloudberryKingdom
{
	class BobPhsxMeat : public BobPhsxNormal
	{
	public:
		virtual void Release();

		virtual void Set( const std::shared_ptr<BobPhsx> &phsx );
		void Set( const std::shared_ptr<BobPhsx> &phsx, Vector2 modsize );

		// Singleton
	protected:
		virtual void InitSingleton();
	private:
		static const std::shared_ptr<BobPhsxMeat> instance;
	public:
		const static std::shared_ptr<BobPhsxMeat> &getInstance() const;

		// Instancable class
		BobPhsxMeat();

		virtual void Init( const std::shared_ptr<Bob> &bob );

	private:
		bool LastJumpWasSticky;
	public:
		int StepsSinceSide, StepsOnSide;
		int StickyDuration;
	private:
		ColType StickySide;
		std::shared_ptr<BlockBase> LastStickyBlock;
		bool IsStuck;
	public:
		virtual void SideHit( ColType side, const std::shared_ptr<BlockBase> &block );

		virtual void LandOnSomething( bool MakeReadyToJump, const std::shared_ptr<ObjectBase> &ThingLandedOn );

	private:
		bool CanWallJump;
	public:
		int WallJumpCount;
	private:
		int StickyGracePeriod;
	public:
		float Max_yVel_ForWallJump;

	private:
		int SideJumpLength;
		float SideJumpStr;

	public:
		virtual void Jump();

	private:
		float SideToDir( ColType side );

		const float &getStickyDir() const;

	public:
		virtual void PhsxStep();

		virtual void DoXAccel();

		virtual float GetXAccel();

	protected:
		virtual void DoJump();

	public:
		virtual bool ShouldStartJumpAnim();

	protected:
		virtual void SetTarget( const std::shared_ptr<RichLevelGenData> &GenData );

	private:
		Vector2 PrefferedDir;
		void NewTarget();

	public:
		bool WantToLandOnTop;
	private:
		Vector2 Target;
		Vector2 AlwaysForward;
		int StraightUpDuration;
		float yVelCutoff;
	public:
		virtual void GenerateInput( int CurPhsxStep );

		virtual bool IsTopCollision( ColType Col, const std::shared_ptr<AABox> &box, const std::shared_ptr<BlockBase> &block );

		virtual bool IsBottomCollision( ColType Col, const std::shared_ptr<AABox> &box, const std::shared_ptr<BlockBase> &block );

		virtual void ModData( std::shared_ptr<Level.MakeData> &makeData, const std::shared_ptr<StyleData> &Style );

	private:
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef MEAT
