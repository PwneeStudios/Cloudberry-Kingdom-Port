#ifndef GUI_LEVEL
#define GUI_LEVEL

#include <global_header.h>

namespace CloudberryKingdom
{
	class EzText;
}


using namespace Microsoft::Xna::Framework;

namespace CloudberryKingdom
{
	class GUI_CampaignLevel : public GUI_Level
	{
	public:
		GUI_CampaignLevel();

		virtual void OnAdd();

		virtual std::wstring ToString();
	};

	class GUI_Level : public GUI_Panel
	{
	public:
		Localization::Words Prefix;

		/// <summary>
		/// Return a string representation of the Level
		/// </summary>
		virtual std::wstring ToString();

	private:
		bool DoSlideIn;

		bool AddedOnce;
	public:
		virtual void OnAdd();

	protected:
		virtual void ReleaseBody();

	private:
//C# TO C++ CONVERTER NOTE: The variable Level was renamed since it is named the same as a user-defined type:
		int Level_Renamed;
	public:
//C# TO C++ CONVERTER NOTE: The parameter Level was renamed since it is named the same as a user-defined type:
		void SetLevel( int Level_Renamed );

		std::shared_ptr<EzText> LevelText;
	protected:
		void UpdateLevelText();

	public:
		GUI_Level();
		GUI_Level( bool SlideIn );

		GUI_Level( int LevelNum );

	private:
		void DoInit( bool SlideIn );

	protected:
		virtual void MyDraw();

		virtual void MyPhsxStep();

	private:
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef GUI_LEVEL
