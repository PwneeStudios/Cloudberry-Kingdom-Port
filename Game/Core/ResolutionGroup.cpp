#include <small_header.h>
#include "Core/ResolutionGroup.h"

#include "Game/Tools/IntVector2.h"
#include "Game/Tools/Tools.h"


namespace CloudberryKingdom
{

	ResolutionGroup::ResolutionGroup()
	{
		LineHeightMod = 1;
	}

	ResolutionGroup::~ResolutionGroup()
	{
	}

	boost::shared_ptr<DisplayMode> ResolutionGroup::LastSetMode = 0;

	IntVector2 ResolutionGroup::SafeResolution( int width, int height )
	{
		/*bool MatchingFound = false;
		int SuitableY = -1;

		// Make sure this is a supported resolution
		for ( Microsoft::Xna::Framework::Graphics::DisplayModeCollection::const_iterator mode = GraphicsAdapter::DefaultAdapter->SupportedDisplayModes.begin(); mode != GraphicsAdapter::DefaultAdapter->SupportedDisplayModes.end(); ++mode )
		{
			if ( ( *mode )->Width == width )
			{
				if ( ( *mode )->Height == height )
				{
					MatchingFound = true;
					break;
				}
				else
					SuitableY = ( *mode )->Height;
			}
		}

		if ( !MatchingFound )
		{
			if ( SuitableY > 0 )
				height = SuitableY;
			else
			{
				width = GraphicsAdapter::DefaultAdapter->CurrentDisplayMode->Width;
				height = GraphicsAdapter::DefaultAdapter->CurrentDisplayMode->Height;
			}
		}

		return IntVector2( width, height );*/
		return IntVector2( 1280, 720 );
	}

	void ResolutionGroup::Use( const boost::shared_ptr<DisplayMode> &mode )
	{
		/*LastSetMode = mode;
		Use( mode->Width, mode->Height );*/
	}

	void ResolutionGroup::Use( int width, int height )
	{
		//Use( width, height, true );
	}

	void ResolutionGroup::Use( int width, int height, bool AllowModifications )
	{
	/*#if defined(WINDOWS)
		Vector2 save = Tools::getMousePos();
	#endif
		if ( AllowModifications )
			if ( Tools::TheGame->MyGraphicsDeviceManager->IsFullScreen )
			{
				CloudberryKingdom::IntVector2 safe = SafeResolution( width, height );
				width = safe.X;
				height = safe.Y;
			}
			else
				// Trim excess
				height = static_cast<int>( ( 720.f / 1280.f ) * width );

		Tools::TheGame->MyGraphicsDeviceManager->PreferredBackBufferWidth = width;
		Tools::TheGame->MyGraphicsDeviceManager->PreferredBackBufferHeight = height;
		Tools::TheGame->MyGraphicsDeviceManager->ApplyChanges();
		Tools::Render->MakeInnerViewport();

	#if defined(WINDOWS) 
		Tools::setMousePos( save );
	#endif*/
	}

	void ResolutionGroup::Use()
	{
		/*int width = Backbuffer.X, height = Backbuffer.Y;
		if ( !Tools::TheGame->MyGraphicsDeviceManager->IsFullScreen )
		{
			height = static_cast<int>( ( 720.f / 1280.f ) * width );
		}

		Tools::TheGame->MyGraphicsDeviceManager->PreferredBackBufferWidth = width;
		Tools::TheGame->MyGraphicsDeviceManager->PreferredBackBufferHeight = height;
		Tools::TheGame->MyGraphicsDeviceManager->ApplyChanges();
		Tools::Render->MakeInnerViewport();*/
	}

	std::wstring ResolutionGroup::ToString()
	{
		return std::wstring( L"FIXME" );
		/*return Backbuffer.X + std::wstring( L" x " ) + Backbuffer.Y;*/
	}

	void ResolutionGroup::CopyTo( ResolutionGroup &dest )
	{
		/*dest.Backbuffer = Backbuffer;
		dest.Bob_Renamed = Bob_Renamed;

		dest.TextOrigin = TextOrigin;
		dest.LineHeightMod = LineHeightMod;*/
	}

	void ResolutionGroup::CopyTo( ResolutionGroup &dest, Vector2 scale )
	{
		/*dest.Backbuffer = Backbuffer * scale;
		dest.Bob_Renamed = Bob_Renamed * scale;

		dest.TextOrigin = TextOrigin - scale;
		dest.LineHeightMod = LineHeightMod * scale.Y;*/
	}
}
