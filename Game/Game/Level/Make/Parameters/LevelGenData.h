#ifndef LEVELGENDATA
#define LEVELGENDATA

#include <global_header.h>

namespace CloudberryKingdom
{
	class LevelGenData;
}

namespace CloudberryKingdom
{

	class RichLevelGenData
	{
	public:
		std::shared_ptr<LevelGenData> gen1, gen2;
		Vector2 p1, p2;

		void Set( DifficultyParam type, int val );
		int Get( DifficultyParam type );
		int Get( DifficultyParam type, Vector2 pos );


		void Set( BehaviorParam type, int val );
		int Get( BehaviorParam type );
		int Get( BehaviorParam type, Vector2 pos );
	};

	class LevelGenData
	{
	public:
		std::vector<int> Difficulty;
		std::vector<int> BehaviorParams;

		//public int Get(DifficultyParam type) { return Difficulty[(int)type]; }
		//public int Get(BehaviorParam type) { return Difficulty[(int)type]; }

		int &operator []( DifficultyParam type );

		int &operator []( BehaviorParam type );

		LevelGenData();
	};
}


#endif	//#ifndef LEVELGENDATA
