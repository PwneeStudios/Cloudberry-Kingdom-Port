#include <global_header.h>

#include <Hacks/Parse.h>
#include <Hacks/String.h>

namespace CloudberryKingdom
{

	StatsMenu::StringificationWrapper::StringificationWrapper( const std::shared_ptr<LambdaFunc_1<int, int> > &f )
	{
		this->f = f;
	}

	std::wstring StatsMenu::StringificationWrapper::Apply( const int &i )
	{
		return ToString( f->Apply( i ) );
	}

	StatsMenu::StatsLevels::StatsLevels( std::vector<std::shared_ptr<PlayerStats> > Stats )
	{
		this->Stats = Stats;
	}

	int StatsMenu::StatsLevels::Apply( const int &j )
	{
		 return Stats[ j ]->Levels;
	}

	StatsMenu::StatsJumps::StatsJumps( std::vector<std::shared_ptr<PlayerStats> > Stats )
	{
		this->Stats = Stats;
	}

	int StatsMenu::StatsJumps::Apply( const int &j )
	{
		return Stats[ j ]->Jumps;
	}

	StatsMenu::StatsScore::StatsScore( std::vector<std::shared_ptr<PlayerStats> > Stats )
	{
		this->Stats = Stats;
	}

	int StatsMenu::StatsScore::Apply( const int &j )
	{
		return Stats[ j ]->Score;
	}

	StatsMenu::StatsCoins::StatsCoins( std::vector<std::shared_ptr<PlayerStats> > Stats )
	{
		this->Stats = Stats;
	}

	int StatsMenu::StatsCoins::Apply( const int &j )
	{
		return Stats[ j ]->Coins;
	}

	StatsMenu::StatsTotalCoins::StatsTotalCoins( std::vector<std::shared_ptr<PlayerStats> > Stats )
	{
		this->Stats = Stats;
	}

	int StatsMenu::StatsTotalCoins::Apply( const int &j )
	{
		return Stats[ j ]->TotalCoins;
	}

	StatsMenu::StatsCoinPercentGotten::StatsCoinPercentGotten( std::vector<std::shared_ptr<PlayerStats> > Stats )
	{
		this->Stats = Stats;
	}

	std::wstring StatsMenu::StatsCoinPercentGotten::Apply( const int &j )
	{
		return Format( _T( "%d%%" ), Stats[ j ]->getCoinPercentGotten() );
	}

	StatsMenu::StatsBlobs::StatsBlobs( std::vector<std::shared_ptr<PlayerStats> > Stats )
	{
		this->Stats = Stats;
	}

	int StatsMenu::StatsBlobs::Apply( const int &j )
	{
		return Stats[ j ]->Blobs;
	}

	StatsMenu::StatsCheckpoints::StatsCheckpoints( std::vector<std::shared_ptr<PlayerStats> > Stats )
	{
		this->Stats = Stats;
	}

	int StatsMenu::StatsCheckpoints::Apply( const int &j )
	{
		return Stats[ j ]->Checkpoints;
	}

	StatsMenu::StatsLifeExpectancy::StatsLifeExpectancy( std::vector<std::shared_ptr<PlayerStats> > Stats )
	{
		this->Stats = Stats;
	}

	std::wstring StatsMenu::StatsLifeExpectancy::Apply( const int &j )
	{
		return Stats[ j ]->getLifeExpectancy();
	}

	StatsMenu::StatsDeathsBy::StatsDeathsBy( std::vector<std::shared_ptr<PlayerStats> > Stats, int i )
	{
		this->Stats = Stats;
		this->i = i;
	}

	int StatsMenu::StatsDeathsBy::Apply( const int &j )
	{
		return Stats[ j ]->DeathsBy[ i ];
	}

	StatsMenu::OnAddHelper::OnAddHelper( const std::shared_ptr<ScrollBar> &bar )
	{
		this->bar = bar;
	}

	bool StatsMenu::OnAddHelper::Apply()
	{
		return bar->MyMenu->HitTest();
	}

	void StatsMenu::SetItemProperties( const std::shared_ptr<MenuItem> &item )
	{
		CkBaseMenu::SetItemProperties( item );

		item->MyText->Shadow = item->MySelectedText->Shadow = false;
	}

	void StatsMenu::SetHeaderProperties( const std::shared_ptr<EzText> &text )
	{
		text->MyFloatColor = Vector4( .6f,.6f,.6f, 1 );
		text->OutlineColor = Vector4( 0, 0, 0, 1 );

		text->Shadow = false;
		text->ShadowColor = Color( .2f,.2f,.2f, 1 );
		text->ShadowOffset = Vector2( 12, 12 );

		text->setScale( FontScale *.9f );
	}

	const Vector2 tempVector[] = { Vector2( 1431.285f, -158.9048f ) };
	std::vector<Vector2> StatsMenu::x1_name = std::vector<Vector2>( tempVector, tempVector + sizeof( tempVector ) / sizeof( tempVector[ 0 ] ) );
	const Vector2 tempVector2[] = { Vector2( 1217, -147 ), Vector2( 2056, -147 ) };
	std::vector<Vector2> StatsMenu::x2_name = std::vector<Vector2>( tempVector2, tempVector2 + sizeof( tempVector2 ) / sizeof( tempVector2[ 0 ] ) );
	const Vector2 tempVector3[] = { Vector2( 1225, -295 ), Vector2( 1624, -127.3015f ), Vector2( 2116, -295 ) };
	std::vector<Vector2> StatsMenu::x3_name = std::vector<Vector2>( tempVector3, tempVector3 + sizeof( tempVector3 ) / sizeof( tempVector3[ 0 ] ) );
	const Vector2 tempVector4[] = { Vector2( 1090, -295 ), Vector2( 1445, -127.3015f ), Vector2( 1800, -295 ), Vector2( 2155, -127.3015f ) };
	std::vector<Vector2> StatsMenu::x4_name = std::vector<Vector2>( tempVector4, tempVector4 + sizeof( tempVector4 ) / sizeof( tempVector4[ 0 ] ) );
	const float tempVector5[] = { 1920 };
	std::vector<float> StatsMenu::x1 = std::vector<float>( tempVector5, tempVector5 + sizeof( tempVector5 ) / sizeof( tempVector5[ 0 ] ) );
	const float tempVector6[] = { 1722.699f, 2454.445f };
	std::vector<float> StatsMenu::x2 = std::vector<float>( tempVector6, tempVector6 + sizeof( tempVector6 ) / sizeof( tempVector6[ 0 ] ) );
	const float tempVector7[] = { 1650, 2075, 2505 };
	std::vector<float> StatsMenu::x3 = std::vector<float>( tempVector7, tempVector7 + sizeof( tempVector7 ) / sizeof( tempVector7[ 0 ] ) );
	const float tempVector8[] = { 1550, 1905, 2260, 2615 };
	std::vector<float> StatsMenu::x4 = std::vector<float>( tempVector8, tempVector8 + sizeof( tempVector8 ) / sizeof( tempVector8[ 0 ] ) );
	const std::vector<float> tempVector9[] = { std::vector<float>(), StatsMenu::x1, StatsMenu::x2, StatsMenu::x3, StatsMenu::x4 };
	std::vector<std::vector<float> > StatsMenu::x = std::vector<std::vector<float> >( tempVector9, tempVector9 + sizeof( tempVector9 ) / sizeof( tempVector9[ 0 ] ) );
	const std::vector<Vector2> tempVector10[] = { std::vector<Vector2>(), StatsMenu::x1_name, StatsMenu::x2_name, StatsMenu::x3_name, StatsMenu::x4_name };
	std::vector<std::vector<Vector2> > StatsMenu::name_pos = std::vector<std::vector<Vector2> >( tempVector10, tempVector10 + sizeof( tempVector10 ) / sizeof( tempVector10[ 0 ] ) );

	std::shared_ptr<MenuItem> StatsMenu::AddRow( const std::shared_ptr<MenuItem> &Item, const std::shared_ptr<LambdaFunc_1<int, int> > &f )
	{
		return AddRow( Item, std::make_shared<StringificationWrapper>( f ) );
	}

	std::shared_ptr<MenuItem> StatsMenu::AddRow( const std::shared_ptr<MenuItem> &Item, const std::shared_ptr<LambdaFunc_1<int, std::wstring> > &f )
	{
		AddItem( Item );

		int index = 0;
		std::shared_ptr<EzText> Text;
		for ( int j = 0; j < 4; j++ )
		{
			if ( PlayerManager::Get( j )->Exists )
			{
				std::wstring val = f->Apply( j );

				Text = std::make_shared<EzText>( val, ItemFont, false, true );
				Text->Layer = 1;
				MyPile->Add( Text );
				Text->FancyPos->SetCenter( Item->FancyPos );
				//Text.Pos = new Vector2(1550 + xSpacing * j, -147.1428f);
				Text->setPos( Vector2( x[ n ][ index ], -147.1428f ) );

				Text->setScale( Text->getScale() * .9f );
				if ( val.length() <= 5 )
					Text->setScale( Text->getScale() * .7f );
				else if ( val.length() == 6 )
					Text->setScale( Text->getScale() * .6f );
				else
					Text->setScale( Text->getScale() * .5f );

				Text->RightJustify = true;

				index++;
			}
		}

		return Item;
	}

	void StatsMenu::Init()
	{
		CkBaseMenu::Init();

		CategoryDelays();
	}

	StatsMenu::StatsMenu( StatGroup group ) { }
	void StatsMenu::StatsMenu_Construct( StatGroup group )
	{
		CkBaseMenu::CkBaseMenu_Construct();

		InitializeInstanceFields();
		n = PlayerManager::GetNumPlayers();

		// Grab the stats for each player
		for ( int i = 0; i < 4; i++ )
		{
			std::shared_ptr<CloudberryKingdom::PlayerData> player = PlayerManager::Get( i );

			Stats[ i ] = player->GetSummedStats( group );
			if ( !Tools::CurLevel->Finished && !Tools::CurLevel->CoinsCountInStats )
				Stats[ i ]->TotalCoins += Tools::CurLevel->NumCoins;
		}

		MyPile = std::make_shared<DrawPile>();

		// Make the menu
		MyMenu = std::make_shared<LongMenu>();
		MyMenu->FixedToCamera = false;
		MyMenu->WrapSelect = false;

		MyMenu->setControl( -1 );

		MyMenu->OnB = std::make_shared<MenuReturnToCallerLambdaFunc>( std::static_pointer_cast<GUI_Panel>( shared_from_this() ) );

		MakeBack();

		ItemPos = Vector2( -1305, 950 );
		PosAdd = Vector2( 0, -151 ) * 1.2f * 1.1f;
		Vector2 HeaderPosAdd = PosAdd + Vector2( 0, -120 );

		BarPos = Vector2( 340, 125 );

		// Header
		std::shared_ptr<MenuItem> Header;
		if ( group == StatGroup_LIFETIME )
			Header = std::make_shared<MenuItem>( std::make_shared<EzText>( Localization::Words_STATISTICS, Resources::Font_Grobold42_2 ) );
		else if ( group == StatGroup_CAMPAIGN )
		{
			Header = std::make_shared<MenuItem>( std::make_shared<EzText>( Localization::Words_STORY_MODE, Resources::Font_Grobold42_2 ) );
			Header->MyText->setScale( Header->MyText->getScale() * .725f );
		}
		else
			Header = std::make_shared<MenuItem>( std::make_shared<EzText>( Localization::Words_STATISTICS, Resources::Font_Grobold42_2 ) );
		MyMenu->Add( Header );
		Header->Pos = Vector2( HeaderPos, ItemPos.Y - 40 );
		SetHeaderProperties( Header->MyText );
		Header->MyText->setScale( Header->MyText->getScale() * 1.15f );
		Header->Selectable = false;
		ItemPos += HeaderPosAdd;

	#if defined(NOT_PC)
		std::shared_ptr<EzText> Text;
		Header = std::make_shared<MenuItem>( std::make_shared<EzText>( _T( "" ), ItemFont ) );
		MyMenu->Add( Header );
		Header->Pos = Vector2( -1138.889f, 988.0952f );
		Header->Selectable = false;
		int index = 0;
		for ( int j = 0; j < 4; j++ )
		{
			if ( PlayerManager::Get( j )->Exists )
			{
				//string val = "Hobabby!";
				std::wstring val = PlayerManager::Get( j )->GetName();
				Text = std::make_shared<EzText>( val, ItemFont, true, true );
				Text->Layer = 1;
				MyPile->Add( Text );
				Text->FancyPos->SetCenter( Header->FancyPos );
				GamerTag::ScaleGamerTag( Text );

				//Text.Pos = new Vector2(1090 + xSpacing * j, -147.1428f);
				//if (j % 2 == 0) Text.FancyPos.RelVal.Y -= 150;
				//Text.Scale *= .85f;

				Text->setPos( name_pos[ n ][ index ] );

				if ( n == 1 )
					Text->setScale( Text->getScale() * 1.15f );
				else if ( n == 2 )
					Text->setScale( Text->getScale() * 1.05f );
				else if ( n == 3 )
					Text->setScale( Text->getScale() * .95f );
				else
					Text->setScale( Text->getScale() * .85f );

				index++;
			}
		}
	#endif
		AddRow( std::make_shared<MenuItem>( std::make_shared<EzText>( Localization::Words_LEVELS_BEAT, ItemFont ) ), std::make_shared<StatsLevels>( Stats ) );
		AddRow( std::make_shared<MenuItem>( std::make_shared<EzText>( Localization::Words_JUMPS, ItemFont ) ), std::make_shared<StatsJumps>( Stats ) );
		AddRow( std::make_shared<MenuItem>( std::make_shared<EzText>( Localization::Words_SCORE, ItemFont ) ), std::make_shared<StatsScore>( Stats ) );


		// Coins
		std::shared_ptr<MenuItem> coinitem = std::make_shared<MenuItem>( std::make_shared<EzText>( Localization::Words_COINS, ItemFont ) );
		coinitem->Selectable = false;
		AddItem( coinitem );

		AddRow( std::make_shared<MenuItem>( std::make_shared<EzText>( Localization::Words_GRABBED, ItemFont ) ), std::make_shared<StatsCoins>( Stats ) );
		AddRow( std::make_shared<MenuItem>( std::make_shared<EzText>( Localization::Words_COINS_OUT_OF, ItemFont ) ), std::make_shared<StatsTotalCoins>( Stats ) );
		AddRow( std::make_shared<MenuItem>( std::make_shared<EzText>( Localization::Words_PERCENT, ItemFont ) ), std::make_shared<StatsCoinPercentGotten>( Stats ) );

		AddRow( std::make_shared<MenuItem>( std::make_shared<EzText>( Localization::Words_FLYING_BLOBS, ItemFont ) ), std::make_shared<StatsBlobs>( Stats ) );
		AddRow( std::make_shared<MenuItem>( std::make_shared<EzText>( Localization::Words_CHECKPOINTS, ItemFont ) ), std::make_shared<StatsCheckpoints>( Stats ) );
		AddRow( std::make_shared<MenuItem>( std::make_shared<EzText>( Localization::Words_AVERAGE_LIFE, ItemFont ) ), std::make_shared<StatsLifeExpectancy>( Stats ) );

		// Deaths
		Header = std::make_shared<MenuItem>( std::make_shared<EzText>( Localization::Words_DEATHS, Resources::Font_Grobold42_2 ) );
		MyMenu->Add( Header );
		Header->Pos = Vector2( HeaderPos, ItemPos.Y - 40 );
		SetHeaderProperties( Header->MyText );
		Header->MyText->setScale( Header->MyText->getScale() * 1.15f );
		Header->Selectable = false;
		ItemPos += HeaderPosAdd;

		int NumDeathTypes = BobDeathType_TOTAL;
		for ( int i = 1; i < NumDeathTypes; i++ )
		{
			BobDeathType type = static_cast<BobDeathType>( i );

			if ( Bob::BobDeathNames.find( type ) != Bob::BobDeathNames.end() )
			{
				Localization::Words word = Bob::BobDeathNames[ type ];

				AddRow( std::make_shared<MenuItem>( std::make_shared<EzText>( word, ItemFont ) ), std::make_shared<StatsDeathsBy>( Stats, i ) );
			}
		}


		// Back
		//MenuItem item = MakeBackButton();
		//item.ScaleText(1.4f);

		// Select first selectable item
		//MyMenu.SelectItem(0);
		MyMenu->SelectItem( 1 );



		// Darker Backdrop
		std::shared_ptr<QuadClass> Backdrop = std::make_shared<QuadClass>( _T( "Backplate_1230x740" ), _T( "Backdrop" ) );
		MyPile->Add( Backdrop );
		MyPile->Add( Backdrop );

		EnsureFancy();
		MyMenu->setPos( Vector2( 67.45706f, 0 ) );
		MyPile->setPos( Vector2( 83.33417f, 130.9524f ) );

		SetPos();
	}

	void StatsMenu::SetPos()
	{
		std::shared_ptr<MenuItem> _item;
		_item = MyMenu->FindItemByName( _T( "Back" ) );
		if ( _item != 0 )
		{
			_item->setSetPos( Vector2( 1230.718f, 975.2383f ) );
			_item->MyText->setScale( 0.375f );
			_item->MySelectedText->setScale( 0.375f );
			_item->SelectIconOffset = Vector2( 0, 0 );
		}
		MyMenu->setPos( Vector2( 67.45706f, 0 ) );

		std::shared_ptr<QuadClass> _q;
		_q = MyPile->FindQuad( _T( "Backdrop" ) );
		if ( _q != 0 )
		{
			_q->setPos( Vector2( -91.66821f, -103.8888f ) );
			_q->setSize( Vector2( 1907.893f, 1089.838f ) );
		}

		MyPile->setPos( Vector2( 83.33417f, 130.9524f ) );
	}

	void StatsMenu::OnAdd()
	{
		CkBaseMenu::OnAdd();

		// Scroll bar
	#if defined(PC_VERSION)
		bar = std::make_shared<ScrollBar>( std::static_pointer_cast<LongMenu>( MyMenu ), std::static_pointer_cast<GUI_Panel>( shared_from_this() ) );
		bar->setBarPos( BarPos );
		MyGame->AddGameObject( bar );
		MyMenu->AdditionalCheckForOutsideClick = std::make_shared<OnAddHelper>( bar );
	#endif
	}

	void StatsMenu::MakeBack()
	{
		std::shared_ptr<MenuItem> item;

		ItemPos = Vector2( 1230.718f, 975.2383f );
		item = MakeBackButton();
		item->UnaffectedByScroll = true;
		item->ScaleText( .5f );
	}

	void StatsMenu::MyPhsxStep()
	{
		CkBaseMenu::MyPhsxStep();
	}

	void StatsMenu::MyDraw()
	{
		CkBaseMenu::MyDraw();

		MyPile->Draw( 1 );
	}

	void StatsMenu::InitializeInstanceFields()
	{
		HeaderPos = -1595;
		Stats = std::vector<std::shared_ptr<PlayerStats> >( 4 );
	}
}
