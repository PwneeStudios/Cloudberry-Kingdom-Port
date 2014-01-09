#ifndef REPLAYGUI
#define REPLAYGUI

#include <small_header.h>

//#include "Core/Graphics/Draw/DrawPile.h"
//#include "Core/Graphics/Draw/Quads/QuadClass.h"
#include "Game/Localization.h"
//#include "Game/CloudberryKingdom/CloudberryKingdom.CloudberryKingdomGame.h"
//#include "Core/Input/ButtonCheck.h"
//#include "Core/Text/EzText.h"
//#include "Core/Tools/ColorHelper.h"
//#include "Core/Tools/CoreMath.h"
#include "Game/Menus/CkBaseMenu.h"
//#include "Game/Menus/Concrete Menus/InGameStartMenus/InGameStartMenu.h"
//#include "Game/Objects/In Game Objects/Grab/MakeData.h"
//#include "Game/Level/Level.h"
//#include "Game/Tools/Tools.h"


namespace CloudberryKingdom
{
	
	struct ReplayGUI : public CkBaseMenu
	{
	
		virtual ~ReplayGUI()
		{
#ifdef BOOST_BIN
			OnDestructor( "ReplayGUI" );
#endif
		}


		virtual void ReturnToCaller();
	
		bool SkipPhsxStep;

		boost::shared_ptr<EzText> Play, Toggle, End, Speed, LB, RB;

		boost::shared_ptr<QuadClass> BigPaused, BigEnd;
	
		ReplayGUIType Type;

		ReplayGUI();
		boost::shared_ptr<ReplayGUI> ReplayGUI_Construct();
	
		void SetGrayHeaderProperties( const boost::shared_ptr<EzText> &text );

		virtual void SetHeaderProperties( const boost::shared_ptr<EzText> &text );
	
		virtual void Init();

		virtual void OnAdd();

		void StartUp();

		void ResetReplay( const boost::shared_ptr<Level> &level );

		void SetToggleText();

    Localization::Words PlayWord;
    void SetPlayWord( Localization::Words word );

		void SetPlayText();

		void SetSpeed();

		bool StepControl;

		int SpeedVal;
		int Delay;
		int PrevDir;
	
		void ProcessInput();

		virtual void Reset( bool BoxesOnly );
	
		bool PauseSelected;

		int TimeStamp;
	
		virtual void MyPhsxStep();

		virtual void MyDraw();

		bool ReplayIsOver();
	
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef REPLAYGUI
