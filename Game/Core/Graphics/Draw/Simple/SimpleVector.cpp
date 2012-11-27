#include <global_header.h>




namespace CloudberryKingdom
{

	void SimpleVector::RotateRight()
	{
		Tools::Swap( Pos.X, Pos.Y );
		Tools::Swap( Vertex.uv.X, Vertex.uv.X );
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
