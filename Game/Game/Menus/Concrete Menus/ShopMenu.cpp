#include <global_header.h>

#include <Hacks/List.h>
#include <Hacks/Compare.h>
#include <Hacks/String.h>

namespace CloudberryKingdom
{

	VerifyPurchaseMenu::CoinSoundPlayer::CoinSoundPlayer( float pitch )
	{
		this->pitch = pitch;
		sound = Tools::Sound( std::wstring( L"Coin" ) );
	}

	void VerifyPurchaseMenu::CoinSoundPlayer::Apply()
	{
		sound->Play( 1, pitch, 0 );
	}

	VerifyPurchaseMenu::YesProxy::YesProxy( const boost::shared_ptr<VerifyPurchaseMenu> &vpm )
	{
		this->vpm = vpm;
	}

	void VerifyPurchaseMenu::YesProxy::Apply( const boost::shared_ptr<MenuItem> &item )
	{
		vpm->Yes( item );
	}

	VerifyPurchaseMenu::NoProxy::NoProxy( const boost::shared_ptr<VerifyPurchaseMenu> &vpm )
	{
		this->vpm = vpm;
	}

	void VerifyPurchaseMenu::NoProxy::Apply( const boost::shared_ptr<MenuItem> &item )
	{
		vpm->No( item );
	}

	VerifyPurchaseMenu::VerifyPurchaseMenu( int Control, const boost::shared_ptr<Buyable> &buyable ) :
		VerifyBaseMenu( false ),
		Cost( 0 )
	{
	}
	boost::shared_ptr<VerifyPurchaseMenu> VerifyPurchaseMenu::VerifyPurchaseMenu_Construct( int Control, const boost::shared_ptr<Buyable> &buyable )
	{
		VerifyBaseMenu::VerifyBaseMenu_Construct( false );

		this->buyable = buyable;
		this->Cost = buyable->GetPrice();
		this->setControl( Control );

		Constructor();

		return boost::static_pointer_cast<VerifyPurchaseMenu>( shared_from_this() );
	}

	void VerifyPurchaseMenu::Yes( const boost::shared_ptr<MenuItem> &item )
	{
		boost::shared_ptr<CloudberryKingdom::EzSound> sound = Tools::Sound( std::wstring( L"Coin" ) );
		int wait = 0;
		float pitch = 0;
		for ( int i = 0; i < Cost; i += 150 )
		{
			MyGame->WaitThenDo( wait, boost::make_shared<CoinSoundPlayer>( pitch ) );
			wait += 5;
			pitch += .05f;
		}

		PlayerManager::DeductCost( Cost );
		PlayerManager::GiveBoughtItem( buyable );

		ShopMenu::ActiveShop->UpdateAll();

		ReturnToCaller();
	}

	void VerifyPurchaseMenu::No( const boost::shared_ptr<MenuItem> &item )
	{
		ReturnToCaller();
	}

	void VerifyPurchaseMenu::MakeBackdrop()
	{
		Backdrop = boost::make_shared<QuadClass>( std::wstring( L"score_screen" ), 1500.f, true );
		MyPile->Add( Backdrop );
		MyPile->Add( Backdrop );
		Backdrop->setSize( Vector2( 1246.031f, 691.4683f ) );
		Backdrop->setPos( Vector2( 1086.013f, 352.7779f ) );
		Backdrop->Quad_Renamed.SetColor( bColor( 215, 215, 215, 255 ) );
	}

	void VerifyPurchaseMenu::Init()
	{
		VerifyBaseMenu::Init();

		// Make the menu
		boost::shared_ptr<MenuItem> item;

		// Header
		std::wstring pic = ShopMenu::GetString( buyable );
		/*
		float width = (int)(100f * buyable.HatPicScale.X);
		Vector2 Offset = buyable.HatPicShift * 100;
		string offset = string.Format("{0},{1}", Offset.X, -Offset.Y);
		string pic = "{p" + buyable.GetTexture().Name + "," + width.ToString() + ",?," + offset + "}";
		*/

		std::wstring postfix = std::wstring( L"{pCoinBlue,80,?}x " ) + StringConverterHelper::toString( Cost );
		std::wstring Text = std::wstring( L"Buy  " ) + pic + std::wstring( L"\n    for " ) + postfix + std::wstring( L"?" );
		boost::shared_ptr<EzText> HeaderText = boost::make_shared<EzText>( Text, ItemFont, 1000.f, false, false, .8f );
		HeaderText->setScale( HeaderText->getScale() * .85f );
		//SetHeaderProperties(HeaderText);
		MyPile->Add( HeaderText );
		HeaderText->setPos( HeaderPos + Vector2( -200, 200 ) );

		// Yes
		item = MakeMagic( MenuItem, ( boost::make_shared<EzText>( Localization::Words_Yes, ItemFont ) ) );
		item->setGo( boost::make_shared<YesProxy>( boost::static_pointer_cast<VerifyPurchaseMenu>( shared_from_this() ) ) );
		AddItem( item );
		item->SelectSound.reset();

		// No
		item = MakeMagic( MenuItem, ( boost::make_shared<EzText>( Localization::Words_No, ItemFont ) ) );
		item->setGo( boost::make_shared<NoProxy>( boost::static_pointer_cast<VerifyPurchaseMenu>( shared_from_this() ) ) );
		AddItem( item );
		item->SelectSound.reset();

		MyMenu->OnX = MyMenu->OnB = boost::make_shared<MenuReturnToCallerLambdaFunc>( boost::static_pointer_cast<GUI_Panel>( shared_from_this() ) );

		// Select the first item in the menu to start
		MyMenu->SelectItem( 0 );
	}

	ShopMenu::VerifyPurchaseProxy::VerifyPurchaseProxy( const boost::shared_ptr<ShopMenu> &sm )
	{
		this->sm = sm;
	}

	void ShopMenu::VerifyPurchaseProxy::Apply( const boost::shared_ptr<MenuItem> &item )
	{
		sm->VerifyPurchase( item );
	}

	ShopMenu::OnAddHelper::OnAddHelper( const boost::shared_ptr<ScrollBar> &bar )
	{
		this->bar = bar;
	}

	bool ShopMenu::OnAddHelper::Apply()
	{
#if defined(WINDOWS) && !defined(NOT_PC)
		return bar->MyMenu->HitTest();
#else
		return false;
#endif
	}

boost::shared_ptr<ShopMenu> ShopMenu::ActiveShop = 0;

	void ShopMenu::ReleaseBody()
	{
		CkBaseMenu::ReleaseBody();

		ActiveShop.reset();
		SaveGroup::SaveAll();
	}

	void ShopMenu::VerifyPurchase( const boost::shared_ptr<MenuItem> &item )
	{
		boost::shared_ptr<Buyable> buyable = boost::dynamic_pointer_cast<Buyable>( item->MyObject );
		int Price = buyable->GetPrice();
		if ( PlayerManager::CombinedBank() >= Price )
			Call( MakeMagic( VerifyPurchaseMenu, ( -1, buyable ) ), 6 );
		else
			Tools::Sound( std::wstring( L"Menu_Tick" ) )->Play();
	}

	void ShopMenu::SetItemProperties( const boost::shared_ptr<MenuItem> &item )
	{
		CkBaseMenu::SetItemProperties( item );

		item->MyText->Shadow = item->MySelectedText->Shadow = false;
	}

	void ShopMenu::SetHeaderProperties2( const boost::shared_ptr<EzText> &text )
	{
		CkBaseMenu::SetHeaderProperties( text );
		text->Shadow = false;
		text->MyFloatColor = ColorHelper::Gray( .923f );
	}

	void ShopMenu::Init()
	{
		CkBaseMenu::Init();

		CategoryDelays();
	}

	void ShopMenu::SetBankAmount()
	{
		int coins = PlayerManager::CombinedBank();
		BankAmount->SubstituteText( StringConverterHelper::toString( coins ) );
	}

	void ShopMenu::UpdateAll()
	{
		SetItem( MyMenu->getCurItem() );
		SetBankAmount();
	}

	std::wstring ShopMenu::ClrString( boost::shared_ptr<ClrTextFx> data )
	{
		boost::shared_ptr<EzTexture> texture;
		int width = 100, height = 96;

		Vector2 Offset = Vector2();
		std::wstring offset = Format( _T( "%f,%f" ), Offset.X, -Offset.Y );

		std::wstring pic;
		if ( data->PicTexture != 0 )
		{
			texture = data->PicTexture;
		}
		else
		{
			texture = data->Texture;
			offset += std::wstring( L",1" ); // Use paint effect
		}

		pic = std::wstring( L"{p" ) + texture->Name + std::wstring( L"," ) + StringConverterHelper::toString( width ) + std::wstring( L"," ) + StringConverterHelper::toString( height ) + std::wstring( L"," ) + offset + std::wstring( L"}" );

		return pic;
	}

	void ShopMenu::SetItem( const boost::shared_ptr<MenuItem> &item )
	{
		boost::shared_ptr<Buyable> buyable = boost::dynamic_pointer_cast<Buyable>( item->MyObject );

		bool Sold = PlayerManager::Bought( buyable );



		std::wstring pic, postfix;

		pic = GetString( item );

		if ( Sold )
			postfix = std::wstring( L"  {c255,100,100,255}Sold!" );
		else
			postfix = Format( _T( "  {pCoinBlue,80,?}x %d" ), buyable->GetPrice() );

		// Replace text and reset item properties
		boost::shared_ptr<EzText> Text = boost::make_shared<EzText>( pic + postfix, ItemFont );
		boost::shared_ptr<EzText> SelectedText = boost::make_shared<EzText>( pic + postfix, ItemFont );
		item->MyText->Release();
		item->MySelectedText->Release();
		item->MyText = Text;
		item->MySelectedText = SelectedText;
		SetItemProperties( item );

		// Action
		if ( Sold )
			item->_Go.reset();
		else
		{
			item->setGo( boost::make_shared<VerifyPurchaseProxy>( boost::static_pointer_cast<ShopMenu>( shared_from_this() ) ) );
			item->MySelectedText->MyFloatColor = ( bColor( 50, 220, 50 ) ).ToVector4();
		}
	}

	std::wstring ShopMenu::GetString( const boost::shared_ptr<MenuItem> &item )
	{
		boost::shared_ptr<Buyable> buyable = boost::dynamic_pointer_cast<Buyable>( item->MyObject );
		return GetString( buyable );
	}

	std::wstring ShopMenu::GetString( const boost::shared_ptr<Buyable> &buyable )
	{
		std::wstring pic;
		boost::shared_ptr<Hat> hat = boost::dynamic_pointer_cast<Hat>( buyable );
		if ( 0 != hat )
		{
			float width;
			Vector2 Offset;
			std::wstring offset;

			width = static_cast<float>( static_cast<int>( 100 * hat->HatPicScale.X ) );
			Offset = hat->HatPicShift * 100;
			offset = Format( _T( "%f,%f" ), Offset.X, -Offset.Y );
			pic = std::wstring( L"{p" ) + hat->GetTexture()->Name + std::wstring( L"," ) + StringConverterHelper::toString(width) + std::wstring( L",?," ) + offset + std::wstring( L"}" );
		}
		else
		{
			boost::shared_ptr<ClrTextFx> clr = boost::static_pointer_cast<ClrTextFx>( buyable );
			pic = ShopMenu::ClrString( clr );
		}
		return pic;
	}

	void ShopMenu::MenuGo_Customize( const boost::shared_ptr<MenuItem> &item )
	{
		SlideInFrom = PresetPos_LEFT;
		Hide( PresetPos_LEFT );
		CharSelect();
	}

	void ShopMenu::CharSelect()
	{
		CharacterSelectManager::Start( boost::static_pointer_cast<GUI_Panel>( shared_from_this() ), false );
	}

	int ShopMenu::HatCompare( const boost::shared_ptr<Hat> &h1, const boost::shared_ptr<Hat> &h2 )
	{
		return Compare( h1->Price, h2->Price );
	}

	ShopMenu::ShopMenu() { }
	boost::shared_ptr<ShopMenu> ShopMenu::ShopMenu_Construct()
	{
		CkBaseMenu::CkBaseMenu_Construct();

		ActiveShop = boost::static_pointer_cast<ShopMenu>( shared_from_this() );

		MyPile = boost::make_shared<DrawPile>();

		// Make the menu
		ItemPos = Vector2( -1305, 620 );
		PosAdd = Vector2( 0, -151 ) * 1.2f * 1.1f;

		MyMenu = boost::make_shared<LongMenu>();
		MyMenu->FixedToCamera = false;
		MyMenu->WrapSelect = false;

		MyMenu->setControl( -1 );

		MyMenu->OnB = boost::make_shared<MenuReturnToCallerLambdaFunc>( boost::static_pointer_cast<GUI_Panel>( shared_from_this() ) );

		// Header
		boost::shared_ptr<MenuItem> Header = MakeMagic( MenuItem, ( boost::make_shared<EzText>( Localization::Words_None, Resources::Font_Grobold42_2 ) ) );
		MyMenu->Add( Header );
		Header->Pos = Vector2( -1608.809f, 951.508f );
		SetHeaderProperties( Header->MyText );
		Header->MyText->setScale( Header->MyText->getScale() * 1.15f );
		Header->Selectable = false;


		MakeBack();
		ItemPos = Vector2( -1305, 620 );

		// Format the list of hats into a menu
		boost::shared_ptr<MenuItem> item;
		std::vector<boost::shared_ptr<Hat> > hats = std::vector<boost::shared_ptr<Hat> >( ColorSchemeManager::HatInfo );
		Sort( hats, HatCompare );

		//foreach (Hat hat in ColorSchemeManager.HatInfo)
		for ( std::vector<boost::shared_ptr<Hat> >::const_iterator hat = hats.begin(); hat != hats.end(); ++hat )
		{
			if ( ( *hat )->AssociatedAward != 0 || ( *hat )->GetTexture() == 0 || ( *hat ).get() == Hat::None.get() )
				continue;

			//item = new MenuItem(new EzText(pic + postfix, ItemFont));
			item = MakeMagic( MenuItem, ( boost::make_shared<EzText>( std::wstring( L"xxx" ), ItemFont ) ) );
			item->MyObject = boost::static_pointer_cast<Object>( *hat );

			AddItem( item );
			SetItem( item );

			ItemPos.Y -= 60;
		}

		// Header
		MakeHeader( Header, std::wstring( L"Skins" ) );

		for ( std::vector<boost::shared_ptr<MenuListItem> >::const_iterator clr_item = ColorSchemeManager::ColorList.begin(); clr_item != ColorSchemeManager::ColorList.end(); ++clr_item )
		{
			boost::shared_ptr<ClrTextFx> clr = boost::static_pointer_cast<ClrTextFx>( ( *clr_item )->obj );

			if ( clr->Price <= 0 )
				continue;

			item = MakeMagic( MenuItem, ( boost::make_shared<EzText>( std::wstring( L"xxx" ), ItemFont ) ) );
			item->MyObject = boost::static_pointer_cast<Object>( clr );

			AddItem( item );
			SetItem( item );

			// Space before header
			ItemPos.Y -= 60;
		}


		// Header
		MakeHeader( Header, std::wstring( L"Capes" ) );

		for ( std::vector<boost::shared_ptr<MenuListItem> >::const_iterator clr_item = ColorSchemeManager::CapeColorList.begin(); clr_item != ColorSchemeManager::CapeColorList.end(); ++clr_item )
		{
			boost::shared_ptr<ClrTextFx> clr = boost::static_pointer_cast<ClrTextFx>( ( *clr_item )->obj );

			bool found = false;
			for ( std::vector<boost::shared_ptr<MenuListItem> >::iterator match = ColorSchemeManager::ColorList.begin(); match != ColorSchemeManager::ColorList.end(); ++match )
			{
				if ( clr->Guid == ( boost::static_pointer_cast<Buyable>( ( *match )->obj ) )->GetGuid() )
				{
					found = true;
					break;
				}
			}

			if ( found )
				continue;

			if ( clr->Price <= 0 )
				continue;

			item = MakeMagic( MenuItem, ( boost::make_shared<EzText>( std::wstring( L"xxx" ), ItemFont ) ) );
			item->MyObject = clr;

			AddItem( item );
			SetItem( item );

			// Space before header
			ItemPos.Y -= 60;
		}

		//MakeBack();


		// Select first selectable item
		//MyMenu.SelectItem(1);
		MyMenu->SelectItem( 3 );

		MakeRest();

		return boost::static_pointer_cast<ShopMenu>( shared_from_this() );
	}

	void ShopMenu::MakeHeader( boost::shared_ptr<MenuItem> &Header, const std::wstring &str )
	{
		Header = MakeMagic( MenuItem, ( boost::make_shared<EzText>( str, Resources::Font_Grobold42_2 ) ) );
		MyMenu->Add( Header );
		ItemPos.Y -= 40;
		Header->Pos = ItemPos + Vector2( -130, 40 );
		SetHeaderProperties( Header->MyText );
		Header->MyText->setScale( Header->MyText->getScale() * 1 ); // 1.15f;
		Header->Selectable = false;

		ItemPos.Y -= 213;
	}

	void ShopMenu::MakeRest()
	{
		// Backdrop
		boost::shared_ptr<QuadClass> backdrop;

		//backdrop = new QuadClass("Backplate_1500x900", 1500, true);
		//MyPile.Add(backdrop);
		//backdrop.Pos = new Vector2(3009.921265f, -111.1109f) + new Vector2(-297.6191f, 15.87299f);

		backdrop = boost::make_shared<QuadClass>( std::wstring( L"score_screen" ), 1500.f, true );
		MyPile->Add( backdrop );
		MyPile->Add( backdrop );
		backdrop->setSize( Vector2( 853.1744f, 1973.215f ) );
		backdrop->setPos( Vector2( 869.0458f, -35.71438f ) );

		backdrop = boost::make_shared<QuadClass>( std::wstring( L"score_screen" ), 1500.f, true );
		MyPile->Add( backdrop );
		MyPile->Add( backdrop );
		backdrop->setSize( Vector2( 853.1744f, 1973.215f ) );
		backdrop->setPos( Vector2( -825.3976f, -71.42863f ) );

		boost::shared_ptr<QuadClass> shop = boost::make_shared<QuadClass>( std::wstring( L"menupic_shop" ), 965 * 1.042f * 1.15f, true );
		shop->setPos( Vector2( 800, -200 ) );
		MyPile->Add( shop );

		Bank = boost::make_shared<EzText>( Localization::Words_Bank, Resources::Font_Grobold42 );
		Bank->setScale( Bank->getScale() * 1.1f );
		CkColorHelper::UnpleasantColor( Bank );
		MyPile->Add( Bank );
		Bank->setPos( Vector2( 100, 919.0476f ) );

		BankAmount = boost::make_shared<EzText>( std::wstring( L"xx" ), Resources::Font_Grobold42 );
		BankAmount->setScale( BankAmount->getScale() * .935f );
		MyPile->Add( BankAmount );
		BankAmount->setPos( Vector2( 855.f, 877.5f ) );
		SetBankAmount();

		EnsureFancy();
		MyMenu->setPos( Vector2( 67.45706f, 0 ) );
		MyPile->setPos( Vector2( 83.33417f, 130.9524f ) );

	}

	void ShopMenu::MakeBack()
	{
		boost::shared_ptr<MenuItem> item;

		ItemPos = Vector2( -1257.38f, -5900.f );

	//#if defined(PC_VERSION)
	//            // Customize
	//            ItemPos.Y -= 5;
	//            item = new MenuItem(new EzText(Localization::Words_Customize, ItemFont));
	//            item.Go = MenuGo_Customize;
	//            //AddItem(item);
	//            item.MySelectedText.MyFloatColor = new Color(50, 220, 50).ToVector4();
	//            //item.ScaleText(1.12f);
	//            ItemPos.Y -= 60;

	//            ItemPos = new Vector2(1175.161f, 773.0161f);
	//            item.UnaffectedByScroll = true;
	//            AddItem(item);
	//            item.ScaleText(.5f);
	//#endif

		this->DestinationScale *= 1.05f;

		// Back
		//item = MakeBackButton();
		//item.ScaleText(1.4f);

		ItemPos = Vector2( 1341.829f, 697.1431f );
		item = MakeBackButton();
		item->UnaffectedByScroll = true;
		item->ScaleText( .5f );
	}

	void ShopMenu::OnAdd()
	{
		SlideInFrom = PresetPos_RIGHT;
		SlideOutTo = PresetPos_RIGHT;

		CkBaseMenu::OnAdd();

		// Scroll bar
	#if defined(PC_VERSION)
		{
			boost::shared_ptr<ScrollBar> bar = MakeMagic( ScrollBar, ( boost::static_pointer_cast<LongMenu>( MyMenu ), boost::static_pointer_cast<GUI_Panel>( shared_from_this() ) ) );
			bar->setBarPos( Vector2( -2384.921f, 135 ) );
			MyGame->AddGameObject( bar );
			MyMenu->AdditionalCheckForOutsideClick = boost::make_shared<OnAddHelper>( bar );
		}
	#endif
	}

	void ShopMenu::MyPhsxStep()
	{
		CkBaseMenu::MyPhsxStep();
	}
}
