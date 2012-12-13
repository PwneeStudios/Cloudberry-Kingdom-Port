#include <global_header.h>

namespace CloudberryKingdom
{

#if defined(PC_VERSION)
	ControlItem::ControlItem( Localization::Words description, Keys key ) : MenuItem( std::make_shared<EzText>( description, Resources::Font_Grobold42, 2000.f, false, false, .65f ) )
	{
		MyKey = key;
		MyQuad = std::make_shared<QuadClass>( _T( "White" ), 72.f );
		//MyQuad.Quad.SetColor(CustomControlsMenu.SecondaryKeyColor);
		MyQuad->Quad_Renamed.SetColor( bColor( 240, 240, 240 ) );
		SetKey( MyKey );
	}
#endif

#if defined(PC_VERSION)
	void ControlItem::SetKey( Keys key )
	{
		MyKey = key;
		//SetSecondaryKey(key);
		SetQuad();
	}
#endif

#if defined(PC_VERSION)
	void ControlItem::SetQuad()
	{
		MyQuad->setTextureName( ButtonString::KeyToTexture( MyKey ) );
		MyQuad->ScaleYToMatchRatio();
	}
#endif

#if defined(PC_VERSION)
	CustomControlsMenu::ResetProxy::ResetProxy( const std::shared_ptr<CustomControlsMenu> &ccm )
	{
		this->ccm = ccm;
	}
#endif

#if defined(PC_VERSION)
	void CustomControlsMenu::ResetProxy::Apply( const std::shared_ptr<MenuItem> &_item )
	{
		ccm->Reset( _item );
	}
#endif

#if defined(PC_VERSION)
	void CustomControlsMenu::KeyQuickspawn_KeyboardKey::Apply( const Keys &key )
	{
		ButtonCheck::Quickspawn_KeyboardKey->Set( key );
	}
#endif

#if defined(PC_VERSION)
	void CustomControlsMenu::KeyHelp_KeyboardKey::Apply( const Keys &key )
	{
		ButtonCheck::Help_KeyboardKey->Set( key );
	}
#endif

#if defined(PC_VERSION)
	void CustomControlsMenu::KeyLeft_Secondary::Apply( const Keys &key )
	{
		ButtonCheck::Left_Secondary = key;
	}
#endif

#if defined(PC_VERSION)
	void CustomControlsMenu::KeyRight_Secondary::Apply( const Keys &key )
	{
		ButtonCheck::Right_Secondary = key;
	}
#endif

#if defined(PC_VERSION)
	void CustomControlsMenu::KeyUp_Secondary::Apply( const Keys &key )
	{
		ButtonCheck::Up_Secondary = key;
	}
#endif

#if defined(PC_VERSION)
	void CustomControlsMenu::KeyDown_Secondary::Apply( const Keys &key )
	{
		ButtonCheck::Down_Secondary = key;
	}
#endif

#if defined(PC_VERSION)
	void CustomControlsMenu::KeyReplayPrev_Secondary::Apply( const Keys &key )
	{
		ButtonCheck::ReplayPrev_Secondary = key;
	}
#endif

#if defined(PC_VERSION)
	void CustomControlsMenu::KeyReplayNext_Secondary::Apply( const Keys &key )
	{
		ButtonCheck::ReplayNext_Secondary = key;
	}
#endif

#if defined(PC_VERSION)
	void CustomControlsMenu::KeyReplayToggle_Secondary::Apply( const Keys &key )
	{
		ButtonCheck::ReplayToggle_Secondary = key;
	}
#endif

#if defined(PC_VERSION)
	void CustomControlsMenu::KeySlowMoToggle_Secondary::Apply( const Keys &key )
	{
		ButtonCheck::SlowMoToggle_Secondary = key;
	}
#endif

#if defined(PC_VERSION)
	void CustomControlsMenu::ResetQuickspawn_KeyboardKey::Apply( const std::shared_ptr<ControlItem> &_item )
	{
		_item->SetKey( ButtonCheck::Quickspawn_KeyboardKey->KeyboardKey );
	}
#endif

#if defined(PC_VERSION)
	void CustomControlsMenu::ResetHelp_KeyboardKey::Apply( const std::shared_ptr<ControlItem> &_item )
	{
		_item->SetKey( ButtonCheck::Help_KeyboardKey->KeyboardKey );
	}
#endif

#if defined(PC_VERSION)
	void CustomControlsMenu::ResetLeft_Secondary::Apply( const std::shared_ptr<ControlItem> &_item )
	{
		_item->SetKey( ButtonCheck::Left_Secondary );
	}
#endif

#if defined(PC_VERSION)
	void CustomControlsMenu::ResetRight_Secondary::Apply( const std::shared_ptr<ControlItem> &_item )
	{
		_item->SetKey( ButtonCheck::Right_Secondary );
	}
#endif

#if defined(PC_VERSION)
	void CustomControlsMenu::ResetUp_Secondary::Apply( const std::shared_ptr<ControlItem> &_item )
	{
		_item->SetKey( ButtonCheck::Up_Secondary );
	}
#endif

#if defined(PC_VERSION)
	void CustomControlsMenu::ResetDown_Secondary::Apply( const std::shared_ptr<ControlItem> &_item )
	{
		_item->SetKey( ButtonCheck::Down_Secondary );
	}
#endif

#if defined(PC_VERSION)
	void CustomControlsMenu::ResetReplayPrev_Secondary::Apply( const std::shared_ptr<ControlItem> &_item )
	{
		_item->SetKey( ButtonCheck::ReplayPrev_Secondary );
	}
#endif

#if defined(PC_VERSION)
	void CustomControlsMenu::ResetReplayNext_Secondary::Apply( const std::shared_ptr<ControlItem> &_item )
	{
		_item->SetKey( ButtonCheck::ReplayNext_Secondary );
	}
#endif

#if defined(PC_VERSION)
	void CustomControlsMenu::ResetReplayToggle_Secondary::Apply( const std::shared_ptr<ControlItem> &_item )
	{
		_item->SetKey( ButtonCheck::SlowMoToggle_Secondary );
	}
#endif

#if defined(PC_VERSION)
	void CustomControlsMenu::ResetSlowMoToggle_Secondary::Apply( const std::shared_ptr<ControlItem> &_item )
	{
		_item->SetKey( ButtonCheck::SlowMoToggle_Secondary );
	}
#endif

#if defined(PC_VERSION)
	CustomControlsMenu::InitOnButtonHelper::InitOnButtonHelper( const std::shared_ptr<CustomControlsMenu> &ccm )
	{
		this->ccm = ccm;
	}
#endif

#if defined(PC_VERSION)
	bool CustomControlsMenu::InitOnButtonHelper::Apply( const std::shared_ptr<Menu> &_m )
	{
		ccm->Save();
		return ccm->MenuReturnToCaller( _m );
	}
#endif

#if defined(PC_VERSION)
	Color CustomControlsMenu::SecondaryKeyColor = Color::SkyBlue;
#endif

#if defined(PC_VERSION)
	void CustomControlsMenu::ReleaseBody()
	{
		CkBaseMenu::ReleaseBody();
	}
#endif

#if defined(PC_VERSION)
	void CustomControlsMenu::Save()
	{
		// Before we exit make sure secondary keys match up to what the user just specified.
		for ( std::vector<std::shared_ptr<MenuItem> >::const_iterator item = MyMenu->Items.begin(); item != MyMenu->Items.end(); ++item )
		{
			std::shared_ptr<ControlItem> citem = std::dynamic_pointer_cast<ControlItem>( *item );
			if ( 0 != citem )
				citem->SetSecondaryKey->Apply( citem->MyKey );
		}

		PlayerManager::SaveRezAndKeys();
	}
#endif

#if defined(PC_VERSION)
	void CustomControlsMenu::SetTextProperties( const std::shared_ptr<EzText> &text )
	{
		CkBaseMenu::SetTextProperties( text );

		//text.Shadow = false;
	}
#endif

#if defined(PC_VERSION)
	void CustomControlsMenu::SetItemProperties( const std::shared_ptr<MenuItem> &item )
	{
		CkBaseMenu::SetItemProperties( item );

		item->MyText->Shadow = false;
	}
#endif

#if defined(PC_VERSION)
	void CustomControlsMenu::AddItem( const std::shared_ptr<MenuItem> &item )
	{
		CkBaseMenu::AddItem( item );

		// Add the associated quad
		std::shared_ptr<ControlItem> citem = std::dynamic_pointer_cast<ControlItem>( item );
		if ( 0 == citem )
			return;

		MyPile->Add( citem->MyQuad );
		citem->MyQuad->setPos( item->Pos + Vector2( -150, -132 ) );
	}
#endif

#if defined(PC_VERSION)
	CustomControlsMenu::CustomControlsMenu() { }
	std::shared_ptr<CustomControlsMenu> CustomControlsMenu::CustomControlsMenu_Construct()
	{
		CkBaseMenu::CkBaseMenu_Construct();
	}
#endif

#if defined(PC_VERSION)
	void CustomControlsMenu::MakeBackdrop()
	{
		Backdrop = std::make_shared<QuadClass>( _T( "Backplate_1230x740" ), 1500.f, true );
		MyPile->Add( Backdrop );
		Backdrop->setSize( Vector2( 1376.984f, 1077.035f ) );
		Backdrop->setPos( Vector2( -18.6521f, -10.31725f ) );
	}
#endif

#if defined(PC_VERSION)
	void CustomControlsMenu::MakeInstructions()
	{
		//var backdrop = new QuadClass("score_screen", 1500, true);
		//MyPile.Add(backdrop);
		//MyPile.Add(backdrop);
		//backdrop.Size = new Vector2(603.1736f, 429.5635f);
		//backdrop.Pos = new Vector2(1157.441f, 51.19061f);
		//backdrop.Quad.SetColor(new Color(215, 215, 215, 255));

		//var text = new EzText("Press any key to switch control of selected item.", Resources.Font_Grobold42, 700, true, true, .675f);
		//text.Scale *= .68f;
		//text.Pos = new Vector2(1158.73f, 79.36493f);
		//MyPile.Add(text, "instructions");
	}
#endif

#if defined(PC_VERSION)
	void CustomControlsMenu::Reset( const std::shared_ptr<MenuItem> &_item )
	{
		ButtonCheck::Reset();
//C# TO C++ CONVERTER TODO TASK: There is no equivalent to implicit typing in C++ unless the C++11 inferred typing option is selected:
		for ( std::vector<std::shared_ptr<MenuItem> >::const_iterator item = MyMenu->Items.begin(); item != MyMenu->Items.end(); ++item )
		{
			std::shared_ptr<ControlItem> c = std::dynamic_pointer_cast<ControlItem>( *item );
			if ( 0 == c )
				continue;

			c->Reset->Apply( c );
		}
	}
#endif

#if defined(PC_VERSION)
	void CustomControlsMenu::MakeBack()
	{
		std::shared_ptr<MenuItem> item;

		// Customize
		item = std::make_shared<MenuItem>( std::make_shared<EzText>( Localization::Words_RESET, ItemFont ) );
		item->Name = _T( "Reset" );
		item->setGo( std::make_shared<ResetProxy>( std::static_pointer_cast<CustomControlsMenu>( shared_from_this() ) ) );
		item->MySelectedText->MyFloatColor = ( bColor( 50, 220, 50 ) ).ToVector4();

		ItemPos = Vector2( 698.9696f, 892.0638f );
		item->UnaffectedByScroll = true;
		AddItem( item );
		item->ScaleText( .5f );

		// Back
		ItemPos = Vector2( 810.0829f, 752.6987f );
		item = MakeBackButton();
		item->UnaffectedByScroll = true;
		item->ScaleText( .5f );
	}
#endif

#if defined(PC_VERSION)
	void CustomControlsMenu::Init()
	{
		CkBaseMenu::Init();

		setPauseGame( true );

		ReturnToCallerDelay = 10;
		SlideInLength = 26;
		SlideOutLength = 26;

		this->SlideInFrom = PresetPos_RIGHT;
		this->SlideOutTo = PresetPos_RIGHT;

		FontScale = .8f;

		MyPile = std::make_shared<DrawPile>();

		// Make the backdrop
		MakeBackdrop();

		MakeInstructions();

		// Make the menu
		MyMenu = std::make_shared<Menu>( false );
		MyMenu->setControl( getControl() );

		MakeBack();
		ItemSetup();

		std::shared_ptr<ControlItem> item;

		item = std::make_shared<ControlItem>( Localization::Words_QUICK_SPAWN, ButtonCheck::Quickspawn_KeyboardKey->KeyboardKey );
		item->Name = _T( "quickspawn" );
		item->SetSecondaryKey = std::make_shared<KeyQuickspawn_KeyboardKey>();
		item->Reset = std::make_shared<ResetQuickspawn_KeyboardKey>();
		AddItem( item );

		item = std::make_shared<ControlItem>( Localization::Words_POWER_UP_MENU, ButtonCheck::Help_KeyboardKey->KeyboardKey );
		item->Name = _T( "powerup" );
		item->SetSecondaryKey = std::make_shared<KeyHelp_KeyboardKey>();
		item->Reset = std::make_shared<ResetHelp_KeyboardKey>();
		AddItem( item );

		item = std::make_shared<ControlItem>( Localization::Words_LEFT, ButtonCheck::Left_Secondary );
		item->Name = _T( "left" );
		item->SetSecondaryKey = std::make_shared<KeyLeft_Secondary>();
		item->Reset = std::make_shared<ResetLeft_Secondary>();
		AddItem( item );

		item = std::make_shared<ControlItem>( Localization::Words_RIGHT, ButtonCheck::Right_Secondary );
		item->Name = _T( "right" );
		item->SetSecondaryKey = std::make_shared<KeyRight_Secondary>();
		item->Reset = std::make_shared<ResetRight_Secondary>();
		AddItem( item );

		item = std::make_shared<ControlItem>( Localization::Words_UP, ButtonCheck::Up_Secondary );
		item->Name = _T( "up" );
		item->SetSecondaryKey = std::make_shared<KeyUp_Secondary>();
		item->Reset = std::make_shared<ResetUp_Secondary>();
		AddItem( item );

		item = std::make_shared<ControlItem>( Localization::Words_DOWN, ButtonCheck::Down_Secondary );
		item->Name = _T( "down" );
		item->SetSecondaryKey = std::make_shared<KeyDown_Secondary>();
		item->Reset = std::make_shared<ResetDown_Secondary>();
		AddItem( item );

		item = std::make_shared<ControlItem>( Localization::Words_REPLAY_PREV, ButtonCheck::ReplayPrev_Secondary );
		item->Name = _T( "replayprev" );
		item->SetSecondaryKey = std::make_shared<KeyReplayPrev_Secondary>();
		item->Reset = std::make_shared<ResetReplayPrev_Secondary>();
		AddItem( item );

		item = std::make_shared<ControlItem>( Localization::Words_REPLAY_NEXT, ButtonCheck::ReplayNext_Secondary );
		item->Name = _T( "replaynext" );
		item->SetSecondaryKey = std::make_shared<KeyReplayNext_Secondary>();
		item->Reset = std::make_shared<ResetReplayNext_Secondary>();
		AddItem( item );

		item = std::make_shared<ControlItem>( Localization::Words_REPLAY_TOGGLE, ButtonCheck::SlowMoToggle_Secondary );
		item->Name = _T( "replaytoggle" );
		item->SetSecondaryKey = std::make_shared<KeyReplayToggle_Secondary>();
		item->Reset = std::make_shared<ResetSlowMoToggle_Secondary>();
		AddItem( item );

		item = std::make_shared<ControlItem>( Localization::Words_ACTIVATE_SLOW_MO, ButtonCheck::SlowMoToggle_Secondary );
		item->Name = _T( "toggleslowmo" );
		item->SetSecondaryKey = std::make_shared<KeySlowMoToggle_Secondary>();
		item->Reset = std::make_shared<ResetSlowMoToggle_Secondary>();
		AddItem( item );

		ButtonCheck::KillSecondary();
		MyMenu->OnX = MyMenu->OnB = std::make_shared<InitOnButtonHelper>( std::static_pointer_cast<CustomControlsMenu>( shared_from_this() ) );

		// Shift everything
		EnsureFancy();

		MyMenu->SelectItem( 2 );

		SetPos();
	}
#endif

#if defined(PC_VERSION)
	void CustomControlsMenu::SetPos()
	{
		std::shared_ptr<MenuItem> _item;
		_item = MyMenu->FindItemByName( _T( "Reset" ) );
		if ( _item != 0 )
		{
			_item->setSetPos( Vector2( 648.9698f, 861.5082f ) );
			_item->MyText->setScale( 0.4f );
			_item->MySelectedText->setScale( 0.4f );
			_item->SelectIconOffset = Vector2( 0, 0 );
		}
		_item = MyMenu->FindItemByName( _T( "Back" ) );
		if ( _item != 0 )
		{
			_item->setSetPos( Vector2( 676.7499f, 761.0321f ) );
			_item->MyText->setScale( 0.4f );
			_item->MySelectedText->setScale( 0.4f );
			_item->SelectIconOffset = Vector2( 0, 0 );
		}
		_item = MyMenu->FindItemByName( _T( "quickspawn" ) );
		if ( _item != 0 )
		{
			_item->setSetPos( Vector2( -877.7778f, 870.3333f ) );
			_item->MyText->setScale( 0.5840001f );
			_item->MySelectedText->setScale( 0.5840001f );
			_item->SelectIconOffset = Vector2( 0, 0 );
		}
		_item = MyMenu->FindItemByName( _T( "powerup" ) );
		if ( _item != 0 )
		{
			_item->setSetPos( Vector2( -886.1108f, 683.2222f ) );
			_item->MyText->setScale( 0.5840001f );
			_item->MySelectedText->setScale( 0.5840001f );
			_item->SelectIconOffset = Vector2( 0, 0 );
		}
		_item = MyMenu->FindItemByName( _T( "left" ) );
		if ( _item != 0 )
		{
			_item->setSetPos( Vector2( -877.7778f, 498.8889f ) );
			_item->MyText->setScale( 0.5840001f );
			_item->MySelectedText->setScale( 0.5840001f );
			_item->SelectIconOffset = Vector2( 0, 0 );
		}
		_item = MyMenu->FindItemByName( _T( "right" ) );
		if ( _item != 0 )
		{
			_item->setSetPos( Vector2( -874.9998f, 314.5556f ) );
			_item->MyText->setScale( 0.5840001f );
			_item->MySelectedText->setScale( 0.5840001f );
			_item->SelectIconOffset = Vector2( 0, 0 );
		}
		_item = MyMenu->FindItemByName( _T( "up" ) );
		if ( _item != 0 )
		{
			_item->setSetPos( Vector2( -866.6667f, 149.6667f ) );
			_item->MyText->setScale( 0.5840001f );
			_item->MySelectedText->setScale( 0.5840001f );
			_item->SelectIconOffset = Vector2( 0, 0 );
		}
		_item = MyMenu->FindItemByName( _T( "down" ) );
		if ( _item != 0 )
		{
			_item->setSetPos( Vector2( -863.8887f, -34.66666f ) );
			_item->MyText->setScale( 0.5840001f );
			_item->MySelectedText->setScale( 0.5840001f );
			_item->SelectIconOffset = Vector2( 0, 0 );
		}
		_item = MyMenu->FindItemByName( _T( "replayprev" ) );
		if ( _item != 0 )
		{
			_item->setSetPos( Vector2( -861.1111f, -219 ) );
			_item->MyText->setScale( 0.539f );
			_item->MySelectedText->setScale( 0.539f );
			_item->SelectIconOffset = Vector2( 0, 0 );
		}
		_item = MyMenu->FindItemByName( _T( "replaynext" ) );
		if ( _item != 0 )
		{
			_item->setSetPos( Vector2( -858.3333f, -395 ) );
			_item->MyText->setScale( 0.5430002f );
			_item->MySelectedText->setScale( 0.5430002f );
			_item->SelectIconOffset = Vector2( 0, 0 );
		}
		_item = MyMenu->FindItemByName( _T( "replaytoggle" ) );
		if ( _item != 0 )
		{
			_item->setSetPos( Vector2( -847.2224f, -576.5555f ) );
			_item->MyText->setScale( 0.4623334f );
			_item->MySelectedText->setScale( 0.4623334f );
			_item->SelectIconOffset = Vector2( 0, 0 );
		}
		_item = MyMenu->FindItemByName( _T( "toggleslowmo" ) );
		if ( _item != 0 )
		{
			_item->setSetPos( Vector2( -841.6666f, -760.8889f ) );
			_item->MyText->setScale( 0.4046669f );
			_item->MySelectedText->setScale( 0.4046669f );
			_item->SelectIconOffset = Vector2( 0, 0 );
		}

		MyMenu->setPos( Vector2( 0, 0 ) );

		std::shared_ptr<EzText> _t;
		_t = MyPile->FindEzText( _T( "instructions" ) );
		if ( _t != 0 )
		{
			_t->setPos( Vector2( 636.5076f, 215.4761f ) );
			_t->setScale( 0.4948333f );
		}

		MyPile->setPos( Vector2( 0, 0 ) );
	}
#endif

#if defined(PC_VERSION)
	void CustomControlsMenu::ItemSetup()
	{
		ItemPos = Vector2( 0, 700 ) + Vector2( -850, 187 ); //214.2859f);
		PosAdd = Vector2( 0, -176 ); //-165);
		FontScale *= .73f; // .778f;
	}
#endif

#if defined(PC_VERSION)
	void CustomControlsMenu::MyPhsxStep()
	{
		CkBaseMenu::MyPhsxStep();

		if ( !Active || MyMenu == 0 || MyMenu->Released )
			return;

		std::shared_ptr<ControlItem> item = std::dynamic_pointer_cast<ControlItem>( MyMenu->getCurItem() );
		if ( 0 != item )
		{
			for ( std::map<Keys, std::wstring>::const_iterator key = ButtonString::KeyToString.begin(); key != ButtonString::KeyToString.end(); ++key )
				if ( ButtonCheck::State( key->first ).Down )
				{
					//// Make sure there are no double keys
					//foreach (MenuItem other in MyMenu.Items)
					//{
					//    ControlItem citem = other as ControlItem;
					//    if (null != citem && citem.MyKey == key)
					//        citem.SetKey(item.MyKey);
					//}

					item->SetKey( key->first );
				}
		}
	}
#endif
}
