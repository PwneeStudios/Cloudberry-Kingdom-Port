#ifndef BASEQUAD
#define BASEQUAD

#include <global_header.h>

#include "Hacks/NET/BinaryWriter.h"
#include "Hacks/NET/BinaryReader.h"

namespace CloudberryKingdom
{
	struct BaseQuad : public boost::enable_shared_from_this<BaseQuad>
	{
	
		ObjectDrawOrder MyDrawOrder;

		boost::shared_ptr<ObjectClass> ParentObject;
		boost::shared_ptr<Quad> ParentQuad;

		std::vector<MyOwnVertexFormat> Vertices;
		int NumVertices;

		/// <summary>
		/// Color rotation matrix.
		/// </summary>
		const Matrix &getMyMatrix() const;

		void setMyMatrix( const Matrix &value );

	
		Matrix _MyMatrix;
	
		float MyMatrixSignature;

		boost::shared_ptr<EzTexture> MyTexture;
		boost::shared_ptr<EzEffect> MyEffect;

		boost::shared_ptr<AnimationData_Texture> TextureAnim;
		bool UpdateSpriteAnim;
		bool getTextureIsAnimated() const;

		Color MyColor, PremultipliedColor;

		std::wstring Name;

		bool Is( const std::wstring &Name );

		bool Show;

		bool Released;

#if defined(EDITOR)
		bool Expanded; // Whether the tree node for this quad is expanded

		boost::shared_ptr<ObjectVector> ParentPoint, ChildPoint, ReleasePoint;
		bool SetToBeParent, SetToBeChild;
#endif

		void Clone( const boost::shared_ptr<BaseQuad> &quad );

		virtual void Release();

		virtual void Update();
		virtual void Update( float Expand );

		virtual void SetHold();
		virtual void ReadAnim( int anim, int frame );
		virtual void Record( int anim, int frame, bool UseRelativeCoords );
		virtual void Calc( int anim, float t, int AnimLength, bool Loop, bool Linear );
		virtual void Transfer( int anim, float DestT, int AnimLength, bool Loop, bool DestLinear, float t );

		virtual void CopyAnim( const boost::shared_ptr<BaseQuad> &quad, int Anim );
		virtual void CopyAnimShallow( const boost::shared_ptr<BaseQuad> &quad, int Anim );

		virtual void Write( const boost::shared_ptr<BinaryWriter> &writer );

		virtual void Read( const boost::shared_ptr<BinaryReader> &reader, const boost::shared_ptr<EzEffectWad> &EffectWad, const boost::shared_ptr<EzTextureWad> &TextureWad, int VersionNumber );

#if defined(EDITOR)
		virtual void SaveState( int StateIndex );

		virtual void RecoverState( int StateIndex );
#endif

		Vector2 BL();

		Vector2 TR();

		void SetTexture( const std::wstring &Name, const boost::shared_ptr<EzTextureWad> &Wad );

		void SetEffect( const std::wstring &Name, const boost::shared_ptr<EzEffectWad> &Wad );

		void OrphanSelf();

		virtual void FinishLoading( const boost::shared_ptr<GraphicsDevice> &device, const boost::shared_ptr<EzTextureWad> &TexWad, const boost::shared_ptr<EzEffectWad> &EffectWad );
		virtual void FinishLoading( const boost::shared_ptr<GraphicsDevice> &device, const boost::shared_ptr<EzTextureWad> &TexWad, const boost::shared_ptr<EzEffectWad> &EffectWad, bool UseNames );

		virtual void Draw();
		virtual void Draw( boost::shared_ptr<QuadDrawer> &QDrawer );
		virtual void DrawExtra( boost::shared_ptr<QuadDrawer> &QDrawer, bool Additional, float ScaleLines );
		virtual bool HitTest( Vector2 x );

#if defined(EDITOR)
		virtual std::vector<ObjectVector*> GetObjectVectors();

		void ColoredDraw( const boost::shared_ptr<QuadDrawer> &QDrawer, Color color );
#endif

		virtual void SetColor( Color color );

		virtual void Set_PosFromRelPos( const boost::shared_ptr<ObjectVector> &v );

		virtual void Set_RelPosFromPos( const boost::shared_ptr<ObjectVector> &v );

#if defined(EDITOR)
		virtual void ClickOnChildButton();

		void ClickOnReleaseButton();
#endif

	
		void InitializeInstanceFields();


		BaseQuad()
		{
			InitializeInstanceFields();
		}

		virtual ~BaseQuad()
		{
		}
	};
}


#endif	//#ifndef BASEQUAD
