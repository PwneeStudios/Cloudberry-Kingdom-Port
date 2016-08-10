#include <small_header.h>
#include "Game/Objects/Game Objects/GameObjects/CoinScoreMultiplierObject.h"

#include "Game/Objects/ObjectBase.h"
#include "Game/Objects/Game Objects/GameObject.h"

#include "Game/Games/GameType.h"

namespace CloudberryKingdom
{

	CoinScoreMultiplierObject::OnCoinGrabProxy::OnCoinGrabProxy( const boost::shared_ptr<CoinScoreMultiplierObject> &csmo )
	{
		this->csmo = csmo;
	}

	void CoinScoreMultiplierObject::OnCoinGrabProxy::Apply( const boost::shared_ptr<ObjectBase> &obj )
	{
		csmo->OnCoinGrab( obj );
	}

	CoinScoreMultiplierObject::OnLevelRetryProxy::OnLevelRetryProxy( const boost::shared_ptr<CoinScoreMultiplierObject> &csmo )
	{
		this->csmo = csmo;
	}

	void CoinScoreMultiplierObject::OnLevelRetryProxy::Apply()
	{
		csmo->OnLevelRetry();
	}

	CoinScoreMultiplierObject::OnCalculateCoinScoreMultiplierProxy::OnCalculateCoinScoreMultiplierProxy( const boost::shared_ptr<CoinScoreMultiplierObject> &csmo )
	{
		this->csmo = csmo;
	}

	void CoinScoreMultiplierObject::OnCalculateCoinScoreMultiplierProxy::Apply( const boost::shared_ptr<GameData> &obj )
	{
		obj->CoinScoreMultiplier *= csmo->_CoinScoreMultiplier;
	}

	void CoinScoreMultiplierObject::OnAdd()
	{
		GameObject::OnAdd();

		ResetMultiplier();

		MyGame->OnCoinGrab->Add( boost::make_shared<OnCoinGrabProxy>( boost::static_pointer_cast<CoinScoreMultiplierObject>( shared_from_this() ) ) );
		MyGame->OnLevelRetry->Add( boost::make_shared<OnLevelRetryProxy>( boost::static_pointer_cast<CoinScoreMultiplierObject>( shared_from_this() ) ) );

		MyGame->OnCalculateCoinScoreMultiplier->Add( boost::make_shared<OnCalculateCoinScoreMultiplierProxy>( boost::static_pointer_cast<CoinScoreMultiplierObject>( shared_from_this() ) ) );
	}

	void CoinScoreMultiplierObject::ReleaseBody()
	{
		GameObject::ReleaseBody();

		//MyGame.OnCoinGrab -= OnCoinGrab;
		//MyGame.OnLevelRetry -= OnLevelRetry;
	}

	const float &CoinScoreMultiplierObject::getCoinScoreMultiplier() const
	{
		return _CoinScoreMultiplier;
	}

	void CoinScoreMultiplierObject::setCoinScoreMultiplier( const float &value )
	{
		_CoinScoreMultiplier = value;
		//UpdateGameMultiplier();                
	}

	void CoinScoreMultiplierObject::OnCoinGrab( const boost::shared_ptr<ObjectBase> &obj )
	{
		setCoinScoreMultiplier( getCoinScoreMultiplier() + 1 );
	}

	void CoinScoreMultiplierObject::OnLevelRetry()
	{
		ResetMultiplier();
	}

	void CoinScoreMultiplierObject::ResetMultiplier()
	{
		setCoinScoreMultiplier( 1 );
	}

	CoinScoreMultiplierObject::CoinScoreMultiplierObject()
	{
		// Object is carried over through multiple levels, so prevent it from being released.
		InitializeInstanceFields();
		PreventRelease = true;

		PauseOnPause = true;
	}

	void CoinScoreMultiplierObject::InitializeInstanceFields()
	{
		_CoinScoreMultiplier = 1;
	}
}
