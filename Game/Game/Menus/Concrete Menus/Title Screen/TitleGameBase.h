#ifndef TITLEGAMEBASE
#define TITLEGAMEBASE

#include <small_header.h>

//#include "Game/Tilesets/Backgrounds/Background.h"
#include "Game/Games/GameType.h"
//#include "Game/Level/Make/LockableBool.h"
//#include "Game/Level/Make/LevelSeedData.h"
//#include "Game/Objects/In Game Objects/Grab/MakeData.h"
//#include "Game/Level/Level.h"
//#include "Game/Objects/Special/CameraZone.h"
//#include "Game/Tools/Camera.h"
//#include "Game/Tools/Recycler.h"
//#include "Game/Tools/Tools.h"


namespace CloudberryKingdom
{
	struct TitleFactory : public GameFactory
	{
	
		virtual ~TitleFactory()
		{
#ifdef BOOST_BIN
			OnDestructor( "TitleFactory" );
#endif
		}


		virtual boost::shared_ptr<GameData> Make( const boost::shared_ptr<LevelSeedData> &data, bool MakeInBackground );

	};

	struct TitleGameData : public GameData
	{

		virtual ~TitleGameData()
		{
#ifdef BOOST_BIN
			OnDestructor( "TitleGameData" );
#endif
		}

	
		static void InitializeStatics();
	
		static boost::shared_ptr<GameFactory> Factory;

		virtual void Release();

		TitleGameData();

		virtual void SetToReturnTo( int code );

		virtual void ReturnTo( int code );

	
		boost::shared_ptr<CameraZone> CamZone;
		virtual boost::shared_ptr<Level> MakeLevel();

	
		virtual void Init();

		virtual void AdditionalReset();

		bool PanCamera;
	
		float PanAcc;
		float PanMaxSpeed;
		float PanMaxDist;
		float PanMinDist;

	
		virtual void PhsxStep();

		virtual void PostDraw();

	
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef TITLEGAMEBASE
