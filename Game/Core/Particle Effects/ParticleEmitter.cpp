#include <small_header.h>
#include "Core/Particle Effects/ParticleEmitter.h"

#include "Core/Particle Effects/Particle.h"
#include "Core/Texture/EzTexture.h"
#include "Game/Objects/In Game Objects/Grab/MakeData.h"
#include "Game/Level/Level.h"
#include "Game/Tools/Recycler.h"
#include "Game/Tools/Tools.h"

#include <Game/CloudberryKingdom/CloudberryKingdom.CloudberryKingdomGame.h>
#include "Core/Texture/EzTextureWad.h"

namespace CloudberryKingdom
{

	void ParticleEmitter::InitializeStatics()
	{
		ParticleEmitter::Pool = boost::make_shared<ParticleEmitterBin>();
	}
	
	// Statis
	boost::shared_ptr<ParticleEmitterBin> ParticleEmitter::Pool;


	ParticleEmitterBin::ParticleEmitterBin()
	{
		const int capacity = 20;
		MyStack = std::vector<boost::shared_ptr<ParticleEmitter> >( capacity );
		for ( int i = 0; i < capacity; ++i )
			MyStack[i] = boost::make_shared<ParticleEmitter>( 300 );
	}

	boost::shared_ptr<ParticleEmitter> ParticleEmitterBin::Get()
	{
		boost::shared_ptr<ParticleEmitter> item = 0;

//C# TO C++ CONVERTER TODO TASK: There is no built-in support for multithreading in native C++:
		//lock ( MyStack )
		{
			stackLock.Lock();

			if ( MyStack.empty() )
			{
				stackLock.Unlock();
				return boost::make_shared<ParticleEmitter>( 300 );
			}

			item = MyStack.back();
			MyStack.pop_back();

			stackLock.Unlock();
		}

		return item;
	}

	void ParticleEmitterBin::ReturnItem( const boost::shared_ptr<ParticleEmitter> &item )
	{
//C# TO C++ CONVERTER TODO TASK: There is no built-in support for multithreading in native C++:
		//lock ( MyStack )
		{
			stackLock.Lock();

			MyStack.push_back( item );

			stackLock.Unlock();
		}
	}

	bool ParticleEmitter::IsActive()
	{
		return Tools::TheGame->DrawCount == LastActiveStep;
	}

	void ParticleEmitter::UpdateStep()
	{
		LastActiveStep = Tools::TheGame->DrawCount;
	}

	void ParticleEmitter::Release()
	{
		MyLevel.reset();
		Clean();
		Pool->ReturnItem( shared_from_this() );
	}

	ParticleEmitter::ParticleEmitter( int Capacity )
	{
		Init( Capacity );
	}

	void ParticleEmitter::Init( int capacity )
	{
		TotalCapacity = capacity;

		Count = Index = 0;

		Particles = std::list<boost::shared_ptr<Particle> >();

		MyTexture = Tools::TextureWad->TextureList[ 0 ];

		On = true;

		DisplacementRange = 0;
		VelRange = 5;
		VelBase = 2;
		VelDir = Vector2( 0, 0 );

		ParticleTemplate = boost::make_shared<Particle>();
		ParticleTemplate->Init();
		ParticleTemplate->SetSize( 150 );
		ParticleTemplate->Life = 200;
	}

	void ParticleEmitter::Clean()
	{
		for ( std::list<boost::shared_ptr<Particle> >::const_iterator p = Particles.begin(); p != Particles.end(); ++p )
			( *p )->Recycle();
		Particles.clear();
	}

	void ParticleEmitter::Absorb( const boost::shared_ptr<ParticleEmitter> &emitter )
	{
		for ( std::list<boost::shared_ptr<Particle> >::const_iterator p = emitter->Particles.begin(); p != emitter->Particles.end(); ++p )
			Particles.push_back( *p );
		emitter->Particles.clear();
	}

	std::list<boost::shared_ptr<Particle> >::iterator ParticleEmitter::KillParticle( const std::list<boost::shared_ptr<Particle> >::iterator &node )
	{
		boost::shared_ptr<Particle> p = *node;
		p->Recycle();
		return Particles.erase( node );
	}

	void ParticleEmitter::EmitParticle( const boost::shared_ptr<Particle> &p )
	{
		Particles.push_back( p );
	}

	boost::shared_ptr<Particle> ParticleEmitter::GetNewParticle( const boost::shared_ptr<Particle> &template_Renamed )
	{
		boost::shared_ptr<CloudberryKingdom::Particle> p = Particle::Pool->Get();
		p->Copy( template_Renamed );

		Particles.push_back( p );

		if ( static_cast<int>( Particles.size() ) > TotalCapacity )
			KillParticle( Particles.begin() );

		return p;
	}

	void ParticleEmitter::Draw()
	{
		if ( Tools::Render->UsingSpriteBatch )
			Tools::Render->EndSpriteBatch();

		for ( std::list<boost::shared_ptr<Particle> >::const_iterator p = Particles.begin(); p != Particles.end(); ++p )
			( *p )->Draw();
		Tools::QDrawer->Flush();
	}

	void ParticleEmitter::Unfreeze( int code )
	{
		for ( std::list<boost::shared_ptr<Particle> >::const_iterator p = Particles.begin(); p != Particles.end(); ++p )
			if ( ( *p )->Code == code )
				( *p )->Frozen = false;
	}

	void ParticleEmitter::RestrictedUpdate( int code )
	{
		for ( std::list<boost::shared_ptr<Particle> >::const_iterator p = Particles.begin(); p != Particles.end(); ++p )
			if ( ( *p )->Code == code )
				( *p )->Phsx( Tools::CurLevel->getMainCamera() );
	}

	void ParticleEmitter::Phsx()
	{
		UpdateStep();

		// FIXME: Check update loop logic.

//C# TO C++ CONVERTER TODO TASK: There is no equivalent to implicit typing in C++ unless the C++11 inferred typing option is selected:
		std::list<boost::shared_ptr<Particle> >::iterator node = Particles.begin();
		while ( node != Particles.end() )
		{
//C# TO C++ CONVERTER TODO TASK: There is no equivalent to implicit typing in C++ unless the C++11 inferred typing option is selected:
			boost::shared_ptr<Particle> &p = *node;
//C# TO C++ CONVERTER TODO TASK: There is no equivalent to implicit typing in C++ unless the C++11 inferred typing option is selected:
			//var next = node->Next;

			if ( p->Life > 0 ) // && p.MyColor.W > 0)
			{
				p->Phsx( Tools::CurLevel->getMainCamera() );
				++node;
			}
			else
				node = KillParticle( node );
		}
	}
}
