#ifndef QUADCLASS
#define QUADCLASS

#include <global_header.h>

namespace CloudberryKingdom
{
	class SpriteInfo;
}

namespace CloudberryKingdom
{
	class FancyVector2;
}

namespace CloudberryKingdom
{
	class Quad;
}

namespace CloudberryKingdom
{
	class Camera;
}

namespace CloudberryKingdom
{
	class EzTexture;
}

namespace CloudberryKingdom
{
	class TextureOrAnim;
}





namespace CloudberryKingdom
{
	class QuadClass : public ViewReadWrite
	{
#if defined(WINDOWS)
	public:
		virtual std::vector<std::wstring> GetViewables();

		virtual void ProcessMouseInput( Vector2 shift, bool ShiftDown );
#endif

		static std::shared_ptr<QuadClass> FindQuad( std::vector<QuadClass*> &list, const std::wstring &Name );

		bool HitTest( Vector2 pos );
		bool HitTest( Vector2 pos, Vector2 padding );

		bool HitTest_WithParallax( Vector2 pos, Vector2 padding, float Parallax );

		const Vector2 &getTR() const;
		const Vector2 &getBL() const;

		const float &getLeft() const;
		void setLeft( const float &value );

		const float &getX() const;
		void setX( const float &value );
		const float &getY() const;
		void setY( const float &value );

		bool Shadow;
		Vector2 ShadowOffset;
		Color ShadowColor;
		float ShadowScale;

//C# TO C++ CONVERTER NOTE: The variable Quad was renamed since it is named the same as a user-defined type:
		SimpleQuad Quad_Renamed;
		BasePoint Base;

		std::shared_ptr<FancyVector2> FancyPos, FancyScale, FancyAngle;

		std::shared_ptr<FancyVector2> FancyLightAlpha;
		void MakeLightAlpha();

		void SetDefaultShadow();
		void SetDefaultShadow( float Offset );
		void SetDefaultShadow( Vector2 offset, Color color );

		/// <summary>
		/// Name of the quad, used in DrawPiles
		/// </summary>
		std::wstring Name;

		/// <summary>
		/// Layer of the quad, used in DrawPiles
		/// </summary>
		int Layer;

		void MakeFancyPos();

		void Release();

		const Vector2 &getLightAlpha() const;
		void setLightAlpha( const Vector2 &value );

		const Vector2 &getPos() const;
		void setPos( const Vector2 &value );
		const float &getPosY() const;
		void setPosY( const float &value );

		const float &getSizeX() const;
		void setSizeX( const float &value );
		const float &getSizeY() const;
		void setSizeY( const float &value );
		const Vector2 &getSize() const;
		void setSize( const Vector2 &value );

		const float &getDegrees() const;
		void setDegrees( const float &value );

		const float &getAngle() const;
		void setAngle( const float &value );

		QuadClass( const std::shared_ptr<Quad> &quad );

		QuadClass( const std::shared_ptr<QuadClass> &quad );

		QuadClass();
		QuadClass( const std::shared_ptr<FancyVector2> &Center );
		QuadClass( const std::shared_ptr<FancyVector2> &Center, bool UseFancySize );
		QuadClass( const std::shared_ptr<FancyVector2> &Center, bool UseFancySize, bool UseFancyAngle );

		void Initialize( const std::shared_ptr<FancyVector2> &Center, bool UseFancySize, bool UseFancyAngle );

		/// <summary>
		/// The name of the quad's texture. Setting will automatically search the TextureWad for a matching texture.
		/// </summary>
		const std::wstring &getTextureName() const;
		void setTextureName( const std::wstring &value );

		/// <summary>
		/// The name of the quad's Effect. Setting will automatically search the EffectWad for a matching Effect.
		/// </summary>
		const std::wstring &getEffectName() const;
		void setEffectName( const std::wstring &value );

		std::shared_ptr<QuadClass> Clone();

		/// <summary>
		/// Copy this quads' properties TO another quad
		/// </summary>
		void Clone( const std::shared_ptr<QuadClass> &quad );

		void SetTexture( const std::wstring &Name );

		float WidthToScreenWidthRatio( const std::shared_ptr<Camera> &cam );

		/// <summary>
		/// Sets the size to the given Vector2.
		/// If a given component is negative, then the quad's aspect ratio is maintained.
		/// </summary>
		void SetSize( Vector2 size );

		void ScaleToTextureSize();

		void Rescale( Vector2 size );

		void Scale( float scale );

		/// <summary>
		/// Gets the scaling of the quad relative to its texture's size
		/// </summary>
		Vector2 GetTextureScaling();

		void ScaleXToMatchRatio();
		void ScaleXToMatchRatio( float height );

		void ScaleYToMatchRatio();
		void ScaleYToMatchRatio( float width );

		void RepeatY();

		void PointxAxisTo( float Radians );

		void PointxAxisTo( Vector2 Dir );

		void TextureParralax( float Parralax, Vector2 repeat, Vector2 shift, const std::shared_ptr<Camera> &Cam );

		void FullScreen( const std::shared_ptr<Camera> &cam );

		void FromBounds( Vector2 BL, Vector2 TR );

		void SetToDefault();

		QuadClass( const std::shared_ptr<EzTexture> &texture );
		QuadClass( const std::wstring &name );

		QuadClass( const std::wstring &TextureName, float Width );
		QuadClass( const std::wstring &TextureName, const std::wstring &Name );
		QuadClass( const std::shared_ptr<EzTexture> &Texture, float Width, const std::wstring &Name );
		QuadClass( const std::shared_ptr<EzTexture> &Texture, float Width, bool Fancy );
		QuadClass( const std::wstring &TextureName, float Width, bool Fancy );
		void Set( const std::wstring &TextureName, float Width );
		void Set( const std::shared_ptr<EzTexture> &Texture, float Width );
		void Set( const std::shared_ptr<TextureOrAnim> &t_or_a );
		void Set( const std::wstring &name );

		void Set( const std::shared_ptr<SpriteInfo> &info );
		virtual void Set( const std::shared_ptr<SpriteInfo> &info, Vector2 Size );

		void Draw();
		void DrawShadow();

		/// <summary>
		/// If this quad is an element in a bigger structure (such as a DrawPile),
		/// this vector represents the scaling of the parent structure.
		/// </summary>
		Vector2 ParentScaling;
		float ParentAlpha;

		void MultiplyAlpha( float alpha );

		const float &getAlpha() const;
		void setAlpha( const float &value );

	private:
		bool Fading;
		float FadeSpeed;
	public:
		void Fade( float speed );

		void ResetFade();

		/// <summary>
		/// When the alpha of this quad is being automatically changed (via FadeSpeed),
		/// the alpha value is always restricted between this min and max.
		/// </summary>
		float MinAlpha, MaxAlpha;

		bool Show;
		virtual void Draw( bool Update, bool DrawQuad, bool DrawShadow );

		void UpdateShift();

		void UpdateShift_Precalc();

		void Update();

		void Write( const std::shared_ptr<BinaryWriter> &writer );
		void Read( const std::shared_ptr<BinaryReader> &reader );

	private:
		void InitializeInstanceFields();
	};

	class HsvQuad : public QuadClass
	{
		/// <summary>
		/// Color rotation matrix.
		/// </summary>
	public:
		const Matrix &getMyMatrix() const;

		void setMyMatrix( const Matrix &value );
	private:
		Matrix _MyMatrix;
		float _MyMatrixSignature;

	public:
		HsvQuad();

		virtual void Set( const std::shared_ptr<SpriteInfo> &info, Vector2 Size );

		virtual void Draw( bool Update, bool DrawQuad, bool DrawShadow );
	};
}


#endif	//#ifndef QUADCLASS
