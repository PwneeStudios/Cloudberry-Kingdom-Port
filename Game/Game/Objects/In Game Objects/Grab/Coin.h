#ifndef COIN
#define COIN

#define _USE_MATH_DEFINES
#include <global_header.h>

namespace CloudberryKingdom
{

	struct Coin : public ObjectBase
	{
	
		virtual ~Coin() { }

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
