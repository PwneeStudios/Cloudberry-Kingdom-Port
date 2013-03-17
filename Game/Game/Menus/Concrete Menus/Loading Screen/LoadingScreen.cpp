#include <global_header.h>

#include <Game/CloudberryKingdom/CloudberryKingdom.CloudberryKingdomGame.h>

#include <MasterHack.h>

namespace CloudberryKingdom
{

	void LoadingScreen::InitializeStatics()
	{
		LoadingScreen::DefaultMinLoadLength = 85;
		LoadingScreen::MinLoadLength = 0;
	}

	// Statics
	int LoadingScreen::DefaultMinLoadLength;
	int LoadingScreen::MinLoadLength;

	const int LoadingScreen::DrawCount_Max = 60 * 60 - 300; // 60 seconds, minus fade time and safety margin

	void LoadingScreen::MakeFake()
	{
		Fake = true;
		FadeAlpha = 1.2f;
	}

	void LoadingScreen::AddHint( const std::wstring &hint, int extra_wait )
	{
		MinLoading += extra_wait;

		HintText = boost::make_shared<EzText>( hint, Resources::Font_Grobold42, 10000.f, true, true );
		HintText->setScale( HintText->getScale() * .6125f );
		CkColorHelper::_x_x_HappyBlueColor( HintText );
		//HintText.OutlineColor = Color.Purple.ToVector4();
		HintText->setPos( Vector2( 0, -250 ) );
	}

	LoadingScreen::LoadingScreen()
	{
		InitializeInstanceFields();
		BackgroundQuad = boost::make_shared<QuadClass>();
		BackgroundQuad->SetToDefault();

		BackgroundQuad->Set( std::wstring( L"LoadingStrip" ) );
		BackgroundQuad->Quad_Renamed.SetColor( Color::Gray );

		BlackQuad = boost::make_shared<QuadClass>();
		BlackQuad->SetToDefault();
		BlackQuad->Quad_Renamed.SetColor( bColor( 0, 0, 0, 0 ) );

		LoadingText = boost::make_shared<EzText>( Localization::WordString( Localization::Words_Loading ) + L"...", Resources::Font_Grobold42, true, true );
		LoadingText->setScale( LoadingText->getScale() * .445f );
		LoadingText->FixedToCamera = true;
		LoadingText->_Pos = Vector2( 21, -106 );

		if ( CenterObject != 0 )
		{
			CenterObject->Release();
			CenterObject.reset();
		}
		TextObject.reset();

		boost::shared_ptr<BobPhsx> type;
		//if (Tools::WorldMap != null)
		//if ( Tools::CurGameData == 0 || Tools::CurGameData->DefaultHeroType == 0 )
		//	type = Tools::WorldMap->DefaultHeroType;
		//else
		//	type = Tools::CurGameData->DefaultHeroType;
		type = BobPhsxNormal::getInstance();

		//if ( boost::dynamic_pointer_cast<BobPhsxSpaceship>( type ) != 0 )
		//{
		//	TextObject = boost::make_shared<EzText>( std::wstring( L"?" ), Resources::Font_Grobold42, true, true );
		//	CkColorHelper::_x_x_HappyBlueColor( TextObject );
		//	TextObject->setScale( TextObject->getScale() * 1.25f );
		//	TextObject->FixedToCamera = true;
		//	TextObject->_Pos = Vector2( 11, 170 );
		//}
		//else
		{
			CenterObject = boost::make_shared<ObjectClass>( type->Prototype->PlayerObject, false, false );
			ObjectClass_PostConstruct_3params( CenterObject, type->Prototype->PlayerObject, false, false );

			Vector2 size = CenterObject->BoxList[ 0 ]->Size();
			float ratio = size.Y / size.X;
			int width = Tools::TheGame->Resolution.Bob_Renamed.X;
			CenterObject->FinishLoading( Tools::QDrawer, Tools::Device, Tools::TextureWad, Tools::EffectWad, Tools::Device->PP, width, static_cast<int>( width * ratio ) ); //Tools::Device.PresentationParameters.BackBufferWidth / 4, Tools::Device.PresentationParameters.BackBufferHeight / 4);

			//CenterObject.FinishLoading(Tools::QDrawer, Tools::Device, Tools::TextureWad, Tools::EffectWad, Tools::Device.PresentationParameters, 400, 550);
			CenterObject->ParentQuad->Scale( Vector2( 1.35f, 1.35f ) );
			CenterObject->Read( 1, 0 );
			CenterObject->EnqueueAnimation( 1, 0, true );
			//CenterObject.ParentQuad.Center.Move(new Vector2(0, -126));

			if ( type == BobPhsxBox::getInstance() )
			{
				for ( std::vector<boost::shared_ptr<BaseQuad> >::const_iterator quad = CenterObject->QuadList.begin(); quad != CenterObject->QuadList.end(); ++quad )
					if ( ( *quad )->MyDrawOrder == ObjectDrawOrder_WITH_OUTLINE )
						( *quad )->Show = false;
			}

			//if ( boost::dynamic_pointer_cast<BobPhsxSpaceship>( type ) != 0 )
			//{
			//	for ( std::vector<boost::shared_ptr<BaseQuad> >::const_iterator quad = CenterObject->QuadList.begin(); quad != CenterObject->QuadList.end(); ++quad )
			//		( *quad )->MyDrawOrder = ObjectDrawOrder_WITH_OUTLINE;
			//}
		}
	}

	void LoadingScreen::Start()
	{
		DrawCount = 0;

		MinLoading = MinLoadLength;
		MinLoadLength = DefaultMinLoadLength;

		Fade = false;
		FadeAlpha = -.1f;
	}

	void LoadingScreen::End()
	{
		Fade = true;
	}

	void LoadingScreen::PreDraw()
	{
		MinLoading--;

		if ( Fake && MinLoading <= 0 && ( Resources::FinalLoadDone || DrawCount > DrawCount_Max ) )
			End();

		if ( Fake && FadeAlpha > -.1f && !Fade )
		{
			FadeAlpha -= .07f;
		}

		if ( Fade && MinLoading <= 0 )
		{
			FadeAlpha += .07f;
            if ( Fake && FadeAlpha > 1.4f || !Fake && FadeAlpha > 1.2f )
			{
				Tools::ShowLoadingScreen = false;
				//ReleaseLoadingScreen( Tools::CurrentLoadingScreen );
			}
		}
		BlackQuad->Quad_Renamed.SetColor( Color( 0.f, 0.f, 0.f, FadeAlpha ) );

		if ( CenterObject != 0 )
		{
			CenterObject->PlayUpdate( CenterObject->LoadingRunSpeed );
			CenterObject->Update( 0 );
		}
	}

	void LoadingScreen::Draw( const boost::shared_ptr<Camera> &cam )
	{
		DrawCount++;

		Tools::Device->Clear( Color::Black );
		BackgroundQuad->FullScreen( cam );
		BackgroundQuad->Scale( 1.25f );
		BlackQuad->FullScreen( cam );
		BlackQuad->Scale( 1.25f );

		if ( CenterObject != 0 )
			CenterObject->MoveTo( Vector2( 0, -70 ) );
		LoadingText->_Pos = Vector2( 18, -140 );

		BackgroundQuad->Draw();
		Tools::QDrawer->Flush();
		if ( CenterObject != 0 )
		{
			//CenterObject.ContainedDraw();
			CenterObject->Draw( true );
			Tools::QDrawer->Flush();
		}
		LoadingText->Draw( cam );
		if ( HintText != 0 )
			HintText->Draw( cam );
		if ( TextObject != 0 )
			TextObject->Draw( cam );
		Tools::Render->EndSpriteBatch();
		BlackQuad->Draw();
		Tools::QDrawer->Flush();

		if ( Tools::ShowLoadingScreen == false )
		{
			ReleaseLoadingScreen( Tools::CurrentLoadingScreen );
		}
	}

	void LoadingScreen::InitializeInstanceFields()
	{
		DrawCount = 0;

		MinLoading = 0;
		Fade = false;
		FadeAlpha = 0;

		Fake = false;
	}
}
