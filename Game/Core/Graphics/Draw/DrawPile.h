#ifndef DRAWPILE
#define DRAWPILE

#include <global_header.h>

namespace CloudberryKingdom
{
	struct DrawPile : public boost::enable_shared_from_this<DrawPile>
	{

	
		static void InitializeStatics();

	
		struct WaitThenPop : public Lambda
		{
		
			boost::shared_ptr<DrawPile> MyDrawPile_;
		
			WaitThenPop( const boost::shared_ptr<DrawPile> &MyDrawPile );

			void Apply();
		};

	
		struct WaitThenPop2 : public Lambda
		{
		
			void Apply();
		};
	

		boost::shared_ptr<FancyVector2> FancyScale;
		const Vector2 &getSize() const;
		void setSize( const Vector2 &value );

		boost::shared_ptr<FancyVector2> FancyPos;
		const Vector2 &getPos() const;
		void setPos( const Vector2 &value );

		std::vector<boost::shared_ptr<EzText> > MyTextList;
		std::vector<boost::shared_ptr<QuadClass> > MyQuadList;

		DrawPile();

		DrawPile( const boost::shared_ptr<FancyVector2> &Center );

		void Clear();

		void Add( const boost::shared_ptr<QuadClass> &quad );
		void Add( const boost::shared_ptr<QuadClass> &quad, const std::wstring &name );
		void Add( const boost::shared_ptr<QuadClass> &quad, bool KeepFancyCenter, const std::wstring &name );

		void Insert( int index, const boost::shared_ptr<QuadClass> &quad );

		void Add( const boost::shared_ptr<EzText> &text );

		void Add( const boost::shared_ptr<EzText> &text, const std::wstring &name );

		void Remove( const boost::shared_ptr<EzText> &text );

		boost::shared_ptr<QuadClass> FindQuad( const std::wstring &Name );

		boost::shared_ptr<EzText> FindEzText( const std::wstring &Name );

		float AlphaVel;

		boost::shared_ptr<FancyColor> MyFancyColor;
		float getAlpha();
		void setAlpha( const float &value );

		void Scale( float scale );

	
		std::vector<Vector2> SavedScales, SavedPositions, SavedShadowOffsets;
	
		void SaveScale();

		void RevertScale();

		void Update();

		void Draw();
		void Draw( int Layer );

		void DrawNonText( int Layer );

		void DrawText( int Layer );

		OscillateParams MyOscillateParams;
		void Draw( bool Selected );

		bool Fading;
		float FadeSpeed;
		void FadeIn( float speed );
		void FadeOut( float speed );
	
		void Fade();

	
		void BubbleDownAndFade( bool sound );

		static std::vector<Vector2> BubbleScale;
		void BubbleUp( bool sound );
		void BubbleUp( bool sound, int Length, float Intensity );

		/// <summary>
		/// The pitch of the pop noise when the draw pile is popped. Must be 1, 2, 3.
		/// </summary>
		int MyPopPitch;
		void BubbleDown( bool sound );
		void BubbleDown( bool sound, int Length );
	
	
		static std::vector<Vector2> JiggleScale;

	
		void Jiggle( bool sound );
		void Jiggle( bool sound, int Length, float Intensity );


	
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef DRAWPILE
