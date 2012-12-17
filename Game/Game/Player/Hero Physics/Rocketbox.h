#ifndef ROCKETBOX
#define ROCKETBOX

#include <global_header.h>

namespace CloudberryKingdom
{
	struct BobPhsxRocketbox : public BobPhsxBox
	{

	
		static void InitializeStatics();

		// Singleton
	
		virtual void InitSingleton();
	
		static boost::shared_ptr<BobPhsxRocketbox> instance;
	
		const static boost::shared_ptr<BobPhsxRocketbox> &getInstance();

		virtual boost::shared_ptr<BobPhsx> Clone();
		void CopyTo( const boost::shared_ptr<BobPhsxRocketbox> &bob );

		// Instancable struct
		BobPhsxRocketbox();

		virtual void Init( const boost::shared_ptr<Bob> &bob );

		virtual void SideHit( ColType side, const boost::shared_ptr<BlockBase> &block );

		virtual void DefaultValues();

		virtual void DoXAccel();

	
		boost::shared_ptr<Quad> LeftWheel, RightWheel;
		float WheelAngle;
	
		virtual void AnimStep();

		virtual void GenerateInput( int CurPhsxStep );

		virtual void PhsxStep2();

	
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef ROCKETBOX
