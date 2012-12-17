#ifndef PARTICLEEMITTER
#define PARTICLEEMITTER

#include <global_header.h>

namespace CloudberryKingdom
{
	struct ParticleEmitterBin
	{

	
		std::vector<boost::shared_ptr<ParticleEmitter> > MyStack;
		Mutex stackLock;

	
		ParticleEmitterBin();

		boost::shared_ptr<ParticleEmitter> Get();

		void ReturnItem( const boost::shared_ptr<ParticleEmitter> &item );
	};

	struct ParticleEmitter : public boost::enable_shared_from_this<ParticleEmitter>
	{

	
		static void InitializeStatics();

	
		static boost::shared_ptr<ParticleEmitterBin> Pool;

		boost::shared_ptr<EzTexture> MyTexture;

		Vector2 Position;
		int Delay;
		int Amount;
	
		int Count;
	
		int Index;

		boost::shared_ptr<Particle> ParticleTemplate;

		std::list<boost::shared_ptr<Particle> > Particles;

		int DisplacementRange;
		float VelRange;
		float VelBase;
		Vector2 VelDir;

		bool On;

		boost::shared_ptr<Level> MyLevel;

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

		void Absorb( const boost::shared_ptr<ParticleEmitter> &emitter );

		std::list<boost::shared_ptr<Particle> >::iterator KillParticle( const std::list<boost::shared_ptr<Particle> >::iterator &node );

		void EmitParticle( const boost::shared_ptr<Particle> &p );

		boost::shared_ptr<Particle> GetNewParticle( const boost::shared_ptr<Particle> &template_Renamed );

		void Draw();

		void Unfreeze( int code );

		void RestrictedUpdate( int code );

		void Phsx();
	};
}


#endif	//#ifndef PARTICLEEMITTER
