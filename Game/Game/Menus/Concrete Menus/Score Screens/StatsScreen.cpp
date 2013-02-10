#include <global_header.h>

#include <Hacks\Parse.h>
#include <Hacks\String.h>
#include <Hacks\List.h>

namespace CloudberryKingdom
{

    std::wstring FormatFunc( int n )
    {
        return FormatWithSeparators( n );
    }

	StatsMenu::StringificationWrapper::StringificationWrapper( const boost::shared_ptr<LambdaFunc_1<int, int> > &f )
	{
		this->f = f;
	}

	std::wstring StatsMenu::StringificationWrapper::Apply( const int &i )
	{
		//return ToString( f->Apply( i ) );
		return FormatFunc( f->Apply( i ) );
	}

	StatsMenu::StatsLevels::StatsLevels( std::vector<boost::shared_ptr<PlayerStats> > Stats )
	{
		this->Stats = Stats;
	}

	int StatsMenu::StatsLevels::Apply( const int &j )
	{
		 return Stats[ j ]->Levels;
	}

	StatsMenu::StatsJumps::StatsJumps( std::vector<boost::shared_ptr<PlayerStats> > Stats )
	{
		this->Stats = Stats;
	}

	int StatsMenu::StatsJumps::Apply( const int &j )
	{
		return Stats[ j ]->Jumps;
	}

	StatsMenu::StatsScore::StatsScore( std::vector<boost::shared_ptr<PlayerStats> > Stats )
	{
		this->Stats = Stats;
	}

	int StatsMenu::StatsScore::Apply( const int &j )
	{
		return Stats[ j ]->Score;
	}

	StatsMenu::StatsCoins::StatsCoins( std::vector<boost::shared_ptr<PlayerStats> > Stats )
	{
		this->Stats = Stats;
	}

	int StatsMenu::StatsCoins::Apply( const int &j )
	{
		return Stats[ j ]->Coins;
	}

	StatsMenu::StatsTotalCoins::StatsTotalCoins( std::vector<boost::shared_ptr<PlayerStats> > Stats )
	{
		this->Stats = Stats;
	}

	int StatsMenu::StatsTotalCoins::Apply( const int &j )
	{
		return Stats[ j ]->TotalCoins;
	}

	StatsMenu::StatsCoinPercentGotten::StatsCoinPercentGotten( std::vector<boost::shared_ptr<PlayerStats> > Stats )
	{
		this->Stats = Stats;
	}

	std::wstring StatsMenu::StatsCoinPercentGotten::Apply( const int &j )
	{
		return Format( _T( "%d%%" ), Stats[ j ]->getCoinPercentGotten() );
	}

	StatsMenu::StatsBlobs::StatsBlobs( std::vector<boost::shared_ptr<PlayerStats> > Stats )
	{
		this->Stats = Stats;
	}

	int StatsMenu::StatsBlobs::Apply( const int &j )
	{
		return Stats[ j ]->Blobs;
	}

	StatsMenu::StatsCheckpoints::StatsCheckpoints( std::vector<boost::shared_ptr<PlayerStats> > Stats )
	{
		this->Stats = Stats;
	}

	int StatsMenu::StatsCheckpoints::Apply( const int &j )
	{
		return Stats[ j ]->Checkpoints;
	}

	StatsMenu::StatsLifeExpectancy::StatsLifeExpectancy( std::vector<boost::shared_ptr<PlayerStats> > Stats )
	{
		this->Stats = Stats;
	}

	std::wstring StatsMenu::StatsLifeExpectancy::Apply( const int &j )
	{
		return Stats[ j ]->getLifeExpectancy();
	}

	StatsMenu::StatsDeathsBy::StatsDeathsBy( std::vector<boost::shared_ptr<PlayerStats> > Stats, int i )
	{
		this->Stats = Stats;
		this->i = i;
	}

	int StatsMenu::StatsDeathsBy::Apply( const int &j )
	{
		return Stats[ j ]->DeathsBy[ i ];
	}

	StatsMenu::OnAddHelper::OnAddHelper( const boost::shared_ptr<ScrollBar> &bar )
	{
		this->bar = bar;
	}

	bool StatsMenu::OnAddHelper::Apply()
	{
#if defined(WINDOWS) && !defined(NOT_PC)
		return bar->MyMenu->HitTest();
#else
		return false;
#endif
	}

	void StatsMenu::SetItemProperties( const boost::shared_ptr<MenuItem> &item )
	{
		CkBaseMenu::SetItemProperties( item );

		item->MyText->Shadow = item->MySelectedText->Shadow = false;
	}

	void StatsMenu::SetHeaderProperties( const boost::shared_ptr<EzText> &text )
	{
		text->MyFloatColor = Vector4( .6f,.6f,.6f, 1 );
		text->OutlineColor = Vector4( 0, 0, 0, 1 );

		text->Shadow = false;
		text->ShadowColor = Color( .2f,.2f,.2f, 1 );
		text->ShadowOffset = Vector2( 12, 12 );

		text->setScale( FontScale *.9f );
	}

	static Vector2 tempVector[] = { Vector2( 1431.285f, -158.9048f ) };
	std::vector<Vector2> StatsMenu::x1_name = VecFromArray( tempVector );
	Vector2 tempVector2[] = { Vector2( 1217, -147 ), Vector2( 2056, -147 ) };
	std::vector<Vector2> StatsMenu::x2_name = VecFromArray( tempVector2 );
	Vector2 tempVector3[] = { Vector2( 1225, -295 ), Vector2( 1624, -127.3015f ), Vector2( 2116, -295 ) };
	std::vector<Vector2> StatsMenu::x3_name = VecFromArray( tempVector3 );
	Vector2 tempVector4[] = { Vector2( 1090, -295 ), Vector2( 1445, -127.3015f ), Vector2( 1800, -295 ), Vector2( 2155, -127.3015f ) };
	std::vector<Vector2> StatsMenu::x4_name = VecFromArray( tempVector4 );
	float tempVector5[] = { 1920 };
	std::vector<float> StatsMenu::x1 = VecFromArray( tempVector5 );
	float tempVector6[] = { 1722.699f - 200, 2454.445f - 30 };
	std::vector<float> StatsMenu::x2 = VecFromArray( tempVector6 );
	float tempVector7[] = { 1650.0f - 200, 2075.0f - 140.0f, 2505.0f - 80.0f };
	std::vector<float> StatsMenu::x3 = VecFromArray( tempVector7 );
	float tempVector8[] = { 1525.0f - 200, 1905.0f - 180.0f, 2260.0f - 160.0f, 2615.0f - 140.0f };
	std::vector<float> StatsMenu::x4 = VecFromArray( tempVector8 );
	std::vector<float> tempVector9[] = { std::vector<float>(), StatsMenu::x1, StatsMenu::x2, StatsMenu::x3, StatsMenu::x4 };
	std::vector<std::vector<float> > StatsMenu::x = VecFromArray( tempVector9 );
	std::vector<Vector2> tempVector10[] = { std::vector<Vector2>(), StatsMenu::x1_name, StatsMenu::x2_name, StatsMenu::x3_name, StatsMenu::x4_name };
	std::vector<std::vector<Vector2> > StatsMenu::name_pos = VecFromArray( tempVector10 );

	boost::shared_ptr<MenuItem> StatsMenu::AddRow( const boost::shared_ptr<MenuItem> &Item, const boost::shared_ptr<LambdaFunc_1<int, int> > &f )
	{
		return AddRow( Item, boost::make_shared<StringificationWrapper>( f ) );
	}

	boost::shared_ptr<MenuItem> StatsMenu::AddRow( const boost::shared_ptr<MenuItem> &Item, const boost::shared_ptr<LambdaFunc_1<int, std::wstring> > &f )
	{
		AddItem( Item );

		Item->MyText->setScale( .5f );
		Item->MySelectedText->setScale( .5f );

		int index = 0;
		boost::shared_ptr<EzText> Text;
		for ( int j = 0; j < 4; j++ )
		{
			if ( PlayerManager::Get( j )->Exists )
			{
				std::wstring val = f->Apply( j );

				Text = boost::make_shared<EzText>( val, ItemFont, false, true );
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

				Text->setScale( Text->getScale() * .77f );

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

        

    void StatsMenu::SetParams()
    {
    //float[] x1 = { 1920 };
    //float[] x2 = { 1722.699f - 200, 2454.445f - 30 };
    //float[] x3 = { 1650f - 200, 2075f - 140, 2505f - 80 };
    //float[] x4 = { 1525f - 200, 1905f - 180, 2260f - 160, 2615f - 140};
    //x = new float[][]{ null, x1, x2, x3, x4 };


        PlayerManager::Players[1]->Exists = false;
        PlayerManager::Players[2]->Exists = false;
        PlayerManager::Players[3]->Exists = false;
            

        ItemPos = Vector2(-1225, 950);
        PosAdd = Vector2(0, -141) * 1.2f * 1.1f;
        HeaderPosAdd = PosAdd + Vector2(0, -120);

        BarPos = Vector2(340, 125);
    }


	StatsMenu::StatsMenu( StatGroup group ) :
		n( 0 ), HeaderPos( 0 )
	{
		//PlayerManager::Players[1]->Exists = true;
		//PlayerManager::Players[2]->Exists = true;
	}
	boost::shared_ptr<StatsMenu> StatsMenu::StatsMenu_Construct( StatGroup group )
	{
		InitializeInstanceFields();

		CkBaseMenu::CkBaseMenu_Construct();
		
		//n = PlayerManager::GetNumPlayers();
		EnableBounce();

		// Grab the stats for each player
		for ( int i = 0; i < 4; i++ )
		{
			boost::shared_ptr<CloudberryKingdom::PlayerData> player = PlayerManager::Get( i );

			Stats[ i ] = player->GetSummedStats( group );
			if ( !Tools::CurLevel->Finished && !Tools::CurLevel->CoinsCountInStats )
				Stats[ i ]->TotalCoins += Tools::CurLevel->NumCoins;
		}

		MyPile = boost::make_shared<DrawPile>();

		// Make the menu
		MyMenu = boost::make_shared<LongMenu>();
		MyMenu->FixedToCamera = false;
		MyMenu->WrapSelect = false;

		MyMenu->setControl( -1 );

		MyMenu->OnB = boost::make_shared<MenuReturnToCallerLambdaFunc>( boost::static_pointer_cast<GUI_Panel>( shared_from_this() ) );
            
		SetParams();
        n = PlayerManager::GetNumPlayers();

		// Header
		boost::shared_ptr<MenuItem> Header;
		if ( group == StatGroup_LIFETIME )
			Header = MakeMagic( MenuItem, ( boost::make_shared<EzText>( Localization::Words_Statistics, Resources::Font_Grobold42_2 ) ) );
		else if ( group == StatGroup_CAMPAIGN )
		{
			Header = MakeMagic( MenuItem, ( boost::make_shared<EzText>( Localization::Words_StoryMode, Resources::Font_Grobold42_2 ) ) );
			Header->MyText->setScale( Header->MyText->getScale() * .725f );
		}
		else
			Header = MakeMagic( MenuItem, ( boost::make_shared<EzText>( Localization::Words_Statistics, Resources::Font_Grobold42_2 ) ) );
		MyMenu->Add( Header );
		Header->Pos = Vector2( HeaderPos, ItemPos.Y - 40 );
		SetHeaderProperties( Header->MyText );
		Header->MyText->setScale( Header->MyText->getScale() * 1.15f );
		Header->Selectable = false;
		ItemPos += HeaderPosAdd;

	#if defined(NOT_PC)
		boost::shared_ptr<EzText> Text;
		Header = MakeMagic( MenuItem, ( boost::make_shared<EzText>( std::wstring( L"" ), ItemFont ) ) );
		MyMenu->Add( Header );
		Header->Pos = Vector2( -1138.889f, 988.0952f );
		Header->Selectable = false;
		int index = 0;
		if ( PlayerManager::NumPlayers > 1 )
		for ( int j = 0; j < 4; j++ )
		{
			if ( PlayerManager::Get( j )->Exists )
			{
                std::wstring val = PlayerManager::Get(j)->GetName();
                Text = MakeGamerTag(Header, index, val);

				index++;
			}
		}
	#endif
		AddRow( MakeMagic( MenuItem, ( boost::make_shared<EzText>( Localization::Words_LevelsBeat, ItemFont ) ) ), boost::make_shared<StatsLevels>( Stats ) );
		AddRow( MakeMagic( MenuItem, ( boost::make_shared<EzText>( Localization::Words_Jumps, ItemFont ) ) ), boost::make_shared<StatsJumps>( Stats ) );
		AddRow( MakeMagic( MenuItem, ( boost::make_shared<EzText>( Localization::Words_Score, ItemFont ) ) ), boost::make_shared<StatsScore>( Stats ) );

		AddRow( MakeMagic( MenuItem, ( boost::make_shared<EzText>( Localization::Words_FlyingBlobs, ItemFont ) ) ), boost::make_shared<StatsBlobs>( Stats ) );
		AddRow( MakeMagic( MenuItem, ( boost::make_shared<EzText>( Localization::Words_Checkpoints, ItemFont ) ) ), boost::make_shared<StatsCheckpoints>( Stats ) );
		AddRow( MakeMagic( MenuItem, ( boost::make_shared<EzText>( Localization::Words_AverageLife, ItemFont ) ) ), boost::make_shared<StatsLifeExpectancy>( Stats ) );


		// Coins
        Header = MakeMagic( MenuItem, (boost::make_shared<EzText>(Localization::Words_Coins, Resources::Font_Grobold42_2) ) );
        MyMenu->Add(Header);
        Header->Pos = Vector2(HeaderPos, ItemPos.Y - 40);
        SetHeaderProperties(Header->MyText);
        Header->MyText->setScale(Header->MyText->getScale() * 1.15f);
        Header->Selectable = false;
        ItemPos += HeaderPosAdd;

		//boost::shared_ptr<MenuItem> coinitem = MakeMagic( MenuItem, ( boost::make_shared<EzText>( Localization::Words_Coins, ItemFont ) ) );
		//coinitem->Selectable = false;
		//AddItem( coinitem );

		AddRow( MakeMagic( MenuItem, ( boost::make_shared<EzText>( Localization::Words_Grabbed, ItemFont ) ) ), boost::make_shared<StatsCoins>( Stats ) );
		AddRow( MakeMagic( MenuItem, ( boost::make_shared<EzText>( Localization::Words_CoinsOutOf, ItemFont ) ) ), boost::make_shared<StatsTotalCoins>( Stats ) );
		AddRow( MakeMagic( MenuItem, ( boost::make_shared<EzText>( Localization::Words_Percent, ItemFont ) ) ), boost::make_shared<StatsCoinPercentGotten>( Stats ) );

		// Deaths
		Header = MakeMagic( MenuItem, ( boost::make_shared<EzText>( Localization::Words_Deaths, Resources::Font_Grobold42_2 ) ) );
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

				AddRow( MakeMagic( MenuItem, ( boost::make_shared<EzText>( word, ItemFont ) ) ), boost::make_shared<StatsDeathsBy>( Stats, i ) );
			}
		}


		// Back
		//MenuItem item = MakeBackButton();
		//item.ScaleText(1.4f);

		// Select first selectable item
		//MyMenu.SelectItem(0);
		MyMenu->SelectItem( 1 );



		// Darker Backdrop
		boost::shared_ptr<QuadClass> Backdrop;
		//if (UseSimpleBackdrop)
		if (true)
        {
            Backdrop = boost::make_shared<QuadClass>( std::wstring( L"Arcade_BoxLeft" ), 1500.f, true );
            Backdrop->setAlpha( Backdrop->getAlpha() * .8f );
        }
        else
            Backdrop = boost::make_shared<QuadClass>( std::wstring( L"Backplate_1230x740" ), std::wstring( L"Backdrop" ) );

		MyPile->Add( Backdrop );
		MyPile->Add( Backdrop );

		EnsureFancy();
		MyMenu->setPos( Vector2( 67.45706f, 0 ) );
		MyPile->setPos( Vector2( 83.33417f, 130.9524f ) );

		MakeBack();

		SetPos();

		return boost::static_pointer_cast<StatsMenu>( shared_from_this() );
	}

	boost::shared_ptr<EzText> StatsMenu::MakeGamerTag( boost::shared_ptr<MenuItem> Header, int index, std::wstring val )
    {
        boost::shared_ptr<EzText> Text;
        Text = boost::make_shared<EzText>( val, ItemFont, true, true );
        Text->Layer = 1;
        MyPile->Add( Text );
        Text->FancyPos->SetCenter( Header->FancyPos );
        //GamerTag.ScaleGamerTag(Text);

        Text->setPos( name_pos[n][index] );

        if (n == 1) Text->setScale( Text->getScale() * .65f );
        else if (n == 2) Text->setScale( Text->getScale() * .5f );
        else if (n == 3) Text->setScale( Text->getScale() * .4f );
        else Text->setScale( Text->getScale() * .4f );
        return Text;
    }

	void StatsMenu::SetPos()
	{
        boost::shared_ptr<MenuItem> _item;
        _item = MyMenu->FindItemByName( L"Back" ); if (_item != 0 ) { _item->setSetPos( Vector2( 1230.718f, 975.2383f ) ); _item->MyText->setScale( 0.375f ); _item->MySelectedText->setScale( 0.375f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }
        MyMenu->setPos( Vector2( 67.45706f, 0.f ) );

        boost::shared_ptr<QuadClass> _q;
        _q = MyPile->FindQuad( L"Backdrop" ); if (_q != 0 ) { _q->setPos( Vector2(-91.66821f, -103.8888f ) ); _q->setSize( Vector2( 1907.893f, 1089.838f ) ); }
        _q = MyPile->FindQuad( L"Button_Back" ); if (_q != 0 ) { _q->setPos( Vector2( 1522.222f, -983.3331f ) ); _q->setSize( Vector2( 90.f, 90.f ) ); }
        _q = MyPile->FindQuad( L"BackArrow" ); if (_q != 0 ) { _q->setPos( Vector2( 1322.222f, -1008.333f ) ); _q->setSize( Vector2( 100.f, 86.f ) ); }

        MyPile->setPos( Vector2( 83.33417f, 130.9524f ) );
	}

	void StatsMenu::OnAdd()
	{
		CkBaseMenu::OnAdd();

		// Scroll bar
	#if defined(PC_VERSION)
		bar = MakeMagic( ScrollBar, ( boost::static_pointer_cast<LongMenu>( MyMenu ), boost::static_pointer_cast<GUI_Panel>( shared_from_this() ) ) );
		bar->setBarPos( BarPos );
		MyGame->AddGameObject( bar );
		MyMenu->AdditionalCheckForOutsideClick = boost::make_shared<OnAddHelper>( bar );
	#endif
	}

	void StatsMenu::MakeBack()
	{
		boost::shared_ptr<MenuItem> item;

		ItemPos = Vector2( 1230.718f, 975.2383f );

#ifdef PC_VERSION
		item = MakeBackButton();
		item->UnaffectedByScroll = true;
		item->ScaleText( .5f );
#else
        MakeStaticBackButton();
#endif
	}

	void StatsMenu::MyPhsxStep()
	{
		CkBaseMenu::MyPhsxStep();
	}

	void StatsMenu::MyDraw()
	{
		CkBaseMenu::MyDraw();
	}

	void StatsMenu::InitializeInstanceFields()
	{
		HeaderPos = -1595;
		Stats = std::vector<boost::shared_ptr<PlayerStats> >( 4 );
	}
}
