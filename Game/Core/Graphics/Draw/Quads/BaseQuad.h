#ifndef BASEQUAD
#define BASEQUAD

#include <global_header.h>

#include "Hacks/NET/BinaryWriter.h"
#include "Hacks/NET/BinaryReader.h"

namespace CloudberryKingdom
{
	struct BaseQuad : public std::enable_shared_from_this<BaseQuad>
	{
	
		ObjectDrawOrder MyDrawOrder;

		std::shared_ptr<ObjectClass> ParentObject;
		std::shared_ptr<Quad> ParentQuad;

		std::vector<MyOwnVertexFormat> Vertices;
		int NumVertices;

		/// <summary>
		/// Color rotation matrix.
		/// </summary>
		const Matrix &getMyMatrix() const;

		void setMyMatrix( const Matrix &value );

	
		Matrix _MyMatrix;
	
		float MyMatrixSignature;

		std::shared_ptr<EzTexture> MyTexture;
		std::shared_ptr<EzEffect> MyEffect;

		std::shared_ptr<AnimationData_Texture> TextureAnim;
		bool UpdateSpriteAnim;
		bool getTextureIsAnimated() const;

		Color MyColor, PremultipliedColor;

		std::wstring Name;

		bool Is( const std::wstring &Name );

		bool Show;

		bool Released;

#if defined(EDITOR)
		bool Expanded; // Whether the tree node for this quad is expanded

		std::shared_ptr<ObjectVector> ParentPoint, ChildPoint, ReleasePoint;
		bool SetToBeParent, SetToBeChild;
#endif

		void Clone( const std::shared_ptr<BaseQuad> &quad );

		virtual void Release();

		virtual void Update();
		virtual void Update( float Expand );

		virtual void SetHold();
		virtual void ReadAnim( int anim, int frame );
		virtual void Record( int anim, int frame, bool UseRelativeCoords );
		virtual void Calc( int anim, float t, int AnimLength, bool Loop, bool Linear );
		virtual void Transfer( int anim, float DestT, int AnimLength, bool Loop, bool DestLinear, float t );

		virtual void CopyAnim( const std::shared_ptr<BaseQuad> &quad, int Anim );
		virtual void CopyAnimShallow( const std::shared_ptr<BaseQuad> &quad, int Anim );

		virtual void Write( const std::shared_ptr<BinaryWriter> &writer );

		virtual void Read( const std::shared_ptr<BinaryReader> &reader, const std::shared_ptr<EzEffectWad> &EffectWad, const std::shared_ptr<EzTextureWad> &TextureWad, int VersionNumber );

#if defined(EDITOR)
		virtual void SaveState( int StateIndex );

		virtual void RecoverState( int StateIndex );
#endif

		Vector2 BL();

		Vector2 TR();

		void SetTexture( const std::wstring &Name, const std::shared_ptr<EzTextureWad> &Wad );

		void SetEffect( const std::wstring &Name, const std::shared_ptr<EzEffectWad> &Wad );

		void OrphanSelf();

		virtual void FinishLoading( const std::shared_ptr<GraphicsDevice> &device, const std::shared_ptr<EzTextureWad> &TexWad, const std::shared_ptr<EzEffectWad> &EffectWad );
		virtual void FinishLoading( const std::shared_ptr<GraphicsDevice> &device, const std::shared_ptr<EzTextureWad> &TexWad, const std::shared_ptr<EzEffectWad> &EffectWad, bool UseNames );

		virtual void Draw();
		virtual void Draw( std::shared_ptr<QuadDrawer> &QDrawer );
		virtual void DrawExtra( std::shared_ptr<QuadDrawer> &QDrawer, bool Additional, float ScaleLines );
		virtual bool HitTest( Vector2 x );

#if defined(EDITOR)
		virtual std::vector<ObjectVector*> GetObjectVectors();

		void ColoredDraw( const std::shared_ptr<QuadDrawer> &QDrawer, Color color );
#endif

		virtual void SetColor( Color color );

		virtual void Set_PosFromRelPos( const std::shared_ptr<ObjectVector> &v );

		virtual void Set_RelPosFromPos( const std::shared_ptr<ObjectVector> &v );

#if defined(EDITOR)
		virtual void ClickOnChildButton();

		void ClickOnReleaseButton();
#endif

	
		void InitializeInstanceFields();


		BaseQuad()
		{
			InitializeInstanceFields();
		}
	};
}


#endif	//#ifndef BASEQUAD
