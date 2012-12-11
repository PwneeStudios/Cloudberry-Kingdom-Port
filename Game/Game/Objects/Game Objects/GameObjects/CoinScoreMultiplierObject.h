#ifndef COINSCOREMULTIPLIEROBJECT
#define COINSCOREMULTIPLIEROBJECT

#include <global_header.h>

namespace CloudberryKingdom
{
	struct ObjectBase;
}

namespace CloudberryKingdom
{
	struct GameData;
}


namespace CloudberryKingdom
{
	struct CoinScoreMultiplierObject : public GameObject
	{
	
		struct OnCoinGrabProxy : public Lambda_1<std::shared_ptr<ObjectBase> >
		{
		
			std::shared_ptr<CoinScoreMultiplierObject> csmo;
		
			OnCoinGrabProxy( const std::shared_ptr<CoinScoreMultiplierObject> &csmo );

			void Apply( const std::shared_ptr<ObjectBase> &obj );
		};

	
		struct OnLevelRetryProxy : public Lambda
		{
		
			std::shared_ptr<CoinScoreMultiplierObject> csmo;
		
			OnLevelRetryProxy( const std::shared_ptr<CoinScoreMultiplierObject> &csmo );

			void Apply();
		};

	
		struct OnCalculateCoinScoreMultiplierProxy : public Lambda_1<std::shared_ptr<GameData> >
		{
		
			std::shared_ptr<CoinScoreMultiplierObject> csmo;
		
			OnCalculateCoinScoreMultiplierProxy( const std::shared_ptr<CoinScoreMultiplierObject> &csmo );

			void Apply( const std::shared_ptr<GameData> &obj );
		};

	
		virtual void OnAdd();

	
		virtual void ReleaseBody();

	
		float _CoinScoreMultiplier;
	
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

	
		void ResetMultiplier();

	
		CoinScoreMultiplierObject();

	
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef COINSCOREMULTIPLIEROBJECT
