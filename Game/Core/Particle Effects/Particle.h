#ifndef PARTICLE
#define PARTICLE

#include "../Core/PhsxData.h"
#include "../Core/Graphics/Draw/Simple/SimpleQuad.h"
#include "../Core/Graphics/Draw/Simple/BasePoint.h"
#include "../Game/Collision Detection/Phsx.h"
#include <stack>
#include <cmath>

namespace CloudberryKingdom
{
	class Particle;
}

namespace CloudberryKingdom
{
	class Camera;
}


//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
using namespace Microsoft::Xna::Framework;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;

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
