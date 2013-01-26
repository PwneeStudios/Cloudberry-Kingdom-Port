#ifndef PRESSNOTE
#define PRESSNOTE

#include <global_header.h>

namespace CloudberryKingdom
{

	struct PressNote : public GUI_Text
	{

		virtual ~PressNote() { }
	
		static const int ButtonScale = 87;
		static const float TextScale;

	
		boost::shared_ptr<Door> Parent;

		PressNote( const boost::shared_ptr<Door> &Parent );
		boost::shared_ptr<PressNote> PressNote_Construct( const boost::shared_ptr<Door> &Parent );
	
		int Life;
	
		int LifeSpeed; //9;
		void FadeIn();

		int DelayToFadeOut; //80;
	
		int Count;
	
		void FadeOut();

		virtual void MyPhsxStep();
	
		virtual void Draw();
	
		void InitializeInstanceFields();

	};

}


#endif	//#ifndef PRESSNOTE
