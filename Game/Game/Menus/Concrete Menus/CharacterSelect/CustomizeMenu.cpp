#include <global_header.h>

#include "Hacks/List.h"
#include <Core\Tools\Set.h>

#include <Game/CloudberryKingdom/CloudberryKingdom.CloudberryKingdomGame.h>

namespace CloudberryKingdom
{

	CustomizeMenu::GoProxy::GoProxy( const boost::shared_ptr<CustomizeMenu> &cm )
	{
		this->cm = cm;
	}

	void CustomizeMenu::GoProxy::Apply( const boost::shared_ptr<MenuItem> &item )
	{
		cm->Go( item );
	}

	CustomizeMenu::CreateColorSelectProxy::CreateColorSelectProxy( const boost::shared_ptr<CustomizeMenu> &cm )
	{
		this->cm = cm;
	}

	void CustomizeMenu::CreateColorSelectProxy::Apply()
	{
		cm->CreateColorSelect();
	}

	void CustomizeMenu::ReleaseBody()
	{
		CkBaseMenu::ReleaseBody();

		MyCharacterSelect.reset();
	}

	//CustomizeMenu::CustomizeMenu( int Control, const boost::shared_ptr<CharacterSelect> &Parent ) : CkBaseMenu( false )
	CustomizeMenu::CustomizeMenu( int Control, const boost::shared_ptr<CharacterSelect> &Parent ) { }
	boost::shared_ptr<CustomizeMenu> CustomizeMenu::CustomizeMenu_Construct( int Control, const boost::shared_ptr<CharacterSelect> &Parent )
	{
		CkBaseMenu::CkBaseMenu_Construct( false );

		this->Tags->Add( Tag_CHAR_SELECT );
		this->setControl( Control );
		this->MyCharacterSelect = Parent;

		Constructor();

		return boost::static_pointer_cast<CustomizeMenu>( shared_from_this() );
	}

	void CustomizeMenu::SetItemProperties( const boost::shared_ptr<MenuItem> &item )
	{
		item->MySelectedText->setScale( FontScale );
	item->MyText->setScale( item->MySelectedText->getScale() );
		item->MySelectedText->MyFloatColor = ( bColor( 50, 220, 50 ) ).ToVector4();

		item->SelectIconOffset = Vector2( 0, -160 );
	}

	void CustomizeMenu::Init()
	{
		CkBaseMenu::Init();

		SlideInLength = 0;
		SlideOutLength = 0;
		CallDelay = 0;
		ReturnToCallerDelay = 0;

		MyPile = boost::make_shared<DrawPile>();
		MyPile->FancyPos->UpdateWithGame = true;

		// Make the menu
		MyMenu = boost::make_shared<Menu>( false );

		MyMenu->OnB = boost::make_shared<MenuReturnToCallerLambdaFunc>( boost::static_pointer_cast<GUI_Panel>( shared_from_this() ) );

		MakeItems();

		EnsureFancy();
		MyMenu->setControl( getControl() );

		CharacterSelect::Shift( boost::static_pointer_cast<GUI_Panel>( shared_from_this() ) );

		SetPos();
	}

	void CustomizeMenu::SetPos()
	{
		boost::shared_ptr<MenuItem> _item;
		_item = MyMenu->FindItemByName( std::wstring( L"Color" ) );
		if ( _item != 0 )
		{
			_item->setSetPos( Vector2( -208.3333f, 5.555542f ) );
			_item->MyText->setScale( 0.5835f );
			_item->MySelectedText->setScale( 0.5835f );
			_item->SelectIconOffset = Vector2( 0, -160 );
		}
		_item = MyMenu->FindItemByName( std::wstring( L"Beard" ) );
		if ( _item != 0 )
		{
			_item->setSetPos( Vector2( -205.5554f, -123.8889f ) );
			_item->MyText->setScale( 0.5835f );
			_item->MySelectedText->setScale( 0.5835f );
			_item->SelectIconOffset = Vector2( 0, -160 );
		}
		_item = MyMenu->FindItemByName( std::wstring( L"Hat" ) );
		if ( _item != 0 )
		{
			_item->setSetPos( Vector2( -141.6667f, -250.5555f ) );
			_item->MyText->setScale( 0.5835f );
			_item->MySelectedText->setScale( 0.5835f );
			_item->SelectIconOffset = Vector2( 0, -160 );
		}
		_item = MyMenu->FindItemByName( std::wstring( L"Cape" ) );
		if ( _item != 0 )
		{
			_item->setSetPos( Vector2( -188.8889f, -377.2222f ) );
			_item->MyText->setScale( 0.5835f );
			_item->MySelectedText->setScale( 0.5835f );
			_item->SelectIconOffset = Vector2( 0, -160 );
		}
		_item = MyMenu->FindItemByName( std::wstring( L"Lining" ) );
		if ( _item != 0 )
		{
			_item->setSetPos( Vector2( -191.6665f, -501.1112f ) );
			_item->MyText->setScale( 0.5835f );
			_item->MySelectedText->setScale( 0.5835f );
			_item->SelectIconOffset = Vector2( 0, -160 );
		}
		_item = MyMenu->FindItemByName( std::wstring( L"Done" ) );
		if ( _item != 0 )
		{
			_item->setSetPos( Vector2( -177.7778f, -672.2223f ) );
			_item->MyText->setScale( 0.5835f );
			_item->MySelectedText->setScale( 0.5835f );
			_item->SelectIconOffset = Vector2( 0, -160 );
		}

		MyMenu->setPos( Vector2( MyMenu->getPos().X, -22.22222f ) );
	}

	void CustomizeMenu::Go( const boost::shared_ptr<MenuItem> &item )
	{
		GUI_Panel::Call( MakeMagic( Waiting, ( getControl(), MyCharacterSelect, true ) ) );
		Hide();
	}

	void CustomizeMenu::AddMenuItem( Localization::Words Word, const std::wstring &Name )
	{
		boost::shared_ptr<MenuItem> item = MakeMagic( MenuItem, ( boost::make_shared<EzText>( Word, ItemFont ) ) );
		item->Name = Name;
		item->setGo( Cast::ToItem( boost::make_shared<CreateColorSelectProxy>( boost::static_pointer_cast<CustomizeMenu>( shared_from_this() ) ) ) );

		AddItem( item );
	}

	void CustomizeMenu::MakeItems()
	{
		ItemPos = Vector2( -200, 100 );
		PosAdd = Vector2( 0, -160 );
		SelectedItemShift = Vector2( 0, 0 );
		FontScale = .5835f;
		ItemFont = Resources::Font_Grobold42;

		AddMenuItem( Localization::Words_COLOR, std::wstring( L"Color" ) );
		AddMenuItem( Localization::Words_BEARD, std::wstring( L"Beard" ) );
		AddMenuItem( Localization::Words_HAT, std::wstring( L"Hat" ) );
		AddMenuItem( Localization::Words_CAPE, std::wstring( L"Cape" ) );
		AddMenuItem( Localization::Words_LINING, std::wstring( L"Lining" ) );

		boost::shared_ptr<MenuItem> back = MakeMagic( MenuItem, ( boost::make_shared<EzText>( Localization::Words_DONE, ItemFont ), std::wstring( L"Done" ) ) );
		AddItem( back );
		back->setGo( boost::make_shared<GoProxy>( boost::static_pointer_cast<CustomizeMenu>( shared_from_this() ) ) );
	}

	void CustomizeMenu::OnAdd()
	{
		CkBaseMenu::OnAdd();
	}

	void CustomizeMenu::MyDraw()
	{
		CkBaseMenu::MyDraw();
	}

	void CustomizeMenu::CreateColorSelect()
	{
		boost::shared_ptr<ListSelectPanel> ClrSelect;

		Vector2 ShiftSelect = Vector2();

		// Make the hat select
		if ( MyMenu->CurIndex == 2 )
		{
			boost::shared_ptr<ListSelectPanel> list = MakeMagic( ListSelectPanel, ( getControl(), Localization::Words_HAT, MyCharacterSelect, MyMenu->CurIndex ) );
			ClrSelect = list;

			for ( std::map<boost::shared_ptr<Hat>, bool >::const_iterator hat = CharacterSelectManager::AvailableHats->dict.begin(); hat != CharacterSelectManager::AvailableHats->dict.end(); ++hat )
			/*for ( Set<boost::shared_ptr<Hat> >::const_iterator hat = CharacterSelectManager::AvailableHats->begin(); hat != CharacterSelectManager::AvailableHats->end(); ++hat )*/
			{
				int hat_index = IndexOf( ColorSchemeManager::HatInfo, hat->first );
				boost::shared_ptr<MenuItem> item = MakeMagic( MenuItem, ( boost::make_shared<EzText>( hat->first->Name, Resources::Font_Grobold42, false, true ) ) );
				item->ScaleText( .375f );
				item->MyObject = boost::static_pointer_cast<Object>( boost::make_shared<WrappedInt>( hat_index ) );

				//list->MyList->AddItem( item, hat_index );
				list->MyList->AddItem( item, item->MyObject );
			}
			ClrSelect->MyPile->setPos( AmountShifted );
		ClrSelect->MyMenu->setPos( ClrSelect->MyPile->getPos() );
		}
		// Make the beard select
		else if ( MyMenu->CurIndex == 1 )
		{
			boost::shared_ptr<ListSelectPanel> list = MakeMagic( ListSelectPanel, ( getControl(), Localization::Words_BEARD, MyCharacterSelect, MyMenu->CurIndex ) );
			ClrSelect = list;

			for ( std::map<boost::shared_ptr<Hat>, bool >::const_iterator beard = CharacterSelectManager::AvailableBeards->dict.begin(); beard != CharacterSelectManager::AvailableBeards->dict.end(); ++beard )
			//for ( CloudberryKingdom::Set<boost::shared_ptr<Hat> >::const_iterator beard = CharacterSelectManager::AvailableBeards->begin(); beard != CharacterSelectManager::AvailableBeards->end(); ++beard )
			{
				int beard_index = IndexOf( ColorSchemeManager::BeardInfo, beard->first );
				boost::shared_ptr<MenuItem> item = MakeMagic( MenuItem, ( boost::make_shared<EzText>( beard->first->Name, Resources::Font_Grobold42, false, true ) ) );
				item->ScaleText( .375f );
				item->MyObject = boost::static_pointer_cast<Object>( boost::make_shared<WrappedInt>( beard_index ) );

				list->MyList->AddItem( item, item->MyObject );
			}
			ClrSelect->MyPile->setPos( AmountShifted );
		ClrSelect->MyMenu->setPos( ClrSelect->MyPile->getPos() );
		}
		// Make the color select
		else
		{
			std::vector<boost::shared_ptr<MenuListItem> > list = MyCharacterSelect->ItemList[ MyMenu->CurIndex ];
			boost::shared_ptr<ListSelectPanel> select = MakeMagic( ListSelectPanel, ( getControl(), Localization::Words_COLOR, MyCharacterSelect, MyMenu->CurIndex ) );
			ClrSelect = select;

			for ( std::vector<boost::shared_ptr<MenuListItem> >::const_iterator item = list.begin(); item != list.end(); ++item )
			{
				boost::shared_ptr<ClrTextFx> data = boost::static_pointer_cast<ClrTextFx>( ( *item )->obj );

				// Check if color is available
				if ( !CloudberryKingdomGame::UnlockAll )
					if ( data->Price > 0 && !PlayerManager::Bought( data ) )
						continue;

				int clr_index = IndexOf( list, *item );
				boost::shared_ptr<MenuItem> _item = MakeMagic( MenuItem, ( boost::make_shared<EzText>( data->Name, Resources::Font_Grobold42, false, true ) ) );
				_item->ScaleText( .375f );
				_item->MyObject = boost::static_pointer_cast<Object>( boost::make_shared<WrappedInt>( clr_index ) );

				select->MyList->AddItem( _item, _item->MyObject );
			}
		}

		// Set the index of the list
		ClrSelect->SetIndexViaAssociated( MyCharacterSelect->ItemIndex[ MyMenu->CurIndex ] );

		GUI_Panel::Call( ClrSelect );
        ClrSelect->MyMenu->setControl( getControl() );
		ClrSelect->setControl( getControl() );
        //CharacterSelect.Shift(ClrSelect);

		Hide();
	}

	void CustomizeMenu::MyPhsxStep()
	{
		CkBaseMenu::MyPhsxStep();

		if ( !Active )
			return;
		MyCharacterSelect->MyState = CharacterSelect::SelectState_SELECTING;
		MyCharacterSelect->MyDoll->ShowBob = true;
		MyCharacterSelect->MyGamerTag->ShowGamerTag = true;
		MyCharacterSelect->MyHeroLevel->ShowHeroLevel = true;
		MyCharacterSelect->getPlayer()->Exists = true;
	}
}
