#ifndef PHSXDATA
#define PHSXDATA

namespace CloudberryKingdom
{
	class PhsxData
	{
	public:
		Vector2 Position, Velocity, Acceleration;

		PhsxData() { }

		PhsxData( float pos_x, float pos_y, float vel_x, float vel_y, float acc_x, float acc_y );

		void UpdatePosition();

		void Integrate();
	};
}


#endif	//#ifndef PHSXDATA
