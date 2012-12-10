#ifndef PARTICLE
#define PARTICLE

#include <global_header.h>

#include "Hacks/Mutex.h"

namespace CloudberryKingdom
{
	class ParticleBin
	{

	private:
		std::vector<std::shared_ptr<Particle> > MyStack;
		Mutex stackLock;

	public:
		ParticleBin();

		std::shared_ptr<Particle> Get();

		void ReturnItem( const std::shared_ptr<Particle> &item );

	};

	class Particle : public std::enable_shared_from_this<Particle>
	{

	public:
		static void InitializeStatics();

	public:
		static std::shared_ptr<ParticleBin> Pool;

		void Recycle();

		void Copy( const std::shared_ptr<Particle> &template_Renamed );

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

		void Phsx( const std::shared_ptr<Camera> &cam );

		void Draw();
	};
}


#endif	//#ifndef PARTICLE
