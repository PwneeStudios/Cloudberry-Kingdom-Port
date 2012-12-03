#ifndef LEVELGENDATA
#define LEVELGENDATA

#include <global_header.h>

namespace CloudberryKingdom
{

	class RichLevelGenData
	{
	public:
		std::shared_ptr<LevelGenData> gen1, gen2;
		Vector2 p1, p2;

		void Set_Difficulty( int type, int val );
		int Get_Difficulty( int type );
		int Get_Difficulty( int type, Vector2 pos );

		void Set_Behavior( int type, int val );
		int Get_Behavior( int type );
		int Get_Behavior( int type, Vector2 pos );
	};

	class LevelGenData
	{
	public:
		std::vector<int> Difficulty;
		std::vector<int> BehaviorParams;

		//int &operator []( DifficultyParam type );
		//int &operator []( BehaviorParam type );
		int Get_Difficulty(int type);
		int Get_Behavior(int type);
		void Set_Difficulty(int type, int val);
		void Set_Behavior(int type, int val);

		LevelGenData();
	};
}


#endif	//#ifndef LEVELGENDATA
