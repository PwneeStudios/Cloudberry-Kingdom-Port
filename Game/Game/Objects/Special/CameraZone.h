#ifndef CAMERAZONE
#define CAMERAZONE

#include <global_header.h>

namespace CloudberryKingdom
{

	struct CameraZone : public ZoneTrigger
	{
	
		virtual ~CameraZone()
		{
#ifdef BOOST_BIN
			OnDestructor( "CameraZone" );
#endif
		}


		struct ZoneTriggerLambda : public Lambda_1<boost::shared_ptr<ZoneTrigger> >
		{
		
			boost::shared_ptr<CameraZone> zt;
		
			ZoneTriggerLambda( const boost::shared_ptr<CameraZone> &zt );

			void Apply( const boost::shared_ptr<ZoneTrigger> &trig );
		};

	
		bool Activated;
		bool SnapNext;

		int Priority;

		float Zoom;
		Vector2 Start, End;

		bool FreeY;
		float FreeY_MaxY, FreeY_MinY;

		//public float CameraSpeedVel = .5f;
		//public float CameraTargetSpeed = 30f;
		float CameraSpeed; //30 for normal // 45 for the wheel
		bool SetCameraSpeed;
		Camera_PhsxType CameraType;

		virtual void MakeNew();

		CameraZone();

		void Init( Vector2 center, Vector2 size );

		virtual void PhsxStep();

		virtual void PhsxStep2();

		Vector2 GetProjectedPos( Vector2 x );

		Vector2 FromProjected( Vector2 x );

		void SetZoom( const boost::shared_ptr<Camera> &cam );

		void Enforce( const boost::shared_ptr<Camera> &cam );


		virtual void Move( Vector2 shift );

		virtual void Clone( const boost::shared_ptr<ObjectBase> &A );
	};

}


#endif	//#ifndef CAMERAZONE
