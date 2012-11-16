#ifndef SIMPLEBOX
#define SIMPLEBOX

#include "SimpleVector.h"
#include "BasePoint.h"

namespace CloudberryKingdom
{
	class ObjectBox;
}


//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;
using namespace Microsoft::Xna::Framework;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::IO;

namespace CloudberryKingdom
{
	class SimpleBox
	{
	public:
		bool Animated;
		SimpleVector BL, TR;

		void Release();

		void SetHold();

		void ReadAnim( int anim, int frame );

		void Record( int anim, int frame );

		void Transfer( int anim, float DestT, int AnimLength, bool Loop, bool Linear, float t );

		void Calc( int anim, float t, int AnimLength, bool Loop, bool Linear );

		SimpleBox( const std::shared_ptr<SimpleBox> &box );

		SimpleBox( const std::shared_ptr<ObjectBox> &box );

		/// <summary>
		/// Copy and shift the source boxes's vertex locations.
		/// </summary>
		/// <param name="SourceBox">The source box</param>
		/// <param name="shift">The amount to shift</param>
		void CopyUpdate( std::shared_ptr<SimpleBox> &SourceBox, Vector2 &shift );

		void Update( BasePoint &Base );

		Vector2 Center();

		float Width( BasePoint &Base );

		Vector2 Size();

		/*        public void DrawExtra(QuadDrawer Drawer, Color clr)
		        {
		            Drawer.DrawLine(BL.Pos, new Vector2(TR.Pos.X, BL.Pos.Y), clr, .02f);
		            Drawer.DrawLine(BL.Pos, new Vector2(BL.Pos.X, TR.Pos.Y), clr, .02f);
		            Drawer.DrawLine(TR.Pos, new Vector2(TR.Pos.X, BL.Pos.Y), clr, .02f);
		            Drawer.DrawLine(TR.Pos, new Vector2(BL.Pos.X, TR.Pos.Y), clr, .02f);
		        }
		  */
	};
}


#endif	//#ifndef SIMPLEBOX
