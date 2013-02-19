#include <global_header.h>

#include <Hacks\List.h>

#include <Game\CloudberryKingdom\CloudberryKingdom.CloudberryKingdomGame.h>

namespace CloudberryKingdom
{

	GUI_Panel::ReturnToCallerHelper::ReturnToCallerHelper( const boost::shared_ptr<GUI_Panel> &panel )
	{
		this->panel = panel;
	}

	void GUI_Panel::ReturnToCallerHelper::Apply()
	{
		panel->OnReturnTo();
	}

	GUI_Panel::ItemReturnToCallerProxy::ItemReturnToCallerProxy( const boost::shared_ptr<GUI_Panel> &guiPanel )
	{
		this->guiPanel = guiPanel;
	}

	void GUI_Panel::ItemReturnToCallerProxy::Apply( const boost::shared_ptr<MenuItem> &item )
	{
		guiPanel->ItemReturnToCaller( item );
	}

	GUI_Panel::MenuReturnToCallerProxy::MenuReturnToCallerProxy( const boost::shared_ptr<GUI_Panel> &guiPanel )
	{
		this->guiPanel = guiPanel;
	}

	void GUI_Panel::MenuReturnToCallerProxy::Apply( const boost::shared_ptr<Menu> &menu )
	{
		guiPanel->MenuReturnToCaller( menu );
	}

	GUI_Panel::MenuReturnToCallerLambda::MenuReturnToCallerLambda( const boost::shared_ptr<GUI_Panel> &panel )
	{
		this->panel = panel;
	}

	void GUI_Panel::MenuReturnToCallerLambda::Apply( const boost::shared_ptr<MenuItem> &item )
	{
		panel->ReturnToCaller();
	}

	GUI_Panel::MenuReturnToCallerLambdaFunc::MenuReturnToCallerLambdaFunc( const boost::shared_ptr<GUI_Panel> &panel )
	{
		this->panel = panel;
	}

	bool GUI_Panel::MenuReturnToCallerLambdaFunc::Apply( const boost::shared_ptr<Menu> &menu )
	{
		return panel->MenuReturnToCaller( menu );
	}

	GUI_Panel::CallHelper::CallHelper( const boost::shared_ptr<GUI_Panel> &panel, const boost::shared_ptr<GUI_Panel> &child )
	{
		this->panel = panel;
		this->child = child;
	}

	void GUI_Panel::CallHelper::Apply()
	{
		panel->MyGame->AddGameObject( child );
	}

	std::vector<std::wstring> GUI_Panel::GetViewables()
	{
		std::wstring tempVector[] = { std::wstring( L"MyMenu" ), std::wstring( L"MyPile" ) };
		return VecFromArray( tempVector );
	}

	void GUI_Panel::setControl( const int &value )
	{
		_Control = value;
		if ( MyMenu != 0 )
			MyMenu->setControl( value );
	}

	const int &GUI_Panel::getControl() const
	{
		return _Control;
	}

	void GUI_Panel::Shift( Vector2 shift )
	{
		AmountShifted += shift;

		if ( MyPile != 0 )
			MyPile->setPos( MyPile->getPos() + shift );
		if ( MyMenu != 0 )
			MyMenu->setPos( MyMenu->getPos() + shift );
	}

	void GUI_Panel::ReturnToCaller()
	{
		if ( NoBackIfNoCaller && Caller == 0 )
			return;

		ReleaseWhenDone = true;

		Hide();

		if ( Caller != 0 )
			MyGame->WaitThenDo( ReturnToCallerDelay, boost::make_shared<ReturnToCallerHelper>( this->Caller ) );
	}

	void GUI_Panel::ItemReturnToCaller( const boost::shared_ptr<MenuItem> &item )
	{
		ReturnToCaller();
	}

	bool GUI_Panel::MenuReturnToCaller( const boost::shared_ptr<Menu> &menu )
	{
		ReturnToCaller();

		return true;
	}

	void GUI_Panel::OnReturnTo()
	{
		// Reset the menu's selected item's oscillate
		if ( MyMenu != 0 )
			MyMenu->getCurItem()->OnSelect();

		// Activate and show the panel
		Active = true;
		Show();
	}

	void GUI_Panel::Call( const boost::shared_ptr<GUI_Panel> &child )
	{
		Call( child, CallDelay );
	}

	void GUI_Panel::Call( const boost::shared_ptr<GUI_Panel> &child, int Delay )
	{
		child->Caller = boost::static_pointer_cast<GUI_Panel>( shared_from_this() );

		SetChildControl( child );

		MyGame->WaitThenDo( Delay, boost::make_shared<CallHelper>( boost::static_pointer_cast<GUI_Panel>( shared_from_this() ), child ) );

		Active = false;
	}

	void GUI_Panel::SetChildControl( const boost::shared_ptr<GUI_Panel> &child )
	{
		// Copy control index to the child panel if the child hasn't initialized it's control already
		if ( child->getControl() < 0 )
			child->setControl( getControl() );
	}

	void GUI_Panel::Show()
	{
		Hid = false;
	}

	void GUI_Panel::Hide()
	{
		setPauseGame( false );
		Hid = true;
	}

	GUI_Panel::GUI_Panel() :
		NoBackIfNoCaller( false ),
		_Control( 0 ),
		Active( false ),
		ReturnToCallerDelay( 0 ),
		CallDelay( 0 ),
		ReleaseWhenDoneScaling( false ),
		Hid( false ),
		FixedToCamera( false ),
		SlideOutLength( 0 ), SlideInLength( 0 ),
		IsOnScreen( false ),
		CheckForOutsideClick( false ),	
		outside( false )
	{
	}
	boost::shared_ptr<GUI_Panel> GUI_Panel::GUI_Panel_Construct()
	{
		InitializeInstanceFields();
		Constructor();

		return boost::static_pointer_cast<GUI_Panel>( shared_from_this() );
	}

	GUI_Panel::GUI_Panel( bool CallBaseConstructor ) :
		NoBackIfNoCaller( false ),
		_Control( 0 ),
		Active( false ),
		ReturnToCallerDelay( 0 ),
		CallDelay( 0 ),
		ReleaseWhenDoneScaling( false ),
		Hid( false ),
		FixedToCamera( false ),
		SlideOutLength( 0 ), SlideInLength( 0 ),
		IsOnScreen( false ),
		CheckForOutsideClick( false ),	
		outside( false )
	{
	}
	boost::shared_ptr<GUI_Panel> GUI_Panel::GUI_Panel_Construct( bool CallBaseConstructor )
	{
		InitializeInstanceFields();
		if ( CallBaseConstructor )
			Constructor();

		return boost::static_pointer_cast<GUI_Panel>( shared_from_this() );
	}

	void GUI_Panel::Constructor()
	{
		Tools::StartGUIDraw_Fake();
		Init();
		Tools::EndGUIDraw_Fake();
	}

	void GUI_Panel::Init()
	{
		GameObject::Init();

		Pos = boost::make_shared<FancyVector2>();
	}

	void GUI_Panel::OnCameraChange()
	{
		GameObject::OnCameraChange();

		if ( FixedToCamera && getCore()->MyLevel != 0 )
		{
			Pos->Center = getCore()->MyLevel->getMainCamera();
			//Pos.SetCenter(Core.MyLevel.MainCamera, false);
		}
	}

	void GUI_Panel::OnAdd()
	{
		EnsureFancy();

		GameObject::OnAdd();

		if ( FixedToCamera )
			Pos->SetCenter( getCore()->MyLevel->getMainCamera(), true );
		Pos->Update();
	}

	void GUI_Panel::SlideIn()
	{
		SlideIn( SlideInLength );
	}

	void GUI_Panel::SlideIn( int Frames )
	{
		Active = true;
		//Pos.LerpTo(Vector2.Zero, Frames, LerpStyle.DecayNoOvershoot);
		Pos->LerpTo( Vector2(), Frames );
	}

	void GUI_Panel::CopySlideLengths( const boost::shared_ptr<GUI_Panel> &source )
	{
		SlideInLength = source->SlideInLength;
		SlideOutLength = source->SlideOutLength;
	}

	void GUI_Panel::setSlideLength( const int &value )
	{
		SlideInLength = SlideOutLength = value;
	}

	void GUI_Panel::SlideOut( PresetPos Preset )
	{
		SlideOut( Preset, SlideOutLength );
	}

	void GUI_Panel::SlideOut( PresetPos Preset, int Frames )
	{
		// Don't slide out if we've already slid out
		//if (!Active && !Tools::CurCamera.OnScreen(Pos.AbsVal)) return;

		Active = false;

		Vector2 Destination = SlideOutDestination( Preset );

		if ( Frames == 0 )
		{
			Pos->RelVal = Destination;
			Pos->Playing = false;
		}
		else
			Pos->LerpTo( Destination, Frames );
	}

	Vector2 GUI_Panel::SlideOutDestination( PresetPos Preset )
	{
		Vector2 Destination = Vector2();
		switch ( Preset )
		{
			case PresetPos_LEFT:
				Destination = Vector2( -getCore()->MyLevel->getMainCamera()->GetWidth(), 0 );
				break;

			case PresetPos_RIGHT:
				Destination = Vector2( getCore()->MyLevel->getMainCamera()->GetWidth(), 0 );
				break;

			case PresetPos_TOP:
				Destination = Vector2( 0, getCore()->MyLevel->getMainCamera()->GetHeight() );
				break;

			case PresetPos_BOTTOM:
				Destination = Vector2( 0, -getCore()->MyLevel->getMainCamera()->GetHeight() );
				break;
		}

		return Destination * DestinationScale;
	}

	void GUI_Panel::EnsureFancy()
	{
		if ( MyPile != 0 && MyPile->FancyPos == 0 )
			MyPile->FancyPos = boost::make_shared<FancyVector2>( Pos );
		if ( MyMenu != 0 && MyMenu->FancyPos == 0 )
			MyMenu->FancyPos = boost::make_shared<FancyVector2>( Pos );
	}

	bool GUI_Panel::OnScreen()
	{
		if ( FixedToCamera )
		{
			return Pos->Playing || fabs( Pos->RelVal.X ) < .85f * Tools::CurLevel->getMainCamera()->GetWidth() && fabs(Pos->RelVal.Y) < .85f * Tools::CurLevel->getMainCamera()->GetHeight();
				// Pos.RelVal.Length() < .5f * Tools::CurLevel.MainCamera.GetWidth();
		}
		else
			return MyGame->getCam()->OnScreen(Pos->Update(), 800);
	}

	const Vector2 &GUI_Panel::getMyCameraZoom() const
	{
		return _MyCameraZoom;
	}

	void GUI_Panel::setMyCameraZoom( const Vector2 &value )
	{
		_MyCameraZoom = value;
	}

	void GUI_Panel::MyDraw()
	{
		setMyCameraZoom( Tools::getCurCamera()->getZoom() );

		if ( CloudberryKingdomGame::HideGui )
			return;
		if ( !getCore()->Show || getCore()->Released )
			return;

		// Skip if offscreen
		IsOnScreen = OnScreen();
		if ( !IsOnScreen )
			return;

		EnsureFancy();

		EnsurePileFancyPos();
		EnsureMenuFancyPos();

		if ( MyPile != 0 )
			MyPile->Update();

		for ( int i = 0; i < 3; i++ )
		{
			// Draw the DrawPile
			if ( MyPile != 0 )
				MyPile->Draw( i );

			// Draw the menu
			if ( MyMenu != 0 && MyMenu->Layer == i )
				MyMenu->Draw();
		}
	}

	void GUI_Panel::EnsurePileFancyPos()
	{
		if ( MyPile != 0 )
		{
			MyPile->FancyPos->SetCenter( Pos, true );
			MyPile->FancyPos->Update();
		}
	}

	void GUI_Panel::EnsureMenuFancyPos()
	{
		if ( MyMenu != 0 )
		{
			MyMenu->FancyPos->SetCenter( Pos, true );
			MyMenu->FancyPos->Update();
		}
	}

	void GUI_Panel::DrawNonText()
	{
		EnsurePileFancyPos();
		EnsureMenuFancyPos();

		if ( MyPile != 0 )
			MyPile->DrawNonText( 0 );

		if ( MyMenu != 0 )
			MyMenu->DrawNonText( 0 );
	}

	void GUI_Panel::DrawNonText2()
	{
		EnsurePileFancyPos();
		EnsureMenuFancyPos();

		if ( MyMenu != 0 )
			MyMenu->DrawNonText2();
	}

	void GUI_Panel::DrawText()
	{
		EnsurePileFancyPos();
		EnsureMenuFancyPos();

		if ( MyPile != 0 )
			MyPile->DrawText( 0 );

		if ( MyMenu != 0 )
			MyMenu->DrawText( 0 );
	}

	void GUI_Panel::ReleaseBody()
	{
		GameObject::ReleaseBody();

		if ( MyMenu != 0 ) MyMenu->Release(); MyMenu.reset();
		if ( MyPile != 0 ) MyPile->Release(); MyPile.reset();

		Caller.reset();

		if ( Pos != 0 ) Pos->Release(); Pos.reset();
		OnOutsideClick.reset();
	}

	void GUI_Panel::PauseAnimation()
	{
		Pos->Playing = false;
	}

	void GUI_Panel::UnpauseAnimation()
	{
		Pos->Playing = true;
	}

	void GUI_Panel::MyPhsxStep()
	{
		CheckForBackFromOutsideClick();

		boost::shared_ptr<Level> level = getCore()->MyLevel;

		Pos->Update();

		// Release if we are set to release and are done with any animations.
		if ( ReleaseWhenDone && !Pos->Playing )
			Release();
		// Release if we are set to release after scaling and scaling is done
		if ( MyPile != 0 && MyPile->FancyScale != 0 )
			if ( ReleaseWhenDoneScaling && !MyPile->FancyScale->Playing )
				Release();

		if ( !Active )
			return;

		if ( MyMenu != 0 && !MyMenu->Released )
			MyMenu->PhsxStep();

		// Right shoulder action
		if ( ButtonCheck::State( ControllerButtons_RS, getControl() ).Pressed )
		{
			OnRightShoulder();
		}
	}

	void GUI_Panel::OnRightShoulder()
	{
	}

	bool GUI_Panel::HitTest( Vector2 pos )
	{
		return false;
	}

	void GUI_Panel::CheckForBackFromOutsideClick()
	{
		if ( !CheckForOutsideClick )
			return;
		if ( OnOutsideClick == 0 )
			return;

	#if defined(PC_VERSION)
		// Show the mouse so we can see when we are outside the panel
		Tools::TheGame->ShowMouse = true;

		// check if the player clicks back outside the panel
		bool ClickBack = false;
		if ( CheckForOutsideClick && ButtonCheck::MouseInUse && Tools::MouseReleased() )
			if ( outside )
				ClickBack = true;
		if ( !Tools::CurMouseDown() )
			if ( CheckForOutsideClick )
				outside = IsOutside();

		if ( Tools::RightMouseReleased() )
			ClickBack = true;

		// If so then perfom the designated action
		if ( ClickBack )
			OnOutsideClick->Apply();
	#endif
	}

	bool GUI_Panel::IsOutside()
	{
	#if defined(PC_VERSION)
		Vector2 MousePos = Tools::MouseGUIPos( getMyCameraZoom() );
		bool Hit = HitTest( MousePos );

		// Update the mouse icon to reflect whether clicking will go back or not
		Tools::TheGame->setDrawMouseBackIcon( !Hit );

		return !Hit;
	#else
		return false;
	#endif
	}

	void GUI_Panel::InitializeInstanceFields()
	{
		_Control = -2;
		AmountShifted = Vector2();
		ReturnToCallerDelay = 0;
		CallDelay = 0;
		NoBackIfNoCaller = false;
		ReleaseWhenDone = false;
		ReleaseWhenDoneScaling = false;
		Hid = true;
		FixedToCamera = true;
		SlideOutLength = 30;
		SlideInLength = 30;
		DestinationScale = Vector2(1);
		_MyCameraZoom = Vector2(1);
		IsOnScreen = false;
		CheckForOutsideClick = false;
		outside = false;
	}
}
