#ifndef CAMPAIGNSEQUENCE
#define CAMPAIGNSEQUENCE

#include "LevelSequence.h"
#include "../Core/Lambdas/Lambda_1.h"
#include "../Game/Objects/Game Objects/GameObjects/CoinScoreMultiplierObject.h"
#include "../Game/Objects/Game Objects/GameObjects/PerfectScoreObject.h"
#include "../Game/Objects/Game Objects/GameObjects/GUI_NextLife.h"
#include "../Game/Objects/Game Objects/GameObjects/GUI_Timer.h"
#include <string>
#include <unordered_map>
#include <vector>
#include <cmath>
#include <tchar.h>

namespace CloudberryKingdom
{
	class Level;
}

namespace CloudberryKingdom
{
	class ObjectBase;
}

namespace CloudberryKingdom
{
	class Lambda_1;
}

namespace CloudberryKingdom
{
	class LevelSeedData;
}


//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::IO;

using namespace Microsoft::Xna::Framework;

namespace CloudberryKingdom
{
	class CampaignSequence : public LevelSequence
	{
	private:
		class PostMakeCampaignProxy : public Lambda_1<Level*>
		{
		public:
			void Apply( const std::shared_ptr<Level> &level );
		};

	private:
		class OnCoinGrabProxy : public Lambda_1<ObjectBase*>
		{
		public:
			void Apply( const std::shared_ptr<ObjectBase> &obj );
		};

	private:
		class OnCompleteLevelProxy : public Lambda_1<Level*>
		{
		public:
			void Apply( const std::shared_ptr<Level> &level );
		};

	private:
		class WatchMovieLambda : public Lambda_1<Level*>
		{
		private:
			std::wstring movie;
		public:
			WatchMovieLambda( const std::wstring &movie );

			void Apply( const std::shared_ptr<Level> &level );
		};

	private:
		class EndActionProxy : public Lambda_1<Level*>
		{
		public:
			void Apply( const std::shared_ptr<Level> &level );
		};

	private:
		static const std::shared_ptr<CampaignSequence> instance;
	public:
		const static std::shared_ptr<CampaignSequence> &getInstance() const;

	private:
		std::unordered_map<int, int> ChapterStart;
		std::unordered_map<int, Tuple<std::wstring, std::wstring>*> SpecialLevel;

	public:
		virtual void Start( int Chapter );

	protected:
		virtual void MakeSeedList();

	private:
		static std::shared_ptr<LevelSeedData> MakeActionSeed( const std::shared_ptr<Lambda_1<Level*> > &SeedAction );

	public:
		virtual std::shared_ptr<LevelSeedData> GetSeed( int Index );

	private:
		static void PostMakeCampaign( const std::shared_ptr<Level> &level );

		static void OnCoinGrab( const std::shared_ptr<ObjectBase> &obj );

		static void OnCompleteLevel( const std::shared_ptr<Level> &level );

		static std::shared_ptr<Lambda_1<Level*> > MakeWatchMovieAction( const std::wstring &movie );

		static void EndAction( const std::shared_ptr<Level> &level );

	protected:
		CampaignSequence();

	private:
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef CAMPAIGNSEQUENCE
