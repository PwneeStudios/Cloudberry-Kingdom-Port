#ifndef CLOUDBERRYKINGDOM
#define CLOUDBERRYKINGDOM

#include <global_header.h>

namespace CloudberryKingdom
{
	class SpriteInfo;
}

namespace CloudberryKingdom
{
	namespace Particles
	{
		class Particle;
	}
}

namespace CoreEngine
{
	class EzSound;
}

namespace CoreEngine
{
	class Quad;
}

namespace CoreEngine
{
	class EzTexture;
}

namespace Microsoft
{
	namespace Xna
	{
		namespace Framework
		{
			namespace Graphics
			{
				class RenderTarget2D;
			}
		}
	}
}

namespace CloudberryKingdom
{
	namespace Particles
	{
		class ParticleEmitter;
	}
}

namespace Microsoft
{
	namespace Xna
	{
		namespace Framework
		{
			namespace Graphics
			{
				class GraphicsDevice;
			}
		}
	}
}

namespace Microsoft
{
	namespace Xna
	{
		namespace Framework
		{
			namespace Graphics
			{
				class PresentationParameters;
			}
		}
	}
}

namespace CoreEngine
{
	class EzEffectWad;
}

namespace CloudberryKingdom
{
	namespace Levels
	{
		class Level;
	}
}

namespace CloudberryKingdom
{
	class HsvQuad;
}

namespace CloudberryKingdom
{
	namespace Bobs
	{
		class Bob;
	}
}

namespace CloudberryKingdom
{
	class ObjectBase;
}


namespace CloudberryKingdom
{
	namespace Obstacles
	{
		class Fireball : public _CircleDeath
		{
		public:
			class FireballTileInfo : public TileInfoBase
			{
			public:
				std::shared_ptr<SpriteInfo> Sprite;

			private:
				void InitializeInstanceFields();

public:
				FireballTileInfo()
				{
					InitializeInstanceFields();
				}
			};

		private:
			static std::shared_ptr<Particle> ExplodeTemplate, EmitterTemplate;
		public:
			static std::shared_ptr<EzSound> ExplodeSound;
		private:
			static float t;

			static std::shared_ptr<Quad> ShadeQuad;
		public:
			static std::shared_ptr<EzTexture> FireballTexture, FlameTexture, EmitterTexture, BaseFireballTexture;
		private:
			static std::shared_ptr<RenderTarget2D> FireballRenderTarget, FlameRenderTarget, EmitterRenderTarget;
			static int DrawWidth, DrawHeight;
		public:
			static std::shared_ptr<ParticleEmitter> Fireball_Emitter, Flame_Emitter, Emitter_Emitter;

			static void PreInit();

			static void InitRenderTargets( const std::shared_ptr<GraphicsDevice> &device, const std::shared_ptr<PresentationParameters> &pp, int Width, int Height );

			static void TexturePhsx();

			static void DrawFireballTexture( const std::shared_ptr<GraphicsDevice> &device, const std::shared_ptr<EzEffectWad> &EffectWad );

			static void DrawEmitterTexture( const std::shared_ptr<GraphicsDevice> &device, const std::shared_ptr<EzEffectWad> &EffectWad );

			static void Explosion( Vector2 pos, const std::shared_ptr<Level> &level );
			static void Explosion( Vector2 pos, const std::shared_ptr<Level> &level, Vector2 vel, float Scale, float ScaleQuad );


			std::shared_ptr<HsvQuad> MyQuad;

			int Period, Offset;

		private:
			bool Alive;

		public:
			virtual void MakeNew();

			virtual void Die();

			Fireball( bool BoxesOnly );

			void Init( PhsxData data, const std::shared_ptr<Level> &level );

		private:
			float PrevStep;
			Vector2 GetPos();

		protected:
			virtual void ActivePhsxStep();

		public:
			virtual void Interact( const std::shared_ptr<Bob> &bob );

		protected:
			virtual void DrawGraphics();

			virtual void DrawBoxes();

		public:
			virtual void Clone( const std::shared_ptr<ObjectBase> &A );
		};
	}
}


#endif	//#ifndef CLOUDBERRYKINGDOM
