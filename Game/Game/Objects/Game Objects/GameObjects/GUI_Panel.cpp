#include "GUI_Panel.h"
#include "Game/Menus/Menu Components/MenuItem.h"
#include "Game/Menus/Menu.h"
#include "Core/Graphics/Draw/DrawPile.h"
#include "Core/FancyVector2.h"
#include "Game/Tools/Tools.h"
#include "Game/CloudberryKingdom/CloudberryKingdom.CloudberryKingdomGame.h"
#include "Game/Objects/In Game Objects/Grab/CloudberryKingdom.Level.h"
#include "Core/Input/ButtonCheck.h"

using namespace Microsoft::Xna::Framework;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;

namespace CloudberryKingdom
{

	GUI_Panel::ReturnToCallerHelper::ReturnToCallerHelper( const std::shared_ptr<GUI_Panel> &panel )
	{
		this->panel = panel;
	}

	void GUI_Panel::ReturnToCallerHelper::Apply()
	{
		panel->OnReturnTo();
	}

	GUI_Panel::ItemReturnToCallerProxy::ItemReturnToCallerProxy( const std::shared_ptr<GUI_Panel> &guiPanel )
	{
		this->guiPanel = guiPanel;
	}

	void GUI_Panel::ItemReturnToCallerProxy::Apply( const std::shared_ptr<MenuItem> &item )
	{
		guiPanel->ItemReturnToCaller( item );
	}

	GUI_Panel::MenuReturnToCallerProxy::MenuReturnToCallerProxy( const std::shared_ptr<GUI_Panel> &guiPanel )
	{
		this->guiPanel = guiPanel;
	}

	void GUI_Panel::MenuReturnToCallerProxy::Apply( const std::shared_ptr<Menu> &menu )
	{
		guiPanel->MenuReturnToCaller( menu );
	}

	GUI_Panel::MenuReturnToCallerLambda::MenuReturnToCallerLambda( const std::shared_ptr<GUI_Panel> &panel )
	{
		this->panel = panel;
	}

	void GUI_Panel::MenuReturnToCallerLambda::Apply( const std::shared_ptr<MenuItem> &item )
	{
		panel->ReturnToCaller();
	}

	GUI_Panel::MenuReturnToCallerLambdaFunc::MenuReturnToCallerLambdaFunc( const std::shared_ptr<GUI_Panel> &panel )
	{
		this->panel = panel;
	}

	bool GUI_Panel::MenuReturnToCallerLambdaFunc::Apply( const std::shared_ptr<Menu> &menu )
	{
		return panel->MenuReturnToCaller( menu );
	}

	GUI_Panel::CallHelper::CallHelper( const std::shared_ptr<GUI_Panel> &panel, const std::shared_ptr<GUI_Panel> &child )
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
		const std::wstring* tempVector[] = { _T( "MyMenu" ), _T( "MyPile" ) };
		return std::vector<std::wstring*>( tempVector, tempVector + sizeof( tempVector ) / sizeof( tempVector[ 0 ] ) );
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

	std::wstring GUI_Panel::CopyToClipboard( const std::wstring &suffix )
	{
		std::wstring s = _T( "" );

		if ( MyMenu != 0 )
			s += MyMenu->CopyToClipboard( _T( "MyMenu." ) ) + _T( "\n" );
		if ( MyPile != 0 )
			s += MyPile->CopyToClipboard( _T( "MyPile." ) );

		return s;
	}

	void GUI_Panel::ProcessMouseInput( Vector2 shift, bool ShiftDown )
	{
		if ( MyMenu != 0 )
			MyMenu->ProcessMouseInput( shift, ShiftDown );
		if ( MyPile != 0 )
			MyPile->ProcessMouseInput( shift, ShiftDown );
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
			MyGame->WaitThenDo( ReturnToCallerDelay, std::make_shared<ReturnToCallerHelper>( this->Caller ) );
	}

	void GUI_Panel::ItemReturnToCaller( const std::shared_ptr<MenuItem> &item )
	{
		ReturnToCaller();
	}

	bool GUI_Panel::MenuReturnToCaller( const std::shared_ptr<Menu> &menu )
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

	void GUI_Panel::Call( const std::shared_ptr<GUI_Panel> &child )
	{
		Call( child, CallDelay );
	}

	void GUI_Panel::Call( const std::shared_ptr<GUI_Panel> &child, int Delay )
	{
		child->Caller = this;

		SetChildControl( child );

		MyGame->WaitThenDo( Delay, std::make_shared<CallHelper>( this, child ) );

		Active = false;
	}

	void GUI_Panel::SetChildControl( const std::shared_ptr<GUI_Panel> &child )
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

	GUI_Panel::GUI_Panel()
	{
		InitializeInstanceFields();
		Constructor();
	}

	GUI_Panel::GUI_Panel( bool CallBaseConstructor )
	{
		InitializeInstanceFields();
		if ( CallBaseConstructor )
			Constructor();
	}

	void GUI_Panel::Constructor()
	{
		Tools::StartGUIDraw();
		Init();
		Tools::EndGUIDraw();
	}

	void GUI_Panel::Init()
	{
		GameObject::Init();

		Pos = std::make_shared<FancyVector2>();
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
		Pos->LerpTo( Vector2::Zero, Frames );
	}

	void GUI_Panel::CopySlideLengths( const std::shared_ptr<GUI_Panel> &source )
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
		//if (!Active && !Tools.CurCamera.OnScreen(Pos.AbsVal)) return;

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

	Microsoft::Xna::Framework::Vector2 GUI_Panel::SlideOutDestination( PresetPos Preset )
	{
		Vector2 Destination = Vector2::Zero;
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
			MyPile->FancyPos = std::make_shared<FancyVector2>( Pos );
		if ( MyMenu != 0 && MyMenu->FancyPos == 0 )
			MyMenu->FancyPos = std::make_shared<FancyVector2>( Pos );
	}

	bool GUI_Panel::OnScreen()
	{
		if ( FixedToCamera )
		{
			return Pos->Playing || abs( Pos->RelVal.X ) < .85f * Tools::CurLevel->getMainCamera()->GetWidth() && abs(Pos->RelVal.Y) < .85f * Tools::CurLevel->getMainCamera()->GetHeight();
				// Pos.RelVal.Length() < .5f * Tools.CurLevel.MainCamera.GetWidth();
		}
		else
			return MyGame->getCam()->OnScreen(Pos->Update(), 800);
	}

	const Microsoft::Xna::Framework::Vector2 &GUI_Panel::getMyCameraZoom() const
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

		Caller.reset();
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

		std::shared_ptr<Level> level = getCore()->MyLevel;

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
		AmountShifted = Vector2::Zero;
		ReturnToCallerDelay = 0;
		CallDelay = 0;
		NoBackIfNoCaller = false;
		ReleaseWhenDone = false;
		ReleaseWhenDoneScaling = false;
		Hid = true;
		FixedToCamera = true;
		SlideOutLength = 30;
		SlideInLength = 30;
		DestinationScale = Vector2::One;
		_MyCameraZoom = Vector2::One;
		IsOnScreen = false;
		CheckForOutsideClick = false;
		outside = false;
	}
}
