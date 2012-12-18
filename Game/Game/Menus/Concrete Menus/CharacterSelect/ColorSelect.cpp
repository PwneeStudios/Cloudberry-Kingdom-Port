#include <global_header.h>

#include <MasterHack.h>

namespace CloudberryKingdom
{

	ListSelectPanel::OnSelectProxy::OnSelectProxy( const boost::shared_ptr<ListSelectPanel> &lsp )
	{
		this->lsp = lsp;
	}

	void ListSelectPanel::OnSelectProxy::Apply()
	{
		lsp->OnSelect();
	}

	ListSelectPanel::BackProxy::BackProxy( const boost::shared_ptr<ListSelectPanel> &lsp )
	{
		this->lsp = lsp;
	}

	void ListSelectPanel::BackProxy::Apply()
	{
		lsp->Back();
	}

	ListSelectPanel::SelectProxy::SelectProxy( const boost::shared_ptr<ListSelectPanel> &lsp )
	{
		this->lsp = lsp;
	}

	void ListSelectPanel::SelectProxy::Apply()
	{
		lsp->Select();
	}

	void ListSelectPanel::ReleaseBody()
	{
		CkBaseMenu::ReleaseBody();

		MyCharacterSelect.reset();
	}

	void ListSelectPanel::SetPos( Vector2 pos )
	{
		MyPile->setPos( MyPile->getPos() + pos );
		MyMenu->setPos( MyMenu->getPos() + pos );
	}

	void ListSelectPanel::SetIndexViaAssociated( int index )
	{
		int FindIndex = 0;
		for ( std::vector<boost::shared_ptr<MenuItem> >::const_iterator item = MyList->MyList.begin(); item != MyList->MyList.end(); ++item )
		{
			if ( boost::static_pointer_cast<WrappedInt>( ( *item )->MyObject )->MyInt == index )
				break;
			FindIndex++;
		}
		int CorrespondingIndex = FindIndex;

		if ( CorrespondingIndex < 0 )
			CorrespondingIndex = 0;
		MyList->SetIndex( CorrespondingIndex );
	}

	int ListSelectPanel::GetAssociatedIndex()
	{
		return boost::static_pointer_cast<WrappedInt>( MyList->getCurObj() )->MyInt;
	}

	//ListSelectPanel::ListSelectPanel( int Control, Localization::Words Header, const boost::shared_ptr<CharacterSelect> &Parent, int ClrSelectIndex ) : CkBaseMenu( false )
	ListSelectPanel::ListSelectPanel( int Control, Localization::Words Header, const boost::shared_ptr<CharacterSelect> &Parent, int ClrSelectIndex ) :
			Header( static_cast<Localization::Words>( 0 ) ), HoldIndex( 0 ), ClrSelectIndex( 0 )
	{
	}
	boost::shared_ptr<ListSelectPanel> ListSelectPanel::ListSelectPanel_Construct( int Control, Localization::Words Header, const boost::shared_ptr<CharacterSelect> &Parent, int ClrSelectIndex )
	{
		CkBaseMenu::CkBaseMenu_Construct( false );

		this->MyCharacterSelect = Parent;
		this->ClrSelectIndex = ClrSelectIndex;
		this->setControl( Control );

		this->Header = Header;

		HoldIndex = MyCharacterSelect->ItemIndex[ ClrSelectIndex ];

		Constructor();

		return boost::static_pointer_cast<ListSelectPanel>( shared_from_this() );
	}

	void ListSelectPanel::OnSelect()
	{
		MyCharacterSelect->ItemIndex[ ClrSelectIndex ] = GetAssociatedIndex();
		MyCharacterSelect->Customize_UpdateColors();
	}

	void ListSelectPanel::Constructor()
	{
		CkBaseMenu::Constructor();

		setSlideLength( 0 );
		ReturnToCallerDelay = 0;

		MyPile = boost::make_shared<DrawPile>();
		MyMenu = boost::make_shared<Menu>( false );
		EnsureFancy();

		MyMenu->OnB = Cast::ToMenu( boost::make_shared<BackProxy>( boost::static_pointer_cast<ListSelectPanel>( shared_from_this() ) ) );
		MyMenu->OnA = Cast::ToMenu( boost::make_shared<SelectProxy>( boost::static_pointer_cast<ListSelectPanel>( shared_from_this() ) ) );

		MyList = boost::make_shared<MenuList>();
			MenuList_PostConstruct( MyList );
		MyList->Name = _T( "list" );
		MyList->Center = true;
		MyList->OnIndexSelect = boost::make_shared<OnSelectProxy>( boost::static_pointer_cast<ListSelectPanel>( shared_from_this() ) );
		MyList->setGo( Cast::ToItem( boost::make_shared<SelectProxy>( boost::static_pointer_cast<ListSelectPanel>( shared_from_this() ) ) ) );
		MyMenu->Add( MyList );

		//var Done = new MenuItem(new EzText("Use", ItemFont));
		boost::shared_ptr<MenuItem> Done = boost::make_shared<MenuItem>( boost::make_shared<EzText>( Localization::Words_USE, ItemFont ) );
		Done->Name = _T( "Done" );
		Done->setGo( Cast::ToItem( boost::make_shared<SelectProxy>( boost::static_pointer_cast<ListSelectPanel>( boost::static_pointer_cast<ListSelectPanel>( shared_from_this() ) ) ) ) );
		AddItem( Done );

		//var BackButton = new MenuItem(new EzText("{pBackArrow2,80,?}", ItemFont));
		//var BackButton = new MenuItem(new EzText("Cancel", ItemFont));
		boost::shared_ptr<MenuItem> BackButton = boost::make_shared<MenuItem>( boost::make_shared<EzText>( Localization::Words_CANCEL, ItemFont ) );
		BackButton->Name = _T( "Cancel" );
		BackButton->setGo( Cast::ToItem( boost::make_shared<BackProxy>( boost::static_pointer_cast<ListSelectPanel>( boost::static_pointer_cast<ListSelectPanel>( shared_from_this() ) ) ) ) );
		AddItem( BackButton );

		MyPile->Add( boost::make_shared<EzText>( Header, Resources::Font_Grobold42, true ), _T( "Header" ) );

		CharacterSelect::Shift( boost::static_pointer_cast<GUI_Panel>( shared_from_this() ) );
	}

	void ListSelectPanel::OnAdd()
	{
		 CkBaseMenu::OnAdd();

		boost::shared_ptr<MenuItem> _item;
		_item = MyMenu->FindItemByName( _T( "list" ) );
		if ( _item != 0 )
		{
			_item->setSetPos( Vector2( 83.33337f, 153.1746f ) );
			_item->MyText->setScale( 0.375f );
			_item->MySelectedText->setScale( 0.375f );
			_item->SelectIconOffset = Vector2( 0, 0 );
		}
		_item = MyMenu->FindItemByName( _T( "Done" ) );
		if ( _item != 0 )
		{
			_item->setSetPos( Vector2( -177.4444f, 46.11105f ) );
			_item->MyText->setScale( 0.5535835f );
			_item->MySelectedText->setScale( 0.5535835f );
			_item->SelectIconOffset = Vector2( 0, 0 );
		}
		_item = MyMenu->FindItemByName( _T( "Cancel" ) );
		if ( _item != 0 )
		{
			_item->setSetPos( Vector2( -183.0001f, -79.44217f ) );
			_item->MyText->setScale( 0.5352504f );
			_item->MySelectedText->setScale( 0.5352504f );
			_item->SelectIconOffset = Vector2( 0, 0 );
		}

		MyMenu->setPos( Vector2( -1418.571f, -484.127f ) );

		boost::shared_ptr<EzText> _t;
		_t = MyPile->FindEzText( _T( "Header" ) );
		if ( _t != 0 )
		{
			_t->setPos( Vector2( 87.69827f, 534.1268f ) );
			_t->setScale( 1 );
		}
		MyPile->setPos( Vector2( -1414.604f, -492.0635f ) );
	}

	void ListSelectPanel::Back()
	{
		MyCharacterSelect->ItemIndex[ ClrSelectIndex ] = HoldIndex;
		MyCharacterSelect->Customize_UpdateColors();

		//MyMenu.BackSound.Play();
		ReturnToCaller();
	}

	void ListSelectPanel::Select()
	{
		//MyMenu.SelectSound.Play();

		// Save new custom color scheme
		MyCharacterSelect->getPlayer()->CustomColorScheme = MyCharacterSelect->getPlayer()->ColorScheme_Renamed;
		MyCharacterSelect->getPlayer()->ColorSchemeIndex = -1;

		//MyMenu.SelectSound.Play();
		ReturnToCaller();
	}

	void ListSelectPanel::MyPhsxStep()
	{
		 CkBaseMenu::MyPhsxStep();
	}
}
