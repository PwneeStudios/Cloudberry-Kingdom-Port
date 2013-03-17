#include <global_header.h>

#include "Hacks/List.h"

namespace CloudberryKingdom
{

	SwarmBundle::BobToSpritesLambda::BobToSpritesLambda( const boost::shared_ptr<Bob> &bob )
	{
		this->bob = bob;
	}

	void SwarmBundle::BobToSpritesLambda::Apply( const std::map<int, boost::shared_ptr<SpriteAnim> > &dict, const Vector2 &pos )
	{
		bob->MyPhsx->ToSprites( dict, pos );
	}

	void SwarmBundle::Release()
	{
		for ( std::vector<boost::shared_ptr<BobLink> >::const_iterator link = BobLinks.begin(); link != BobLinks.end(); ++link )
		{
			( *link )->j.reset();
			( *link )->k.reset();
		}

		BobLinks.clear();

		for ( std::vector<boost::shared_ptr<SwarmRecord> >::const_iterator swarm = Swarms.begin(); swarm != Swarms.end(); ++swarm )
			( *swarm )->Release();
		Swarms.clear();

		if ( AnimGroup.size() > 0 )
			for ( int i = 0; i < static_cast<int>( AnimGroup.size() ); i++ )
				if ( AnimGroup[ i ] != 0 )
					AnimGroup[ i ]->Release();
		AnimGroup.clear();
	}

	SwarmBundle::SwarmBundle()
	{
		Initialized = false;

		Swarms = std::vector<boost::shared_ptr<SwarmRecord> >();
	}

	void SwarmBundle::Init( const boost::shared_ptr<Level> &level )
	{
		if ( Initialized )
			return;

		BobLinks = std::vector<boost::shared_ptr<BobLink> >();
		if ( level->MyGame->MyGameFlags.IsTethered )
		{
			for ( BobVec::const_iterator bob = level->Bobs.begin(); bob != level->Bobs.end(); ++bob )
				if ( ( *bob )->MyBobLinks.size() > 0 )
					AddRange( BobLinks, ( *bob )->MyBobLinks );

			for ( std::vector<boost::shared_ptr<BobLink> >::const_iterator link = BobLinks.begin(); link != BobLinks.end(); ++link )
			{
				( *link )->_j = IndexOf( level->Bobs, ( *link )->j );
				( *link )->_k = IndexOf( level->Bobs, ( *link )->k );
			}
		}

		AnimGroup = std::vector<boost::shared_ptr<SpriteAnimGroup> >( 4 );

		int count = 0;
		for ( BobVec::iterator bob = level->Bobs.begin(); bob != level->Bobs.end(); ++bob )
		{
			AnimGroup[ count ] = boost::make_shared<SpriteAnimGroup>();
			AnimGroup[ count ]->Init( ( *bob )->PlayerObject, ( *bob )->MyPhsx->SpritePadding, boost::make_shared<BobToSpritesLambda>( *bob ) );
			count++;
		}
		Initialized = true;
	}

	void SwarmBundle::SetSwarm( const boost::shared_ptr<Level> &level, int i )
	{
		i = CoreMath::RestrictVal( 0, Swarms.size() - 1, i );

		CurrentSwarm = Swarms[ i ];
		level->CurPiece = CurrentSwarm->MyLevelPiece;

		for ( int j = 0; j < CurrentSwarm->MainRecord->NumBobs; j++ )
		{
			if ( j >= static_cast<int>( level->Bobs.size() ) )
				continue;
			level->Bobs[ j ]->MyRecord = CurrentSwarm->MainRecord->Recordings[ j ];
		}
	}

	const int SwarmBundle::getSwarmIndex() const
	{
		return IndexOf( Swarms, CurrentSwarm );
	}

	const int SwarmBundle::getNumSwarms() const
	{
		return static_cast<int>( Swarms.size() );
	}

	bool SwarmBundle::GetNextSwarm( const boost::shared_ptr<Level> &level )
	{
		int i = getSwarmIndex() + 1;
		if ( i < static_cast<int>( Swarms.size() ) )
		{
			SetSwarm( level, i );

			return true;
		}
		else
			return false;
	}

	bool SwarmBundle::EndCheck( const boost::shared_ptr<Level> &level )
	{
		return level->CurPhsxStep >= CurrentSwarm->MainRecord->Length;
	}

	void SwarmBundle::StartNewSwarm()
	{
		CurrentSwarm = boost::make_shared<SwarmRecord>();
		Swarms.push_back( CurrentSwarm );
	}

	void SwarmBundle::Draw( int Step, const boost::shared_ptr<Level> &level )
	{
		CurrentSwarm->Draw( Step, level, AnimGroup, BobLinks );
	}
}
