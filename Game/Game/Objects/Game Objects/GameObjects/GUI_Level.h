#ifndef GUI_LEVEL
#define GUI_LEVEL

#include <global_header.h>

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
	
		int Level_Renamed;
	
		void SetLevel( int Level_Renamed );

		boost::shared_ptr<EzText> LevelText;
	
		void UpdateLevelText();

	
		GUI_Level();
		boost::shared_ptr<GUI_Level> GUI_Level_Construct();
		GUI_Level( bool SlideIn );
		boost::shared_ptr<GUI_Level> GUI_Level_Construct( bool SlideIn );

		GUI_Level( int LevelNum );
		boost::shared_ptr<GUI_Level> GUI_Level_Construct( int LevelNum );

	
		void DoInit( bool SlideIn );

	
		virtual void MyDraw();

		virtual void MyPhsxStep();

	
		void InitializeInstanceFields();
	};

	struct GUI_CampaignLevel : public GUI_Level
	{
	
		GUI_CampaignLevel();
		boost::shared_ptr<GUI_CampaignLevel> GUI_CampaignLevel_Construct();

		virtual void OnAdd();

		virtual std::wstring ToString();
	};
}


#endif	//#ifndef GUI_LEVEL
