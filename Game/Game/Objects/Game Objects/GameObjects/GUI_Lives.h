#ifndef GUI_LIVES
#define GUI_LIVES

#include <global_header.h>

namespace CloudberryKingdom
{
	class GUI_LivesLeft;
}

namespace CloudberryKingdom
{
	class QuadClass;
}

namespace CloudberryKingdom
{
	class EzText;
}


//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Text;

using namespace Microsoft::Xna::Framework;

namespace CloudberryKingdom
{
	/// <summary>
	/// A GUI element that tells the player how many lives they have, while they play.
	/// </summary>
	class GUI_Lives : public GUI_Panel
	{
	private:
		std::shared_ptr<StringBuilder> MyString;

	public:
		const int &getLives() const;
	private:
		std::shared_ptr<GUI_LivesLeft> MyGUI_Lives;

		/// <summary>
		/// Return a string representation of the number of Lives
		/// </summary>
		/// <returns></returns>
	public:
		std::shared_ptr<StringBuilder> BuildString();

	private:
		bool AddedOnce;
	public:
		virtual void OnAdd();

		virtual void Hide();

		virtual void Show();

		const Vector2 &getApparentPos() const;

	private:
//C# TO C++ CONVERTER NOTE: The variable Bob was renamed since it is named the same as a user-defined type:
		std::shared_ptr<QuadClass> Bob_Renamed;
		std::shared_ptr<EzText> Text;
		void UpdateLivesText();

	public:
//C# TO C++ CONVERTER NOTE: The parameter GUI_Lives was renamed since it is named the same as a user-defined type:
		GUI_Lives( const std::shared_ptr<GUI_LivesLeft> &GUI_Lives_Renamed );

		virtual void Init();

	protected:
		virtual void MyDraw();

		virtual void MyPhsxStep();

	private:
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef GUI_LIVES
