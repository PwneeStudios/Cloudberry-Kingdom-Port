#include <global_header.h>
namespace CloudberryKingdom
{

	SwarmBundle::BobToSpritesLambda::BobToSpritesLambda( const std::shared_ptr<Bob> &bob )
	{
		this->bob = bob;
	}

	void SwarmBundle::BobToSpritesLambda::Apply( std::unordered_map<int, SpriteAnim*> &dict, Vector2 pos )
	{
		bob->MyPhsx->ToSprites( dict, pos );
	}

	void SwarmBundle::Release()
	{
		BobLinks.clear();

		for ( std::vector<SwarmRecord*>::const_iterator swarm = Swarms.begin(); swarm != Swarms.end(); ++swarm )
			( *swarm )->Release();
		Swarms.clear();

		if ( AnimGroup.size() > 0 )
			for ( int i = 0; i < AnimGroup.size(); i++ )
				if ( AnimGroup[ i ] != 0 )
					AnimGroup[ i ]->Release();
		AnimGroup.clear();
	}

	SwarmBundle::SwarmBundle()
	{
		Initialized = false;

		Swarms = std::vector<SwarmRecord*>();
	}

	void SwarmBundle::Init( const std::shared_ptr<Level> &level )
	{
		if ( Initialized )
			return;

		BobLinks = std::vector<BobLink*>();
		if ( level->MyGame->MyGameFlags.IsTethered )
		{
			for ( std::vector<Bob*>::const_iterator bob = level->Bobs.begin(); bob != level->Bobs.end(); ++bob )
				if ( ( *bob )->MyBobLinks.size() > 0 )
					BobLinks.AddRange( ( *bob )->MyBobLinks );

			for ( std::vector<BobLink*>::const_iterator link = BobLinks.begin(); link != BobLinks.end(); ++link )
			{
				( *link )->_j = level->Bobs.find( ( *link )->j );
				( *link )->_k = level->Bobs.find( ( *link )->k );
			}
		}

		AnimGroup = std::vector<SpriteAnimGroup*>( 4 );

		int count = 0;
		for ( std::vector<Bob*>::const_iterator bob = level->Bobs.begin(); bob != level->Bobs.end(); ++bob )
		{
			AnimGroup[ count ] = std::make_shared<SpriteAnimGroup>();
			AnimGroup[ count ]->Init( ( *bob )->PlayerObject, ( *bob )->MyPhsx->SpritePadding, std::make_shared<BobToSpritesLambda>( *bob ) );
			count++;
		}
		Initialized = true;
	}

	void SwarmBundle::SetSwarm( const std::shared_ptr<Level> &level, int i )
	{
		i = CoreMath::Restrict( 0, Swarms.size() - 1, i );

		CurrentSwarm = Swarms[ i ];
		level->CurPiece = CurrentSwarm->MyLevelPiece;

		for ( int j = 0; j < CurrentSwarm->MainRecord->NumBobs; j++ )
		{
			if ( j >= level->Bobs.size() )
				continue;
			level->Bobs[ j ]->MyRecord = CurrentSwarm->MainRecord->Recordings[ j ];
		}
	}

	const int &SwarmBundle::getSwarmIndex() const
	{
		return Swarms.find( CurrentSwarm );
	}

	const int &SwarmBundle::getNumSwarms() const
	{
		return Swarms.size();
	}

	bool SwarmBundle::GetNextSwarm( const std::shared_ptr<Level> &level )
	{
		int i = getSwarmIndex() + 1;
		if ( i < Swarms.size() )
		{
			SetSwarm( level, i );

			return true;
		}
		else
			return false;
	}

	bool SwarmBundle::EndCheck( const std::shared_ptr<Level> &level )
	{
		return level->CurPhsxStep >= CurrentSwarm->MainRecord->Length;
	}

	void SwarmBundle::StartNewSwarm()
	{
		CurrentSwarm = std::make_shared<SwarmRecord>();
		Swarms.push_back( CurrentSwarm );
	}

	void SwarmBundle::Draw( int Step, const std::shared_ptr<Level> &level )
	{
		CurrentSwarm->Draw( Step, level, AnimGroup, BobLinks );
	}
}
