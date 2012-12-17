#ifndef TEXTFLOAT
#define TEXTFLOAT

#include <global_header.h>

namespace CloudberryKingdom
{
	struct EzText;
}




namespace CloudberryKingdom
{
	struct TextFloat : public GameObject
	{
	
		boost::shared_ptr<EzText> MyText;

		TextFloat( Localization::Words Text, Vector2 pos );

		TextFloat( const std::wstring &Text, Vector2 pos );

	
		virtual void ReleaseBody();

	
		float Alpha;
		float AlphaSpeed;

	
		virtual void MyPhsxStep();

	
		void Update();

	
		virtual void MyDraw();

	
		virtual void Move( Vector2 shift );

	
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef TEXTFLOAT
