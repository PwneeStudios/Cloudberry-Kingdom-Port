#ifndef LEVELSEQUENCE
#define LEVELSEQUENCE

#include <global_header.h>

namespace CloudberryKingdom
{

	struct PassGetSeedAsLambda_LevelSequence : public LambdaFunc_1<int, boost::shared_ptr<LevelSeedData> >
	{

	
		boost::shared_ptr<LevelSequence> ls;

	
		PassGetSeedAsLambda_LevelSequence( const boost::shared_ptr<LevelSequence> &ls);

		boost::shared_ptr<LevelSeedData> Apply( const int &index );

	};

	struct LevelSequence : public boost::enable_shared_from_this<LevelSequence>
	{
	
		struct OnLevelBeginLambda : public LambdaFunc_1<boost::shared_ptr<Level> , bool>
		{
		
			boost::shared_ptr<LevelSequence> ls;
		
			OnLevelBeginLambda( const boost::shared_ptr<LevelSequence> &ls );

			bool Apply( const boost::shared_ptr<Level> &level );
		};

	
		boost::shared_ptr<StringWorldGameData> MyStringWorld;

	
		std::vector<std::wstring> Seeds;

		LevelSequence();

	
		virtual void MakeSeedList();

	
		int StartIndex;
	
		virtual void Start( int StartLevel );

		/// <summary>
		/// Returns true if the standard StringWorld processing should be skipped.
		/// Special levels (such as watching a movie) do not need the normal processing (and would crash the game if they happened).
		/// </summary>
	
		bool OnLevelBegin( const boost::shared_ptr<Level> &level );

	
		virtual void SetGameParent( const boost::shared_ptr<GameData> &game );

		virtual void AdditionalPreStart();

	
		virtual boost::shared_ptr<LevelSeedData> GetSeed( int Index );

	
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef LEVELSEQUENCE
