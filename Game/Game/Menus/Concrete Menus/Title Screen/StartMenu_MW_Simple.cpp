#include <global_header.h>

#include "StartMenu_MW_Simple.h"

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

        // Exit
        item = MakeMagic( MenuItem, ( boost::make_shared<EzText>( Localization::Words_Exit, ItemFont, true ) ) );
        item->Name = L"Exit";
        item->setGo( boost::make_shared<StartMenuLambda_Exit>( boost::static_pointer_cast<StartMenu>( shared_from_this() ) ) );
        AddItem( item );

        EnsureFancy();

        this->CallToLeft = true;
    }

	void StartMenu_MW_Simple::SetPos()
	{
        BackBox->setTextureName( L"White" );
        BackBox->Quad_Renamed.SetColor( ColorHelper::Gray(.1f ));
        BackBox->setAlpha( .73f );

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

}