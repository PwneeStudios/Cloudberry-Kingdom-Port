#ifndef GUI_LIVES
#define GUI_LIVES

#include <global_header.h>

namespace CloudberryKingdom
{
	/// <summary>
	/// A GUI element that tells the player how many lives they have, while they play.
	/// </summary>
	struct GUI_Lives : public GUI_Panel
	{
	
		std::shared_ptr<StringBuilder> MyString;

	
		const int &getLives() const;
	
		std::shared_ptr<GUI_LivesLeft> MyGUI_Lives;

		/// <summary>
		/// Return a string representation of the number of Lives
		/// </summary>
		/// <returns></returns>
	
		std::shared_ptr<StringBuilder> BuildString();

	
		bool AddedOnce;
	
		virtual void OnAdd();

		virtual void Hide();

		virtual void Show();

		const Vector2 getApparentPos() const;

	
//C# TO C++ CONVERTER NOTE: The variable Bob was renamed since it is named the same as a user-defined type:
		std::shared_ptr<QuadClass> Bob_Renamed;
		std::shared_ptr<EzText> Text;
		void UpdateLivesText();

	
//C# TO C++ CONVERTER NOTE: The parameter GUI_Lives was renamed since it is named the same as a user-defined type:
		GUI_Lives( const std::shared_ptr<GUI_LivesLeft> &GUI_Lives_Renamed );

		virtual void Init();

	
		virtual void MyDraw();

		virtual void MyPhsxStep();

	
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef GUI_LIVES
