#ifndef TEXTLIST
#define TEXTLIST

#include <global_header.h>

namespace CloudberryKingdom
{
	class EzText;
}

namespace CloudberryKingdom
{
	class Camera;
}

namespace CloudberryKingdom
{
	class TextList : public ObjectBase
	{
	public:
		virtual void Release();

		std::vector<EzText*> Text;
		int Index;
		float ContinuousIndex;

		std::shared_ptr<Camera> MyCam;

		bool FadeOut;
		float Alpha;

		virtual void MakeNew();

		TextList();

		void SetIndex( int index );

		//public void AddLine(String s)
		//{
		//    Text.Add(new EzText(s, Resources.Font_Grobold42, true));
		//}

		virtual void PhsxStep();

		virtual void Draw();

		void ShiftUp();
		void ShiftDown();

		virtual void Move( Vector2 shift );
	};
}


#endif	//#ifndef TEXTLIST
