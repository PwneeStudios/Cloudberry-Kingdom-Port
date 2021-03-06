#include <small_header.h>
#include "Game/Menus/Concrete Menus/Title Screen/StartMenu_MW_Simple.h"

#include "Core/Graphics/Draw/Quads/QuadClass.h"
#include "Game/Localization.h"
#include "Game/CloudberryKingdom/CloudberryKingdom.CloudberryKingdomGame.h"
#include "Game/Player/LeaderboardView.h"
#include "Core/Text/EzText.h"
#include "Core/Tools/ColorHelper.h"
#include "Game/Menus/Menu Components/MenuItem.h"
#include "Game/Menus/Concrete Menus/Title Screen/StartMenu_MW.h"
#include "Game/Menus/Concrete Menus/Title Screen/TitleGame_MW.h"

#include "Game/Games/Meta Games/Challenges/Challenge_Base.h"
#include "Game/Menus/Concrete Menus/Title Screen/Arcade/ArcadeMenu.h"
#include "Game/Menus/Menu.h"
#include "StartMenu_MW_Simple.h"

#include <Game/Player/LeaderboardView.h>
#include <Game/CloudberryKingdom/CloudberryKingdom.CloudberryKingdomGame.h>

namespace CloudberryKingdom
{

	StartMenu_MW_Simple::StartMenu_MW_Simple( boost::shared_ptr<TitleGameData_MW> Title ) : StartMenu_MW( Title )
    {
	}
		
	boost::shared_ptr<StartMenu_MW_Simple> StartMenu_MW_Simple::StartMenu_MW_Simple_Construct( boost::shared_ptr<TitleGameData_MW> Title )
	{
		StartMenu_MW::StartMenu_MW_Construct( Title );
					
		return boost::static_pointer_cast<StartMenu_MW_Simple>( shared_from_this() );
    }

	extern bool IsParentalLevelSatisfied( bool );

    void StartMenu_MW_Simple::MenuGo_Leaderboards( boost::shared_ptr<MenuItem> item )
    {
		if ( CloudberryKingdomGame::OnlineFunctionalityAvailable() )
		{
			if( IsParentalLevelSatisfied( true ) )
			{
				Challenge::LeaderboardIndex = ArcadeMenu::LeaderboardIndex( 0, 0 );
				Call( MakeMagic( LeaderboardGUI, ( Title, MenuItem::ActivatingPlayer ) ), 0 );
			}
			//Call(new LeaderboardGUI(Title, null, MenuItem.ActivatingPlayer), 0);
		}
		else
		{
			//CloudberryKingdomGame::ShowError_MustBeSignedInToLiveForLeaderboard();
			CloudberryKingdomGame::ShowError_MustBeSignedInToLive(Localization::Words_None);
		}
	}

    void StartMenu_MW_Simple::MakeMenu()
    {
        boost::shared_ptr<MenuItem> item;

        // Arcade
        item = MakeMagic( MenuItem, ( boost::make_shared<EzText>( Localization::Words_TheArcade, ItemFont, true ) ) );
        item->Name = L"Arcade";
        item->setGo( boost::make_shared<StartMenuLambda_Arcade>( boost::static_pointer_cast<StartMenu>( shared_from_this() ) ) );
        AddItem( item );

        // Campaign
        item = MakeMagic( MenuItem, ( boost::make_shared<EzText>( Localization::Words_StoryMode, ItemFont, true ) ) );
        item->Name = L"Campaign";
        AddItem( item );
        item->setGo( boost::make_shared<StartMenuLambda_Campaign>( boost::static_pointer_cast<StartMenu>( shared_from_this() ) ) );

        // Free Play
        item = MakeMagic( MenuItem, ( boost::make_shared<EzText>( Localization::Words_FreePlay, ItemFont, true ) ) );
        item->Name = L"Freeplay";
        item->setGo( boost::make_shared<StartMenuLambda_Freeplay>( boost::static_pointer_cast<StartMenu>( shared_from_this() ) ) );
        AddItem( item );

        // Options
        item = MakeMagic( MenuItem, ( boost::make_shared<EzText>( Localization::Words_Options, ItemFont, true ) ) );
        item->Name = L"Options";
        item->setGo( boost::make_shared<StartMenuLambda_Options>( boost::static_pointer_cast<StartMenu>( shared_from_this() ) ) );
        AddItem( item );

if ( CloudberryKingdomGame::MainMenuType == MainMenuTypes_PS3 )
{
		// Leaderboard
		item = MakeMagic( MenuItem, ( boost::make_shared<EzText>( Localization::Words_Leaderboards, ItemFont, true ) ) );
        item->Name = L"Leaderboards";
		item->setGo( boost::make_shared<MenuGo_LeaderboardsProxy>( boost::static_pointer_cast<StartMenu_MW_Simple>( shared_from_this() ) ) );
        AddItem(item);
}

if ( CloudberryKingdomGame::MainMenuType == MainMenuTypes_PC )
{
        // Exit
        item = MakeMagic( MenuItem, ( boost::make_shared<EzText>( Localization::Words_Exit, ItemFont, true ) ) );
        item->Name = L"Exit";
        item->setGo( boost::make_shared<StartMenuLambda_Exit>( boost::static_pointer_cast<StartMenu>( shared_from_this() ) ) );
        AddItem( item );
}

        EnsureFancy();

        this->CallToLeft = true;
    }

	void StartMenu_MW_Simple::SetPos()
    {
		// This is now called in StartMenu_MW::SetPos(). Bad! Move it back here and mark StartMenu_MW::SetPos() as virtual.
		BackBox->setTextureName( L"White" );
		BackBox->Quad_Renamed.SetColor( ColorHelper::Gray(.1f ));
		BackBox->setAlpha( .73f );

if ( CloudberryKingdomGame::MainMenuType == MainMenuTypes_PS3 )
{
		boost::shared_ptr<MenuItem> _item;
		_item = MyMenu->FindItemByName( L"Arcade" ); if (_item != 0 ) { _item->setSetPos( Vector2( 0.f, 365.5279f ) ); _item->MyText->setScale( 0.66f ); _item->MySelectedText->setScale( 0.66f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }
		_item = MyMenu->FindItemByName( L"Campaign" ); if (_item != 0 ) { _item->setSetPos( Vector2(-8.333496f, 165.8613f ) ); _item->MyText->setScale( 0.66f ); _item->MySelectedText->setScale( 0.66f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }
		_item = MyMenu->FindItemByName( L"Freeplay" ); if (_item != 0 ) { _item->setSetPos( Vector2( 0.f, -26.47217f ) ); _item->MyText->setScale( 0.66f ); _item->MySelectedText->setScale( 0.66f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }
		_item = MyMenu->FindItemByName( L"Options" ); if (_item != 0 ) { _item->setSetPos( Vector2( 0.f, -405.25f ) ); _item->MyText->setScale( 0.66f ); _item->MySelectedText->setScale( 0.66f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }
		_item = MyMenu->FindItemByName( L"Leaderboards" ); if (_item != 0 ) { _item->setSetPos( Vector2( 0.f, -216.0278f ) ); _item->MyText->setScale( 0.66f ); _item->MySelectedText->setScale( 0.66f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }

		MyMenu->setPos( Vector2(-80.55566f, -216.6667f ) );

		boost::shared_ptr<QuadClass> _q;
		_q = MyPile->FindQuad( L"Back" ); if (_q != 0 ) { _q->setPos( Vector2(-61.11133f, -336.1111f ) ); _q->setSize( Vector2( 524.4158f, 524.4158f ) ); }

		MyPile->setPos( Vector2(-27.77734f, -33.33337f ) );
}
else if ( CloudberryKingdomGame::MainMenuType == MainMenuTypes_PC )
{
        boost::shared_ptr<MenuItem> _item;
        _item = MyMenu->FindItemByName( L"Arcade" ); if (_item != 0 ) { _item->setSetPos( Vector2( 0.f, 365.5279f ) ); _item->MyText->setScale( 0.66f ); _item->MySelectedText->setScale( 0.66f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }
        _item = MyMenu->FindItemByName( L"Campaign" ); if (_item != 0 ) { _item->setSetPos( Vector2( 0.f, 160.3057f ) ); _item->MyText->setScale( 0.66f ); _item->MySelectedText->setScale( 0.66f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }
        _item = MyMenu->FindItemByName( L"Freeplay" ); if (_item != 0 ) { _item->setSetPos( Vector2( 0.f, -26.47217f ) ); _item->MyText->setScale( 0.66f ); _item->MySelectedText->setScale( 0.66f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }
        _item = MyMenu->FindItemByName( L"Options" ); if (_item != 0 ) { _item->setSetPos( Vector2( 0.f, -216.0278f ) ); _item->MyText->setScale( 0.66f ); _item->MySelectedText->setScale( 0.66f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }
        _item = MyMenu->FindItemByName( L"Exit" ); if (_item != 0 ) { _item->setSetPos( Vector2( 0.f, -419.1389f ) ); _item->MyText->setScale( 0.66f ); _item->MySelectedText->setScale( 0.66f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }

        MyMenu->setPos( Vector2(-80.55566f, -219.4445f ) );

        boost::shared_ptr<QuadClass> _q;
        _q = MyPile->FindQuad( L"Back" ); if (_q != 0 ) { _q->setPos( Vector2(-61.11133f, -336.1111f ) ); _q->setSize( Vector2( 524.4158f, 524.4158f ) ); }

        MyPile->setPos( Vector2(-27.77734f, -33.33337f ) );
}
else if ( CloudberryKingdomGame::MainMenuType == MainMenuTypes_WiiU )
{
		boost::shared_ptr<MenuItem> _item;
		_item = MyMenu->FindItemByName( L"Arcade" ); if (_item != 0 ) { _item->setSetPos( Vector2( 2.777832f, 298.8612f ) ); _item->MyText->setScale( 0.66f ); _item->MySelectedText->setScale( 0.66f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }
		_item = MyMenu->FindItemByName( L"Campaign" ); if (_item != 0 ) { _item->setSetPos( Vector2( 2.777832f, 104.7502f ) ); _item->MyText->setScale( 0.66f ); _item->MySelectedText->setScale( 0.66f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }
		_item = MyMenu->FindItemByName( L"Freeplay" ); if (_item != 0 ) { _item->setSetPos( Vector2( 2.777832f, -90.36105f ) ); _item->MyText->setScale( 0.66f ); _item->MySelectedText->setScale( 0.66f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }
		_item = MyMenu->FindItemByName( L"Options" ); if (_item != 0 ) { _item->setSetPos( Vector2( 2.777832f, -280.4723f ) ); _item->MyText->setScale( 0.66f ); _item->MySelectedText->setScale( 0.66f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }

		MyMenu->setPos( Vector2(-80.55566f, -219.4445f ) );

		boost::shared_ptr<QuadClass> _q;
		_q = MyPile->FindQuad( L"Back" ); if (_q != 0 ) { _q->setPos( Vector2(-50.00031f, -311.1111f ) ); _q->setSize( Vector2( 539.9984f, 460.6643f ) ); }

		MyPile->setPos( Vector2(-27.77734f, -33.33337f ) );
}

		MyMenu->SortByHeight();
    }
}