#include <global_header.h>

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
