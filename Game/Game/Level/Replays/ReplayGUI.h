#ifndef REPLAYGUI
#define REPLAYGUI

#include <global_header.h>

namespace CloudberryKingdom
{
	struct ReplayGUI : public CkBaseMenu
	{
	
		virtual void ReturnToCaller();

	
		bool SkipPhsxStep;

		std::shared_ptr<EzText> Play, Toggle, End, Speed, LB, RB;

		std::shared_ptr<QuadClass> BigPaused, BigEnd;

	
		ReplayGUIType Type;

		ReplayGUI();

	
		void SetGrayHeaderProperties( const std::shared_ptr<EzText> &text );

		virtual void SetHeaderProperties( const std::shared_ptr<EzText> &text );

	
		virtual void Init();

		virtual void OnAdd();

		void StartUp();

	
		void ResetReplay( const std::shared_ptr<Level> &level );

		void SetToggleText();

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
