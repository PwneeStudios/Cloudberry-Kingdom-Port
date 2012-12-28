#include <global_header.h>

namespace CloudberryKingdom
{

	ComputerRecording::ComputerRecording() :
		IsFromPool( false ),
		Sparse( false ), SuperSparse( false )
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
		for ( int i = 0; i < static_cast<int>( Input.size() ); i++ )
			Input[ i ].Clean();
		for ( int i = 0; i < static_cast<int>( AutoJump.size() ); i++ )
			AutoJump[ i ] = 0;
		for ( int i = 0; i < static_cast<int>( AutoLocs.size() ); i++ )
			AutoLocs[ i ] = Vector2();
		for ( int i = 0; i < static_cast<int>( AutoVel.size() ); i++ )
			AutoVel[ i ] = Vector2();
		for ( int i = 0; i < static_cast<int>( BoxCenter.size() ); i++ )
			BoxCenter[ i ] = Vector2();
		for ( int i = 0; i < static_cast<int>( AutoOnGround.size() ); i++ )
			AutoOnGround[ i ] = false;
		for ( int i = 0; i < static_cast<int>( Anim.size() ); i++ )
			Anim[ i ] = 0;
		for ( int i = 0; i < static_cast<int>( t.size() ); i++ )
			t[ i ] = 0;
		for ( int i = 0; i < static_cast<int>( Alive.size() ); i++ )
			Alive[ i ] = false;
	}

	bool ComputerRecording::GetAlive( int Step )
	{
		//if (!SuperSparse)
			return Alive[ Step ];
		//else
		//    return Alive[Step / PareDivider];
	}

	unsigned char ComputerRecording::GetAnim( int Step )
	{
		if ( !SuperSparse )
			return Anim[ Step ];
		else
			return Anim[ Step / PareDivider ];
	}

	float ComputerRecording::Gett( int Step )
	{
		if ( !SuperSparse )
			return t[ Step ];
		else
			return t[ Step / PareDivider ];
	}

	Vector2 ComputerRecording::GetBoxCenter( int Step )
	{
		//if (!SuperSparse)
		if ( true )
			return BoxCenter[ Step ];
		else
		{
			//return BoxCenter[Step / PareDivider];

			int i1 = Step / PareDivider;
			int i2 = i1 + 1;
			if ( i2 >= static_cast<int>( BoxCenter.size() ) )
				i2 = i1;

			Vector2 p1 = BoxCenter[ i1 ];
			Vector2 p2 = BoxCenter[ i2 ];

			float t = static_cast<float>( i1 * PareDivider - Step ) / static_cast<float>( PareDivider );
			return Vector2::Lerp( p2, p1, t );
		}
	}

	template<typename T>
	std::vector<T> ComputerRecording::PareDown( std::vector<T> SourceArray )
	{
		int n = static_cast<int>( SourceArray.size() );
		int m = n / PareDivider;
		std::vector<T> ParedArray = std::vector<T>( m );

		for ( int i = 0; i < m; i++ )
			ParedArray[ i ] = SourceArray[ i * PareDivider ];

		return ParedArray;
	}

	void ComputerRecording::ConvertToSuperSparse()
	{
		Input.clear();
		AutoJump.clear();
		AutoLocs.clear();
		AutoVel.clear();
		AutoOnGround.clear();

		if ( !SuperSparse )
		{
			//BoxCenter = PareDown<Vector2>(BoxCenter);
			//Alive = PareDown<bool>(Alive);
			t = PareDown<float>( t );
			Anim = PareDown<unsigned char>( Anim );

			SuperSparse = true;
		}
	}

	void ComputerRecording::Release()
	{
		if ( IsFromPool )
		{
			ToPool( shared_from_this() );
			return;
		}

		Alive.clear();
		Anim.clear();
		AutoJump.clear();
		AutoLocs.clear();
		AutoOnGround.clear();
		AutoVel.clear();
		BoxCenter.clear();
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

		BoxCenter = std::vector<Vector2>( length );
		AutoLocs = std::vector<Vector2>( length );
		AutoVel = std::vector<Vector2>( length );
		Input = std::vector<BobInput>( length );

		Anim = std::vector<unsigned char>( length );
		t = std::vector<float>( length );

		Alive = std::vector<bool>( length );

		if ( !Sparse )
		{
			AutoJump = std::vector<int>( length );
			AutoOnGround = std::vector<bool>( length );
		}
		else
			Tools::Nothing();
	}
}
