#ifndef SUPERCHEER
#define SUPERCHEER

#include <small_header.h>

#include "Game/Objects/Game Objects/GameObject.h"
//#include "Game/Games/GameType.h"
//#include "Game/Objects/Game Objects/GameObjects/Cheer.h"


namespace CloudberryKingdom
{

	struct SuperCheer : public GameObject
	{
	
		virtual ~SuperCheer()
		{
#ifdef BOOST_BIN
			OnDestructor( "SuperCheer" );
#endif
		}


		struct CheerHelper : public Lambda
		{
		
			boost::shared_ptr<GameData> mygame;
			Vector2 pos;

		
			CheerHelper( const boost::shared_ptr<GameData> &mygame, Vector2 pos );

			void Apply();
		};

	
		int Rows;
	
		SuperCheer( int Rows );

		virtual void OnAdd();

	
		void AddWave( int Delay );
	};
}


#endif	//#ifndef SUPERCHEER
