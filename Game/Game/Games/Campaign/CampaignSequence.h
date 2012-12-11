#ifndef CAMPAIGNSEQUENCE
#define CAMPAIGNSEQUENCE

#include <global_header.h>

#include "Hacks/NET/Tuple.h"

namespace CloudberryKingdom
{

	struct CampaignSequence : public LevelSequence
	{

	
		struct PostMakeCampaignProxy : public Lambda_1<std::shared_ptr<Level> >
		{
		
			void Apply( const std::shared_ptr<Level> &level );
		};

	
		struct OnCoinGrabProxy : public Lambda_1<std::shared_ptr<ObjectBase> >
		{
		
			void Apply( const std::shared_ptr<ObjectBase> &obj );
		};

	
		struct OnCompleteLevelProxy : public Lambda_1<std::shared_ptr<Level> >
		{
		
			void Apply( const std::shared_ptr<Level> &level );
		};

	
		struct WatchMovieLambda : public Lambda_1<std::shared_ptr<Level> >
		{
		
			std::wstring movie;
		
			WatchMovieLambda( const std::wstring &movie );

			void Apply( const std::shared_ptr<Level> &level );
		};

	
		struct EndActionProxy : public Lambda_1<std::shared_ptr<Level> >
		{
		
			void Apply( const std::shared_ptr<Level> &level );
		};

	
		static std::shared_ptr<CampaignSequence> instance;
		const static std::shared_ptr<CampaignSequence> &getInstance();

	
		std::map<int, int> ChapterStart;
		std::map<int, std::shared_ptr< Tuple<std::wstring, std::wstring> > > SpecialLevel;

	
		virtual void Start( int Chapter );

	
		virtual void MakeSeedList();

	
		static std::shared_ptr<LevelSeedData> MakeActionSeed( const std::shared_ptr<Lambda_1<std::shared_ptr<Level> > > SeedAction );

	
		virtual std::shared_ptr<LevelSeedData> GetSeed( int Index );

	
		static void PostMakeCampaign( const std::shared_ptr<Level> &level );

		static void OnCoinGrab( const std::shared_ptr<ObjectBase> &obj );

		static void OnCompleteLevel( const std::shared_ptr<Level> &level );

		static std::shared_ptr<Lambda_1<std::shared_ptr<Level> > > MakeWatchMovieAction( const std::wstring &movie );

		static void EndAction( const std::shared_ptr<Level> &level );

	
		CampaignSequence();

	
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef CAMPAIGNSEQUENCE
