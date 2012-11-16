#include <global_header.h>

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;


namespace CloudberryKingdom
{

bool AutoGen_Parameters::IntelliSpread = true;

	int AutoGen_Parameters::ChooseOffset( int Period, const std::shared_ptr<Rand> &Rnd )
	{
		if ( AutoGen_Parameters::IntelliSpread )
			return Counter++ % NumOffsets * Period / NumOffsets;
		else
			return Rnd->Rnd->Next( 0, NumOffsets ) * Period / NumOffsets;
	}

	int AutoGen_Parameters::EnforceOffset( int offset, int period )
	{
		int offset_size = period / NumOffsets;
		return static_cast<int>( offset / offset_size ) * offset_size;
	}

	void AutoGen_Parameters::SetParameters( const std::shared_ptr<PieceSeedData> &PieceSeed, const std::shared_ptr<Level> &level )
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

	std::shared_ptr<AutoGen_Parameters> AutoGen::SetParameters( const std::shared_ptr<PieceSeedData> &data, const std::shared_ptr<Level> &level )
	{
		return 0;
	}

	std::shared_ptr<ObjectBase> AutoGen::CreateAt( const std::shared_ptr<Level> &level, Vector2 pos )
	{
		return 0;
	}

	std::shared_ptr<ObjectBase> AutoGen::CreateAt( const std::shared_ptr<Level> &level, Vector2 pos, Vector2 BL, Vector2 TR )
	{
		return 0;
	}

	void AutoGen::PreFill_1( const std::shared_ptr<Level> &level, Vector2 BL, Vector2 TR )
	{
	}

	void AutoGen::PreFill_2( const std::shared_ptr<Level> &level, Vector2 BL, Vector2 TR )
	{
	}

	void AutoGen::ActiveFill_1( const std::shared_ptr<Level> &level, Vector2 BL, Vector2 TR )
	{
	}

	void AutoGen::Cleanup_1( const std::shared_ptr<Level> &level, Vector2 BL, Vector2 TR )
	{
	}

	void AutoGen::Cleanup_2( const std::shared_ptr<Level> &level, Vector2 BL, Vector2 TR )
	{
	}
}
