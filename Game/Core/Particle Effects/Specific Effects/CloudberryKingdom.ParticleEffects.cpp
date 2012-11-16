#include <global_header.h>
namespace CloudberryKingdom
{

std::shared_ptr<Particle> ParticleEffects::CoinExplosionTemplate = 0;

	void ParticleEffects::Init_CoinExplosion()
	{
		CoinExplosionTemplate = std::make_shared<Particle>();

		CoinExplosionTemplate->MyQuad.Init();
		CoinExplosionTemplate->MyQuad.MyEffect = Tools::BasicEffect;
		CoinExplosionTemplate->MyQuad.setMyTexture( Tools::TextureWad->FindByName( _T( "checkpoint3" ) ) );
		CoinExplosionTemplate->Size = Vector2( 45, 70 ) * 1.15f;
		CoinExplosionTemplate->SizeSpeed = Vector2( 1.5f, 1.5f );
		CoinExplosionTemplate->AngleSpeed = .02f;
		CoinExplosionTemplate->Life = 210;
		CoinExplosionTemplate->MyColor = Vector4( 1, 1, 1, 1 );
		CoinExplosionTemplate->ColorVel = Vector4( 0, 0, 0, 0 );
		CoinExplosionTemplate->Data.Acceleration = Vector2( 0, -1.2f );
		CoinExplosionTemplate->KillOffBottom = CoinExplosionTemplate->KillOffSides = true;
	}

	void ParticleEffects::SetRandomCoin( const std::shared_ptr<Particle> &p )
	{
		switch ( Tools::GlobalRnd->RndInt( 0, 6 ) )
		{
			case 0:
				p->MyQuad.setTextureName( _T( "CoinBlue" ) );
				break;
			case 1:
				p->MyQuad.setTextureName( _T( "CoinCyan" ) );
				break;
			case 2:
				p->MyQuad.setTextureName( _T( "CoinGreen" ) );
				break;
			case 3:
				p->MyQuad.setTextureName( _T( "CoinOrange" ) );
				break;
			case 4:
				p->MyQuad.setTextureName( _T( "CoinPurple" ) );
				break;
			case 5:
				p->MyQuad.setTextureName( _T( "CoinRed" ) );
				break;
			case 6:
				p->MyQuad.setTextureName( _T( "CoinYellow" ) );
				break;
		}
	}

	void ParticleEffects::CoinExplosion( const std::shared_ptr<Level> &level, Vector2 pos )
	{
		std::shared_ptr<ParticleEmitter> emit = level->MainEmitter;

		float intensity = 1;

		int i;
		for ( int k = 0; k < 14; k++ )
		{
			std::shared_ptr<CloudberryKingdom::Particle> p = emit->GetNewParticle( CoinExplosionTemplate );

			Vector2 Dir = level->getRnd()->RndDir();

			p->Data.Position = pos + 45 * Dir * intensity;
			p->Data.Velocity = 45 * intensity * static_cast<float>( level->getRnd()->Rnd->NextDouble() ) * Dir + Vector2(0, 13);
			p->Angle = level->getRnd()->RndFloat(0, 100);
			p->Size *= intensity;

			//p.MyQuad.TextureName = "CoinBlue";
			p->MyQuad.setTextureName( _T( "CoinGreen" ) );
			//SetRandomCoin(emit, i);
		}
	}

	std::shared_ptr<Particle> ParticleEffects::SingleAnimatedParticle( Vector2 Pos, Vector2 Size, PhsxData Data, const std::shared_ptr<EzTexture> &Texture )
	{
		std::shared_ptr<Particle> p = std::make_shared<Particle>();
		p->MyQuad.Init();
		p->MyQuad.MyEffect = Tools::BasicEffect;
		p->MyQuad.setMyTexture( Texture );
		p->Size = Size;
		p->SizeSpeed = Vector2( 0 );
		p->AngleSpeed = 0;
		p->Life = 20;
		p->MyColor = Vector4( 1, 1, 1, 1 );
		p->ColorVel = Vector4( 0, 0, 0, 0 );

		return p;
	}

std::shared_ptr<Particle> ParticleEffects::DustCloudTemplate = 0;
std::shared_ptr<EzSound> ParticleEffects::DustCloudSound = 0;
std::shared_ptr<Particle> ParticleEffects::FlameTemplate = 0;
std::shared_ptr<Particle> ParticleEffects::ThrustTemplate = 0;
std::shared_ptr<Particle> ParticleEffects::PieceExplosionTemplate = 0;
std::shared_ptr<Particle> ParticleEffects::CoalesceTemplate = 0;

	void ParticleEffects::Init()
	{
		Init_Coalesce();
		Init_PieceExplosion();
		Init_CoinExplosion();
		Init_DustCloud();
		Init_Flame();
		Init_Thrust();
		Init_Pop();
	}

	void ParticleEffects::Init_Coalesce()
	{
		CoalesceTemplate = std::make_shared<Particle>();

		CoalesceTemplate->MyQuad.Init();
		CoalesceTemplate->MyQuad.MyEffect = Tools::BasicEffect;
		CoalesceTemplate->MyQuad.setMyTexture( Tools::TextureWad->FindByName( _T( "Cloud1" ) ) );
		CoalesceTemplate->SetSize( 145 );
		CoalesceTemplate->SizeSpeed = Vector2( 4, 4 );
		CoalesceTemplate->AngleSpeed = -.03f;
		CoalesceTemplate->Life = 33;
		CoalesceTemplate->MyColor = Vector4( 1,.98f,.98f, 0 );
		CoalesceTemplate->ColorVel = Vector4( 0, 0, 0, 0.014f );
		CoalesceTemplate->UseAttraction = true;
		CoalesceTemplate->AttractionStrength = 2.43f;
	}

	void ParticleEffects::Init_PieceExplosion()
	{
		PieceExplosionTemplate = std::make_shared<Particle>();

		PieceExplosionTemplate->MyQuad.Init();
		PieceExplosionTemplate->MyQuad.MyEffect = Tools::BasicEffect;
		PieceExplosionTemplate->MyQuad.setMyTexture( Tools::TextureWad->FindByName( _T( "Smoke2" ) ) );
		PieceExplosionTemplate->SetSize( 145 );
		PieceExplosionTemplate->SizeSpeed = Vector2( 4, 4 );
		PieceExplosionTemplate->AngleSpeed = .02f;
		PieceExplosionTemplate->Life = 210;
		PieceExplosionTemplate->MyColor = Vector4( 1, 1, 1, 1 );
		PieceExplosionTemplate->ColorVel = Vector4( 0, 0, 0, 0 );
		PieceExplosionTemplate->Data.Acceleration = Vector2( 0, -1.2f );
		PieceExplosionTemplate->KillOffBottom = PieceExplosionTemplate->KillOffSides = true;
	}

	void ParticleEffects::Init_DustCloud()
	{
		DustCloudSound = Tools::SoundWad->FindByName( _T( "DustCloud_Explode" ) );

		DustCloudTemplate = std::make_shared<Particle>();

		DustCloudTemplate->MyQuad.Init();
		DustCloudTemplate->MyQuad.MyEffect = Tools::BasicEffect;
		DustCloudTemplate->MyQuad.setMyTexture( Tools::TextureWad->FindByName( _T( "Smoke2" ) ) );
		DustCloudTemplate->SetSize( 120 );
		DustCloudTemplate->SizeSpeed = Vector2( 4, 4 );
		DustCloudTemplate->AngleSpeed = .02f;
		DustCloudTemplate->Life = 48;
		DustCloudTemplate->MyColor = Vector4( 1.15f, 1.15f, 1.15f, 1.1f );
		DustCloudTemplate->ColorVel = Vector4( 0.02f, 0.02f, 0.02f, -.023f );
		DustCloudTemplate->Data.Acceleration = Vector2( 0,.60f );
	}

	void ParticleEffects::Init_Flame()
	{
		FlameTemplate = std::make_shared<Particle>();

		FlameTemplate->MyQuad.Init();
		FlameTemplate->MyQuad.UseGlobalIllumination = false;
		FlameTemplate->MyQuad.MyEffect = Tools::BasicEffect;
		FlameTemplate->MyQuad.setMyTexture( Fireball::FlameTexture ); // Tools.TextureWad.FindByName("Fire4");
		FlameTemplate->SetSize( 196 ); //106);
		FlameTemplate->SizeSpeed = Vector2( -.3f, -.3f );
		FlameTemplate->AngleSpeed = .015f;
		FlameTemplate->Life = 30;
		FlameTemplate->MyColor = Vector4( .9f, 1, 1, 0 );
		FlameTemplate->ColorVel = Vector4( 0.0007f, -0.0007f, -0.0007f, -.06f );
		FlameTemplate->Data.Acceleration = Vector2( 0,.39f ); //.35f);

		FlameTemplate->FadingIn = true;
		FlameTemplate->FadeInColorVel = Vector4( 0, 0, 0,.05f ); //.07f);
		FlameTemplate->FadeInTargetAlpha = 1; // .5f;
	}

	void ParticleEffects::Init_Thrust()
	{
		ThrustTemplate = std::make_shared<Particle>();

		ThrustTemplate->MyQuad.Init();
		ThrustTemplate->MyQuad.UseGlobalIllumination = false;
		ThrustTemplate->MyQuad.MyEffect = Tools::BasicEffect;
		ThrustTemplate->MyQuad.setMyTexture( Fireball::FlameTexture ); // Tools.TextureWad.FindByName("Fire");
		ThrustTemplate->SetSize( 60 ); //33);
		ThrustTemplate->SizeSpeed = Vector2( -.3f, -.3f );
		ThrustTemplate->AngleSpeed = .05f;
		ThrustTemplate->Life = 15;
		//ThrustTemplate.MyColor = new Vector4(1.15f, 1.15f, 1.15f, 1.1f);
		ThrustTemplate->MyColor = Vector4( .93f,.9f,.9f, 1.1f );
		ThrustTemplate->ColorVel = Vector4( 0.02f, 0.02f, 0.02f, -.07f );
		ThrustTemplate->Data.Acceleration = Vector2( 0, 0 );

		ThrustTemplate->MyQuad.BlendAddRatio = .5f;
	}

	void ParticleEffects::CartThrust( const std::shared_ptr<Level> &level, int Layer, Vector2 pos, Vector2 dir, Vector2 vel )
	{
		if ( level->GetPhsxStep() % 2 != 0 )
			return;

		std::shared_ptr<ParticleEmitter> emit = level->ParticleEmitters[ Layer ];

		for ( int k = 0; k < 1; k++ )
		{
			std::shared_ptr<CloudberryKingdom::Particle> p = emit->GetNewParticle( ThrustTemplate );
			p->Size *= 2;
			p->Life = 9;
			p->MyColor.X *= .8f;
			p->MyColor.Y *= .8f;
			p->MyColor.Z *= .8f;
			Vector2 Dir = Tools::GlobalRnd->RndDir();

			p->Data.Position = pos + 3 * Dir;
			p->Data.Velocity = vel + 13 * ( Tools::GlobalRnd->RndFloat( .6f,.8f ) ) * dir + 1 * Dir + Vector2( 0, static_cast<float>( sin( Tools::t*23 ) ) * 5 );
		}
	}

	void ParticleEffects::Thrust( const std::shared_ptr<Level> &level, int Layer, Vector2 pos, Vector2 dir, Vector2 vel, float scale )
	{
		//if (level.GetPhsxStep() % 3 != 0) return;

		std::shared_ptr<ParticleEmitter> emit = level->ParticleEmitters[ Layer ];

		for ( int k = 0; k < 1; k++ )
		{
			std::shared_ptr<CloudberryKingdom::Particle> p = emit->GetNewParticle( ThrustTemplate );
			Vector2 Dir = Tools::GlobalRnd->RndDir();

			p->Data.Position = pos + 3 * Dir;
			p->Data.Velocity = vel + 23 * ( .6f + .2f * static_cast<float>( Tools::GlobalRnd->Rnd->NextDouble() ) ) * dir + 1 * Dir;

			p->Size *= scale;
		}
	}

	void ParticleEffects::HeroExplosion( const std::shared_ptr<Level> &level, Vector2 pos )
	{
		std::shared_ptr<ParticleEmitter> emit = level->MainEmitter;

		for ( int k = 0; k < 37; k++ )
		{
			std::shared_ptr<CloudberryKingdom::Particle> p = emit->GetNewParticle( DustCloudTemplate );
			Vector2 Dir = Tools::GlobalRnd->RndDir();

			float scale = 1.25f;
			p->Data.Position = pos + 70 * Dir * scale;
			p->Data.Velocity = 10 * static_cast<float>( Tools::GlobalRnd->Rnd->NextDouble() ) * Dir * scale;
			p->Size *= scale;
			if ( k % 2 == 0 )
			{
				p->Data.Velocity.Y = -.5f * abs( p->Data.Velocity.Y );
				p->Data.Velocity.Y -= 10;
			}
			else
			{
				p->Data.Velocity.Y -= 10;
				//p.Data.Velocity.Y /= 3;
			}
		}

		DustCloudSound->Play();
	}

	void ParticleEffects::DustCloudExplosion( const std::shared_ptr<Level> &level, Vector2 pos )
	{
		std::shared_ptr<ParticleEmitter> emit = level->MainEmitter;

		for ( int k = 0; k < 27; k++ )
		{
			std::shared_ptr<CloudberryKingdom::Particle> p = emit->GetNewParticle( DustCloudTemplate );
			Vector2 Dir = Tools::GlobalRnd->RndDir();

			p->Data.Position = pos + 70 * Dir;
			p->Data.Velocity = 10 * static_cast<float>( Tools::GlobalRnd->Rnd->NextDouble() ) * Dir;
			if ( k % 2 == 0 )
			{
				p->Data.Velocity.Y = -.5f * abs( p->Data.Velocity.Y );
				p->Data.Velocity.Y -= 10;
			}
			else
			{
				p->Data.Velocity.Y -= 10;
				//p.Data.Velocity.Y /= 3;
			}
		}

		DustCloudSound->Play();
	}

	void ParticleEffects::Flame( const std::shared_ptr<Level> &level, Vector2 pos, int frame, float intensity, int life, bool ModFade )
	{
		Flame( level->MainEmitter, pos, frame, intensity, life, ModFade );
	}

	void ParticleEffects::Flame( const std::shared_ptr<ParticleEmitter> &emitter, Vector2 pos, int frame, float intensity, int life, bool ModFade )
	{
		//if (frame % 3 != 0) return;
		//if (Tools.TheGame.DrawCount % 3 == 0) return;

		std::shared_ptr<ParticleEmitter> emit = emitter;

		for ( int k = 0; k < 1; k++ )
		{
			std::shared_ptr<CloudberryKingdom::Particle> p = emit->GetNewParticle( FlameTemplate );
			Vector2 Dir = Tools::GlobalRnd->RndDir();

			if ( ModFade )
			{
				p->FadeInColorVel.W *= 55 / life;
				p->ColorVel.W *= 55 / life;
			}

			p->Data.Position = pos + 35 * Dir * intensity;
			p->Data.Velocity = .35f * 2 * intensity * static_cast<float>( Tools::GlobalRnd->Rnd->NextDouble() ) * Dir;
			//p.Data.Acceleration = new Vector2(-.5f, 0);
			//p.Data.Acceleration = -.25f * p.Data.Velocity;
				p->Data.Acceleration = -.5f * p->Data.Velocity;
				p->Life = life;
				p->AngleSpeed /= 2;
			p->Angle = Tools::GlobalRnd->RndFloat( 0, 100 );
			p->Size *= intensity;
		}
	}

	void ParticleEffects::SetRandomPiece( const std::shared_ptr<Particle> &p )
	{
		switch ( Tools::GlobalRnd->Rnd->Next( 0, 8 ) )
		{
			case 0:
				p->MyQuad.Set( _T( "FallingBlock2" ) );
				break;

			case 1:
				p->MyQuad.Set( _T( "FallingBlock1" ) );
				break;

			case 2:
				p->MyQuad.Set( _T( "blue_small" ) );
				break;

			case 3:
				p->MyQuad.Set( _T( "fading_block" ) );
				p->Size *= Vector2( 1, 1.11f );
				break;

			case 4:
				p->MyQuad.Set( _T( "SpikeyGuy" ) );
				p->Size *= Vector2( 1.2f, 1.6f );
				break;

			case 5:
				p->MyQuad.Set( _T( "blob2_body" ) );
				break;

			case 6:
				p->MyQuad.Set( _T( "checkpoint3" ) );
				p->Size *= Vector2( 1, 1 );
				break;

			case 7:
				p->MyQuad.Set( _T( "CoinBlue" ) );
				p->Size *= Vector2( .3f,.7f );
				break;
		}
	}

	void ParticleEffects::Coalesce( const std::shared_ptr<Level> &level, Vector2 pos )
	{
		Coalesce( level, pos, 0 );
	}

	void ParticleEffects::Coalesce( const std::shared_ptr<Level> &level, Vector2 pos, int PadLife )
	{
		std::shared_ptr<ParticleEmitter> emit = level->MainEmitter;

		int num = 1;
		if ( Tools::TheGame->DrawCount % 2 == 0 )
			num = 0;

		for ( int k = 0; k < num; k++ )
		{
			std::shared_ptr<CloudberryKingdom::Particle> p = emit->GetNewParticle( CoalesceTemplate );
			Vector2 Dir = Tools::GlobalRnd->RndDir();

			p->Data.Position = pos + 1500 * Dir;

			p->Angle = Tools::GlobalRnd->RndFloat( 0, 100 );
			//p.Size *= intensity;

			p->AttractionPoint = pos;

			Vector2 dif = pos - p->Data.Position;
			dif.Normalize();
			p->Data.Velocity = 9 * Vector2( -dif.Y, dif.X );

			//p.SizeSpeed = Vector2.Zero;
			p->Size *= 1.25f;
			//p.Life += 16;
			//SetRandomPiece(emit, i);

			p->Life += PadLife;
		}
	}

	void ParticleEffects::PieceExplosion( const std::shared_ptr<Level> &level, Vector2 pos, int frame, float intensity )
	{
		std::shared_ptr<ParticleEmitter> emit = level->MainEmitter;

		int num = 2;
		if ( Tools::TheGame->DrawCount % 2 == 0 )
			num = 3;
		num *= 2;

		for ( int k = 0; k < num; k++ )
		{
			std::shared_ptr<CloudberryKingdom::Particle> p = emit->GetNewParticle( PieceExplosionTemplate );
			Vector2 Dir = Tools::GlobalRnd->RndDir();

			p->Data.Position = pos + 75 * Dir * intensity;
			p->Data.Velocity = 125 * intensity * static_cast<float>( Tools::GlobalRnd->Rnd->NextDouble() ) * Dir;
			p->Angle = Tools::GlobalRnd->RndFloat( 0, 100 );
			p->Size *= intensity;

			SetRandomPiece( p );
		}
	}

	void ParticleEffects::PieceOrb( const std::shared_ptr<Level> &level, PieceOrbStyle style, Vector2 pos, int frame, float intensity )
	{
		PieceOrb( level, style, pos, frame, intensity, 0, Vector2::One, Vector4::One );
	}

	void ParticleEffects::PieceOrb( const std::shared_ptr<Level> &level, PieceOrbStyle style, Vector2 pos, int frame, float intensity, const std::shared_ptr<EzTexture> &texture, Vector2 size, Vector4 color )
	{
		// Number of particles to emit
		int num = 1;
		if ( Tools::TheGame->DrawCount % 2 == 0 )
			num = 2;

		float vel = 1, acc = 1, angle_vel = 1;
		int life = 20;
		switch ( style )
		{
			case PieceOrbStyle_BIG_RND:
				num *= 2;

				float t = 2 - intensity;
				float s = intensity - 1;
				vel = s * 130 + t * 60;
				acc = s * -.182f + t * -.128f;
				life = static_cast<int>( s * 12.5f + t * 18 );
				size *= s * 1.3f + t * 1.15f;

				break;

			case PieceOrbStyle_CLOUD:
				num = 1;

				vel = 50;
				acc = -.128f;
				color *= Vector4( .90f,.815f,.815f,.7f );
				size *= 1.2f * 1.5f * 1.5f;
				angle_vel = -10;
				if ( texture == 0 )
					texture = Tools::TextureWad->FindByName( _T( "Cloud1" ) );
				life = 20;
				break;

			case PieceOrbStyle_FIRE:
				num = 1;

				vel = 50;
				acc = -.128f;
				color *= Vector4( .90f,.815f,.815f,.7f );
				size *= 1.2f * 1.5f * 1.5f;
				angle_vel = -10;
				if ( texture == 0 )
					texture = Fireball::EmitterTexture;
				life = 20;
				break;
		}

		std::shared_ptr<ParticleEmitter> emit = level->MainEmitter;

		for ( int k = 0; k < num; k++ )
		{
			std::shared_ptr<CloudberryKingdom::Particle> p = emit->GetNewParticle( PieceExplosionTemplate );
			Vector2 Dir = Tools::GlobalRnd->RndDir();

			p->MyColor *= color;

			p->Data.Position = pos + 75 * Dir;
			//p.Data.Velocity = 25 * intensity * (float)Tools.GlobalRnd.Rnd.NextDouble() * Dir;
			//p.Data.Velocity = 18 * intensity * (float)Tools.GlobalRnd.Rnd.NextDouble() * Dir;
			//p.Data.Velocity = 50 * intensity * (float)Tools.GlobalRnd.Rnd.NextDouble() * Dir;
			p->Data.Velocity = vel * static_cast<float>( Tools::GlobalRnd->Rnd->NextDouble() ) * Dir;
				p->Data.Position += Tools::GlobalRnd->RndFloat( 0, 2 ) * p->Data.Velocity;
			p->Angle = Tools::GlobalRnd->RndFloat( 0, 100 );
			p->AngleSpeed *= angle_vel;
			p->Size *= size;
			//p.Data.Acceleration = -.15f * p.Data.Velocity;
			//p.Data.Acceleration = -.28f * p.Data.Velocity;                
			//p.Data.Acceleration = -.128f * p.Data.Velocity;           
			p->Data.Acceleration = acc * p->Data.Velocity;

			//p.Life = 15;
			//p.Life = 10;
			//p.Life = 20;
			p->Life = life;

			if ( texture == 0 )
				SetRandomPiece( p );
			else
				p->MyQuad.setMyTexture( texture );
		}
	}

	void ParticleEffects::PiecePopFart( const std::shared_ptr<Level> &level, Vector2 pos )
	{
		Tools::SoundWad->FindByName( _T( "Piece_Explosion_Small" ) )->Play( 1 );
		for ( int i = 0; i < 4; i++ )
			PieceExplosion( level, pos, 0, 1 );
	}

std::shared_ptr<Particle> ParticleEffects::PopTemplate = 0;

	void ParticleEffects::AddPop( const std::shared_ptr<Level> &level, Vector2 pos )
	{
		AddPop( level, pos, 85, PopTemplate->MyQuad.getMyTexture() );
	}

	void ParticleEffects::AddPop( const std::shared_ptr<Level> &level, Vector2 pos, float size )
	{
		AddPop( level, pos, size, PopTemplate->MyQuad.getMyTexture() );
	}

	void ParticleEffects::AddPop( const std::shared_ptr<Level> &level, Vector2 pos, float size, const std::shared_ptr<EzTexture> &tex )
	{
		if ( level->NoParticles )
			return;

		std::shared_ptr<CloudberryKingdom::Particle> p = level->MainEmitter->GetNewParticle( PopTemplate );
		p->Data.Position = pos;
		p->SetSize( size );
		p->MyQuad.setMyTexture( tex );
	}

	void ParticleEffects::Init_Pop()
	{
		PopTemplate = std::make_shared<Particle>();
		PopTemplate->MyQuad.Init();
		PopTemplate->MyQuad.MyEffect = Tools::EffectWad->FindByName( _T( "Shell" ) );
		PopTemplate->MyQuad.setMyTexture( Tools::TextureWad->FindByName( _T( "White" ) ) );
		PopTemplate->SetSize( 85 );
		PopTemplate->SizeSpeed = Vector2( 10, 10 );
		PopTemplate->AngleSpeed = 0;
		PopTemplate->Life = 20;
		PopTemplate->MyColor = Vector4( 1, 1, 1,.75f );
		PopTemplate->ColorVel = Vector4( 0, 0, 0, -.065f );
	}
}
