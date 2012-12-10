#ifndef QUAD
#define QUAD

#include <global_header.h>

#include "Hacks/NET/BinaryWriter.h"
#include "Hacks/NET/BinaryReader.h"

namespace CloudberryKingdom
{
	struct Quad : public BaseQuad
	{
	
		struct UpdateCenterLambda : public Lambda_1<Vector2>
		{
		
			std::shared_ptr<Quad> quad;
		
			UpdateCenterLambda( const std::shared_ptr<Quad> &quad );

			void Apply( const Vector2 &NewPos );
		};

	
		struct UpdatexAxisLambda : public Lambda_1<Vector2>
		{
		
			std::shared_ptr<Quad> quad;
		
			UpdatexAxisLambda( const std::shared_ptr<Quad> &quad );

			void Apply( const Vector2 &NewPos );
		};

	
		struct UpdateyAxisLambda : public Lambda_1<Vector2>
		{
		
			std::shared_ptr<Quad> quad;
		
			UpdateyAxisLambda( const std::shared_ptr<Quad> &quad );

			void Apply( const Vector2 &NewPos );
		};

	
		std::shared_ptr<ObjectVector> Center, xAxis, yAxis;
		std::vector<std::shared_ptr<ObjectVector> > Corner;

		std::vector<std::shared_ptr<BaseQuad> > Children;

		virtual void Release();

		void Resize();

		void MirrorUV_Horizontal();

		virtual void CopyAnim( const std::shared_ptr<BaseQuad> &basequad, int Anim );

		virtual void CopyAnimShallow( const std::shared_ptr<BaseQuad> &basequad, int Anim );

		virtual void SetHold();

		virtual void ReadAnim( int anim, int frame );

		virtual void Record( int anim, int frame, bool UseRelativeCoords );

	
		void ModifyAxis( const std::shared_ptr<ObjectVector> &axis, int anim, int frame, ChangeMode RecordMode );

		Vector2 ToAxisCoordinates( Vector2 v, Vector2 xAxisPos, Vector2 yAxisPos );
		Vector2 FromAxisCoordinates( Vector2 v, Vector2 xAxisPos, Vector2 yAxisPos );

		void ModifyPoint( const std::shared_ptr<ObjectVector> &point, int anim, int frame, ChangeMode RecordMode );

	
		void ModifyAllRecords( int anim, int frame, ChangeMode RecordMode );

		void ShowChildren();

		void HideChildren();

		virtual void Transfer( int anim, float DestT, int AnimLength, bool Loop, bool Linear, float t );

		virtual void Calc( int anim, float t, int AnimLength, bool Loop, bool Linear );


		virtual void Write( const std::shared_ptr<BinaryWriter> &writer );

		virtual void Read( const std::shared_ptr<BinaryReader> &reader, const std::shared_ptr<EzEffectWad> &EffectWad, const std::shared_ptr<EzTextureWad> &TextureWad, int VersionNumber );

#if defined(EDITOR)
		virtual void SaveState( int StateIndex );

		virtual void RecoverState( int StateIndex );
#endif
		std::vector<std::shared_ptr<BaseQuad> > GetAllChildren();

		virtual bool HitTest( Vector2 x );

#if defined(EDITOR)
		virtual std::vector<ObjectVector*> GetObjectVectors();
#endif

		void RemoveQuadChild( const std::shared_ptr<BaseQuad> &child );
		void RemoveQuadChild( const std::shared_ptr<BaseQuad> &child, bool AddToRoot );


		void AddQuadChild( const std::shared_ptr<BaseQuad> &child, bool KeepNumericData );

		void AddQuadChild( const std::shared_ptr<BaseQuad> &child );

#if defined(EDITOR)
		virtual void ClickOnParentButton();
#endif

		virtual void FinishLoading( const std::shared_ptr<GraphicsDevice> &device, const std::shared_ptr<EzTextureWad> &TexWad, const std::shared_ptr<EzEffectWad> &EffectWad );
		virtual void FinishLoading( const std::shared_ptr<GraphicsDevice> &device, const std::shared_ptr<EzTextureWad> &TexWad, const std::shared_ptr<EzEffectWad> &EffectWad, bool UseNames );

	
		void InitVertices();

	
		void ScaleCorners( Vector2 size );

		Quad( const std::shared_ptr<Quad> &quad, bool DeepClone );

		Quad();


		Vector2 getSize() const;
		void setSize( const Vector2 &value );

		void Scale( Vector2 Stretch );

		void PointxAxisTo( Vector2 dir );

		Vector2 CalcBLBound();

		Vector2 CalcTRBound();

		using BaseQuad::Update;
		virtual void Update( float Expand );

		virtual void Set_PosFromRelPos( const std::shared_ptr<ObjectVector> &v );

		virtual void Set_RelPosFromPos( const std::shared_ptr<ObjectVector> &v );

		virtual void Draw();

		virtual void Draw( std::shared_ptr<QuadDrawer> &Drawer );

#if defined(EDITOR)
		void DrawChildren( const std::shared_ptr<QuadDrawer> &Drawer );

		virtual void DrawExtra( const std::shared_ptr<QuadDrawer> &Drawer, bool Additional, float ScaleLines );
#endif
	};
}


#endif	//#ifndef QUAD
