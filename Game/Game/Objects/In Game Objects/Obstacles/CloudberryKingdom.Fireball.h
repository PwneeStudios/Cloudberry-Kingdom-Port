#ifndef CLOUDBERRYKINGDOM_FIREBALL
#define CLOUDBERRYKINGDOM_FIREBALL

#include <global_header.h>

#include <Hacks\XNA\PresentationParameters.h>

namespace CloudberryKingdom
{
	struct Fireball : public _CircleDeath
	{
	
		struct FireballTileInfo : public TileInfoBase
		{
		
			boost::shared_ptr<SpriteInfo> Sprite;

		
			void InitializeInstanceFields();

	
			FireballTileInfo()
			{
				InitializeInstanceFields();
			}
		};

	
		static boost::shared_ptr<Particle> ExplodeTemplate, EmitterTemplate;
	
		static boost::shared_ptr<EzSound> ExplodeSound;
	
		static float t;

		static boost::shared_ptr<Quad> ShadeQuad;
	
		static boost::shared_ptr<EzTexture> FireballTexture, FlameTexture, EmitterTexture, BaseFireballTexture;
	
		static boost::shared_ptr<RenderTarget2D> FireballRenderTarget, FlameRenderTarget, EmitterRenderTarget;
		static int DrawWidth, DrawHeight;
	
		static boost::shared_ptr<ParticleEmitter> Fireball_Emitter, Flame_Emitter, Emitter_Emitter;

		static void PreInit();

		static void InitRenderTargets( const boost::shared_ptr<GraphicsDevice> &device, const boost::shared_ptr<PresentationParameters> &pp, int Width, int Height );

		static void TexturePhsx();

		static void DrawFireballTexture( const boost::shared_ptr<GraphicsDevice> &device, const boost::shared_ptr<EzEffectWad> &EffectWad );

		static void DrawEmitterTexture( const boost::shared_ptr<GraphicsDevice> &device, const boost::shared_ptr<EzEffectWad> &EffectWad );

		static void Explosion( Vector2 pos, const boost::shared_ptr<Level> &level );
		static void Explosion( Vector2 pos, const boost::shared_ptr<Level> &level, Vector2 vel, float Scale, float ScaleQuad );


		boost::shared_ptr<HsvQuad> MyQuad;

		int Period, Offset;

	
		bool Alive;

	
		virtual void MakeNew();

		virtual void Die();

		Fireball( bool BoxesOnly );

		void Init( PhsxData data, const boost::shared_ptr<Level> &level );

	
		float PrevStep;
		Vector2 GetPos();

	
		virtual void ActivePhsxStep();

	
		virtual void Interact( const boost::shared_ptr<Bob> &bob );

	
		virtual void DrawGraphics();

		virtual void DrawBoxes();

	
		virtual void Clone( const boost::shared_ptr<ObjectBase> &A );
	};
}


#endif	//#ifndef CLOUDBERRYKINGDOM_FIREBALL
