#ifndef FLOATRECTANGLE
#define FLOATRECTANGLE

#include <small_header.h>

//#include "Core/WriteReadTools.h"
//#include "Game/Tools/Tools.h"
#include "Hacks/XNA/Rectangle.h"

namespace CloudberryKingdom
{
	struct FloatRectangle
	{
	
		Vector2 TR, BL, Center, Size;

		FloatRectangle();

		FloatRectangle( Vector2 center, Vector2 size );

		void Clone( const boost::shared_ptr<FloatRectangle> &A );

		void Write( const boost::shared_ptr<BinaryWriter> &writer );
		void Read( const boost::shared_ptr<BinaryReader> &reader );

		float BoxSize();

		Vector2 TL();
		Vector2 BR();

		Rectangle GetIntRectangle();

		void Set( Vector2 center, Vector2 size );

		void CalcBounds();

		void FromBounds();

		void Scale( float scale );
	};
}


#endif	//#ifndef FLOATRECTANGLE
