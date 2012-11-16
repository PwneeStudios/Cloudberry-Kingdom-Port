#include <global_header.h>

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
using namespace Microsoft::Xna::Framework;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;

namespace CloudberryKingdom
{

	ParticleEmitterBin::ParticleEmitterBin()
	{
		const int capacity = 20;
		MyStack = std::stack<ParticleEmitter*>( capacity );
		for ( int i = 0; i < capacity; ++i )
			MyStack.push( std::make_shared<ParticleEmitter>( 300 ) );
	}

	std::shared_ptr<ParticleEmitter> ParticleEmitterBin::Get()
	{
		std::shared_ptr<ParticleEmitter> item = 0;

//C# TO C++ CONVERTER TODO TASK: There is no built-in support for multithreading in native C++:
		lock ( MyStack )
		{
			if ( MyStack.empty() )
				return std::make_shared<ParticleEmitter>( 300 );

			item = MyStack.pop();
		}

		return item;
	}

	void ParticleEmitterBin::ReturnItem( const std::shared_ptr<ParticleEmitter> &item )
	{
//C# TO C++ CONVERTER TODO TASK: There is no built-in support for multithreading in native C++:
		lock ( MyStack )
		{
			MyStack.push( item );
		}
	}

std::shared_ptr<ParticleEmitterBin> ParticleEmitter::Pool = std::make_shared<ParticleEmitterBin>();

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
		Pool->ReturnItem( this );
	}

	ParticleEmitter::ParticleEmitter( int Capacity )
	{
		Init( Capacity );
	}

	void ParticleEmitter::Init( int capacity )
	{
		TotalCapacity = capacity;

		Count = Index = 0;

		Particles = std::list<Particle*>();

		MyTexture = Tools::TextureWad->TextureList[ 0 ];

		On = true;

		DisplacementRange = 0;
		VelRange = 5;
		VelBase = 2;
		VelDir = Vector2( 0, 0 );

		ParticleTemplate = std::make_shared<Particle>();
		ParticleTemplate->Init();
		ParticleTemplate->SetSize( 150 );
		ParticleTemplate->Life = 200;
	}

	void ParticleEmitter::Clean()
	{
		for ( std::list<Particle*>::const_iterator p = Particles.begin(); p != Particles.end(); ++p )
			( *p )->Recycle();
		Particles.clear();
	}

	void ParticleEmitter::Absorb( const std::shared_ptr<ParticleEmitter> &emitter )
	{
		for ( std::list<Particle*>::const_iterator p = emitter->Particles.begin(); p != emitter->Particles.end(); ++p )
			Particles.push_back( *p );
		emitter->Particles.clear();
	}

	void ParticleEmitter::KillParticle( const std::shared_ptr<LinkedListNode<Particle*> > &node )
	{
		Particles.remove( node );
		node->Value.Recycle();
	}

	void ParticleEmitter::EmitParticle( const std::shared_ptr<Particle> &p )
	{
		Particles.push_back( p );
	}

	std::shared_ptr<Particle> ParticleEmitter::GetNewParticle( const std::shared_ptr<Particle> &template_Renamed )
	{
		std::shared_ptr<CloudberryKingdom::Particle> p = Particle::Pool->Get();
		p->Copy( template_Renamed );

		Particles.push_back( p );

		if ( Particles.size() > TotalCapacity )
			KillParticle( Particles.First );

		return p;
	}

	void ParticleEmitter::Draw()
	{
		if ( Tools::Render->UsingSpriteBatch )
			Tools::Render->EndSpriteBatch();

		for ( std::list<Particle*>::const_iterator p = Particles.begin(); p != Particles.end(); ++p )
			( *p )->Draw();
		Tools::QDrawer->Flush();
	}

	void ParticleEmitter::Unfreeze( int code )
	{
		for ( std::list<Particle*>::const_iterator p = Particles.begin(); p != Particles.end(); ++p )
			if ( ( *p )->Code == code )
				( *p )->Frozen = false;
	}

	void ParticleEmitter::RestrictedUpdate( int code )
	{
		for ( std::list<Particle*>::const_iterator p = Particles.begin(); p != Particles.end(); ++p )
			if ( ( *p )->Code == code )
				( *p )->Phsx( Tools::CurLevel->getMainCamera() );
	}

	void ParticleEmitter::Phsx()
	{
		UpdateStep();

//C# TO C++ CONVERTER TODO TASK: There is no equivalent to implicit typing in C++ unless the C++11 inferred typing option is selected:
		var node = Particles.First;
		while ( node != 0 )
		{
//C# TO C++ CONVERTER TODO TASK: There is no equivalent to implicit typing in C++ unless the C++11 inferred typing option is selected:
			var p = node->Value;
//C# TO C++ CONVERTER TODO TASK: There is no equivalent to implicit typing in C++ unless the C++11 inferred typing option is selected:
			var next = node->Next;

			if ( p->Life > 0 ) // && p.MyColor.W > 0)
				p->Phsx( Tools::CurLevel->getMainCamera() );
			else
				KillParticle( node );

			node = next;
		}
	}
}
