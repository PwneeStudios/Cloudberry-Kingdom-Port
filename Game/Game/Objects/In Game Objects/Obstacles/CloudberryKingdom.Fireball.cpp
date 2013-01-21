#include <global_header.h>

#include "Hacks/Queue.h"

#include "Graphics/Effect.h"
#include "Graphics/EffectTechnique.h"

#include <Game/CloudberryKingdom/CloudberryKingdom.CloudberryKingdomGame.h>

namespace CloudberryKingdom
{

	void Fireball::FireballTileInfo::InitializeInstanceFields()
	{
		Sprite = boost::make_shared<SpriteInfo>( boost::shared_ptr<TextureOrAnim>(), Vector2( 72, -1 ) );
	}

	boost::shared_ptr<Particle> Fireball::ExplodeTemplate, Fireball::EmitterTemplate;
	boost::shared_ptr<EzSound> Fireball::ExplodeSound;
	float Fireball::t = 0;
	boost::shared_ptr<Quad> Fireball::ShadeQuad = 0;
	boost::shared_ptr<EzTexture> Fireball::FireballTexture, Fireball::FlameTexture, Fireball::EmitterTexture, Fireball::BaseFireballTexture;
	boost::shared_ptr<RenderTarget2D> Fireball::FireballRenderTarget, Fireball::FlameRenderTarget, Fireball::EmitterRenderTarget = 0;
	int Fireball::DrawWidth = 0, Fireball::DrawHeight = 0;
	boost::shared_ptr<ParticleEmitter> Fireball::Fireball_Emitter, Fireball::Flame_Emitter, Fireball::Emitter_Emitter;

	void Fireball::PreInit()
	{
		FireballTexture = boost::make_shared<EzTexture>();
		FireballTexture->FromCode = true;
		FlameTexture = boost::make_shared<EzTexture>();
		FlameTexture->FromCode = true;
		EmitterTexture = boost::make_shared<EzTexture>();
		EmitterTexture->FromCode = true;

		FireballTexture->Name = std::wstring( L"FireballTexture" );
		EmitterTexture->Name = std::wstring( L"EmitterTexture" );

		Tools::TextureWad->AddEzTexture( FireballTexture );
		Tools::TextureWad->AddEzTexture( EmitterTexture );
	}

	void Fireball::InitRenderTargets( const boost::shared_ptr<GraphicsDevice> &device, const boost::shared_ptr<PresentationParameters> &pp, int Width, int Height )
	{
		DrawWidth = Width;
		DrawHeight = Height;
		FireballRenderTarget = boost::make_shared<RenderTarget2D>( device, DrawWidth, DrawHeight, false, pp->BackBufferFormat, pp->DepthStencilFormat, pp->MultiSampleCount, true );

		FlameRenderTarget = boost::make_shared<RenderTarget2D>( device, 300, 300, false, pp->BackBufferFormat, pp->DepthStencilFormat, pp->MultiSampleCount, true );

		EmitterRenderTarget = boost::make_shared<RenderTarget2D>( device, 300, 300, false, pp->BackBufferFormat, pp->DepthStencilFormat, pp->MultiSampleCount, true );


		ShadeQuad = boost::make_shared<Quad>();
		ShadeQuad->InitVertices();
		ShadeQuad->SetColor( Color( 1.f, 1.f, 1.f ) );
		ShadeQuad->MyEffect = Tools::EffectWad->FindByName( std::wstring( L"Fireball" ) );
		ShadeQuad->MyTexture = Tools::TextureWad->FindByName( std::wstring( L"White" ) );
		ShadeQuad->Scale( Vector2( 210 * 1.15f, 55 * 1.15f ) );

		ShadeQuad->Update();

		ExplodeSound = Tools::SoundWad->FindByName( std::wstring( L"DustCloud_Explode" ) );

		// Fireball particle emitter
		Fireball_Emitter = boost::make_shared<ParticleEmitter>( 20 );

		Fireball_Emitter->Position = Vector2( 55, 0 );
		Fireball_Emitter->Amount = 2;
		Fireball_Emitter->Delay = 1;

		Fireball_Emitter->DisplacementRange = 10;
		Fireball_Emitter->VelRange = 1;
		Fireball_Emitter->VelBase = .1f;
		Fireball_Emitter->VelDir = Vector2( -5, 0 );

		Fireball_Emitter->ParticleTemplate->MyQuad.UseGlobalIllumination = false;
		Fireball_Emitter->ParticleTemplate->MyQuad.setMyTexture( Tools::TextureWad->FindByName( std::wstring( L"Fireball" ) ) );
		Fireball_Emitter->ParticleTemplate->MyQuad.MyEffect = Tools::BasicEffect;
		Fireball_Emitter->ParticleTemplate->SetSize( 43 );
		Fireball_Emitter->ParticleTemplate->Life = 140;
		Fireball_Emitter->ParticleTemplate->MyColor = Vector4( 1,.7f,.7f,.75f );
		Fireball_Emitter->ParticleTemplate->ColorVel = Vector4( 0,.01f, 0, -.02f );
		Fireball_Emitter->ParticleTemplate->MyQuad.BlendAddRatio = 0;

		// Flame particle emitter
		Flame_Emitter = boost::make_shared<ParticleEmitter>( 40 );
		Flame_Emitter->Position = Vector2( 0, 0 );

		// Emitter particle emitter
		Emitter_Emitter = boost::make_shared<ParticleEmitter>( 40 );
		Emitter_Emitter->Position = Vector2( 0, 0 );


		BaseFireballTexture = Tools::TextureWad->FindByName( std::wstring( L"Fireball" ) );

		// Initialize explosion particle
		ExplodeTemplate = boost::make_shared<Particle>();
		ExplodeTemplate->MyQuad.Init();
		ExplodeTemplate->MyQuad.UseGlobalIllumination = false;
		ExplodeTemplate->MyQuad.MyEffect = Tools::BasicEffect;
		ExplodeTemplate->MyQuad.setMyTexture( FlameTexture );
		ExplodeTemplate->SetSize( 95 );
		ExplodeTemplate->SizeSpeed = Vector2( 5, 5 ); // new Vector2(5, 5);
		ExplodeTemplate->AngleSpeed = .035f;
		ExplodeTemplate->Life = 35;
		//ExplodeTemplate.MyColor = new Vector4(.96f, .94f, .94f, 1f);
		//ExplodeTemplate.ColorVel = new Vector4(0.00f, -0.007f, -0.007f, -.03f);
		ExplodeTemplate->MyColor = Vector4( 1, 1, 1, 1 );
		ExplodeTemplate->ColorVel = Vector4( 0.00f, -0.003f, -0.003f, -.03f );
		ExplodeTemplate->MyQuad.BlendAddRatio = 0;

		// Initialize emitter particle
		EmitterTemplate = boost::make_shared<Particle>();
		EmitterTemplate->MyQuad.Init();
		EmitterTemplate->MyQuad.UseGlobalIllumination = false;
		EmitterTemplate->MyQuad.MyEffect = Tools::BasicEffect; //Circle");
		EmitterTemplate->MyQuad.setMyTexture( Tools::TextureWad->FindByName( std::wstring( L"Fire" ) ) );
		EmitterTemplate->SetSize( 55 );
		EmitterTemplate->SizeSpeed = Vector2( 2, 2 );
		EmitterTemplate->AngleSpeed = .1f;
		EmitterTemplate->Life = 40;
		EmitterTemplate->MyColor = Vector4( .6f,.62f,.62f,.75f );
		EmitterTemplate->ColorVel = Vector4( 0.006f, -0.0002f, -0.0002f, -.03f );
		EmitterTemplate->MyQuad.BlendAddRatio = 0;
	}

	void Fireball::TexturePhsx()
	{
		boost::shared_ptr<Rand> Rnd = Tools::GlobalRnd;

		// Fireball superparticle physics
		Fireball_Emitter->Phsx();

		// Flame superparticle physics
		for ( int k = 0; k < 1; k++ )
		{
			boost::shared_ptr<CloudberryKingdom::Particle> p = Flame_Emitter->GetNewParticle( EmitterTemplate );
			Vector2 Dir = Rnd->RndDir();
			p->Data.Position = 20 * Dir; //+ Tools::CurLevel.MainCamera.Data.Position;
			//p.Data.Velocity = 4 * (float)MyLevel.Rnd.Rnd.NextDouble() * Dir;
			p->Data.Velocity = 8.5f * static_cast<float>( Rnd->Rnd->NextDouble() ) * Dir;
			p->Data.Acceleration -= .07f * p->Data.Velocity;
			p->AngleSpeed *= 2 * static_cast<float>( Rnd->Rnd->NextDouble() - .5f );
			p->ColorVel.W *= static_cast<float>( .3f * Rnd->Rnd->NextDouble() + .7f );
		}
		Flame_Emitter->Phsx();

		// Emitter superparticle physics
		ParticleEffects::Flame( Emitter_Emitter, Vector2(), Tools::TheGame->DrawCount, 1, 20, false );
		Emitter_Emitter->Phsx();
	}

	void Fireball::DrawFireballTexture( const boost::shared_ptr<GraphicsDevice> &device, const boost::shared_ptr<EzEffectWad> &EffectWad )
	{
		// FIXME
		FireballTexture->_Tex = Tools::TextureWad->TextureList[0]->_Tex;
		return;


		t += 1.f / 60.f;

		device->SetRenderTarget( FireballRenderTarget );
		device->Clear( Color::Transparent );
		float scalex = 350;
		float scaley = 150;

		ShadeQuad->MyEffect->effect->CurrentTechnique = ShadeQuad->MyEffect->Simplest;
		Tools::EffectWad->SetCameraPosition( Vector4( 0, 0, 1 / scalex, 1 / scaley ) );
		ShadeQuad->MyEffect->xCameraAspect->SetValue( 1.f );


		float TimeScale = 4;

		ShadeQuad->SetColor( Color::White );
		ShadeQuad->MyEffect->t->SetValue( t / TimeScale );
		if ( Tools::DrawCount > 5 )
		ShadeQuad->MyTexture = EmitterTexture;
		else
		ShadeQuad->MyTexture = BaseFireballTexture;
		Tools::QDrawer->DrawQuad( ShadeQuad );
		Tools::QDrawer->Flush();

		ShadeQuad->MyEffect->t->SetValue( t / TimeScale + 150 );
		Tools::QDrawer->DrawQuad( ShadeQuad );
		Tools::QDrawer->Flush();

		ShadeQuad->MyEffect->t->SetValue( t / TimeScale + 300 );
		Tools::QDrawer->DrawQuad( ShadeQuad );
		Tools::QDrawer->Flush();

		device->SetRenderTarget( Tools::DestinationRenderTarget );
		Tools::Render->ResetViewport();

		FireballTexture->setTex( FireballRenderTarget );

		// Save to file
		//FireballTexture.Tex.Save(string.Format("Fireball_{0}.png", Tools::DrawCount), ImageFileFormat.Png);
	}

	void Fireball::DrawEmitterTexture( const boost::shared_ptr<GraphicsDevice> &device, const boost::shared_ptr<EzEffectWad> &EffectWad )
	{
		// FIXME
		FlameTexture->_Tex = Tools::TextureWad->TextureList[0]->_Tex;
		EmitterTexture->_Tex = Tools::TextureWad->TextureList[0]->_Tex;
		return;

		t += 1.f / 60.f;

		device->SetRenderTarget( FlameRenderTarget );
		device->Clear( Color::Transparent );
		float scalex = 175;
		float scaley = 175;

		boost::shared_ptr<EzEffect> fx = Tools::BasicEffect;

		fx->effect->CurrentTechnique = fx->Simplest;
		Tools::EffectWad->SetCameraPosition( Vector4( 0, 0, 1 / scalex, 1 / scaley ) );
		fx->xCameraAspect->SetValue( 1.f );

		Flame_Emitter->Draw();

		device->SetRenderTarget( Tools::DestinationRenderTarget );
		Tools::Render->ResetViewport();
		FlameTexture->setTex( FlameRenderTarget );


		// Draw emitter
		device->SetRenderTarget( EmitterRenderTarget );
		device->Clear( Color::Transparent );

		Emitter_Emitter->Draw();

		device->SetRenderTarget( Tools::DestinationRenderTarget );
		Tools::Render->ResetViewport();
		EmitterTexture->setTex( EmitterRenderTarget );
	}

	void Fireball::Explosion( Vector2 pos, const boost::shared_ptr<Level> &level )
	{
		Explosion( pos, level, Vector2(), 1, 1 );
	}

	void Fireball::Explosion( Vector2 pos, const boost::shared_ptr<Level> &level, Vector2 vel, float Scale, float ScaleQuad )
	{
		boost::shared_ptr<Rand> Rnd = Tools::GlobalRnd;

		//int i;
		for ( int k = 0; k < 20; k++ )
		{
			boost::shared_ptr<CloudberryKingdom::Particle> p = level->MainEmitter->GetNewParticle( ExplodeTemplate );

			Vector2 Dir = Rnd->RndDir();

			p->Data.Position = pos + 23 * Dir * Scale;
			p->Data.Velocity = Scale * 8.5f * static_cast<float>( Rnd->Rnd->NextDouble() ) * Dir;
			p->Data.Acceleration = -.045f * p->Data.Velocity;
			p->Data.Velocity += vel;

			p->Size *= ScaleQuad;

			p->AngleSpeed *= 2 * static_cast<float>( Rnd->Rnd->NextDouble() - .5f );
			//p.ColorVel.W *= (float)(.3f * Rnd.Rnd.NextDouble() + .7f);
		}
	}

	void Fireball::MakeNew()
	{
		_CircleDeath::MakeNew();

		getCore()->MyType = ObjectType_FIREBALL;
		AutoGenSingleton = Fireball_AutoGen::getInstance();
		DeathType = BobDeathType_FIREBALL;

		PhsxCutoff_Playing = Vector2( 10000 );
		PhsxCutoff_BoxesOnly = Vector2( 10000 );

		getCore()->ContinuousEnabled = true;

		getCore()->DrawLayer = 8;

		Radius = 40;

		Alive = true;
		PrevStep = 0;
	}

	void Fireball::Die()
	{
		_CircleDeath::Die();

		Alive = false;

		if ( getCore()->MyLevel->PlayMode == 0 )
		{
			ExplodeSound->Play( 1 );
			Explosion( getCore()->Data.Position, getCore()->MyLevel,.33f * getCore()->Data.Velocity, 1, 1 );
		}
	}

	Fireball::Fireball( bool BoxesOnly ) :
		Period( 0 ),
		Offset( 0 ),
		Alive( false ),
		PrevStep( 0 )
	{
		_CircleDeath::Construct( BoxesOnly );

		if ( !getCore()->BoxesOnly )
		{
			MyQuad = boost::make_shared<HsvQuad>();
		}
	}

	void Fireball::Init( PhsxData data, const boost::shared_ptr<Level> &level )
	{
		_CircleDeath::Init( data.Position, level );

		Alive = true;

		getCore()->Data = data;

		if ( !level->BoxesOnly )
		{
			if ( level->getInfo()->Fireballs->Sprite->Sprite != 0 )
			{
				if ( MyQuad == 0 )
					MyQuad = boost::make_shared<HsvQuad>();
				MyQuad->Set( level->getInfo()->Fireballs->Sprite );
			}
			else
			{
				if ( MyQuad == 0 )
					MyQuad = boost::make_shared<HsvQuad>();

				if ( !getCore()->BoxesOnly )
				{
					MyQuad->setSize( Vector2( 195 ) );
					MyQuad->Quad_Renamed.setMyTexture( FireballTexture );
					MyQuad->Set( level->getInfo()->Fireballs->Sprite );
					MyQuad->Show = true;
				}
			}
		}
	}

	Vector2 Fireball::GetPos()
	{
		//if (!Alive) Tools::Write("!");

		// FIXME: check fmod is doing same as modular arithmetic
		//float Step = ( getCore()->MyLevel->IndependentPhsxStep - Offset + Period ) % Period;
		float Step = fmodf( getCore()->MyLevel->IndependentPhsxStep - Offset + Period, static_cast<float>( Period ) );

		if ( PrevStep > Step )
			Alive = true;

		PrevStep = Step;

		//Tools::Write(Core.StartData.Velocity.Length());
		return getCore()->StartData.Position + Step * getCore()->StartData.Velocity;
	}

	void Fireball::ActivePhsxStep()
	{
		if ( !Alive )
		{
			getCore()->Active = false;
			setPos( GetPos() );
			return;
		}
		else
			getCore()->Active = true;

		setPos( GetPos() );

		_CircleDeath::ActivePhsxStep();
	}

	void Fireball::Interact( const boost::shared_ptr<Bob> &bob )
	{
		if ( !Alive )
			return;

		_CircleDeath::Interact( bob );
	}

	void Fireball::DrawGraphics()
	{
		if ( !Alive || !getCore()->MyLevel->getMainCamera()->OnScreen(getPos(), 300) )
			return;

		// Point forward
		MyQuad->PointxAxisTo( -1 * getCore()->Data.Velocity );

		MyQuad->Quad_Renamed.MyEffect = Tools::HslEffect;

		// Shift forward
		Vector2 dir = getCore()->Data.Velocity;
		dir.Normalize();

		MyQuad->setPos( getCore()->Data.Position - 30 * dir );

		// Draw the fireball
		MyQuad->Draw();
	}

	void Fireball::DrawBoxes()
	{
		Circle->Draw( bColor( 50, 50, 255, 220 ) );
	}

	void Fireball::Clone( const boost::shared_ptr<ObjectBase> &A )
	{
		getCore()->Clone(A->getCore());

		boost::shared_ptr<Fireball> FireballA = boost::dynamic_pointer_cast<Fireball>( A );

		Radius = FireballA->Radius;
		Period = FireballA->Period;
		Offset = FireballA->Offset;

		Init( FireballA->getCore()->Data, FireballA->getMyLevel() );
		getCore()->StartData = FireballA->getCore()->StartData;
	}
}
