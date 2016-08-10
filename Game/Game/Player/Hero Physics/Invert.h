#ifndef INVERT
#define INVERT

#include <small_header.h>

//#include "Game/Localization.h"
//#include "Game/Collision Detection/AABox.h"
//#include "Game/Collision Detection/Phsx.h"
//#include "Game/Objects/ObjectBase.h"
//#include "Game/Objects/In Game Objects/Blocks/Block.h"
//#include "Game/Level/Make/PieceSeedData.h"
//#include "Game/Level/Make/Parameters/LevelGenData.h"
//#include "Game/Level/Make/Parameters/StyleData/StyleData.h"
//#include "Game/Player/Hero Physics/Base.h"
//#include "Game/Objects/Icon.h"
//#include "Game/Objects/Bob/Bob.h"
//#include "Game/Objects/In Game Objects/Blocks/Ceiling__Auto.h"
//#include "Game/Objects/In Game Objects/Blocks/GhostBlock__Auto.h"
//#include "Game/Objects/In Game Objects/Blocks/MovingBlock__Auto.h"
//#include "Game/Objects/In Game Objects/Grab/MakeData.h"
//#include "Game/Level/Level.h"
//#include "Game/Objects/In Game Objects/Obstacles/BlockEmitter__Auto.h"
//#include "Game/Objects/In Game Objects/Obstacles/FlyingBlob.h"
#include "Game/Player/Hero Physics/Normal.h"
//#include "Game/Tools/Tools.h"


namespace CloudberryKingdom
{

	struct BobPhsxInvert : public BobPhsxNormal
	{

		virtual ~BobPhsxInvert()
		{
#ifdef BOOST_BIN
			OnDestructor( "BobPhsxInvert" );
#endif
		}


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
