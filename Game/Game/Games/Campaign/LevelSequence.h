#ifndef LEVELSEQUENCE
#define LEVELSEQUENCE

#include <global_header.h>

namespace CloudberryKingdom
{
	class LevelSequence
	{
	private:
		class OnLevelBeginLambda : public LambdaFunc_1<Level*, bool>
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
