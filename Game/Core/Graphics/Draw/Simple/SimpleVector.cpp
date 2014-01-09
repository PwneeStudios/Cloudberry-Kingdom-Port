#include <small_header.h>
#include "Core/Graphics/Draw/Simple/SimpleVector.h"

#include "Core/Animation/AnimationData_Vector.h"
#include "Core/Graphics/VertexFormat.h"
#include "Game/Tools/Tools.h"


namespace CloudberryKingdom
{

	SimpleVector::SimpleVector()
	{
	}

	void SimpleVector::RotateRight()
	{
		std::swap( Pos.X, Pos.Y );
		std::swap( Vertex.uv.X, Vertex.uv.X );
	}

	void SimpleVector::RotateLeft()
	{
		RotateRight();
		Pos.X *= -1;
		Vertex.uv.X *= -1;
	}

	void SimpleVector::Release()
	{
		AnimData.Release();
	}

}
