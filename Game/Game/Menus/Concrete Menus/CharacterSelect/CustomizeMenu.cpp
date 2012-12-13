#include <global_header.h>

#include "Hacks/List.h"

#include <Game/CloudberryKingdom/CloudberryKingdom.CloudberryKingdomGame.h>

namespace CloudberryKingdom
{

	CustomizeMenu::GoProxy::GoProxy( const std::shared_ptr<CustomizeMenu> &cm )
	{
		this->cm = cm;
	}

	void CustomizeMenu::GoProxy::Apply( const std::shared_ptr<MenuItem> &item )
	{
		cm->Go( item );
	}

	CustomizeMenu::CreateColorSelectProxy::CreateColorSelectProxy( const std::shared_ptr<CustomizeMenu> &cm )
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

	//CustomizeMenu::CustomizeMenu( int Control, const std::shared_ptr<CharacterSelect> &Parent ) : CkBaseMenu( false )
	CustomizeMenu::CustomizeMenu( int Control, const std::shared_ptr<CharacterSelect> &Parent ) { }
	std::shared_ptr<CustomizeMenu> CustomizeMenu::CustomizeMenu_Construct( int Control, const std::shared_ptr<CharacterSelect> &Parent )
	{
		CkBaseMenu::CkBaseMenu_Construct( false );

		this->Tags->Add( Tag_CHAR_SELECT );
		this->setControl( Control );
		this->MyCharacterSelect = Parent;

		Constructor();

		return std::static_pointer_cast<CustomizeMenu>( shared_from_this() );
	}

	void CustomizeMenu::SetItemProperties( const std::shared_ptr<MenuItem> &item )
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

		MyPile = std::make_shared<DrawPile>();
		MyPile->FancyPos->UpdateWithGame = true;

		// Make the menu
		MyMenu = std::make_shared<Menu>( false );

		MyMenu->OnB = std::make_shared<MenuReturnToCallerLambdaFunc>( std::static_pointer_cast<GUI_Panel>( shared_from_this() ) );

		MakeItems();

		EnsureFancy();

		CharacterSelect::Shift( std::static_pointer_cast<GUI_Panel>( shared_from_this() ) );

		SetPos();
	}

	void CustomizeMenu::SetPos()
	{
		std::shared_ptr<MenuItem> _item;
		_item = MyMenu->FindItemByName( _T( "Color" ) );
		if ( _item != 0 )
		{
			_item->setSetPos( Vector2( -208.3333f, 5.555542f ) );
			_item->MyText->setScale( 0.5835f );
			_item->MySelectedText->setScale( 0.5835f );
			_item->SelectIconOffset = Vector2( 0, -160 );
		}
		_item = MyMenu->FindItemByName( _T( "Beard" ) );
		if ( _item != 0 )
		{
			_item->setSetPos( Vector2( -205.5554f, -123.8889f ) );
			_item->MyText->setScale( 0.5835f );
			_item->MySelectedText->setScale( 0.5835f );
			_item->SelectIconOffset = Vector2( 0, -160 );
		}
		_item = MyMenu->FindItemByName( _T( "Hat" ) );
		if ( _item != 0 )
		{
			_item->setSetPos( Vector2( -141.6667f, -250.5555f ) );
			_item->MyText->setScale( 0.5835f );
			_item->MySelectedText->setScale( 0.5835f );
			_item->SelectIconOffset = Vector2( 0, -160 );
		}
		_item = MyMenu->FindItemByName( _T( "Cape" ) );
		if ( _item != 0 )
		{
			_item->setSetPos( Vector2( -188.8889f, -377.2222f ) );
			_item->MyText->setScale( 0.5835f );
			_item->MySelectedText->setScale( 0.5835f );
			_item->SelectIconOffset = Vector2( 0, -160 );
		}
		_item = MyMenu->FindItemByName( _T( "Lining" ) );
		if ( _item != 0 )
		{
			_item->setSetPos( Vector2( -191.6665f, -501.1112f ) );
			_item->MyText->setScale( 0.5835f );
			_item->MySelectedText->setScale( 0.5835f );
			_item->SelectIconOffset = Vector2( 0, -160 );
		}
		_item = MyMenu->FindItemByName( _T( "Done" ) );
		if ( _item != 0 )
		{
			_item->setSetPos( Vector2( -177.7778f, -672.2223f ) );
			_item->MyText->setScale( 0.5835f );
			_item->MySelectedText->setScale( 0.5835f );
			_item->SelectIconOffset = Vector2( 0, -160 );
		}

		MyMenu->setPos( Vector2( -1320, -22.22222f ) );

		MyPile->setPos( Vector2( -1320, 0 ) );
	}

	void CustomizeMenu::Go( const std::shared_ptr<MenuItem> &item )
	{
		GUI_Panel::Call( std::make_shared<Waiting>( getControl(), MyCharacterSelect ) );
		Hide();
	}

	void CustomizeMenu::AddMenuItem( Localization::Words Word, const std::wstring &Name )
	{
		std::shared_ptr<MenuItem> item = std::make_shared<MenuItem>( std::make_shared<EzText>( Word, ItemFont ) );
		item->Name = Name;
		item->setGo( Cast::ToItem( std::make_shared<CreateColorSelectProxy>( std::static_pointer_cast<CustomizeMenu>( shared_from_this() ) ) ) );

		AddItem( item );
	}

	void CustomizeMenu::MakeItems()
	{
		ItemPos = Vector2( -200, 100 );
		PosAdd = Vector2( 0, -160 );
		SelectedItemShift = Vector2( 0, 0 );
		FontScale = .5835f;
		ItemFont = Resources::Font_Grobold42;

		AddMenuItem( Localization::Words_COLOR, _T( "Color" ) );
		AddMenuItem( Localization::Words_BEARD, _T( "Beard" ) );
		AddMenuItem( Localization::Words_HAT, _T( "Hat" ) );
		AddMenuItem( Localization::Words_CAPE, _T( "Cape" ) );
		AddMenuItem( Localization::Words_LINING, _T( "Lining" ) );

		std::shared_ptr<MenuItem> back = std::make_shared<MenuItem>( std::make_shared<EzText>( Localization::Words_DONE, ItemFont ), _T( "Done" ) );
		AddItem( back );
		back->setGo( std::make_shared<GoProxy>( std::static_pointer_cast<CustomizeMenu>( shared_from_this() ) ) );
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
		std::shared_ptr<ListSelectPanel> ClrSelect;

		Vector2 ShiftSelect = Vector2();

		// Make the hat select
		if ( MyMenu->CurIndex == 2 )
		{
			std::shared_ptr<ListSelectPanel> list = std::make_shared<ListSelectPanel>( getControl(), Localization::Words_HAT, MyCharacterSelect, MyMenu->CurIndex );
			ClrSelect = list;

			for ( std::map<std::shared_ptr<Hat>, bool >::const_iterator hat = CharacterSelectManager::AvailableHats->dict.begin(); hat != CharacterSelectManager::AvailableHats->dict.end(); ++hat )
			/*for ( Set<std::shared_ptr<Hat> >::const_iterator hat = CharacterSelectManager::AvailableHats->begin(); hat != CharacterSelectManager::AvailableHats->end(); ++hat )*/
			{
				int hat_index = IndexOf( ColorSchemeManager::HatInfo, hat->first );
				std::shared_ptr<MenuItem> item = std::make_shared<MenuItem>( std::make_shared<EzText>( hat->first->Name, Resources::Font_Grobold42, false, true ) );
				item->ScaleText( .375f );
				item->MyObject = std::static_pointer_cast<Object>( std::make_shared<WrappedInt>( hat_index ) );

				//list->MyList->AddItem( item, hat_index );
				list->MyList->AddItem( item, item->MyObject );
			}
			ClrSelect->MyPile->setPos( AmountShifted );
		ClrSelect->MyMenu->setPos( ClrSelect->MyPile->getPos() );
		}
		// Make the beard select
		else if ( MyMenu->CurIndex == 1 )
		{
			std::shared_ptr<ListSelectPanel> list = std::make_shared<ListSelectPanel>( getControl(), Localization::Words_BEARD, MyCharacterSelect, MyMenu->CurIndex );
			ClrSelect = list;

			for ( std::map<std::shared_ptr<Hat>, bool >::const_iterator beard = CharacterSelectManager::AvailableBeards->dict.begin(); beard != CharacterSelectManager::AvailableBeards->dict.end(); ++beard )
			//for ( CloudberryKingdom::Set<std::shared_ptr<Hat> >::const_iterator beard = CharacterSelectManager::AvailableBeards->begin(); beard != CharacterSelectManager::AvailableBeards->end(); ++beard )
			{
				int beard_index = IndexOf( ColorSchemeManager::BeardInfo, beard->first );
				std::shared_ptr<MenuItem> item = std::make_shared<MenuItem>( std::make_shared<EzText>( beard->first->Name, Resources::Font_Grobold42, false, true ) );
				item->ScaleText( .375f );
				item->MyObject = std::static_pointer_cast<Object>( std::make_shared<WrappedInt>( beard_index ) );

				list->MyList->AddItem( item, item->MyObject );
			}
			ClrSelect->MyPile->setPos( AmountShifted );
		ClrSelect->MyMenu->setPos( ClrSelect->MyPile->getPos() );
		}
		// Make the color select
		else
		{
			std::vector<std::shared_ptr<MenuListItem> > list = MyCharacterSelect->ItemList[ MyMenu->CurIndex ];
			std::shared_ptr<ListSelectPanel> select = std::make_shared<ListSelectPanel>( getControl(), Localization::Words_COLOR, MyCharacterSelect, MyMenu->CurIndex );
			ClrSelect = select;

			for ( std::vector<std::shared_ptr<MenuListItem> >::const_iterator item = list.begin(); item != list.end(); ++item )
			{
				std::shared_ptr<ClrTextFx> data = std::static_pointer_cast<ClrTextFx>( ( *item )->obj );

				// Check if color is available
				if ( !CloudberryKingdomGame::UnlockAll )
					if ( data->Price > 0 && !PlayerManager::Bought( data ) )
						continue;

				int clr_index = IndexOf( list, *item );
				std::shared_ptr<MenuItem> _item = std::make_shared<MenuItem>( std::make_shared<EzText>( data->Name, Resources::Font_Grobold42, false, true ) );
				_item->ScaleText( .375f );
				_item->MyObject = std::static_pointer_cast<Object>( std::make_shared<WrappedInt>( clr_index ) );

				select->MyList->AddItem( _item, _item->MyObject );
			}
		}

		// Set the index of the list
		ClrSelect->SetIndexViaAssociated( MyCharacterSelect->ItemIndex[ MyMenu->CurIndex ] );

		GUI_Panel::Call( ClrSelect );
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
