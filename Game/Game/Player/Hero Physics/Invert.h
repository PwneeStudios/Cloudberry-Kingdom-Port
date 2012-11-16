#ifndef INVERT
#define INVERT

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
	class ObjectBase;
}

namespace CloudberryKingdom
{
	class RichLevelGenData;
}

namespace CloudberryKingdom
{
	class StyleData;
}

namespace CloudberryKingdom
{
	class Level;
}

namespace CloudberryKingdom
{
	class PieceSeedData;
}

namespace CloudberryKingdom
{
	class BlockBase;
}

namespace CloudberryKingdom
{
	class AABox;
}


using namespace Microsoft::Xna::Framework;

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;

namespace CloudberryKingdom
{
	class BobPhsxInvert : public BobPhsxNormal
	{
	private:
		enum Behavior
		{
			Behavior_PAUSE,
			Behavior_REGULAR
		};
		// Singleton
	protected:
		virtual void InitSingleton();
	private:
		static const std::shared_ptr<BobPhsxInvert> instance;
	public:
		const static std::shared_ptr<BobPhsxInvert> &getInstance() const;

		// Instancable class
		BobPhsxInvert();

		virtual void Set( const std::shared_ptr<BobPhsx> &phsx );
		void Set( const std::shared_ptr<BobPhsx> &phsx, Vector2 modsize );

		virtual void Init( const std::shared_ptr<Bob> &bob );

		virtual void PhsxStep();

		virtual void UpdateReadyToJump();

	protected:
		virtual void DoJump();

	public:
		void Invert();

		virtual void Forced( Vector2 Dir );

		virtual void LandOnSomething( bool MakeReadyToJump, const std::shared_ptr<ObjectBase> &ThingLandedOn );

		virtual void HitHeadOnSomething( const std::shared_ptr<ObjectBase> &ThingHit );

		virtual bool ShouldStartJumpAnim();

	private:
		Behavior CurBehavior;
		int BehaviorLength;
	public:
		virtual void GenerateInput( int CurPhsxStep );

	private:
		int Count;
	protected:
		virtual void SetTarget( const std::shared_ptr<RichLevelGenData> &GenData );

		virtual void PreventEarlyLandings( const std::shared_ptr<RichLevelGenData> &GenData );

	public:
		virtual void ModData( std::shared_ptr<Level.MakeData> &makeData, const std::shared_ptr<StyleData> &Style );

		virtual void ModLadderPiece( const std::shared_ptr<PieceSeedData> &piece );

		virtual bool IsBottomCollision( ColType Col, const std::shared_ptr<AABox> &box, const std::shared_ptr<BlockBase> &block );

		virtual void DollInitialize();

	private:
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef INVERT
