#ifndef FLOATRECTANGLE
#define FLOATRECTANGLE

#include "../Core/Tools/Set.h"

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::IO;
using namespace Microsoft::Xna::Framework;

namespace CloudberryKingdom
{
	class FloatRectangle
	{
	public:
		Vector2 TR, BL, Center, Size;

		FloatRectangle();

		FloatRectangle( Vector2 center, Vector2 size );

		void Clone( const std::shared_ptr<FloatRectangle> &A );

		void Write( const std::shared_ptr<BinaryWriter> &writer );
		void Read( const std::shared_ptr<BinaryReader> &reader );

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
