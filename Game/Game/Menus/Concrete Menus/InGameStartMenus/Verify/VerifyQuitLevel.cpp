#include "VerifyQuitLevel.h"
#include "Game/Menus/Menu Components/MenuItem.h"
#include "Game/Games/Meta Games/Challenges/Challenge_Base.h"
#include "Game/Tools/Tools.h"
#include "Game/Localization.h"
#include "Core/Text/EzText.h"
#include "Game/Menus/Concrete Menus/Help/HelpMenu.h"
#include "Game/Menus/Concrete Menus/Title Screen/Freeplay/SavedSeedsGUI.h"
#include "Game/Menus/CkBaseMenu.h"
#include "Game/Menus/Menu.h"
#include "Game/Objects/Game Objects/GameObjects/GUI_Panel.h"
#include "Core/Graphics/Draw/Quads/QuadClass.h"

using namespace Microsoft::Xna::Framework;

namespace CloudberryKingdom
{

	VerifyQuitLevelMenu::VerifyQuitOkLambda::VerifyQuitOkLambda()
	{
	}

	void VerifyQuitLevelMenu::VerifyQuitOkLambda::Apply( const std::shared_ptr<MenuItem> &item )
	{
		Tools::CurrentAftermath = std::make_shared<AftermathData>();
		Tools::CurrentAftermath->Success = false;
		Tools::CurrentAftermath->EarlyExit = true;

		Tools::CurGameData->EndGame->Apply( false );
	}

	VerifyQuitLevelMenu::VerifyQuitLevelMenu( bool CallBaseConstructor ) : VerifyBaseMenu( CallBaseConstructor )
	{
	}

	VerifyQuitLevelMenu::VerifyQuitLevelMenu( int Control ) : VerifyBaseMenu( Control )
	{
	}

	void VerifyQuitLevelMenu::Init()
	{
		VerifyBaseMenu::Init();

		// Make the menu
		std::shared_ptr<MenuItem> item;

		// Header
		std::shared_ptr<EzText> HeaderText = std::make_shared<EzText>( Localization::Words_EXIT_LEVEL_QUESTION, ItemFont );
		SetHeaderProperties( HeaderText );
		HeaderText->Name = _T( "Header" );
		MyPile->Add( HeaderText );

		// Ok
		item = std::make_shared<MenuItem>( std::make_shared<EzText>( Localization::Words_YES, ItemFont ) );
		item->setGo( std::make_shared<VerifyQuitOkLambda>() );
		item->Name = _T( "Yes" );
		AddItem( item );

		// No
		item = std::make_shared<MenuItem>( std::make_shared<EzText>( Localization::Words_NO, ItemFont ) );
		item->setGo( Cast::ToItem( std::make_shared<ReturnToCallerProxy>( this ) ) );
		item->Name = _T( "No" );
		AddItem( item );

		MyMenu->OnX = MyMenu->OnB = std::make_shared<MenuReturnToCallerLambdaFunc>( this );

		// Select the first item in the menu to start
		MyMenu->SelectItem( 0 );

		SetPos();
	}

	void VerifyQuitLevelMenu::SetPos()
	{
		std::shared_ptr<MenuItem> _item;
		_item = MyMenu->FindItemByName( _T( "Yes" ) );
		if ( _item != 0 )
		{
			_item->setSetPos( Vector2( 800, 361 ) );
			_item->MyText->setScale( 0.8f );
			_item->MySelectedText->setScale( 0.8f );
			_item->SelectIconOffset = Vector2( 0, 0 );
		}
		_item = MyMenu->FindItemByName( _T( "No" ) );
		if ( _item != 0 )
		{
			_item->setSetPos( Vector2( 800, 61 ) );
			_item->MyText->setScale( 0.8f );
			_item->MySelectedText->setScale( 0.8f );
			_item->SelectIconOffset = Vector2( 0, 0 );
		}

		MyMenu->setPos( Vector2( -1000.001f, -302.7777f ) );

		std::shared_ptr<EzText> _t;
		_t = MyPile->FindEzText( _T( "Header" ) );
		if ( _t != 0 )
		{
			_t->setPos( Vector2( 597.2208f, 746.8888f ) );
			_t->setScale( 0.96f );
		}

		std::shared_ptr<QuadClass> _q;
		_q = MyPile->FindQuad( _T( "Backdrop" ) );
		if ( _q != 0 )
		{
			_q->setPos( Vector2( 1161.806f, 316.6668f ) );
			_q->setSize( Vector2( 1500, 902.439f ) );
		}

		MyPile->setPos( Vector2( -1125.001f, -319.4444f ) );
	}
}
