#ifndef GENERATORS
#define GENERATORS

#include <small_header.h>

//#include "Game/Objects/AutoGen.h"
//#include "Game/Objects/In Game Objects/Blocks/BouncyBlock__Auto.h"
//#include "Game/Objects/In Game Objects/Blocks/Ceiling__Auto.h"
//#include "Game/Objects/In Game Objects/Blocks/Conveyor__Auto.h"
//#include "Game/Objects/In Game Objects/Blocks/FallingBlock__Auto.h"
//#include "Game/Objects/In Game Objects/Blocks/GhostBlock__Auto.h"
//#include "Game/Objects/In Game Objects/Blocks/MovingBlock__Auto.h"
//#include "Game/Objects/In Game Objects/Blocks/NormalBlock__Auto.h"
//#include "Game/Objects/In Game Objects/Blocks/Pendulum__Auto.h"
//#include "Game/Objects/In Game Objects/Grab/Coin__Auto.h"
//#include "Game/Objects/In Game Objects/Obstacles/BlockEmitter__Auto.h"
//#include "Game/Objects/In Game Objects/Obstacles/Boulder__Auto.h"
//#include "Game/Objects/In Game Objects/Obstacles/Cloud__Auto.h"
//#include "Game/Objects/In Game Objects/Obstacles/Fireball__Auto.h"
//#include "Game/Objects/In Game Objects/Obstacles/Firesnake__Auto.h"
//#include "Game/Objects/In Game Objects/Obstacles/FireSpinner__Auto.h"
//#include "Game/Objects/In Game Objects/Obstacles/FlyingBlob__Auto.h"
//#include "Game/Objects/In Game Objects/Obstacles/Laser__Auto.h"
//#include "Game/Objects/In Game Objects/Obstacles/LavaDrip__Auto.h"
//#include "Game/Objects/In Game Objects/Obstacles/Serpent__Auto.h"
//#include "Game/Objects/In Game Objects/Obstacles/SpikeyGuy__Auto.h"
//#include "Game/Objects/In Game Objects/Obstacles/SpikeyLine__Auto.h"
//#include "Game/Objects/In Game Objects/Obstacles/Spike__Auto.h"


namespace CloudberryKingdom
{

	struct Generators
	{

	
		static void InitializeStatics();

	
		static boost::shared_ptr<Generators> instance;
	
		const static boost::shared_ptr<Generators> &getInstance();

		static std::vector<boost::shared_ptr<AutoGen> > Gens, PreFill_1_Gens, PreFill_2_Gens, ActiveFill_1_Gens, WeightedPreFill_1_Gens;

	
		Generators();

	
		static void AddGenerator( const boost::shared_ptr<AutoGen> &gen );

		static int IndexOf( const boost::shared_ptr<AutoGen> &gen );

	};

}


#endif	//#ifndef GENERATORS
