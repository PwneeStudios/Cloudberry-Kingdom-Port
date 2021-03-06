#ifndef TEXTFLOAT
#define TEXTFLOAT

#include <small_header.h>

#include "Game/Localization.h"
//#include "Core/Text/EzText.h"
#include "Game/Objects/Game Objects/GameObject.h"
//#include "Game/Objects/In Game Objects/Grab/MakeData.h"
//#include "Game/Level/Level.h"
//#include "Game/Tools/Resources.h"
//#include "Game/Tools/Tools.h"


namespace CloudberryKingdom
{
	struct EzText;
}




namespace CloudberryKingdom
{
	
	struct TextFloat : public GameObject
	{

		virtual ~TextFloat()
		{
#ifdef BOOST_BIN
			OnDestructor( "TextFloat" );
#endif
		}

	
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
