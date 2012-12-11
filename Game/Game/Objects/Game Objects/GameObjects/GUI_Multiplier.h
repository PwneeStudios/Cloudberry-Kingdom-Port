#ifndef GUI_MULTIPLIER
#define GUI_MULTIPLIER

#include <global_header.h>

namespace CloudberryKingdom
{
	struct EzText;
}




namespace CloudberryKingdom
{
	struct GUI_Multiplier : public GUI_Panel
	{
		/// <summary>
		/// Return a string representation of the Multiplier
		/// </summary>
	
		virtual std::wstring ToString();

	
		bool AddedOnce;
	
		virtual void OnAdd();

	
		virtual void ReleaseBody();

		virtual int GetMultiplier();

	
		int Multiplier;
		void SetMultiplier( int Multiplier );

		std::shared_ptr<EzText> MultiplierText;
		void UpdateMultiplierText();

		bool DoSlideIn;
	
		GUI_Multiplier( int Style );
		GUI_Multiplier( int Style, bool SlideIn );

	
		void DoInit( int Style, bool SlideIn );

	
		virtual void MyDraw();

		virtual void MyPhsxStep();

	
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef GUI_MULTIPLIER
