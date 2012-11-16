#ifndef CLOUDBERRYKINGDOM
#define CLOUDBERRYKINGDOM

#include "../Game/Objects/In Game Objects/BaseClasses/_CircleDeath.h"
#include "../Game/Tilesets/TileSet.h"
#include "../Core/PhsxData.h"
#include <tchar.h>

namespace CloudberryKingdom
{
	class SpriteInfo;
}

namespace CloudberryKingdom
{
	class Particle;
}

namespace CloudberryKingdom
{
	class EzSound;
}

namespace CloudberryKingdom
{
	class Quad;
}

namespace CloudberryKingdom
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
	class ParticleEmitter;
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

namespace CloudberryKingdom
{
	class EzEffectWad;
}

namespace CloudberryKingdom
{
	class Level;
}

namespace CloudberryKingdom
{
	class HsvQuad;
}

namespace CloudberryKingdom
{
	class Bob;
}

namespace CloudberryKingdom
{
	class ObjectBase;
}


using namespace Microsoft::Xna::Framework::Graphics;
using namespace Microsoft::Xna::Framework;

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::IO;

namespace CloudberryKingdom
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


#endif	//#ifndef CLOUDBERRYKINGDOM
