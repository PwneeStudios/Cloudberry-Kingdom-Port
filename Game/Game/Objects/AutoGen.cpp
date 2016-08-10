#include <small_header.h>
#include "Game/Objects/AutoGen.h"

#include "Core/Tools/Random.h"
#include "Game/Objects/ObjectBase.h"
#include "Game/Level/Make/PieceSeedData.h"
#include "Game/Level/Make/Parameters/Param.h"
#include "Game/Level/Make/Parameters/Upgrades.h"
#include "Game/Objects/In Game Objects/Grab/MakeData.h"
#include "Game/Level/Level.h"
#include "Game/Tools/Unset.h"


namespace CloudberryKingdom
{

	AutoGen::AutoGen() :
		Do_WeightedPreFill_1( false ), Do_PreFill_1( false ), Do_PreFill_2( false ), Do_ActiveFill_1( false ), Do_ActiveFill_2( false )
	{
	}

	const bool IntelliSpread = true;

	int AutoGen_Parameters::ChooseOffset( int Period, const boost::shared_ptr<Rand> &Rnd )
	{
		if ( IntelliSpread )
			return Counter++ % NumOffsets * Period / NumOffsets;
		else
			return Rnd->Rnd->Next( 0, NumOffsets ) * Period / NumOffsets;
	}

	int AutoGen_Parameters::EnforceOffset( int offset, int period )
	{
		int offset_size = period / NumOffsets;
		return static_cast<int>( offset / offset_size ) * offset_size;
	}

	void AutoGen_Parameters::SetParameters( const boost::shared_ptr<PieceSeedData> &PieceSeed, const boost::shared_ptr<Level> &level )
	{
		this->PieceSeed = PieceSeed;
	}

	void AutoGen_Parameters::SetVal( Vector2 &val, Vector2 newval )
	{
		if ( val != Unset::Vector )
			return;

		val = newval;
	}

	void AutoGen_Parameters::SetVal( float &val, float newval )
	{
		if ( val != Unset::Float )
			return;

		val = newval;
	}

	void AutoGen_Parameters::SetVal( int &val, int newval )
	{
		if ( val != Unset::Int )
			return;

		val = newval;
	}

	void AutoGen_Parameters::InitializeInstanceFields()
	{
		Counter = 0;
		Masochistic = false;
		NumAngles = 2;
		NumPeriods = 2;
		NumOffsets = 3;
		DoStage2Fill = true;
	}

	boost::shared_ptr<AutoGen_Parameters> AutoGen::SetParameters( const boost::shared_ptr<PieceSeedData> &data, const boost::shared_ptr<Level> &level )
	{
		return 0;
	}

	boost::shared_ptr<ObjectBase> AutoGen::CreateAt( const boost::shared_ptr<Level> &level, Vector2 pos )
	{
		return 0;
	}

	boost::shared_ptr<ObjectBase> AutoGen::CreateAt( const boost::shared_ptr<Level> &level, Vector2 pos, Vector2 BL, Vector2 TR )
	{
		return 0;
	}

	void AutoGen::PreFill_1( const boost::shared_ptr<Level> &level, Vector2 BL, Vector2 TR )
	{
	}

	void AutoGen::PreFill_2( const boost::shared_ptr<Level> &level, Vector2 BL, Vector2 TR )
	{
	}

	void AutoGen::ActiveFill_1( const boost::shared_ptr<Level> &level, Vector2 BL, Vector2 TR )
	{
	}

	void AutoGen::Cleanup_1( const boost::shared_ptr<Level> &level, Vector2 BL, Vector2 TR )
	{
	}

	void AutoGen::Cleanup_2( const boost::shared_ptr<Level> &level, Vector2 BL, Vector2 TR )
	{
	}
}
