#ifndef PARTICLE
#define PARTICLE

#include <global_header.h>

#include "Hacks/Mutex.h"

namespace CloudberryKingdom
{
	struct ParticleBin
	{

	
		std::vector<boost::shared_ptr<Particle> > MyStack;
		Mutex stackLock;

	
		ParticleBin();

		boost::shared_ptr<Particle> Get();

		void ReturnItem( const boost::shared_ptr<Particle> &item );

	};

	struct Particle : public boost::enable_shared_from_this<Particle>
	{

		Particle();
	
		static void InitializeStatics();

	
		static boost::shared_ptr<ParticleBin> Pool;

		void Recycle();

		void Copy( const boost::shared_ptr<Particle> &template_Renamed );

		bool Frozen;
		int Code;
		bool KillOffSides, KillOffBottom;

		bool FadingIn;
		float FadeInTargetAlpha;

		PhsxData Data;
		Vector2 Size, SizeSpeed;
		float Angle, AngleSpeed;
		int Life;

		bool UseAttraction;
		Vector2 AttractionPoint;
		float AttractionStrength;

		Vector4 ColorVel, FadeInColorVel;
		Vector4 MyColor;

		SimpleQuad MyQuad;
		BasePoint Base;

		void Init();

		void UpdateQuad();

		void SetSize( float size );

		void Phsx( const boost::shared_ptr<Camera> &cam );

		void Draw();
	};
}


#endif	//#ifndef PARTICLE
