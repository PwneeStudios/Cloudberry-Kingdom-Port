#include <global_header.h>

namespace CloudberryKingdom
{

	GUI_BlobQuota::MyPhsxStepHelper::MyPhsxStepHelper( const std::shared_ptr<GUI_BlobQuota> &blobQuota )
	{
		this->blobQuota = blobQuota;
	}

	void GUI_BlobQuota::MyPhsxStepHelper::Apply()
	{
		blobQuota->SlideOut( PresetPos_TOP, 26 );
	}

	GUI_BlobQuota::GUI_BlobQuota( int Quota )
	{
		InitializeInstanceFields();
		this->Quota = Quota;
	}

	int GUI_BlobQuota::OutOf()
	{
		return Quota;
	}

	void GUI_BlobQuota::OnAdd()
	{
		GUI_Blobs::OnAdd();

		//FinalDoor = MyGame.MyLevel.FinalDoor;
		//FinalDoor.SetLock(true, true, false);
	}

	void GUI_BlobQuota::Reset( bool BoxesOnly )
	{
		GUI_Blobs::Reset( BoxesOnly );
	}

	void GUI_BlobQuota::MyPhsxStep()
	{
		GUI_Blobs::MyPhsxStep();

		if ( Blobs >= Quota )
		{
			Blobs = Quota;
			UpdateCoinText();

			if ( !QuotaMet )
			{
				// On Quoate Met
				if ( OnQuotaMet != 0 )
					OnQuotaMet->Apply( std::static_pointer_cast<GUI_Blobs>( shared_from_this() ) );

				// Emphasize
				MyPile->BubbleUp( true );

				// Hide
				MyGame->WaitThenDo( 28, std::make_shared<MyPhsxStepHelper>( std::static_pointer_cast<GUI_BlobQuota>( shared_from_this() ) ), _T( "" ), true, true );

				//FinalDoor.SetLock(false);

				QuotaMet = true;
			}
		}
		else
		{
			//FinalDoor.SetLock(true, true, false);

			QuotaMet = false;
		}
	}

	void GUI_BlobQuota::InitializeInstanceFields()
	{
		QuotaMet = false;
	}

	int GUI_Blobs::TempStatsLambda::Apply( const std::shared_ptr<PlayerData> &p )
	{
		return p->TempStats->Blobs;
	}

	std::shared_ptr<StringBuilder> GUI_Blobs::BuildString()
	{
		MyString->setLength( 0 );

		MyString->Add( Blobs, 1 );
		MyString->Append( L'/' );
		MyString->Add( OutOf(), 1 );

		return MyString;
	}

	int GUI_Blobs::OutOf()
	{
		return TotalBlobs;
	}

	void GUI_Blobs::OnAdd()
	{
		GUI_Panel::OnAdd();

		if ( !AddedOnce )
		{
			Hide();

			Show();
		}

		AddedOnce = true;

		if ( TotalBlobs == 0 )
			TotalBlobs = MyGame->MyLevel->NumBlobs;
		Blobs = 0;
	}

	void GUI_Blobs::Hide()
	{
		GUI_Panel::Hide();
		SlideOut( PresetPos_TOP, 0 );
	}

	void GUI_Blobs::Show()
	{
		GUI_Panel::Show();
		//SlideIn();
		//MyPile.BubbleUp(false, 10, .7f);
		SlideIn( 50 );
	}

	const Vector2 GUI_Blobs::getApparentPos() const
	{
		return Text->FancyPos->AbsVal + Text->GetWorldSize() / 2;
	}

	void GUI_Blobs::UpdateCoinText()
	{
		Text->SubstituteText( BuildString() );
	}

	GUI_Blobs::GUI_Blobs() { }
	void GUI_Blobs::GUI_Blobs_Construct()
	{
		GUI_Panel::GUI_Panel_Construct();
		InitializeInstanceFields();
	}

	void GUI_Blobs::Init()
	{
		GUI_Panel::Init();

		MyPile = std::make_shared<DrawPile>();
		EnsureFancy();

		Vector2 shift = Vector2( -320, 0 );
		MyPile->setPos( Vector2( 836.1112f, 806.6667f ) - shift );
		SlideInLength = 0;

		// Object is carried over through multiple levels, so prevent it from being released.
		PreventRelease = true;

		PauseOnPause = true;

		MyPile->FancyPos->UpdateWithGame = true;

		std::shared_ptr<QuadClass> cloud = std::make_shared<QuadClass>( _T( "Cloud1" ), 150.f, true );
		cloud->setPos( Vector2( 193.0659f, -22.74048f ) );
		cloud->setSize( Vector2( 465.5865f, 259.2372f ) );
		MyPile->Add( cloud );

//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
		Text = std::make_shared<EzText>( BuildString()->ToString(), Resources::Font_Grobold42_2, 450.f, false, false );
		Text->setScale( .55f );
		Text->setPos( Vector2( 0.3707275f, 73.3901f ) );
		Text->MyFloatColor = ( bColor( 255, 255, 255 ) ).ToVector4();
		Text->OutlineColor = ( bColor( 0, 0, 0 ) ).ToVector4();
		MyPile->Add( Text );

		Blob = std::make_shared<QuadClass>( _T( "Score/Blob" ), 150.f, true );
		Blob->setPos( Vector2( -26.84131f, 11.98175f ) );
		Blob->setSize( Vector2( 122.2223f, 193.6508f ) );
		Blob->ScaleXToMatchRatio();
		//Blob.Angle = 0.1055556f;
		MyPile->Add( Blob );
	}

	void GUI_Blobs::MyDraw()
	{
		if ( !getCore()->Show || getCore()->MyLevel->SuppressCheckpoints )
			return;

		GUI_Panel::MyDraw();
	}

	void GUI_Blobs::MyPhsxStep()
	{
		GUI_Panel::MyPhsxStep();

		if ( MyGame->SoftPause )
			return;
		if ( Hid || !Active )
			return;

		if ( getCore()->MyLevel->Watching || getCore()->MyLevel->Finished )
			return;

		Blobs = PlayerManager::PlayerSum( std::make_shared<TempStatsLambda>() );

		//CoinText.Pos = new Vector2(CoinText.GetWorldWidth(), CoinText.Pos.Y);
		UpdateCoinText();
	}

	void GUI_Blobs::Reset( bool BoxesOnly )
	{
		GUI_Panel::Reset( BoxesOnly );

		//SlideOut(PresetPos.Top, 0);
		SlideIn( 30 );
	}

	void GUI_Blobs::InitializeInstanceFields()
	{
		MyString = std::make_shared<StringBuilder>( 50, 50 );
		TotalBlobs = 0;
		AddedOnce = false;
	}
}
