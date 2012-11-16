#ifndef MAINRENDER
#define MAINRENDER

namespace Microsoft
{
	namespace Xna
	{
		namespace Framework
		{
			namespace Graphics
			{
				class GraphicsDevice;
			}
		}
	}
}

namespace Microsoft
{
	namespace Xna
	{
		namespace Framework
		{
			namespace Graphics
			{
				class SpriteBatch;
			}
		}
	}
}


//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;



namespace CloudberryKingdom
{
	class MainRender
	{
	private:
		std::shared_ptr<GraphicsDevice> MyGraphicsDevice;
	public:
		float SpriteScaling;

		Viewport MainViewport;

		bool UsingSpriteBatch;
		std::shared_ptr<SpriteBatch> MySpriteBatch;


		MainRender( const std::shared_ptr<GraphicsDevice> &Device );

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

	private:
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef MAINRENDER
