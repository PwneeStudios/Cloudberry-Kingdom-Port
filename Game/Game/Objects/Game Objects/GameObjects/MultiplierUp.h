#ifndef MULTIPLIERUP
#define MULTIPLIERUP

#include <global_header.h>

namespace CloudberryKingdom
{
	struct EzText;
}




namespace CloudberryKingdom
{
	struct MultiplierUp : public GUI_Panel
	{
	
		virtual void OnAdd();

	
		std::shared_ptr<EzText> text;
	
		MultiplierUp();
		MultiplierUp( Vector2 shift, float scale, bool perma );

	
		bool Perma;
		void Init( Vector2 shift, float scale, bool perma );

		int Count;
	
		virtual void MyPhsxStep();

	
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef MULTIPLIERUP
