#ifndef GUI_LEVEL
#define GUI_LEVEL

#include <global_header.h>

namespace CloudberryKingdom
{
	struct EzText;
}




namespace CloudberryKingdom
{
	struct GUI_Level : public GUI_Panel
	{
	
		Localization::Words Prefix;

		/// <summary>
		/// Return a string representation of the Level
		/// </summary>
		virtual std::wstring ToString();

	
		bool DoSlideIn;

		bool AddedOnce;
	
		virtual void OnAdd();

	
		virtual void ReleaseBody();

	
//C# TO C++ CONVERTER NOTE: The variable Level was renamed since it is named the same as a user-defined type:
		int Level_Renamed;
	
//C# TO C++ CONVERTER NOTE: The parameter Level was renamed since it is named the same as a user-defined type:
		void SetLevel( int Level_Renamed );

		std::shared_ptr<EzText> LevelText;
	
		void UpdateLevelText();

	
		GUI_Level();
		GUI_Level( bool SlideIn );

		GUI_Level( int LevelNum );

	
		void DoInit( bool SlideIn );

	
		virtual void MyDraw();

		virtual void MyPhsxStep();

	
		void InitializeInstanceFields();
	};

	struct GUI_CampaignLevel : public GUI_Level
	{
	
		GUI_CampaignLevel();

		virtual void OnAdd();

		virtual std::wstring ToString();
	};
}


#endif	//#ifndef GUI_LEVEL
