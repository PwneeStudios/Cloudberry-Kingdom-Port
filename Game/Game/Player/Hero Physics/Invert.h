#ifndef INVERT
#define INVERT

#include <global_header.h>

namespace CloudberryKingdom
{
	struct BobPhsxInvert : public BobPhsxNormal
	{

	
		static void InitializeStatics();

	
		enum Behavior
		{
			Behavior_PAUSE,
			Behavior_REGULAR
		};
		// Singleton
	
		virtual void InitSingleton();
	
		static std::shared_ptr<BobPhsxInvert> instance;
	
		const static std::shared_ptr<BobPhsxInvert> &getInstance();

		virtual std::shared_ptr<BobPhsx> Clone();
		void CopyTo( const std::shared_ptr<BobPhsxInvert> &bob );

		// Instancable struct
		BobPhsxInvert();

		virtual void Set( const std::shared_ptr<BobPhsx> &phsx );
		void Set( const std::shared_ptr<BobPhsx> &phsx, Vector2 modsize );

		virtual void Init( const std::shared_ptr<Bob> &bob );

		virtual void PhsxStep();

		virtual void UpdateReadyToJump();

	
		virtual void DoJump();

	
		void Invert();

		virtual void Forced( Vector2 Dir );

		virtual void LandOnSomething( bool MakeReadyToJump, const std::shared_ptr<ObjectBase> &ThingLandedOn );

		virtual void HitHeadOnSomething( const std::shared_ptr<ObjectBase> &ThingHit );

		virtual bool ShouldStartJumpAnim();

	
		Behavior CurBehavior;
		int BehaviorLength;
	
		virtual void GenerateInput( int CurPhsxStep );

	
		int Count;
	
		virtual void SetTarget( const std::shared_ptr<RichLevelGenData> &GenData );

		virtual void PreventEarlyLandings( const std::shared_ptr<RichLevelGenData> &GenData );

	
		virtual void ModData( std::shared_ptr<MakeData> &makeData, const std::shared_ptr<StyleData> &Style );

		virtual void ModLadderPiece( const std::shared_ptr<PieceSeedData> &piece );

		virtual bool IsBottomCollision( ColType Col, const std::shared_ptr<AABox> &box, const std::shared_ptr<BlockBase> &block );

		virtual void DollInitialize();

	
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef INVERT
