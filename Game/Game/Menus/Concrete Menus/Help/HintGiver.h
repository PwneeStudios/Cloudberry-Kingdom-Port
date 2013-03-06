#ifndef HINTGIVER
#define HINTGIVER

#include <global_header.h>

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
