#include <small_header.h>
#include "Game/Objects/Game Objects/GameObjects/GUI_Timer.h"

#include "Core/Tools/CoreMath.h"
#include "Game/Objects/ObjectBase.h"
#include "Game/Objects/Game Objects/GameObject.h"
#include "Game/Objects/Game Objects/GameObjects/GUI_Timer_Base.h"
#include "Game/Objects/In Game Objects/Grab/MakeData.h"
#include "Game/Level/Level.h"

#include "Game/Games/GameType.h"

namespace CloudberryKingdom
{

	GUI_Timer::OnCoinGrabProxy::OnCoinGrabProxy( const boost::shared_ptr<GUI_Timer> &timer )
	{
		this->timer = timer;
	}

	void GUI_Timer::OnCoinGrabProxy::Apply( const boost::shared_ptr<ObjectBase> &obj )
	{
		timer->OnCoinGrab( obj );
	}

	GUI_Timer::OnCompleteLevelProxy::OnCompleteLevelProxy( const boost::shared_ptr<GUI_Timer> &timer )
	{
		this->timer = timer;
	}

	void GUI_Timer::OnCompleteLevelProxy::Apply( const boost::shared_ptr<Level> &level )
	{
		timer->OnCompleteLevel( level );
	}

	void GUI_Timer::OnAdd()
	{
		GUI_Timer_Base::OnAdd();

		MyGame->OnCoinGrab->Add( boost::make_shared<OnCoinGrabProxy>( boost::static_pointer_cast<GUI_Timer>( shared_from_this() ) ) );
		MyGame->OnCompleteLevel->Add( boost::make_shared<OnCompleteLevelProxy>( boost::static_pointer_cast<GUI_Timer>( shared_from_this() ) ) );
	}

	void GUI_Timer::ReleaseBody()
	{
		//MyGame.OnCoinGrab -= OnCoinGrab; 

		GUI_Timer_Base::ReleaseBody();
	}

	void GUI_Timer::OnCoinGrab( const boost::shared_ptr<ObjectBase> &obj )
	{
		setTime( getTime() + CoinTimeValue );

		if ( getTime() > MaxTime )
			setTime( MaxTime );
	}

	void GUI_Timer::OnCompleteLevel( const boost::shared_ptr<Level> &level )
	{
		MinLevelStartTimeValue = 124;
		setTime( CoreMath::RestrictVal( MinLevelStartTimeValue, MaxTime, getTime() ) );
	}

	void GUI_Timer::InitializeInstanceFields()
	{
		CoinTimeValue = 60;
		MinLevelStartTimeValue = 62 + 31;
		MaxTime = 60;
	}

	GUI_Timer::GUI_Timer() :
		CoinTimeValue( 0 ),
		MinLevelStartTimeValue( 0 ),
		MaxTime( 0 )
	{
	}
	boost::shared_ptr<GUI_Timer> GUI_Timer::GUI_Timer_Construct()
	{
		InitializeInstanceFields();
		GUI_Timer_Base::GUI_Timer_Base_Construct();

		return boost::static_pointer_cast<GUI_Timer>( shared_from_this() );
	}
}
