#include <global_header.h>




namespace CloudberryKingdom
{

	Cast::ToMenuHelper1::ToMenuHelper1( const std::shared_ptr<Lambda_1<MenuItem*> > &a )
	{
		this->a = a;
	}

	bool Cast::ToMenuHelper1::Apply( const std::shared_ptr<Menu> &dummy )
	{
		a->Apply( 0 );
		return true;
	}

	Cast::LambdaWrapper::LambdaWrapper( const std::shared_ptr<Lambda> &a )
	{
		this->a = a;
	}

	void Cast::LambdaWrapper::Apply( const std::shared_ptr<MenuItem> &dummy )
	{
		a->Apply();
	}

	Cast::Lambda_1Wrapper::Lambda_1Wrapper( const std::shared_ptr<Lambda_1<Menu*> > &a )
	{
		this->a = a;
	}

	void Cast::Lambda_1Wrapper::Apply()
	{
		a->Apply( 0 );
	}

	Cast::ToMenuHelper::ToMenuHelper( const std::shared_ptr<Lambda> &a )
	{
		this->a = a;
	}

	bool Cast::ToMenuHelper::Apply( const std::shared_ptr<Menu> &dummy )
	{
		a->Apply();
		return true;
	}

	std::shared_ptr<LambdaFunc_1<Menu*, bool> > Cast::ToMenu( const std::shared_ptr<Lambda> &a )
	{
		return std::make_shared<ToMenuHelper>( a );
	}

	std::shared_ptr<LambdaFunc_1<Menu*, bool> > Cast::ToMenu( const std::shared_ptr<Lambda_1<MenuItem*> > &a )
	{
		return std::make_shared<ToMenuHelper1>( a );
	}

	std::shared_ptr<Lambda_1<MenuItem*> > Cast::ToItem( const std::shared_ptr<Lambda> &a )
	{
		return std::make_shared<LambdaWrapper>( a );
	}

	std::shared_ptr<Lambda> Cast::ToAction( const std::shared_ptr<Lambda_1<Menu*> > &a )
	{
		return std::make_shared<Lambda_1Wrapper>( a );
	}

	Menu::FindItemByNameLambda::FindItemByNameLambda( const std::wstring &name )
	{
		this->name = name;
	}

	bool Menu::FindItemByNameLambda::Apply( const std::shared_ptr<MenuItem> &item )
	{
		return item->Name == name;
	}

	bool Menu::DefaultOnBProxy::Apply( const std::shared_ptr<Menu> &menu )
	{
		return Menu::DefaultOnB( menu );
	}

Vector4 Menu::DefaultMenuInfo::SelectedNextColor = ( Color( 100, 250, 100, 255 ) ).ToVector4();
Vector4 Menu::DefaultMenuInfo::SelectedBackColor = ( Color( 250, 100, 100, 255 ) ).ToVector4();
Vector4 Menu::DefaultMenuInfo::UnselectedNextColor = ( Color( 40, 180, 40, 255 ) ).ToVector4();
Vector4 Menu::DefaultMenuInfo::UnselectedBackColor = ( Color( 180, 40, 40, 255 ) ).ToVector4();
std::shared_ptr<EzSound> Menu::DefaultMenuInfo::Menu_UpDown_Sound = Tools::NewSound( _T( "Menu_Hover" ),.7f );
std::shared_ptr<EzSound> Menu::DefaultMenuInfo::Menu_Select_Sound = Tools::NewSound( _T( "Menu_Select" ),.6f );
std::shared_ptr<EzSound> Menu::DefaultMenuInfo::Menu_Slide_Sound = Tools::NewSound( _T( "Menu_Tick" ),.3f );
std::shared_ptr<EzSound> Menu::DefaultMenuInfo::Menu_ListScroll_Sound = Tools::NewSound( _T( "Menu_Hover" ),.5f );
std::shared_ptr<EzSound> Menu::DefaultMenuInfo::Menu_Back_Sound = Tools::NewSound( _T( "Menu_Back" ),.8f );
int Menu::DefaultMenuInfo::Menu_Slide_SoundDelay = 8;
std::shared_ptr<EzTexture> Menu::DefaultMenuInfo::MenuRightArrow_Texture = Tools::Texture( _T( "ListRightArrow" ) );
std::shared_ptr<EzTexture> Menu::DefaultMenuInfo::MenuLeftArrow_Texture = Tools::Texture( _T( "ListLeftArrow" ) );
Vector2 Menu::DefaultMenuInfo::MenuRightArrow_Offset = Vector2( 20, -14 );
Vector2 Menu::DefaultMenuInfo::MenuLeftArrow_Offset = Vector2( -20, -14 );
Vector2 Menu::DefaultMenuInfo::MenuArrow_Size = Vector2( 45, 45 );
Vector4 Menu::DefaultMenuInfo::MenuArrow_Color = ( Color( 255, 255, 255, 255 ) ).ToVector4();
std::shared_ptr<EzTexture> Menu::DefaultMenuInfo::MenuRightArrow_Selected_Texture = Tools::Texture( _T( "ListRightArrow" ) );
std::shared_ptr<EzTexture> Menu::DefaultMenuInfo::MenuLeftArrow_Selected_Texture = Tools::Texture( _T( "ListLeftArrow" ) );
Vector2 Menu::DefaultMenuInfo::MenuRightArrow_Selected_Offset = Vector2( 20, -14 );
Vector2 Menu::DefaultMenuInfo::MenuLeftArrow_Selected_Offset = Vector2( -20, -14 );
Vector2 Menu::DefaultMenuInfo::MenuArrow_Selected_Size = Vector2( 45, 45 );
Vector4 Menu::DefaultMenuInfo::MenuArrow_Selected_Color = ( Color( 255, 255, 255, 0 ) ).ToVector4();
std::shared_ptr<EzTexture> Menu::DefaultMenuInfo::SliderBack_Texture = Tools::Texture( _T( "menuslider_bar" ) );
Vector2 Menu::DefaultMenuInfo::SliderBack_Size = Vector2( 250, 35 );
std::shared_ptr<EzTexture> Menu::DefaultMenuInfo::Slider_Texture = Tools::Texture( _T( "menuslider_slider" ) );
Vector2 Menu::DefaultMenuInfo::Slider_StartPos = Vector2( -210, 0 );
Vector2 Menu::DefaultMenuInfo::Slider_EndPos = Vector2( 210, 0 );
Vector2 Menu::DefaultMenuInfo::Slider_Size = Vector2( 28, 55 );

	std::vector<std::wstring> Menu::GetViewables()
	{
		const std::wstring* tempVector[] = { _T( "BackdropShift" ), _T( "Items" ) };
		return std::vector<std::wstring*>( tempVector, tempVector + sizeof( tempVector ) / sizeof( tempVector[ 0 ] ) );
	}

	std::wstring Menu::CopyToClipboard( const std::wstring &suffix )
	{
		std::wstring s = _T( "" );

		if ( Items.size() > 0 )
			s += _T( "MenuItem _item;\n" );
		for ( std::vector<MenuItem*>::const_iterator item = Items.begin(); item != Items.end(); ++item )
		{
			s += ( *item )->ToCode( suffix ) + _T( "\n" );
		}

		if ( Items.size() > 0 )
			s += _T( "\n" );
		s += std::wstring::Format( _T( "{0}Pos = {1};\n" ), suffix, Tools::ToCode( getPos() ) );

		return s;
	}

	void Menu::ProcessMouseInput( Vector2 shift, bool ShiftDown )
	{
		setPos( getPos() + shift );
	}

	std::shared_ptr<MenuItem> Menu::FindItemByName( const std::wstring &name )
	{
		return Tools::Find( Items, std::make_shared<FindItemByNameLambda>( name ) );
	}

	void Menu::GetChildren( std::vector<InstancePlusName*> &ViewableChildren )
	{
		if ( Items.size() > 0 )
			for ( std::vector<MenuItem*>::const_iterator item = Items.begin(); item != Items.end(); ++item )
			{
				std::wstring name = ( *item )->MyText->MyString;
				ViewableChildren.push_back( std::make_shared<InstancePlusName>( *item, name ) );
			}
	}

	const Microsoft::Xna::Framework::Vector2 &Menu::getPos() const
	{
		return FancyPos->RelVal;
	}

	void Menu::setPos( const Vector2 &value )
	{
		FancyPos->RelVal = value;
	}

	const int &Menu::getControl() const
	{
		return _Control;
	}

	void Menu::setControl( const int &value )
	{
		_Control = value;
	}

	const std::shared_ptr<MenuItem> &Menu::getCurItem() const
	{
		if ( Items.empty() )
			return 0;

		return Items[ CurIndex ];
	}

	void Menu::Release()
	{
		Release( true );
	}

	void Menu::Release( bool ReleaseParents )
	{
		if ( Released )
			return;
		Released = true;

		if ( SelectIcon != 0 )
			SelectIcon->Release();
			SelectIcon.reset();
		if ( FancyPos != 0 )
			FancyPos->Release();
			FancyPos.reset();

		if ( ReleaseParents && ParentMenu != 0 )
			ParentMenu->Release( true );
		ParentMenu.reset();

		if ( Items.size() > 0 )
			for ( std::vector<MenuItem*>::const_iterator item = Items.begin(); item != Items.end(); ++item )
				( *item )->Release();
		Items.clear();

		OnStart = OnX = OnA = OnB = 0;

		AdditionalCheckForOutsideClick.reset();
	}

	void Menu::ClearList()
	{
		if ( Items.size() > 0 )
			for ( std::vector<MenuItem*>::const_iterator item = Items.begin(); item != Items.end(); ++item )
				( *item )->Release();
		Items.clear();
	}

	Menu::Menu()
	{
		InitializeInstanceFields();
		Init();
	}

	Menu::Menu( bool FixedToCamera )
	{
		InitializeInstanceFields();
		Init();
		this->FixedToCamera = FixedToCamera;
	}

	void Menu::Init()
	{
		UpDownSound = DefaultMenuInfo::Menu_UpDown_Sound;
		SelectSound = DefaultMenuInfo::Menu_Select_Sound;
		BackSound = DefaultMenuInfo::Menu_Back_Sound;
		SlideSound = DefaultMenuInfo::Menu_Slide_Sound;
		ListScrollSound = DefaultMenuInfo::Menu_ListScroll_Sound;

		SkipPhsx = true;

		setControl( -1 );

		Items = std::vector<MenuItem*>();
		CurIndex = 0;

		OnB = std::make_shared<DefaultOnBProxy>();

		MyPieceQuadTemplate.reset();
		MyPieceQuadTemplate2.reset();
	}

	bool Menu::DefaultOnB( const std::shared_ptr<Menu> &menu )
	{
		menu->Release( false );

		return true;
	}

	void Menu::SelectItem( const std::shared_ptr<MenuItem> &item )
	{
		HasSelectedThisStep = true;

		int Index = Items.find( item );
		if ( CurIndex != Index )
		{
			SelectItem( Index );
		}
	}

	void Menu::SelectItem( int Index )
	{
		HasSelectedThisStep = true;

		// If no items are selectable, return
		bool All = true;
		for ( std::vector<MenuItem*>::const_iterator item = Items.begin(); item != Items.end(); ++item )
			if ( ( *item )->Selectable )
				All = false;
		if ( All )
			return;

		// Play a selection sound
		if ( UpDownSound != 0 && ReadyToPlaySound )
			UpDownSound->Play();

//C# TO C++ CONVERTER NOTE: The variable Sign was renamed since it is named the same as a user-defined type:
		int Sign_Renamed = Math::Sign( Index - CurIndex );
		if ( Sign_Renamed == 0 )
			Sign_Renamed = 1;

		// Ensure a valid index
		if ( WrapSelect )
		{
			if ( Index < 0 )
			{
				CurIndex = Index = Items.size() - 1;
			}
			if ( Index >= Items.size() )
			{
				CurIndex = Index = 0;
			}
		}
		else
			Index = __max( 0, __min( Items.size() - 1, Index ) );


		if ( Items[ Index ]->Selectable && Items[ Index ]->Show )
			CurIndex = Index;
		else
		{
			// Find the next selectable index
			while ( !Items[ Index ]->Selectable || !Items[ Index ]->Show )
			{
				//if (Index > CurIndex) Index++;
				//else if (Index < CurIndex) Index--;
				//else Index++;

				Index += Sign_Renamed;

				if ( WrapSelect )
				{
					if ( Index < 0 )
						Index = Items.size() - 1;
					if ( Index >= Items.size() )
						Index = 0;
				}
				else
				{
					if ( Index < 0 ) // Index = 0; CurIndex = 0; }
					{
						Index = CurIndex;
						break;
					}
					if ( Index >= Items.size() ) // Index = Items.Count; CurIndex = Items.Count + 1; }
					{
						Index = CurIndex;
						break;
					}
				}
			}

			CurIndex = Index;
		}

		if ( OnSelect != 0 )
			OnSelect->Apply();

		SkipPhsx = true;
	}

	bool Menu::CheckForBackFromOutsideClick()
	{
	#if defined(PC_VERSION)
		bool Hit = HitTest();

		if ( !Hit && AdditionalCheckForOutsideClick != 0 )
			Hit |= AdditionalCheckForOutsideClick->Apply();

		// Update the mouse icon to reflect whether clicking will go back or not
		Tools::TheGame->setDrawMouseBackIcon( !Hit );

		return !Hit;
	#else
		return false;
	#endif
	}

#if defined(PC_VERSION)
	bool Menu::HitTest()
	{
		return HitTest( Vector2( 100, 100 ) );
	}
#endif

#if defined(PC_VERSION)
	bool Menu::HitTest( Vector2 HitPadding )
	{
		Vector2 MousePos = Tools::MouseGUIPos( getMyCameraZoom() );

		bool Hit = false;
		for ( std::vector<MenuItem*>::const_iterator item = Items.begin(); item != Items.end(); ++item )
			Hit |= ( *item )->HitTest( MousePos, HitPadding );

		return Hit;
	}
#endif

	void Menu::PhsxStep()
	{
		if ( !Active || !Show )
			return;

		if ( SkipPhsx )
		{
			SkipPhsx = false;
			return;
		}

		if ( Tools::TheGame->DrawCount - ActiveTimeStamp > 5 )
		{
			SkipPhsx = true;
			ActiveTimeStamp = Tools::TheGame->DrawCount;
			return;
		}
		ActiveTimeStamp = Tools::TheGame->DrawCount;

	#if defined(PC_VERSION)
		// Show the mouse 
		Tools::TheGame->ShowMouse = true;

		// If mouse is in use check to see if anything should be selected
		if ( ButtonCheck::MouseInUse )
		{
			/*
			if (Tools.MouseDown())
			    NoneSelected = false;
			else*/
		{
				// MUST BE POSITIVE
				Vector2 HitPadding = Vector2( 100, 0 );

				// If we are checking whether to start showing selections again,
				// only do so if we actually hit a MenuItem
				if ( NoneSelected )
					HitPadding = Vector2::Zero;

				if ( !HitTest( HitPadding ) )
					NoneSelected = true;
				else
					NoneSelected = false;
			}
		}
		else
		{
			// If the mouse isn't in use and the menu is capable of using the keyboard,
			// then start behaving as if the keyboard is the main input device and no mouse exists
			if ( !MouseOnly )
				NoneSelected = false;
		}
	#endif 

		// Start button action
		if ( OnStart != 0 && ButtonCheck::State( ControllerButtons_START, getControl() ).Pressed )
		{
			ButtonCheck::PreventInput();
			OnStart->Apply( this );
		}

		// X button action
		if ( OnX != 0 && ButtonCheck::State( ControllerButtons_X, getControl() ).Pressed )
		{
			ButtonCheck::PreventInput();
			OnX->Apply( this );
		}

		// Y button action
		if ( OnY != 0 && ButtonCheck::State( ControllerButtons_Y, getControl() ).Pressed )
		{
			ButtonCheck::PreventInput();
			OnY->Apply();
		}

		// Allow for a new item to be selected if the user has stopped holding down A (or LeftMouseButton)
		if ( !ButtonCheck::State( ControllerButtons_A, getControl() ).Pressed )
			HasSelectedThisStep = false;

		if ( OnA_AutoTimerLength > 0 && OnA_AutoTimerCount > 0 )
		{
			OnA_AutoTimerCount--;
			if ( OnA_AutoTimerCount == 0 )
				if ( OnA != 0 )
					if ( OnA->Apply( this ) )
						return;
		}

		bool ActivateOnA = false;
		if ( ButtonCheck::State( ControllerButtons_A, getControl() ).Pressed )
			ActivateOnA = true;

		// Don't activate the item if it isn't being drawn as selected
		//if (NoneSelected)
		//    ActivateOnA = false;

	#if defined(WINDOWS)
		if ( !Tools::MouseNotDown() )
			ActivateOnA = false;
	#endif
		// A button
		if ( ActivateOnA )
		{
			bool CheckForOverride = true;
	#if defined(PC_VERSION)
			if ( ButtonCheck::State( ButtonCheck::Go_Secondary ).Pressed )
				CheckForOverride = false;
	#endif
			if ( OnA != 0 && !( CheckForOverride && Items[ CurIndex ]->getOverrideA() ) )
			{
				//ButtonCheck.PreventInput();
				if ( OnA->Apply( this ) )
					return;
			}
		}

		if ( SkipPhsx )
		{
			return;
		}

		// Click outside the menu to go back
		bool ClickBack = false;

	#if defined(PC_VERSION)
		if ( CheckForOutsideClick && NoneSelected && ButtonCheck::MouseInUse && Tools::MouseReleased() )
			if ( outside )
				ClickBack = true;
		if ( !Tools::CurMouseDown() )
		{
			if ( CheckForOutsideClick && OnB != 0 )
				outside = CheckForBackFromOutsideClick();
			else
			{
				outside = false;
				if ( AffectsOutsideMouse )
					Tools::TheGame->setDrawMouseBackIcon( false );
			}
		}

		if ( Tools::RightMouseReleased() )
			ClickBack = true;
	#endif
		// B button
		if ( ButtonCheck::State( ControllerButtons_B, getControl() ).Pressed || ClickBack )
		{
			if ( OnB != 0 )
			{
				if ( BackSound != 0 )
					BackSound->Play();

				if ( OnB->Apply( this ) )
					return;

				ButtonCheck::PreventInput();
			}
		}

		if ( SkipPhsx )
		{
			return;
		}

		for ( std::vector<MenuItem*>::const_iterator item = Items.begin(); item != Items.end(); ++item )
		{
			( *item )->PhsxStep( *item == Items[ CurIndex ] && ( !NoneSelected || AlwaysSelected ) );
			if ( Released )
				return;
		}

	#if defined(PC_VERSION)
		// If the mouse is in use and nothing is selected, then hitting a key on the keyboard
		// should only hide the mouse, it shouldn't immediately change what is selected
		if ( ButtonCheck::MouseInUse )
		{
			if ( NoneSelected )
				DelayCount = SelectDelay;
			else
				DelayCount = 0;
		}
	#endif

		// If the menu can use the keyboard then check for index changes by the arrow keys
	#if defined(PC_VERSION)
		if ( !MouseOnly && !ButtonCheck::PrevMouseInUse )
	#else
		if ( !MouseOnly )
	#endif
		{
			if ( DelayCount > 0 )
				DelayCount--;

			Vector2 Dir = Vector2::Zero;
			if ( getControl() < 0 )
			{
				Dir = ButtonCheck::GetMaxDir( getControl() == -1 );
			}
			else
				Dir = ButtonCheck::GetDir( getControl() );

			if ( Dir.Length() < .2f )
				DelayCount = 0;

			if ( abs( Dir.Y ) > ButtonCheck::ThresholdSensitivity )
			{
				MotionCount++;
				if ( DelayCount <= 0 )
				{
					if ( Dir.Y > 0 )
						SelectItem( CurIndex - 1 );
					else
						SelectItem( CurIndex + 1 );

					DelayCount = SelectDelay;
					if ( MotionCount > SelectDelay * 2 )
						DelayCount /= 2;
				}
			}
			else
				MotionCount = 0;
		}

		ReadyToPlaySound = true;
	}

	void Menu::ArrangeItems( float Spacing, Vector2 Center )
	{
		Vector2 Pos = Center;
		for ( int i = 0; i < Items.size(); i++ )
		{
			Pos.Y -= Spacing + Items[ i ]->Height() / 2;

			Items[ i ]->Pos = Pos;

			Pos.Y -= Spacing + Items[ i ]->Height() / 2;
		}

		float Height = Center.Y - Pos.Y;
		for ( std::vector<MenuItem*>::const_iterator item = Items.begin(); item != Items.end(); ++item )
			( *item )->Pos.Y += Height / 2;
	}

	void Menu::SetBoundary()
	{
		SetBoundary( Vector2( 110, 84 ), Vector2( 110, 84 ) );
	}

	void Menu::SetBoundary( Vector2 Padding )
	{
		SetBoundary( Padding, Padding );
	}

	void Menu::SetBoundary( Vector2 TR_Padding, Vector2 BL_Padding )
	{
		CalcBounds();

		TR += TR_Padding;
		BL -= BL_Padding;

		ResetPieces();
	}

	void Menu::CalcBounds()
	{
		TR = Vector2( -100000, -100000 );
		BL = Vector2( 100000, 100000 );

		for ( std::vector<MenuItem*>::const_iterator item = Items.begin(); item != Items.end(); ++item )
		{
			Vector2 Size = ( *item )->Size();
			TR = Vector2::Max( TR, ( *item )->Pos + Size / 2 );
			BL = Vector2::Min( BL, ( *item )->Pos - Size / 2 );
		}
	}

	int Menu::SortByHeightMethod( const std::shared_ptr<MenuItem> &item1, const std::shared_ptr<MenuItem> &item2 )
	{
		return -item1->Pos.Y.compare( item2->Pos.Y );
	}

	void Menu::SortByHeight()
	{
		Items.Sort( SortByHeightMethod );
	}

	void Menu::ResetPieces()
	{
		MyPieceQuad = std::make_shared<PieceQuad>();
		MyPieceQuad->Clone( MyPieceQuadTemplate );
		MyPieceQuad->CalcQuads( ( TR - BL ) / 2 );
		BackdropShift = ( TR + BL ) / 2;

		if ( MyPieceQuadTemplate2 != 0 )
		{
			MyPieceQuad2 = std::make_shared<PieceQuad>();
			MyPieceQuad2->Clone( MyPieceQuadTemplate2 );
			MyPieceQuad2->CalcQuads( ( TR - BL ) / 2 );
		}
	}

	void Menu::DrawNonText( int Layer )
	{
		setMyCameraZoom( Tools::getCurCamera()->getZoom() );
		if ( !Show )
			return;

		if ( FancyPos != 0 )
			PosOffset = FancyPos->Update();

		if ( MyPieceQuad != 0 && Layer == 0 )
		{
			if ( FixedToCamera )
				MyPieceQuad->Base.Origin = Tools::CurGameData->MyLevel->getMainCamera()->Data.Position + BackdropShift + PosOffset;
			else
				MyPieceQuad->Base.Origin = BackdropShift + PosOffset;
			MyPieceQuad->Draw();
		}

		CurDrawLayer = Layer;

		int SelectedIndex = getApparentCurIndex();

		// Draw item text backdrops
		for ( std::vector<MenuItem*>::const_iterator item = Items.begin(); item != Items.end(); ++item )
		{
			( *item )->PosOffset = PosOffset;
			if ( SelectedIndex < 0 || item != Items[ SelectedIndex ] )
				( *item )->DrawBackdrop( false );
		}
		if ( SelectedIndex >= 0 && Items.size() > 0 )
			Items[ SelectedIndex ]->DrawBackdrop( true );

		// Draw item non-text
		for ( std::vector<MenuItem*>::const_iterator item = Items.begin(); item != Items.end(); ++item )
		{
			( *item )->PosOffset = PosOffset;
			( *item )->Draw( false, Tools::CurLevel->getMainCamera(), DrawItemAsSelected(*item) );
		}

		if ( MyPieceQuadTemplate2 != 0 )
		{
			MyPieceQuad2->Base.Origin = Tools::CurLevel->getMainCamera()->Data.Position + BackdropShift + PosOffset;
			MyPieceQuad2->Draw();
		}
	}

	void Menu::DrawNonText2()
	{
		setMyCameraZoom( Tools::getCurCamera()->getZoom() );
		if ( !Show )
			return;

		CurDrawLayer = 1;
		for ( std::vector<MenuItem*>::const_iterator item = Items.begin(); item != Items.end(); ++item )
		{
			( *item )->Draw( false, Tools::CurLevel->getMainCamera(), DrawItemAsSelected(*item) );
		}

		// Draw select icon
		if ( SelectIcon != 0 && getApparentCurIndex() >= 0 )
		{
			SelectIcon->setPos( Items[ getApparentCurIndex() ]->Pos + Items[ getApparentCurIndex() ]->PosOffset + Items[ getApparentCurIndex() ]->SelectIconOffset );
			if ( FixedToCamera )
				SelectIcon->setPos( SelectIcon->getPos() + Tools::CurLevel->getMainCamera()->Data.Position );
			SelectIcon->Draw();
		}
	}

	void Menu::DrawText( int Layer )
	{
		setMyCameraZoom( Tools::getCurCamera()->getZoom() );
		if ( !Show )
			return;

		CurDrawLayer = Layer;

		// Draw item text
		for ( std::vector<MenuItem*>::const_iterator item = Items.begin(); item != Items.end(); ++item )
		{
			( *item )->PosOffset = PosOffset;
			if ( ( *item )->UnaffectedByScroll )
				( *item )->PosOffset -= FancyPos->RelVal;

			( *item )->Draw( true, Tools::CurLevel->getMainCamera(), DrawItemAsSelected(*item) );
		}
	}

	bool Menu::DrawItemAsSelected( const std::shared_ptr<MenuItem> &item )
	{
	#if defined(PC_VERSION)
	#else
		// Never draw anything as selected if the menu is mouse only and there is no mouse
		if ( MouseOnly )
			return false;
	#endif

		if ( !NoneSelected || AlwaysSelected )
			return item == Items[ CurIndex ];
		else if ( ShowLastActivated && LastActivatedItem >= 0 )
			return item == Items[ LastActivatedItem ];
		else
			return false;
	}

	const int &Menu::getApparentCurIndex() const
	{
		if ( !NoneSelected )
			return CurIndex;
		else if ( ShowLastActivated && LastActivatedItem >= 0 )
			return LastActivatedItem;
		else
			return -1;
	}

	const Microsoft::Xna::Framework::Vector2 &Menu::getMyCameraZoom() const
	{
		return _MyCameraZoom;
	}

	void Menu::setMyCameraZoom( const Vector2 &value )
	{
		_MyCameraZoom = value;
	}

	void Menu::Draw()
	{
		setMyCameraZoom( Tools::getCurCamera()->getZoom() );

		if ( !Show )
			return;

		DrawNonText( 0 );
		DrawText( 0 );
		Tools::Render->EndSpriteBatch();
		DrawNonText2();
		DrawText( 1 );
	}

	void Menu::Add( const std::shared_ptr<MenuItem> &item )
	{
		Add( item, Items.size() );
	}

	void Menu::Add( const std::shared_ptr<MenuItem> &item, int index )
	{
		item->SelectSound = SelectSound;
		item->SlideSound = SlideSound;
		item->ListScrollSound = ListScrollSound;

		item->MyMenu = this;
		item->setFixedToCamera( FixedToCamera );
		item->Control = getControl();
		Items.Insert( index, item );
	}

	void Menu::InitializeInstanceFields()
	{
		Layer = 0;
		FixedToCamera = true;
		SelectDelay = 11;
		OnA_AutoTimerLength = -1;
		HasSelectedThisStep = false;
		WrapSelect = true;
		MouseOnly = false;
		SlipSelect = false;
		NoneSelected = false;
		AlwaysSelected = false;
		ShowLastActivated = false;
		LastActivatedItem = -1;
		Active = true;
		CheckForOutsideClick = false;
		AffectsOutsideMouse = true;
		outside = false;
		_MyCameraZoom = Vector2::One;
		Show = true;
	}
}
