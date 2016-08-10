#ifndef GUI_LIVES
#define GUI_LIVES

#include <small_header.h>

//#include "Core/Graphics/Draw/DrawPile.h"
//#include "Core/Graphics/Draw/Quads/QuadClass.h"
//#include "Core/Text/EzText.h"
#include "Game/Objects/Game Objects/GameObjects/GUI_Panel.h"
//#include "Game/Objects/Bob/Bob.h"
//#include "Game/Objects/Game Objects/GameObjects/GUI_LivesLeft.h"
//#include "Game/Tools/Resources.h"
//#include "Game/Tools/Tools.h"


namespace CloudberryKingdom
{

	/// <summary>
	/// A GUI element that tells the player how many lives they have, while they play.
	/// </summary>
	struct GUI_Lives : public GUI_Panel
	{

		virtual ~GUI_Lives()
		{
#ifdef BOOST_BIN
			OnDestructor( "GUI_Lives" );
#endif
		}


		using GUI_Panel::SlideOut;
		using GUI_Panel::SlideIn;
		using GUI_Panel::Call;
	
		boost::shared_ptr<StringBuilder> MyString;

	
		const int &getLives() const;
	
		boost::shared_ptr<GUI_LivesLeft> MyGUI_Lives;

		/// <summary>
		/// Return a string representation of the number of Lives
		/// </summary>
		/// <returns></returns>
	
		boost::shared_ptr<StringBuilder> BuildString();

	
		bool AddedOnce;
	
		virtual void OnAdd();

		virtual void Hide();

		virtual void Show();

		const Vector2 getApparentPos() const;


		boost::shared_ptr<QuadClass> Bob_Renamed;
		boost::shared_ptr<EzText> Text;
		void UpdateLivesText();
	
		GUI_Lives( const boost::shared_ptr<GUI_LivesLeft> &GUI_Lives_Renamed );
		boost::shared_ptr<GUI_Lives> GUI_Lives_Construct( const boost::shared_ptr<GUI_LivesLeft> &GUI_Lives_Renamed );

		virtual void Init();

	
		virtual void MyDraw();

		virtual void MyPhsxStep();

	
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef GUI_LIVES
