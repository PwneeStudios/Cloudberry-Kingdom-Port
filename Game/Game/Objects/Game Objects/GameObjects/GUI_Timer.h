#ifndef GUI_TIMER
#define GUI_TIMER

#include <global_header.h>

namespace CloudberryKingdom
{
	class ObjectBase;
}

namespace CloudberryKingdom
{
	class Level;
}


//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Text;

using namespace Microsoft::Xna::Framework;

namespace CloudberryKingdom
{
	class GUI_Timer : public GUI_Timer_Base
	{
	private:
		class OnCoinGrabProxy : public Lambda_1<ObjectBase*>
		{
		private:
			std::shared_ptr<GUI_Timer> timer;

		public:
			OnCoinGrabProxy( const std::shared_ptr<GUI_Timer> &timer );

			void Apply( const std::shared_ptr<ObjectBase> &obj );
		};

	private:
		class OnCompleteLevelProxy : public Lambda_1<Level*>
		{
		private:
			std::shared_ptr<GUI_Timer> timer;

		public:
			OnCompleteLevelProxy( const std::shared_ptr<GUI_Timer> &timer );

			void Apply( const std::shared_ptr<Level> &level );
		};


	public:
		virtual void OnAdd();

	protected:
		virtual void ReleaseBody();

	public:
		int CoinTimeValue, MinLevelStartTimeValue;
		int MaxTime;
		void OnCoinGrab( const std::shared_ptr<ObjectBase> &obj );

		void OnCompleteLevel( const std::shared_ptr<Level> &level );

	private:
		void InitializeInstanceFields();

public:
		GUI_Timer()
		{
			InitializeInstanceFields();
		}
	};
}


#endif	//#ifndef GUI_TIMER
