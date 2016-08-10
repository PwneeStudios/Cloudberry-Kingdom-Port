#ifndef TIME
#define TIME

#include <small_header.h>

//#include "Game/Localization.h"
//#include "Game/Objects/ObjectBase.h"
//#include "Game/Level/Make/Parameters/StyleData/StyleData.h"
//#include "Game/Player/Hero Physics/Base.h"
//#include "Game/Objects/Icon.h"
//#include "Game/Objects/Bob/Bob.h"
//#include "Game/Objects/In Game Objects/Grab/MakeData.h"
//#include "Game/Level/Level.h"
#include "Game/Player/Hero Physics/Normal.h"
//#include "Game/Tools/Tools.h"


namespace CloudberryKingdom
{

	struct BobPhsxTime : public BobPhsxNormal
	{

		virtual ~BobPhsxTime()
		{
#ifdef BOOST_BIN
			OnDestructor( "BobPhsxTime" );
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
	
		static boost::shared_ptr<BobPhsxTime> instance;
	
		const static boost::shared_ptr<BobPhsxTime> &getInstance();

		virtual boost::shared_ptr<BobPhsx> Clone();
		void CopyTo( const boost::shared_ptr<BobPhsxTime> &bob );

		// Instancable struct
		BobPhsxTime();

		virtual void Set( const boost::shared_ptr<BobPhsx> &phsx );
		void Set( const boost::shared_ptr<BobPhsx> &phsx, Vector2 modsize );

		virtual void Init( const boost::shared_ptr<Bob> &bob );

		virtual void PhsxStep();

		virtual void LandOnSomething( bool MakeReadyToJump, const boost::shared_ptr<ObjectBase> &ThingLandedOn );

	
		Behavior CurBehavior;
		int BehaviorLength;
	
		virtual void GenerateInput( int CurPhsxStep );

		virtual void ModData( boost::shared_ptr<MakeData> &makeData, const boost::shared_ptr<StyleData> &Style );

	
		void InitializeInstanceFields();
	};

}


#endif	//#ifndef TIME
