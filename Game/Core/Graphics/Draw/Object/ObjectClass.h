#ifndef OBJECTCLASS
#define OBJECTCLASS

#include <global_header.h>

namespace CloudberryKingdom
{
	class Quad;
}

namespace CloudberryKingdom
{
	class EzTexture;
}

namespace CloudberryKingdom
{
	class EzEffect;
}

namespace CloudberryKingdom
{
	class BaseQuad;
}

namespace CloudberryKingdom
{
	class QuadDrawer;
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
	class AnimQueueEntry;
}

namespace CloudberryKingdom
{
	class ObjectBox;
}

namespace CloudberryKingdom
{
	class EzReader;
}

namespace CloudberryKingdom
{
	class EzEffectWad;
}

namespace CloudberryKingdom
{
	class EzTextureWad;
}

namespace CloudberryKingdom
{
	class ObjectVector;
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
	class SpriteAnim;
}

namespace Microsoft
{
	namespace Xna
	{
		namespace Framework
		{
			namespace Graphics
			{
				class Texture2D;
			}
		}
	}
}












namespace CloudberryKingdom
{
	class ObjectClass
	{
	public:
		float LoadingRunSpeed;

		float CapeThickness;
		Vector2 p1_Left;
		Vector2 p2_Left;
		Vector2 p1_Right;
		Vector2 p2_Right;


		static int ObjectClassVersionNumber;
		int VersionNumber;

		float ContainedQuadAngle;
		std::shared_ptr<Quad> ContainedQuad;

		std::shared_ptr<EzTexture> MySkinTexture;
		std::shared_ptr<EzEffect> MySkinEffect;

		std::shared_ptr<Quad> ParentQuad;
		std::vector<BaseQuad*> QuadList;

	private:
		std::shared_ptr<QuadDrawer> QDrawer;
	public:
		bool xFlip, yFlip, CenterFlipOnBox;
		Vector2 FlipCenter;

	private:
		std::shared_ptr<RenderTarget2D> ObjectRenderTarget, ToTextureRenderTarget;
		int DrawWidth, DrawHeight;

	public:
		std::vector<EzEffect*> MyEffects;

		const bool &getDonePlaying() const;

		std::queue<AnimQueueEntry*> AnimQueue;
		std::shared_ptr<AnimQueueEntry> LastAnimEntry;
		std::vector<int> AnimLength;
		std::vector<std::wstring> AnimName;
		std::vector<float> AnimSpeed;
		bool Play, Loop, Transfer, OldLoop, Linear;
		int anim, OldAnim;
		float t, OldT, StartT;

		std::vector<ObjectBox*> BoxList;

		bool BoxesOnly;

		void Release();

		void ConvertForSimple();

		void Write( const std::shared_ptr<BinaryWriter> &writer );

		void ReadFile( const std::shared_ptr<EzReader> &reader );
		void ReadFile( const std::shared_ptr<BinaryReader> &reader, const std::shared_ptr<EzEffectWad> &EffectWad, const std::shared_ptr<EzTextureWad> &TextureWad );

#if defined(EDITOR)
		std::vector<ObjectVector*> GetObjectVectors();
#endif

		/// <summary>
		/// Update the list of effects associated with the object's quads
		/// </summary>
		void UpdateEffectList();

		Vector2 CalcBLBound();

		Vector2 CalcTRBound();

		void EnqueueTransfer( int _anim, float _destT, float speed, bool DestLoop );
		void EnqueueTransfer( int _anim, float _destT, float speed, bool DestLoop, bool KeepTransfers );

		void ImportAnimData( const std::shared_ptr<ObjectClass> &SourceObj, std::vector<BaseQuad*> &SourceQuads, std::vector<std::wstring> &SourceAnims );

		void ImportAnimDataShallow( const std::shared_ptr<ObjectClass> &SourceObj, std::vector<BaseQuad*> &SourceQuads, std::vector<std::wstring> &SourceAnims );

		bool HasAnim( const std::wstring &name );
		int FindAnim( const std::wstring &name );
		void EnqueueAnimation( const std::wstring &name );
		void EnqueueAnimation( const std::wstring &name, float startT, bool loop, bool clear );
		void EnqueueAnimation( const std::wstring &name, float startT, bool loop, bool clear, float TransferSpeed, float PlaySpeed );
		void EnqueueAnimation( const std::wstring &name, float startT, bool loop, bool clear, float TransferSpeed, float PlaySpeed, bool KeepTransfers );
		void EnqueueAnimation( int _anim, float startT, bool loop );
		void EnqueueAnimation( int _anim, float startT, bool loop, bool clear );
		void EnqueueAnimation( int _anim, float startT, bool loop, bool clear, bool KeepTransfers, float TransferSpeed );

		int DestinationAnim();

		std::shared_ptr<AnimQueueEntry> DestAnim();

		void DequeueTransfers();

		void SetAnimT( float t, bool Loop );

		/// <summary>
		/// Returns true when the animation is at the specified time
		/// </summary>
		/// <param name="time"></param>
		/// <returns></returns>
		bool AtTime( float time );

		bool DoSpriteAnim;
		void PlayUpdate( float DeltaT );

		void SetHold();

#if defined(EDITOR)
		void DeleteFrame( int anim, int frame );

		void InsertFrame( int anim, int frame );
#endif

		void Record( int anim, int frame, bool UseRelativeCoords );

		void Read( int anim, int frame );
		void Read_NoTexture( int anim, int frame );

		void ReadQuadData( int anim, int frame );
		void ReadBoxData( int anim, int frame );



		void FinishLoading();
		void FinishLoading( const std::shared_ptr<QuadDrawer> &Drawer, const std::shared_ptr<GraphicsDevice> &device, const std::shared_ptr<EzTextureWad> &TexWad, const std::shared_ptr<EzEffectWad> &EffectWad, const std::shared_ptr<PresentationParameters> &pp, int Width, int Height );
		void FinishLoading( const std::shared_ptr<QuadDrawer> &Drawer, const std::shared_ptr<GraphicsDevice> &device, const std::shared_ptr<EzTextureWad> &TexWad, const std::shared_ptr<EzEffectWad> &EffectWad, const std::shared_ptr<PresentationParameters> &pp, int Width, int Height, bool UseNames );

		ObjectClass();

		ObjectClass( const std::shared_ptr<ObjectClass> &obj, bool _BoxesOnly, bool DeepClone );

		ObjectClass( const std::shared_ptr<QuadDrawer> &Drawer, const std::shared_ptr<GraphicsDevice> &device, const std::shared_ptr<EzEffect> &BaseEffect, const std::shared_ptr<EzTexture> &BaseTexture );

		ObjectClass( const std::shared_ptr<QuadDrawer> &Drawer, const std::shared_ptr<GraphicsDevice> &device, const std::shared_ptr<PresentationParameters> &pp, int Width, int Height, const std::shared_ptr<EzEffect> &BaseEffect, const std::shared_ptr<EzTexture> &BaseTexture );

		void ObjectClassInit( const std::shared_ptr<QuadDrawer> &Drawer, const std::shared_ptr<GraphicsDevice> &device, const std::shared_ptr<PresentationParameters> &pp, int Width, int Height, const std::shared_ptr<EzEffect> &BaseEffect, const std::shared_ptr<EzTexture> &BaseTexture );

		void MakeRenderTargetUnique( int width, int height );

		bool OriginalRenderTarget;
	private:
		void InitRenderTargets( const std::shared_ptr<ObjectClass> &obj );

		void InitRenderTargets( const std::shared_ptr<GraphicsDevice> &device, const std::shared_ptr<PresentationParameters> &pp, int Width, int Height );

	public:
//ORIGINAL LINE: public List<BaseQuad> FindQuads(params string[] names)
//C# TO C++ CONVERTER TODO TASK: Use 'va_start', 'va_arg', and 'va_end' to access the parameter array within this method:
		std::vector<BaseQuad*> FindQuads( ... );
		std::shared_ptr<BaseQuad> FindQuad( const std::wstring &name );

	private:
		void AddToNewList( std::vector<BaseQuad*> &NewList, const std::shared_ptr<BaseQuad> &quad );
	public:
		void Sort();

		/// <summary>
		/// Scale the object's ParentQuad
		/// </summary>
		/// <param name="scale">The amount to scale by, as a ratio</param>
		void Scale( float scale );

		/// <summary>
		/// Scale the object's ParentQuad
		/// </summary>
		/// <param name="scale">The amount to scale by, as a ratio</param>
		void Scale( Vector2 scale );

		/// <summary>
		/// Move the object to a new position, updating the entire structure
		/// </summary>
		/// <param name="NewPosition">The new position</param>
		void MoveTo( Vector2 NewPosition );

		/// <summary>
		/// Move the object to a new position, updating the entire structure
		/// </summary>
		/// <param name="NewPosition">The new position</param>
		/// <param name="Update">Whether to update the object structure</param>
		void MoveTo( Vector2 NewPosition, bool UpdateObject );

		void SetColor( Color color );

		void UpdateBoxes();

		void Update( const std::shared_ptr<BaseQuad> &quad );

		void AddBox( const std::shared_ptr<ObjectBox> &box );

		void AddQuad( const std::shared_ptr<Quad> &quad );
		void AddQuad( const std::shared_ptr<Quad> &quad, bool ChangeParent );

		void RemoveQuad( const std::shared_ptr<BaseQuad> &quad );

		void ContainedDraw();

		std::shared_ptr<Quad> ExtraQuadToDraw;
		std::shared_ptr<EzTexture> ExtraQuadToDrawTexture;
		bool DrawExtraQuad;

		void Draw( bool UpdateFirst );

		std::shared_ptr<SpriteAnim> AnimToSpriteFrames( int anim, int NumFrames, bool Loop, Vector2 Padding );
		std::shared_ptr<SpriteAnim> AnimToSpriteFrames( int anim, int NumFrames, bool Loop, float StartT, float EndT, Vector2 Padding );

		std::shared_ptr<Texture2D> DrawToTexture( const std::shared_ptr<GraphicsDevice> &device, const std::shared_ptr<EzEffectWad> &EffectWad, Vector2 Padding );

	private:
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef OBJECTCLASS
