#ifndef SUPERCHEER
#define SUPERCHEER

#include <global_header.h>

namespace CloudberryKingdom
{
	struct SuperCheer : public GameObject
	{
	
		struct CheerHelper : public Lambda
		{
		
			std::shared_ptr<GameData> mygame;
			Vector2 pos;

		
			CheerHelper( const std::shared_ptr<GameData> &mygame, Vector2 pos );

			void Apply();
		};

	
		int Rows;
	
		SuperCheer( int Rows );

		virtual void OnAdd();

	
		void AddWave( int Delay );
	};
}


#endif	//#ifndef SUPERCHEER
