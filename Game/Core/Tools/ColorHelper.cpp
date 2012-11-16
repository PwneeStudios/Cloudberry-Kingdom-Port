#include <global_header.h>









namespace CloudberryKingdom
{

	Microsoft::Xna::Framework::Color ColorHelper::GrayColor( float val )
	{
		return Color( Gray( val ) );
	}

	Microsoft::Xna::Framework::Vector4 ColorHelper::Gray( float val )
	{
		return Vector4( val, val, val, 1 );
	}

Matrix ColorHelper::transform_red = Matrix( 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1 );
Matrix ColorHelper::transform_green = Matrix( 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1 );
Matrix ColorHelper::transform_blue = Matrix( 0, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1 );

	Microsoft::Xna::Framework::Matrix ColorHelper::LinearColorTransform( float angle )
	{
		float s = ( ( angle % 360 + 360 ) % 360 ) / 120;

		if ( s < 1 )
		{
			return ( 1 - s ) * transform_green + s * transform_blue;
		}
		else if ( s < 2 )
		{
			s = s - 1;
			return ( 1 - s ) * transform_blue + s * transform_red;
		}
		else
		{
			s = s - 2;
			return ( 1 - s ) * transform_red + s * transform_green;
		}
	}

	Microsoft::Xna::Framework::Matrix ColorHelper::PureColor( Color color )
	{
		return Matrix( 0, 0, 0, color.R, 0, 0, 0, color.G, 0, 0, 0, color.B, 0, 0, 0, 1 );
	}

	Microsoft::Xna::Framework::Matrix ColorHelper::HsvTransform( float V, float S, float H )
	{
		float a = CoreMath::Radians( H );
		float U = static_cast<float>( cos( a ) ), W = static_cast<float>( sin( a ) );
		Matrix hsv = Matrix( .299f * V + .701f * V * S * U + .168f * V * S * W,.587f * V - .587f * V * S * U + .330f * V * S * W,.114f * V - .114f * V * S * U - .497f * V * S * W, 0,.299f * V - .299f * V * S * U - .328f * V * S * W,.587f * V + .413f * V * S * U + .035f * V * S * W,.114f * V - .114f * V * S * U + .292f * V * S * W, 0,.299f * V - .300f * V * S * U + 1.25f * V * S * W,.587f * V - .588f * V * S * U - 1.05f * V * S * W,.114f * V + .886f * V * S * U - .203f * V * S * W, 0, 0, 0, 0, 1 );
		return hsv;
	}

	float ColorHelper::MatrixSignature( Matrix m )
	{
		return m.M11 + m.M22 + m.M33;
	}

	Microsoft::Xna::Framework::Color ColorHelper::PremultiplyAlpha( Color color )
	{
		return Color( color.R, color.G, color.B ) * ( color.A / 255 );
	}

	Microsoft::Xna::Framework::Color ColorHelper::PremultiplyAlpha( Color color, float BlendAddRatio )
	{
		Color NewColor = PremultiplyAlpha( color );
		NewColor.A = static_cast<unsigned char>( NewColor.A * ( 1 - BlendAddRatio ) );

		return NewColor;
	}
}
