#ifndef WHEEL
#define WHEEL

#include <global_header.h>

namespace CloudberryKingdom
{
	struct BobPhsxWheel : public BobPhsxNormal
	{

	
		static void InitializeStatics();

		// Singleton
	
		virtual void InitSingleton();
	
		static std::shared_ptr<BobPhsxWheel> instance;
	
		const static std::shared_ptr<BobPhsxWheel> &getInstance();

		virtual std::shared_ptr<BobPhsx> Clone();
		void CopyTo( const std::shared_ptr<BobPhsxWheel> &bob );

		// Instancable struct
	
		std::shared_ptr<EzSound> LandSound;

		float AngleSpeed;

	
		BobPhsxWheel();

		virtual void DefaultValues();

	
		static int AnimIndex;
	
		virtual void Init( const std::shared_ptr<Bob> &bob );

		virtual void DuckingPhsx();

		float MaxAngleSpeed, AngleAcc;
		virtual void DoXAccel();

	
		float AngleToDist( float Angle );


	
		virtual float RetardxVec();

		virtual void LandOnSomething( bool MakeReadyToJump, const std::shared_ptr<ObjectBase> &ThingLandedOn );

		virtual void HitHeadOnSomething( const std::shared_ptr<ObjectBase> &ThingHit );

		virtual void GenerateInput( int CurPhsxStep );

		virtual void AnimStep();

		virtual bool CheckFor_xFlip();

		virtual void SideHit( ColType side, const std::shared_ptr<BlockBase> &block );

		virtual void Die( BobDeathType DeathType );

		virtual void ModData( std::shared_ptr<MakeData> &makeData, const std::shared_ptr<StyleData> &Style );

		virtual void ToSprites( std::map<int, std::shared_ptr<SpriteAnim> > &SpriteAnims, Vector2 Padding );

	
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef WHEEL
