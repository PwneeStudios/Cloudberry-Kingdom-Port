#ifndef PARTICLEEMITTER
#define PARTICLEEMITTER

#include "../Game/Collision Detection/Phsx.h"
#include <list>
#include <stack>

namespace CloudberryKingdom
{
	class ParticleEmitter;
}

namespace CloudberryKingdom
{
	class EzTexture;
}

namespace CloudberryKingdom
{
	class Particle;
}

namespace CloudberryKingdom
{
	class Level;
}


//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
using namespace Microsoft::Xna::Framework;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;

namespace CloudberryKingdom
{
	class ParticleEmitterBin
	{
	private:
		std::stack<ParticleEmitter*> MyStack;

	public:
		ParticleEmitterBin();

		std::shared_ptr<ParticleEmitter> Get();

		void ReturnItem( const std::shared_ptr<ParticleEmitter> &item );
	};

	class ParticleEmitter
	{
	public:
		static std::shared_ptr<ParticleEmitterBin> Pool;

		std::shared_ptr<EzTexture> MyTexture;

		Vector2 Position;
		int Delay;
		int Amount;
	private:
		int Count;
	public:
		int Index;

		std::shared_ptr<Particle> ParticleTemplate;

		std::list<Particle*> Particles;

		int DisplacementRange;
		float VelRange;
		float VelBase;
		Vector2 VelDir;

		bool On;

		std::shared_ptr<Level> MyLevel;

		int LastActiveStep; // Tracks the last RealTime step the emitter was active
		bool IsActive();
	private:
		void UpdateStep();

	public:
		void Release();

		int TotalCapacity;
		ParticleEmitter( int Capacity );

	private:
		void Init( int capacity );

		/// <summary>
		/// Clear all particles.
		/// </summary>
	public:
		void Clean();

		void Absorb( const std::shared_ptr<ParticleEmitter> &emitter );

		void KillParticle( const std::shared_ptr<LinkedListNode<Particle*> > &node );

		void EmitParticle( const std::shared_ptr<Particle> &p );

		std::shared_ptr<Particle> GetNewParticle( const std::shared_ptr<Particle> &template_Renamed );

		void Draw();

		void Unfreeze( int code );

		void RestrictedUpdate( int code );

		void Phsx();
	};
}


#endif	//#ifndef PARTICLEEMITTER
