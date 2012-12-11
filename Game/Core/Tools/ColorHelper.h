#ifndef COLORHELPER
#define COLORHELPER

#include <global_header.h>

namespace CloudberryKingdom
{
	struct ColorHelper
	{
	
		static Color GrayColor( float val );
		static Vector4 Gray( float val );

	
		static Matrix transform_red;

		static Matrix transform_green;

		static Matrix transform_blue;

	
		static Matrix LinearColorTransform( float angle );

		static Matrix PureColor( Color color );

		static Matrix HsvTransform( float V, float S, float H );

		/// <summary>
		/// Gets a non-unique number associated with a matrix.
		/// Used to quickly determine if two matrices are probably the same.
		/// </summary>
		static float MatrixSignature( Matrix m );

		/// <summary>
		/// Premultiply a color's alpha against its RGB components.
		/// </summary>
		/// <param name="color">The normal, non-premultiplied color.</param>
		static Color PremultiplyAlpha( Color color );

		/// <summary>
		/// Premultiply a color's alpha against its RGB components.
		/// </summary>
		/// <param name="color">The normal, non-premultiplied color.</param>
		/// <param name="BlendAddRatio">When 0 blending is normal, when 1 blending is additive.</param>
		static Color PremultiplyAlpha( Color color, float BlendAddRatio );
	};
}


#endif	//#ifndef COLORHELPER
