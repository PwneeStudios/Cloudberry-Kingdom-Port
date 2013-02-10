#ifndef QUADDRAWER
#define QUADDRAWER

#include <global_header.h>

#include "Core/Graphics/VertexFormat.h"
#include "Core/Graphics/Draw/Simple/SimpleVector.h"
#include "Core/Graphics/Draw/Simple/SimpleQuad.h"
#include "Core/Animation/SpriteAnim.h"
#include "Core/Effects/EzEffectWad.h"
#include "Core/Effects/EzEffect.h"
#include "Core/Graphics/MainRender.h"
#include "Core/Graphics/Draw/Quads/BaseQuad.h"
#include "Core/Graphics/Draw/Quads/Quad.h"
#include "Core/Graphics/Draw/Quads/QuadClass.h"
#include "Core/Graphics/Draw/Simple/SimpleBox.h"
#include "Core/Graphics/Draw/Simple/SimpleObject.h"

#include <Hacks\XNA\SamplerState.h>
#include <Hacks\Dict.h>

namespace CloudberryKingdom
{

    struct GlyphData
    {

        Vector4 TextureCoordinates;
        Vector2 Size;
        Vector2 Offset;

		GlyphData();
        GlyphData(Vector4 TextureCoordinates_, Vector2 Size_, Vector2 Offset_);

	};

	struct HackFont
    {

        std::map<int, GlyphData> Data;

        /// Texture path.
        std::wstring texturePath_;

        /// Spacing offset between characters.
        int charSpacing_;

		boost::shared_ptr<EzTexture> MyTexture;

        GlyphData GetData( wchar_t c );

        float CharSpacing;

        HackFont(std::string name);

    };

    struct HackSpriteFont
    {

        boost::shared_ptr<HackFont> font;
        int thickness;

        HackSpriteFont( boost::shared_ptr<HackFont> font_, int thickness_ );

    };


	struct QuadDrawer
	{
	
		static void InitializeStatics();

	
		boost::shared_ptr<GraphicsDevice> Device;

	
		boost::shared_ptr<EzEffect> DefaultEffect;
		boost::shared_ptr<EzTexture> DefaultTexture;

	
		boost::shared_ptr<EzEffect> CurrentEffect;
		boost::shared_ptr<EzTexture> CurrentTexture;

		/// <summary>
		/// Color rotation matrix.
		/// </summary>
		const Matrix &getCurrentMatrix() const;

		void setCurrentMatrix( const Matrix &value );
		Matrix _CurrentMatrix;
	
		float CurrentMatrixSignature;
	
		bool Current_U_Wrap, Current_V_Wrap;
	
		std::vector<MyOwnVertexFormat> Vertices;
		int N;
		int TrianglesInBuffer;
	
		int i;

		SimpleQuad LineQuad;

		boost::shared_ptr<SamplerState> WrapWrap, ClampWrap, WrapClamp, ClampClamp;

	
		const float &getGlobalIllumination() const;
		void setGlobalIllumination( const float &value );
	
		float _GlobalIllumination;
		float Illumination;

		//float CurrentIllumination = 1f;
		//public void InvalidateIllumination() { CurrentIllumination = -1; }

	
		QuadDrawer( const boost::shared_ptr<GraphicsDevice> &device, int n );

		void SetColorMatrix( Matrix m, float signature );

		void DrawQuad( const boost::shared_ptr<Quad> &quad );

		void SetInitialState();

	
		void SetSamplerState();

	
		void SetAddressMode( bool U_Wrap, bool V_Wrap );

		void DrawQuad_Particle( SimpleQuad &quad );

		void DrawQuad( SimpleQuad &quad );

		void DrawFilledBox( Vector2 BL, Vector2 TR, Color color );

		void DrawLine( Vector2 x1, Vector2 x2, const boost::shared_ptr<LineSpriteInfo> &info );
		void DrawLine( Vector2 x1, Vector2 x2, const boost::shared_ptr<LineSpriteInfo> &info, Vector4 Tint, float Width );
		void DrawLine( Vector2 x1, Vector2 x2, const boost::shared_ptr<LineSpriteInfo> &info, Vector4 Tint, float Width, float v_shift );
		void DrawLine( Vector2 x1, Vector2 x2, Color color, float width );
		void DrawLine( Vector2 x1, Vector2 x2, Color color, float width, const boost::shared_ptr<EzTexture> &Tex, const boost::shared_ptr<EzEffect> &fx, float RepeatWidth, int Dir, bool Illumination );
		void DrawLine( Vector2 x1, Vector2 x2, Color color, float width, const boost::shared_ptr<EzTexture> &Tex, const boost::shared_ptr<EzEffect> &fx, float RepeatWidth, int Dir, float BlendAddRatio );
		void DrawLine( Vector2 x1, Vector2 x2, Color color, float width, const boost::shared_ptr<EzTexture> &Tex, const boost::shared_ptr<EzEffect> &fx, float RepeatWidth, int Dir, float BlendAddRatio, float v_shift, bool Wrap );

		void DrawLineAndEndPoints( Vector2 x1, Vector2 x2, Color color, float width, const boost::shared_ptr<EzTexture> &Tex1, const boost::shared_ptr<EzTexture> &Tex2, const boost::shared_ptr<EzTexture> &Tex3, const boost::shared_ptr<EzEffect> &fx, float RepeatWidth, int Dir, float BlendAddRatio, float v_shift );

		void DrawCircle( Vector2 x, float r, Color color );

	
		static float CurLightSourceFade;
	
		void DrawLightSource( Vector2 x, float r, float Fade, Color color );

		void DrawSquareDot( Vector2 x, Color color, float width );
		void DrawSquareDot( Vector2 x, Color color, float width, const boost::shared_ptr<EzTexture> &Tex, const boost::shared_ptr<EzEffect> &fx );


		void DrawToScaleQuad( Vector2 x, Color color, float width );
		void DrawToScaleQuad( Vector2 x, Color color, float width, const boost::shared_ptr<EzTexture> &Tex, const boost::shared_ptr<EzEffect> &fx );

		void DrawBox( Vector2 BL, Vector2 TR, Color color, float width );

		void SetToDefaultTexture();

		/// <summary>
		/// Makes sure the current texture isn't set to any RenderTargets
		/// </summary>
		void WashTexture();

		void Flush();

	
		void InitializeInstanceFields();


		void DrawPic(Vector2 pos, Vector2 pos2, boost::shared_ptr<EzTexture> texture, Color color);
		void DrawString(boost::shared_ptr<HackSpriteFont> spritefont, std::wstring s, Vector2 position, Vector4 color, Vector2 scale);
		void DrawString(boost::shared_ptr<HackSpriteFont> spritefont, boost::shared_ptr<StringBuilder> s, Vector2 position, Vector4 color, Vector2 scale);
		Vector2 MeasureString(boost::shared_ptr<HackSpriteFont> spritefont, std::wstring s);
		Vector2 MeasureString(boost::shared_ptr<HackSpriteFont> spritefont, boost::shared_ptr<StringBuilder> s);

		void DrawCircleDot( Vector2 pos );

	};
}


#endif	//#ifndef QUADDRAWER
