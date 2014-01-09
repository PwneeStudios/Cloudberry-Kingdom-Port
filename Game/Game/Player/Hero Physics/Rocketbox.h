#ifndef ROCKETBOX
#define ROCKETBOX

#include <small_header.h>

//#include "Core/Graphics/Draw/Quads/Quad.h"
//#include "Game/Localization.h"
//#include "Core/Particle Effects/Specific Effects/CloudberryKingdom.ParticleEffects.h"
//#include "Core/Tools/ColorHelper.h"
//#include "Core/Tools/CoreMath.h"
//#include "Game/Collision Detection/Phsx.h"
//#include "Game/Objects/In Game Objects/Blocks/Block.h"
//#include "Game/Player/Hero Physics/Base.h"
//#include "Game/Objects/Icon.h"
//#include "Game/Objects/Bob/Bob.h"
#include "Game/Player/Hero Physics/Box.h"
//#include "Game/Tools/Tools.h"


namespace CloudberryKingdom
{
	
	struct BobPhsxRocketbox : public BobPhsxBox
	{

		virtual ~BobPhsxRocketbox()
		{
#ifdef BOOST_BIN
			OnDestructor( "BobPhsxRocketbox" );
#endif
		}

	
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
