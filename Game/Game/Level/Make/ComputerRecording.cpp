#include <global_header.h>

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
		if ( SuperSparse ) return;

		Input.clear();
		AutoJump.clear();
		AutoLocs.clear();
		AutoVel.clear();
		AutoOnGround.clear();

		Box_BL.resize( Step + 1, 0 );
		Box_Size.resize( Step + 1, 0 );
		t.resize( Step + 1, 0 );

		SuperSparse = true;
	}

	void ComputerRecording::Release()
	{
		if ( IsFromPool )
		{
			ToPool( shared_from_this() );
			return;
		}

		AutoJump.clear();
		AutoLocs.clear();
		AutoOnGround.clear();
		AutoVel.clear();
		Box_BL.clear();
		Box_Size.clear();
		Input.clear();
		t.clear();
	}

	void ComputerRecording::Init( int length )
	{
		Init( length, false );
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
