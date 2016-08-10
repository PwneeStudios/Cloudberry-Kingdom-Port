#ifndef GUI_MULTIPLIER
#define GUI_MULTIPLIER

#include <small_header.h>

//#include "Core/Graphics/Draw/DrawPile.h"
//#include "Core/Text/EzFont.h"
//#include "Core/Text/EzText.h"
#include "Game/Objects/Game Objects/GameObjects/GUI_Panel.h"
//#include "Game/Tools/Resources.h"


namespace CloudberryKingdom
{
	struct GUI_Multiplier : public GUI_Panel
	{

		virtual ~GUI_Multiplier()
		{
#ifdef BOOST_BIN
			OnDestructor( "GUI_Multiplier" );
#endif
		}


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

		boost::shared_ptr<EzText> MultiplierText;
		void UpdateMultiplierText();

		bool DoSlideIn;
	
		GUI_Multiplier( int Style );
		boost::shared_ptr<GUI_Multiplier> GUI_Multiplier_Construct( int Style );
		GUI_Multiplier( int Style, bool SlideIn );
		boost::shared_ptr<GUI_Multiplier> GUI_Multiplier_Construct( int Style, bool SlideIn );

	
		void DoInit( int Style, bool SlideIn );

	
		virtual void MyDraw();

		virtual void MyPhsxStep();

	
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef GUI_MULTIPLIER
