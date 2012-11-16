#ifndef COIN
#define COIN

#define _USE_MATH_DEFINES
#include <global_header.h>

namespace CloudberryKingdom
{
	class SpriteInfo;
}

namespace CloudberryKingdom
{
	class EzSound;
}

namespace CloudberryKingdom
{
	class Particle;
}

namespace CloudberryKingdom
{
	class AABox;
}

namespace CloudberryKingdom
{
	class QuadClass;
}

namespace CloudberryKingdom
{
	class GameData;
}

namespace CloudberryKingdom
{
	class Bob;
}

namespace CloudberryKingdom
{
	class ObjectBase;
}


//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::IO;


namespace CloudberryKingdom
{
	class Coin : public ObjectBase
	{
	public:
		enum CoinType
		{
			CoinType_BLUE,
			CoinType_RED
		};
	public:
		class CoinTileInfo : public TileInfoBase
		{
			//public SpriteInfo Sprite = new SpriteInfo("CoinBlue2", new Vector2(105, -1));
		public:
			std::shared_ptr<SpriteInfo> Sprite;

			Vector2 BoxSize;
			Color Color;
			bool ShowEffect, ShowText, ShowCoin;

			std::shared_ptr<EzSound> MySound;

			std::shared_ptr<Particle> DieTemplate;
			CoinTileInfo();

		private:
			void InitializeInstanceFields();
		};

	public:
		bool Touched;

		std::shared_ptr<AABox> Box;
		std::shared_ptr<QuadClass> MyQuad;

		int MyValue, MyScoreValue;

		virtual void MakeNew();

		virtual void Release();

		Coin( bool BoxesOnly );

		static Vector2 PosOfLastCoinGrabbed;
		void Die();

	private:
		const std::shared_ptr<GameData> &getMyGame() const;

	public:
		int CalcScoreValue();

		CoinType MyType;

		void SetType( CoinType type );

	private:
		bool AlwaysActive;
	public:
		int Offset, Period;
	private:
		Vector2 Radii;
	public:
		Vector2 GetPos();

		virtual void PhsxStep();

		virtual void PhsxStep2();

		virtual void Reset( bool BoxesOnly );

		virtual void Move( Vector2 shift );

		virtual void Interact( const std::shared_ptr<Bob> &bob );

	private:
		static Vector2 DrawGrace;
	public:
		virtual void Draw();

		virtual void Clone( const std::shared_ptr<ObjectBase> &A );

	private:
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef COIN
