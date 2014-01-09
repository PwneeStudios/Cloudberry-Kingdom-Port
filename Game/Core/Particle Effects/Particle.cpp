#include <small_header.h>
#include "Core/Particle Effects/Particle.h"

#include "Core/PhsxData.h"
#include "Core/Graphics/Draw/Simple/BasePoint.h"
#include "Core/Graphics/Draw/Simple/SimpleQuad.h"
#include "Game/Tools/Camera.h"
#include "Game/Tools/Recycler.h"
#include "Game/Tools/Tools.h"
#include "Game/Level/Level.h"

namespace CloudberryKingdom
{

	Particle::Particle() :
		Frozen( false ),
		Code( 0 ),
		KillOffSides( false ), KillOffBottom( false ),
		FadingIn( false ),
		FadeInTargetAlpha( 0 ),
		Angle( 0 ), AngleSpeed( 0 ),
		Life( 0 ),
		UseAttraction( false ),
		AttractionStrength( 0 )
	{
	}

	void Particle::InitializeStatics()
	{
		Particle::Pool = boost::make_shared<ParticleBin>();
	}

	// Statics
	boost::shared_ptr<ParticleBin> Particle::Pool;


	ParticleBin::ParticleBin()
	{
		MyStack = std::vector<boost::shared_ptr<Particle> >( 1000 );

		for ( int i = 0; i < 1000; i++ )
			MyStack[ i ] = boost::make_shared<Particle>();
	}

	boost::shared_ptr<Particle> ParticleBin::Get()
	{
		boost::shared_ptr<Particle> item = 0;

//C# TO C++ CONVERTER TODO TASK: There is no built-in support for multithreading in native C++:
		//lock ( MyStack )
		{
			stackLock.Lock();

			if ( MyStack.empty() )
			{
				stackLock.Unlock();
				return boost::make_shared<Particle>();
			}

			item = MyStack.back();
			MyStack.pop_back();

			stackLock.Unlock();
		}

		return item;
	}

	void ParticleBin::ReturnItem( const boost::shared_ptr<Particle> &item )
	{
//C# TO C++ CONVERTER TODO TASK: There is no built-in support for multithreading in native C++:
		//lock ( MyStack )
		{
			stackLock.Lock();

			MyStack.push_back( item );
			
			stackLock.Unlock();
		}
	}

	void Particle::Recycle()
	{
		Pool->ReturnItem( shared_from_this() );
	}

	void Particle::Copy( const boost::shared_ptr<Particle> &template_Renamed )
	{
		Frozen = template_Renamed->Frozen;
		Code = template_Renamed->Code;
		KillOffSides = template_Renamed->KillOffSides;
		KillOffBottom = template_Renamed->KillOffBottom;

		FadingIn = template_Renamed->FadingIn;
		FadeInTargetAlpha = template_Renamed->FadeInTargetAlpha;

		Data = template_Renamed->Data;
		Size = template_Renamed->Size;
		SizeSpeed = template_Renamed->SizeSpeed;
		Angle = template_Renamed->Angle;
		AngleSpeed = template_Renamed->AngleSpeed;
		Life = template_Renamed->Life;

		UseAttraction = template_Renamed->UseAttraction;
		AttractionPoint = template_Renamed->AttractionPoint;
		AttractionStrength = template_Renamed->AttractionStrength;

		ColorVel = template_Renamed->ColorVel;
		FadeInColorVel = template_Renamed->FadeInColorVel;
		MyColor = template_Renamed->MyColor;

		MyQuad = template_Renamed->MyQuad;
		Base = template_Renamed->Base;
	}

	void Particle::Init()
	{
		MyQuad.Init();
		MyQuad.MyEffect = Tools::BasicEffect;
	}

	void Particle::UpdateQuad()
	{
		Base.Origin = Data.Position;
		float c = static_cast<float>( cos( Angle ) );
		float s = static_cast<float>( sin( Angle ) );
		Base.e1 = Size.X * Vector2( c, s );
		Base.e2 = Size.Y * Vector2( -s, c );

		MyQuad.SymmetricUpdate( Base );
	}

	void Particle::SetSize( float size )
	{
		Size.X = Size.Y = size;
	}

	void Particle::Phsx( const boost::shared_ptr<Camera> &cam )
	{
		if ( Frozen )
			return;

		if ( FadingIn )
		{
			MyColor += FadeInColorVel;
			if ( MyColor.W >= FadeInTargetAlpha )
				FadingIn = false;
		}
		else
			MyColor += ColorVel;

		Angle += AngleSpeed;
		Size += SizeSpeed;

		if ( UseAttraction )
		{
			Vector2 dif = AttractionPoint - Data.Position;
			dif.Normalize();
			Data.Velocity += dif * AttractionStrength;
		}
		else
			Data.Velocity += Data.Acceleration;

		Data.Position += Data.Velocity;
		Life -= 1;

		if ( KillOffSides )
		{
			if ( Data.Position.X + Size.X < cam->BL.X )
				Life = 0;
			if ( Data.Position.X - Size.X > cam->TR.X )
				Life = 0;
		}
		if ( KillOffBottom && Data.Position.Y + Size.Y < cam->BL.Y )
			Life = 0;
	}

	void Particle::Draw()
	{
		if ( KillOffSides )
		{
			if ( Data.Position.X - Size.X > Tools::CurLevel->getMainCamera()->TR.X )
				return;
			if ( Data.Position.X + Size.X < Tools::CurLevel->getMainCamera()->BL.X )
				return;
			if ( Data.Position.Y + Size.Y < Tools::CurLevel->getMainCamera()->BL.Y )
				return;
			if ( Data.Position.Y - Size.Y > Tools::CurLevel->getMainCamera()->TR.Y )
				return;
		}

		MyQuad.SetColor( Color( MyColor ) );

		UpdateQuad();
		Tools::QDrawer->DrawQuad_Particle( MyQuad );
	}
}
