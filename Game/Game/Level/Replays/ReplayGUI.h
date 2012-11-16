#ifndef REPLAYGUI
#define REPLAYGUI

#include <global_header.h>

namespace CloudberryKingdom
{
	class EzText;
}

namespace CloudberryKingdom
{
	class QuadClass;
}

namespace CloudberryKingdom
{
	class Level;
}


//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;


namespace CloudberryKingdom
{
	enum ReplayGUIType
	{
		ReplayGUIType_REPLAY,
		ReplayGUIType_COMPUTER
	};
	class ReplayGUI : public CkBaseMenu
	{
	public:
		virtual void ReturnToCaller();

	private:
		bool SkipPhsxStep;

		std::shared_ptr<EzText> Play, Toggle, End, Speed, LB, RB;

		std::shared_ptr<QuadClass> BigPaused, BigEnd;

	public:
		ReplayGUIType Type;

		ReplayGUI();

	protected:
		void SetGrayHeaderProperties( const std::shared_ptr<EzText> &text );

		virtual void SetHeaderProperties( const std::shared_ptr<EzText> &text );

	public:
		virtual void Init();

		virtual void OnAdd();

		void StartUp();

	private:
		void ResetReplay( const std::shared_ptr<Level> &level );

		void SetToggleText();

		void SetPlayText();

		void SetSpeed();

		bool StepControl;

		int SpeedVal;
		int Delay;
		int PrevDir;
	public:
		void ProcessInput();

		virtual void Reset( bool BoxesOnly );

	private:
		bool PauseSelected;

		int TimeStamp;
	protected:
		virtual void MyPhsxStep();

		virtual void MyDraw();

	private:
		bool ReplayIsOver();

	private:
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef REPLAYGUI
