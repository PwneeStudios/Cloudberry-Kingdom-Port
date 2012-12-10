#ifndef CLOSINGCIRCLE
#define CLOSINGCIRCLE

#include <global_header.h>

namespace CloudberryKingdom
{
	struct QuadClass;
}

namespace CloudberryKingdom
{
	struct Camera;
}

namespace CloudberryKingdom
{
	struct IPos;
}

namespace CloudberryKingdom
{
	struct ClosingCircle
	{
	
		std::shared_ptr<QuadClass> Circle;
		std::shared_ptr<Camera> MyCamera;

		std::shared_ptr<IPos> CenterObj;
		Vector2 CenterPos;

		float Speed;

	
		int FinishedCount;

		ClosingCircle( const std::shared_ptr<Camera> &camera, float Frames );
		ClosingCircle( const std::shared_ptr<Camera> &camera, float Frames, const std::shared_ptr<IPos> &Center );
		ClosingCircle( const std::shared_ptr<Camera> &camera, float Frames, Vector2 Center );

	
		void Init( const std::shared_ptr<Camera> &camera, float Frames );

		float angle;
	
		void UpdateCircle();

	
		bool Done;
	
		void Draw();

	
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef CLOSINGCIRCLE
