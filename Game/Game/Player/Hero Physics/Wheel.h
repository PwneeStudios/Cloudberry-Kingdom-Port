#ifndef WHEEL
#define WHEEL

#include "Normal.h"
#include "../Game/Collision Detection/Phsx.h"
#include "../Game/Objects/Bob/Bob.h"
#include "../Game/Objects/Game Objects/GameObjects/GUI_Text.h"
#include "../Game/Objects/In Game Objects/Blocks/Ceiling__Auto.h"
#include "../Game/Objects/In Game Objects/Obstacles/BlockEmitter__Auto.h"
#include "../Core/Text/EzText.h"
#include <unordered_map>
#include <cmath>
#include <tchar.h>

namespace CloudberryKingdom
{
	class EzSound;
}

namespace CloudberryKingdom
{
	class ObjectBase;
}

namespace CloudberryKingdom
{
	class BlockBase;
}

namespace CloudberryKingdom
{
	class StyleData;
}

namespace CloudberryKingdom
{
	class Level;
}

namespace CloudberryKingdom
{
	class SpriteAnim;
}


//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;

using namespace Microsoft::Xna::Framework;

namespace CloudberryKingdom
{
	class BobPhsxWheel : public BobPhsxNormal
	{
		// Singleton
	protected:
		virtual void InitSingleton();
	private:
		static const std::shared_ptr<BobPhsxWheel> instance;
	public:
		const static std::shared_ptr<BobPhsxWheel> &getInstance() const;

		// Instancable class
	private:
		std::shared_ptr<EzSound> LandSound;

		float AngleSpeed;

	public:
		BobPhsxWheel();

		virtual void DefaultValues();

	private:
		static int AnimIndex;
	public:
		virtual void Init( const std::shared_ptr<Bob> &bob );

		virtual void DuckingPhsx();

		float MaxAngleSpeed, AngleAcc;
		virtual void DoXAccel();

	private:
		float AngleToDist( float Angle );


	public:
		virtual float RetardxVec();

		virtual void LandOnSomething( bool MakeReadyToJump, const std::shared_ptr<ObjectBase> &ThingLandedOn );

		virtual void HitHeadOnSomething( const std::shared_ptr<ObjectBase> &ThingHit );

		virtual void GenerateInput( int CurPhsxStep );

		virtual void AnimStep();

		virtual bool CheckFor_xFlip();

		virtual void SideHit( ColType side, const std::shared_ptr<BlockBase> &block );

		virtual void Die( Bob::BobDeathType DeathType );

		virtual void ModData( std::shared_ptr<Level.MakeData> &makeData, const std::shared_ptr<StyleData> &Style );

		virtual void ToSprites( std::unordered_map<int, SpriteAnim*> &SpriteAnims, Vector2 Padding );

	private:
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef WHEEL
