#include "BlockEmitter.h"
#include "Game/Tools/Recycler.h"
#include "Game/Level/Make/PieceSeedData.h"
#include "Core/Tools/CoreMath.h"
#include "Game/Objects/In Game Objects/Grab/CloudberryKingdom.Level.h"

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::IO;
using namespace Microsoft::Xna::Framework;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;

namespace CloudberryKingdom
{

	void BlockEmitter::Release()
	{
		ObjectBase::Release();

		Platforms.clear();
	}

	void BlockEmitter::OnUsed()
	{
		for ( std::vector<MovingPlatform*>::const_iterator platform = Platforms.begin(); platform != Platforms.end(); ++platform )
			( *platform )->getCore()->GenData->Used = true;
	}

	void BlockEmitter::OnMarkedForDeletion()
	{
		if ( !getCore()->DeletedByBob )
			return;

		// Delete all children platforms
		for ( std::vector<MovingPlatform*>::const_iterator platform = Platforms.begin(); platform != Platforms.end(); ++platform )
		{
			( *platform )->Parent.reset(); // Make sure we destroy this connection to prevent an infinite recursion
			( *platform )->CollectSelf();
		}

		Platforms.clear();
	}

	void BlockEmitter::MakeNew()
	{
		Platforms.clear();

		MyMoveType = MovingPlatform::MoveType_NORMAL;
		Amp = 0;

		Active = true;

		getCore()->Init();
		getCore()->MyType = ObjectType_BLOCK_EMITTER;
		getCore()->DrawLayer = 1;
		GiveLayer = false;

		Range = Vector2( 8000, 3000 );
		GiveCustomRange = false;

		if ( DoPreEmit )
			SetToPreEmit = true;
	}

	BlockEmitter::BlockEmitter( bool BoxesOnly )
	{
		InitializeInstanceFields();
		getCore()->BoxesOnly = BoxesOnly;

		MakeNew();
	}

	void BlockEmitter::Reset( bool BoxesOnly )
	{
		if ( DoPreEmit )
			SetToPreEmit = true;
	}

	void BlockEmitter::PreEmit()
	{
		SetToPreEmit = false;

		int step = Offset - Delay;
		if ( Offset == 0 )
			step = 0;
		for ( ; step > -60 * 10; step -= Delay )
			Emit( step );
	}

	void BlockEmitter::Emit( int offset )
	{
		std::shared_ptr<MovingPlatform> block = static_cast<MovingPlatform*>( getCore()->getRecycle()->GetObject(ObjectType_MOVING_PLATFORM, getCore()->BoxesOnly) );

		block->Parent = this;
		block->Init( EmitData.Position, Size, getMyLevel(), MyBoxStyle );

		if ( GiveLayer )
			block->getCore()->DrawLayer = getCore()->DrawLayer;

		block->getCore()->Tag = getCore()->Tag;

		block->getCore()->Active = true;
		block->Range = Range;
		if ( getCore()->MyLevel->Geometry == LevelGeometry_UP || getCore()->MyLevel->Geometry == LevelGeometry_DOWN )
			block->Range.X = 300;
		else
			block->Range.Y = 300;
		if ( GiveCustomRange )
			block->Range = Range;

		EmitData.Acceleration.Y = EmitData.Velocity.Y;
		block->getCore()->StartData = block->getBlockCore()->Data = EmitData;

		block->MyMoveType = MyMoveType;
		block->Amp = Amp;
		block->Offset = offset;

		// Set Gen data
		if ( getCore()->BoxesOnly )
		{
			block->getCore()->GenData.RemoveIfOverlap = getCore()->GenData.RemoveIfOverlap;
			block->getBlockCore()->Virgin = true;
			block->getBlockCore()->Finalized = true;
			block->getCore()->GenData.AlwaysLandOn_Reluctantly = true;
		}

		getCore()->MyLevel->AddBlock(block);
		AddPlatform( block );
		block->getCore()->WakeUpRequirements = true;
	}

	void BlockEmitter::AddPlatform( const std::shared_ptr<MovingPlatform> &platform )
	{
		Platforms.push_back( platform );
	}

	void BlockEmitter::RemovePlatform( const std::shared_ptr<MovingPlatform> &platform )
	{
		Platforms.Remove( platform );
	}

	void BlockEmitter::PhsxStep()
	{
		if ( SetToPreEmit )
			PreEmit();

		if ( !Active )
			return;

		if ( !AlwaysOn )
			if ( getCore()->Data.Position.X > getCore()->MyLevel->getMainCamera()->TR.X + Range.X || getCore()->Data.Position.X < getCore()->MyLevel->getMainCamera()->BL.X - Range.X || getCore()->Data.Position.Y > getCore()->MyLevel->getMainCamera()->TR.Y + Range.Y || getCore()->Data.Position.Y < getCore()->MyLevel->getMainCamera()->BL.Y - Range.Y )
			{
				getCore()->SkippedPhsx = true;
				return;
			}
		getCore()->SkippedPhsx = false;

		if ( CoreMath::Modulo( getCore()->GetPhsxStep(), Delay ) == Offset )
		{
			Emit( getCore()->MyLevel->CurPhsxStep );
		}
	}

	void BlockEmitter::Move( Vector2 shift )
	{
		ObjectBase::Move( shift );

		EmitData.Position += shift;
	}

	void BlockEmitter::Init( Vector2 pos, const std::shared_ptr<Level> &level, BlockEmitter_Parameters::BoxStyle MyBoxStyle )
	{
		ObjectBase::Init( pos, level );

		this->MyBoxStyle = MyBoxStyle;
	}

	void BlockEmitter::Clone( const std::shared_ptr<ObjectBase> &A )
	{
		getCore()->Clone(A->getCore());

		std::shared_ptr<BlockEmitter> EmitterA = dynamic_cast<BlockEmitter*>( A );
		Init( A->getPos(), A->getMyLevel(), EmitterA->MyBoxStyle );

		EmitData = EmitterA->EmitData;
		Delay = EmitterA->Delay;
		Offset = EmitterA->Offset;
		Size = EmitterA->Size;
		GiveLayer = EmitterA->GiveLayer;

		Amp = EmitterA->Amp;
		MyMoveType = EmitterA->MyMoveType;

		Range = EmitterA->Range;
		GiveCustomRange = EmitterA->GiveCustomRange;
	}

	void BlockEmitter::InitializeInstanceFields()
	{
		Platforms = std::vector<MovingPlatform*>();
		DoPreEmit = true;
		SetToPreEmit = false;
		GiveCustomRange = false;
		GiveLayer = false;
	}
}
