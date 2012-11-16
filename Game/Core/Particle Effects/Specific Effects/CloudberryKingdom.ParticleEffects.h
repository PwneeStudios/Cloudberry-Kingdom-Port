#ifndef CLOUDBERRYKINGDOM
#define CLOUDBERRYKINGDOM

#include <global_header.h>

namespace CloudberryKingdom
{
	class Particle;
}

namespace CloudberryKingdom
{
	class Level;
}

namespace CloudberryKingdom
{
	class EzTexture;
}

namespace CloudberryKingdom
{
	class EzSound;
}

namespace CloudberryKingdom
{
	class ParticleEmitter;
}








namespace CloudberryKingdom
{
	class ParticleEffects
	{
	public:
		enum PieceOrbStyle
		{
			PieceOrbStyle_BIG_RND,
			PieceOrbStyle_CLOUD,
			PieceOrbStyle_FIRE
		};
	public:
		static std::shared_ptr<Particle> CoinExplosionTemplate;

		static void Init_CoinExplosion();

	private:
		static void SetRandomCoin( const std::shared_ptr<Particle> &p );

	public:
		static void CoinExplosion( const std::shared_ptr<Level> &level, Vector2 pos );


		static std::shared_ptr<Particle> SingleAnimatedParticle( Vector2 Pos, Vector2 Size, PhsxData Data, const std::shared_ptr<EzTexture> &Texture );

	private:
		static std::shared_ptr<Particle> DustCloudTemplate;
		static std::shared_ptr<EzSound> DustCloudSound;

		static std::shared_ptr<Particle> FlameTemplate;
		static std::shared_ptr<Particle> ThrustTemplate;
		static std::shared_ptr<Particle> PieceExplosionTemplate;
		static std::shared_ptr<Particle> CoalesceTemplate;

	public:
		static void Init();

		static void Init_Coalesce();

		static void Init_PieceExplosion();

		static void Init_DustCloud();

		static void Init_Flame();

		static void Init_Thrust();

		static void CartThrust( const std::shared_ptr<Level> &level, int Layer, Vector2 pos, Vector2 dir, Vector2 vel );

		static void Thrust( const std::shared_ptr<Level> &level, int Layer, Vector2 pos, Vector2 dir, Vector2 vel, float scale );

		static void HeroExplosion( const std::shared_ptr<Level> &level, Vector2 pos );

		static void DustCloudExplosion( const std::shared_ptr<Level> &level, Vector2 pos );

		static void Flame( const std::shared_ptr<Level> &level, Vector2 pos, int frame, float intensity, int life, bool ModFade );
		static void Flame( const std::shared_ptr<ParticleEmitter> &emitter, Vector2 pos, int frame, float intensity, int life, bool ModFade );

	private:
		static void SetRandomPiece( const std::shared_ptr<Particle> &p );

	public:
		static void Coalesce( const std::shared_ptr<Level> &level, Vector2 pos );
		static void Coalesce( const std::shared_ptr<Level> &level, Vector2 pos, int PadLife );

		static void PieceExplosion( const std::shared_ptr<Level> &level, Vector2 pos, int frame, float intensity );


		static void PieceOrb( const std::shared_ptr<Level> &level, PieceOrbStyle style, Vector2 pos, int frame, float intensity );
		static void PieceOrb( const std::shared_ptr<Level> &level, PieceOrbStyle style, Vector2 pos, int frame, float intensity, const std::shared_ptr<EzTexture> &texture, Vector2 size, Vector4 color );

		/// <summary>
		/// Create an explosion of pieces at the specified location, plus a fart sound.
		/// </summary>
		static void PiecePopFart( const std::shared_ptr<Level> &level, Vector2 pos );

	private:
		static std::shared_ptr<Particle> PopTemplate;
	public:
		static void AddPop( const std::shared_ptr<Level> &level, Vector2 pos );
		static void AddPop( const std::shared_ptr<Level> &level, Vector2 pos, float size );
		static void AddPop( const std::shared_ptr<Level> &level, Vector2 pos, float size, const std::shared_ptr<EzTexture> &tex );

	private:
		static void Init_Pop();
	};
}


#endif	//#ifndef CLOUDBERRYKINGDOM
