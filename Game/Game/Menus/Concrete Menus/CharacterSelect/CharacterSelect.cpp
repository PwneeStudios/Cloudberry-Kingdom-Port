#include <global_header.h>






#if ! defined(PC_VERSION) && (defined(XBOX) || defined(XBOX_SIGNIN))

#endif

namespace CloudberryKingdom
{

	CharacterSelect::RandomizeProxy::RandomizeProxy( const std::shared_ptr<CharacterSelect> &cs )
	{
		this->cs = cs;
	}

	void CharacterSelect::RandomizeProxy::Apply()
	{
		cs->Randomize();
	}

	const std::shared_ptr<PlayerData> &CharacterSelect::getPlayer() const
	{
		return PlayerManager::Get( PlayerIndex );
	}

float CharacterSelect::Width = 0;
std::vector<Vector2> CharacterSelect::Centers = 0;

	void CharacterSelect::InitCenters()
	{
		Vector2 Spacing = Vector2( 880, 0 );
		const Vector2 tempVector[] = { -1.5f * Spacing, -.5f * Spacing,.5f * Spacing, 1.5f * Spacing };
		Centers = std::vector<Vector2>( tempVector, tempVector + sizeof( tempVector ) / sizeof( tempVector[ 0 ] ) );
	}

	void CharacterSelect::Shift( const std::shared_ptr<GUI_Panel> &panel )
	{
		panel->Shift( Centers[ panel->getControl() ] );
	}

	void CharacterSelect::Release()
	{
		MyGamerTag->Release();
		MyHeroLevel->Release();
		MyDoll->Release();
	}

	CharacterSelect::CharacterSelect( int PlayerIndex, bool QuickJoin )
	{
		InitializeInstanceFields();
		std::shared_ptr<GameData> game = Tools::CurGameData;

		Tools::StartGUIDraw();

		this->PlayerIndex = PlayerIndex;
		this->QuickJoin = QuickJoin;

		InitCenters();
		Center = Centers[ PlayerIndex ];
		NormalZoomCenter = Center;

		MyDoll = std::make_shared<Doll>( PlayerIndex, this );
		MyGamerTag = std::make_shared<GamerTag>( PlayerIndex, this );
		MyHeroLevel = std::make_shared<HeroLevel>( PlayerIndex, this );
		game->AddGameObject( MyDoll );
		game->AddGameObject( MyGamerTag );
		game->AddGameObject( MyHeroLevel );

		InitColorScheme( PlayerIndex );

		game->AddGameObject( std::make_shared<JoinText>( PlayerIndex, this ) );

		/*
		if (QuickJoin)
		{
	#if XBOX || XBOX_SIGNIN
		    if (Player.MyGamer == null)
		        game.AddGameObject(new SignInMenu(this));
		    else
		        game.AddGameObject(new SimpleMenu(PlayerIndex, this));
	#else
		    game.AddGameObject(new SimpleMenu(PlayerIndex, this));
	#endif
		}
		else
		{
	#if PC_VERSION
		    if (PlayerIndex == 0)
		        game.AddGameObject(new SimpleMenu(PlayerIndex, this));
		    else
		        game.AddGameObject(new JoinText(this));
	#else
		    game.AddGameObject(new JoinText(this));
	#endif
		}
		*/
		Tools::EndGUIDraw();
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

			std::vector<MenuListItem*> list = std::vector<MenuListItem*>( ItemList[ i ].capacity() );
//C# TO C++ CONVERTER TODO TASK: There is no equivalent to implicit typing in C++ unless the C++11 inferred typing option is selected:
			for ( std::vector::const_iterator item = ItemList[ i ].begin(); item != ItemList[ i ].end(); ++item )
				if ( PlayerManager::BoughtOrFree( static_cast<Buyable*>( ( *item )->obj ) ) )
					list.push_back( *item );

			ItemIndex[ i ] = ItemList[ i ].find( list.Choose( Tools::GlobalRnd ) );
		}

		std::shared_ptr<Hat> hat = CharacterSelectManager::AvailableHats->Choose( Tools::GlobalRnd );
		std::shared_ptr<Hat> beard = CharacterSelectManager::AvailableBeards->Choose( Tools::GlobalRnd );
		ItemIndex[ 1 ] = ColorSchemeManager::BeardInfo.find( beard );
		ItemIndex[ 2 ] = ColorSchemeManager::HatInfo.find( hat );

		Customize_UpdateColors();

		// Save new custom color scheme
		getPlayer()->CustomColorScheme = getPlayer()->ColorScheme_Renamed;
		getPlayer()->ColorSchemeIndex = -1;
	}

	void CharacterSelect::Customize_UpdateColors()
	{
		bool ShowingCape = getPlayer()->ColorScheme_Renamed->CapeColor->Clr->A > 0 || getPlayer()->ColorScheme_Renamed->CapeOutlineColor->Clr->A > 0;

		getPlayer()->ColorScheme_Renamed->SkinColor = static_cast<ClrTextFx>(ItemList[ 0 ][ ItemIndex[ 0 ] ]->obj);
		getPlayer()->ColorScheme_Renamed->BeardData = ColorSchemeManager::BeardInfo[ ItemIndex[ 1 ] ];
		getPlayer()->ColorScheme_Renamed->HatData = ColorSchemeManager::HatInfo[ ItemIndex[ 2 ] ];
		getPlayer()->ColorScheme_Renamed->CapeColor = static_cast<ClrTextFx>(ItemList[ 3 ][ ItemIndex[ 3 ] ]->obj);
		getPlayer()->ColorScheme_Renamed->CapeOutlineColor = static_cast<ClrTextFx>(ItemList[ 4 ][ ItemIndex[ 4 ] ]->obj);

		// If the cape has gone from not-shown to shown,
		// make sure both the cape color and cape outline color aren't invisible.
		if ( !ShowingCape && ( getPlayer()->ColorScheme_Renamed->CapeColor->Clr->A > 0 || getPlayer()->ColorScheme_Renamed->CapeOutlineColor->Clr->A > 0 ) )
		{
			if ( getPlayer()->ColorScheme_Renamed->CapeColor->Equals(ColorSchemeManager::None) || getPlayer()->ColorScheme_Renamed->CapeColor->Clr->A == 0 )
			{
				ItemIndex[ 3 ] = HoldCapeIndex;
				getPlayer()->ColorScheme_Renamed->CapeColor = static_cast<ClrTextFx>(ItemList[ 3 ][ ItemIndex[ 3 ] ]->obj);
			}
			if ( getPlayer()->ColorScheme_Renamed->CapeOutlineColor->Equals(ColorSchemeManager::None) || getPlayer()->ColorScheme_Renamed->CapeOutlineColor->Clr->A == 0 )
			{
				ItemIndex[ 4 ] = HoldCapeOutlineIndex;
				getPlayer()->ColorScheme_Renamed->CapeOutlineColor = static_cast<ClrTextFx>(ItemList[ 4 ][ ItemIndex[ 4 ] ]->obj);
			}
		}

		// If the outline color is null, set the cape color to null and vis a versa
		if ( getPlayer()->ColorScheme_Renamed->CapeOutlineColor->Equals(ColorSchemeManager::None) && getPlayer()->ColorScheme_Renamed->CapeColor->Clr->A > 0 )
		{
			HoldCapeIndex = ItemIndex[ 3 ];
			ItemIndex[ 3 ] = 0;
			getPlayer()->ColorScheme_Renamed->CapeColor = static_cast<ClrTextFx>(ItemList[ 3 ][ ItemIndex[ 3 ] ]->obj);
		}
		if ( getPlayer()->ColorScheme_Renamed->CapeColor->Equals(ColorSchemeManager::None) && getPlayer()->ColorScheme_Renamed->CapeOutlineColor->Clr->A > 0 )
		{
			HoldCapeOutlineIndex = ItemIndex[ 4 ];
			ItemIndex[ 4 ] = 0;
			getPlayer()->ColorScheme_Renamed->CapeOutlineColor = static_cast<ClrTextFx>(ItemList[ 4 ][ ItemIndex[ 4 ] ]->obj);
		}

		MyDoll->UpdateColorScheme();
	}

	bool CharacterSelect::HasCustom()
	{
		return getPlayer()->CustomColorScheme.SkinColor.Effect != 0;
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
			getPlayer()->ColorSchemeIndex = CoreMath::Restrict(0, ColorSchemeManager::ColorSchemes.size() - 1, getPlayer()->ColorSchemeIndex);

			getPlayer()->ColorScheme_Renamed = ColorSchemeManager::ColorSchemes[ getPlayer()->ColorSchemeIndex ];
			MyDoll->MyDoll->SetColorScheme( getPlayer()->ColorScheme_Renamed );
		}

		// Make sure indices match up to the color scheme.
		CopyIndicesFromColorScheme();
	}

	int CharacterSelect::FindIndex( std::vector<MenuListItem*> &list, ClrTextFx obj )
	{
		int index = 0;
//C# TO C++ CONVERTER TODO TASK: There is no equivalent to implicit typing in C++ unless the C++11 inferred typing option is selected:
		for ( std::vector<MenuListItem*>::const_iterator item = list.begin(); item != list.end(); ++item )
		{
			if ( ( static_cast<ClrTextFx>( ( *item )->obj ) ).Guid == obj.Guid )
				return index;
			index++;
		}
		return 0;
	}

	void CharacterSelect::CopyIndicesFromColorScheme()
	{
		ItemIndex[ 0 ] = FindIndex( ItemList[ 0 ], getPlayer()->ColorScheme_Renamed->SkinColor );
		ItemIndex[ 1 ] = ColorSchemeManager::BeardInfo.find( getPlayer()->ColorScheme_Renamed->BeardData );
		ItemIndex[ 2 ] = ColorSchemeManager::HatInfo.find( getPlayer()->ColorScheme_Renamed->HatData );
		ItemIndex[ 3 ] = FindIndex( ItemList[ 3 ], getPlayer()->ColorScheme_Renamed->CapeColor );
		ItemIndex[ 4 ] = FindIndex( ItemList[ 4 ], getPlayer()->ColorScheme_Renamed->CapeOutlineColor );

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
		MyState = SelectState_BEGINNING;
		Join = false;
		ItemIndex = std::vector<int>( 5 );
		const std::vector<MenuListItem*> tempVector2[] = { ColorSchemeManager::ColorList, ColorSchemeManager::OutlineList, ColorSchemeManager::HatList, ColorSchemeManager::CapeColorList, ColorSchemeManager::CapeOutlineColorList };
		std::vector<std::vector<MenuListItem*> > temp_ItemList = std::vector<std::vector<MenuListItem*> >( tempVector2, tempVector2 + sizeof( tempVector2 ) / sizeof( tempVector2[ 0 ] ) );
		for ( int element = 0; element < sizeof( temp_ItemList ) / sizeof( temp_ItemList[ 0 ] ); element++ )
			ItemList[ element ] = temp_ItemList[ element ];
		HoldCapeIndex = 1;
		HoldCapeOutlineIndex = 1;
	}
}
