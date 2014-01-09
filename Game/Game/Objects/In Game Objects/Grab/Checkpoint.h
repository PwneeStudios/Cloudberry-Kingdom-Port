#ifndef CHECKPOINT
#define CHECKPOINT

#include <small_header.h>

//#include "Core/Graphics/Draw/Simple/BasePoint.h"
//#include "Core/Graphics/Draw/Simple/SimpleObject.h"
//#include "Core/Graphics/Draw/Simple/SimpleQuad.h"
//#include "Core/Particle Effects/Particle.h"
//#include "Core/Sound/EzSound.h"
//#include "Core/Texture/TextureOrAnim.h"
//#include "Game/Collision Detection/AABox.h"
//#include "Game/Collision Detection/Phsx.h"
#include "Game/Objects/ObjectBase.h"
#include "Game/Tilesets/TileSet.h"
//#include "Game/Level/LevelPiece.h"
//#include "Game/Objects/Bob/Bob.h"
//#include "Game/Objects/In Game Objects/Grab/MakeData.h"
//#include "Game/Level/Level.h"
//#include "Game/Tools/Prototypes.h"
//#include "Game/Tools/Recycler.h"
//#include "Game/Tools/Tools.h"
//#include "Game/Tilesets/TileSetInfo.h"


namespace CloudberryKingdom
{

	struct Checkpoint : public ObjectBase
	{

		virtual ~Checkpoint()
		{
#ifdef BOOST_BIN
			OnDestructor( "Checkpoint" );
#endif
		}

	
		static void InitializeStatics();

	
		struct CheckpointTileInfo : public TileInfoBase
		{
		
			boost::shared_ptr<TextureOrAnim> Sprite;
			Vector2 Size;
			Vector2 TextureSize;

			boost::shared_ptr<EzSound> MySound;

			boost::shared_ptr<Particle> DieTemplate;
			CheckpointTileInfo();

		
			void InitializeInstanceFields();
		};

	
		virtual void Release();

		bool Taken, TakenAnimFinished;
	
		bool GhostFaded;

		float Taken_Scale, Taken_Alpha;

		static boost::shared_ptr<EzSound> MySound;

	
		bool SkipPhsx;

		bool Touched;

		boost::shared_ptr<AABox> Box;
		SimpleQuad MyQuad;
		BasePoint Base;

		boost::shared_ptr<SimpleObject> MyObject;

		boost::shared_ptr<LevelPiece> MyPiece;
		int MyPieceIndex;

		virtual void MakeNew();

		Checkpoint();

	
		void SetAnimation();

	
		void Revert();

	
		void ResetTakenAnim();

	
		void Die();

		void Init( const boost::shared_ptr<Level> &level );

		void AnimStep();

		virtual void PhsxStep();

		virtual void PhsxStep2();

		void Update();

		virtual void Reset( bool BoxesOnly );

		virtual void Move( Vector2 shift );

		virtual void Interact( const boost::shared_ptr<Bob> &bob );

		void SetAlpha();

		virtual void Draw();

		virtual void Clone( const boost::shared_ptr<ObjectBase> &A );
	};

}


#endif	//#ifndef CHECKPOINT
