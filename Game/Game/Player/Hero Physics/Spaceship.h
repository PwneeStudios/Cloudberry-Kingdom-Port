#ifndef SPACESHIP
#define SPACESHIP

#include <small_header.h>

//#include "Core/Animation/SpriteAnim.h"
//#include "Core/Graphics/Draw/Object/ObjectClass.h"
//#include "Game/Localization.h"
//#include "Core/Particle Effects/Specific Effects/CloudberryKingdom.ParticleEffects.h"
//#include "Game/Collision Detection/Phsx.h"
//#include "Game/Objects/ObjectBase.h"
//#include "Game/Objects/In Game Objects/Blocks/Block.h"
//#include "Game/Level/Make/PieceSeedData.h"
//#include "Game/Level/Make/Parameters/LevelGenData.h"
//#include "Game/Level/Make/Parameters/StyleData/StyleData.h"
#include "Game/Player/Hero Physics/Base.h"
//#include "Game/Objects/Icon.h"
//#include "Game/Objects/Bob/Bob.h"
//#include "Game/Objects/In Game Objects/Blocks/GhostBlock__Auto.h"
//#include "Game/Objects/In Game Objects/Grab/MakeData.h"
//#include "Game/Level/Level.h"
//#include "Game/Objects/In Game Objects/Obstacles/BlockEmitter__Auto.h"
//#include "Game/Objects/In Game Objects/Obstacles/CloudberryKingdom.Fireball.h"
//#include "Game/Tools/Tools.h"


namespace CloudberryKingdom
{

	struct BobPhsxSpaceship : public BobPhsx
	{

		virtual ~BobPhsxSpaceship()
		{
#ifdef BOOST_BIN
			OnDestructor( "BobPhsxSpaceship" );
#endif
		}


	
		static void InitializeStatics();

	
		static float KeepUnused( float UpgradeLevel );

		// Singleton
	
		virtual void InitSingleton();
	
		static boost::shared_ptr<BobPhsxSpaceship> instance;
	
		const static boost::shared_ptr<BobPhsxSpaceship> &getInstance();

		virtual boost::shared_ptr<BobPhsx> Clone();
		void CopyTo( const boost::shared_ptr<BobPhsxSpaceship> &bob );

		// Instancable struct
	
		int AutoMoveLength, AutoMoveType, AutoStrafeLength;
		int AutoDirLength, AutoDir;

		int RndMoveType;

	
		BobPhsxSpaceship();

		virtual void DefaultValues();

		virtual void Init( const boost::shared_ptr<Bob> &bob );

		virtual void PhsxStep();

		virtual void SideHit( ColType side, const boost::shared_ptr<BlockBase> &block );

		virtual void PhsxStep2();

		virtual bool CheckFor_xFlip();

		virtual void Jump();

		virtual void LandOnSomething( bool MakeReadyToJump, const boost::shared_ptr<ObjectBase> &ThingLandedOn );

		virtual void HitHeadOnSomething( const boost::shared_ptr<ObjectBase> &ThingHit );

	
		int Dir;
	
		void GenerateInput_Vertical( int CurPhsxStep );

		virtual void GenerateInput( int CurPhsxStep );

	
		void GenerateInput_Right( int CurPhsxStep );

	
		virtual void AnimStep();

		virtual void ToSprites( std::map<int, boost::shared_ptr<SpriteAnim> > &SpriteAnims, Vector2 Padding );

		virtual void Die( BobDeathType DeathType );

		virtual void BlockInteractions();

		virtual void ModData( boost::shared_ptr<MakeData> &makeData, const boost::shared_ptr<StyleData> &Style );

		virtual void ModLadderPiece( const boost::shared_ptr<PieceSeedData> &piece );

	
		void InitializeInstanceFields();
	};

}


#endif	//#ifndef SPACESHIP
