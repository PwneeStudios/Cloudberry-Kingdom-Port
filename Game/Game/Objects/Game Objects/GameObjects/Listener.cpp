#include <global_header.h>

namespace CloudberryKingdom
{

	Listener::Listener() :
		MyType( Type_ON_DOWN ),
		TriggeringPlayerIndex( 0 ),
		RemoveAfterActivation( false ),
		MyButton( ControllerButtons_A )
	{
	}
	boost::shared_ptr<Listener> Listener::Listener_Construct()
	{
		InitializeInstanceFields();
		GUI_Panel::GUI_Panel_Construct();

		Active = true;
		PauseOnPause = true;
		getCore()->Show = false;

		return boost::static_pointer_cast<Listener>( shared_from_this() );
	}

	Listener::Listener( ControllerButtons button, const boost::shared_ptr<Lambda> &action ) :
		MyType( Type_ON_DOWN ),
		TriggeringPlayerIndex( 0 ),
		RemoveAfterActivation( false ),
		MyButton( ControllerButtons_A )
	{
	}
	boost::shared_ptr<Listener> Listener::Listener_Construct( ControllerButtons button, const boost::shared_ptr<Lambda> &action )
	{
		InitializeInstanceFields();
		GUI_Panel::GUI_Panel_Construct();

		if ( button == ControllerButtons_A )
		{
			if ( MyButton2 == 0 )
				MyButton2 = boost::make_shared<ButtonClass>();
			MyButton2->Set( ControllerButtons_ENTER );
		}

		Active = true;
		PauseOnPause = false;
		RemoveAfterActivation = true;

		MyButton = button;
		MyAction = action;

		setControl( -1 );

		return boost::static_pointer_cast<Listener>( shared_from_this() );
	}

	void Listener::Activate()
	{
		if ( MyAction != 0 )
			MyAction->Apply();

		if ( RemoveAfterActivation )
			Release();
	}

	void Listener::MyPhsxStep()
	{
		GUI_Panel::MyPhsxStep();

		if ( !Active )
			return;

		boost::shared_ptr<Level> level = getCore()->MyLevel;

		// Listen
		if ( MyType == Type_ON_DOWN && ( ButtonCheck::State( MyButton, getControl() ).Down || ButtonCheck::State(MyButton2, getControl()).Down ) || (MyType == Type_ON_PRESSED && (ButtonCheck::State(MyButton, getControl()).Pressed || ButtonCheck::State(MyButton2, getControl()).Pressed)) )
		{
			// If any player could trigger the event, check to see which did
			TriggeringPlayerIndex = getControl();
			if ( getControl() < 0 )
			{
				for ( int i = 0; i < 4; i++ )
				{
					switch ( MyType )
					{
						case Type_ON_PRESSED:
							if ( PlayerManager::Get( i )->Exists && ButtonCheck::State( MyButton, i ).Pressed )
								TriggeringPlayerIndex = i;
							break;

						case Type_ON_DOWN:
							if ( PlayerManager::Get( i )->Exists && ButtonCheck::State( MyButton, i ).Down )
								TriggeringPlayerIndex = i;
							break;
					}
				}
			}

			Activate();
		}
	}

	void Listener::InitializeInstanceFields()
	{
		MyType = Type_ON_PRESSED;
		RemoveAfterActivation = false;
		MyButton = ControllerButtons_A;
		MyButton2 = 0;
	}
}
