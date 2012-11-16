#include "ComputerRecording.h"
#include "Game/Objects/Bob/BobInput.h"

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::IO;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Text;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;
using namespace Microsoft::Xna::Framework;

namespace CloudberryKingdom
{

std::stack<ComputerRecording*> ComputerRecording::Pool = 0;

	void ComputerRecording::FillPool()
	{
		std::shared_ptr<ComputerRecording> record = std::make_shared<ComputerRecording>();
		record->Init( 7000, false );
		record->IsFromPool = true;
		Pool.push( record );
	}

	void ComputerRecording::InitPool()
	{
		Pool = std::stack<ComputerRecording*>();
		for ( int i = 0; i < 20; i++ )
			FillPool();
	}

	std::shared_ptr<ComputerRecording> ComputerRecording::FromPool()
	{
		if ( Pool.empty() )
			FillPool();

		std::shared_ptr<ComputerRecording> popped = Pool.pop();
		popped->Clean();

		return popped;
	}

	void ComputerRecording::ToPool( const std::shared_ptr<ComputerRecording> &record )
	{
		Pool.push( record );
	}

	void ComputerRecording::Shift( Vector2 shift )
	{
		if ( AutoLocs.empty() )
			return;

		for ( int i = 0; i < AutoLocs.size(); i++ )
			AutoLocs[ i ] += shift;
	}

int ComputerRecording::PareDivider = 4;

	void ComputerRecording::Write( const std::shared_ptr<BinaryWriter> &writer, int Length )
	{
		for ( int frame = 0; frame < Length; frame++ )
		{
			writer->Write( AutoLocs[ frame ] );
			//writer.Write(BoxCenter[frame]);
			//writer.Write(AutoOnGround[frame]);
			Input[ frame ].Write( writer );
		}
	}

	void ComputerRecording::Read( const std::shared_ptr<BinaryReader> &reader, int Length )
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
		for ( int i = 0; i < Input.size(); i++ )
			Input[ i ].Clean();
		for ( int i = 0; i < AutoJump.size(); i++ )
			AutoJump[ i ] = 0;
		for ( int i = 0; i < AutoLocs.size(); i++ )
			AutoLocs[ i ] = Vector2::Zero;
		for ( int i = 0; i < AutoVel.size(); i++ )
			AutoVel[ i ] = Vector2::Zero;
		for ( int i = 0; i < BoxCenter.size(); i++ )
			BoxCenter[ i ] = Vector2::Zero;
		for ( int i = 0; i < AutoOnGround.size(); i++ )
			AutoOnGround[ i ] = false;
		for ( int i = 0; i < Anim.size(); i++ )
			Anim[ i ] = 0;
		for ( int i = 0; i < t.size(); i++ )
			t[ i ] = 0;
		for ( int i = 0; i < Alive.size(); i++ )
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

	Microsoft::Xna::Framework::Vector2 ComputerRecording::GetBoxCenter( int Step )
	{
		//if (!SuperSparse)
		if ( true )
			return BoxCenter[ Step ];
		else
		{
			//return BoxCenter[Step / PareDivider];

			int i1 = Step / PareDivider;
			int i2 = i1 + 1;
			if ( i2 >= BoxCenter.size() )
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
		int n = SourceArray.size();
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
			ToPool( this );
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
	}
}
