#ifndef SIMPLEQUAD
#define SIMPLEQUAD

#include "Core/Graphics/Draw/Simple/SimpleVector.h"
#include "Core/Effects/EzEffect.h"

#include <global_header.h>

namespace CloudberryKingdom
{
	struct SimpleQuad
	{

	
		bool Animated;

		void NextKeyFrame();

		boost::shared_ptr<AnimationData_Texture> TextureAnim;
		void SetTextureAnim( const boost::shared_ptr<AnimationData_Texture> &TextureAnim );
		void Set( const boost::shared_ptr<TextureOrAnim> &t_or_a );
		void Set( const std::wstring &name );

		float t;

		int anim;
		bool Playing;
		float speed;
		bool Loop;

		void UpdateTextureAnim();

		bool UseGlobalIllumination;
		float Illumination;

	
		Vector2 uv0, uv1, uv2, uv3;

		Vector2 PreCalc0, PreCalc1, PreCalc2, PreCalc3;

	
		SimpleVector v0, v1, v2, v3;
		boost::shared_ptr<EzEffect> MyEffect;

		/// <summary>
		/// Extra textures used as input more advanced pixel shaders.
		/// </summary>
		boost::shared_ptr<EzTexture> ExtraTexture1, ExtraTexture2;

		/// <summary>
		/// Texture to be drawn on this quad.
		/// </summary>
		const boost::shared_ptr<EzTexture> &getMyTexture() const;
		void setMyTexture( const boost::shared_ptr<EzTexture> &value );
		boost::shared_ptr<EzTexture> _MyTexture;

		void CalcTexture( int anim, float frame );

	
		void map( Vector2 &base_uv, Vector2 &new_uv, Vector2 &bl, Vector2 &tr );

	
		bool Hide;

		bool U_Wrap, V_Wrap;

		std::wstring Name;

		void Release();

		SimpleQuad();

		SimpleQuad( const SimpleQuad &quad );

		SimpleQuad( const boost::shared_ptr<Quad> &quad );

		void SetTextureOrAnim( const boost::shared_ptr<TextureOrAnim> &t_or_a );
		void SetTextureOrAnim( const std::wstring &name );

		const int &getTexWidth() const;
		const int &getTexHeight() const;

		/// <summary>
		/// The name of the quad's texture. Setting will automatically search the TextureWad for a matching texture.
		/// </summary>
		const std::wstring &getTextureName() const;
		void setTextureName( const std::wstring &value );

		void EnforceTextureRatio();

		const Vector2 &getTR() const;
		const Vector2 &getBL() const;

		const float &getRight() const;
		const float &getLeft() const;
		const float &getTop() const;
		const float &getBottom() const;
		const float getWidth() const;
		const float getHeight() const;

		void Shift( Vector2 shift );

		void FromBounds( Vector2 BL, Vector2 TR );

		void RotateRight();

		void RotateLeft();

		void RotateUV();

		void MirrorUV_Vertical();

		void MirrorUV_Horizontal();

		const Vector2 getUV_Offset() const;
		void setUV_Offset( const Vector2 &value );
		const Vector2 getUV_Repeat() const;
		void setUV_Repeat( const Vector2 &value );

		void UV_Phsx( Vector2 speed );

		// v0 v1
		// v2 v3
		void UVFromBounds( Vector2 BL, Vector2 TR );

		void UVFromBounds_2( Vector2 BL, Vector2 TR );

		void Init();

		void DefaultCorners();

	
		bool IsDefault();

		/// <summary>
		/// Shift the quad's absolute vertex coordinates. Does not effect normal coordinates.
		/// </summary>
		/// <param name="shift"></param>
	
		void UpdatedShift( Vector2 shift );

		/// <summary>
		/// Copy and shift the source quad's vertex locations.
		/// </summary>
		/// <param name="SourceQuad">The source quad</param>
		/// <param name="shift">The amount to shift</param>
		void CopyUpdate( SimpleQuad &SourceQuad, Vector2 &shift );

		void UpdateShift( BasePoint &Base );

		void UpdateShift_Precalc( BasePoint &Base );

		void Update( BasePoint &Base );

		void SymmetricUpdate( BasePoint &Base );

		void SetHold();

		void ReadAnim( int anim, int frame );

		void Transfer( int anim, float DestT, int AnimLength, bool Loop, bool Linear, float t );

		void Calc( int anim, float t, int AnimLength, bool Loop, bool Linear );

		Color MySetColor, PremultipliedColor;
		float BlendAddRatio;
		void SetColor( Color color );
		void SetColor( Color color, bool ForceUpdate );
		void SetColor( Vector4 color );

		void SetAlpha( float alpha );

		void MultiplyAlpha( float alpha );
	};
}


#endif	//#ifndef SIMPLEQUAD
