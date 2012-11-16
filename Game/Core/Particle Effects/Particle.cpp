#include <global_header.h>







namespace CloudberryKingdom
{

	ParticleBin::ParticleBin()
	{
		MyStack = std::stack<Particle*>( 1000 );

		for ( int i = 0; i < 1000; i++ )
			MyStack.push( std::make_shared<Particle>() );
	}

	std::shared_ptr<Particle> ParticleBin::Get()
	{
		std::shared_ptr<Particle> item = 0;

//C# TO C++ CONVERTER TODO TASK: There is no built-in support for multithreading in native C++:
		lock ( MyStack )
		{
			if ( MyStack.empty() )
				return std::make_shared<Particle>();

			item = MyStack.pop();
		}

		return item;
	}

	void ParticleBin::ReturnItem( const std::shared_ptr<Particle> &item )
	{
//C# TO C++ CONVERTER TODO TASK: There is no built-in support for multithreading in native C++:
		lock ( MyStack )
		{
			MyStack.push( item );
		}
	}

std::shared_ptr<ParticleBin> Particle::Pool = std::make_shared<ParticleBin>();

	void Particle::Recycle()
	{
		Pool->ReturnItem( this );
	}

	void Particle::Copy( const std::shared_ptr<Particle> &template_Renamed )
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

	void Particle::Phsx( const std::shared_ptr<Camera> &cam )
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
