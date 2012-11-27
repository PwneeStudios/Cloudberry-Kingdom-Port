#include <global_header.h>
namespace CloudberryKingdom
{

	std::wstring MenuItem::ToCode( const std::wstring &suffix )
	{
		std::wstring SelectedPosStr = _T( "" );
		if ( SelectedPos != Pos )
		{
			Vector2 spos = SelectedPos;
			if ( spos.Y == Pos.Y )
				spos.Y = -1;

			SelectedPosStr = std::wstring::Format( _T( "_SetSelectedPos({0});" ), Tools::ToCode( spos ) );
		}

		return std::wstring::Format( _T( "_item = {0}FindItemByName(\"{1}\"); if (_item != null) {{ _item.SetPos = {2}; _item.MyText.Scale = {3}f; _item.MySelectedText.Scale = {4}f; _item.SelectIconOffset = {5}; {6} }}" ), suffix, Name, Tools::ToCode( Pos ), MyText->getScale(), MySelectedText->getScale(), Tools::ToCode(SelectIconOffset), SelectedPosStr );
	}

	std::shared_ptr<MenuItem> MenuItem::Clone()
	{
		std::shared_ptr<MenuItem> clone = std::make_shared<MenuItem>( MyText->Clone(), MySelectedText->Clone() );
		if ( Icon != 0 )
		{
			clone->Icon = Icon->Clone();
			clone->Icon->FancyPos->SetCenter( clone->FancyPos );
		}
		return clone;
	}

	void MenuItem::SetSelectedPos( Vector2 selectedpos )
	{
		SelectedPos = selectedpos;

		if ( SelectedPos.Y == -1 )
			SelectedPos.Y = Pos.Y;
	}

	const Vector2 &MenuItem::getSetPos() const
	{
		return Pos;
	}

	void MenuItem::setSetPos( const Vector2 &value )
	{
		Pos = SelectedPos = value;
	}

	void MenuItem::Shift( Vector2 shift )
	{
		Pos += shift;
		SelectedPos += shift;
	}

	void MenuItem::SetIcon( const std::shared_ptr<ObjectIcon> &Icon )
	{
		this->Icon = Icon;
		Icon->FancyPos->SetCenter( FancyPos );
	}

	void MenuItem::SubstituteText( Localization::Words text )
	{
		MyText->SubstituteText( text );
		MySelectedText->SubstituteText( text );
	}

	void MenuItem::SubstituteText( const std::wstring &text )
	{
		MyText->SubstituteText( text );
		MySelectedText->SubstituteText( text );
	}

	void MenuItem::setGo( const std::shared_ptr<Lambda_1<MenuItem*> > &value )
	{
		_Go = value;
		if ( _Go != 0 )
			setOverrideA( true );
	}

	const std::shared_ptr<Lambda_1<MenuItem*> > &MenuItem::getGo() const
	{
		return _Go;
	}

	const bool &MenuItem::getOverrideA() const
	{
		return _OverrideA;
	}

	void MenuItem::setOverrideA( const bool &value )
	{
		_OverrideA = value;
		//if (value && this is MenuSliderBase)
		//    Tools.Write("");
	}

	const std::wstring &MenuItem::getMyString() const
	{
		if ( MyText == 0 )
			return _T( "" );
		else
			return MyText->MyString;
	}

	void MenuItem::Release()
	{
		MyObject.reset();
		MyMenu.reset();

		if ( MyText != 0 )
			MyText->Release();
			MyText.reset();
		if ( MySelectedText != 0 )
			MySelectedText->Release();
			MySelectedText.reset();

		getGo().reset();
	}

	void MenuItem::SetFade( bool Fade )
	{
		if ( FadedOut != Fade )
		{
			if ( Fade )
				FadeOut();
			else
				FadeIn();

			FadedOut = Fade;
		}
	}

	void MenuItem::FadeOut()
	{
		MyText->MyFloatColor.W = .3f;
		MyText->OutlineColor.W = .3f;
	}

	void MenuItem::FadeIn()
	{
		MyText->MyFloatColor.W = 1;
		MyText->OutlineColor.W = 1;
	}

	MenuItem::MenuItem()
	{
		InitializeInstanceFields();
		SetToDefaultColors();

		setOverrideA( false );
	}

	void MenuItem::SetToDefaultColors()
	{
		MySelectedColor = ( Color( 255, 255, 255, 255 ) ).ToVector4();
		MyColor = ( Color( 220, 220, 220, 200 ) ).ToVector4();

		MySelectedFont = Resources::Font_Grobold42;
		MyFont = Resources::Font_Grobold42;
	}

	Vector2 MenuItem::Size()
	{
		return Vector2( Width(), Height() );
	}

	float MenuItem::Height()
	{
		if ( MyText == 0 )
			return 50;
		else
			return MyText->GetWorldHeight();
	}

	float MenuItem::Width()
	{
		if ( MyText == 0 )
			return 50;
		else
			return __max( MyText->GetWorldWidth(), MySelectedText->GetWorldWidth() );
	}

	MenuItem::MenuItem( const std::shared_ptr<EzText> &Text )
	{
		InitializeInstanceFields();
		Init( Text, Text->Clone() );
	}

	MenuItem::MenuItem( const std::shared_ptr<EzText> &Text, const std::wstring &Name )
	{
		InitializeInstanceFields();
		Init( Text, Text->Clone() );
		this->Name = Name;
	}

	MenuItem::MenuItem( const std::shared_ptr<EzText> &Text, const std::shared_ptr<EzText> &SelectedText )
	{
		InitializeInstanceFields();
		Init( Text, SelectedText );
	}

	void MenuItem::ScaleText( float scale )
	{
		MyText->setScale( MyText->getScale() * scale );
		MySelectedText->setScale( MySelectedText->getScale() * scale );
	}

	void MenuItem::Init( const std::shared_ptr<EzText> &Text, const std::shared_ptr<EzText> &SelectedText )
	{
		//MyOscillateParams.Set(2f, 1.03f, .05f);
		MyOscillateParams.Set( 2.05f, 1.0295f,.045f );

		Selectable = true;

		MyText = Text;
		MySelectedText = SelectedText;
	}

	void MenuItem::setFixedToCamera( const bool &value )
	{
		if ( MyText != 0 )
			MyText->FixedToCamera = value;
		if ( MySelectedText != 0 )
			MySelectedText->FixedToCamera = value;
	}

	const bool &MenuItem::getFixedToCamera() const
	{
		if ( MyText != 0 )
			return MyText->FixedToCamera;
		else
			return false;
	}

	void MenuItem::SetTextSelection( bool Selected )
	{
		if ( !Selectable )
			Selected = false;
	}

	void MenuItem::UpdatePos()
	{
		MyText->_Pos = Pos + PosOffset;
		MySelectedText->_Pos = SelectedPos + PosOffset;
	}

	void MenuItem::DrawBackdrop( bool Selected )
	{
		if ( Selected )
		{
			if ( MySelectedText != 0 )
				MySelectedText->_Pos = SelectedPos + PosOffset;
		}
		else
		{
			if ( MyText != 0 )
				MyText->_Pos = Pos + PosOffset;
		}
	}

	const bool &MenuItem::getOnScreen() const
	{
		if ( getFixedToCamera() )
			return true;

		if ( MyText->getPos().Y > Tools::CurLevel->getMainCamera()->TR.Y + 500 )
			return false;
		if ( MyText->getPos().Y < Tools::CurLevel->getMainCamera()->BL.Y - 500 )
			return false;
		return true;
	}

	void MenuItem::DrawText( const std::shared_ptr<Camera> &cam, bool Selected )
	{
		if ( !getOnScreen() )
			return;

		if ( MyMenu->CurDrawLayer != MyDrawLayer || !Show )
			return;

		GrayOut();

	#if defined(PC_VERSION)
		if ( Selected && ( ButtonCheck::MouseInUse || !MyMenu->MouseOnly ) || AlwaysDrawAsSelected && MyOscillateParams.MyType != OscillateParams::Type_OSCILLATE )
	#else
		if ( Selected || AlwaysDrawAsSelected && MyOscillateParams.MyType != OscillateParams::Type_OSCILLATE )
	#endif
		{
			// The selected text of the current menu item may not ever have been drawn,
			// so update its CameraZoom manually
			MySelectedText->setMyCameraZoom( getMyCameraZoom() );

			// Oscillate
			float HoldScale = MySelectedText->getScale();
			Vector2 HoldPos = MySelectedText->getPos();
			Vector2 HoldShadowOffset = MySelectedText->ShadowOffset;
			if ( SelectionOscillate )
			{
				float scale = MyOscillateParams.GetScale();
				Vector2 PosShift = Vector2( .5f * ( scale - 1 ) * MySelectedText->GetWorldWidth(), 0 );
				MySelectedText->setPos( MySelectedText->getPos() - PosShift );
				MySelectedText->setScale( MySelectedText->getScale() * scale );
				MySelectedText->ShadowScale = 1 / ( .9f * ( scale - 1 ) + 1 );
				MySelectedText->ShadowOffset *= 15 * ( scale - 1 ) + 1;
				MySelectedText->ShadowOffset -= .7f * PosShift;
				MySelectedText->ShadowOffset.X = .5f * ( MySelectedText->ShadowOffset.X + HoldShadowOffset.X - PosShift.X );
				//MySelectedText.ShadowOffset.Y *= 6f * (scale - 1) + 1;
			}

			// Draw the selected text
			MySelectedText->Draw( cam, false );

			if ( SelectionOscillate )
			{
				MySelectedText->setScale( HoldScale );
				MySelectedText->setPos( HoldPos );
				MySelectedText->ShadowOffset = HoldShadowOffset;
			}

			PrevSelected = true;
		}
		else
		{
			MyOscillateParams.Reset();

			// Draw the unselected text
			MyText->Draw( cam, false );

			PrevSelected = false;
		}

		DeGrayOut();
	}

	void MenuItem::GrayOut()
	{
		if ( !Selectable && GrayOutOnUnselectable )
			DoGrayOut();
	}

	void MenuItem::DeGrayOut()
	{
		if ( !Selectable && GrayOutOnUnselectable )
			DoDeGrayOut();
	}

	void MenuItem::DoGrayOut()
	{
		MyText->MyFloatColor.W = .5f;
		if ( Icon != 0 && dynamic_cast<PictureIcon*>( Icon ) != 0 )
			( static_cast<PictureIcon*>( Icon ) )->IconQuad->setAlpha( .5f );
	}

	void MenuItem::DoDeGrayOut()
	{
		MyText->MyFloatColor.W = 1;
		if ( Icon != 0 && dynamic_cast<PictureIcon*>( Icon ) != 0 )
			( static_cast<PictureIcon*>( Icon ) )->IconQuad->setAlpha( 1 );
	}

	void MenuItem::setInclude( const bool &value )
	{
		Show = Selectable = value;
	}

	void MenuItem::OnSelect()
	{
		if ( AdditionalOnSelect != 0 )
			AdditionalOnSelect->Apply();

		// Stop jiggling
		if ( JiggleOnGo )
		{
			MyOscillateParams.SetType( OscillateParams::Type_OSCILLATE );
			if ( Icon != 0 )
				Icon->MyOscillateParams.SetType( OscillateParams::Type_OSCILLATE );
		}
	}

	const Vector2 &MenuItem::getMyCameraZoom() const
	{
		return _MyCameraZoom;
	}

	void MenuItem::setMyCameraZoom( const Vector2 &value )
	{
		_MyCameraZoom = value;
	}

	void MenuItem::Draw()
	{
		this->Draw( false, Tools::getCurCamera(), false );
		this->Draw( true, Tools::getCurCamera(), false );
	}

	bool MenuItem::DrawBase( bool Text, const std::shared_ptr<Camera> &cam, bool Selected )
	{
		setMyCameraZoom( cam->getZoom() );

		if ( MyDrawLayer != MyMenu->CurDrawLayer || !Show )
			return true;

		if ( !Selectable )
			Selected = false;

		if ( FancyPos != 0 )
		{
			FancyPos->RelVal = Pos + PosOffset;
			FancyPos->Update();
		}

		// If just selected perfrom the OnSelect callback
		if ( Selected != this->Selected && Selected )
		{
			OnSelect();
		}
		this->Selected = Selected;

		return false;
	}

	void MenuItem::Draw( bool Text, const std::shared_ptr<Camera> &cam, bool Selected )
	{
		if ( DrawBase( Text, cam, Selected ) )
			return;

		GrayOut();

		SetTextSelection( Selected );

		if ( Text )
		{
			if ( Selected || !CustomSelectedPos )
			{
				MyText->_Pos = Pos + PosOffset;
				MySelectedText->_Pos = SelectedPos + PosOffset;
			}
			else
			{
				MyText->_Pos = SelectedPos + PosOffset;
				MySelectedText->_Pos = SelectedPos + PosOffset;
			}

			DrawText( cam, Selected );
		}
		else
		{
			if ( Icon != 0 )
				Icon->Draw( Selected );
		}

		DeGrayOut();
	}

#if defined(WINDOWS)
	bool MenuItem::HitTest()
	{
		return HitTest( Tools::MouseGUIPos( getMyCameraZoom() ) );
	}
#endif

#if defined(WINDOWS)
	bool MenuItem::HitTest( Vector2 pos )
	{
		return HitTest( pos, Vector2() );
	}
#endif

#if defined(WINDOWS)
	bool MenuItem::HitTest( Vector2 pos, Vector2 padding )
	{
		return ColWithIcon && Icon != 0 && Icon->HitTest( pos ) || MyText->HitTest( pos, Padding + padding );
	}
#endif

int MenuItem::ActivatingPlayer = -1;

	std::shared_ptr<PlayerData> MenuItem::GetActivatingPlayerData()
	{
		int p = MenuItem::ActivatingPlayer;
		if ( p < 0 )
			p = PlayerManager::FirstPlayer;
		return PlayerManager::Get( p );
	}

	void MenuItem::PhsxStep( bool Selected )
	{
		// When a select jiggle animation is done, go back to oscillating
		if ( MyOscillateParams.MyType == OscillateParams::Type_JIGGLE && MyOscillateParams.Done )
			MyOscillateParams.SetType( OscillateParams::Type_OSCILLATE );

		FancyPos->RelVal = Pos + PosOffset;
		FancyPos->Update();

		if ( MyMenu != 0 )
		{
			Control = MyMenu->getControl();
			setFixedToCamera( MyMenu->FixedToCamera );
		}

	#if defined(PC_VERSION)
		// Mouse interact
		bool SelectThis = false;
		if ( ButtonCheck::MouseInUse && ( Tools::MouseNotDown() || MyMenu->SlipSelect ) && !MyMenu->HasSelectedThisStep && Selectable )
			if ( HitTest() )
			{
				SelectThis = true;
				MyMenu->HasSelectedThisStep = true;
			}
	#endif

		if ( !Selected )
		{
	#if defined(PC_VERSION)
			// Mouse interact
			if ( SelectThis )
				MyMenu->SelectItem( this );
	#endif
			return;
		}

		bool Activate = false;

		ButtonData data = ButtonCheck::State( ControllerButtons_A, Control );
		if ( data.Pressed )
		{
			ActivatingPlayer = data.PressingPlayer;
			Activate = true;
		}

		// Don't activate the item if it isn't being drawn as selected
		if ( MyMenu->NoneSelected )
			Activate = false;

	#if defined(PC_VERSION)
		// Don't activate the item if the menu is mouse only and the mouse isn't in use
		if ( MyMenu->MouseOnly && !ButtonCheck::MouseInUse )
			Activate = false;

		// Don't activate the itme if the mouse is in use and isn't over the item
		if ( ButtonCheck::MouseInUse && !HitTest() )
			Activate = false;
	#else
		if ( MyMenu->MouseOnly )
			Activate = false;
	#endif

		// Mouse down over the item
	#if defined(PC_VERSION)
		if ( OnClick != 0 && ButtonCheck::MouseInUse && Tools::CurMouseDown() && HitTest() )
			OnClick->Apply( this );
	#endif
		// Go function
		if ( Activate && getGo() != 0 )
		{
			DoActivationAnimation();

			if ( SelectSound != 0 )
				SelectSound->Play();
			getGo()->Apply(this);
			MyMenu->LastActivatedItem = MyMenu->Items.find( this );
			ButtonCheck::PreventInput();
		}
	}

	void MenuItem::DoActivationAnimation()
	{
		if ( JiggleOnGo )
		{
			MyOscillateParams.Reset();
			MyOscillateParams.SetType( OscillateParams::Type_JIGGLE );
			if ( Icon != 0 )
				Icon->MyOscillateParams.SetType( OscillateParams::Type_JIGGLE );
		}
	}

	void MenuItem::InitializeInstanceFields()
	{
		Code = 0;
		Name = _T( "" );
		UnaffectedByScroll = false;
		MyObject = 0;
		MyInt = 0;
		FancyPos = std::make_shared<FancyVector2>();
		SelectionOscillate = true;
		AlwaysDrawAsSelected = false;
		ColWithIcon = true;
		GrayOutOnUnselectable = false;
		Show = true;
		JiggleOnGo = true;
		_MyCameraZoom = Vector2(1);
#if defined(WINDOWS)
		Padding = Vector2( -22, -7 );
#endif
	}
}
