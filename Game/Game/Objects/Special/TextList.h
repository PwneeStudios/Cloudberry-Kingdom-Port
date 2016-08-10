#ifndef TEXTLIST
#define TEXTLIST

#include <small_header.h>

//#include "Core/Text/EzText.h"
#include "Game/Objects/ObjectBase.h"
//#include "Game/Tools/Camera.h"
//#include "Game/Tools/Tools.h"


namespace CloudberryKingdom
{
	
	struct TextList : public ObjectBase
	{
	
		virtual ~TextList()
		{
#ifdef BOOST_BIN
			OnDestructor( "TextList" );
#endif
		}


		virtual void Release();

		std::vector<EzText*> Text;
		int Index;
		float ContinuousIndex;

		boost::shared_ptr<Camera> MyCam;

		bool FadeOut;
		float Alpha;

		virtual void MakeNew();

		TextList();

		void SetIndex( int index );

		//public void AddLine(String s)
		//{
		//    Text.Add(new EzText(s, Resources::Font_Grobold42, true));
		//}

		virtual void PhsxStep();

		virtual void Draw();

		void ShiftUp();
		void ShiftDown();

		virtual void Move( Vector2 shift );
	};

}


#endif	//#ifndef TEXTLIST
