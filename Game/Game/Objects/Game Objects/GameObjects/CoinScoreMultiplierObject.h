#ifndef COINSCOREMULTIPLIEROBJECT
#define COINSCOREMULTIPLIEROBJECT

#include "../Game/Objects/Game Objects/GameObject.h"
#include "../Core/Lambdas/Lambda_1.h"
#include "../Game/Games/Campaign/CampaignSequence.h"
#include "PerfectScoreObject.h"
#include "GUI_NextLife.h"
#include "GUI_Timer.h"
#include "../Core/Lambdas/Lambda.h"

namespace CloudberryKingdom
{
	class ObjectBase;
}

namespace CloudberryKingdom
{
	class GameData;
}


namespace CloudberryKingdom
{
	class CoinScoreMultiplierObject : public GameObject
	{
	private:
		class OnCoinGrabProxy : public Lambda_1<ObjectBase*>
		{
		private:
			std::shared_ptr<CoinScoreMultiplierObject> csmo;
		public:
			OnCoinGrabProxy( const std::shared_ptr<CoinScoreMultiplierObject> &csmo );

			void Apply( const std::shared_ptr<ObjectBase> &obj );
		};

	private:
		class OnLevelRetryProxy : public Lambda
		{
		private:
			std::shared_ptr<CoinScoreMultiplierObject> csmo;
		public:
			OnLevelRetryProxy( const std::shared_ptr<CoinScoreMultiplierObject> &csmo );

			void Apply();
		};

	private:
		class OnCalculateCoinScoreMultiplierProxy : public Lambda_1<GameData*>
		{
		private:
			std::shared_ptr<CoinScoreMultiplierObject> csmo;
		public:
			OnCalculateCoinScoreMultiplierProxy( const std::shared_ptr<CoinScoreMultiplierObject> &csmo );

			void Apply( const std::shared_ptr<GameData> &obj );
		};

	public:
		virtual void OnAdd();

	protected:
		virtual void ReleaseBody();

	private:
		float _CoinScoreMultiplier;
	public:
		const float &getCoinScoreMultiplier() const;
		void setCoinScoreMultiplier( const float &value );

		/*
		/// <summary>
		/// Make the GameData's multiplier match this multiplier
		/// </summary>
		void UpdateGameMultiplier()
		{
		    MyGame.CoinScoreMultiplier = _CoinScoreMultiplier;
		}*/

		/// <summary>
		/// Every time a coin is grabbed increase the multiplier
		/// </summary>
		void OnCoinGrab( const std::shared_ptr<ObjectBase> &obj );

		/// <summary>
		/// When the players die reset the multiplier
		/// </summary>
		void OnLevelRetry();

	private:
		void ResetMultiplier();

	public:
		CoinScoreMultiplierObject();

	private:
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef COINSCOREMULTIPLIEROBJECT
