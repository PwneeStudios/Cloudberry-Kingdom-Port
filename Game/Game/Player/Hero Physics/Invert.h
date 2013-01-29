#ifndef INVERT
#define INVERT

#include <global_header.h>

namespace CloudberryKingdom
{

	struct BobPhsxInvert : public BobPhsxNormal
	{

		virtual ~BobPhsxInvert() { }

		static void InitializeStatics();
	
		enum Behavior
		{
			Behavior_PAUSE,
			Behavior_REGULAR
		};
		// Singleton
	
		virtual void InitSingleton();
	
		static boost::shared_ptr<BobPhsxInvert> instance;
	
		const static boost::shared_ptr<BobPhsxInvert> &getInstance();

		virtual boost::shared_ptr<BobPhsx> Clone();
		void CopyTo( const boost::shared_ptr<BobPhsxInvert> &bob );

		// Instancable struct
		BobPhsxInvert();

		virtual void Set( const boost::shared_ptr<BobPhsx> &phsx );
		void Set( const boost::shared_ptr<BobPhsx> &phsx, Vector2 modsize );

		virtual void Init( const boost::shared_ptr<Bob> &bob );

		virtual void PhsxStep();

		virtual void UpdateReadyToJump();

	
		virtual void DoJump();

	
		void Invert();

		virtual void Forced( Vector2 Dir );

		virtual void LandOnSomething( bool MakeReadyToJump, const boost::shared_ptr<ObjectBase> &ThingLandedOn );

		virtual void HitHeadOnSomething( const boost::shared_ptr<ObjectBase> &ThingHit );

		virtual bool ShouldStartJumpAnim();

	
		Behavior CurBehavior;
		int BehaviorLength;
	
		virtual void GenerateInput( int CurPhsxStep );

	
		int Count;
	
		virtual void SetTarget( const boost::shared_ptr<RichLevelGenData> &GenData );

		virtual void PreventEarlyLandings( const boost::shared_ptr<RichLevelGenData> &GenData );

	
		virtual void ModData( boost::shared_ptr<MakeData> &makeData, const boost::shared_ptr<StyleData> &Style );

		virtual void ModLadderPiece( const boost::shared_ptr<PieceSeedData> &piece );

		virtual bool IsBottomCollision( ColType Col, const boost::shared_ptr<AABox> &box, const boost::shared_ptr<BlockBase> &block );

		virtual void DollInitialize();

	
		void InitializeInstanceFields();
	};

}


#endif	//#ifndef INVERT
