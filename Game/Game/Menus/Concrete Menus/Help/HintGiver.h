#ifndef HINTGIVER
#define HINTGIVER

#include <global_header.h>

namespace CloudberryKingdom
{
	class HintGiver;
}




namespace CloudberryKingdom
{
	class Hints
	{
	public:
		static int YForHelpNum;
		static void SetYForHelpNum( int val );
		static void IncrYForHelpNum();

		static int QuickSpawnNum;
		static void SetQuickSpawnNum( int val );
		static void IncrQuickSpawnNum();

		static std::shared_ptr<HintGiver> CurrentGiver;
	};

	class HintGiver : public GUI_Panel
	{
	private:
		class Check_QuickSpawnHelper : public Lambda
		{
		private:
			std::shared_ptr<HintGiver> hg;

		public:
			Check_QuickSpawnHelper( const std::shared_ptr<HintGiver> &hg );

			void Apply();
		};

	private:
		class Check_YForHelpHelper : public Lambda
		{
		private:
			std::shared_ptr<HintGiver> hg;

		public:
			Check_YForHelpHelper( const std::shared_ptr<HintGiver> &hg );

			void Apply();
		};

	public:
		HintGiver();

	protected:
		virtual void ReleaseBody();

		virtual void MyPhsxStep();

	public:
		void Check_QuickSpawn();

		const static std::wstring getQuickSpawnHint();

		const static std::wstring getPowerupHint();

		void Check_YForHelp();
	};
}


#endif	//#ifndef HINTGIVER
