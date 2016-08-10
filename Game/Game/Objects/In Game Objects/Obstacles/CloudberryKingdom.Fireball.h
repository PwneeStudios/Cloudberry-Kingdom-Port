#ifndef CLOUDBERRYKINGDOM_FIREBALL
#define CLOUDBERRYKINGDOM_FIREBALL

#include <small_header.h>

#include "Core/PhsxData.h"
//#include "Core/Effects/EzEffect.h"
//#include "Core/Effects/EzEffectWad.h"
//#include "Core/Graphics/Draw/Quads/Quad.h"
//#include "Core/Graphics/Draw/Quads/QuadClass.h"
//#include "Core/Particle Effects/Particle.h"
//#include "Core/Particle Effects/ParticleEmitter.h"
//#include "Core/Particle Effects/Specific Effects/CloudberryKingdom.ParticleEffects.h"
//#include "Core/Sound/EzSound.h"
//#include "Core/Texture/EzTexture.h"
//#include "Core/Tools/Random.h"
//#include "Game/Objects/ObjectBase.h"
#include "Game/Tilesets/TileSet.h"
//#include "Game/Objects/Bob/Bob.h"
#include "Game/Objects/In Game Objects/BaseClasses/_CircleDeath.h"
//#include "Game/Objects/In Game Objects/Grab/MakeData.h"
//#include "Game/Level/Level.h"
//#include "Game/Objects/In Game Objects/Obstacles/Fireball__Auto.h"
//#include "Game/Tilesets/SpriteInfo.h"
//#include "Game/Tools/Recycler.h"
//#include "Game/Tools/Tools.h"
//#include "Game/Tilesets/TileSetInfo.h"


#include <Hacks\XNA\PresentationParameters.h>

namespace CloudberryKingdom
{

	struct Fireball : public _CircleDeath
	{

		virtual ~Fireball()
		{
#ifdef BOOST_BIN
			OnDestructor( "Fireball" );
#endif
		}

	
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
