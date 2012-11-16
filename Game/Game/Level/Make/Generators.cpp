#include "Generators.h"
#include "Game/Objects/AutoGen.h"
#include "Game/Objects/In Game Objects/Blocks/NormalBlock__Auto.h"
#include "Game/Objects/In Game Objects/Blocks/Ceiling__Auto.h"
#include "Game/Objects/In Game Objects/Grab/Coin__Auto.h"
#include "Game/Objects/In Game Objects/Obstacles/Fireball__Auto.h"
#include "Game/Objects/In Game Objects/Obstacles/FireSpinner__Auto.h"
#include "Game/Objects/In Game Objects/Obstacles/Spike__Auto.h"
#include "Game/Objects/In Game Objects/Obstacles/Laser__Auto.h"
#include "Game/Objects/In Game Objects/Obstacles/Boulder__Auto.h"
#include "Game/Objects/In Game Objects/Obstacles/SpikeyGuy__Auto.h"
#include "Game/Objects/In Game Objects/Obstacles/FlyingBlob__Auto.h"
#include "Game/Objects/In Game Objects/Blocks/FallingBlock__Auto.h"
#include "Game/Objects/In Game Objects/Blocks/GhostBlock__Auto.h"
#include "Game/Objects/In Game Objects/Blocks/MovingBlock__Auto.h"
#include "Game/Objects/In Game Objects/Obstacles/BlockEmitter__Auto.h"
#include "Game/Objects/In Game Objects/Blocks/BouncyBlock__Auto.h"
#include "Game/Objects/In Game Objects/Obstacles/Cloud__Auto.h"
#include "Game/Objects/In Game Objects/Obstacles/SpikeyLine__Auto.h"
#include "Game/Objects/In Game Objects/Obstacles/Firesnake__Auto.h"
#include "Game/Objects/In Game Objects/Blocks/Conveyor__Auto.h"
#include "Game/Objects/In Game Objects/Blocks/Pendulum__Auto.h"
#include "Game/Objects/In Game Objects/Obstacles/Serpent__Auto.h"
#include "Game/Objects/In Game Objects/Obstacles/LavaDrip__Auto.h"

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;

namespace CloudberryKingdom
{

const std::shared_ptr<Generators> Generators::instance = std::make_shared<Generators>();

	const std::shared_ptr<Generators> &Generators::getInstance() const
	{
		return instance;
	}

std::vector<AutoGen*> Gens, PreFill_1_Gens, PreFill_2_Gens, ActiveFill_1_Gens, Generators::WeightedPreFill_1_Gens = 0;

	Generators::Generators()
	{
	}

	Generators::Generators()
	{
		Gens = std::vector<AutoGen*>();
		PreFill_1_Gens = std::vector<AutoGen*>();
		PreFill_2_Gens = std::vector<AutoGen*>();
		ActiveFill_1_Gens = std::vector<AutoGen*>();
		WeightedPreFill_1_Gens = std::vector<AutoGen*>();

		AddGenerator( NormalBlock_AutoGen::getInstance() );
		AddGenerator( Ceiling_AutoGen::getInstance() );

		AddGenerator( Coin_AutoGen::getInstance() );

		AddGenerator( Fireball_AutoGen::getInstance() );
		AddGenerator( FireSpinner_AutoGen::getInstance() );
		AddGenerator( Spike_AutoGen::getInstance() );
		AddGenerator( Laser_AutoGen::getInstance() );
		AddGenerator( Boulder_AutoGen::getInstance() );
		AddGenerator( SpikeyGuy_AutoGen::getInstance() );
		AddGenerator( FlyingBlob_AutoGen::getInstance() );
		AddGenerator( FallingBlock_AutoGen::getInstance() );
		AddGenerator( GhostBlock_AutoGen::getInstance() );
		AddGenerator( MovingBlock_AutoGen::getInstance() );
		AddGenerator( BlockEmitter_AutoGen::getInstance() );
		AddGenerator( BouncyBlock_AutoGen::getInstance() );
		AddGenerator( Cloud_AutoGen::getInstance() );
		AddGenerator( SpikeyLine_AutoGen::getInstance() );
		AddGenerator( Firesnake_AutoGen::getInstance() );
		AddGenerator( ConveyorBlock_AutoGen::getInstance() );
		AddGenerator( Pendulum_AutoGen::getInstance() );
		AddGenerator( Serpent_AutoGen::getInstance() );
		AddGenerator( LavaDrip_AutoGen::getInstance() );
	}

	void Generators::AddGenerator( const std::shared_ptr<AutoGen> &gen )
	{
		Gens.push_back( gen );
		if ( gen->Do_WeightedPreFill_1 )
			WeightedPreFill_1_Gens.push_back( gen );
		if ( gen->Do_PreFill_1 )
			PreFill_1_Gens.push_back( gen );
		if ( gen->Do_ActiveFill_1 )
			ActiveFill_1_Gens.push_back( gen );
		if ( gen->Do_PreFill_2 )
			PreFill_2_Gens.push_back( gen );
	}

	int Generators::IndexOf( const std::shared_ptr<AutoGen> &gen )
	{
		return Gens.find( gen );
	}
}
