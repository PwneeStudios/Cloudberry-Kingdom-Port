#ifndef MULTIPLIERUP
#define MULTIPLIERUP

#include <global_header.h>

namespace CloudberryKingdom
{
	struct MultiplierUp : public GUI_Panel
	{
	
		virtual void OnAdd();

		boost::shared_ptr<EzText> text;
	
		MultiplierUp();
		boost::shared_ptr<MultiplierUp> MultiplierUp_Construct();
		MultiplierUp( Vector2 shift, float scale, bool perma );
		boost::shared_ptr<MultiplierUp> MultiplierUp_Construct( Vector2 shift, float scale, bool perma );

	
		bool Perma;
		void Init( Vector2 shift, float scale, bool perma );

		int Count;
	
		virtual void MyPhsxStep();

	
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef MULTIPLIERUP
