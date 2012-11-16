#include "LoadingScreen.h"
#include "Core/Graphics/Draw/Quads/QuadClass.h"
#include "Core/Graphics/Draw/Object/ObjectClass.h"
#include "Core/Text/EzText.h"
#include "Game/Tools/Resources.h"
#include "Properties/Resources.Designer.h"
#include "Game/Tools/CkColorHelper.h"
#include "Game/Localization.h"
#include "Game/Player/Hero Physics/Base.h"
#include "Game/Tools/Tools.h"
#include "Game/Player/Hero Physics/Spaceship.h"
#include "Game/Player/Hero Physics/Box.h"
#include "Core/Graphics/Draw/Quads/BaseQuad.h"
#include "Game/Tools/Camera.h"

using namespace Microsoft::Xna::Framework;

namespace CloudberryKingdom
{

int LoadingScreen::DefaultMinLoadLength = 85;
int LoadingScreen::MinLoadLength = 0;

	void LoadingScreen::MakeFake()
	{
		Fake = true;
	}

	void LoadingScreen::AddHint( const std::wstring &hint, int extra_wait )
	{
		MinLoading += extra_wait;

		HintText = std::make_shared<EzText>( hint, Resources::Font_Grobold42, 10000, true, true );
		HintText->setScale( HintText->getScale() * .6125f );
		CkColorHelper::_x_x_HappyBlueColor( HintText );
		//HintText.OutlineColor = Color.Purple.ToVector4();
		HintText->setPos( Vector2( 0, -250 ) );
	}

	LoadingScreen::LoadingScreen()
	{
		InitializeInstanceFields();
		BackgroundQuad = std::make_shared<QuadClass>();
		BackgroundQuad->SetToDefault();

		BackgroundQuad->Set( _T( "LoadingStrip" ) );
		BackgroundQuad->Quad_Renamed->SetColor( Color::Gray );

		BlackQuad = std::make_shared<QuadClass>();
		BlackQuad->SetToDefault();
		BlackQuad->Quad_Renamed->SetColor( Color( 0, 0, 0, 0 ) );

		LoadingText = std::make_shared<EzText>( Localization::Words_LOADING, Resources::Font_Grobold42, true, true );
		LoadingText->setScale( LoadingText->getScale() * .445f );
		LoadingText->FixedToCamera = true;
		LoadingText->_Pos = Vector2( 21, -106 );

		if ( CenterObject != 0 )
		{
			CenterObject->Release();
			CenterObject.reset();
		}
		TextObject.reset();

		std::shared_ptr<BobPhsx> type;
		//if (Tools.WorldMap != null)
		if ( Tools::CurGameData == 0 || Tools::CurGameData->DefaultHeroType == 0 )
			type = Tools::WorldMap->DefaultHeroType;
		else
			type = Tools::CurGameData->DefaultHeroType;

		if ( dynamic_cast<BobPhsxSpaceship*>( type ) != 0 )
		{
			TextObject = std::make_shared<EzText>( _T( "?" ), Resources::Font_Grobold42, true, true );
			CkColorHelper::_x_x_HappyBlueColor( TextObject );
			TextObject->setScale( TextObject->getScale() * 1.25f );
			TextObject->FixedToCamera = true;
			TextObject->_Pos = Vector2( 11, 170 );
		}
		else
		{
			CenterObject = std::make_shared<ObjectClass>( type->Prototype->PlayerObject, false, false );

			Vector2 size = CenterObject->BoxList[ 0 ]->Size();
			float ratio = size.Y / size.X;
			int width = Tools::TheGame->Resolution.Bob_Renamed::X;
			CenterObject->FinishLoading( Tools::QDrawer, Tools::Device, Tools::TextureWad, Tools::EffectWad, Tools::Device->PresentationParameters, width, static_cast<int>( width * ratio ) ); //Tools.Device.PresentationParameters.BackBufferWidth / 4, Tools.Device.PresentationParameters.BackBufferHeight / 4);

			//CenterObject.FinishLoading(Tools.QDrawer, Tools.Device, Tools.TextureWad, Tools.EffectWad, Tools.Device.PresentationParameters, 400, 550);
			CenterObject->ParentQuad->Scale( Vector2( 1.35f, 1.35f ) );
			CenterObject->Read( 1, 0 );
			CenterObject->EnqueueAnimation( 1, 0, true );
			//CenterObject.ParentQuad.Center.Move(new Vector2(0, -126));

			if ( type == BobPhsxBox::getInstance() )
			{
				for ( std::vector<BaseQuad*>::const_iterator quad = CenterObject->QuadList.begin(); quad != CenterObject->QuadList.end(); ++quad )
					if ( ( *quad )->MyDrawOrder == ObjectDrawOrder_WITH_OUTLINE )
						( *quad )->Show = false;
			}

			if ( dynamic_cast<BobPhsxSpaceship*>( type ) != 0 )
			{
				for ( std::vector<BaseQuad*>::const_iterator quad = CenterObject->QuadList.begin(); quad != CenterObject->QuadList.end(); ++quad )
					( *quad )->MyDrawOrder = ObjectDrawOrder_WITH_OUTLINE;
			}
		}
	}

	void LoadingScreen::Start()
	{
		//MinLoadLength = 10000;

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

		if ( Fake && MinLoading == 0 )
			End();

		if ( Fade && MinLoading <= 0 )
		{
			FadeAlpha += .07f;
			if ( FadeAlpha > 1.2f )
				Tools::ShowLoadingScreen = false;
		}
		BlackQuad->Quad_Renamed->SetColor( Color( 0, 0, 0, FadeAlpha ) );

		if ( CenterObject != 0 )
		{
			CenterObject->PlayUpdate( CenterObject->LoadingRunSpeed );
			CenterObject->Update( 0 );
		}
	}

	void LoadingScreen::Draw( const std::shared_ptr<Camera> &cam )
	{
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
	}

	void LoadingScreen::InitializeInstanceFields()
	{
		Fake = false;
	}
}
