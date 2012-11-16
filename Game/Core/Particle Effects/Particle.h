#ifndef PARTICLE
#define PARTICLE

#include <global_header.h>

namespace CloudberryKingdom
{
	class Particle;
}

namespace CloudberryKingdom
{
	class Camera;
}



namespace CloudberryKingdom
{
	class ParticleBin
	{
	private:
		std::stack<Particle*> MyStack;

	public:
		ParticleBin();

		std::shared_ptr<Particle> Get();

		void ReturnItem( const std::shared_ptr<Particle> &item );
	};

	class Particle
	{
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
