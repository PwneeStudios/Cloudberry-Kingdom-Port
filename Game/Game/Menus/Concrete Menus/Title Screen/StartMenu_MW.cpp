#include <small_header.h>
#include "Game/Menus/Concrete Menus/Title Screen/StartMenu_MW.h"

#include "Core/Graphics/Draw/Quads/QuadClass.h"
#include "Game/Localization.h"
#include "Game/CloudberryKingdom/CloudberryKingdom.CloudberryKingdomGame.h"
#include "Core/Text/EzText.h"
#include "Core/Tools/ColorHelper.h"
#include "Game/Objects/Game Objects/GameObjects/GUI_Panel.h"
#include "Game/Menus/Menu Components/MenuItem.h"
#include "Game/Menus/Concrete Menus/Title Screen/StartMenu.h"
#include "Game/Menus/Concrete Menus/Title Screen/StartMenu_MW_Backpanel.h"
#include "Game/Menus/Concrete Menus/Title Screen/StartMenu_MW_CustomLevel.h"
#include "Game/Menus/Concrete Menus/Title Screen/StartMenu_MW_Exit.h"
#include "Game/Menus/Concrete Menus/Title Screen/StartMenu_MW_Options.h"
#include "Game/Menus/Concrete Menus/Title Screen/TitleGame_MW.h"
#include "Game/Menus/Concrete Menus/Title Screen/Arcade/StartMenu_MW_Arcade.h"
#include "Game/Menus/Concrete Menus/Title Screen/Story/StartMenu_MW_Campaign.h"


#include "Game/Menus/Concrete Menus/ShopMenu.h"
#include "Game/Menus/Menu.h"

#include <Game/CloudberryKingdom/CloudberryKingdom.CloudberryKingdomGame.h>

#include "StartMenu_MW.h"
#include "StartMenu_MW_Simple.h"

namespace CloudberryKingdom
{

	void StartMenu_MW::MenuGo_Campaign( const boost::shared_ptr<MenuItem> &item )
	{
		// Upsell
		if ( CloudberryKingdomGame::getIsDemo() )
		{
			Title->BackPanel->SetState( StartMenu_MW_Backpanel::State_SCENE_BLUR_DARK );
			CallingOptionsMenu = true;
			Call( MakeMagic( UpSellMenu, ( Localization::Words_UpSell_Campaign, MenuItem::ActivatingPlayer ) ) );

			return;
		}

		StartMenu::MenuGo_Campaign( item );
	}

	void StartMenu_MW::MenuGo_Options( const boost::shared_ptr<MenuItem> &item )
	{
		Title->BackPanel->SetState( StartMenu_MW_Backpanel::State_SCENE_BLUR_DARK );
		Call( MakeMagic( StartMenu_MW_Options, ( getControl(), true ) ), 0 );
		CallingOptionsMenu = true;
	}

	void StartMenu_MW::Exit()
	{
		SelectSound.reset();
		Title->BackPanel->SetState( StartMenu_MW_Backpanel::State_SCENE_BLUR_DARK );
		Call( MakeMagic( StartMenu_MW_Exit, ( getControl() ) ), 0 );
	}

	void StartMenu_MW::BringNextMenu()
	{
		StartMenu::BringNextMenu();

		GUI_Panel::Hide();
	}

	StartMenu_MW::StartMenu_MW( const boost::shared_ptr<TitleGameData_MW> &Title ) : StartMenu() { }
	boost::shared_ptr<StartMenu_MW> StartMenu_MW::StartMenu_MW_Construct( const boost::shared_ptr<TitleGameData_MW> &Title )
	{
		StartMenu::StartMenu_Construct();

		EnableBounce();
		ReturnToCallerDelay = 0;

		this->Title = Title;
		CallingOptionsMenu = false;

		return boost::static_pointer_cast<StartMenu_MW>( shared_from_this() );
	}

	void StartMenu_MW::SlideIn( int Frames )
	{
		Title->BackPanel->SetState( StartMenu_MW_Backpanel::State_SCENE_TITLE );
		StartMenu::SlideIn( 0 );
	}

	void StartMenu_MW::SlideOut( PresetPos Preset, int Frames )
	{
		StartMenu::SlideOut( Preset, 0 );

		StartMenu::SlideOut( Preset, Frames );
	}

	void StartMenu_MW::BringCampaign()
	{
		StartMenu::BringCampaign();

		GUI_Panel::Call( MakeMagic( StartMenu_MW_Campaign, ( Title ) ) );
	}

	void StartMenu_MW::BringArcade()
	{
		StartMenu::BringArcade();

		GUI_Panel::Call( MakeMagic( StartMenu_MW_Arcade, ( Title ) ) );
	}

	void StartMenu_MW::BringFreeplay()
	{
		StartMenu::BringFreeplay();

		SkipCallSound = true;
		GUI_Panel::Call( MakeMagic( StartMenu_MW_CustomLevel, ( Title ) ) );
	}

	void StartMenu_MW::SetItemProperties( const boost::shared_ptr<MenuItem> &item )
	{
		StartMenu::SetItemProperties( item );

		item->MySelectedText->Shadow = item->MyText->Shadow = false;
	}

	void StartMenu_MW::OnAdd()
	{
		CloudberryKingdomGame::SetPresence( Presence_TitleScreen );

		StartMenu::OnAdd();
	}

	void StartMenu_MW::Call( const boost::shared_ptr<GUI_Panel> &child, int Delay )
	{
		UseBounce = false;
		ReturnToCallerDelay = 0;

		StartMenu::Call( child, Delay );
	}

    void StartMenu_MW::OnReturnTo()
    {
		UseBounce = false;
		ReturnToCallerDelay = 0;

		CloudberryKingdomGame::SetPresence( Presence_TitleScreen );

        if (CallingOptionsMenu)
        {
				MyMenu->ReadyToPlaySound = false;
				if ( CloudberryKingdomGame::MainMenuType == MainMenuTypes_WiiU )
				{
					MyMenu->SelectItem(3);
				}
				else if ( CloudberryKingdomGame::MainMenuType == MainMenuTypes_Xbox )
				{
					MyMenu->SelectItem(3);
				}
				else
				{
					MyMenu->SelectItem(4);
				}
				MyMenu->ReadyToPlaySound = true;

            CallingOptionsMenu = false;
        }

        StartMenu::OnReturnTo();
    }

	void StartMenu_MW::ReturnToCaller()
	{
		if ( NoBack )
			return;

		UseBounce = false;
		ReturnToCallerDelay = 0;

		return StartMenu::ReturnToCaller();
	}

	void StartMenu_MW::Init()
	{
		StartMenu::Init();

		CallDelay = ReturnToCallerDelay = 0;
		MyMenu->OnB = boost::make_shared<MenuReturnToCallerLambdaFunc>( boost::static_pointer_cast<GUI_Panel>( shared_from_this() ) );

		BackBox = boost::make_shared<QuadClass>( std::wstring( L"Title_Strip" ) );
		BackBox->setAlpha( .9f );
		MyPile->Add( BackBox, std::wstring( L"Back" ) );

		SetPos();
	}

	void StartMenu_MW::MakeMenu()
    {
        boost::shared_ptr<MenuItem> item;

        // Arcade
        item = MakeMagic( MenuItem, (boost::make_shared<EzText>(Localization::Words_TheArcade, ItemFont, true ) ) );
        item->Name = L"Arcade";
        item->setGo( boost::make_shared<StartMenuLambda_Arcade>( boost::static_pointer_cast<StartMenu>( shared_from_this() ) ) );
        AddItem(item);

        // Campaign
        item = MakeMagic( MenuItem, (boost::make_shared<EzText>(Localization::Words_StoryMode, ItemFont, true ) ) );
        item->Name = L"Campaign";
        AddItem(item);
        item->setGo( boost::make_shared<StartMenuLambda_Campaign>( boost::static_pointer_cast<StartMenu>( shared_from_this() ) ) );

        // Free Play
        item = MakeMagic( MenuItem, (boost::make_shared<EzText>(Localization::Words_FreePlay, ItemFont, true ) ) );
        item->Name = L"Freeplay";
        item->setGo( boost::make_shared<StartMenuLambda_Freeplay>( boost::static_pointer_cast<StartMenu>( shared_from_this() ) ) );
        AddItem(item);

        // Options
        item = MakeMagic( MenuItem, (boost::make_shared<EzText>(Localization::Words_Options, ItemFont, true ) ) );
        item->Name = L"Options";
        item->setGo( boost::make_shared<StartMenuLambda_Options>( boost::static_pointer_cast<StartMenu>( shared_from_this() ) ) );
        AddItem(item);

        // Exit
        item = MakeMagic( MenuItem, (boost::make_shared<EzText>(Localization::Words_Back, ItemFont, true ) ) );
        item->Name = L"Exit";
        item->setGo( boost::make_shared<ItemReturnToCallerProxy>( boost::static_pointer_cast<GUI_Panel>( shared_from_this() ) ) );
        AddItem(item);

        EnsureFancy();

        this->CallToLeft = true;
    }

	void StartMenu_MW::SetPos()
	{
		// This should be called in StartMenu_MW::SetPos(). Bad! Mark StartMenu_MW::SetPos() as virtual.
		boost::shared_ptr<StartMenu_MW_Simple> simple = boost::dynamic_pointer_cast<StartMenu_MW_Simple>( shared_from_this() );
		if ( simple != 0 )
		{
			simple->SetPos();
			return;
		}


        BackBox->setTextureName( L"White" );
        BackBox->Quad_Renamed.SetColor( ColorHelper::Gray(.1f ));
        BackBox->setAlpha( .73f );

			boost::shared_ptr<MenuItem> _item;
			_item = MyMenu->FindItemByName( L"Arcade" ); if (_item != 0 ) { _item->setSetPos( Vector2( 0.f, 365.5279f ) ); _item->MyText->setScale( 0.6517504f ); _item->MySelectedText->setScale( 0.6517504f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }
			_item = MyMenu->FindItemByName( L"Campaign" ); if (_item != 0 ) { _item->setSetPos( Vector2( 0.f, 174.1946f ) ); _item->MyText->setScale( 0.6517504f ); _item->MySelectedText->setScale( 0.6517504f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }
			_item = MyMenu->FindItemByName( L"Freeplay" ); if (_item != 0 ) { _item->setSetPos( Vector2( 0.f, -17.1387f ) ); _item->MyText->setScale( 0.6517504f ); _item->MySelectedText->setScale( 0.6517504f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }
			_item = MyMenu->FindItemByName( L"Options" ); if (_item != 0 ) { _item->setSetPos( Vector2( 0.f, -208.472f ) ); _item->MyText->setScale( 0.6517504f ); _item->MySelectedText->setScale( 0.6517504f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }
			_item = MyMenu->FindItemByName( L"Exit" ); if (_item != 0 ) { _item->setSetPos( Vector2( 0.f, -399.8053f ) ); _item->MyText->setScale( 0.6517504f ); _item->MySelectedText->setScale( 0.6517504f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }

			MyMenu->setPos( Vector2(-80.55566f, -219.4445f ) );

			boost::shared_ptr<QuadClass> _q;
			_q = MyPile->FindQuad( L"Back" ); if (_q != 0 ) { _q->setPos( Vector2(-61.11133f, -336.1111f ) ); _q->setSize( Vector2( 524.4158f, 524.4158f ) ); }

			MyPile->setPos( Vector2(-27.77734f, -33.33337f ) );
	}
}
