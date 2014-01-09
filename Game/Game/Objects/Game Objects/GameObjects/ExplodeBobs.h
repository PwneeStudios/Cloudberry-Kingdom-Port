#ifndef EXPLODEBOBS
#define EXPLODEBOBS

#include <small_header.h>

#include "Game/Objects/Game Objects/GameObjects/GUI_Panel.h"
//#include "Game/Player/PlayerManager.h"
//#include "Game/Menus/Concrete Menus/Score Screens/ScoreScreen.h"
//#include "Game/Objects/Bob/Bob.h"
//#include "Game/Objects/In Game Objects/Grab/MakeData.h"
//#include "Game/Level/Level.h"
//#include "Game/Objects/In Game Objects/Obstacles/CloudberryKingdom.Fireball.h"


namespace CloudberryKingdom
{

	struct ExplodeBobs : public GUI_Panel
	{

		virtual ~ExplodeBobs()
		{
#ifdef BOOST_BIN
			OnDestructor( "ExplodeBobs" );
#endif
		}

	
		enum Speed
		{
			Speed_REGULAR,
			Speed_FAST
		};
	
		ExplodeBobs( int speed );
		boost::shared_ptr<ExplodeBobs> ExplodeBobs_Construct( int speed );

	
		int MySpeed;

	
		void SetSpeed( int speed );

		boost::shared_ptr<Lambda> OnDone;
	
		void Finish();

		static int CompareBobs( const boost::shared_ptr<Bob> &A, const boost::shared_ptr<Bob> &B );

		int Count;
	
		int InitialDelay_MultipleBobs, Delay, InitialDelay_OneBob;
	
		virtual void MyPhsxStep();

	
		void InitializeInstanceFields();
	};

}


#endif	//#ifndef EXPLODEBOBS
