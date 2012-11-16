#ifndef FANCYCOLOR
#define FANCYCOLOR

#include <global_header.h>

namespace CloudberryKingdom
{
	class FancyVector2;
}


using namespace Microsoft::Xna::Framework;

namespace CloudberryKingdom
{
	class FancyColor
	{
	private:
		std::shared_ptr<FancyVector2> clr1, clr2;
	public:
		const float &getA() const;
		const Microsoft::Xna::Framework::Color &getColor() const;
		void setColor( const Microsoft::Xna::Framework::Color &value );

		void Release();

		FancyColor();

		FancyColor( Microsoft::Xna::Framework::Color color );

	private:
		void Init( Microsoft::Xna::Framework::Color color );

		void CreateVectors();

		static Microsoft::Xna::Framework::Color ToColor( Vector2 v1, Vector2 v2 );
		static Vector2 Pair1( Vector4 v );
		static Vector2 Pair2( Vector4 v );

	public:
		Microsoft::Xna::Framework::Color GetDest();

		void ToAndBack( Vector4 End, int Frames );
		void ToAndBack( Vector4 Start, Vector4 End, int Frames );

	private:
		LerpStyle DefaultLerpStyle;
	public:
		void LerpTo( Vector4 End, int Frames );
		void LerpTo( Vector4 End, int Frames, LerpStyle Style );
		void LerpTo( Vector4 Start, Vector4 End, int Frames );
		void LerpTo( Vector4 Start, Vector4 End, int Frames, LerpStyle Style );

		Microsoft::Xna::Framework::Color Update();

	private:
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef FANCYCOLOR
