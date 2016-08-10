#include <small_header.h>
#include "Core/Graphics/MainRender.h"

#include "Game/Tools/Tools.h"


#include <Game/CloudberryKingdom/CloudberryKingdom.CloudberryKingdomGame.h>

namespace CloudberryKingdom
{

	MainRender::MainRender( const boost::shared_ptr<GraphicsDevice> &Device )
	{
		InitializeInstanceFields();
		MyGraphicsDevice = Device;
	}

	void MainRender::SetStandardRenderStates()
	{
		Tools::QDrawer->SetInitialState();

		MyGraphicsDevice->RasterizerState = GfxRasterizerState_CullNone;
		MyGraphicsDevice->BlendState = GfxBlendState_AlphaBlend;
		MyGraphicsDevice->DepthStencilState = GfxDepthStencilState_DepthRead;

		ResetViewport();
	}

	void MainRender::ResetViewport()
	{
		Tools::TheGame->MyGraphicsDevice->VP = Tools::Render->MainViewport;
	}

	void MainRender::MakeInnerViewport()
	{
		float targetAspectRatio = 1280.f / 720.f;
		// figure out the largest area that fits in this resolution at the desired aspect ratio
		int width = MyGraphicsDevice->PP->BackBufferWidth;
		SpriteScaling = width / 1280.f;
		int height = static_cast<int>( width / targetAspectRatio + .5f );
		if ( height > MyGraphicsDevice->PP->BackBufferHeight )
		{
			height = MyGraphicsDevice->PP->BackBufferHeight;
			width = static_cast<int>( height * targetAspectRatio + .5f );
		}

		// set up the new viewport centered in the backbuffer
		Viewport vp;
		vp.X = MyGraphicsDevice->PP->BackBufferWidth / 2.f - width / 2.f;
		vp.Y = MyGraphicsDevice->PP->BackBufferHeight / 2.f - height / 2.f;
		vp.Width = static_cast<float>( width );
		vp.Height = static_cast<float>( height );
		vp.MinDepth = 0;
		vp.MaxDepth = 1;

		MainViewport = MyGraphicsDevice->VP = vp;
	}

	void MainRender::EndSpriteBatch()
	{
		if ( UsingSpriteBatch )
		{
			UsingSpriteBatch = false;

			MySpriteBatch->End();

			Tools::Render->SetStandardRenderStates();
		}
	}

	void MainRender::InitializeInstanceFields()
	{
		SpriteScaling = 1;
		UsingSpriteBatch = false;
	}
}
