#include <small_header.h>
#include "Core/PhsxData.h"



namespace CloudberryKingdom
{

	PhsxData::PhsxData( float pos_x, float pos_y, float vel_x, float vel_y, float acc_x, float acc_y )
	{
		Position = Vector2( pos_x, pos_y );
		Velocity = Vector2( vel_x, vel_y );
		Acceleration = Vector2( acc_x, acc_y );
	}

	void PhsxData::UpdatePosition()
	{
		Position += Velocity;
	}

	void PhsxData::Integrate()
	{
		Velocity += Acceleration;
		Position += Velocity;
	}

}
