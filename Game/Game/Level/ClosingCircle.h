#ifndef CLOSINGCIRCLE
#define CLOSINGCIRCLE

#include <small_header.h>

//#include "Core/FancyVector2.h"
//#include "Core/Graphics/Draw/Quads/QuadClass.h"
//#include "Game/Tools/Camera.h"
//#include "Game/Tools/Tools.h"


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
	
		boost::shared_ptr<QuadClass> Circle;
		boost::shared_ptr<Camera> MyCamera;

		boost::shared_ptr<IPos> CenterObj;
		Vector2 CenterPos;

		float Speed;

	
		int FinishedCount;

		ClosingCircle( const boost::shared_ptr<Camera> &camera, float Frames );
		ClosingCircle( const boost::shared_ptr<Camera> &camera, float Frames, const boost::shared_ptr<IPos> &Center );
		ClosingCircle( const boost::shared_ptr<Camera> &camera, float Frames, Vector2 Center );

	
		void Init( const boost::shared_ptr<Camera> &camera, float Frames );

		float angle;
	
		void UpdateCircle();

	
		bool Done;
	
		void Draw();

	
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef CLOSINGCIRCLE
