#include <small_header.h>
#include "Game/Menus/Concrete Menus/CharacterSelect/CharacterSelect.h"

#include "Core/Tools/CoreMath.h"
#include "Game/Objects/Game Objects/GameObjects/GUI_Panel.h"
#include "Game/Player/Buyable.h"
#include "Game/Player/ClrTextFx.h"
#include "Game/Games/GameType.h"
#include "Game/Menus/Concrete Menus/CharacterSelect/CharSelectManager.h"
#include "Game/Menus/Concrete Menus/CharacterSelect/Doll.h"
#include "Game/Menus/Concrete Menus/CharacterSelect/GamerTag.h"
#include "Game/Menus/Concrete Menus/CharacterSelect/HeroLevel.h"
#include "Game/Menus/Concrete Menus/CharacterSelect/JoinText.h"
#include "Game/Menus/Concrete Menus/CharacterSelect/Waiting.h"
#include "Game/Player/PlayerManager.h"
#include "Game/Player/ColorScheme.h"
#include "Game/Player/ColorSchemeManager.h"
#include "Game/Player/PlayerData.h"
#include "Game/Tools/Tools.h"
#include "Game/Tools/Unset.h"

#include "Game/Objects/Bob/Bob.h"
#include "Core/Tools/Random.h"

#include "Hacks/List.h"
#include <Core\Tools\Set.h>

namespace CloudberryKingdom
{

	void CharacterSelect::InitializeStatics()
	{
		CharacterSelect::Width = 0;
	}
	
	// Statics
	float CharacterSelect::Width;
	std::vector<Vector2> CharacterSelect::Centers;


	CharacterSelect::RandomizeProxy::RandomizeProxy( const boost::shared_ptr<CharacterSelect> &cs )
	{
		this->cs = cs;
	}

	void CharacterSelect::RandomizeProxy::Apply()
	{
		cs->Randomize();
	}

	const boost::shared_ptr<PlayerData> CharacterSelect::getPlayer() const
	{
		return PlayerManager::Get( PlayerIndex );
	}

	void CharacterSelect::InitCenters()
	{
		Vector2 Spacing = Vector2( 880, 0 );
		Vector2 tempVector[] = { -1.5f * Spacing, -.5f * Spacing,.5f * Spacing, 1.5f * Spacing };
		Centers = VecFromArray( tempVector );
	}

	void CharacterSelect::Shift( const boost::shared_ptr<GUI_Panel> &panel )
	{
		panel->Shift( Centers[ panel->getControl() ] );
	}

	void CharacterSelect::Release()
	{
		MyGamerTag->Release();
		MyGamerTag.reset();
		MyHeroLevel->Release();
		MyHeroLevel.reset();
		MyDoll->Release();
		MyDoll.reset();
	}

	CharacterSelect::CharacterSelect( int PlayerIndex, bool QuickJoin )
	{
		InitializeInstanceFields();

		// Rest of constructor is in CharacterSelect_PostConstruct
	}

	void CharacterSelect::InitColorScheme( int PlayerIndex )
	{
		if ( getPlayer()->ColorSchemeIndex == Unset::Int )
			SetIndex( PlayerIndex );
		else
			SetIndex( getPlayer()->ColorSchemeIndex );
	}

	void CharacterSelect::Randomize()
	{
		for ( int i = 0; i < 5; i++ )
		{
			if ( i == 1 || i == 2 )
				continue;

			std::vector<boost::shared_ptr<MenuListItem> > list = std::vector<boost::shared_ptr<MenuListItem> >();
			list.reserve( ItemList[ i ].capacity() );

			for ( std::vector<boost::shared_ptr<MenuListItem> >::const_iterator item = ItemList[ i ].begin(); item != ItemList[ i ].end(); ++item )
				if ( PlayerManager::BoughtOrFree( boost::static_pointer_cast<Buyable>( ( *item )->obj ) ) )
					list.push_back( *item );

			ItemIndex[ i ] = IndexOf( ItemList[ i ], ListExtension::Choose( list, Tools::GlobalRnd ) );
		}

		boost::shared_ptr<Hat> hat = CharacterSelectManager::AvailableHats->Choose( Tools::GlobalRnd );
		boost::shared_ptr<Hat> beard = CharacterSelectManager::AvailableBeards->Choose( Tools::GlobalRnd );
		ItemIndex[ 1 ] = IndexOf( ColorSchemeManager::BeardInfo, beard );
		ItemIndex[ 2 ] = IndexOf( ColorSchemeManager::HatInfo, hat );

		Customize_UpdateColors();

		// Save new custom color scheme
		getPlayer()->CustomColorScheme = getPlayer()->ColorScheme_Renamed;
		getPlayer()->ColorSchemeIndex = -1;
	}

	void CharacterSelect::Customize_UpdateColors()
	{
		bool ShowingCape = getPlayer()->ColorScheme_Renamed.CapeColor->Clr.A > 0 || getPlayer()->ColorScheme_Renamed.CapeOutlineColor->Clr.A > 0;

		getPlayer()->ColorScheme_Renamed.SkinColor = boost::static_pointer_cast<ClrTextFx>(ItemList[ 0 ][ ItemIndex[ 0 ] ]->obj);
		getPlayer()->ColorScheme_Renamed.BeardData = ColorSchemeManager::BeardInfo[ ItemIndex[ 1 ] ];
		getPlayer()->ColorScheme_Renamed.HatData = ColorSchemeManager::HatInfo[ ItemIndex[ 2 ] ];
		getPlayer()->ColorScheme_Renamed.CapeColor = boost::static_pointer_cast<ClrTextFx>(ItemList[ 3 ][ ItemIndex[ 3 ] ]->obj);
		getPlayer()->ColorScheme_Renamed.CapeOutlineColor = boost::static_pointer_cast<ClrTextFx>(ItemList[ 4 ][ ItemIndex[ 4 ] ]->obj);

		// If the cape has gone from not-shown to shown,
		// make sure both the cape color and cape outline color aren't invisible.
		if ( !ShowingCape && ( getPlayer()->ColorScheme_Renamed.CapeColor->Clr.A > 0 || getPlayer()->ColorScheme_Renamed.CapeOutlineColor->Clr.A > 0 ) )
		{
			if ( getPlayer()->ColorScheme_Renamed.CapeColor->Equals(*ColorSchemeManager::None) || getPlayer()->ColorScheme_Renamed.CapeColor->Clr.A == 0 )
			{
				ItemIndex[ 3 ] = HoldCapeIndex;
				getPlayer()->ColorScheme_Renamed.CapeColor = boost::static_pointer_cast<ClrTextFx>(ItemList[ 3 ][ ItemIndex[ 3 ] ]->obj);
			}
			if ( getPlayer()->ColorScheme_Renamed.CapeOutlineColor->Equals(*ColorSchemeManager::None) || getPlayer()->ColorScheme_Renamed.CapeOutlineColor->Clr.A == 0 )
			{
				ItemIndex[ 4 ] = HoldCapeOutlineIndex;
				getPlayer()->ColorScheme_Renamed.CapeOutlineColor = boost::static_pointer_cast<ClrTextFx>(ItemList[ 4 ][ ItemIndex[ 4 ] ]->obj);
			}
		}

		// If the outline color is null, set the cape color to null and vis a versa
		if ( getPlayer()->ColorScheme_Renamed.CapeOutlineColor->Equals(*ColorSchemeManager::None) && getPlayer()->ColorScheme_Renamed.CapeColor->Clr.A > 0 )
		{
			HoldCapeIndex = ItemIndex[ 3 ];
			ItemIndex[ 3 ] = 0;
			getPlayer()->ColorScheme_Renamed.CapeColor = boost::static_pointer_cast<ClrTextFx>(ItemList[ 3 ][ ItemIndex[ 3 ] ]->obj);
		}
		if ( getPlayer()->ColorScheme_Renamed.CapeColor->Equals(*ColorSchemeManager::None) && getPlayer()->ColorScheme_Renamed.CapeOutlineColor->Clr.A > 0 )
		{
			HoldCapeOutlineIndex = ItemIndex[ 4 ];
			ItemIndex[ 4 ] = 0;
			getPlayer()->ColorScheme_Renamed.CapeOutlineColor = boost::static_pointer_cast<ClrTextFx>(ItemList[ 4 ][ ItemIndex[ 4 ] ]->obj);
		}

		MyDoll->UpdateColorScheme();
	}

	bool CharacterSelect::HasCustom()
	{
		return getPlayer()->CustomColorScheme.SkinColor->Effect != 0;
	}

	bool CharacterSelect::AvailableColorScheme( ColorScheme scheme )
	{
		return CharacterSelectManager::AvailableHats->Contains( scheme.HatData ) && CharacterSelectManager::AvailableBeards->Contains( scheme.BeardData ) && PlayerManager::BoughtOrFree( scheme.SkinColor ) && PlayerManager::BoughtOrFree( scheme.CapeColor ) && PlayerManager::BoughtOrFree( scheme.CapeOutlineColor );
	}

	void CharacterSelect::SetIndex( int i )
	{
		getPlayer()->ColorSchemeIndex = i;

		if ( getPlayer()->ColorSchemeIndex == -1 )
		{
			getPlayer()->ColorScheme_Renamed = getPlayer()->CustomColorScheme;
			MyDoll->MyDoll->SetColorScheme( getPlayer()->ColorScheme_Renamed );
		}
		else
		{
			getPlayer()->ColorSchemeIndex = CoreMath::RestrictVal(0, ColorSchemeManager::ColorSchemes.size() - 1, getPlayer()->ColorSchemeIndex);

			getPlayer()->ColorScheme_Renamed = ColorSchemeManager::ColorSchemes[ getPlayer()->ColorSchemeIndex ];
			MyDoll->MyDoll->SetColorScheme( getPlayer()->ColorScheme_Renamed );
		}

		// Make sure indices match up to the color scheme.
		CopyIndicesFromColorScheme();
	}

	int CharacterSelect::FindIndex( std::vector<boost::shared_ptr<MenuListItem> > &list, ClrTextFx obj )
	{
		int index = 0;
//C# TO C++ CONVERTER TODO TASK: There is no equivalent to implicit typing in C++ unless the C++11 inferred typing option is selected:
		for ( std::vector<boost::shared_ptr<MenuListItem> >::const_iterator item = list.begin(); item != list.end(); ++item )
		{
			if ( ( boost::static_pointer_cast<ClrTextFx>( ( *item )->obj ) )->Guid == obj.Guid )
				return index;
			index++;
		}
		return 0;
	}

	void CharacterSelect::CopyIndicesFromColorScheme()
	{
		ItemIndex[ 0 ] = FindIndex( ItemList[ 0 ], *getPlayer()->ColorScheme_Renamed.SkinColor );
		ItemIndex[ 1 ] = IndexOf( ColorSchemeManager::BeardInfo, getPlayer()->ColorScheme_Renamed.BeardData );
		ItemIndex[ 2 ] = IndexOf( ColorSchemeManager::HatInfo, getPlayer()->ColorScheme_Renamed.HatData );
		ItemIndex[ 3 ] = FindIndex( ItemList[ 3 ], *getPlayer()->ColorScheme_Renamed.CapeColor );
		ItemIndex[ 4 ] = FindIndex( ItemList[ 4 ], *getPlayer()->ColorScheme_Renamed.CapeOutlineColor );

		for ( int i = 0; i <= 4; i++ )
			if ( ItemIndex[ i ] < 0 )
				ItemIndex[ i ] = 0;
	}

	void CharacterSelect::PhsxStep()
	{
	}

	void CharacterSelect::Draw()
	{
	}

	void CharacterSelect::InitializeInstanceFields()
	{
		Fake = false;

		MyState = SelectState_BEGINNING;
		Join = false;
		ItemIndex = std::vector<int>( 5 );
		std::vector<boost::shared_ptr<MenuListItem> > tempVector2[] = { ColorSchemeManager::ColorList, ColorSchemeManager::OutlineList, ColorSchemeManager::HatList, ColorSchemeManager::CapeColorList, ColorSchemeManager::CapeOutlineColorList };
		ItemList = VecFromArray( tempVector2 );
		HoldCapeIndex = 1;
		HoldCapeOutlineIndex = 1;
	}
}
