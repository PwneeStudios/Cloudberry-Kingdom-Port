#ifndef RESOLUTIONGROUP
#define RESOLUTIONGROUP

#include <global_header.h>

#include "Hacks/XNA/DisplayMode.h"

namespace CloudberryKingdom
{
	class ResolutionGroup
	{
	public:
		ResolutionGroup();

		static std::shared_ptr<DisplayMode> LastSetMode;

		static IntVector2 SafeResolution( int width, int height );

		static void Use( const std::shared_ptr<DisplayMode> &mode );

		static void Use( int width, int height );
		static void Use( int width, int height, bool AllowModifications );

		void Use();

//C# TO C++ CONVERTER NOTE: The variable Bob was renamed since it is named the same as a user-defined type:
		IntVector2 Backbuffer, Bob_Renamed;

		Vector2 TextOrigin;
		float LineHeightMod;

		virtual std::wstring ToString();

		void CopyTo( ResolutionGroup &dest );

		void CopyTo( ResolutionGroup &dest, Vector2 scale );
	};
}


#endif	//#ifndef RESOLUTIONGROUP
