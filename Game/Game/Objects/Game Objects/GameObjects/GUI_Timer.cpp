#include <global_header.h>

namespace CloudberryKingdom
{

	GUI_Timer::OnCoinGrabProxy::OnCoinGrabProxy( const std::shared_ptr<GUI_Timer> &timer )
	{
		this->timer = timer;
	}

	void GUI_Timer::OnCoinGrabProxy::Apply( const std::shared_ptr<ObjectBase> &obj )
	{
		timer->OnCoinGrab( obj );
	}

	GUI_Timer::OnCompleteLevelProxy::OnCompleteLevelProxy( const std::shared_ptr<GUI_Timer> &timer )
	{
		this->timer = timer;
	}

	void GUI_Timer::OnCompleteLevelProxy::Apply( const std::shared_ptr<Level> &level )
	{
		timer->OnCompleteLevel( level );
	}

	void GUI_Timer::OnAdd()
	{
		GUI_Timer_Base::OnAdd();

		MyGame->OnCoinGrab->Add( std::make_shared<OnCoinGrabProxy>( std::static_pointer_cast<GUI_Timer>( shared_from_this() ) ) );
		MyGame->OnCompleteLevel->Add( std::make_shared<OnCompleteLevelProxy>( std::static_pointer_cast<GUI_Timer>( shared_from_this() ) ) );
	}

	void GUI_Timer::ReleaseBody()
	{
		//MyGame.OnCoinGrab -= OnCoinGrab; 

		GUI_Timer_Base::ReleaseBody();
	}

	void GUI_Timer::OnCoinGrab( const std::shared_ptr<ObjectBase> &obj )
	{
		setTime( getTime() + CoinTimeValue );

		if ( getTime() > MaxTime )
			setTime( MaxTime );
	}

	void GUI_Timer::OnCompleteLevel( const std::shared_ptr<Level> &level )
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

	GUI_Timer::GUI_Timer() { }
	void GUI_Timer::GUI_Timer_Construct()
	{
		GUI_Timer_Base::GUI_Timer_Base_Construct();

		InitializeInstanceFields();
	}
}
