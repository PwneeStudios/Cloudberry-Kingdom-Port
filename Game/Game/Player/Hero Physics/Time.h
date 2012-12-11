#ifndef TIME
#define TIME

#include <global_header.h>

namespace CloudberryKingdom
{
	struct BobPhsxTime : public BobPhsxNormal
	{

	
		static void InitializeStatics();

	
		enum Behavior
		{
			Behavior_PAUSE,
			Behavior_REGULAR
		};
		// Singleton
	
		virtual void InitSingleton();
	
		static std::shared_ptr<BobPhsxTime> instance;
	
		const static std::shared_ptr<BobPhsxTime> &getInstance();

		virtual std::shared_ptr<BobPhsx> Clone();
		void CopyTo( const std::shared_ptr<BobPhsxTime> &bob );

		// Instancable struct
		BobPhsxTime();

		virtual void Set( const std::shared_ptr<BobPhsx> &phsx );
		void Set( const std::shared_ptr<BobPhsx> &phsx, Vector2 modsize );

		virtual void Init( const std::shared_ptr<Bob> &bob );

		virtual void PhsxStep();

		virtual void LandOnSomething( bool MakeReadyToJump, const std::shared_ptr<ObjectBase> &ThingLandedOn );

	
		Behavior CurBehavior;
		int BehaviorLength;
	
		virtual void GenerateInput( int CurPhsxStep );

		virtual void ModData( std::shared_ptr<MakeData> &makeData, const std::shared_ptr<StyleData> &Style );

	
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef TIME
