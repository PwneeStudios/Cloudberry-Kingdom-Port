#include <global_header.h>

namespace CloudberryKingdom
{

	FlyingBlob_Parameters::FlyingBlob_Parameters()
	{
		InitializeInstanceFields();
	}

	void FlyingBlob_Parameters::SetParameters( const std::shared_ptr<PieceSeedData> &PieceSeed, const std::shared_ptr<Level> &level )
	{
		AutoGen_Parameters::SetParameters( PieceSeed, level );

		std::shared_ptr<CloudberryKingdom::Upgrades> u = PieceSeed->getu();

		float FlyingBlobLevel = PieceSeed->MyUpgrades1->Get( Upgrade_FLY_BLOB );

		Motion = static_cast<MotionType>( level->getRnd()->Choose(MotionLevel, static_cast<int>(FlyingBlobLevel)) );

		KeepUnused = Param( PieceSeed );
		if ( std::dynamic_pointer_cast<BobPhsxSpaceship>( level->DefaultHeroType ) != 0 )
		{
			KeepUnused.SetVal( BobPhsxSpaceship::KeepUnused( u->Get( Upgrade_FLY_BLOB ) ) );
		}

		FillWeight = Param( PieceSeed, u->Get( Upgrade_FLY_BLOB ) );

		float val = DifficultyHelper::Interp( 40, 500,.5f * ( u->Get( Upgrade_JUMP ) + u->Get( Upgrade_FLY_BLOB ) ) );
		if ( val < 80 )
			val = 0;
		Range = Param( PieceSeed, val );

		float speed = 200 - 20 * u->Get( Upgrade_SPEED ) + 25 *.5f * ( u->Get( Upgrade_JUMP ) + u->Get( Upgrade_FLY_BLOB ) );
		Period = Param( PieceSeed, CoreMath::RestrictVal( 40.f, 1000.f, speed ) );

		EdgeSafety = Param( PieceSeed );
		EdgeSafety.SetVal( __max( 6, DifficultyHelper::Interp( 45, 6, u->Get( Upgrade_FLY_BLOB ) ) ) );

		Size = Param( PieceSeed, 1 );
	}

	void FlyingBlob_Parameters::InitializeInstanceFields()
	{
		const int tempVector[] = { 0, 1, 2, 3, 4, 5, 7, 8 };
		std::vector<int> temp_MotionLevel = std::vector<int>( tempVector, tempVector + sizeof( tempVector ) / sizeof( tempVector[ 0 ] ) );
		for ( int element = 0; element < sizeof( temp_MotionLevel ) / sizeof( temp_MotionLevel[ 0 ] ); element++ )
			MotionLevel[ element ] = temp_MotionLevel[ element ];
		TunnelCeiling = true;
		TunnelDisplacement = 0;
		TunnelMotionType = MotionType_HORIZONTAL;
	}

std::shared_ptr<FlyingBlob_AutoGen> FlyingBlob_AutoGen::instance = std::make_shared<FlyingBlob_AutoGen>();

	const std::shared_ptr<FlyingBlob_AutoGen> &FlyingBlob_AutoGen::getInstance()
	{
		return instance;
	}

	FlyingBlob_AutoGen::FlyingBlob_AutoGen()
	{
		Do_WeightedPreFill_1 = true;
		Do_PreFill_1 = true;
		//Generators.AddGenerator(this);
	}

	std::shared_ptr<AutoGen_Parameters> FlyingBlob_AutoGen::SetParameters( const std::shared_ptr<PieceSeedData> &data, const std::shared_ptr<Level> &level )
	{
		std::shared_ptr<FlyingBlob_Parameters> Params = std::make_shared<FlyingBlob_Parameters>();
		Params->SetParameters( data, level );

		return std::static_pointer_cast<AutoGen_Parameters>( Params );
	}

	void FlyingBlob_AutoGen::Circle( const std::shared_ptr<Level> &level, Vector2 Center, float Radius, int Num, int Dir )
	{
		Circle( level, Center, Radius, Num, Dir, 1 );
	}

	void FlyingBlob_AutoGen::Circle( const std::shared_ptr<Level> &level, Vector2 Center, float Radius, int Num, int Dir, float ModPeriod )
	{
		for ( int j = 0; j < Num; j++ )
		{
			std::shared_ptr<FlyingBlob> blob = std::static_pointer_cast<FlyingBlob>( CreateAt( level, Center ) );

			blob->SetColor( FlyingBlob::BlobColor_BLUE );

			blob->Period = 3 * blob->Period / 2;
			blob->Offset = static_cast<int>( j * ( static_cast<float>( blob->Period ) / Num ) );

			SetMoveType( blob, Radius, FlyingBlob_Parameters::MotionType_CIRLCES, level->getRnd() );

			blob->Displacement.X = Dir * abs( blob->Displacement.X );

			blob->getCore()->GenData.RemoveIfUnused = false;

			level->AddObject( blob );
		}
	}

	void FlyingBlob_AutoGen::Pinwheel( const std::shared_ptr<Level> &level, Vector2 BL, Vector2 TR )
	{
		Vector2 Center = ( TR + BL ) / 2;

		int Num = 30;

		//Circle(level, Center, 160 * 7, Num, -1);
		//Circle(level, Center, 160 * 10, Num, 1);

		float mod = 1.2f;
		for ( int i = 7; i <= 19; i += 3 )
		{
			Circle( level, Center, 160.f * i, Num, 1, mod );
			mod += .2f;
		}

		//for (int i = 4; i <= 8; i += 2)
		  //  Circle(level, Center, 160 * i + 90, Num, 1);
	}

	void FlyingBlob_AutoGen::SetTunnelBlobParameter( const std::shared_ptr<FlyingBlob> &blob, const std::shared_ptr<FlyingBlob_Parameters> &Params, const std::shared_ptr<Rand> &Rnd )
	{
		blob->SetColor( FlyingBlob::BlobColor_PINK );

		blob->getCore()->GenData.RemoveIfUnused = false;

		SetMoveType( blob, Params->TunnelDisplacement, Params->TunnelMotionType, Rnd );
		blob->Displacement.X = abs( blob->Displacement.X );

		blob->Offset = 0;
	}

	void FlyingBlob_AutoGen::Tunnel( const std::shared_ptr<Level> &level, Vector2 BL, Vector2 TR )
	{
		// Get Goomba parameters
		std::shared_ptr<FlyingBlob_Parameters> Params = std::static_pointer_cast<FlyingBlob_Parameters>( level->getStyle()->FindParams( FlyingBlob_AutoGen::getInstance() ) );

		BL.X = level->FillBL.X;

		float Step = 150;
		Vector2 size = ( TR - BL ) / Step;
		int N = static_cast<int>( size.X ), M = static_cast<int>( size.Y );

		Params->TunnelGUIDs = std::vector<std::vector<unsigned long long> >( N, M );

		for ( int i = 0; i < N; i++ )
		{
			for ( int j = 0; j < M; j++ )
			{
				std::shared_ptr<FlyingBlob> blob = std::static_pointer_cast<FlyingBlob>( CreateAt( level, BL + Vector2( static_cast<float>( i ), static_cast<float>( j ) ) * Step ) );
				SetTunnelBlobParameter( blob, Params, level->getRnd() );

				Params->TunnelGUIDs[ i ][ j ] = blob->getCore()->MyGuid;
			}
		}
	}

	/*void FlyingBlob_AutoGen::Clean( array_Renamed<std::shared_ptr<ObjectBase> , 2> *array_Renamed )
	{
		for ( int i = 0; i < array_Renamed.GetLength( 0 ); i++ )
			for ( int j = 0; j < array_Renamed.GetLength( 1 ); j++ )
				if ( array_Renamed[ i ][ j ] != 0 && array_Renamed[ i ][ j ]->getCore()->MarkedForDeletion )
					array_Renamed[ i ][ j ] = 0;
	}

	void FlyingBlob_AutoGen::Clean( array_Renamed<std::shared_ptr<ObjectBase> , 2> *array_Renamed, int i, int j )
	{
		if ( array_Renamed[ i ][ j ] == 0 )
			return;
		array_Renamed[ i ][ j ]->CollectSelf();
		array_Renamed[ i ][ j ] = 0;
	}

	void FlyingBlob_AutoGen::CleanupTunnel( const std::shared_ptr<Level> &level )
	{
		// Get Goomba parameters
		std::shared_ptr<FlyingBlob_Parameters> Params = std::static_pointer_cast<FlyingBlob_Parameters>( level->getStyle()->FindParams( FlyingBlob_AutoGen::getInstance() ) );

		std::vector<std::vector<unsigned long long> > GUIDs = Params->TunnelGUIDs;
		std::vector<ObjectVec > Blobs = std::vector<ObjectVec >( GUIDs.GetLength( 0 ), GUIDs.GetLength( 1 ) );

		for ( int i = 0; i < Blobs.GetLength( 0 ); i++ )
			for ( int j = 0; j < Blobs.GetLength( 1 ); j++ )
				Blobs[ i ][ j ] = level->GuidToObj( GUIDs[ i ][ j ] );

		// Head room
		for ( int i = 0; i < Blobs.GetLength( 0 ); i++ )
		{
			for ( int j = Blobs.GetLength( 1 ) - 1; j >= 1; j-- )
			{
				if ( Blobs[ i ][ j ] == 0 )
					continue;
				if ( Blobs[ i ][ j ]->getCore()->GenData.Used )
					continue;

				if ( Blobs[ i ][ j - 1 ] == 0 )
					Clean( Blobs, i, j );
			}
		}

		// Remove ceiling
		if ( !Params->TunnelCeiling )
		{
			for ( int i = 0; i < Blobs.GetLength( 0 ); i++ )
			{
				int j;
				for ( j = Blobs.GetLength( 1 ) - 1; j >= 1; j-- )
					if ( Blobs[ i ][ j ] == 0 )
						break;

				for ( ; j < Blobs.GetLength( 1 ); j++ )
					Clean( Blobs, i, j );
			}
		}

		for ( int i = 0; i < Blobs.GetLength( 0 ); i++ )
		{
			for ( int j = 0; j < Blobs.GetLength( 1 ); j++ )
			{
				if ( Blobs[ i ][ j ] == 0 )
					continue;
				if ( Blobs[ i ][ j ]->getCore()->GenData.Used )
					continue;

				if ( j - 1 >= 0 && Blobs[ i ][ j - 1 ] == 0 )
					continue;
				if ( j + 1 < Blobs.GetLength( 1 ) && Blobs[ i ][ j + 1 ] == 0 )
					continue;
				if ( j - 2 >= 0 && Blobs[ i ][ j - 2 ] == 0 )
					continue;
				if ( j + 2 < Blobs.GetLength( 1 ) && Blobs[ i ][ j + 2 ] == 0 )
					continue;
				if ( j - 3 >= 0 && Blobs[ i ][ j - 3 ] == 0 )
					continue;
				if ( j + 3 < Blobs.GetLength( 1 ) && Blobs[ i ][ j + 3 ] == 0 )
					continue;

				Blobs[ i ][ j ]->CollectSelf();
			}
		}
		Clean( Blobs );

		// Remove warts
		for ( int i = 1; i < Blobs.GetLength( 0 ) - 1; i++ )
		{
			for ( int j = 1; j < Blobs.GetLength( 1 ); j++ )
			{
				if ( Blobs[ i ][ j ] == 0 )
					continue;
				if ( Blobs[ i ][ j ]->getCore()->GenData.Used )
					continue;

				if ( Blobs[ i - 1 ][ j ] == 0 && Blobs[ i + 1 ][ j ] == 0 && Blobs[ i ][ j - 1 ] == 0 )
					Clean( Blobs, i, j );
			}
		}

		GUIDs = Params->TunnelGUIDs.clear();
		Blobs.clear();
	}*/

	void FlyingBlob_AutoGen::PreFill_1( const std::shared_ptr<Level> &level, Vector2 BL, Vector2 TR )
	{
		AutoGen::ActiveFill_1( level, BL, TR );

		// Get Goomba parameters
		std::shared_ptr<FlyingBlob_Parameters> Params = std::static_pointer_cast<FlyingBlob_Parameters>( level->getStyle()->FindParams( FlyingBlob_AutoGen::getInstance() ) );

		if ( Params->Special.Tunnel )
			Tunnel( level, BL, TR );
		if ( Params->Special.Pinwheel )
			Pinwheel( level, BL, TR );
	}

	void FlyingBlob_AutoGen::Cleanup_1( const std::shared_ptr<Level> &level, Vector2 BL, Vector2 TR )
	{
		AutoGen::Cleanup_1( level, BL, TR );

		// Get Goomba parameters
		std::shared_ptr<FlyingBlob_Parameters> Params = std::static_pointer_cast<FlyingBlob_Parameters>( level->getStyle()->FindParams( FlyingBlob_AutoGen::getInstance() ) );

		/*if ( Params->Special.Tunnel )
			CleanupTunnel( level );*/
	}

	void FlyingBlob_AutoGen::PreFill_2( const std::shared_ptr<Level> &level, Vector2 BL, Vector2 TR )
	{
		AutoGen::PreFill_2( level, BL, TR );
	}

	void FlyingBlob_AutoGen::Cleanup_2( const std::shared_ptr<Level> &level, Vector2 BL, Vector2 TR )
	{
		AutoGen::Cleanup_2( level, BL, TR );
	}

	void FlyingBlob_AutoGen::SetMoveType( const std::shared_ptr<FlyingBlob> &fblob, float Displacement, FlyingBlob_Parameters::MotionType mtype, const std::shared_ptr<Rand> &Rnd )
	{
		switch ( mtype )
		{
			case FlyingBlob_Parameters::MotionType_VERTICAL:
				fblob->MyMoveType = FlyingBlob::PrescribedMoveType_LINE;
				fblob->Displacement = Vector2( 0,.5f * Displacement );
				break;

			case FlyingBlob_Parameters::MotionType_HORIZONTAL:
				fblob->MyMoveType = FlyingBlob::PrescribedMoveType_LINE;
				fblob->Displacement = Vector2( Displacement, 0 );
				break;

			case FlyingBlob_Parameters::MotionType_CROSS:
				fblob->MyMoveType = FlyingBlob::PrescribedMoveType_LINE;
				if ( Rnd->Rnd->NextDouble() > .5f )
					fblob->Displacement = Vector2( Displacement,.5f * Displacement );
				else
					fblob->Displacement = Vector2( -Displacement,.5f * Displacement );
				break;

			case FlyingBlob_Parameters::MotionType_CIRLCES:
				fblob->MyMoveType = FlyingBlob::PrescribedMoveType_CIRCLE;
				fblob->Displacement = Vector2( Displacement *.7f, Displacement *.5f );
				fblob->Displacement.X *= Rnd->Rnd->Next( 0, 2 ) * 2 - 1;
				break;

			case FlyingBlob_Parameters::MotionType_AA:
				if ( Rnd->Rnd->NextDouble() > .5f )
					SetMoveType( fblob, Displacement, FlyingBlob_Parameters::MotionType_VERTICAL, Rnd );
				else
					SetMoveType( fblob, Displacement, FlyingBlob_Parameters::MotionType_HORIZONTAL, Rnd );
				break;

			case FlyingBlob_Parameters::MotionType_STRAIGHT:
				if ( Rnd->Rnd->NextDouble() > .5f )
					SetMoveType( fblob, Displacement, FlyingBlob_Parameters::MotionType_CROSS, Rnd );
				else
					SetMoveType( fblob, Displacement, FlyingBlob_Parameters::MotionType_AA, Rnd );
				break;

			case FlyingBlob_Parameters::MotionType_HEART:
				fblob->MyMoveType = FlyingBlob::PrescribedMoveType_STAR;
				fblob->Displacement = Vector2( Displacement *.7f, Displacement *.7f );
				fblob->Displacement.X *= Rnd->Rnd->Next( 0, 2 ) * 2 - 1;
				break;

			case FlyingBlob_Parameters::MotionType_ALL:
				double rnd = Rnd->Rnd->NextDouble();
				if ( rnd > .66666f )
					SetMoveType( fblob, Displacement, FlyingBlob_Parameters::MotionType_STRAIGHT, Rnd );
				else
				{
					if ( rnd > .33333f )
						SetMoveType( fblob, Displacement, FlyingBlob_Parameters::MotionType_CIRLCES, Rnd );
					else
						SetMoveType( fblob, Displacement, FlyingBlob_Parameters::MotionType_HEART, Rnd );
				}
				break;
		}
	}

	std::shared_ptr<ObjectBase> FlyingBlob_AutoGen::CreateAt( const std::shared_ptr<Level> &level, Vector2 pos, Vector2 BL, Vector2 TR )
	{
		AutoGen::CreateAt( level, pos, BL, TR );

		std::shared_ptr<FlyingBlob> NewBlob = std::static_pointer_cast<FlyingBlob>( BasicCreateAt( level, pos ) );

		TR.X += 200;
		Tools::EnsureBounds_X( NewBlob, TR, BL );

		// If the blob is too low make sure it's path is horizontal
		if ( pos.Y < BL.Y + 500 )
			SetMoveType( NewBlob, CoreMath::SupNorm( NewBlob->Displacement ), FlyingBlob_Parameters::MotionType_HORIZONTAL, level->getRnd() );

		level->AddObject( NewBlob );

		return NewBlob;
	}

	std::shared_ptr<ObjectBase> FlyingBlob_AutoGen::CreateAt( const std::shared_ptr<Level> &level, Vector2 pos )
	{
		AutoGen::CreateAt( level, pos );

		std::shared_ptr<FlyingBlob> NewBlob = std::static_pointer_cast<FlyingBlob>( BasicCreateAt( level, pos ) );

		level->AddObject( NewBlob );

		return NewBlob;
	}

	std::shared_ptr<ObjectBase> FlyingBlob_AutoGen::BasicCreateAt( const std::shared_ptr<Level> &level, Vector2 pos )
	{
		std::shared_ptr<StyleData> Style = level->getStyle();
		std::shared_ptr<RichLevelGenData> GenData = level->CurMakeData->GenData;
		std::shared_ptr<PieceSeedData> piece = level->CurMakeData->PieceSeed;

		// Get Goomba parameters
		std::shared_ptr<FlyingBlob_Parameters> Params = std::static_pointer_cast<FlyingBlob_Parameters>( level->getStyle()->FindParams( FlyingBlob_AutoGen::getInstance() ) );

		// Make the new blob
		std::shared_ptr<FlyingBlob> NewBlob = std::static_pointer_cast<FlyingBlob>( level->getRecycle()->GetObject(ObjectType_FLYING_BLOB, true) );
		NewBlob->Init( pos, level );

		NewBlob->getCore()->Data.Position = NewBlob->getCore()->StartData.Position = pos;
		NewBlob->Period = static_cast<int>( Params->Period.GetVal( pos ) );

		//NewBlob.Offset = MyLevel.Rnd.Rnd.Next(0, NewBlob.Period);
		NewBlob->Offset = level->getStyle()->GetOffset( NewBlob->Period, pos, level->getStyle()->FlyingBlobOffsetType );

		float Displacement = Params->Range.GetVal( pos );
		SetMoveType( NewBlob, Displacement, Params->Motion, level->getRnd() );

		// Decide if we should keep the blob even if unused
		if ( level->getRnd()->Rnd->NextDouble() < Params->KeepUnused.GetVal(pos) )
			NewBlob->getCore()->GenData.RemoveIfUnused = false;
		else
			NewBlob->getCore()->GenData.RemoveIfUnused = true;

		if ( level->getStyle()->RemoveBlockOnOverlap )
			NewBlob->getCore()->GenData.RemoveIfOverlap = true;

		NewBlob->getCore()->GenData.EdgeSafety = Params->EdgeSafety.GetVal(pos);

		return NewBlob;
	}
}
