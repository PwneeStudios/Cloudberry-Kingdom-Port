#include <global_header.h>




namespace CloudberryKingdom
{

const std::shared_ptr<Generators> Generators::instance = std::make_shared<Generators>();

	const std::shared_ptr<Generators> &Generators::getInstance()
	{
		return instance;
	}

std::vector<AutoGen*> Gens, PreFill_1_Gens, PreFill_2_Gens, ActiveFill_1_Gens, Generators::WeightedPreFill_1_Gens = 0;

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
