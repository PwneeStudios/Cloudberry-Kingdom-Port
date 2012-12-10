#ifndef PARTICLEEMITTER
#define PARTICLEEMITTER

#include <global_header.h>

namespace CloudberryKingdom
{
	struct ParticleEmitterBin
	{

	
		std::vector<std::shared_ptr<ParticleEmitter> > MyStack;
		Mutex stackLock;

	
		ParticleEmitterBin();

		std::shared_ptr<ParticleEmitter> Get();

		void ReturnItem( const std::shared_ptr<ParticleEmitter> &item );
	};

	struct ParticleEmitter : public std::enable_shared_from_this<ParticleEmitter>
	{

	
		static void InitializeStatics();

	
		static std::shared_ptr<ParticleEmitterBin> Pool;

		std::shared_ptr<EzTexture> MyTexture;

		Vector2 Position;
		int Delay;
		int Amount;
	
		int Count;
	
		int Index;

		std::shared_ptr<Particle> ParticleTemplate;

		std::list<std::shared_ptr<Particle> > Particles;

		int DisplacementRange;
		float VelRange;
		float VelBase;
		Vector2 VelDir;

		bool On;

		std::shared_ptr<Level> MyLevel;

		int LastActiveStep; // Tracks the last RealTime step the emitter was active
		bool IsActive();
	
		void UpdateStep();

	
		void Release();

		int TotalCapacity;
		ParticleEmitter( int Capacity );

	
		void Init( int capacity );

		/// <summary>
		/// Clear all particles.
		/// </summary>
	
		void Clean();

		void Absorb( const std::shared_ptr<ParticleEmitter> &emitter );

		std::list<std::shared_ptr<Particle> >::iterator KillParticle( const std::list<std::shared_ptr<Particle> >::iterator &node );

		void EmitParticle( const std::shared_ptr<Particle> &p );

		std::shared_ptr<Particle> GetNewParticle( const std::shared_ptr<Particle> &template_Renamed );

		void Draw();

		void Unfreeze( int code );

		void RestrictedUpdate( int code );

		void Phsx();
	};
}


#endif	//#ifndef PARTICLEEMITTER
