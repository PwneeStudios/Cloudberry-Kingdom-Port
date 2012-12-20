#ifndef RESOLUTIONGROUP
#define RESOLUTIONGROUP

#include <global_header.h>

#include "Game/Tools/IntVector2.h"

#include "Hacks/XNA/DisplayMode.h"

namespace CloudberryKingdom
{
	struct ResolutionGroup
	{
	
		ResolutionGroup();

		static boost::shared_ptr<DisplayMode> LastSetMode;

		static IntVector2 SafeResolution( int width, int height );

		static void Use( const boost::shared_ptr<DisplayMode> &mode );

		static void Use( int width, int height );
		static void Use( int width, int height, bool AllowModifications );

		void Use();

		IntVector2 Backbuffer, Bob_Renamed;

		Vector2 TextOrigin;
		float LineHeightMod;

		virtual std::wstring ToString();

		void CopyTo( ResolutionGroup &dest );

		void CopyTo( ResolutionGroup &dest, Vector2 scale );
	};
}


#endif	//#ifndef RESOLUTIONGROUP
