#ifndef TIME
#define TIME

#include <global_header.h>

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
