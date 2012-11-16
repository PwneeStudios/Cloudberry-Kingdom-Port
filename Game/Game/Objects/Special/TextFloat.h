#ifndef TEXTFLOAT
#define TEXTFLOAT

#include <global_header.h>

namespace CloudberryKingdom
{
	class EzText;
}


using namespace Microsoft::Xna::Framework;

namespace CloudberryKingdom
{
	class TextFloat : public GameObject
	{
	public:
		std::shared_ptr<EzText> MyText;

		TextFloat( Localization::Words Text, Vector2 pos );

		TextFloat( const std::wstring &Text, Vector2 pos );

	protected:
		virtual void ReleaseBody();

	private:
		float Alpha;
		float AlphaSpeed;

	protected:
		virtual void MyPhsxStep();

	private:
		void Update();

	protected:
		virtual void MyDraw();

	public:
		virtual void Move( Vector2 shift );

	private:
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef TEXTFLOAT
