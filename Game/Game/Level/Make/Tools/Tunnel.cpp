#include <global_header.h>

namespace CloudberryKingdom
{

	TunnelFill::TunnelFill()
	{
		InitializeInstanceFields();
	}

	void TunnelFill::Init( int N, int M )
	{
		this->N = N;
		this->M = M;

		TunnelGUIDs = std::vector<std::vector<unsigned long long> >( N, std::vector<unsigned long long>( M ) );
		TunnelObjs = std::vector<ObjectVec >( N, ObjectVec( M ) );
	}

	void TunnelFill::SetTunnelObjParameter( const boost::shared_ptr<ObjectBase> &obj )
	{
		obj->getCore()->GenData.RemoveIfUnused = false;
	}

	void TunnelFill::Clean()
	{
		for ( int i = 0; i < N; i++ )
			for ( int j = 0; j < M; j++ )
				if ( TunnelObjs[ i ][ j ] != 0 && TunnelObjs[ i ][ j ]->getCore()->MarkedForDeletion )
					TunnelObjs[ i ][ j ] = 0;
	}

	void TunnelFill::Clean( int i, int j )
	{
		if ( TunnelObjs[ i ][ j ] == 0 )
			return;
		TunnelObjs[ i ][ j ]->CollectSelf();
		TunnelObjs[ i ][ j ] = 0;
	}

	void TunnelFill::CleanupTunnel( const boost::shared_ptr<Level> &level )
	{
		std::map<unsigned long long, boost::shared_ptr<ObjectBase> > ObjDict = std::map<unsigned long long, boost::shared_ptr<ObjectBase> >();
		for ( ObjectVec::const_iterator obj = level->Objects.begin(); obj != level->Objects.end(); ++obj )
			if ( ObjDict.find( ( *obj )->getCore()->MyGuid ) == ObjDict.end() )
				ObjDict.insert( std::make_pair( ( *obj )->getCore()->MyGuid, *obj ) );

		// Convert GUIDs to IObjects
		for ( int i = 0; i < N; i++ )
			for ( int j = 0; j < M; j++ )
			{
				if ( ObjDict.find( TunnelGUIDs[ i ][ j ] ) != ObjDict.end() )
					TunnelObjs[ i ][ j ] = ObjDict[ TunnelGUIDs[ i ][ j ] ];
				else
					TunnelObjs[ i ][ j ] = 0;
				//TunnelObjs[i, j] = level.LookupGUID(TunnelGUIDs[i, j]);
				if ( TunnelObjs[ i ][ j ] != 0 && TunnelObjs[ i ][ j ]->getCore()->MarkedForDeletion )
					TunnelObjs[ i ][ j ] = 0;
			}

		// Head room
		for ( int i = 0; i < N; i++ )
		{
			for ( int j = M - 1; j >= 1; j-- )
			{
				if ( TunnelObjs[ i ][ j ] == 0 )
					continue;
				if ( TunnelObjs[ i ][ j ]->getCore()->GenData.Used )
					continue;

				if ( TunnelObjs[ i ][ j - 1 ] == 0 )
					Clean( i, j );
			}
		}

		// Remove ceiling
		if ( !TunnelCeiling )
		{
			for ( int i = 0; i < N; i++ )
			{
				int j;
				for ( j = M - 1; j >= 1; j-- )
					if ( TunnelObjs[ i ][ j ] == 0 )
						break;

				for ( ; j < M; j++ )
					Clean( i, j );
			}
		}

		// Remove floor
		if ( !TunnelFloor )
		{
			for ( int i = 0; i < N; i++ )
			{
				int j;
				for ( j = 0; j < M - 1; j++ )
					if ( TunnelObjs[ i ][ j ] == 0 )
						break;

				for ( ; j >= 0; j-- )
					Clean( i, j );
			}
		}

		// Remove excess
		for ( int i = 0; i < N; i++ )
		{
			for ( int j = 0; j < M; j++ )
			{
				if ( TunnelObjs[ i ][ j ] == 0 )
					continue;
				if ( TunnelObjs[ i ][ j ]->getCore()->GenData.Used )
					continue;

				if ( j - 1 >= 0 && TunnelObjs[ i ][ j - 1 ] == 0 )
					continue;
				if ( j + 1 < M && TunnelObjs[ i ][ j + 1 ] == 0 )
					continue;

				if ( Thickness > 1 )
				{
					if ( j - 2 >= 0 && TunnelObjs[ i ][ j - 2 ] == 0 )
						continue;
					if ( j + 2 < M && TunnelObjs[ i ][ j + 2 ] == 0 )
						continue;
				}

				if ( Thickness > 2 )
				{
					if ( j - 3 >= 0 && TunnelObjs[ i ][ j - 3 ] == 0 )
						continue;
					if ( j + 3 < M && TunnelObjs[ i ][ j + 3 ] == 0 )
						continue;
				}

				TunnelObjs[ i ][ j ]->CollectSelf();
			}
		}
		Clean();

		// Remove warts
		if ( RemoveWarts )
		for ( int i = 1; i < N - 1; i++ )
		{
			for ( int j = 1; j < M; j++ )
			{
				if ( TunnelObjs[ i ][ j ] == 0 )
					continue;
				if ( TunnelObjs[ i ][ j ]->getCore()->GenData.Used )
					continue;

				if ( TunnelObjs[ i - 1 ][ j ] == 0 && TunnelObjs[ i + 1 ][ j ] == 0 && TunnelObjs[ i ][ j - 1 ] == 0 )
					Clean( i, j );
			}
		}

		TunnelGUIDs.clear();
		TunnelObjs.clear();
	}

	void TunnelFill::InitializeInstanceFields()
	{
		N = 0; M = 0;

		TunnelCeiling = true;
		TunnelFloor = true;
		RemoveWarts = false;
		HeadRoom = 0;
		Thickness = 1;
	}
}
