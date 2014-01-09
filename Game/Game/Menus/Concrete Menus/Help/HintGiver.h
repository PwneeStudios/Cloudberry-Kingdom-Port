#ifndef HINTGIVER
#define HINTGIVER

#include <small_header.h>

//#include "Game/Localization.h"
//#include "Core/Input/ButtonCheck.h"
//#include "Core/Text/EzText.h"
#include "Game/Objects/Game Objects/GameObjects/GUI_Panel.h"
//#include "Game/Player/PlayerManager.h"
//#include "Game/Menus/Concrete Menus/Help/HintBlurb.h"
//#include "Game/Objects/In Game Objects/Grab/MakeData.h"
//#include "Game/Level/Level.h"


namespace CloudberryKingdom
{
	struct Hints
	{
	
		static int YForHelpNum;
		static void SetYForHelpNum( int val );
		static void IncrYForHelpNum();

		static int QuickSpawnNum;
		static void SetQuickSpawnNum( int val );
		static void IncrQuickSpawnNum();

		static boost::shared_ptr<HintGiver> CurrentGiver;
	};

	struct HintGiver : public GUI_Panel
	{

		virtual ~HintGiver()
		{
#ifdef BOOST_BIN
			OnDestructor( "HintGiver" );
#endif
		}

	
		struct Check_QuickSpawnHelper : public Lambda
		{
		
			boost::shared_ptr<HintGiver> hg;

		
			Check_QuickSpawnHelper( const boost::shared_ptr<HintGiver> &hg );

			void Apply();
		};

	
		struct Check_YForHelpHelper : public Lambda
		{
		
			boost::shared_ptr<HintGiver> hg;

		
			Check_YForHelpHelper( const boost::shared_ptr<HintGiver> &hg );

			void Apply();
		};

	
		HintGiver();
		boost::shared_ptr<HintGiver> HintGiver_Construct();

	
		virtual void ReleaseBody();

		virtual void MyPhsxStep();

	
		void Check_QuickSpawn();

		const static std::wstring getQuickSpawnHint();

		const static std::wstring getPowerupHint();

		void Check_YForHelp();
	};
}


#endif	//#ifndef HINTGIVER
