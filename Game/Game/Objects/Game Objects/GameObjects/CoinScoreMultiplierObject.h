#ifndef COINSCOREMULTIPLIEROBJECT
#define COINSCOREMULTIPLIEROBJECT

#include <global_header.h>

namespace CloudberryKingdom
{

	struct CoinScoreMultiplierObject : public GameObject
	{

		virtual ~CoinScoreMultiplierObject()
		{
#ifdef BOOST_BIN
			OnDestructor( "CoinScoreMultiplierObject" );
#endif
		}

	
		struct OnCoinGrabProxy : public Lambda_1<boost::shared_ptr<ObjectBase> >
		{
		
			boost::shared_ptr<CoinScoreMultiplierObject> csmo;
		
			OnCoinGrabProxy( const boost::shared_ptr<CoinScoreMultiplierObject> &csmo );

			void Apply( const boost::shared_ptr<ObjectBase> &obj );
		};

	
		struct OnLevelRetryProxy : public Lambda
		{
		
			boost::shared_ptr<CoinScoreMultiplierObject> csmo;
		
			OnLevelRetryProxy( const boost::shared_ptr<CoinScoreMultiplierObject> &csmo );

			void Apply();
		};

	
		struct OnCalculateCoinScoreMultiplierProxy : public Lambda_1<boost::shared_ptr<GameData> >
		{
		
			boost::shared_ptr<CoinScoreMultiplierObject> csmo;
		
			OnCalculateCoinScoreMultiplierProxy( const boost::shared_ptr<CoinScoreMultiplierObject> &csmo );

			void Apply( const boost::shared_ptr<GameData> &obj );
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
		void OnCoinGrab( const boost::shared_ptr<ObjectBase> &obj );

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
