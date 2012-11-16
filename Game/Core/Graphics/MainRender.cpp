#include <global_header.h>

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
using namespace Microsoft::Xna::Framework;
using namespace Microsoft::Xna::Framework::Graphics;

namespace CloudberryKingdom
{

	MainRender::MainRender( const std::shared_ptr<GraphicsDevice> &Device )
	{
		InitializeInstanceFields();
		MyGraphicsDevice = Device;
	}

	void MainRender::SetStandardRenderStates()
	{
		Tools::QDrawer->SetInitialState();

		MyGraphicsDevice->RasterizerState = RasterizerState::CullNone;
		MyGraphicsDevice->BlendState = BlendState::AlphaBlend;
		MyGraphicsDevice->DepthStencilState = DepthStencilState::DepthRead;

		ResetViewport();
	}

	void MainRender::ResetViewport()
	{
		Tools::TheGame->MyGraphicsDevice->Viewport = Tools::Render->MainViewport;
	}

	void MainRender::MakeInnerViewport()
	{
		float targetAspectRatio = 1280 / 720;
		// figure out the largest area that fits in this resolution at the desired aspect ratio
		int width = MyGraphicsDevice->PresentationParameters->BackBufferWidth;
		SpriteScaling = width / 1280;
		int height = static_cast<int>( width / targetAspectRatio + .5f );
		if ( height > MyGraphicsDevice->PresentationParameters->BackBufferHeight )
		{
			height = MyGraphicsDevice->PresentationParameters->BackBufferHeight;
			width = static_cast<int>( height * targetAspectRatio + .5f );
		}

		// set up the new viewport centered in the backbuffer
		MainViewport = MyGraphicsDevice->Viewport = Viewport { X = MyGraphicsDevice->PresentationParameters->BackBufferWidth / 2 - width / 2, Y = MyGraphicsDevice->PresentationParameters->BackBufferHeight / 2 - height / 2, Width = width, Height = height, MinDepth = 0, MaxDepth = 1 };
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
