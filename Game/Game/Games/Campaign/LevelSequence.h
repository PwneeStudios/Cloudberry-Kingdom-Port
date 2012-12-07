#ifndef LEVELSEQUENCE
#define LEVELSEQUENCE

#include <global_header.h>

namespace CloudberryKingdom
{

	class PassGetSeedAsLambda_LevelSequence : public LambdaFunc_1<int, std::shared_ptr<LevelSeedData> >
	{

	private:
		std::shared_ptr<LevelSequence> ls;

	public:
		PassGetSeedAsLambda_LevelSequence( const std::shared_ptr<LevelSequence> &ls);

		std::shared_ptr<LevelSeedData> Apply( const int &index );

	};

	class LevelSequence : public std::enable_shared_from_this<LevelSequence>
	{
	private:
		class OnLevelBeginLambda : public LambdaFunc_1<std::shared_ptr<Level> , bool>
		{
		private:
			std::shared_ptr<LevelSequence> ls;
		public:
			OnLevelBeginLambda( const std::shared_ptr<LevelSequence> &ls );

			bool Apply( const std::shared_ptr<Level> &level );
		};

	protected:
		std::shared_ptr<StringWorldGameData> MyStringWorld;

	public:
		std::vector<std::wstring> Seeds;

		LevelSequence();

	protected:
		virtual void MakeSeedList();

	private:
		int StartIndex;
	public:
		virtual void Start( int StartLevel );

		/// <summary>
		/// Returns true if the standard StringWorld processing should be skipped.
		/// Special levels (such as watching a movie) do not need the normal processing (and would crash the game if they happened).
		/// </summary>
	private:
		bool OnLevelBegin( const std::shared_ptr<Level> &level );

	protected:
		virtual void SetGameParent( const std::shared_ptr<GameData> &game );

		virtual void AdditionalPreStart();

	public:
		virtual std::shared_ptr<LevelSeedData> GetSeed( int Index );

	private:
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef LEVELSEQUENCE
