#include <global_header.h>

namespace CloudberryKingdom
{

	void BlockEmitter_Parameters::SetParameters( const boost::shared_ptr<PieceSeedData> &PieceSeed, const boost::shared_ptr<Level> &level )
	{
		AutoGen_Parameters::SetParameters( PieceSeed, level );

		boost::shared_ptr<CloudberryKingdom::Upgrades> u = PieceSeed->getu();

		MyStyle = static_cast<Style>( level->getRnd()->RndInt( 0, BlockEmitter_Parameters::Style_LENGTH - 1 ) );

		FillWeight = Param( PieceSeed,.5f * u->Get( Upgrade_ELEVATOR ) );

		KeepUnused = Param( PieceSeed );
		if ( boost::dynamic_pointer_cast<BobPhsxSpaceship>( level->DefaultHeroType ) != 0 )
		{
			KeepUnused.SetVal( BobPhsxSpaceship::KeepUnused( u->Get( Upgrade_GHOST_BLOCK ) ) );
		}

		float D;
		if ( u->Get( Upgrade_ELEVATOR ) > 0 )
			D = .105f * DifficultyHelper::Interp19( 5000, 500, u->Get( Upgrade_ELEVATOR ) );
		else
			D = 1400;

		Dist = Param( PieceSeed );
		Dist.SetVal( D );

		DistAdd = Param( PieceSeed );
		DistAdd.SetVal( DifficultyHelper::Interp19( .135f * 2800,.385f * 500, u->Get( Upgrade_ELEVATOR ) ) );

		Amp = Param( PieceSeed );
		Amp.SetVal( __min( 450, 0 + 30 * u->Get( Upgrade_ELEVATOR ) ) );

		Types = Param( PieceSeed );
		Types.SetVal( __min( 2, u->Get( Upgrade_ELEVATOR ) / 4 ) );

		Delay = Param( PieceSeed );
		Delay.SetVal( __max( 60, 120 - 6 * u->Get( Upgrade_SPEED ) ) );

		Speed = Param( PieceSeed );
		Speed.SetVal( DifficultyHelper::Interp19( 5.6f, 16, u->Get( Upgrade_SPEED ) ) );

		Width = Param( PieceSeed, DifficultyHelper::Interp159( 150, 120, 75, u->Get( Upgrade_ELEVATOR ) ) );

		SpeedAdd = Param( PieceSeed );
		SpeedAdd.SetVal( DifficultyHelper::Interp19( 5.6f, 13, u->Get( Upgrade_SPEED ) ) *.025f * u->Get( Upgrade_ELEVATOR ) );

		WidthAdd = Param( PieceSeed );
		WidthAdd.SetVal( 0 );
	}

	void BlockEmitter_Parameters::InitializeInstanceFields()
	{
		LastUsedTimeStamp = 0;
		StepCutoff = 1350;
	}

boost::shared_ptr<BlockEmitter_AutoGen> BlockEmitter_AutoGen::instance = boost::make_shared<BlockEmitter_AutoGen>();

	const boost::shared_ptr<BlockEmitter_AutoGen> &BlockEmitter_AutoGen::getInstance()
	{
		return instance;
	}

	BlockEmitter_AutoGen::BlockEmitter_AutoGen()
	{
		Do_PreFill_1 = true;
		Do_WeightedPreFill_1 = true;
	}

	boost::shared_ptr<ObjectBase> BlockEmitter_AutoGen::CreateAt( const boost::shared_ptr<Level> &level, Vector2 pos )
	{
		return AutoGen::CreateAt( level, pos );

		// Do nothing
	}

	boost::shared_ptr<AutoGen_Parameters> BlockEmitter_AutoGen::SetParameters( const boost::shared_ptr<PieceSeedData> &data, const boost::shared_ptr<Level> &level )
	{
		boost::shared_ptr<BlockEmitter_Parameters> Params = boost::make_shared<BlockEmitter_Parameters>();
		Params->SetParameters( data, level );

		return boost::static_pointer_cast<AutoGen_Parameters>( Params );
	}

	void BlockEmitter_AutoGen::PreFill_1( const boost::shared_ptr<Level> &level, Vector2 BL, Vector2 TR )
	{
		AutoGen::PreFill_1( level, BL, TR );

		// Get BlockEmitter parameters
		boost::shared_ptr<BlockEmitter_Parameters> Params = boost::static_pointer_cast<BlockEmitter_Parameters>( level->getStyle()->FindParams( BlockEmitter_AutoGen::getInstance() ) );

		Vector2 Pos = BL;
		int count = 0;

		// Fill horizontal level
		if ( level->getPieceSeed()->GeometryType == LevelGeometry_RIGHT )
			while ( Pos.X < level->Fill_TR.X )
			{
				if ( Params->Dist.GetVal( Pos ) < Params->StepCutoff )
				{
					boost::shared_ptr<BlockEmitter> bm = boost::static_pointer_cast<BlockEmitter>( level->getRecycle()->GetObject(ObjectType_BLOCK_EMITTER, true) );
					bm->Init( Pos, level, level->CurMakeData->PieceSeed->ElevatorBoxStyle );

					float Vel = GetVel( Params, Pos );

					bool Bottom = false;
					switch ( level->getStyle()->ElevatorSwitchType )
					{
						case StyleData::_ElevatorSwitchType_ALL_DOWN:
							Bottom = true;
							break;
						case StyleData::_ElevatorSwitchType_ALL_UP:
							Bottom = false;
							break;
						case StyleData::_ElevatorSwitchType_ALTERNATE:
							Bottom = count % 2 == 0;
							break;
						case StyleData::_ElevatorSwitchType_RANDOM:
							Bottom = level->getRnd()->Rnd->NextDouble() > .5f;
							break;
					}

					if ( Bottom )
					{
						bm->EmitData.Position = bm->getCore()->Data.Position = Vector2(Pos.X, level->getMainCamera()->BL.Y - 200);
						bm->EmitData.Velocity = Vector2( 0, Vel );
					}
					else
					{
						bm->EmitData.Position = bm->getCore()->Data.Position = Vector2(Pos.X, level->getMainCamera()->TR.Y + 200);
						bm->EmitData.Velocity = Vector2( 0, -Vel );
					}

					SetAndAdd( level, Params, Pos, bm );
					bm->Range.Y = level->getMainCamera()->GetHeight() / 2;
				}

				Pos.X += Params->Dist.GetVal( Pos ) + level->getRnd()->RndFloat(0, Params->DistAdd.GetVal(Pos));

				count++;
			}
		// Fill vertical level
		else
			while ( Pos.Y < TR.Y )
			{
				if ( Params->Dist.GetVal( Pos ) < Params->StepCutoff )
				{
					float DistAdd = Params->Dist.GetVal( Pos );
					if ( level->getPieceSeed()->GeometryType == LevelGeometry_DOWN )
						DistAdd *= .2f;

					if ( DistAdd < Params->StepCutoff )
					{
						boost::shared_ptr<BlockEmitter> bm = boost::static_pointer_cast<BlockEmitter>( level->getRecycle()->GetObject(ObjectType_BLOCK_EMITTER, true) );

						float Vel = GetVel( Params, Pos );

						bool Left = false;
						switch ( level->getStyle()->ElevatorSwitchType )
						{
							case StyleData::_ElevatorSwitchType_ALL_DOWN:
								Left = true;
								break;
							case StyleData::_ElevatorSwitchType_ALL_UP:
								Left = false;
								break;
							case StyleData::_ElevatorSwitchType_ALTERNATE:
								Left = count % 2 == 0;
								break;
							case StyleData::_ElevatorSwitchType_RANDOM:
								Left = level->getRnd()->Rnd->NextDouble() > .5f;
								break;
						}

						if ( Left )
						{
							bm->EmitData.Position = bm->getCore()->Data.Position = Vector2(level->getMainCamera()->BL.X - 200, Pos.Y);
							bm->EmitData.Velocity = Vector2( Vel, 0 );
						}
						else
						{
							bm->EmitData.Position = bm->getCore()->Data.Position = Vector2(level->getMainCamera()->TR.X + 200, Pos.Y);
							bm->EmitData.Velocity = Vector2( -Vel, 0 );
						}

						SetAndAdd( level, Params, Pos, bm );
						bm->Range.Y = bm->Range.X;
						bm->Range.X = level->getMainCamera()->GetWidth() / 2;
					}
				}

				Pos.Y += Params->Dist.GetVal( Pos ) + level->getRnd()->RndFloat(0, Params->DistAdd.GetVal(Pos));

				count++;
			}
	}

	float BlockEmitter_AutoGen::GetVel( const boost::shared_ptr<BlockEmitter_Parameters> &Params, Vector2 &Pos )
	{
		//float SpeedAdd = Params.SpeedAdd.GetVal(Pos);

		float Vel = Params->Speed.GetVal( Pos ) + 0;
		//Tools::ChooseOne(SpeedAdd, 0, -SpeedAdd);

		//MyLevel.Rnd.RndFloat(-Params.SpeedAdd.GetVal(Pos),
		//             Params.SpeedAdd.GetVal(Pos));

		return Vel;
	}

	void BlockEmitter_AutoGen::SetAndAdd( const boost::shared_ptr<Level> &level, const boost::shared_ptr<BlockEmitter_Parameters> &Params, Vector2 Pos, const boost::shared_ptr<BlockEmitter> &bm )
	{
		bm->Delay = static_cast<int>( Params->Delay.GetVal( Pos ) );

		// Longer delays for vertical levels
		if ( level->Geometry == LevelGeometry_UP || level->Geometry == LevelGeometry_DOWN )
			bm->Delay *= 2;

		bm->Size = Vector2( 0, 40 );
		bm->Size.X = Params->Width.GetVal( Pos ) + level->getRnd()->RndFloat(0, Params->WidthAdd.GetVal(Pos));
		bm->AlwaysOn = true;

		//bm.Core.GenData.RemoveIfUnused = level.DefaultHeroType is BobPhsxSpaceship ? false : true;
		bm->getCore()->GenData.Decide_RemoveIfUnused(Params->KeepUnused.GetVal(Pos), level->getRnd());

		// Discrete period offsets
		int NumOffsets = 4; // Params.NumOffsets;
		bm->Offset = level->getRnd()->Rnd->Next(0, NumOffsets) * bm->Delay / NumOffsets;

		bm->MyMoveType = static_cast<MovingPlatform::MoveType>( level->getRnd()->Rnd->Next(0, static_cast<int>(Params->Types.GetVal(Pos))) );
		bm->Amp = Params->Amp.GetVal( Pos );

		if ( level->getStyle()->RemoveBlockOnOverlap )
			bm->getCore()->GenData.RemoveIfOverlap = true;

		level->AddObject( bm );
	}

	void BlockEmitter_AutoGen::Cleanup_2( const boost::shared_ptr<Level> &level, Vector2 BL, Vector2 TR )
	{
		AutoGen::Cleanup_2( level, BL, TR );
	}
}
