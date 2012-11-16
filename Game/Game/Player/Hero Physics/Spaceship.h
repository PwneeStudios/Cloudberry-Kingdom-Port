#ifndef SPACESHIP
#define SPACESHIP

#include "Base.h"
#include "../Game/Collision Detection/Phsx.h"
#include "../Game/Objects/Bob/Bob.h"
#include "../Game/Objects/Game Objects/GameObjects/GUI_Text.h"
#include "../Game/Objects/In Game Objects/Blocks/Ceiling__Auto.h"
#include "../Game/Objects/In Game Objects/Obstacles/BlockEmitter__Auto.h"
#include "../Core/Text/EzText.h"
#include <unordered_map>
#include <vector>
#include <cmath>
#include <tchar.h>

namespace CloudberryKingdom
{
	class BlockBase;
}

namespace CloudberryKingdom
{
	class ObjectBase;
}

namespace CloudberryKingdom
{
	class SpriteAnim;
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
	class PieceSeedData;
}


//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;

using namespace Microsoft::Xna::Framework;

namespace CloudberryKingdom
{
	class BobPhsxSpaceship : public BobPhsx
	{
	public:
		static float KeepUnused( float UpgradeLevel );

		// Singleton
	protected:
		virtual void InitSingleton();
	private:
		static const std::shared_ptr<BobPhsxSpaceship> instance;
	public:
		const static std::shared_ptr<BobPhsxSpaceship> &getInstance() const;

		// Instancable class
	private:
		int AutoMoveLength, AutoMoveType, AutoStrafeLength;
		int AutoDirLength, AutoDir;

		int RndMoveType;

	public:
		BobPhsxSpaceship();

		virtual void DefaultValues();

		virtual void Init( const std::shared_ptr<Bob> &bob );

		virtual void PhsxStep();

		virtual void SideHit( ColType side, const std::shared_ptr<BlockBase> &block );

		virtual void PhsxStep2();

		virtual bool CheckFor_xFlip();

		virtual void Jump();

		virtual void LandOnSomething( bool MakeReadyToJump, const std::shared_ptr<ObjectBase> &ThingLandedOn );

		virtual void HitHeadOnSomething( const std::shared_ptr<ObjectBase> &ThingHit );

	private:
		int Dir;
	public:
		void GenerateInput_Vertical( int CurPhsxStep );

		virtual void GenerateInput( int CurPhsxStep );

	private:
		void GenerateInput_Right( int CurPhsxStep );

	public:
		virtual void AnimStep();

		virtual void ToSprites( std::unordered_map<int, SpriteAnim*> &SpriteAnims, Vector2 Padding );

		virtual void Die( Bob::BobDeathType DeathType );

		virtual void BlockInteractions();

		virtual void ModData( std::shared_ptr<Level.MakeData> &makeData, const std::shared_ptr<StyleData> &Style );

		virtual void ModLadderPiece( const std::shared_ptr<PieceSeedData> &piece );

	private:
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef SPACESHIP
