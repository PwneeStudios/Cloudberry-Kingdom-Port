#ifndef FANCYCOLOR
#define FANCYCOLOR

#include <global_header.h>

namespace CloudberryKingdom
{
	struct FancyColor
	{
	
		boost::shared_ptr<FancyVector2> clr1, clr2;
	
		float getA();
		Color getColor();
		void setColor( const Color &value );

		void Release();

		FancyColor();

		FancyColor( Color color );

	
		void Init( Color color );

		void CreateVectors();

		static Color ToColor( Vector2 v1, Vector2 v2 );
		static Vector2 Pair1( Vector4 v );
		static Vector2 Pair2( Vector4 v );

	
		Color GetDest();

		void ToAndBack( Vector4 End, int Frames );
		void ToAndBack( Vector4 Start, Vector4 End, int Frames );

	
		LerpStyle DefaultLerpStyle;

	
		void LerpTo( Vector4 End, int Frames );
		void LerpTo( Vector4 End, int Frames, LerpStyle Style );
		void LerpTo( Vector4 Start, Vector4 End, int Frames );
		void LerpTo( Vector4 Start, Vector4 End, int Frames, LerpStyle Style );

		Color Update();

	
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef FANCYCOLOR
