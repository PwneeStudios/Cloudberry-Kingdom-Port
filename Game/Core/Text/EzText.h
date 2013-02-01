#ifndef EZTEXT
#define EZTEXT

#include <global_header.h>

#include "Game/Localization.h"

#include "Hacks/NET/StringBuilder.h"
#include "Hacks/XNA/Rectangle.h"

namespace CloudberryKingdom
{

	struct ButtonTexture
	{

        static boost::shared_ptr<EzTexture> getGo();
        static boost::shared_ptr<EzTexture> getBack();

#if PC_VERSION
        static boost::shared_ptr<EzTexture> _Go();
        static boost::shared_ptr<EzTexture> _Back();
        static boost::shared_ptr<EzTexture> getX();
        static boost::shared_ptr<EzTexture> getY();
        static boost::shared_ptr<EzTexture> getLeftRight();
        static boost::shared_ptr<EzTexture> getLeftBumper();
		static boost::shared_ptr<EzTexture> getRightBumper();
#elif PS3
        static boost::shared_ptr<EzTexture> _Go();
        static boost::shared_ptr<EzTexture> _Back();
        static boost::shared_ptr<EzTexture> getX();
        static boost::shared_ptr<EzTexture> getY();
        static boost::shared_ptr<EzTexture> getLeftRight();
        static boost::shared_ptr<EzTexture> getLeftBumper();
        static boost::shared_ptr<EzTexture> getRightBumper();
#elif CAFE
        static bool UseGamepad;
        static boost::shared_ptr<EzTexture> _Go();
        static boost::shared_ptr<EzTexture> _Back();
        static boost::shared_ptr<EzTexture> getX();
        static boost::shared_ptr<EzTexture> getY();
        static boost::shared_ptr<EzTexture> getLeftRight();
        static boost::shared_ptr<EzTexture> getLeftBumper();
        static boost::shared_ptr<EzTexture> getRightBumper();
#else
        static boost::shared_ptr<EzTexture> _Go();
        static boost::shared_ptr<EzTexture> _Back();
        static boost::shared_ptr<EzTexture> getX();
        static boost::shared_ptr<EzTexture> getY();
        static boost::shared_ptr<EzTexture> getLeftRight();
        static boost::shared_ptr<EzTexture> getLeftBumper();
        static boost::shared_ptr<EzTexture> getRightBumper();
#endif

	};

	struct ButtonString
	{

#if defined(PC_VERSION)
		static std::map<Keys, std::wstring> KeyToString;
		static void Init();

		static void SetKeyFromString( Keys &key, const std::wstring &str );

		static std::wstring KeyToTexture( Keys key );
		static boost::shared_ptr<EzTexture> ActualKeyToTexture( Keys key );

		// Go/Back small keys
		//public static string Back(int size) { return string.Format("{{p{1},{0},?}}{{s15,0}}", size, KeyToTexture(ButtonCheck.Back_Secondary)); }
		//public static string Go(int size) { return string.Format("{{p{1},{0},?}}{{s15,0}}", size, KeyToTexture(ButtonCheck.Go_Secondary)); }

		// Go/Back big keys
		//public static string Back(int size) { return string.Format("{{p{1},{0},?}}{{s15,0}}", size, KeyToTexture(Keys.Back)); }
		//public static string Go(int size) { return string.Format("{{p{1},{0},?}}{{s15,0}}", size, KeyToTexture(Keys.Enter)); }

		// Go/Back no keys
		static std::wstring Back( int size );
		static std::wstring Go( int size );

		static std::wstring Backspace( int size );
		static std::wstring Enter( int size );

		static std::wstring X( int size );
		static std::wstring Y( int size );
		static std::wstring LeftRight( int size );
		static std::wstring LeftBumper( int size );
		static std::wstring RightBumper( int size );
		static std::wstring Up( int size );
		static std::wstring Jump( int size );

		// Regular keys
		static std::wstring KeyStr( Keys key, int size );

		// Sane
		//public static float BackScale = 1.3f;
		//public static string Back(int size) { return string.Format("{{pBackspace_Key,{0},?}}{{s15,0}}", size * BackScale); }
		//public static string Go(int size) { return string.Format("{{pEnterKey,{0},?}}{{s15,0}}", size * BackScale); }
		//public static string X(int size) { return string.Format("{{pC_Key,{0},?}}{{s15,0}}", size); }
		//public static string Y(int size) { return string.Format("{{pV_Key,{0},?}}{{s15,0}}", size); }
		//public static string LeftRight(int size) { return string.Format("{{pLeftRight_Key,{0},?}}{{s15,0}}", size); }
		//public static string LeftBumper(int size) { return string.Format("{{pSpaceKey,{0},?}}{{s15,0}}", size * BackScale); }
		//public static string RightBumper(int size) { return string.Format("{{pD_Key,{0},?}}{{s15,0}}", size); }
		//public static string Up(int size) { return string.Format("{{pUp_Key,{0},?}}{{s15,0}}", size); }
		//public static string Jump(int size) { return string.Format("{{pUp_Key,{0},?}}{{s15,0}}", size); }

		// Old school
		//public static string Back(int size) { return string.Format("{{pX_Key,{0},?}}{{s15,0}}", size); }
		//public static string Go(int size) { return string.Format("{{pZ_Key,{0},?}}{{s15,0}}", size); }
		//public static string X(int size) { return string.Format("{{pC_Key,{0},?}}{{s15,0}}", size); }
		//public static string Y(int size) { return string.Format("{{pV_Key,{0},?}}{{s15,0}}", size); }
		//public static string LeftRight(int size) { return string.Format("{{pLeftRight_Key,{0},?}}{{s15,0}}", size); }
		//public static string LeftBumper(int size) { return string.Format("{{pA_Key,{0},?}}{{s15,0}}", size); }
		//public static string RightBumper(int size) { return string.Format("{{pD_Key,{0},?}}{{s15,0}}", size); }
		//public static string Up(int size) { return string.Format("{{pUp_Key,{0},?}}{{s15,0}}", size); }
		//public static string Jump(int size) { return string.Format("{{pUp_Key,{0},?}}{{s15,0}}", size); }

		static std::wstring Go_Controller( int size );
#else
		static void Init();
		static std::wstring Back( int size );
		static std::wstring Go( int size );
		static std::wstring X( int size );
		static std::wstring Y( int size );
		static std::wstring LeftRight( int size );
		static std::wstring LeftBumper( int size );
		static std::wstring RightBumper( int size );
		static std::wstring Jump( int size );
#endif
	};

	struct EzText
	{

	
		static void InitializeStatics();

	
		struct EzTextBit
		{
		
			int LineNumber;
			std::wstring str;
			boost::shared_ptr<StringBuilder> builder_str;
			Vector2 loc, size;
			Color clr;
		};
	
		struct EzTextPic
		{
		
			int LineNumber;
			boost::shared_ptr<EzTexture> tex;
			Rectangle rect;
			Vector2 size;
			bool AsPaint;
		};
	
		enum Style
		{
			Style_NORMAL,
			Style_FADING_OFF
		};
	
		enum ParseData
		{
			ParseData_PIC,
			ParseData_COLOR
		};
	

		static std::wstring ColorToMarkup( int r, int g, int b );
		static std::wstring ColorToMarkup( int r, int g, int b, int shift );
		static std::wstring ColorToMarkup( int r, int g, int b, int shift, const std::wstring &bit );
		static std::wstring ColorToMarkup( Color clr );
		static std::wstring ColorToMarkup( Color clr, int shift );
		static std::wstring ColorToMarkup( Color clr, int shift, const std::wstring &bit );

		/// <summary>
		/// Name of the text, used in DrawPiles
		/// </summary>
		std::wstring Name;

		/// <summary>
		/// Layer of the text, used in DrawPiles
		/// </summary>
		int Layer;

		bool HitTest( Vector2 pos );
		bool HitTest( Vector2 pos, Vector2 padding );

	
		std::vector<boost::shared_ptr<EzTextBit> > Bits;
		std::vector<boost::shared_ptr<EzTextPic> > Pics;

		/// <summary>
		/// Replaces the first bit of text, with no reformatting
		/// </summary>
	
		Vector2 EzText::MeasureString( std::wstring text );
		Vector2 EzText::MeasureString( boost::shared_ptr<StringBuilder> text );

		void SubstituteText( const std::wstring &text );
		void SubstituteText( const boost::shared_ptr<StringBuilder> &text );
		void SubstituteText( Localization::Words word );

		/// <summary>
		/// Appends the given text to the first bit of text, with no reformatting
		/// </summary>
		void AppendText( const std::wstring &text );

		/// <summary>
		/// Appends the given character to the first bit of text, with no reformatting
		/// </summary>
		void AppendText( wchar_t character );

		/// <summary>
		/// Returns the string from the first bit of text
		/// </summary>
		/// <returns></returns>
		std::wstring FirstString();

		bool FixedToCamera;

		bool ColorizePics;
	
		Color PicColor;

	
		boost::shared_ptr<EzFont> MyFont;
	
		Color MyColor;
	
		Vector4 MyFloatColor;

		Vector2 TR, BL;

		void MakeFancyPos();

		/// <summary>
		/// If this quad is an element in a bigger structure (such as a DrawPile),
		/// this vector represents the scaling of the parent structure.
		/// </summary>
		Vector2 ParentScaling;
		float ParentAlpha;

		Vector2 _Pos;
		const Vector2 &getPos() const;
		void setPos( const Vector2 &value );
		const float &getX() const;
		void setX( const float &value );
		const float &getY() const;
		void setY( const float &value );

		boost::shared_ptr<FancyVector2> FancyPos;
		float TextBoxWidth;
		float Height, TextWidth;

		std::wstring MyString;

		int Code;

		Vector4 OutlineColor;

		bool Shadow;
		bool PicShadow;
		Vector2 ShadowOffset;
		Color ShadowColor;
		float ShadowScale;

		float Alpha, AlphaVel;

		float _Scale;
		void setScale( const float &value );
		const float &getScale() const;

		void Release();

		virtual boost::shared_ptr<EzText> Clone();

		bool RightJustify;
		bool Centered, YCentered;

		EzText( Localization::Words word );
		EzText( Localization::Words word, const boost::shared_ptr<EzFont> &font );
		EzText( Localization::Words word, const boost::shared_ptr<EzFont> &font, const std::wstring &Name );
		EzText( Localization::Words word, const boost::shared_ptr<EzFont> &font, bool Centered );
		EzText( Localization::Words word, const boost::shared_ptr<EzFont> &font, bool Centered, bool YCentered );
		EzText( Localization::Words word, const boost::shared_ptr<EzFont> &font, float Width, bool Centered, bool YCentered );
		EzText( Localization::Words word, const boost::shared_ptr<EzFont> &font, float Width, bool Centered, bool YCentered, float LineHeightMod );

		EzText( const std::wstring &str );
		EzText( const std::wstring &str, const boost::shared_ptr<EzFont> &font );
		EzText( const std::wstring &str, const boost::shared_ptr<EzFont> &font, const std::wstring &Name );
		EzText( const std::wstring &str, const boost::shared_ptr<EzFont> &font, bool Centered );
		EzText( const std::wstring &str, const boost::shared_ptr<EzFont> &font, bool Centered, bool YCentered );
		EzText( const std::wstring &str, const boost::shared_ptr<EzFont> &font, float Width, bool Centered, bool YCentered );
		EzText( const std::wstring &str, const boost::shared_ptr<EzFont> &font, float Width, bool Centered, bool YCentered, float LineHeightMod );

	
		Vector2 loc;
		float LineHeight;
		void CheckForLineEnd( Vector2 TextSize );

		/// <summary>
		/// Returns the text code to generate the given color, of the form "{c r,g,b,a}"
		/// </summary>
	
		static std::wstring ColorToCode( Color clr );

	
		std::wstring Parse_PicName;
		Vector2 Parse_PicSize;
		Vector2 Parse_PicShift;
		bool AsPaint;
		Color Parse_Color;
		ParseData Parse_Type;
		void Parse( const std::wstring &str );

		int GetLineEnd( const std::wstring &str );

		Vector2 StringSize( std::wstring str );

		Color CurColor;
		float AddLine( std::wstring str, float StartX, float StartY, int LineNumber );

		/// <summary>
		/// Gets the real world size of the text, accounting for scaling
		/// </summary>
	
		Vector2 GetWorldSize();

		/// <summary>
		/// Get the real world height of the text, accounting for scaling
		/// </summary>
		float GetWorldHeight();

		/// <summary>
		/// Get the real world width of the text, accounting for scaling
		/// </summary>
		float GetWorldWidth();

		float GetWorldWidth( const std::wstring &str );

	
		Vector2 _MyCameraZoom;
		/// <summary>
		/// The value of the camera zoom the last time this EzText was drawn
		/// </summary>
	
		const Vector2 &getMyCameraZoom() const;
		void setMyCameraZoom( const Vector2 &value );

	
		Vector2 GetWorldVector( Vector2 v );
		float GetWorldFloat( float interval );


		/// <summary>
		/// Converts a length from screen units to world units
		/// </summary>
	
		static float GetWorldFloat( float interval, Vector2 zoom );

		/// <summary>
		/// Converts a length from screen units to world units
		/// </summary>
		static Vector2 GetWorldVector( Vector2 v, Vector2 zoom );

		/// <summary>
		/// Converts a length from screen units to GUI units
		/// </summary>
		static Vector2 GetGUIVector( Vector2 v );

	
		float LineHeightMod;
		std::vector<Vector2> LineSizes;
		void Init( const std::wstring &str );
		void Init( std::wstring str, float Width, bool Centered, bool YCentered, float LineHeightMod );

	
		void Center();

	
		Vector2 JustificationShift;

	
		bool Show;
		void Draw( const boost::shared_ptr<Camera> &cam );
		virtual void Draw( const boost::shared_ptr<Camera> &cam, bool EndBatch );

		float Angle;

		static bool ZoomWithCamera_Override;
		bool ZoomWithCam;
		void _Draw( const boost::shared_ptr<Camera> &cam, bool EndBatch, bool DrawPics, const boost::shared_ptr<HackSpriteFont> &font, Vector4 color );

		void CalcBounds();

	
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef EZTEXT
