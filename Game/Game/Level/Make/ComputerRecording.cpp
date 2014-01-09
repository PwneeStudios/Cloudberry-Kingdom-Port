#include <small_header.h>
#include "Game/Level/Make/ComputerRecording.h"

#include "Core/WriteReadTools.h"
#include "Game/Objects/Bob/BobInput.h"
#include "Game/Objects/Bob/Bob.h"


namespace CloudberryKingdom
{

	ComputerRecording::ComputerRecording() :
		IsFromPool( false ),
		Released( false ),
		Sparse( false ),
		SuperSparse( false )
	{
	}

	void ComputerRecording::InitializeStatics()
	{
		ComputerRecording::Pool = std::stack<boost::shared_ptr<ComputerRecording> >();
		ComputerRecording::PareDivider = 4;
	}

	// Statics
	std::stack<boost::shared_ptr<ComputerRecording> > ComputerRecording::Pool;
	int ComputerRecording::PareDivider;

	void ComputerRecording::FillPool()
	{
		boost::shared_ptr<ComputerRecording> record = boost::make_shared<ComputerRecording>();
		record->Init( 7000, false );
		record->IsFromPool = true;
		Pool.push( record );
	}

	void ComputerRecording::InitPool()
	{
		Pool = std::stack<boost::shared_ptr<ComputerRecording> >();
		for ( int i = 0; i < 20; i++ )
			FillPool();
	}

	boost::shared_ptr<ComputerRecording> ComputerRecording::FromPool()
	{
		if ( Pool.empty() )
			FillPool();

		boost::shared_ptr<ComputerRecording> popped = Pool.top();
		Pool.pop();
		popped->Clean();

		return popped;
	}

	void ComputerRecording::ToPool( const boost::shared_ptr<ComputerRecording> &record )
	{
		if ( record->Released ) return;

		record->Released = true;

		Pool.push( record );
	}

	void ComputerRecording::Shift( Vector2 shift )
	{
		if ( AutoLocs.empty() )
			return;

		for ( int i = 0; i < static_cast<int>( AutoLocs.size() ); i++ )
			AutoLocs[ i ] += shift;
	}

	void ComputerRecording::Write( const boost::shared_ptr<BinaryWriter> &writer, int Length )
	{
		for ( int frame = 0; frame < Length; frame++ )
		{
			writer->Write( AutoLocs[ frame ] );
			//writer.Write(BoxCenter[frame]);
			//writer.Write(AutoOnGround[frame]);
			Input[ frame ].Write( writer );
		}
	}

	void ComputerRecording::Read( const boost::shared_ptr<BinaryReader> &reader, int Length )
	{
		for ( int frame = 0; frame < Length; frame++ )
		{
			AutoLocs[ frame ] = reader->ReadVector2();
			//BoxCenter[frame] = reader.ReadVector2();
			//AutoOnGround[frame] = reader.ReadBoolean();
			Input[ frame ].Read( reader );
		}
	}

	void ComputerRecording::Clean()
	{
		Released = false;

		for ( int i = 0; i < static_cast<int>( Input.size() ); i++ )
			Input[ i ].Clean();
		for ( int i = 0; i < static_cast<int>( AutoJump.size() ); i++ )
			AutoJump[ i ] = 0;
		for ( int i = 0; i < static_cast<int>( AutoLocs.size() ); i++ )
			AutoLocs[ i ] = Vector2();
		for ( int i = 0; i < static_cast<int>( AutoVel.size() ); i++ )
			AutoVel[ i ] = Vector2();
		for ( int i = 0; i < static_cast<int>( Box_BL.size() ); i++ )
			Box_BL[ i ] = 0;
		for ( int i = 0; i < static_cast<int>( Box_Size.size() ); i++ )
			Box_Size[ i ] = 0;
		for ( int i = 0; i < static_cast<int>( AutoOnGround.size() ); i++ )
			AutoOnGround[ i ] = false;
		for ( int i = 0; i < static_cast<int>( t.size() ); i++ )
			t[ i ] = 0;
	}

	int ComputerRecording::Gett( int Step )
	{
		return t[ Step ];
	}

	Vector2 ComputerRecording::GetBoxCenter( int Step )
	{
		return Bob::UnpackIntIntoVector_Pos( Box_BL[ Step ] ) + GetBoxSize( Step ) / 2.0f;
	}

	Vector2 ComputerRecording::GetBoxSize( int Step )
	{
		return Bob::UnpackIntIntoVector_Size( Box_Size[ Step ] );
	}

	void ComputerRecording::ConvertToSuperSparse( int Step )
	{
		if ( !Sparse ) return;
		if ( SuperSparse ) return;

		std::vector<BobInput>( ).swap( Input );
		std::vector<int>( ).swap( AutoJump );
		std::vector<Vector2>( ).swap( AutoLocs );
		std::vector<Vector2>( ).swap( AutoVel );
		std::vector<bool>( ).swap( AutoOnGround );

		Box_BL.resize( Step + 1 );
		Box_Size.resize( Step + 1 );
		t.resize( Step + 1);
		std::vector<unsigned int>( Box_BL	).swap( Box_BL  );
		std::vector<unsigned int>( Box_Size ).swap( Box_Size );
		std::vector<int>		 ( t		).swap( t		 );

		SuperSparse = true;
	}

	void ComputerRecording::Release()
	{
		if ( IsFromPool )
		{
			ToPool( shared_from_this() );
			return;
		}

		std::vector<BobInput>( ).swap( Input );
		std::vector<int>( ).swap( AutoJump );
		std::vector<Vector2>( ).swap( AutoLocs );
		std::vector<Vector2>( ).swap( AutoVel );
		std::vector<bool>( ).swap( AutoOnGround );
		std::vector<unsigned int>( ).swap( Box_BL  );
		std::vector<unsigned int>( ).swap( Box_Size );
		std::vector<int>		 ( ).swap( t		 );
	}

	void ComputerRecording::Init( int length )
	{
		Init( length, true );
	}

	void ComputerRecording::Init( int length, bool Sparse )
	{
		this->Sparse = Sparse;

		Box_BL   = std::vector<unsigned int>( length );
		Box_Size = std::vector<unsigned int>( length );
		AutoLocs = std::vector<Vector2>( length );
		AutoVel  = std::vector<Vector2>( length );
		Input    = std::vector<BobInput>( length );

		t = std::vector<int>( length );

		if ( !Sparse )
		{
			AutoJump = std::vector<int>( length );
			AutoOnGround = std::vector<bool>( length );
		}
	}
}
