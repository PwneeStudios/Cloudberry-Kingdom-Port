#ifndef SUPERCHEER
#define SUPERCHEER

#include <global_header.h>

namespace CloudberryKingdom
{
	class GameData;
}




namespace CloudberryKingdom
{
	class SuperCheer : public GameObject
	{
	private:
		class CheerHelper : public Lambda
		{
		private:
			std::shared_ptr<GameData> mygame;
			Vector2 pos;

		public:
			CheerHelper( const std::shared_ptr<GameData> &mygame, Vector2 pos );

			void Apply();
		};

	private:
		int Rows;
	public:
		SuperCheer( int Rows );

		virtual void OnAdd();

	private:
		void AddWave( int Delay );
	};
}


#endif	//#ifndef SUPERCHEER
