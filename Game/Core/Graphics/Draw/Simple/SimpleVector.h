#ifndef SIMPLEVECTOR
#define SIMPLEVECTOR

#include <global_header.h>

namespace CloudberryKingdom
{
	class SimpleVector
	{
	public:
		AnimationData AnimData;
		MyOwnVertexFormat Vertex;
		Vector2 Pos;

		SimpleVector();

		void RotateRight();

		void RotateLeft();

		void Release();
	};
}


#endif	//#ifndef SIMPLEVECTOR
