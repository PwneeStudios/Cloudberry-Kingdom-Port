#ifndef OBJECTCLASS
#define OBJECTCLASS

#include <global_header.h>

#include "Hacks/NET/BinaryWriter.h"
#include "Hacks/NET/BinaryReader.h"
#include "Hacks/XNA/RenderTarget2D.h"
#include "Hacks/XNA/GraphicsDevice.h"
#include "Hacks/XNA/PresentationParameters.h"
#include <Graphics/Texture2D.h>

namespace CloudberryKingdom
{
	struct ObjectClass : public boost::enable_shared_from_this<ObjectClass>
	{

	
		static void InitializeStatics();

	
		float LoadingRunSpeed;

		float CapeThickness;
		Vector2 p1_Left;
		Vector2 p2_Left;
		Vector2 p1_Right;
		Vector2 p2_Right;

		static int ObjectClassVersionNumber;
		int VersionNumber;

		float ContainedQuadAngle;
		boost::shared_ptr<Quad> ContainedQuad;

		boost::shared_ptr<EzTexture> MySkinTexture;
		boost::shared_ptr<EzEffect> MySkinEffect;

		boost::shared_ptr<Quad> ParentQuad;
		std::vector<boost::shared_ptr<BaseQuad> > QuadList;

	
		boost::shared_ptr<QuadDrawer> QDrawer;
	
		bool xFlip, yFlip, CenterFlipOnBox;
		Vector2 FlipCenter;

	
		boost::shared_ptr<RenderTarget2D> ObjectRenderTarget, ToTextureRenderTarget;
		int DrawWidth, DrawHeight;

	
		std::vector<boost::shared_ptr<EzEffect> > MyEffects;

		bool getDonePlaying() const;

		std::queue<boost::shared_ptr<AnimQueueEntry> > AnimQueue;
		boost::shared_ptr<AnimQueueEntry> LastAnimEntry;
		std::vector<int> AnimLength;
		std::vector<std::wstring> AnimName;
		std::vector<float> AnimSpeed;
		bool Play, Loop, Transfer, OldLoop, Linear;
		int anim, OldAnim;
		float t, OldT, StartT;

		std::vector<boost::shared_ptr<ObjectBox> > BoxList;

		bool BoxesOnly;

		void Release();

		void ConvertForSimple();

		void Write( const boost::shared_ptr<BinaryWriter> &writer );

		void ReadFile( const boost::shared_ptr<EzReader> &reader );
		void ReadFile( const boost::shared_ptr<BinaryReader> &reader, const boost::shared_ptr<EzEffectWad> &EffectWad, const boost::shared_ptr<EzTextureWad> &TextureWad );

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

		void ImportAnimData( const boost::shared_ptr<ObjectClass> &SourceObj, std::vector<boost::shared_ptr<BaseQuad> > &SourceQuads, std::vector<std::wstring> &SourceAnims );

		void ImportAnimDataShallow( const boost::shared_ptr<ObjectClass> &SourceObj, std::vector<boost::shared_ptr<BaseQuad> > &SourceQuads, std::vector<std::wstring> &SourceAnims );

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

		boost::shared_ptr<AnimQueueEntry> DestAnim();

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
		void FinishLoading( const boost::shared_ptr<QuadDrawer> &Drawer, const boost::shared_ptr<GraphicsDevice> &device, const boost::shared_ptr<EzTextureWad> &TexWad, const boost::shared_ptr<EzEffectWad> &EffectWad, const boost::shared_ptr<PresentationParameters> &pp, int Width, int Height );
		void FinishLoading( const boost::shared_ptr<QuadDrawer> &Drawer, const boost::shared_ptr<GraphicsDevice> &device, const boost::shared_ptr<EzTextureWad> &TexWad, const boost::shared_ptr<EzEffectWad> &EffectWad, const boost::shared_ptr<PresentationParameters> &pp, int Width, int Height, bool UseNames );

		ObjectClass();

		ObjectClass( const boost::shared_ptr<ObjectClass> &obj, bool _BoxesOnly, bool DeepClone );

		ObjectClass( const boost::shared_ptr<QuadDrawer> &Drawer, const boost::shared_ptr<GraphicsDevice> &device, const boost::shared_ptr<EzEffect> &BaseEffect, const boost::shared_ptr<EzTexture> &BaseTexture );

		ObjectClass( const boost::shared_ptr<QuadDrawer> &Drawer, const boost::shared_ptr<GraphicsDevice> &device, const boost::shared_ptr<PresentationParameters> &pp, int Width, int Height, const boost::shared_ptr<EzEffect> &BaseEffect, const boost::shared_ptr<EzTexture> &BaseTexture );

		void ObjectClassInit( const boost::shared_ptr<QuadDrawer> &Drawer, const boost::shared_ptr<GraphicsDevice> &device, const boost::shared_ptr<PresentationParameters> &pp, int Width, int Height, const boost::shared_ptr<EzEffect> &BaseEffect, const boost::shared_ptr<EzTexture> &BaseTexture );

		void MakeRenderTargetUnique( int width, int height );

		bool OriginalRenderTarget;
	
		void InitRenderTargets( const boost::shared_ptr<ObjectClass> &obj );

		void InitRenderTargets( const boost::shared_ptr<GraphicsDevice> &device, const boost::shared_ptr<PresentationParameters> &pp, int Width, int Height );

	
		boost::shared_ptr<BaseQuad> FindQuad( const std::wstring &name );

	
		void AddToNewList( std::vector<boost::shared_ptr<BaseQuad> > &NewList, const boost::shared_ptr<BaseQuad> &quad );
	
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

		void Update( const boost::shared_ptr<BaseQuad> &quad );

		void AddBox( const boost::shared_ptr<ObjectBox> &box );

		void AddQuad( const boost::shared_ptr<Quad> &quad );
		void AddQuad( const boost::shared_ptr<Quad> &quad, bool ChangeParent );

		void RemoveQuad( const boost::shared_ptr<BaseQuad> &quad );

		void ContainedDraw();

		boost::shared_ptr<Quad> ExtraQuadToDraw;
		boost::shared_ptr<EzTexture> ExtraQuadToDrawTexture;
		bool DrawExtraQuad;

		void Draw( bool UpdateFirst );

		boost::shared_ptr<SpriteAnim> AnimToSpriteFrames( int anim, int NumFrames, bool Loop, Vector2 Padding );
		boost::shared_ptr<SpriteAnim> AnimToSpriteFrames( int anim, int NumFrames, bool Loop, float StartT, float EndT, Vector2 Padding );

		boost::shared_ptr<Texture2D> DrawToTexture( const boost::shared_ptr<GraphicsDevice> &device, const boost::shared_ptr<EzEffectWad> &EffectWad, Vector2 Padding );

	
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef OBJECTCLASS
