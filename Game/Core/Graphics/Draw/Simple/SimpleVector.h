#ifndef SIMPLEVECTOR
#define SIMPLEVECTOR

#include <small_header.h>

//#include "Core/Animation/AnimationData_Vector.h"
//#include "Core/Graphics/VertexFormat.h"
//#include "Game/Tools/Tools.h"


#include "Core/Graphics/VertexFormat.h"

#include "Core/Animation/AnimationData_Vector.h"
#include "Core/Animation/AnimationData_Integer.h"

namespace CloudberryKingdom
{
	struct SimpleVector
	{

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
