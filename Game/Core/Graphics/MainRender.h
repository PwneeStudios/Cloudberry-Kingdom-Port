#ifndef MAINRENDER
#define MAINRENDER

#include <Hacks/XNA/SpriteBatch.h>
#include <Hacks/XNA/Viewport.h>

namespace CloudberryKingdom
{
	struct MainRender
	{
	
		boost::shared_ptr<GraphicsDevice> MyGraphicsDevice;
	
		float SpriteScaling;

		Viewport MainViewport;

		bool UsingSpriteBatch;
		boost::shared_ptr<SpriteBatch> MySpriteBatch;


		MainRender( const boost::shared_ptr<GraphicsDevice> &Device );

		/// <summary>
		/// Sets the standard render states.
		/// </summary>
		void SetStandardRenderStates();

		void ResetViewport();

		/// <summary>
		/// If the aspect ratio of the game (1280:720) doesn't match the window, use a letterbox viewport.
		/// </summary>
		void MakeInnerViewport();

		/// <summary>
		/// Ends the SpriteBatch, if in use, and resets standard render states.
		/// </summary>
		void EndSpriteBatch();

	
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef MAINRENDER
