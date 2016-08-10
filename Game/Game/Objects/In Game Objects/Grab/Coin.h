#ifndef COIN
#define COIN

#define _USE_MATH_DEFINES
#include <small_header.h>

//#include "Core/Graphics/Draw/Quads/QuadClass.h"
//#include "Core/Particle Effects/Specific Effects/CloudberryKingdom.ParticleEffects.h"
//#include "Core/Sound/EzSound.h"
//#include "Game/Collision Detection/AABox.h"
//#include "Game/Collision Detection/Phsx.h"
#include "Game/Objects/ObjectBase.h"
#include "Game/Tilesets/TileSet.h"
//#include "Game/Games/GameType.h"
//#include "Game/Objects/Bob/Bob.h"
//#include "Game/Objects/Special/TextFloat.h"
//#include "Game/Tilesets/SpriteInfo.h"
//#include "Game/Tools/Recycler.h"
//#include "Game/Tools/Tools.h"
//#include "Game/Tilesets/TileSetInfo.h"


namespace CloudberryKingdom
{

	struct Coin : public ObjectBase
	{
	
		virtual ~Coin()
		{
#ifdef BOOST_BIN
			OnDestructor( "Coin" );
#endif
		}


		enum CoinType
		{
			CoinType_BLUE,
			CoinType_RED
		};
	
		struct CoinTileInfo : public TileInfoBase
		{
			//public SpriteInfo Sprite = new SpriteInfo("CoinBlue2", new Vector2(105, -1));
		
			boost::shared_ptr<SpriteInfo> Sprite;

			Vector2 BoxSize;
			Color Color;
			bool ShowEffect, ShowText, ShowCoin;

			boost::shared_ptr<EzSound> MySound;

			CoinTileInfo();

		
			void InitializeInstanceFields();
		};

	
		bool Touched;

		boost::shared_ptr<AABox> Box;
		boost::shared_ptr<QuadClass> MyQuad;

		int MyValue, MyScoreValue;

		virtual void MakeNew();

		virtual void Release();

		Coin( bool BoxesOnly );

		static Vector2 PosOfLastCoinGrabbed;
		void Die();

	
		const boost::shared_ptr<GameData> &getMyGame() const;

	
		int CalcScoreValue();

		CoinType MyType;

		void SetType( CoinType type );

	
		bool AlwaysActive;
	
		int Offset, Period;
	
		Vector2 Radii;
	
		Vector2 GetPos();

		virtual void PhsxStep();

		virtual void PhsxStep2();

		virtual void Reset( bool BoxesOnly );

		virtual void Move( Vector2 shift );

		virtual void Interact( const boost::shared_ptr<Bob> &bob );

	
		static Vector2 DrawGrace;
	
		virtual void Draw();

		virtual void Clone( const boost::shared_ptr<ObjectBase> &A );

	
		void InitializeInstanceFields();
	};

}


#endif	//#ifndef COIN
