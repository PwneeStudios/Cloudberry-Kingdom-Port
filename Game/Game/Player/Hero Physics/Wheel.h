#ifndef WHEEL
#define WHEEL

#include <small_header.h>

//#include "Core/Animation/SpriteAnim.h"
//#include "Core/Graphics/Draw/Object/ObjectClass.h"
//#include "Game/Localization.h"
//#include "Core/Sound/EzSound.h"
//#include "Game/Collision Detection/Phsx.h"
//#include "Game/Objects/ObjectBase.h"
//#include "Game/Objects/In Game Objects/Blocks/Block.h"
//#include "Game/Level/Make/Parameters/LevelGenData.h"
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

	struct BobPhsxWheel : public BobPhsxNormal
	{

		virtual ~BobPhsxWheel()
		{
#ifdef BOOST_BIN
			OnDestructor( "BobPhsxWheel" );
#endif
		}

	
		static void InitializeStatics();

		// Singleton
	
		virtual void InitSingleton();
	
		static boost::shared_ptr<BobPhsxWheel> instance;
	
		const static boost::shared_ptr<BobPhsxWheel> &getInstance();

		virtual boost::shared_ptr<BobPhsx> Clone();
		void CopyTo( const boost::shared_ptr<BobPhsxWheel> &bob );

		// Instancable struct
	
		boost::shared_ptr<EzSound> LandSound;

		float AngleSpeed;

	
		BobPhsxWheel();

		virtual void DefaultValues();

	
		static int AnimIndex;
	
		virtual void Init( const boost::shared_ptr<Bob> &bob );

		virtual void DuckingPhsx();

		float MaxAngleSpeed, AngleAcc;
		virtual void DoXAccel();

	
		float AngleToDist( float Angle );


	
		virtual float RetardxVec();

		virtual void LandOnSomething( bool MakeReadyToJump, const boost::shared_ptr<ObjectBase> &ThingLandedOn );

		virtual void HitHeadOnSomething( const boost::shared_ptr<ObjectBase> &ThingHit );

		virtual void GenerateInput( int CurPhsxStep );

		virtual void AnimStep();

		virtual bool CheckFor_xFlip();

		virtual void SideHit( ColType side, const boost::shared_ptr<BlockBase> &block );

		virtual void Die( BobDeathType DeathType );

		virtual void ModData( boost::shared_ptr<MakeData> &makeData, const boost::shared_ptr<StyleData> &Style );

		virtual void ToSprites( std::map<int, boost::shared_ptr<SpriteAnim> > &SpriteAnims, Vector2 Padding );

	
		void InitializeInstanceFields();
	};

}


#endif	//#ifndef WHEEL
