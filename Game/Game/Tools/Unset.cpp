#include <global_header.h>

namespace CloudberryKingdom
{

	void Unset::InitializeStatics()
	{
		Unset::Int = -23232323;
		Unset::Float = -23232323.23232323f;
		Unset::Vector = Vector2( Unset::Float, Unset::Float );
	}

	// Statics
	int Unset::Int;
	float Unset::Float;
	Vector2 Unset::Vector;

}
